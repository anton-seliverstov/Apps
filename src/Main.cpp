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

#include <iostream>
#include <string>
#include <functional>

#include "KeyboardReader.h"
#include "MenuManager.h"
#include "AppsException.h"
#include "SglStringUtils.h"

using namespace Apps;

void fff(std::string s){}

class Test
{
public:
      void blah() { std::cout << "BLAH!" << std::endl; }
};

int main()
{
    MenuManager *menu = NULL;
    try
    {
        menu = new MenuManager();
        KeyboardReader::subscribeForeve(std::bind(&MenuManager::processKey, menu, std::placeholders::_1));
    }
    catch( const AppsException& e )
    {
        delete menu;
        if(e.severity() == EXCEPTION_INFO && e.message() == EXCEPTION_MSG_FINISHED)
            return 0;
        else
            return 1;
    }
    catch( const std::invalid_argument& e )
    {
        std::cout << e.what() << endl;
        delete menu;
        return (1);
    }
    catch( const exception& e )
    {
        std::cout << e.what() << endl;
        delete menu;
        return (1);
    }

    delete menu;
    return 0;
}

