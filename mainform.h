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



#ifndef MAINFORM_H
#define MAINFORM_H



#include <QtCore/QDebug>
#include <QtGui/QWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QLabel>
#include <QtGui/QShortcut>



class MainForm : public QWidget
{
    Q_OBJECT

public:

    MainForm( QWidget * parent );

    const QString originalText() const;
    void setTranslatedText( const QString & translatedText );
    void clear();

signals:

    void translateClicked();
    void optionsClicked();
    void exitShortcutActivated();
    void translateShortcutActivated();
    void minimizeShortcutActivated();

protected:

    void showEvent( QShowEvent * event );

private slots:

    void onSourceChanged();

private:

    QVBoxLayout * _layout;
    QTextEdit * _originalText;
    QPushButton * _optionsButton;
    QPushButton * _translateButton;
    QTextEdit * _translatedText;
    QShortcut * _exitShortcut;
    QShortcut * _translateShortcut;
    QShortcut * _translateShortcutDup;
    QShortcut * _minimizeShortcut;
};



inline
MainForm::MainForm( QWidget * parent )
    : QWidget( parent ), _exitShortcut( 0 ), _translateShortcut( 0 ),
      _translateShortcutDup( 0 ), _minimizeShortcut( 0 )
{
    _layout = new QVBoxLayout( this );
    setLayout( _layout );

    _originalText = new QTextEdit( this );
    connect( _originalText, SIGNAL( textChanged() ),
             this, SLOT( onSourceChanged() ) );
    _layout->addWidget( _originalText );

    QWidget * buttonWidget = new QWidget( this );

    QHBoxLayout * buttonLayout = new QHBoxLayout( buttonWidget );
    buttonLayout->setMargin( 0 );

    _optionsButton = new QPushButton( buttonWidget );
    _optionsButton->setIcon( QIcon(":/img/configure.png"));
    _optionsButton->setSizePolicy( QSizePolicy::Maximum,
                                   QSizePolicy::Preferred );
    connect( _optionsButton, SIGNAL( clicked() ),
             this, SIGNAL( optionsClicked() ) );
    buttonLayout->addWidget( _optionsButton );


    buttonLayout->addStretch();

    _translateButton = new QPushButton( buttonWidget );
    _translateButton->setIcon( QIcon( ":/img/translate.png" ) );
    _translateButton->setText( tr( "translate" ) );
    _translateButton->setEnabled( false );
    connect( _translateButton, SIGNAL( clicked() ),
             this, SIGNAL( translateClicked() ) );
    buttonLayout->addWidget( _translateButton );

    _layout->addWidget( buttonWidget );


    _translatedText = new QTextEdit( this );
    _translatedText->setReadOnly( true );
    _translatedText->setBackgroundRole( QPalette::Window );
    _layout->addWidget( _translatedText );

}



inline const QString
MainForm::originalText() const
{
    return _originalText->toPlainText();
}



inline void
MainForm::setTranslatedText( const QString & translatedText )
{
    _translatedText->setText( translatedText );
}



inline void
MainForm::clear()
{
    _originalText->clear();
    _translatedText->clear();
}



inline void
MainForm::showEvent( QShowEvent * event )
{
    if( _exitShortcut != 0 )
        delete _exitShortcut;
    _exitShortcut = new QShortcut( Qt::CTRL + Qt::Key_Q, this );
    connect( _exitShortcut, SIGNAL( activated() ),
             this, SIGNAL( exitShortcutActivated() ) );

    if( _translateShortcut != 0 )
        delete _translateShortcut;
    _translateShortcut = new QShortcut( Qt::CTRL + Qt::Key_T, this );
    connect( _translateShortcut, SIGNAL( activated() ),
             this, SIGNAL( translateShortcutActivated() ) );

    if( _translateShortcutDup != 0 )
        delete _translateShortcutDup;
    _translateShortcutDup = new QShortcut( Qt::CTRL + Qt::Key_Return, this );
    connect( _translateShortcutDup, SIGNAL( activated() ),
             this, SIGNAL( translateShortcutActivated() ) );

    if( _minimizeShortcut != 0 )
        delete _minimizeShortcut;
    _minimizeShortcut = new QShortcut( Qt::Key_Escape, this );
    connect( _minimizeShortcut, SIGNAL( activated() ),
             this, SIGNAL( minimizeShortcutActivated() ) );

}



inline void
MainForm::onSourceChanged()
{
    _translateButton->setEnabled( ! _originalText->document()->isEmpty() );
}



#endif // MAINFORM_H
