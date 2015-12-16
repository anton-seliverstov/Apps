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

#include <iostream>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include "UiPrinter.h"

namespace Apps {

UiPrinter::UiPrinter() :
    mColumns(0)
{
    try{
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        mColumns = w.ws_col;
    }catch(...)
    {
        mColumns = 80;
    }

    clearLine();
    jumpUp();
}

UiPrinter::~UiPrinter()
{
    cout << endl;
}

void UiPrinter::print(vector<string> strings)
{
    clearLine();
    cout << "\r" << strings.at(0);
    for (int i = 1; i < strings.size(); i++)
    {
        cout << "\n";
        clearLine();
        cout << "\r" << strings.at(i);
    }
    jumpUp(strings.size() - 1);
    cout << "\r";
}

void UiPrinter::clearLine()
{
    string cleanLine(mColumns, ' ');
    cout << "\r" << cleanLine;
}

void UiPrinter::jumpUp(int num)
{
    for (int i=0; i<num; i++)
        cout << "\x1b[A";
}

}
