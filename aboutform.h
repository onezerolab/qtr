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



#ifndef ABOUTFORM_H
#define ABOUTFORM_H



#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>



class AboutForm : public QWidget
{
    Q_OBJECT

public:

    AboutForm();
    void setTitle( const QString title );
    void setBuildStamp( const QString version );
    void setOrganization( const QString organization );
    void setEmail( const QString email );

signals:

    void backClicked();

private:

    QLabel * _title;
    QLabel * _version;
    QLabel * _copyright;
    QLabel * _feedback;
};



inline
AboutForm::AboutForm()
{
    QVBoxLayout * layout = new QVBoxLayout;

    setLayout( layout );

    _title = new QLabel;
    _title->setTextFormat( Qt::RichText );
    QFont titleFont( _title->font() );
    titleFont.setPointSize( titleFont.pointSize() + 4 );
    titleFont.setBold( true );
    _title->setFont( titleFont );
    layout->addWidget( _title );

    _version = new QLabel;
    _version->setTextFormat( Qt::RichText );
    layout->addWidget( _version );

    QLabel * description = new QLabel;
    description->setTextFormat( Qt::RichText );
    description->setWordWrap( true );
    description->setText( tr( "Multilingual translator using Google AJAX Language API" ) );
    layout->addWidget( description );

    _copyright = new QLabel;
    _copyright->setTextFormat( Qt::RichText );
    layout->addWidget( _copyright );

    QLabel * license = new QLabel;
    license->setTextFormat( Qt::RichText );
    license->setWordWrap( true );
    license->setText( tr( "Licensed under <b>GNU General Public License</b>" ) );
    layout->addWidget( license );

    QImage image( ":/img/gplv3.png" );
    QLabel * icon = new QLabel;
    icon->setPixmap( QPixmap::fromImage( image ) );
    layout->addWidget( icon );

    _feedback = new QLabel;
    _feedback->setTextFormat( Qt::RichText );
    _feedback->setWordWrap( true );
    _feedback->setOpenExternalLinks( true );
    layout->addWidget( _feedback );

    layout->addStretch();

    QPushButton * backButton = new QPushButton;
    backButton->setText( tr( "back" ) );
    connect( backButton, SIGNAL( clicked() ),
             this, SIGNAL( backClicked() ) );
    layout->addWidget( backButton );
}



inline void
AboutForm::setTitle( const QString title )
{
    _title->setText( title );
}



inline void
AboutForm::setBuildStamp( const QString version )
{
    _version->setText( tr( "Build on <b>%1</b>" ).arg( version ) );
}


inline void
AboutForm::setOrganization( const QString organization )
{
    _copyright->setText( tr( "Copyright (c) 2010, <b>%1</b>\n" ).arg( organization ) );
}


inline void
AboutForm::setEmail( const QString email )
{
    _feedback->setText( tr( "Send any suggestions to <b>%1</b>").arg( email ) );
}



#endif // ABOUTFORM_H
