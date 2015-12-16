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

# This script will lookup for a description 
# of given application in manpages.
#
# it failse for bash for some reason and several other apps...

function getDescription
{
# Get first line in "NAME" section of manpage, remove "application_name -" prefix and trim. 
man $1 | awk '/NAME/{getline; print}' | sed -e 's/.*-//' | sed -e 's/^[[:space:]]*//' -e 's/[[:space:]]*$//' 
}

if [ -n "$1" ]; then
	# search manpage for given parameter string
	getDescription $1
else
	# ... or from pipe "|" input.
	read var
	getDescription ${var}
fi

