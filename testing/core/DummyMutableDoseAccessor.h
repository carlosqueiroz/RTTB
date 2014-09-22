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
#ifndef __DUMMY_MUTABLE_DOSE_ACCESSOR_H
#define __DUMMY_MUTABLE_DOSE_ACCESSOR_H

#include <vector>

#include "rttbMutableDoseAccessorInterface.h"
#include "rttbGeometricInfo.h"
#include "rttbBaseType.h"


namespace rttb
{
	namespace testing
	{

		/*! @class DummyMutableDoseAccessor
			@brief A dummy MutableDoseAccessor for testing filled with random dose values between 0 and 100.
			The default grid size is [11,10,5]
		*/
		class DummyMutableDoseAccessor: public core::MutableDoseAccessorInterface
		{

		private:
			/*! vector of dose data(absolute Gy dose/doseGridScaling)*/
			std::vector<DoseTypeGy> doseData;

			IDType _doseUID;


		public:
			~DummyMutableDoseAccessor();

			/*! @brief A dummy DummyMutableDoseAccessor for testing filled with random dose values between 0 and 100.
				    The default grid size is [11,10,5]
			    */
			DummyMutableDoseAccessor();

			/*! @brief Constructor.
				Initialisation of dose with a given vector.
			*/
			DummyMutableDoseAccessor(const std::vector<DoseTypeGy>& aDoseVector,
			                         const core::GeometricInfo& geoInfo);

			const std::vector<DoseTypeGy>* getDoseVector() const
			{
				return &doseData;
			};

			DoseTypeGy getDoseAt(const VoxelGridID aID) const;

			DoseTypeGy getDoseAt(const VoxelGridIndex3D& aIndex) const;

			void setDoseAt(const VoxelGridID aID, DoseTypeGy value);

			void setDoseAt(const VoxelGridIndex3D& aIndex, DoseTypeGy value);

			const IDType getDoseUID() const
			{
				return _doseUID;
			};
		};
	}
}

#endif