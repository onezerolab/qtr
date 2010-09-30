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



#ifndef HELPFORM_H
#define HELPFORM_H


#include <QtGui/QWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QTextBrowser>
#include <QtGui/QPushButton>



class HelpForm : public QWidget
{
    Q_OBJECT

public:

    HelpForm();

signals:

    void backClicked();
};



inline
HelpForm::HelpForm()
{
    QVBoxLayout * layout = new QVBoxLayout;
    setLayout( layout );

    QTextBrowser * browser = new QTextBrowser;
    browser->setSource( QUrl( "qrc:/html/manual.html" ) );
    layout->addWidget( browser );

    QPushButton * backButton = new QPushButton;
    backButton->setText( tr( "back" ) );
    connect( backButton, SIGNAL( clicked() ),
             this, SIGNAL( backClicked() ) );
    layout->addWidget( backButton );

}



#endif // HELPFORM_H
