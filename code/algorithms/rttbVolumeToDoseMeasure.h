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
// @version $Revision: 1674 $ (last changed revision)
// @date    $Date: 2017-01-27 10:34:46 +0100 (Fr, 27 Jan 2017) $ (last change date)
// @author  $Author: hentsch $ (last changed by)
*/

#ifndef __VOLUME_TO_DOSE_MEASURE_H
#define __VOLUME_TO_DOSE_MEASURE_H

#include "rttbMeasureInterface.h"

namespace rttb
{

	namespace algorithms
	{
		class RTTBAlgorithms_EXPORT VolumeToDoseMeasure : public MeasureInterface {

		public:
			typedef std::map<VolumeType, DoseTypeGy> VolumeToDoseFunctionType;

		private:
			complexStatistics name;
			VolumeToDoseFunctionType values;
			VolumeType _volume;

		public:
			VolumeToDoseMeasure(complexStatistics name, VolumeToDoseFunctionType values = std::map<VolumeType, DoseTypeGy>(), VolumeType volume = -1);
			void insertValue(std::pair<VolumeType, DoseTypeGy> value);
			DoseTypeGy getValue(VolumeType xVolumeAbsolute) const;
			DoseTypeGy getValue(VolumeType xVolumeAbsolute, bool findNearestValue, VolumeType& nearestXDose) const;
			DoseTypeGy getValueRelative(VolumeType xDoseRelative) const;
			DoseTypeGy getValueRelative(VolumeType xDoseRelative, bool findNearestValue, VolumeType& nearestXDose) const;
			VolumeToDoseFunctionType getAllValues() const;
			friend bool operator==(const VolumeToDoseMeasure& volumeToDoseMesure, const VolumeToDoseMeasure& otherVolumeToDoseMesure);
			void setVolume(VolumeType volume);
		private:
			double getSpecificValue(double key, bool findNearestValueInstead, double& storedKey) const;
		};
	}
}


#endif