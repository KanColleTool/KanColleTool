set PATH=%PATH%;C:\Qt\5.2.0\mingw48_32\bin
set PATH=%PATH%;C:\Qt\Tools\mingw48_32\bin

qmake
mingw32-make release

del /Q ..\dist
mkdir ..\dist

xcopy release\KCTViewer.exe ..\dist\
xcopy C:\Qt\5.2.0\mingw48_32\bin\libgcc_s_dw2-1.dll ..\dist\
xcopy C:\Qt\5.2.0\mingw48_32\bin\libstdc++-6.dll ..\dist\
xcopy C:\Qt\5.2.0\mingw48_32\bin\libwinpthread-1.dll ..\dist\
windeployqt --no-translations ..\dist\KCTViewer.exe

del /q ..\dist\accessible\*d.dll
del /q ..\dist\bearer\*d.dll
del /q ..\dist\iconengines\*d.dll
del /q ..\dist\imageformats\*d.dll
del /q ..\dist\mediaservice\*d.dll
del /q ..\dist\platforms\*d.dll

rmdir /s /q ..\dist\playlistformats
rmdir /s /q ..\dist\printsupport
rmdir /s /q ..\dist\qmltooling
rmdir /s /q ..\dist\sqldrivers

mingw32-make clean
rmdir /s /q debug
rmdir /s /q release

::pause
