#-----------------------------------------------------------------------------
# Setup the system information test.  Write out some basic failsafe
# information in case the test doesn't run.
#-----------------------------------------------------------------------------


SET(ALGORITHMS_TESTS ${EXECUTABLE_OUTPUT_PATH}/rttbAlgorithmsTests)
SET(ALGORITHMS_HEADER_TEST ${EXECUTABLE_OUTPUT_PATH}/rttbAlgorithmsHeaderTest)

SET(TEST_DATA_ROOT ${RTTBTesting_SOURCE_DIR}/data)

SET(TEMP ${RTTBTesting_BINARY_DIR}/temporary)


#-----------------------------------------------------------------------------
ADD_TEST(DoseStatisticsTest ${ALGORITHMS_TESTS} DoseStatisticsTest)
ADD_TEST(ArithmeticTest ${ALGORITHMS_TESTS} ArithmeticTest)
ADD_TEST(BinaryFunctorDoseAccessorTest ${ALGORITHMS_TESTS} BinaryFunctorDoseAccessorTest "${TEST_DATA_ROOT}/DICOM/TestDose/ConstantTwo.dcm" "${TEST_DATA_ROOT}/DICOM/TestDose/dicompylerTestDose.dcm")

RTTB_CREATE_TEST_MODULE(rttbAlgorithms DEPENDS RTTBAlgorithms RTTBMasks RTTBDicomIO PACKAGE_DEPENDS Boost Litmus DCMTK)
