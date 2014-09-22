// -----------------------------------------------------------------------
// RTToolbox - DKFZ radiotherapy quantitative evaluation library
//
// (c) Copyright 2007, DKFZ, Heidelberg, Germany
// ALL RIGHTS RESERVED
//
// THIS FILE CONTAINS CONFIDENTIAL AND PROPRIETARY INFORMATION OF DKFZ.
// ANY DUPLICATION, MODIFICATION, DISTRIBUTION, OR
// DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY PROHIBITED
// WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF DKFZ.
//
//------------------------------------------------------------------------
/*!
// @file
// @version $Revision$ (last changed revision)
// @date $Date$ (last change date)
// @author zhangl (last changed by)
// @author *none* (Reviewer)
// @author zhangl (Programmer)
//
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/RTToolbox/branch/restructure/testing/algorithms/RTDoseIndexTest.cpp $
*/

// this file defines the rttbCoreTests for the test driver
// and all it expects is that you have a function called RegisterTests

#include "litCheckMacros.h"
#include "rttbDoseIndex.h"
#include "rttbDVHSet.h"
#include "rttbDVHTxtFileReader.h"
#include "rttbBaseType.h"
#include "rttbNullPointerException.h"
#include "rttbConformalIndex.h"
#include "rttbConformationNumber.h"
#include "rttbConformityIndex.h"
#include "rttbCoverageIndex.h"
#include "rttbHomogeneityIndex.h"
#include "rttbException.h"
#include "rttbInvalidParameterException.h"

#include <math.h>


namespace rttb{
  namespace testing{
    /*! @brief DoseIndexTest. ConformationNumber ConformalIndex ConformityIndex CoverageIndex HomogeneityIndex are tested.
    test dvh: deltaV 0.125, deltaD 0.5
    1. dvh TV: number of voxels 2900,  maximum dose bin 133, dose bin 127~133
    2. dvh HT1: number of voxels 5410, maximum dose bin 40, dose bin 0~2,40
    3. dvh HT2: number of voxels 10210, maximum dose bin 50, dose bin 0~2,50
    4. dvh HT3: number of voxels 1210, maximum dose bin 70, dose bin 0~2,70

    Test if calculation in new architecture returns similar results to the 
    original implementation.

    WARNING: The values for comparison need to be adjusted if the input files are changed!
    */
    int RTDoseIndexTest(int argc, char* argv[] )
    {
      PREPARE_DEFAULT_TEST_REPORTING;

      //ARGUMENTS: 1: ptv dvh file name
      //           2: normal tissue 1 dvh file name
      //           3: normal tissue 2 dvh file name
      //           4: normal tissue 3 dvh file name

      std::string DVH_FILENAME_PTV;
      std::string DVH_FILENAME_NT1;
      std::string DVH_FILENAME_NT2;
      std::string DVH_FILENAME_NT3;


      if (argc>1)
      {
        DVH_FILENAME_PTV = argv[1];
      }
      if (argc>2)
      {
        DVH_FILENAME_NT1 = argv[2];
      }
      if (argc>3)
      {
        DVH_FILENAME_NT2 = argv[3];
      }
      if (argc>4)
      {
        DVH_FILENAME_NT3 = argv[4];
      }


      /*test dvh: deltaV 0.125, deltaD 0.5*/
      /*dvh TV: number of voxels 2900,  maximum dose bin 133, dose bin 127~133*/
			rttb::io::other::DVHTxtFileReader dvhReader=rttb::io::other::DVHTxtFileReader(DVH_FILENAME_PTV);
      rttb::core::DVH dvhPTV=*(dvhReader.generateDVH());
      /*dvh HT1: number of voxels 5410, maximum dose bin 40, dose bin 0~2,40*/
			rttb::io::other::DVHTxtFileReader dvhReader1=rttb::io::other::DVHTxtFileReader(DVH_FILENAME_NT1);
      core::DVH dvhNT1=*(dvhReader1.generateDVH());
      /*dvh HT2: number of voxels 10210, maximum dose bin 50, dose bin 0~2,50*/
			rttb::io::other::DVHTxtFileReader dvhReader2=rttb::io::other::DVHTxtFileReader(DVH_FILENAME_NT2);
      core::DVH dvhNT2=*(dvhReader2.generateDVH());
      /*dvh HT3: number of voxels 1210, maximum dose bin 70, dose bin 0~2,70*/
			rttb::io::other::DVHTxtFileReader dvhReader3=rttb::io::other::DVHTxtFileReader(DVH_FILENAME_NT3);
      core::DVH dvhNT3=*(dvhReader3.generateDVH());

      std::vector<core::DVH> dvhTVSet;
      std::vector<core::DVH> dvhHTSet;
      dvhTVSet.push_back(dvhPTV);
      dvhHTSet.push_back(dvhNT1);
      dvhHTSet.push_back(dvhNT2);
      dvhHTSet.push_back(dvhNT3);

      core::DVHSet dvhSet=core::DVHSet(dvhTVSet,dvhHTSet,"testStrSet",dvhPTV.getDoseID());

      /*test exception*/
      indices::ConformalIndex test1=indices::ConformalIndex(NULL,0);
      indices::ConformationNumber test2=indices::ConformationNumber(NULL,0);
      indices::ConformityIndex test3=indices::ConformityIndex(NULL,0);
      indices::CoverageIndex test4=indices::CoverageIndex(NULL,0);
      indices::HomogeneityIndex test5=indices::HomogeneityIndex(NULL,0);

      CHECK_THROW_EXPLICIT(test1.init(),core::NullPointerException);
      CHECK_THROW_EXPLICIT(test2.init(),core::NullPointerException);
      CHECK_THROW_EXPLICIT(test3.init(),core::NullPointerException);
      CHECK_THROW_EXPLICIT(test4.init(),core::NullPointerException);
      CHECK_THROW_EXPLICIT(test5.init(),core::NullPointerException);


      /*test exception for invalid reference dose*/
      test1=indices::ConformalIndex(&dvhSet,100);
      test2=indices::ConformationNumber(&dvhSet,100);
      test3=indices::ConformityIndex(&dvhSet,100);
      test5=indices::HomogeneityIndex(&dvhSet,0);

      CHECK_THROW_EXPLICIT(test1.init(),core::InvalidParameterException);
      CHECK_THROW_EXPLICIT(test2.init(),core::InvalidParameterException);
      CHECK_THROW_EXPLICIT(test3.init(),core::InvalidParameterException);
      CHECK_THROW_EXPLICIT(test5.init(),core::InvalidParameterException);

      /*test index calculation*/

      /*RTConformationNumber */
      //PTV covered by reference dose 30 = the whole PTV =362.5; Volume of the referece 30=362.5+1.25
      indices::ConformationNumber cn=indices::ConformationNumber(&dvhSet, 30);
      cn.init();
      //check if values are close. Equality is only achieved with double precission.
      CHECK_CLOSE(362.5/363.75,cn.getValue(),errorConstant);

      //cn==1*TV0/V0=362.5/2466.25
      cn.setDoseReference(0);
      //if not init, throw Exception
      CHECK_THROW_EXPLICIT(cn.getValue(),core::Exception);
      cn.init();
      CHECK_CLOSE(362.5/2466.25,cn.getValue(),errorConstant);

      cn.setDoseReference(65);
      //if not init, throw Exception
      CHECK_THROW_EXPLICIT(cn.getValue(),core::Exception);
      cn.init();
      CHECK_CLOSE(2300/2900.0,cn.getValue(),errorConstant);//ref dose: 65 -> TVref=Vref -> cn=TVref/TV=2300/2900

      CHECK_EQUAL(cn.getValue(),cn.getDoseIndexAt(0));
      CHECK_THROW_EXPLICIT(cn.getDoseIndexAt(1),core::InvalidParameterException);

      /*ConformalIndex */
      //HT 1 covered by ref=HT2 covered by ref=0, HT3 covered by ref=1.25 
      indices::ConformalIndex coin=indices::ConformalIndex(&dvhSet, 30);
      coin.init();
      CHECK_CLOSE((362.5/363.75)*(1-1.25/151.25),coin.getValue(),errorConstant);

      coin.setDoseReference(0);
      //if not init, throw Exception
      CHECK_THROW_EXPLICIT(coin.getValue(),core::Exception);
      coin.init();
      CHECK_EQUAL(0,coin.getValue());

      coin.setDoseReference(65);
      //if not init, throw Exception
      CHECK_THROW_EXPLICIT(coin.getValue(),core::Exception);
      coin.init();
      CHECK_CLOSE(2300/2900.0,coin.getValue(),errorConstant);//ref dose: 65 -> Vref=0 for all HT -> cn=cn*(1-0)=cn

      CHECK_EQUAL(coin.getValue(),coin.getDoseIndexAt(0));
      CHECK_THROW_EXPLICIT(coin.getDoseIndexAt(1),core::InvalidParameterException);

      /*ConformityIndex */
      indices::ConformityIndex ci=indices::ConformityIndex(&dvhSet, 30);
      //if not init, throw Exception
      CHECK_THROW_EXPLICIT(ci.getValue(),core::Exception);
      ci.init();
      CHECK_CLOSE(362.5/363.75,ci.getValue(),errorConstant);

      ci.setDoseReference(65);
      //if not init, throw Exception
      CHECK_THROW_EXPLICIT(ci.getValue(),core::Exception);
      ci.init();
      CHECK_CLOSE(2300/2900.0,ci.getValue(),errorConstant);//ref dose: 65->ci=2300/2900*1*1*1

      CHECK_EQUAL(ci.getValue(),ci.getDoseIndexAt(0));
      CHECK_THROW_EXPLICIT(ci.getDoseIndexAt(1),core::InvalidParameterException);

      /*CoverageIndex*/
      indices::CoverageIndex coverageI=indices::CoverageIndex(&dvhSet, 30);
      //if not init, throw Exception
      CHECK_THROW_EXPLICIT(coverageI.getValue(),core::Exception);
      coverageI.init();
      CHECK_CLOSE(362.5/362.5,coverageI.getValue(),errorConstant);//ref dose: 30 -> coverage index=1

      coverageI.setDoseReference(65);
      //if not init, throw Exception
      CHECK_THROW_EXPLICIT(coverageI.getValue(),core::Exception);
      coverageI.init();
      CHECK_CLOSE(2300/2900.0,coverageI.getValue(),errorConstant);//ref dose: 65->coverage index=2300/2900

      CHECK_EQUAL(coverageI.getValue(),coverageI.getDoseIndexAt(0));
      CHECK_THROW_EXPLICIT(coverageI.getDoseIndexAt(1),core::InvalidParameterException);


      /*HomogeneityIndex TV max: 133*0.5=66.5, TV min: 127*0.5=63.5 -> hi=(66.5-63.5)/30*/
      indices::HomogeneityIndex hi=indices::HomogeneityIndex(&dvhSet, 30);
      //if not init, throw Exception
      CHECK_THROW_EXPLICIT(hi.getValue(),core::Exception);
      hi.init();
      CHECK_CLOSE(3/30.0,hi.getValue(),errorConstant);

      hi.setDoseReference(65);
      //if not init, throw Exception
      CHECK_THROW_EXPLICIT(hi.getValue(),core::Exception);
      hi.init();
      CHECK_CLOSE(3/65.0,hi.getValue(),errorConstant);			

      CHECK_EQUAL(hi.getValue(),hi.getDoseIndexAt(0));
      CHECK_THROW_EXPLICIT(hi.getDoseIndexAt(1),core::InvalidParameterException);


      RETURN_AND_REPORT_TEST_SUCCESS;


    }

  }//testing
}//rttb