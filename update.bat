@echo off

for /d %%f in (%LOCALAPPDATA%\GitHub\PortableGit_*) do ( set git=%%f\bin\git.exe )

%git% stash
%git% pull --rebase
%git% stash pop

%git% submodule foreach --recursive "git pull --rebase || git pull --rebase origin master"
