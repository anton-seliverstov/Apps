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

#ifndef KEYBOARDREADER_H
#define KEYBOARDREADER_H

#include <functional>
#include <string>

namespace Apps {
using namespace std;

/**
 * @brief Reads keyboard character sequence.
 * It can return 1 symbol at a time or subscribe call back for
 * continuous updates.
 */
class KeyboardReader
{
public:
    /**
     * @brief Read 1 character without echo.
     * @return
     */
    int static getch();

    /**
     * @brief Read 1 character with echo.
     * @return
     */
    int static getche();

    /**
     * @brief subscribes callback for keyboard events.
     * There is no unsubscribe method.
     * It will break the sequence once it recognized it and on of
     * ANSI sequences, and when callback returns true.
     *
     * @param callback - function to subscribe.
     */
    void static subscribeForeve(function<bool(string)>callback);

protected:
    KeyboardReader();
    int static getchAny(int echo);
    bool static isAnsiSequence(string sequence);
};

}
#endif // KEYBOARDREADER_H
