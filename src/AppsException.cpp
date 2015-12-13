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

#include "AppsException.h"

namespace Apps {

AppsException::AppsException(const std::string &message, int severity) :
    mMessage(message),
    mSeverity(severity)
{
}

const char* AppsException::what() const throw()
{
    return mMessage.c_str();
}

string AppsException::message() const
{
    return mMessage;
}

int AppsException::severity() const
{
    return mSeverity;
}

}
