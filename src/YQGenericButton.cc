/*
  Copyright (C) 2000-2012 Novell, Inc
  This library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2.1 of the
  License, or (at your option) version 3.0 of the License. This library
  is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
  License for more details. You should have received a copy of the GNU
  Lesser General Public License along with this library; if not, write
  to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
  Floor, Boston, MA 02110-1301 USA
*/


/*-/

  File:	      YQGenericButton.cc

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/

#include <QLayout>

#include <qpushbutton.h>
#include <qsize.h>
#include <qevent.h>
#include <qpixmap.h>
#include <qevent.h>
#define YUILogComponent "qt-ui"
#include <yui/YUILog.h>

#include "utf8.h"
#include "YQUI.h"
#include "YQApplication.h"
#include <yui/YEvent.h>
#include "YQGenericButton.h"
#include "YQDialog.h"
#include "YQLayoutBox.h"


YQGenericButton::YQGenericButton( YWidget *		parent,
				  const std::string &	label )
    : QPushButton( (QWidget *) parent->widgetRep() )
    , YPushButton( parent, label )
    , _dialog( 0 )
{
    setWidgetRep( 0 );
    QWidget* pParent =(QWidget *) parent->widgetRep();
    YQLayoutBox *pParentLayout = dynamic_cast<YQLayoutBox*>(parent);
    if (pParentLayout)
    {
      QLayout *pLayout = pParentLayout->layout();
      if (pLayout)
      {
//         std::cout << "pParent " << parent << " _pLayout " << pParentLayout << std::endl;

        pLayout->addWidget(this);
        pLayout->activate();
      }
    }
    else
    {
      if (pParent && pParent->layout())
      {
        pParent->layout()->addWidget(this);
      }
    }
    
    if (pParent)
    {
      pParent->update();
    }
}


YQGenericButton::~YQGenericButton()
{
  if ( _dialog ) // If we don't have one any more, don't bother
  {
    if ( _dialog->focusButton() == this )
      _dialog->losingFocus ( this );

    if ( _dialog->defaultButton() == this )
      _dialog->setDefaultButton ( 0 );
  }
  
  YQLayoutBox *pParentLayout = dynamic_cast<YQLayoutBox*> ( YWidget::parent() );
  if ( pParentLayout )
  {
    QLayout *pLayout = pParentLayout->layout();
    if ( pLayout )
    {
      pLayout->removeWidget( this );
      pLayout->activate();
    }
  }
  else
  {
     QWidget* pParent =(QWidget *)  YWidget::parent()->widgetRep();
     if (pParent && pParent->layout())
      pParent->layout()->removeWidget(this);
  }
}


void YQGenericButton::forgetDialog()
{
   _dialog = 0;
}


YQDialog *
YQGenericButton::dialog()
{
    if ( ! _dialog )
    {
	YDialog * yDialog = findDialog();

	if ( yDialog )
	    _dialog = dynamic_cast<YQDialog *> (yDialog);

	YUI_CHECK_PTR( _dialog );
    }

    return _dialog;
}


void YQGenericButton::setEnabled( bool enabled )
{
    QPushButton::setEnabled( enabled );

    YWidget::setEnabled( enabled );
}


bool YQGenericButton::isEnabled() const
{
    return QPushButton::isEnabled();
}


void YQGenericButton::setIcon( const std::string & iconName )
{
   QString qIconName = fromUTF8( iconName );

    if ( qIconName.isEmpty() )
    {
	QPushButton::setIcon( QIcon() );
	return;
    }

    // Search for the icon - FaTE #306356
    qIconName =  fromUTF8( YQUI::yqApp()->iconLoader()->findIcon( iconName ) );
    QPixmap icon( qIconName );

    if ( icon.isNull() )
	yuiWarning() << "Can't load icon \"" << qIconName << "\"" << std::endl;
    else
	QPushButton::setIcon( icon );
}


void YQGenericButton::setLabel( const QString & label )
{
  QPushButton::setText( label );
  YPushButton::setLabel( toUTF8( label ) );
}


void YQGenericButton::setLabel( const std::string & label )
{
  QPushButton::setText( fromUTF8( label ) );
  YPushButton::setLabel( label );
}


void YQGenericButton::showAsDefault( bool show )
{
  QPushButton::setAutoDefault( !show );
  QPushButton::setDefault( show );
  QPushButton::update();
}


bool YQGenericButton::isShownAsDefault() const
{
  return QPushButton::isDefault();
}


QString
YQGenericButton::text() const
{
    return QPushButton::text();
}


void YQGenericButton::activate()
{
  QPushButton::animateClick();
}


bool YQGenericButton::eventFilter( QObject * obj, QEvent * event )
{
  if ( event )
  {
      if ( event->type() == QEvent::FocusIn )
      {
          dialog()->gettingFocus( this );
          return false;	// event processed?
      }
      else if ( event->type() == QEvent::FocusOut )
      {
          dialog()->losingFocus( this );
          return false;	// event processed?
      }
      else if ( event->type() == QEvent::MouseButtonRelease )
      {
          QMouseEvent * mouseEvent = dynamic_cast<QMouseEvent *> (event);

          if ( mouseEvent && mouseEvent->button() == Qt::RightButton )
          {
              yuiMilestone() << "Right click on button detected" << std::endl;
              YQUI::yqApp()->maybeLeftHandedUser();
          }
      }
  }


  return QObject::eventFilter( obj, event );
}


bool YQGenericButton::setKeyboardFocus()
{
  dialog()->gettingFocus( this );
  QPushButton::setFocus();

  return true;
}


#include "YQGenericButton.moc"

