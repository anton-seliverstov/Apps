/*
Copyright 2016 Anton Seliverstov (seliverstov.ad@ya.ru)

This file is part of Apps.

Apps is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Apps is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Apps.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef APPSXMLCONSTANTS_H
#define APPSXMLCONSTANTS_H

#include <string>

namespace AppsXmlConsts {
using namespace std;

static const string FILESEPARATOR = "/";
static const string APPS_RC_FOLDER = ".config/apps";
static const string APPS_RC_FILENAME = "apps-rc";

static const string MENU_ITEM_TAG = "folder";
static const string PROPERTY_TAG = "prop";
static const string MENU_APPLICATION_TAG = "app";
static const string MENU_ROOT_NAME = "root";
static const string ATTRIBUTE_NAME = "name";
static const string ATTRIBUTE_CMD = "cmd";
static const string ATTRIBUTE_COMMENT = "comment";
static const string ATTRIBUTE_VALUE = "value";

static const string PROP_SHOW_COLORS = "SHOW_COLORS";
static const string PROP_SHOW_CMD = "SHOW_CMD";
static const string PROP_SHOW_COMMENTS = "SHOW_COMMENTS";
static const string PROP_KEYCODE_MENU_PREVIOUS = "KEYCODE_MENU_PREVIOUS";
static const string PROP_KEYCODE_MENU_NEXT = "KEYCODE_MENU_NEXT";
static const string PROP_KEYCODE_MENU_IN = "KEYCODE_MENU_IN";
static const string PROP_KEYCODE_MENU_OUT = "KEYCODE_MENU_OUT";
static const string PROP_KEYCODE_MENU_RUN = "KEYCODE_MENU_RUN";
static const string PROP_KEYCODE_MENU_EXIT = "KEYCODE_MENU_EXIT";

static const string PROP_FOLDER_ICON_PRE = "FOLDER_ICON_PRE";
static const string PROP_FOLDER_ICON_POST = "FOLDER_ICON_POST";
static const string PROP_APPLICATION_ICON_PRE = "APPLICATION_ICON_PRE";
static const string PROP_APPLICATION_ICON_POST = "APPLICATION_ICON_POST";

static const string APPS_RC_DEFAULTS = "<apps >\
\n    -- see \"man apps-rc\" for detailed information.\
\n    <prop name=\"SHOW_CMD\" value=\"false\"/>\
\n    <prop name=\"SHOW_COMMENTS\" value=\"true\"/>\
\n    -- arrows\
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
\n        <folder name=\"Network\">\
\n            <folder name=\"Linux\" comment=\"Common Linux environment.\">\
\n                <app name=\"ping -c4\" comment=\"ping 4 times only.\"/>\
\n                <app name=\"/sbin/ifconfig\" cmd=\"/sbin/ifconfig\" comment=\"Show IP to non-root user.\"/>\
\n            </folder>\
\n        </folder>\
\n        <folder name=\"Editors\">\
\n            <folder name=\"Linux\" comment=\"Common Linux environment.\">\
\n                <app name=\"vim\" cmd=\"vim\" comment=\"Full featured editor.\"/>\
\n            </folder>\
\n            <app name=\"nano\" comment=\"User friendly editor. Not Standard.\"/>\
\n        </folder>\
\n        <folder name=\"Admin tools\"/>\
\n        <folder name=\"Toys\"/>\
\n    </folder>\
\n</apps >\
\n";

}

#endif // APPSXMLCONSTANTS_H

