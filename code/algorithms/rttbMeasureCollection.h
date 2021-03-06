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

#ifndef __MEASURE_COLLECTION_H
#define __MEASURE_COLLECTION_H

#include <map>
#include <rttbCommon.h>

#include "rttbBaseType.h"

#include "RTTBAlgorithmsExports.h"

namespace rttb
{

	namespace algorithms
	{
		/*! @class MeasureCollection
		@brief This class handels the access to the MeasureCollection elements and defines which names can be used for them
		*/
		class RTTBAlgorithms_EXPORT MeasureCollection {

		public:
      rttbClassMacroNoParent(MeasureCollection)
			enum complexStatistics { Dx, Vx, MOHx, MOCx, MaxOHx, MinOCx };

		protected:
			complexStatistics _name;

		public:
			complexStatistics getName() const;

		protected:
			double getSpecificValue(const std::map<double, double>& values, double key, bool findNearestValueInstead, double& storedKey) const;
			std::map<double, double>::const_iterator findNearestKeyInMap(const std::map<double, double>& values, double key) const;
		};
	}
}


#endif
