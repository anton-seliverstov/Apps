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

#ifndef UIPRINTER_H
#define UIPRINTER_H

#include <string>
#include <vector>

namespace Apps {

using namespace std;

/**
 * @brief Prints messages to console in a specific to this app way.
 */
class UiPrinter
{
public:
    /**
     * @brief Constructor will try to connect to current console
     * and prepare it for output.
     */
    UiPrinter(int rows);
    ~UiPrinter();

    /**
     * @brief prints lines from argument to console one-by-one.
     * @param strings - lines to print.
     */
    void print(vector<string> strings);

protected:
    void clear();
    void clearLine();
    void jumpUp(int num=1);
    void hideAnsiCursor();
    void showAnsiCursor();

protected:
    int     mColumns;
    int     mRows;
};

}
#endif // UIPRINTER_H
