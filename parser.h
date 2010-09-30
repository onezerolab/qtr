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



#ifndef PARSER_H
#define PARSER_H



#include <QtCore/QString>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>



struct Parser
{

    bool parse( const QString & source );
    const QString & message() const;

private:

    bool failWith( const QString & message );

    QString _message;
    QScriptEngine _engine;
};



inline bool
Parser::parse( const QString & source )\
{
    const int CORRECT_STATUS = 200;
    static const QString RESPONSE_STATUS = "responseStatus";
    static const QString RESPONSE_DETAILS = "responseDetails";
    static const QString RESPONSE_DATA = "responseData";
    static const QString TRANSLATED_TEXT = "translatedText";
    static const QString UNABLE_TO_PARSE = "Unable to parse response";
    static const QString INVALID_RESPONSE_STATUS = "Invalid \"responseStatus\"";
    static const QString INVALID_RESPONSE_DETAILS = "Invalid \"responseDetails\"";
    static const QString INVALID_RESPONSE_DATA = "Invalid \"responseData\"";
    static const QString INVALID_TRANSLATED_TEXT = "Invalid \"translatedText\"";

    QScriptValue response = _engine.evaluate( "(" + source + ")" );
    if( _engine.hasUncaughtException() )
        return failWith( UNABLE_TO_PARSE );

    QScriptValue responseStatus = response.property( RESPONSE_STATUS );
    if( ! responseStatus.isValid() || ! responseStatus.isNumber() )
        return failWith( INVALID_RESPONSE_STATUS );

    if( responseStatus.toInt32() != CORRECT_STATUS )
    {
        QScriptValue responseDetails = response.property( RESPONSE_DETAILS );
        if( ! responseDetails.isValid() || ! responseDetails.isString() )
            return failWith( INVALID_RESPONSE_DETAILS );

        return failWith( responseDetails.toString() );
    }

    QScriptValue responseData = response.property( RESPONSE_DATA );
    if( ! responseData.isValid() )
        return failWith( INVALID_RESPONSE_DATA );

    QScriptValue translatedText = responseData.property( TRANSLATED_TEXT );
    if( ! translatedText.isValid() || ! translatedText.isString())
        return failWith( INVALID_TRANSLATED_TEXT );

    _message = translatedText.toString();

    return true;
}



inline const QString &
Parser::message() const
{
    return _message;
}



inline bool
Parser::failWith( const QString & message )
{
    _message = message;
    return false;
}



#endif // PARSER_H
