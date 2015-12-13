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

#include <fstream>

#include "AppsException.h"
#include "SglStringUtils/SglStringUtils.h"
#include "AppsXmlConstants.h"
#include "MenuManager.h"

namespace Apps {
using namespace AppsXmlConsts;

MenuManager::MenuManager() :
    mUiOut(new UiPrinter()),
    mSelector(0)
{
    string homedir = GetEnvVar("HOME");
    if(homedir.empty())
        throw invalid_argument("HOME variable is empty. Please don't run me as root, I'm too young for it...\n");

    mAppsRcPath = homedir + FILESEPARATOR + APPS_RC_FOLDER + FILESEPARATOR + APPS_RC_FILENAME;

    if(isFileExists(mAppsRcPath) == false)
        createAppsrcFileStub();

    SglXmlElementPtr dom = SglXml::SglXml::parseFile(mAppsRcPath);
    mMenuParent = findMenuRootElement(dom);
    if(getElementsByTag(mMenuParent, MENU_ITEM_TAG).size() == 0)
        throw invalid_argument("Thanks for using apps!\nPlease add some categories and applications to\n" + mAppsRcPath);

    setupGlobalProperties(dom);
    dom.reset();

    eventMenuPrevious();
}

MenuManager::~MenuManager()
{
    delete mUiOut;
}

std::string MenuManager::GetEnvVar( const std::string & var ) {
     const char * val = std::getenv( var.c_str() );
     if ( val == 0 ) {
         return "";
     }
     else {
         return val;
     }
}

bool MenuManager::processKey(string key)
{
    if (key == mKeyCodeMenuPrevious)
        eventMenuPrevious();
    else if (key == mKeyCodeMenuNext)
        eventMenuNext();
    else if (key == mKeyCodeMenuIn)
        eventMenuIn();
    else if (key == mKeyCodeMenuOut)
        eventMenuOut();
    else if (key == mKeyCodeRun)
        eventMenuRun();
    else if (key == mKeyCodeExit)
        eventMenuExit();
    else
        return false;

    return true;
}

void MenuManager::setupGlobalProperties(SglXmlElementPtr menu)
{
    mIsShowColors = getPropertyValueBool(menu, PROP_SHOW_COLORS);
    mIsShowCmd = getPropertyValueBool(menu, PROP_SHOW_CMD);
    mIsShowComments = getPropertyValueBool(menu, PROP_SHOW_COMMENTS);
    mKeyCodeMenuPrevious = getPropertyValueStr(menu, PROP_KEYCODE_MENU_PREVIOUS);
    mKeyCodeMenuNext = getPropertyValueStr(menu, PROP_KEYCODE_MENU_NEXT);
    mKeyCodeMenuIn = getPropertyValueStr(menu, PROP_KEYCODE_MENU_IN);
    mKeyCodeMenuOut = getPropertyValueStr(menu, PROP_KEYCODE_MENU_OUT);
    mKeyCodeRun = getPropertyValueStr(menu, PROP_KEYCODE_MENU_RUN);
    mKeyCodeExit = getPropertyValueStr(menu, PROP_KEYCODE_MENU_EXIT);

    mFolderIconPre = getPropertyValueStr(menu, PROP_FOLDER_ICON_PRE);
    mFolderIconPost = getPropertyValueStr(menu, PROP_FOLDER_ICON_POST);
    mFolderAppPre = getPropertyValueStr(menu, PROP_APPLICATION_ICON_PRE);
    mFolderAppPost = getPropertyValueStr(menu, PROP_APPLICATION_ICON_POST);
}

void MenuManager::printCurrentMenuItem()
{
    string preIcon = "[?]";
    string postIcon = "";
    if(mMenuParent->getChilds().at(mSelector)->getTag() == MENU_ITEM_TAG)
    {
        preIcon = mFolderIconPre;
        postIcon = (mMenuParent->getChilds().at(mSelector)->getChilds().size() > 0 ? mFolderIconPost : "");
    }
    else if(mMenuParent->getChilds().at(mSelector)->getTag() == MENU_APPLICATION_TAG)
    {
        preIcon = mFolderAppPre;
        postIcon = (mMenuParent->getChilds().at(mSelector)->getAttribute(ATTRIBUTE_CMD) != "" ? mFolderAppPost : "");
    }

    vector<string> printItems;
    string cmd = mMenuParent->getChilds().at(mSelector)->getAttribute(ATTRIBUTE_CMD);
    if (mIsShowCmd && cmd != "")
        printItems.push_back(preIcon + cmd + postIcon);
    else
        printItems.push_back(preIcon + mMenuParent->getChilds().at(mSelector)->getAttribute(ATTRIBUTE_NAME) + postIcon);
    if(mIsShowComments)
        printItems.push_back("Comment: " + mMenuParent->getChilds().at(mSelector)->getAttribute(ATTRIBUTE_COMMENT));
    mUiOut->print(printItems);
}

void MenuManager::eventMenuPrevious()
{
    if (mSelector > 0)
        mSelector--;
    printCurrentMenuItem();
}

void MenuManager::eventMenuNext()
{
    if(mSelector < mMenuParent->getChilds().size() - 1)
        mSelector++;
    printCurrentMenuItem();
}

void MenuManager::eventMenuIn()
{
    if(mMenuParent->getChilds().at(mSelector)->getChilds().size() == 0)
        return;

    mMenuParent = mMenuParent->getChilds().at(mSelector);
    mSelector = 0;
    printCurrentMenuItem();
}

void MenuManager::eventMenuOut()
{
    if(!mMenuParent->getParent() || mMenuParent->getAttribute(ATTRIBUTE_NAME) == MENU_ROOT_NAME)
        return;
    mMenuParent = mMenuParent->getParent();
    mSelector = 0;
    printCurrentMenuItem();
}

void MenuManager::eventMenuRun()
{
    string cmd = mMenuParent->getChilds().at(mSelector)->getAttribute(ATTRIBUTE_CMD);
    if (cmd=="")
        return;
    system(cmd.c_str());
    throw AppsException (EXCEPTION_MSG_FINISHED, EXCEPTION_INFO);
}

void MenuManager::eventMenuExit()
{
    throw AppsException (EXCEPTION_MSG_FINISHED, EXCEPTION_INFO);
}

void MenuManager::createAppsrcFileStub()
{
    string mkdir = "mkdir -p " + mAppsRcPath.substr(0, mAppsRcPath.find(APPS_RC_FOLDER)) + APPS_RC_FOLDER;
    system(mkdir.c_str());
    ofstream myfile;
    myfile.open (mAppsRcPath.c_str());
    myfile << APPS_RC_DEFAULTS;
    myfile.close();
}

SglXmlElementPtr MenuManager::findMenuRootElement(SglXmlElementPtr menu)
{
    vector<SglXmlElementPtr> elements = getElementsByTag(menu, MENU_ITEM_TAG);
    for (SglXmlElementPtr element : elements)
        if(element->getAttribute(ATTRIBUTE_NAME) == MENU_ROOT_NAME)
            return element;
    throw invalid_argument("Thanks for using apps!\nPlease add some categories and applications to\n" + mAppsRcPath);
}

vector<SglXmlElementPtr> MenuManager::getElementsByTag(SglXmlElementPtr menu, string tag)
{
    vector<SglXmlElementPtr> result;
    for (SglXmlElementPtr element : menu->getChilds())
        if(element->getTag() == tag)
            result.push_back(element);

    return result;
}

string MenuManager::getPropertyValueStr(SglXmlElementPtr menu, string name)
{
    for (SglXmlElementPtr element : menu->getChilds())
        if (element->getAttribute(ATTRIBUTE_NAME) == name)
            return element->getAttribute(ATTRIBUTE_VALUE);

    return "";
}

int MenuManager::getPropertyValueInt(SglXmlElementPtr menu, string name)
{
    string result = getPropertyValueStr(menu, name);
    return (result == "" ? 0 : atoi(result.c_str()));
}

bool MenuManager::getPropertyValueBool(SglXmlElementPtr menu, string name)
{
    string result = getPropertyValueStr(menu, name);
    return (SglUtils::SglStringUtils::toLowCase(result) == "true" ? true : false);
}

};
