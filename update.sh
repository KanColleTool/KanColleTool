#!/bin/bash

SSH_INACCESSIBLE=false

update_repo()
{
	if [[ -d $1 ]]; then
		echo -n "$(tput bold)Updating $1...$(tput sgr0)"
		
		# If the target directory exists, move into it and `git pull --rebase`
		OLDPWD=$(pwd)
		cd $1
		OUTPUT=$(git pull --no-progress --rebase)
		if [[ $? -eq 0 ]]; then
			echo "$(tput bold)$(tput setaf 2) Success$(tput sgr0)"
		else
			echo "$(tput bold)$(tput setaf 1)-> Error:$(tput sgr0)"
			echo $OUTPUT
			return 1
		fi
		cd $OLDPWD
	else
		echo -n "$(tput bold)Cloning $1...$(tput sgr0)"
		
		# Otherwise, try to clone it via git, if that fails, try https instead
		# The former will fail if the user doesn't have their SSH key properly
		# set up with GitHub, in which case they probably only need readonly
		# access anyways.
		OUTPUT=$(git clone --no-progress git@github.com:KanColleTool/kct-$1.git $1)
		if [[ $? -eq 0 ]]; then
			echo "$(tput bold)$(tput setaf 2) Success$(tput sgr0)"
		else
			OUTPUT2=$(git clone --no-progress https://github.com/KanColleTool/kct-$1.git $1)
			if [[ $? -eq 0 ]]; then
				echo "$(tput bold)$(tput setaf 3) Success$(tput sgr0)"
				SSH_INACCESSIBLE=true
			else
				echo "$(tput bold)$(tput setaf 1)-> Failed$(tput sgr0)"
				exit
			fi
		fi
	fi
}

# Switch to the directory the script is stored in
cd $(dirname "${BASH_SOURCE[0]}")

update_repo macviewer
update_repo viewer
update_repo tool

# If an SSH clone failed, print a notice about it
if $SSH_INACCESSIBLE; then
	echo "Note: SSH clones appear to fail, likely because you haven't set up your SSH"
	echo "      keys (properly). This is probably not a problem, but worth noting."
	echo "      It's also possible that a firewall of some kind is blocking Port 22."
fi
