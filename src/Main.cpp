/*
Copyright 2015 Anton Seliverstov (seliverstov.ad@ya.ru)

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


#include <signal.h>
#include <iostream>
#include <string>
#include <thread>

#include "KeyboardReader.h"
#include "MenuManager.h"
#include "AppsException.h"

using namespace Apps;

MenuManager     *menu = NULL;
KeyboardReader  *keyBoardReader = NULL;
thread          *keyBoardReaderThread = NULL;

void quitproc(int parameter);

int main()
{
    signal(SIGINT, quitproc);
    signal(SIGHUP, quitproc);
    signal(SIGQUIT, quitproc);

    try
    {
        menu = new MenuManager();
        keyBoardReader = new KeyboardReader(std::bind(&MenuManager::processKey, menu, std::placeholders::_1));
        keyBoardReaderThread = new thread(&KeyboardReader::run, keyBoardReader);
        if (keyBoardReaderThread->joinable())
            keyBoardReaderThread->join();
    }
    catch( const AppsException& e )
    {
        quitproc(0);
        if(e.severity() == EXCEPTION_INFO && e.message() == EXCEPTION_MSG_FINISHED)
            return 0;
        else
            return 1;
    }
    catch( const std::invalid_argument& e )
    {
        std::cout << e.what() << endl;
        quitproc(0);
    }
    catch( ... )
    {

        quitproc(0);
    }

    quitproc(0);
    return 0;

}

void quitproc(int parameter)
{
    try{
        if (keyBoardReaderThread)
        {
            if (keyBoardReaderThread->joinable())
                keyBoardReaderThread->join();
            delete keyBoardReaderThread;
        }
    }catch(...){}

    if (keyBoardReader)
        delete keyBoardReader;

    if (menu)
        delete menu;

    exit(0);
}
