IF(NOT BoostBinaries_FOUND)

  IF(DEFINED Boost_INCLUDE_DIR)
    IF(NOT IS_ABSOLUTE ${Boost_INCLUDE_DIR})
      SET(Boost_INCLUDE_DIR "${RTToolbox_BINARY_DIR}/${Boost_INCLUDE_DIR}")
    ENDIF(NOT IS_ABSOLUTE ${Boost_INCLUDE_DIR})
  ENDIF(DEFINED Boost_INCLUDE_DIR)

  IF(NOT DEFINED RTTB_USE_MITK_BOOST)
    OPTION(RTTB_USE_MITK_BOOST "RTTB should use a boost which is available in the MITK superbuild external projects structure." OFF)
    MARK_AS_ADVANCED(RTTB_USE_MITK_BOOST)
  ENDIF(NOT DEFINED RTTB_USE_MITK_BOOST)
  
  IF(BUILD_SHARED_LIBS OR RTTB_USE_MITK_BOOST)
    SET(Boost_USE_STATIC_LIBS OFF)
	ADD_DEFINITIONS(-DBOOST_ALL_DYN_LINK)
  ELSE(BUILD_SHARED_LIBS OR RTTB_USE_MITK_BOOST)
    SET(Boost_USE_STATIC_LIBS ON)
  ENDIF(BUILD_SHARED_LIBS OR RTTB_USE_MITK_BOOST)

  SET(BOOST_MIN_VERSION "1.56.0")
  FIND_PACKAGE(Boost ${BOOST_MIN_VERSION} REQUIRED COMPONENTS filesystem regex system thread ${RTTB_Boost_ADDITIONAL_COMPONENT} QUIET)
  LIST(APPEND ALL_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS})
  LIST(APPEND ALL_LIBRARIES ${Boost_LIBRARIES})
  link_directories(${Boost_LIBRARY_DIRS})
	
  MARK_AS_ADVANCED(CLEAR Boost_INCLUDE_DIR)

  SET(BoostBinaries_FOUND TRUE)

ENDIF(NOT BoostBinaries_FOUND)



