cmake_minimum_required(VERSION 2.8)
project(KanColleTool)

include(ExternalProject)

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
