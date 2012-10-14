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

  File:	      YQFrame.cc

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/


#define YUILogComponent "qt-ui"
#include <yui/YUILog.h>
#include "YQUI.h"
#include "utf8.h"
#include <QDebug>
#include <QLayout>

using std::max;

#include "YQFrame.h"
#include "YQLayoutBox.h"


YQFrame::YQFrame( YWidget * 		parent,
		  const std::string &	initialLabel )
    : QGroupBox( (QWidget *) parent->widgetRep() )
    , YFrame( parent, initialLabel )
{
  setWidgetRep ( this );
  QGroupBox::setTitle( fromUTF8( label() ) );


  QWidget* pParent =(QWidget *) parent->widgetRep();

  YQLayoutBox *pParentLayout = dynamic_cast<YQLayoutBox*>(parent);
  if (pParentLayout)
  {
    QLayout *pLayout = pParentLayout->layout();
    if ( pLayout )
    {
      pLayout->addWidget(this);
      if ( pParent )
      pParent->show();
    }
  }
}


YQFrame::~YQFrame()
{
  YQLayoutBox *pParentLayout = dynamic_cast<YQLayoutBox*>(YWidget::parent());
  if (pParentLayout)
  {
    QLayout *pLayout = pParentLayout->layout();
    if ( pLayout )
    {
      pLayout->removeWidget(this);
    }
  }
}


void YQFrame::setEnabled( bool enabled )
{
    QGroupBox::setEnabled( enabled );
    YWidget::setEnabled( enabled );
}


void
YQFrame::setSize( int newWidth, int newHeight )
{
  resize ( newWidth, newHeight );

  if ( hasChildren() )
  {
    int left, top, right, bottom;
    getContentsMargins ( &left, &top, &right, &bottom );
    int newChildWidth  = newWidth - left - right;
    int newChildHeight = newHeight - bottom - top;

    firstChild()->setSize ( newChildWidth, newChildHeight );

    QWidget * qw = dynamic_cast<QWidget*> ( firstChild() );
    if ( qw )
      qw->move ( left, top );

  }
  QLayout *pLayout = layout();
  if ( pLayout )
  {
    pLayout->activate();
  }
}


void
YQFrame::setLabel( const std::string & newLabel )
{
    YFrame::setLabel( newLabel );
    QGroupBox::setTitle( fromUTF8( label() ) );
}


int YQFrame::preferredWidth()
{
    int preferredWidth = hasChildren() ? firstChild()->preferredWidth() : 0;
    int left, top, right, bottom;
    getContentsMargins( &left, &top, &right, &bottom );

    preferredWidth += left + right;

    if ( minimumSizeHint().width() >  preferredWidth )
	preferredWidth = minimumSizeHint().width();

    return preferredWidth;
}


int YQFrame::preferredHeight()
{
    int preferredHeight = hasChildren() ? firstChild()->preferredHeight() : 0;
    int left, top, right, bottom;
    getContentsMargins( &left, &top, &right, &bottom );

    return preferredHeight + top + left;
}


#include "YQFrame.moc"
