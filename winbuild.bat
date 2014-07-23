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
windeployqt --no-compiler-runtime --no-translations --no-svg dist\KanColleTool\KCTViewer.exe
windeployqt --no-compiler-runtime --no-translations --no-svg dist\KanColleTool\KanColleTool.exe

:: Delete all database drivers but sqlite
del /q dist\KanColleTool\sqldrivers\qsqlmysql*
del /q dist\KanColleTool\sqldrivers\qsqlodbc*
del /q dist\KanColleTool\sqldrivers\qsqlpsql*

:: Copy the README file
xcopy targets\windows\README.txt dist\KanColleTool

:: pause
