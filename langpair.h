//    Copyright (c) 2010, Andrey Ilyin (ortfero@gmail.com)
//
//    This file is part of Qtr.
//
//    Qtr is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Qtr is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with Qtr.  If not, see <http://www.gnu.org/licenses/>.



#ifndef LANGPAIR_H
#define LANGPAIR_H



#include <QtCore/QString>
#include "language.h"


struct LangPair
{
    LangPair();

    const QString toString() const;

    Language & source();
    Language & result();

    const Language & source() const;
    const Language & result() const;

private:

    LangPair( const LangPair & );

    Language _source;
    Language _result;
};



inline
LangPair::LangPair()
{ }



inline const QString
LangPair::toString() const
{
    static const QString PATTERN = "%1|%2";
    QString result = PATTERN;
    return result.arg( _source.abbr(), _result.abbr() );
}



inline Language &
LangPair::source()
{
    return _source;
}



inline Language &
LangPair::result()
{
    return _result;
}



inline const Language &
LangPair::source() const
{
    return _source;
}



inline const Language &
LangPair::result() const
{
    return _result;
}



#endif // LANGPAIR_H
