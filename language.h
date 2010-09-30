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



#ifndef LANGUAGE_H
#define LANGUAGE_H



#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QVariant>
#include <QtCore/QDebug>



struct Language
{
    struct List;

    Language();
    Language( const QString & name, const QString & abbr );
    Language( const Language & other );

    Language & operator = ( const Language & other );

    const QString & name() const;
    const QString & abbr() const;

    static const List LIST;

    static const QVariant packPtr( const Language * language );
    static const Language * unpackPtr( const QVariant packed );

private:

    QString _name;
    QString _abbr;
};



struct Language::List : public QVector< Language >
{
    List();
};



inline
Language::Language()
    : _name( "unknown" )
{ }



inline
Language::Language( const QString & name, const QString & abbr )
: _name( name ), _abbr( abbr )
{ }



inline
Language::Language( const Language & other )
: _name( other._name ), _abbr( other._abbr )
{ }



inline Language &
Language::operator = ( const Language & other )
{
    _name = other._name;
    _abbr = other._abbr;
    return( * this );
}



inline const QString &
Language::name() const
{
    return _name;
}



inline const QString &
Language::abbr() const
{
    return _abbr;
}



inline const QVariant
Language::packPtr( const Language * language )
{
    return QVariant( ( long long )language );
}



inline const Language *
Language::unpackPtr( const QVariant packed )
{
    return ( Language * )( packed.toLongLong() );
}



inline
Language::List::List()
{
    reserve( 128 );
    clear();
    append( Language() );
    append( Language( "afrikaans" , "af" ) );
    append( Language( "albanian" , "sq" ) );
    append( Language( "amharic" , "am" ) );
    append( Language( "arabic" , "ar" ) );
    append( Language( "armenian" , "hy" ) );
    append( Language( "azerbaijani" , "az" ) );
    append( Language( "basque" , "eu" ) );
    append( Language( "belarusian" , "be" ) );
    append( Language( "bengali" , "bn" ) );
    append( Language( "bihari" , "bh" ) );
    append( Language( "bulgarian" , "bg" ) );
    append( Language( "burmese" , "my" ) );
    append( Language( "catalan" , "ca" ) );
    append( Language( "cherokee" , "chr" ) );
    append( Language( "chinese" , "zh" ) );
    append( Language( "chinese simplified" , "zh-CN" ) );
    append( Language( "chinese traditional" , "zh-TW" ) );
    append( Language( "croatian" , "hr" ) );
    append( Language( "czech" , "cs" ) );
    append( Language( "danish" , "da" ) );
    append( Language( "dhiveli" , "dv" ) );
    append( Language( "dutch", "nl" ) );
    append( Language( "english" , "en" ) );
    append( Language( "esperanto" , "eo" ) );
    append( Language( "estonian" , "et" ) );
    append( Language( "filipino" , "tl" ) );
    append( Language( "finnish" , "fi" ) );
    append( Language( "french" , "fr" ) );
    append( Language( "galician" , "gl" ) );
    append( Language( "georgian" , "ka" ) );
    append( Language( "german" , "de" ) );
    append( Language( "greek" , "el" ) );
    append( Language( "guarani" , "gn" ) );
    append( Language( "gujarati" , "gu" ) );
    append( Language( "hebrew" , "iw" ) );
    append( Language( "hindi" , "hi" ) );
    append( Language( "hungarian" , "hu" ) );
    append( Language( "icelandic" , "is" ) );
    append( Language( "indonesian" , "id" ) );
    append( Language( "inuktitut" , "iu" ) );
    append( Language( "italian" , "it" ) );
    append( Language( "japanese" , "ja" ) );
    append( Language( "kannada" , "kn" ) );
    append( Language( "kazakh" , "kk" ) );
    append( Language( "khmer" , "km" ) );
    append( Language( "korean" , "ko" ) );
    append( Language( "kurdish", "ku" ) );
    append( Language( "kyrgyz", "ky" ) );
    append( Language( "laothian", "lo" ) );
    append( Language( "latvian" , "lv" ) );
    append( Language( "lithuanian" , "lt" ) );
    append( Language( "macedonian" , "mk" ) );
    append( Language( "malay" , "ms" ) );
    append( Language( "malayalam" , "ml" ) );
    append( Language( "maltese" , "mt" ) );
    append( Language( "marathi" , "mr" ) );
    append( Language( "mongolian" , "mn" ) );
    append( Language( "nepali" , "ne" ) );
    append( Language( "norwegian" , "no" ) );
    append( Language( "oriya" , "or" ) );
    append( Language( "pashto" , "ps" ) );
    append( Language( "persian" , "fa" ) );
    append( Language( "polish" , "pl" ) );
    append( Language( "portuguese" , "pt-PT" ) );
    append( Language( "punjabi" , "pa" ) );
    append( Language( "romanian" , "ro" ) );
    append( Language( "russian" , "ru" ) );
    append( Language( "sanskrit" , "sa" ) );
    append( Language( "serbian" , "sr" ) );
    append( Language( "sindhi" , "sd" ) );
    append( Language( "sinhalese" , "si" ) );
    append( Language( "slovak" , "sk" ) );
    append( Language( "slovenian" , "sl" ) );
    append( Language( "spanish" , "es" ) );
    append( Language( "swahili" , "sw" ) );
    append( Language( "swedish" , "sv" ) );
    append( Language( "tajik" , "tg" ) );
    append( Language( "tamil" , "ta" ) );
    append( Language( "tagalog" , "tl" ) );
    append( Language( "telugu" , "te" ) );
    append( Language( "thai" , "th" ) );
    append( Language( "tibetian" , "bo" ) );
    append( Language( "turkish" , "tr" ) );
    append( Language( "ukrainian" , "uk" ) );
    append( Language( "urdu" , "ur" ) );
    append( Language( "uzbek" , "uz" ) );
    append( Language( "uighur" , "ug" ) );
    append( Language( "vietnamese" , "vi" ) );
}



#endif // LANGUAGE_H
