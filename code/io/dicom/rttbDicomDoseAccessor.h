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
#ifndef __DICOM_DOSE_ACCESSOR_H
#define __DICOM_DOSE_ACCESSOR_H

#include <string>
#include <vector>
#include <exception>

#include <boost/shared_ptr.hpp>

#include "osconfig.h"    /* make sure OS specific configuration is included first */
#include "drtdose.h"

#include "rttbDoseAccessorInterface.h"
#include "rttbBaseType.h"


namespace rttb
{
	namespace io
	{
		namespace dicom
		{

			/*! @class DicomDoseAccessor
			@brief This class gives access to dose information from DRTDoseIOD
			*/
			class DicomDoseAccessor: public core::DoseAccessorInterface
			{
			public:
				typedef boost::shared_ptr<DRTDoseIOD> DRTDoseIODPtr;

			private:
				DRTDoseIODPtr _dose;

				/*! vector of dose data(absolute Gy dose/doseGridScaling)*/
				std::vector<Uint16> doseData;

				double _doseGridScaling;

				IDType _doseUID;

				DicomDoseAccessor();

			protected:
				/*! @brief Initialize dose data
				@exception InvalidDoseException Thrown if _dose is invalid: one of column/row/numberOfFrames/doseGridScaling/pixelSpacing=0
				@exception DcmrtException Throw if dcmrt error
				@exception boost/bad_lexical_cast Thrown if the imported header tags are not numerical.
				*/
				bool begin();

				/*! @brief get all required data from dicom information contained in _dose
				@exception boost/bad_lexical_cast Thrown if the imported header tags are not numerical.
				*/
				bool assembleGeometricInfo();


			public:
				~DicomDoseAccessor();

				/*! @brief Constructor. Initialisation with a boost::shared_ptr of DRTDoseIOD
				@exception DcmrtException Throw if dcmrt error
				*/
				DicomDoseAccessor(DRTDoseIODPtr aDRTDoseIODP);

				DoseTypeGy getDoseAt(const VoxelGridID aID) const;

				DoseTypeGy getDoseAt(const VoxelGridIndex3D& aIndex) const;

				const IDType getDoseUID() const
				{
					return _doseUID;
				};
			};
		}
	}
}

#endif