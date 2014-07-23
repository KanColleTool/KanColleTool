:: Find the latest Qt for Visual Studio 2013 installation
for /d %%f in (C:\Qt\5.*) do (set QTDIR=%%f\msvc2013)

:: Set up PATH
set PATH=%PATH%;"%QTDIR%\bin"
set PATH=%PATH%;"%PROGRAMFILES(x86)%\CMake\bin"
set PATH=%PATH%;"%PROGRAMFILES(x86)%\MSBuild\12.0\Bin"



:prepare
:: Delete old dist dir; the last thing we need is partial builds
rmdir /s /q dist
mkdir dist
mkdir dist\KanColleTool



:build
:: Build everything
cmake -G "Visual Studio 12 2013" .
MSBuild KanColleTool.sln /property:Configuration=Release
xcopy tool\bin\Release\KanColleTool.exe dist\KanColleTool
xcopy viewer\bin\Release\KCTViewer.exe dist\KanColleTool

:package
:: Copy Visual Studio redistributables, and always the 32bit one
if exist C:\Windows\SysWOW64 (
	xcopy /q /y C:\Windows\SysWOW64\msvcp120.dll dist\KanColleTool
	xcopy /q /y C:\Windows\SysWOW64\msvcr120.dll dist\KanColleTool
) else (
	xcopy /q /y C:\Windows\System32\msvcp120.dll dist\KanColleTool
	xcopy /q /y C:\Windows\System32\msvcr120.dll dist\KanColleTool
)

:: Let Qt collect DLLs
windeployqt dist\KanColleTool\KCTViewer.exe
windeployqt dist\KanColleTool\KanColleTool.exe

:: Delete things we don't need at all
rmdir /s /q dist\KanColleTool\accessible
rmdir /s /q dist\KanColleTool\iconengines
rmdir /s /q dist\KanColleTool\imageformats
rmdir /s /q dist\KanColleTool\mediaservice
rmdir /s /q dist\KanColleTool\playlistformats
rmdir /s /q dist\KanColleTool\printsupport
rmdir /s /q dist\KanColleTool\position
rmdir /s /q dist\KanColleTool\qmltooling
rmdir /s /q dist\KanColleTool\sensorgestures
rmdir /s /q dist\KanColleTool\sensors

:: Delete debug versions of frameworks
del /q dist\KanColleTool\bearer\*d.dll
del /q dist\KanColleTool\platforms\*d.dll
del /q dist\KanColleTool\sqldrivers\*d.dll

:: Delete all database drivers but sqlite
del /q dist\KanColleTool\sqldrivers\qsqlmysql*
del /q dist\KanColleTool\sqldrivers\qsqlodbc*
del /q dist\KanColleTool\sqldrivers\qsqlpsql*

:: pause
