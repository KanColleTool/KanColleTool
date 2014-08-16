cmake_minimum_required(VERSION 2.8)
project(KanColleTool)

# These three are managed by the version bump script!
set(VERSION_MAJOR 0)
set(VERSION_MINOR 9)
set(VERSION_PATCH 3)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(ExternalProject)

# On Windows, we need to manually find Qt installations >_>
if(WIN32)
	file(GLOB QtVerDirs "C:/Qt/5.*")
	foreach(dir ${QtVerDirs})
		if(MSVC)
			file(GLOB QtDirs "${dir}/msvc*")
			list(GET QtDirs 0 QtDir)
		else()
			file(GLOB QtDirs "${dir}/mingw*")
			list(GET QtDirs 0 QtDir)
		endif()
		set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${QtDir}")
		set(ENV{PATH} "$ENV{PATH};${QtDir}")
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
else()
	add_subdirectory(viewer)
endif()

add_subdirectory(tool)

if(WIN32)
	foreach(target "viewer" "tool")
		set(base ${PROJECT_SOURCE_DIR}/${target}/bin/Release)
		
		file(GLOB DLLS ${base}/*.dll)
		install(FILES ${DLLS} DESTINATION .)
		
		file(GLOB children RELATIVE ${base} ${base}/*)
		foreach(child ${children})
			if(IS_DIRECTORY ${base}/${child})
				file(GLOB DLLS2 ${base}/${child}/*.dll)
				install(FILES ${DLLS2} DESTINATION ${child})
			endif()
		endforeach()
	endforeach()
endif()

#
# --> CPack stuff
#
# General
set(CPACK_PACKAGE_NAME "KanColleTool")
set(CPACK_PACKAGE_VENDOR "The KanColleTool Team")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Makes KanColle better")
set(CPACK_PACKAGE_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")

set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
set(CPACK_PACKAGE_EXECUTABLES "KanColleTool;KanColleTool" "KCTViewer;KanColleTool Viewer")

set(CPACK_RESOURCE_FILE_README "${PROJECT_SOURCE_DIR}/README.txt")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE.txt")

# --> Windows specific
set(CPACK_PACKAGE_INSTALL_DIRECTORY "KanColleTool")

# --> Linux specific
set(CPACK_INSTALL_PREFIX "/usr")

# --> Debian specific
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Johannes Ekberg <uppfinnarn@gmail.com>")
set(CPACK_DEBIAN_PACKAGE_SECTION "games")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_PACKAGE_REPLACES "kancolletool-viewer")

# --> NSIS specific
set(CPACK_NSIS_EXECUTABLES_DIRECTORY ".")
set(CPACK_NSIS_INSTALLED_ICON_NAME "KanColleTool.exe")
set(CPACK_NSIS_HELP_LINK "http://kancolletool.github.io/")
set(CPACK_NSIS_URL_INFO_ABOUT "http://kancolletool.github.io/")
set(CPACK_NSIS_CONTACT "kctool@macaronicode.se")

include(CPack)
