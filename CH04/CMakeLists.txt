cmake_minimum_required(VERSION 3.25)

add_subdirectory(utils)
add_subdirectory(BGRsplit)
add_subdirectory(Gray)
add_subdirectory(CIExyz)
add_subdirectory(YCrCbcolor)
add_subdirectory(HSVcolor)
add_subdirectory(HLScolor)
add_subdirectory(CIElab)
add_subdirectory(CIELuvcolor)

# NOTE: There aren't sample images for the sample!
add_subdirectory(Bayer)

add_subdirectory(HSVsegment)
add_subdirectory(YCrCbsegment)

# NOTE: The images for the sample are low-resolution.
add_subdirectory(colorTransfer)

