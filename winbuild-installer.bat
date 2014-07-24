set PATH=%PATH%;C:\Program Files (x86)\Inno Setup 5

cd targets\windows
compil32 /cc KanColleTool.iss
cp Output\*.exe ..\..\dist\
cd ..\..
