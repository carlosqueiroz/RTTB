MESSAGE (STATUS "generating app: VoxelizerTool - voxelize DICOM RTSTRUCT files")
SET(RTTB_Boost_ADDITIONAL_COMPONENT program_options)
RTTB_CREATE_APPLICATION(VoxelizerTool DEPENDS RTTBBoostMask RTTBCore RTTBUtilsIO PACKAGE_DEPENDS ArgumentParsingLib ITK BoostBinaries)

