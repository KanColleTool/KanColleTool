cmake_minimum_required(VERSION 2.8)
project(KanColleTool)

# These three are managed by the version bump script!
set(VERSION_MAJOR 0)
set(VERSION_MINOR 9)
set(VERSION_PATCH 2)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

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
	
	install(DIRECTORY macviewer/build/Build/Products/Release/KCTViewer.app DESTINATION . USE_SOURCE_PERMISSIONS)
else(APPLE)
	add_subdirectory(viewer)
endif(APPLE)

add_subdirectory(tool)

#
# --> CPack stuff
#
set(CPACK_PACKAGE_NAME "KanColleTool")
set(CPACK_PACKAGE_VENDOR "The KanColleTool Team")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Makes KanColle better")
set(CPACK_PACKAGE_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "KanColleTool")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
set(CPACK_INSTALL_PREFIX "/usr")

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Johannes <uppfinnarn@gmail.com>")
set(CPACK_DEBIAN_PACKAGE_SECTION "games")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_PACKAGE_REPLACES "kancolletool-viewer")

include(CPack)
