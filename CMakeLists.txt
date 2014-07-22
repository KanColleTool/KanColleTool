cmake_minimum_required(VERSION 2.8)
project(KanColleTool)

include(ExternalProject)

# On Windows, we need to manually find Qt installations >_>
if(WIN32)
	file(GLOB QtVerDirs "C:/Qt/5.*")
	foreach(dir ${QtVerDirs})
		file(GLOB msvc_dirs "${dir}/msvc*")
		file(GLOB mingw_dirs "${dir}/mingw*")
		set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${msvc_dirs};${mingw_dirs}")
	endforeach(dir)
endif(WIN32)

if(APPLE)
	ExternalProject_Add(macviewer
		SOURCE_DIR macviewer
		BINARY_DIR macviewer
		CONFIGURE_COMMAND pod install
		BUILD_COMMAND xcodebuild -workspace KCTViewer.xcworkspace -scheme KCTViewer -configuration Release -derivedDataPath ./build
		INSTALL_COMMAND ""
	)
else(APPLE)
	add_subdirectory(viewer)
endif(APPLE)

add_subdirectory(tool)
