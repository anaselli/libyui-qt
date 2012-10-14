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

  File:	      YQPushButton.cc

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/


#include <qpushbutton.h>
#include <qsize.h>
#include <QLayout>

#define YUILogComponent "qt-ui"
#include <yui/YUILog.h>

#include "utf8.h"
#include "YQUI.h"
#include <yui/YEvent.h>
#include "YQPushButton.h"
#include "YQLayoutBox.h"


YQPushButton::YQPushButton( YWidget *		parent,
			    const std::string &	label )
    : YQGenericButton( parent, label )
{
    setWidgetRep( this );

    // fromUTF8( label ) ?
    YQGenericButton::setLabel(label);

    connect( this, SIGNAL( clicked() ),
            this,   SLOT  ( hit()     ) );
    
    YQLayoutBox *pParentLayout = dynamic_cast<YQLayoutBox*>(parent);
    if (pParentLayout)
    {
      QLayout *pLayout = pParentLayout->layout();
      if (pLayout)
      {
          pLayout->activate();            
      }
    }
    this->show();
}


YQPushButton::~YQPushButton()
{
}


int YQPushButton::preferredWidth()
{
    return 2 * YQButtonBorder + qPushButton()->sizeHint().width();
}


int YQPushButton::preferredHeight()
{
    return 2 * YQButtonBorder + qPushButton()->sizeHint().height();
}


void YQPushButton::setSize( int newWidth, int newHeight )
{
    QPushButton::resize( newWidth  - 2 * YQButtonBorder,
                           newHeight - 2 * YQButtonBorder );
    resize( newWidth, newHeight );
    
    YQLayoutBox *pParentLayout = dynamic_cast<YQLayoutBox*>(YWidget::parent());
    if (pParentLayout)
    {
      QLayout *pLayout = pParentLayout->layout();
      if (pLayout)
      {
          pLayout->activate();        
      }
    }
}


void YQPushButton::hit()
{
    YQUI::ui()->sendEvent( new YWidgetEvent( this, YEvent::Activated ) );
}


#include "YQPushButton.moc"
