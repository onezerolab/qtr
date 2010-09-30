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



#ifndef CONTROLLER_H
#define CONTROLLER_H



#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QScopedPointer>
#include <QtCore/QSettings>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>

#include "frame.h"
#include "mainform.h"
#include "optionsform.h"
#include "aboutform.h"
#include "helpform.h"
#include "connector.h"
#include "language.h"
#include "langpair.h"
#include "settings.h"



class Controller : public QObject
{
    Q_OBJECT

public:

    Controller();
    ~Controller();

private slots:

    void onBeginTranslation();
    void onTranslationFinished( const TranslationResult & result );
    void onOptionsClicked();
    void onOptionsHelpClicked();
    void onOptionsAboutClicked();
    void onOptionsExitClicked();
    void onOptionsBackClicked();
    void onBackClicked();

private:

    Connector * _connector;
    LangPair _langPair;
    QScopedPointer< Frame > _frame;
    MainForm * _mainForm;
    OptionsForm * _optionsForm;
    HelpForm * _helpForm;
    AboutForm * _aboutForm;
};



inline
Controller::Controller()
{
    QCoreApplication::setOrganizationName( "Andrey Ilyin" );
    QCoreApplication::setOrganizationDomain( "bitorious.com" );
    QCoreApplication::setApplicationName( "Qtr" );

    Settings settings;
    settings.read();
    _langPair = settings.langPair();

    _connector = new Connector( this );
    connect( _connector, SIGNAL( translationFinished(TranslationResult) ),
             this, SLOT( onTranslationFinished(TranslationResult) ) );

    _frame.reset( new Frame );

    _mainForm = new MainForm( _frame.data() );
    connect( _mainForm, SIGNAL( translateClicked() ),
             this, SLOT( onBeginTranslation() ) );
    connect( _mainForm, SIGNAL( optionsClicked() ),
             this, SLOT( onOptionsClicked() ) );
    connect( _mainForm, SIGNAL( exitShortcutActivated() ),
             _frame.data(), SLOT( close() ) );
    connect( _mainForm, SIGNAL( translateShortcutActivated() ),
             this, SLOT( onBeginTranslation() ) );
    connect( _mainForm, SIGNAL( minimizeShortcutActivated() ),
             _frame.data(), SLOT( showMinimized() ) );
    _frame->addForm( _mainForm );


    _optionsForm = new OptionsForm;
    connect( _optionsForm, SIGNAL( helpClicked() ),
             this, SLOT( onOptionsHelpClicked() ) );
    connect( _optionsForm, SIGNAL( aboutClicked() ),
             this, SLOT( onOptionsAboutClicked() ) );
    connect( _optionsForm, SIGNAL( exitClicked() ),
             this, SLOT( onOptionsExitClicked() ) );
    connect( _optionsForm, SIGNAL( backClicked() ),
             this, SLOT( onOptionsBackClicked() ) );

    for( Language::List::ConstIterator it = Language::LIST.begin();
         it != Language::LIST.end();
         ++it )
    {

        const Language & language = * it;
        _optionsForm->addLanguage( language.name(),
                                   Language::packPtr( & language ) );
    }
    _frame->addForm( _optionsForm );

    _helpForm = new HelpForm;
    connect( _helpForm, SIGNAL( backClicked() ),
            this, SLOT( onBackClicked() ) );
    _frame->addForm( _helpForm );

    _aboutForm = new AboutForm;
    _aboutForm->setTitle( QCoreApplication::applicationName() );
    _aboutForm->setBuildStamp( __DATE__ );
    _aboutForm->setOrganization( QCoreApplication::organizationName() );
    _aboutForm->setEmail( "ortfero@gmail.com" );
    connect( _aboutForm, SIGNAL( backClicked() ),
            this, SLOT( onBackClicked() ) );
    _frame->addForm( _aboutForm );

    _frame->move( settings.pos() );
    _frame->resize( settings.size() );
    _frame->setWindowTitle( QCoreApplication::applicationName() );
}



inline
Controller::~Controller()
{
    Settings settings;
    settings.langPair() = _langPair;
    settings.pos() = _frame->pos();
    settings.size() = _frame->size();
    settings.write();
}



inline void
Controller::onBeginTranslation()
{
    _connector->onBeginTranslation( _mainForm->originalText(), _langPair );
}



inline void
Controller::onTranslationFinished( const TranslationResult & result )
{
    if( result.isSucceeded() )
    {
        _mainForm->setTranslatedText( result.message() );
        _frame->clearStatus();
    }
    else
    {
        _frame->setStatus( result.message() );
        _mainForm->clear();
    }
}



inline void
Controller::onOptionsClicked()
{
    _optionsForm->setLangPair( _langPair.source().name(),
                               _langPair.result().name() );
    _frame->setCurrentForm( _optionsForm );
}



inline void
Controller::onOptionsHelpClicked()
{
    _frame->setCurrentForm( _helpForm );
}



inline void
Controller::onOptionsAboutClicked()
{
    _frame->setCurrentForm( _aboutForm );
}



inline void
Controller::onOptionsExitClicked()
{
    _frame->close();
}


inline void
Controller::onOptionsBackClicked()
{
    _langPair.source() = * Language::unpackPtr( _optionsForm->sourceLanguage() );
    _langPair.result() = * Language::unpackPtr( _optionsForm->resultLanguage() );
    _frame->setCurrentForm( _mainForm );
}



inline void
Controller::onBackClicked()
{
    _frame->setCurrentForm( _optionsForm );
}




#endif // CONTROLLER_H
