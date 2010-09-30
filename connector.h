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



#ifndef CONNECTOR_H
#define CONNECTOR_H



#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtCore/QString>
#include <QtCore/QByteArray>
#include <QtCore/QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include "langpair.h"
#include "parser.h"



struct TranslationResult
{
    TranslationResult();

    void succeeded( const QString & message );
    void failed( const QString & message );

    bool isSucceeded() const;
    const QString & message() const;

private:

    bool _succeeded;
    QString _message;
};



class Connector : public QObject
{
    Q_OBJECT

public:

    Connector( QObject * parent );
    ~Connector();

signals:

    void translationFinished( const TranslationResult & result );

public slots:

    void onBeginTranslation( const QString originalText,
                             const LangPair & langPair );

private slots:

    void onReplyFinished( QNetworkReply * reply );

private:

    QNetworkRequest buildRequest( const QString originalText,
                                  const LangPair & langPair );

    const QString & translationUrl() const;

    TranslationResult _translationResult;
    Parser _parser;
    QNetworkAccessManager * _network;
};



inline
TranslationResult::TranslationResult()
    : _succeeded( false )
{ }



inline void
TranslationResult::succeeded( const QString & message )
{
    _succeeded = true;
    _message = message;
}



inline void
TranslationResult::failed( const QString & message )
{
    _succeeded = false;
    _message = message;
}



inline bool
TranslationResult::isSucceeded() const
{
    return _succeeded;
}



inline const QString &
TranslationResult::message() const
{
    return _message;
}



inline
Connector::Connector( QObject * parent )
: QObject( parent )
{
    _network = new QNetworkAccessManager( this );
    connect( _network, SIGNAL( finished(QNetworkReply*) ),
             this, SLOT( onReplyFinished(QNetworkReply*) ) );
}



inline
Connector::~Connector()
{ }



inline void
Connector::onBeginTranslation( const QString originalText,
                               const LangPair & langPair )
{
    _network->get( buildRequest( originalText, langPair ) );
}



inline void
Connector::onReplyFinished( QNetworkReply * reply )
{
    if( reply->error() == QNetworkReply::NoError )
    {
        QByteArray resultBytes = reply->readAll();
        QString resultString = QString::fromUtf8( resultBytes.constData(),
                                                  resultBytes.size() );
        if( _parser.parse( resultString ) )
            _translationResult.succeeded( _parser.message() );
        else
            _translationResult.failed( _parser.message() );
    }
    else
    {
        _translationResult.failed( tr( "Unable to translate source text" ) );
    }
    emit translationFinished( _translationResult );
    reply->deleteLater();
}



inline QNetworkRequest
Connector::buildRequest( const QString originalText,
                         const LangPair & langPair )
{
    QUrl url = translationUrl();
    url.addQueryItem( "v", "1.0" );
    url.addQueryItem( "q", originalText );
    url.addQueryItem( "langpair", langPair.toString() );
    return QNetworkRequest( url );
}


inline const QString &
Connector::translationUrl() const
{
    static const QString url =
                  "http://ajax.googleapis.com/ajax/services/language/translate";

    return url;
}



#endif // CONNECTOR_H
