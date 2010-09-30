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



#ifndef FRAME_H
#define FRAME_H

#include <QtGui/QMainWindow>
#include <QtGui/QStatusBar>
#include <QtGui/QLabel>
#include <QtGui/QStackedWidget>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtGui/QSystemTrayIcon>



class Frame : public QMainWindow
{
    Q_OBJECT

public:

    Frame( QWidget * parent = 0 );
    void addForm( QWidget * form );
    void setCurrentForm( QWidget * form );
    void setStatus( const QString & statusText );
    void clearStatus();

protected:

    void mousePressEvent( QMouseEvent * event );
    void mouseMoveEvent( QMouseEvent * event );
    void paintEvent( QPaintEvent * event );

private slots:

    void onTrayActivated( QSystemTrayIcon::ActivationReason reason );

private:

    static QRegion roundedRect( const QRect & rect, int r );

private:

    QStackedWidget * _centralWidget;
    QLabel * _status;
    QSystemTrayIcon * _trayIcon;
    QPoint _dragOrigin;
};



inline
Frame::Frame(QWidget *parent)
    : QMainWindow(parent)
{
    _centralWidget = new QStackedWidget( this );
    setCentralWidget( _centralWidget );

    QStatusBar * statusHolder = new QStatusBar( this );

    _status = new QLabel( statusHolder );
    _status->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Ignored );
    statusHolder->addPermanentWidget( _status );

    setStatusBar( statusHolder );

    QIcon mainIcon( ":/img/translate.png" );

    setWindowFlags( Qt::FramelessWindowHint );
    setWindowOpacity( 0.95 );
    setWindowIcon( mainIcon );

    _trayIcon = new QSystemTrayIcon( this );
    _trayIcon->setIcon( mainIcon );
    connect( _trayIcon, SIGNAL( activated(QSystemTrayIcon::ActivationReason) ),
             this, SLOT( onTrayActivated(QSystemTrayIcon::ActivationReason)) );
    _trayIcon->show();

}



inline void
Frame::addForm( QWidget * form )
{
    _centralWidget->addWidget( form );
}



inline void
Frame::setCurrentForm( QWidget * form )
{
    _centralWidget->setCurrentWidget( form );
}



inline void
Frame::setStatus( const QString & statusText )
{
    _status->setText( statusText );
}



inline void
Frame::clearStatus()
{
    _status->clear();
}



inline void
Frame::mousePressEvent( QMouseEvent * event )
{
    if( event->button() == Qt::LeftButton )
    {
        _dragOrigin = event->globalPos() -
                      frameGeometry().topLeft();
        event->accept();
    }
}



inline void
Frame::mouseMoveEvent( QMouseEvent * event )
{
    if( event->buttons() == Qt::LeftButton )
    {
        move( event->globalPos() - _dragOrigin );
        event->accept();
    }
}



inline void
Frame::paintEvent( QPaintEvent * event )
{
    Q_UNUSED( event );

    const int roundness = 4;
    QRect maskRect( rect().adjusted( 1, 1, -1, -1 ) );

    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing );
    painter.setPen( Qt::lightGray );
    painter.drawRoundedRect( maskRect, roundness, roundness );

    QRegion mask = roundedRect( maskRect, roundness );
    setMask( mask );
}



inline void
Frame::onTrayActivated( QSystemTrayIcon::ActivationReason reason )
{
    if( reason == QSystemTrayIcon::Trigger ||
        reason == QSystemTrayIcon::DoubleClick )
    {
        setVisible( ! isVisible() );
    }
}



inline QRegion
Frame::roundedRect(const QRect& rect, int r)
{
    QRegion region;

    // middle and borders
    region += rect.adjusted(r, 0, -r, 0);
    region += rect.adjusted(0, r, 0, -r);

    // top left
    QRect corner(rect.topLeft(), QSize(r*2, r*2));
    region += QRegion(corner, QRegion::Ellipse);

    // top right
    corner.moveTopRight(rect.topRight());
    region += QRegion(corner, QRegion::Ellipse);

    // bottom left
    corner.moveBottomLeft(rect.bottomLeft());
    region += QRegion(corner, QRegion::Ellipse);

    // bottom right
    corner.moveBottomRight(rect.bottomRight());
    region += QRegion(corner, QRegion::Ellipse);

    return region;
}



#endif // WIDGET_H
