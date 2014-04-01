#!/bin/bash

SSH_INACCESSIBLE=false

update_repo()
{
	# Note: Repos are always fetched from the 'KanColleTool' user on GitHub
	REPO="$1"
	DEST="$2"
	NAME="$3"

	if [[ -d $DEST ]]; then
		echo -n "$(tput bold)Updating ${NAME}...$(tput sgr0)"
		
		# If the target directory exists, move into it
		OLDPWD=$(pwd)
		cd ${DEST}
		
		# If there are unstaged changes, we have to stash them to allow a pull
		CHANGED=$(git diff-index --name-only HEAD --)
		if [ -n "$CHANGED" ]; then
			git stash --quiet
		fi
		
		# Do a `git pull --rebase` with no progress, and report the status
		OUTPUT=$(git pull --no-progress --rebase)
		if [[ $? -eq 0 ]]; then
			echo "$(tput bold)$(tput setaf 2) Success$(tput sgr0)"
		else
			echo "$(tput bold)$(tput setaf 1)-> Error:$(tput sgr0)"
			echo $OUTPUT
			return 1
		fi
		
		# Restore the stashed changes, if there are any
		if [ -n "$CHANGED" ]; then
			git stash pop --quiet
		fi
		
		cd $OLDPWD
	else
		echo -n "$(tput bold)Cloning ${NAME}...$(tput sgr0)"
		
		# Otherwise, try to clone it via git, if that fails, try https instead
		# The former will fail if the user doesn't have their SSH key properly
		# set up with GitHub, in which case they probably only need readonly
		# access anyways.
		OUTPUT=$(git clone --no-progress git@github.com:KanColleTool/${REPO}.git ${DEST})
		if [[ $? -eq 0 ]]; then
			echo "$(tput bold)$(tput setaf 2) Success$(tput sgr0)"
		else
			OUTPUT2=$(git clone --no-progress https://github.com/KanColleTool/${REPO}.git ${DEST})
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

update_repo KanColleTool . "Main Repo"
update_repo kct-macviewer macviewer "Mac Viewer"
update_repo kct-viewer viewer "Viewer"
update_repo kct-tool tool "Tool"

# If an SSH clone failed, print a notice about it
if $SSH_INACCESSIBLE; then
	echo "Note: SSH clones appear to fail, likely because you haven't set up your SSH"
	echo "      keys (properly). This is probably not a problem, but worth noting."
	echo "      It's also possible that a firewall of some kind is blocking Port 22."
fi
