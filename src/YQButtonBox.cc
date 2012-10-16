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

  File:	      YQButtonBox.cc

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/


#define YUILogComponent "qt-ui"
#include <yui/YUILog.h>
#include "YQButtonBox.h"
#include "YQLayoutBox.h"


YQButtonBox::YQButtonBox( YWidget * parent )
    : QWidget( (QWidget *) parent->widgetRep() )
    , YButtonBox( parent )
{
    setWidgetRep( this );
    YQLayoutBox *pParentLayout = dynamic_cast<YQLayoutBox*>(parent);
    QLayout *pLayout = NULL;
    if (pParentLayout)
    {
      pLayout = pParentLayout->layout();
    }
    else
    {
      QWidget* pParent =(QWidget *) parent->widgetRep();
      if (pParent)
        pLayout = pParent->layout();
    }
    
    if (pLayout)
    {
      pLayout->addWidget(this);
    }
}


YQButtonBox::~YQButtonBox()
{
  YQLayoutBox *pParentLayout = dynamic_cast<YQLayoutBox*> ( YWidget::parent() );
  QLayout *pLayout = NULL;
  if ( pParentLayout )
  {
    pLayout = pParentLayout ->layout();
  }
  else
  {
    QWidget* pParent = ( QWidget * )  YWidget::parent()->widgetRep();
    if ( pParent )
      pLayout = pParent->layout();
  }

  if ( pLayout )
  {
    pLayout->removeWidget ( this );
  }}


void YQButtonBox::setEnabled( bool enabled )
{
    QWidget::setEnabled( enabled );
    YWidget::setEnabled( enabled );
}


void YQButtonBox::setSize( int newWidth, int newHeight )
{
    resize( newWidth, newHeight );
    YButtonBox::setSize( newWidth, newHeight );
}


void YQButtonBox::moveChild( YWidget * child, int newX, int newY )
{
    QWidget * qw = (QWidget *)( child->widgetRep() );
    qw->move( newX, newY );
}


#include "YQButtonBox.moc"
