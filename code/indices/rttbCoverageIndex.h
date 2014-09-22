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
#ifndef __COVERAGE_INDEX_H
#define __COVERAGE_INDEX_H

#include <string>
#include <vector>

#include "rttbDoseIndex.h"
#include "rttbBaseType.h"
#include "rttbDVHSet.h"

namespace rttb{

  namespace indices{

    /*! @class CoverageIndex
        @brief This class representing a CoverageIndex Object. Coverage Index fraction of the target volume receiving a dose >= the reference dose
		@ingroup indices
    */
    class CoverageIndex: public DoseIndex
    {

    protected: 
      /*! @brief Calculate conformation number
          @exception InvalidParameterException Thrown if dvhSet invalid
      */
      bool calcIndex();

      
    public: 
      /*! @brief Constructor
      */
      CoverageIndex(core::DVHSet* dvhSet, DoseTypeGy aDoseReference);

      /*! @return Return true if calcIndex() finished sucessfully
          @exception NullPointerException thrown if dvhSet is NULL
		  @see calcIndex
      */
      bool init();

      /*! @brief Dose index calculation for tvIndex-th treated volume
       *  @param tvIndex: index in the vector of DVH TV
       *  @return Return index value 
          @exception InvalidParameterException Thrown if tvIndex invalid
      */
	  IndexValueType getDoseIndexAt(const GridIndexType tvIndex);



    };

  }
}

#endif