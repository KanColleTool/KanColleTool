REM @echo off

for /d %%f in (%LOCALAPPDATA%\GitHub\PortableGit_*) do (
	PATH=%%f\bin;%PATH%
	break
)

call:update_repo tool
call:update_repo viewer

pause

:update_repo
if exist %~1 (
	cd %~1
	git pull --rebase
	cd ..
) else (
	git clone "git://github.com/KanColleTool/kct-%~1.git" %~1
)
goto:eof
