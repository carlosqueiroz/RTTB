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

#ifndef __CONFORMAL_INDEX_H
#define __CONFORMAL_INDEX_H


#include "rttbDoseIndex.h"
#include "rttbBaseType.h"

namespace rttb{

  namespace indices{

    /*! @class ConformalIndex
		@brief This class representing a ConformalIndex Object. Conformal Index (COIN)= Conformation Number(CN)* (1-Vref,0/Vnt,0)*(1-Vref,1/Vnt,1)... i: i-th critiacal organ
		Conformation Number (CN)= (TVref/TV) * (TVref/Vref)
		@ingroup indices
    */
    class ConformalIndex: public DoseIndex
    {
    protected: 
      /*! @brief Calculate conformal index
		  @exception InvalidParameterException Thrown if dvhSet or aDoseReference invalid
      */
      bool calcIndex();
      

    public: 
      /*! @brief Constructor
      */
      ConformalIndex(core::DVHSet* dvhSet, DoseTypeGy aDoseReference);

      /*! @return Return true if calcIndex() finished
		  @exception NullPointerException thrown if dvhSet is NULL
      */
      bool init();

      /*! @brief Dose index calculation for tvIndex-th treated volume
          @param tvIndex index in the DVH in the current set of tv-DVHs
          @return Return index value 
          @exception InvalidParameterException Thrown if tvIndex or aDoseReference invalid
      */
      IndexValueType getDoseIndexAt(const GridIndexType tvIndex);

    };

  }
}

#endif