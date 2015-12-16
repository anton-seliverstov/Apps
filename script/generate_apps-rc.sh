#!/bin/bash

# Copyright 2015 Anton Seliverstov (seliverstov.ad@ya.ru)
#
# This file is part of Apps.
#
# Apps is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Apps is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Apps.  If not, see <http://www.gnu.org/licenses/>.
#

# This script will lookup for executables in description folder
# and add to menu those, that have matching package name,
# because in most cases package has the same name as main executable.
#
# By default it looks for executables in 
# /usr/bin,
# moves existing apps-rc to apps-rc_backup and creates new
# ~/.config/apps/apps-rc
#
# usage:
# ./generate_apps-rc.sh [where] [apps-rc filename]
#

# backup - first of all!
timestamp="$(date +"%T-%d-%m-%y")"
mv "${HOME}/.config/apps/apps-rc" "${HOME}/.config/apps/apps-rc_backup_${timestamp}"
printf "Original apps-rc file was moved to\n\"${HOME}/.config/apps/apps-rc_backup_${timestamp}\"\n"

# process cmd parameters...
filename="${HOME}/.config/apps/apps-rc"
description="/usr/bin"
if [ -n "$1" ]; then
    description=$1
fi
if [ -n "$2" ]; then
    filename=$2
fi

# just in case, get folder of this script.
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# make sure destination folder contains some executables
if [ "$(find ${description} -executable)" ]; then
    echo "Scanning ${description}..."
else
    echo "${description} is Empty"
    exit 1
fi

# output header of default settings + start root menu element
printf  "<apps >\
\n    -- see \"man apps\" for detailed information.\
\n    <prop name=\"SHOW_CMD\" value=\"false\"/>\
\n    <prop name=\"SHOW_COMMENTS\" value=\"true\"/>\
\n    -- arrows. see \"man apps-rc\" to learn codes.\
\n    <prop name=\"KEYCODE_MENU_PREVIOUS\" value=\"027 091 065\"/>\
\n    <prop name=\"KEYCODE_MENU_NEXT\" value=\"027 091 066\"/>\
\n    <prop name=\"KEYCODE_MENU_IN\" value=\"027 091 067\"/>\
\n    <prop name=\"KEYCODE_MENU_OUT\" value=\"027 091 068\"/>\
\n    -- return button\
\n    <prop name=\"KEYCODE_MENU_RUN\" value=\"010\"/>\
\n    -- space bar\
\n    <prop name=\"KEYCODE_MENU_EXIT\" value=\"032\"/>\
\n    \
\n    <prop name=\"FOLDER_ICON_PRE\" value=\"|_| \"/>\
\n    <prop name=\"FOLDER_ICON_POST\" value=\" ~~\"/>\
\n    <prop name=\"APPLICATION_ICON_PRE\" value=\"| \"/>\
\n    <prop name=\"APPLICATION_ICON_POST\" value=\" ~~\"/>\
\n    \
\n    -- Main menu\
\n    <folder name=\"root\">\
" > ${filename}

# Spoiler will spinn, while we processing destination folder.
spoiler=("-" "\\" "|" "/")
# graphic selector
spoileri=0
# We want to spin it slow, once in several loops. 
spoilerc=0
spoilerdelay=10

# all valid programs will be added to this array
# as one string in format "category~~~name~~~cmd~~~comment"
items=()
itemsi=0

files="$(ls ${description})"
for file in  ${files}; do
	# spin spoiler it it's time...
    if [[ "${spoilerc}" == "${spoilerdelay}" ]]; then
        printf "\r${spoiler[spoileri]}"
        spoileri=$((spoileri+1))
        if [[ "${spoileri}" == "4" ]]; then
            spoileri=0
        fi
        spoilerc=0
    else
        spoilerc=$((spoilerc+1))
    fi
	
	# get file name
    name="${file%.*}"
	# "apt-cache show [app]" shows description of package. 
	# we assume, that package has same name as main executable file, that is true in most cases.
	# the "Section" is a unique field, so if it exists, the matching package description found.
    if [ "$(apt-cache show ${name} 2>/dev/null | grep Section  | head -n1)" ]; then
        section="$(apt-cache show ${name} 2>/dev/null | grep Section  | head -n1 | sed -e 's/.*: //')"
		# warning, there is also "Description-md5" field, that we don't want. 	        
		desc="$( apt-cache show ${name} 2>/dev/null | grep Description | head -n1 | sed -e 's/.*: //')"
		# adding to array of valid apps        
		items[itemsi]="${section}~~~${name}~~~${file}~~~${desc}"
        itemsi=$((itemsi+1))
    fi
done

printf "\rFound ${itemsi} applications, sorting...\n"

# this function checks whether array contains string.
function contains() {
    local n=$#
    local value=${!n}
    for ((i=1;i < $#;i++)); 
    do
        if [ "${!i}" == "${value}" ]; then
            echo "y"
            return 0
        fi
    done
    echo "n"
    return 1
}

# here we split applications by categories.
# arrays in Bash is a nightmare, and that's why this part is so ugly =(
usedCategories=()
usedCategoriesi=0
for ((i = 0; i < ${#items[@]}; i++))
do
	# so here we iterate all apps, pick a category 
	# and if it wasn't added so far, we search for apps that has same category
	# by iterating same array again.
    category="$(echo ${items[$i]} | sed -e 's/~~~.*//')"
    if [ $(contains "${usedCategories[@]}" "${category}") == "y" ]; then
        continue
    else
		# array usedCategories cantains all unique categories,
		# if selected category is not there yet - search for apps to add.
        usedCategories[usedCategoriesi]=${category}
        usedCategoriesi=$((usedCategoriesi+1))
        echo "Adding category \"${category}\""
        printf "\n        <folder name=\"${category}\" >\n" >> ${filename}
    fi
    
	# here we search apps that match selected category
    cati=0
    categoryItems=()
    for ((j = 0; j < ${#items[@]}; j++))
    do
        currentCategory="$(echo ${items[$j]} | sed -e 's/~~~.*//')"
        if [ "${category}" == "${currentCategory}" ]; then
            categoryItems[cati]="${items[$j]}"
            cati=$((cati+1))
        fi
    done
	
	# write down found apps. Obviously, there will be at least one.
    for ((k = 0; k < ${#categoryItems[@]}; k++))
    do
        name="$(echo ${categoryItems[k]} | awk -F'~~~' '{print $2}')"
        cmd="$(echo ${categoryItems[k]} | awk -F'~~~' '{print $3}')"
        comment="$(echo ${categoryItems[k]} | awk -F'~~~' '{print $4}')"
        printf "            <app name=\"${name}\" cmd=\"${cmd}\" comment=\"${comment}\" />\n" >> ${filename}
    done
	# close category
    printf "        </folder>\n" >> ${filename}
done

# close root menu element and <apps>.
printf  "${result}
\n    </folder>\
\n</apps >\
\n" >> ${filename}

