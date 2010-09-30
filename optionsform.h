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



#ifndef OPTIONSFORM_H
#define OPTIONSFORM_H



#include <QtCore/QDebug>
#include <QtGui/QWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QFormLayout>
#include <QtGui/QComboBox>
#include <QtGui/QPushButton>
#include <QtGui/QGroupBox>



class OptionsForm : public QWidget
{
    Q_OBJECT

public:

    OptionsForm();

    void addLanguage( const QString & name, const QVariant & data );
    void setLangPair( const QString & source, const QString & result );
    const QVariant sourceLanguage() const;
    const QVariant resultLanguage() const;

signals:

    void helpClicked();
    void aboutClicked();
    void exitClicked();
    void backClicked();

private:

    int indexByName( QComboBox * comboBox, const QString & name );

private:

    QComboBox * _sourceLanguage;
    QComboBox * _resultLanguage;
};



inline
OptionsForm::OptionsForm()
{
    QVBoxLayout * layout = new QVBoxLayout;
    setLayout( layout );

    QGroupBox * formWidget = new QGroupBox;
    formWidget->setTitle( tr( "translation" ) );

    QFormLayout * formLayout = new QFormLayout;
    formWidget->setLayout( formLayout );

    _sourceLanguage = new QComboBox( formWidget );
    _sourceLanguage->setEditable( false );

    _resultLanguage = new QComboBox( formWidget );
    _resultLanguage->setEditable( false );

    formLayout->addRow( tr( "source" ), _sourceLanguage );
    formLayout->addRow( tr( "result" ), _resultLanguage );

    layout->addWidget( formWidget );

    QGroupBox * menuBox = new QGroupBox;
    menuBox->setTitle( tr( "menu" ) );

    QVBoxLayout * menuLayout = new QVBoxLayout;
    menuBox->setLayout( menuLayout );


    QPushButton * helpButton = new QPushButton;
    helpButton->setText( tr( "help" ) );
    connect( helpButton, SIGNAL( clicked() ),
             this, SIGNAL( helpClicked() ) );
    menuLayout->addWidget( helpButton );

    QPushButton * aboutButton = new QPushButton;
    aboutButton->setText( tr( "about" ) );
    connect( aboutButton, SIGNAL( clicked() ),
             this, SIGNAL( aboutClicked() ) );
    menuLayout->addWidget( aboutButton );

    QPushButton * exitButton = new QPushButton;
    exitButton->setText( tr( "exit" ) );
    connect( exitButton, SIGNAL( clicked() ),
             this, SIGNAL( exitClicked() ) );
    menuLayout->addWidget( exitButton );

    layout->addWidget( menuBox );

    layout->addStretch();

    QPushButton * backButton = new QPushButton;
    backButton->setIcon( QIcon( ":/img/apply.png" ) );
    backButton->setText( tr( "apply" ) );
    connect( backButton, SIGNAL( clicked() ),
             this, SIGNAL( backClicked() ) );
    layout->addWidget( backButton );
}



inline void
OptionsForm::addLanguage( const QString & name, const QVariant & data )
{
    _sourceLanguage->addItem( name, data );
    _resultLanguage->addItem( name, data );
}



inline void
OptionsForm::setLangPair( const QString & source, const QString & result )
{
    int sourceIdx = indexByName( _sourceLanguage, source );
    if( sourceIdx != -1 )
        _sourceLanguage->setCurrentIndex( sourceIdx );

    int resultIdx = indexByName( _resultLanguage, result );
    if( resultIdx != -1 )
        _resultLanguage->setCurrentIndex( resultIdx );
}



inline int
OptionsForm::indexByName( QComboBox * comboBox, const QString & name )
{
    for( int i = 0; i < comboBox->count(); ++i )
    {
        if( comboBox->itemText( i ) == name )
        {
            return i;
        }
    }

    return -1;
}



inline const QVariant
OptionsForm::sourceLanguage() const
{
    int index = _sourceLanguage->currentIndex();
    if( index == -1 )
        return QVariant();

    return _sourceLanguage->itemData( index );
}



inline const QVariant
OptionsForm::resultLanguage() const
{
    int index = _resultLanguage->currentIndex();
    if( index == -1 )
        return QVariant();

    return _resultLanguage->itemData( index );
}



#endif // OPTIONSDIALOG_H
