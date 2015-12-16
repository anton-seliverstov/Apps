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

#ifndef APPSEXCEPTION_H
#define APPSEXCEPTION_H

#include <exception>
#include <string>

namespace Apps {
using namespace std;

static const string EXCEPTION_MSG_FINISHED = "finished";

static const int EXCEPTION_ERROR = 0;
static const int EXCEPTION_WARN = 1;
static const int EXCEPTION_INFO = 2;

/**
 * @brief Exception used to report errors to Main.
 */
class AppsException : public exception
{
public:
    AppsException(const string& message, int severity=0);
    virtual const char* what() const throw();
    string message() const;
    int severity() const;

protected:
    string  mMessage;
    int     mSeverity;
};

}

#endif // APPSEXCEPTION_H
