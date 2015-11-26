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

#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

#include "litCheckMacros.h"

#include "rttbBaseType.h"
#include "rttbGenericDoseIterator.h"
#include "rttbDoseIteratorInterface.h"
#include "rttbNullPointerException.h"
#include "rttbDoseStatisticsCalculator.h"
#include "rttbInvalidDoseException.h"
#include "rttbInvalidParameterException.h"
#include "rttbDataNotAvailableException.h"

#include "../core/DummyDoseAccessor.h"

namespace rttb
{
	namespace testing
	{

		typedef core::GenericDoseIterator::DoseAccessorPointer DoseAccessorPointer;
		typedef core::DoseIteratorInterface::DoseIteratorPointer DoseIteratorPointer;
		typedef rttb::algorithms::DoseStatistics::ResultListPointer ResultListPointer;
		typedef rttb::algorithms::DoseStatistics::DoseStatisticsPointer DoseStatisticsPointer;

		/*! @brief DoseStatisticsCalculatorTest - test the API of DoseStatisticsCalculator
			1) test constructors
			2) test setDoseIterator
			3) test calculateDoseSatistics
			4) get statistical values
		*/

		int DoseStatisticsCalculatorTest(int argc, char* argv[])
		{
			PREPARE_DEFAULT_TEST_REPORTING;

			boost::shared_ptr<DummyDoseAccessor> spTestDoseAccessor = boost::make_shared<DummyDoseAccessor>();
			DoseAccessorPointer spDoseAccessor(spTestDoseAccessor);
			const std::vector<DoseTypeGy>* doseVals = spTestDoseAccessor->getDoseVector();

			boost::shared_ptr<core::GenericDoseIterator> spTestDoseIterator =
			    boost::make_shared<core::GenericDoseIterator>(spDoseAccessor);
			DoseIteratorPointer spDoseIterator(spTestDoseIterator);

			DoseIteratorPointer spDoseIteratorNull;

			//1) test constructors
			// the values cannot be accessed from outside, therefore correct default values are not tested

			CHECK_THROW_EXPLICIT(rttb::algorithms::DoseStatisticsCalculator myDoseStatsCalculator(spDoseIteratorNull),
			                     core::NullPointerException);

			CHECK_NO_THROW(rttb::algorithms::DoseStatisticsCalculator myDoseStatsCalculator(spDoseIterator));
			rttb::algorithms::DoseStatisticsCalculator myDoseStatsCalculator(spDoseIterator);

			//2) test setDoseIterator

			//3) test calculateDoseStatistics
			DoseStatisticsPointer theStatistics;
			//simple dose statistics
			CHECK_NO_THROW(theStatistics = myDoseStatsCalculator.calculateDoseStatistics());
			CHECK_EQUAL(theStatistics->getMinimumPositions()->empty(), false);
			CHECK_EQUAL(theStatistics->getMaximumPositions()->empty(), false);
			CHECK_EQUAL(theStatistics->getAllVx().empty(), true);
			CHECK_EQUAL(theStatistics->getAllDx().empty(), true);
			CHECK_EQUAL(theStatistics->getAllVx().empty(), true);
			CHECK_EQUAL(theStatistics->getAllMaxOHx().empty(), true);
			CHECK_EQUAL(theStatistics->getAllMOHx().empty(), true);
			CHECK_EQUAL(theStatistics->getAllMOCx().empty(), true);
			CHECK_EQUAL(theStatistics->getAllMinOCx().empty(), true);

			//check default values for computeComplexMeasures=true
			DoseStatisticsPointer theStatisticsDefault;
			CHECK_NO_THROW(theStatisticsDefault = myDoseStatsCalculator.calculateDoseStatistics(true));
			CHECK_NO_THROW(theStatisticsDefault->getVx(0.02 * theStatisticsDefault->getMaximum()));
			CHECK_NO_THROW(theStatisticsDefault->getVx(0.05 * theStatisticsDefault->getMaximum()));
			CHECK_NO_THROW(theStatisticsDefault->getVx(0.1 * theStatisticsDefault->getMaximum()));
			CHECK_NO_THROW(theStatisticsDefault->getVx(0.9 * theStatisticsDefault->getMaximum()));
			CHECK_NO_THROW(theStatisticsDefault->getVx(0.95 * theStatisticsDefault->getMaximum()));
			CHECK_NO_THROW(theStatisticsDefault->getVx(0.98 * theStatisticsDefault->getMaximum()));
			CHECK_NO_THROW(theStatisticsDefault->getDx(0.02 * theStatisticsDefault->getVolume()));
			CHECK_NO_THROW(theStatisticsDefault->getDx(0.05 * theStatisticsDefault->getVolume()));
			CHECK_NO_THROW(theStatisticsDefault->getDx(0.1 * theStatisticsDefault->getVolume()));
			CHECK_NO_THROW(theStatisticsDefault->getDx(0.9 * theStatisticsDefault->getVolume()));
			CHECK_NO_THROW(theStatisticsDefault->getDx(0.95 * theStatisticsDefault->getVolume()));
			CHECK_NO_THROW(theStatisticsDefault->getDx(0.98 * theStatisticsDefault->getVolume()));

			//check manually set reference dose and the default x values
			CHECK_NO_THROW(theStatistics = myDoseStatsCalculator.calculateDoseStatistics(100.0));
			CHECK_THROW_EXPLICIT(theStatistics->getVx(0.1 * theStatistics->getMaximum()), core::DataNotAvailableException);
			CHECK_NO_THROW(theStatistics->getVx(0.1 * 100.0));
			CHECK_NO_THROW(theStatistics->getDx(0.1 * theStatistics->getVolume()));
			CHECK_NO_THROW(theStatistics->getDx(0.9 * theStatistics->getVolume()));
			CHECK_NO_THROW(theStatistics->getMOHx(0.95 * theStatistics->getVolume()));
			CHECK_NO_THROW(theStatistics->getMOCx(0.98 * theStatistics->getVolume()));
			CHECK_EQUAL(theStatistics->getReferenceDose(), 100.0);

			//check manually set x values
			std::vector<double> precomputeDoseValues, precomputeVolumeValues;
			precomputeDoseValues.push_back(0.01);
			precomputeDoseValues.push_back(0.02);
			precomputeDoseValues.push_back(0.05);

			precomputeVolumeValues.push_back(0.9);
			precomputeVolumeValues.push_back(0.95);
			precomputeVolumeValues.push_back(0.99);

			CHECK_NO_THROW(theStatistics = myDoseStatsCalculator.calculateDoseStatistics(precomputeDoseValues,
			                               precomputeVolumeValues));
			CHECK_NO_THROW(theStatistics->getVx(0.01 * theStatistics->getMaximum()));
			CHECK_NO_THROW(theStatistics->getVx(0.02 * theStatistics->getMaximum()));
			CHECK_NO_THROW(theStatistics->getVx(0.05 * theStatistics->getMaximum()));
			CHECK_THROW_EXPLICIT(theStatistics->getVx(0.03 * theStatistics->getMaximum()), core::DataNotAvailableException);
			CHECK_NO_THROW(theStatistics->getDx(0.9 * theStatistics->getVolume()));
			CHECK_NO_THROW(theStatistics->getDx(0.95 * theStatistics->getVolume()));
			CHECK_NO_THROW(theStatistics->getDx(0.99 * theStatistics->getVolume()));
			CHECK_THROW_EXPLICIT(theStatistics->getDx(0.03 * theStatistics->getVolume()), core::DataNotAvailableException);
			CHECK_EQUAL(theStatistics->getVx(0.02 * theStatistics->getMaximum()),
				theStatisticsDefault->getVx(0.02 * theStatistics->getMaximum()));
			CHECK_EQUAL(theStatistics->getVx(0.05 * theStatistics->getMaximum()),
				theStatisticsDefault->getVx(0.05 * theStatistics->getMaximum()));
			CHECK_EQUAL(theStatistics->getDx(0.9 * theStatistics->getVolume()),
				theStatisticsDefault->getDx(0.9 * theStatistics->getVolume()));
			CHECK_EQUAL(theStatistics->getDx(0.95 * theStatistics->getVolume()),
				theStatisticsDefault->getDx(0.95 * theStatistics->getVolume()));

			//check manually set reference dose and x values
			CHECK_NO_THROW(theStatistics = myDoseStatsCalculator.calculateDoseStatistics(precomputeDoseValues,
				precomputeVolumeValues, 100.0));
			CHECK_THROW_EXPLICIT(theStatistics->getVx(0.01 * theStatistics->getMaximum()), core::DataNotAvailableException);
			CHECK_NO_THROW(theStatistics->getVx(0.01 * 100.0));
			CHECK_NO_THROW(theStatistics->getDx(0.9 * theStatistics->getVolume()));
			CHECK_EQUAL(theStatistics->getReferenceDose(), 100.0);

			//MOHx, MOCx, MaxOHx and MinOCx are computed analogous to Dx, they will not be checked.

			//4) get statistical values
			CHECK_EQUAL(theStatistics->getNumberOfVoxels(), doseVals->size());

			//compute simple statistical values (min, mean, max, stddev) for comparison
			DoseStatisticType maximum = 0;
			DoseStatisticType minimum = 1000000;
			DoseStatisticType mean = 0;
			DoseStatisticType variance = 0;
			std::vector<DoseTypeGy>::const_iterator doseIt = doseVals->begin();

			while (doseIt != doseVals->end())
			{
				if (maximum < *doseIt)
				{
					maximum = *doseIt;
				}

				if (minimum > *doseIt)
				{
					minimum = *doseIt;
				}

				mean += *doseIt;
				++doseIt;
			}

			mean /= doseVals->size();
			DoseTypeGy compMean = (int(mean * 100)) / 100;

			doseIt = doseVals->begin();

			while (doseIt != doseVals->end())
			{
				variance += pow(*doseIt - mean, 2);
				++doseIt;
			}

			variance /= doseVals->size();
			DoseStatisticType stdDev = pow(variance, 0.5);

			//we have some precision problems here...
			double errorConstantLarger = 1e-2;

			CHECK_EQUAL(theStatistics->getMaximum(), maximum);
			CHECK_EQUAL(theStatistics->getMinimum(), minimum);
			CHECK_CLOSE(theStatistics->getMean(), mean, errorConstantLarger);
			CHECK_CLOSE(theStatistics->getStdDeviation(), stdDev, errorConstantLarger);
			CHECK_CLOSE(theStatistics->getVariance(), variance, errorConstantLarger);

			//check for complex doseStatistics (maximumPositions, minimumPositions, Vx, Dx, MOHx, MOCx, MAXOHx, MinOCx)

			unsigned int nMax = 0, nMin = 0;

			doseIt = doseVals->begin();

			while (doseIt != doseVals->end())
			{
				if (*doseIt == theStatistics->getMaximum())
				{
					nMax++;
				}

				if (*doseIt == theStatistics->getMinimum())
				{
					nMin++;
				}

				++doseIt;
			}

			//only 100 positions are stored
			if (nMax > 100)
			{
				nMax = 100;
			}

			if (nMin > 100)
			{
				nMin = 100;
			}

			auto maximaPositions = theStatistics->getMaximumPositions();
			auto minimaPositions = theStatistics->getMinimumPositions();

			CHECK_EQUAL(maximaPositions->size(), nMax);
			CHECK_EQUAL(minimaPositions->size(), nMin);

			for (auto maximaPositionsIterator = std::begin(*maximaPositions); maximaPositionsIterator != std::end(*maximaPositions);
			     ++maximaPositionsIterator)
			{
				CHECK_EQUAL(maximaPositionsIterator->first, theStatistics->getMaximum());
			}

			for (auto minimaPositionsIterator = std::begin(*minimaPositions); minimaPositionsIterator != std::end(*minimaPositions);
			     ++minimaPositionsIterator)
			{
				CHECK_EQUAL(minimaPositionsIterator->first, theStatistics->getMinimum());
			}


			//generate specific example dose
			maximum = 9.5;
			minimum = 2.5;
			mean = 6;
			int sizeTemplate = 500;
			std::vector<DoseTypeGy> aDoseVector;

			for (int i = 0; i < sizeTemplate; i++)
			{
				aDoseVector.push_back(maximum);
				aDoseVector.push_back(minimum);
			}

			core::GeometricInfo geoInfo = spTestDoseAccessor->getGeometricInfo();
			geoInfo.setNumRows(20);
			geoInfo.setNumColumns(10);
			geoInfo.setNumSlices(5);

			boost::shared_ptr<DummyDoseAccessor> spTestDoseAccessor2 =
			    boost::make_shared<DummyDoseAccessor>(aDoseVector, geoInfo);
			DoseAccessorPointer spDoseAccessor2(spTestDoseAccessor2);

			boost::shared_ptr<core::GenericDoseIterator> spTestDoseIterator2 =
			    boost::make_shared<core::GenericDoseIterator>(spDoseAccessor2);
			DoseIteratorPointer spDoseIterator2(spTestDoseIterator2);

			rttb::algorithms::DoseStatisticsCalculator myDoseStatsCalculator2(spDoseIterator2);
			DoseStatisticsPointer theStatistics3 = myDoseStatsCalculator2.calculateDoseStatistics();

			CHECK_EQUAL(theStatistics3->getMaximum(), maximum);
			CHECK_EQUAL(theStatistics3->getMinimum(), minimum);
			CHECK_EQUAL(theStatistics3->getMean(), mean);


			maximaPositions = theStatistics3->getMaximumPositions();
			minimaPositions = theStatistics3->getMinimumPositions();

			CHECK_EQUAL(maximaPositions->empty(), false);
			CHECK_EQUAL(minimaPositions->empty(), false);

			for (auto maximaPositionsIterator = std::begin(*maximaPositions); maximaPositionsIterator != std::end(*maximaPositions);
			     ++maximaPositionsIterator)
			{
				CHECK_EQUAL(maximaPositionsIterator->first, theStatistics3->getMaximum());
			}

			for (auto minimaPositionsIterator = std::begin(*minimaPositions); minimaPositionsIterator != std::end(*minimaPositions);
			     ++minimaPositionsIterator)
			{
				CHECK_EQUAL(minimaPositionsIterator->first, theStatistics3->getMinimum());
			}

			RETURN_AND_REPORT_TEST_SUCCESS;
		}

	}//end namespace testing
}//end namespace rttb