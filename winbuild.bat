for /d %%f in (C:\Qt\5.*) do (set QTDIR=%%f\msvc2013)
set PATH=%PATH%;%QTDIR%\bin

:build
:: Delete old dist dir; the last thing we need is partial builds
rmdir /s /q dist
mkdir dist
mkdir dist\KanColleTool

:: Build everything
cmake -G "Visual Studio 12 2013" .
"C:\Program Files (x86)\MSBuild\12.0\Bin\MSBuild.exe" KanColleTool.sln /property:Configuration=Release
xcopy tool\bin\Release\KanColleTool.exe dist\KanColleTool
xcopy viewer\bin\Release\KCTViewer.exe dist\KanColleTool

:: Build the tool
:: -- Disabled for now
:: cd tool
:: lrelease src\src.pro
:: xcopy translations\*.qm ..\dist\KanColleTool

:package
:: Copy MinGW32 DLLs that Qt doesn't catch automatically
:: xcopy %QTDIR%\mingw48_32\bin\libgcc_s_dw2-1.dll dist\KanColleTool
:: xcopy %QTDIR%\mingw48_32\bin\libstdc++-6.dll dist\KanColleTool
:: xcopy %QTDIR%\mingw48_32\bin\libwinpthread-1.dll dist\KanColleTool

:: Let Qt collect DLLs
windeployqt.exe dist\KanColleTool\KCTViewer.exe
windeployqt.exe dist\KanColleTool\KanColleTool.exe

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

pause
