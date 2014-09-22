// -----------------------------------------------------------------------
// RTToolbox - DKFZ radiotherapy quantitative evaluation library
//
// Copyright (c) German Cancer Research Center (DKFZ),
// Software development for Integrated Diagnostics and Therapy (SIDT).
// ALL RIGHTS RESERVED.
// See rttbCopyright.txt or
// http://www.dkfz.de/en/sidt/projects/rttb/copyright.html
//
// This software is distributed WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the above copyright notices for more information.
//
//------------------------------------------------------------------------
/*!
// @file
// @version $Revision$ (last changed revision)
// @date    $Date$ (last change date)
// @author  $Author$ (last changed by)
*/

#ifndef __INTERPOLATION_BASE_H
#define __INTERPOLATION_BASE_H

#include <vector>
#include <assert.h>

#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/array.hpp>

#include "rttbDoseAccessorInterface.h"
#include "rttbBaseType.h"

namespace rttb
{
	namespace interpolation
	{

		/*! @class InterpolationBase
			@brief Base class for interpolation.
			@ingroup interpolation
		*/
		class InterpolationBase
		{
		public:
			typedef boost::shared_ptr<InterpolationBase> Pointer;
			typedef rttb::core::DoseAccessorInterface::DoseAccessorPointer DoseAccessorPointer;

			/*! @brief Constructor
			*/
			InterpolationBase() {};

			/*! @brief Virtual destructor of base class
			*/
			virtual ~InterpolationBase() {};

			/*! @brief Sets the DoseAccessPointer
				@pre originalDose initialized
				@exception core::NullPointerException if originalDose==NULL
			*/
			void setDoseAccessorPointer(const DoseAccessorPointer originalDose);

			/*! @brief Returns the interpolated value for the given world coordinate
			*/
			virtual DoseTypeGy getValue(const WorldCoordinate3D& aWorldCoordinate) const = 0;

		protected:
			DoseAccessorPointer _spOriginalDose;
			/*! @brief determines voxels in a certain neighborhood of a physical based coordinate and converts in a standard cube with corner points [0 0 0], [1 0 0], [0 1 0], [1 1 0], [0 0 1], [1 0 1], [0 1 1], [1 1 1].
				@param aWorldCoordinate the coordinate where to start
				@param neighborhood voxel around coordinate (currently only 0 and 8 implemented)
				@param target coordinates inside the standard cube with values [0 1] in each dimension.
				@param values dose values at all corner points of the standard cube. Is of type boost:shared_array[neighborhood]
				@pre target and values have to be correctly initialized (e.g. boost::array<double, 3> target = {0.0, 0.0, 0.0}; boost::shared_array<DoseTypeGy> values(new DoseTypeGy[8]()); where 8 is neighborhood)
				@exception core::InvalidParameterException if neighborhood =! 0 && !=8
				@exception core::MappingOutsideOfImageException if initial mapping of aWorldCoordinate is outside image
				@exception core::NullPointerException if dose is NULL
				@todo use shared_ptr[] with boost >1.52 instead of shared_array
			*/
			void getNeighborhoodVoxelValues(const WorldCoordinate3D& aWorldCoordinate,
											unsigned int neighborhood, boost::array<double, 3>& target,
											boost::shared_array<DoseTypeGy> values) const;

			/*! @brief returns the nearest inside voxel value
				@pre the voxelGridIndex is outside the image and voxelGridIndex>image.size() for all dimensions. Also voxelGridIndex[]>=0 for all dimensions
				@note used for virtually expanding the image by one voxel as edge handling
			*/
			DoseTypeGy getNearestInsideVoxelValue(const VoxelGridIndex3D& currentVoxelIndex) const;
		};

	}
}

#endif