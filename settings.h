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



#ifndef SETTINGS_H
#define SETTINGS_H



#include <QtCore/QSettings>
#include <QtCore/QString>
#include <QtCore/QPoint>
#include <QtCore/QSize>
#include "langpair.h"



struct Settings
{

    void read();
    void write();

    const LangPair & langPair() const;
    LangPair & langPair();

    const QPoint & pos() const;
    QPoint & pos();

    const QSize & size() const;
    QSize & size();

private:

    static const QString SOURCE_NAME;
    static const QString SOURCE_ABBR;
    static const QString RESULT_NAME;
    static const QString RESULT_ABBR;
    static const QString GEOMETRY_POS;
    static const QString GEOMETRY_SIZE;

    QSettings _settings;
    LangPair _langPair;
    QPoint _pos;
    QSize _size;
};



inline void
Settings::read()
{
    _langPair.source() = Language(
        _settings.value( SOURCE_NAME, "unknown" ).toString(),
        _settings.value( SOURCE_ABBR, "" ).toString()
    );

    _langPair.result() = Language(
        _settings.value( RESULT_NAME, "english" ).toString(),
        _settings.value( RESULT_ABBR, "en" ).toString()
    );

    _pos = _settings.value( GEOMETRY_POS,
                            QPoint( 0, 0 ) ).toPoint();
    _size = _settings.value( GEOMETRY_SIZE,
                             QSize( 120, 240 ) ).toSize();
}



inline void
Settings::write()
{
    _settings.setValue( SOURCE_NAME, _langPair.source().name() );
    _settings.setValue( SOURCE_ABBR, _langPair.source().abbr() );
    _settings.setValue( RESULT_NAME, _langPair.result().name() );
    _settings.setValue( RESULT_ABBR, _langPair.result().abbr() );
    _settings.setValue( GEOMETRY_POS, _pos );
    _settings.setValue( GEOMETRY_SIZE, _size );
}



inline const LangPair &
Settings::langPair() const
{
    return _langPair;
}



inline LangPair &
Settings::langPair()
{
    return _langPair;
}


inline const QPoint &
Settings::pos() const
{
    return _pos;
}



inline QPoint &
Settings::pos()
{
    return _pos;
}



inline const QSize &
Settings::size() const
{
    return _size;
}



inline QSize &
Settings::size()
{
    return _size;
}



#endif // SETTINGS_H
