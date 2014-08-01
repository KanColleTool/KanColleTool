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
	#add_custom_target(ToolDependencies ALL
	#	windeployqt --no-compiler-runtime --no-translations --no-svg $<TARGET_FILE:KanColleTool>
	#	DEPENDS KanColleTool
	#)
	#add_custom_target(ViewerDependencies ALL
	#	windeployqt --no-compiler-runtime --no-translations --no-svg $<TARGET_FILE:KCTViewer>
	#	DEPENDS KCTViewer
	#)
	
	#install(CODE "
	#	execute_process(
	#		COMMAND windeployqt --no-compiler-runtime --no-translations --no-svg tool/bin/Release/KanColleTool.exe
	#		COMMAND windeployqt --no-compiler-runtime --no-translations --no-svg viewer/bin/Release/KCTViewer.exe
	#	)
	#")
	
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

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Johannes Ekberg <uppfinnarn@gmail.com>")
set(CPACK_DEBIAN_PACKAGE_SECTION "games")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_PACKAGE_REPLACES "kancolletool-viewer")

include(CPack)
