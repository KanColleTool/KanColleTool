@echo off

for /d %%f in (%LOCALAPPDATA%\GitHub\PortableGit_*) do (
	PATH=%%f\bin;%%PATH%%
	break
)

echo "--> Updating main repo..."
git stash
git pull --rebase
git stash pop

call:updateRepo tool
call:updateRepo viewer

:updateRepo
if exist %~1 (
	echo."--> Updating %~1..."
	cd %~1
	git pull --rebase
	cd ..
) else (
	git clone "git://github.com/KanColleTool/kct-%~1.git" %~1
)
goto:eof
