cmake_minimum_required(VERSION 3.0...3.10)
project(AtlasTranslate)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(WIN32)
	add_definitions(-static -static-libgcc -static-libstdc++)
endif()

add_definitions(-DNO_ZLIB -DUNICODE -D_UNICODE)

set(CMAKE_SHARED_MODULE_PREFIX "")

include_directories(
	src
	src/Shared
)

add_library(AtlasTranslate MODULE
	src/atlastranslate.cpp
	src/extensionimpl.cpp
	src/Shared/Atlas.cpp
	src/Shared/ConversionTable.cpp
	src/Shared/ProcessUtil.cpp
	src/Shared/Shrink.cpp
	src/Shared/StringUtil.cpp
	src/Shared/TextRuleSet.cpp
	src/Shared/EUCJPtoUTF16.cpp
)

set_property(TARGET AtlasTranslate PROPERTY CXX_STANDARD 17)
