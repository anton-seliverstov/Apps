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

#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <string>
#include <sys/stat.h>
#include <stdexcept>

#include "UiPrinter.h"
#include "SglXml/SglXml.h"

namespace Apps {

using namespace std;
using namespace SglXml;

class MenuManager
{
public:
    MenuManager();
    ~MenuManager();
    bool processKey(string key);

protected:
    void setupGlobalProperties(SglXmlElementPtr menu);
    void printCurrentMenuItem();
    void eventMenuPrevious();
    void eventMenuNext();
    void eventMenuIn();
    void eventMenuOut();
    void eventMenuRun();
    void eventMenuExit();
    SglXmlElementPtr findMenuRootElement(SglXmlElementPtr menu);
    vector<SglXmlElementPtr> getElementsByTag(SglXmlElementPtr menu, string tag);
    string getPropertyValueStr(SglXmlElementPtr menu, string name);
    int getPropertyValueInt(SglXmlElementPtr menu, string name);
    bool getPropertyValueBool(SglXmlElementPtr menu, string name);

    static string GetEnvVar( const string & var );
    void createAppsrcFileStub();
    static inline bool isFileExists (const string& name)
    {
      struct stat buffer;
      return (stat (name.c_str(), &buffer) == 0);
    }

protected:
    string                  mAppsRcPath;
    UiPrinter               *mUiOut;
    SglXmlElementPtr        mMenuParent;
    int                     mSelector;

    bool                    mIsShowColors;
    bool                    mIsShowCmd;
    bool                    mIsShowComments;
    string                  mKeyCodeMenuPrevious;
    string                  mKeyCodeMenuNext;
    string                  mKeyCodeMenuIn;
    string                  mKeyCodeMenuOut;
    string                  mKeyCodeRun;
    string                  mKeyCodeExit;
    string                  mFolderIconPre;
    string                  mFolderIconPost;
    string                  mFolderAppPre;
    string                  mFolderAppPost;
};

}
#endif // MENUMANAGER_H
