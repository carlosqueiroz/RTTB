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
#include "rttbBaseTypeModels.h"


namespace rttb
{
	namespace models
	{
		/*! @brief Calculate biological LinearQuadratic Model of a dose
		@details \f$LQ = exp(-\frac{alpha*d+beta*d^2}{nFractions})\f$
		@param dose
		@param alpha
		@param beta
        @param nFractions the number of fractions
		@pre dose>=0
		@pre alpha>=0
		@pre beta>=0
		@return The LQ value
		@exception rttb::core::InvalidParameterException Thrown if parameters were not set correctly.
		*/
		BioModelValueType calcLQ(DoseTypeGy dose, DoseCalcType alpha,
		                         DoseCalcType beta, unsigned int nFractions=1);
	}
}