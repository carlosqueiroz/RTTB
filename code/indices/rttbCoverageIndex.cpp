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

#include "rttbCoverageIndex.h"
#include "rttbNullPointerException.h"
#include "rttbInvalidParameterException.h"
#include "rttbExceptionMacros.h"

namespace rttb{

	namespace indices{

		CoverageIndex::CoverageIndex(core::DVHSet* dvhSet, DoseTypeGy aDoseReference)
			{
			_dvhSet=dvhSet;
			_doseReference=aDoseReference;
			initSuccess=false;
			}

		bool CoverageIndex::init()
			{
			if(!_dvhSet){
				throw core::NullPointerException("DVHSet must not be NULL! ");
				}
			if( this->calcIndex()){
				initSuccess=true;
				return true;
				}
			else 
				return false;
			}

		bool CoverageIndex::calcIndex()
			{
			VolumeType TV=_dvhSet->getTVVolume(0);
			if(TV!=0)
				_value=_dvhSet->getTVVolume(this->_doseReference)/TV;
			else{
				throw core::InvalidParameterException("DVH Set invalid: Target volume should not be 0!");
				}
			return true;
			}

		IndexValueType CoverageIndex::getDoseIndexAt(GridIndexType tvIndex){
			std::vector<core::DVH> dvhTVSet=this->_dvhSet->getDVHTVSet();
			VolumeType Vref=_dvhSet->getWholeVolume(_doseReference);
			if(tvIndex>=dvhTVSet.size()){
				rttbExceptionMacro(core::InvalidParameterException, <<"tvIndex invalid: it should be <"<<dvhTVSet.size()<<"!");
				}
			core::DVH dvh=dvhTVSet.at(tvIndex);
			VolumeType TV=dvh.getVx(0);
			if(TV==0){
				throw core::InvalidParameterException("DVH invalid: Volume of tvIndex should not be 0!");
				}
			IndexValueType value=dvh.getVx(_doseReference)/TV;//the irradiation factor of i-th treated volume
			return value;
			}

		}//end namespace indices
	}//end namespace rttb