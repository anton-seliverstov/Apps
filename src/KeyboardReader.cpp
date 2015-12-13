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

// console access
#include <stdio.h>
#include <termios.h>

// character sequence formatted result
#include <sstream>
#include <iomanip>

#include "AppsException.h"
#include "KeyboardReader.h"

namespace Apps {

int KeyboardReader::getchAny(int echo)
{
    int ch = 0;
    struct termios oldt;
    tcgetattr(0, &oldt);                      /* grab old terminal i/o settings */
    //Non-blocking mode is not used in this release.
    //int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    //fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    try{
        struct termios newt = oldt;           /* make new settings same as old settings */
        newt.c_lflag &= ~ICANON;              /* disable buffered i/o */
        newt.c_lflag &= echo ? ECHO : ~ECHO;  /* set echo mode */
        tcsetattr(0, TCSANOW, &newt);         /* use these new terminal i/o settings now */
        fflush(stdin);
        ch = getchar();
    }catch (...) {
        tcsetattr(0, TCSANOW, &oldt);         /* Restore old terminal i/o settings */
        throw AppsException ("Can't connect to console!", EXCEPTION_ERROR);
    }

    //fcntl(STDIN_FILENO, F_SETFL, flags);
    tcsetattr(0, TCSANOW, &oldt);             /* Restore old terminal i/o settings */
    return ch;
}

int KeyboardReader::getch()
{
  return getchAny(0);
}

int KeyboardReader::getche()
{
  return getchAny(1);
}

void KeyboardReader::subscribeForeve(function<bool(string)>callback)
{
    static const string KEY_ESC_STR = "027";
    static const int KEY_ESC = 27;
    ostringstream sequence;
    while(true)
    {
        string current = sequence.str();
        if (((current.length() >= 3) && (current.substr(0, 3) != KEY_ESC_STR))
                || (isAnsiSequence(current) == true))
        {
            sequence.str("");
            sequence.clear();
        }

        int ch = getch();
        if (ch == KEY_ESC)
        {
            sequence.str("");
            sequence.clear();
        }

        current = sequence.str();
        sequence << (current=="" ? "" : " " ) << setfill('0') << setw(3) << ch;
        if(callback(sequence.str()))
        {
            sequence.str("");
            sequence.clear();
        }
    }
}

bool KeyboardReader::isAnsiSequence(string sequence)
{
string ansi[] = {"027 079 080",             // F1
                 "027 079 081",             // F2
                 "027 079 082",             // F3
                 "027 079 083",             // F4
                 "027 091 049 053 126",     // F5
                 "027 091 049 055 126",     // F6
                 "027 091 049 056 126",     // F7
                 "027 091 049 057 126",     // F8
                 "027 091 050 048 126",     // F9
                 "027 091 050 049 126",     // F10
                 "027 091 050 050 126",     // F11
                 "027 091 050 051 126",     // F12
                 "027 091 050 052 126",     // F12+
                 "027 091 049 126",         // Home
                 "027 079 072",             // Home+
                 "027 091 052 126",         // End
                 "027 079 070",             // End+
                 "027 091 053 126",         // Page-Up
                 "027 091 054 126",         // Page-Down
                 "027 091 050 126",         // Insert
                 "027 091 065",             // Up
                 "027 091 066",             // Down
                 "027 091 068",             // Right
                 "027 091 067"              // Left
                };
    for (string ansiSq : ansi)
        if (ansiSq == sequence)
            return true;
    return false;
}

}
