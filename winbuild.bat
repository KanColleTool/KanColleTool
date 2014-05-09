for /d %%f in (C:\Qt\*) do (set QTDIR=%%f)
for /d %%f in (%QTDIR%) do (set QTDIR2=%%f)
IF NOT DEFINED QTDIR2 set QTDIR2=%QTDIR%
for /d %%f in (%QTDIR2%\5.*) do (set QTBIN=%%f\mingw48_32\bin)

set PATH=%PATH%;%QTBIN%
set PATH=%PATH%;%QTDIR%\Tools\mingw48_32\bin
set PATH=%PATH%;C:\Qt\Tools\mingw48_32\bin

:build
:: Delete old dist dir; the last thing we need is partial builds
rmdir /s /q dist
mkdir dist
mkdir dist\KanColleTool

:: Build the tool
cd tool
lrelease src\src.pro
xcopy translations\*.qm ..\dist\KanColleTool
qmake
mingw32-make release
xcopy bin\KanColleTool.exe ..\dist\KanColleTool
mingw32-make clean
rmdir /s /q debug
rmdir /s /q release
cd ..

:: Build the viewer
cd viewer
qmake
mingw32-make release
xcopy bin\KCTViewer.exe ..\dist\KanColleTool
mingw32-make clean
rmdir /s /q debug
rmdir /s /q release
cd ..

:package
:: Copy MinGW32 DLLs that Qt doesn't catch automatically
xcopy %QTDIR%\mingw48_32\bin\libgcc_s_dw2-1.dll dist\KanColleTool
xcopy %QTDIR%\mingw48_32\bin\libstdc++-6.dll dist\KanColleTool
xcopy %QTDIR%\mingw48_32\bin\libwinpthread-1.dll dist\KanColleTool

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
rmdir /s /q dist\KanColleTool\qmltooling

:: Delete debug versions of frameworks
del /q dist\KanColleTool\bearer\*d.dll
del /q dist\KanColleTool\platforms\*d.dll
del /q dist\KanColleTool\sqldrivers\*d.dll

:: Delete all database drivers but sqlite
del /q dist\KanColleTool\sqldrivers\qsqlmysql*
del /q dist\KanColleTool\sqldrivers\qsqlodbc*
del /q dist\KanColleTool\sqldrivers\qsqlpsql*

::pause
