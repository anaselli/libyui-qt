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

  File:	      YQAlignment.cc

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/


#define YUILogComponent "qt-ui"
#include <yui/YUILog.h>
#include <qpixmap.h>
#include "YQAlignment.h"
#include "YQLayoutBox.h"

using std::string;


YQAlignment::YQAlignment( YWidget *	  	parent,
			  YAlignmentType 	horAlign,
			  YAlignmentType 	vertAlign )
    : QWidget( (QWidget *) parent->widgetRep() )
    , YAlignment( parent, horAlign, vertAlign )
{
    setWidgetRep( this );
        QGridLayout *layout = new QGridLayout();
    setLayout( layout );

    Qt::Alignment align = 0;
    if (horAlign == YAlignBegin)
      align |= Qt::AlignLeft;
    else if (horAlign == YAlignEnd)
      align |= Qt::AlignRight;
    else if (horAlign == YAlignCenter)
      align |= Qt::AlignHCenter;

    if (vertAlign == YAlignBegin)
      align |= Qt::AlignTop;
    else if (vertAlign == YAlignEnd)
      align |= Qt::AlignBottom;
    else if (vertAlign == YAlignCenter)
      align |= Qt::AlignVCenter;
  
    layout->setAlignment(align);
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


YQAlignment::YQAlignment( YWidget *	  	yParent,
			  QWidget *		qParent,
			  YAlignmentType 	horAlign,
			  YAlignmentType 	vertAlign )
    : QWidget( qParent )
    , YAlignment( yParent, horAlign, vertAlign )
{
    setWidgetRep( this );
    
    QGridLayout *layout = new QGridLayout();
    setLayout( layout );

    Qt::Alignment align = 0;
    if (horAlign == YAlignBegin)
      align |= Qt::AlignLeft;
    else if (horAlign == YAlignEnd)
      align |= Qt::AlignRight;
    else if (horAlign == YAlignCenter)
      align |= Qt::AlignHCenter;

    if (vertAlign == YAlignBegin)
      align |= Qt::AlignTop;
    else if (vertAlign == YAlignEnd)
      align |= Qt::AlignBottom;
    else if (vertAlign == YAlignCenter)
      align |= Qt::AlignVCenter;
  
    layout->setAlignment(align);
    
    YQLayoutBox *pParentLayout = dynamic_cast<YQLayoutBox*>(yParent);
    if (pParentLayout)
    {
      QLayout *pLayout = pParentLayout->layout();
      if (pLayout)
      {
        pLayout->addWidget(this);
      }
    }
}

YQAlignment::~YQAlignment()
{
  YQLayoutBox *pParentLayout = dynamic_cast<YQLayoutBox*>(YWidget::parent());
  if (pParentLayout)
  {
    QLayout *pLayout = pParentLayout->layout();
    if (pLayout)
    {
      pLayout->removeWidget(this);
    }
  }
}

void YQAlignment::setEnabled( bool enabled )
{
    QWidget::setEnabled( enabled );
    YWidget::setEnabled( enabled );
}


void YQAlignment::moveChild( YWidget * child, int newX, int newY )
{
    QWidget * qw = (QWidget *) ( child->widgetRep() );
    qw->move( newX, newY );
}


void YQAlignment::setSize( int newWidth, int newHeight )
{
    resize( newWidth, newHeight );
    YAlignment::setSize( newWidth, newHeight );
}


void YQAlignment::setBackgroundPixmap( const std::string & pixmapFileName )
{
    std::string pixmapName = pixmapFileName;

    YAlignment::setBackgroundPixmap( pixmapName );	// Prepend path etc.
    pixmapName = YAlignment::backgroundPixmap();

    if ( pixmapName.empty() )	// Delete any old background pixmap
    {
            QPalette pal = palette();
            pal.setBrush(backgroundRole(), QBrush());
            setPalette(pal);
    }
    else			// Set a new background pixmap
    {
	QPixmap pixmap( pixmapName.c_str() );

	if ( pixmap.isNull() )
	{
	    yuiError() << "Can't load background pixmap \"" << pixmapName << "\"" << std::endl;
	}
	else
	{
            QPalette pal = palette();
            pal.setBrush(backgroundRole(), QBrush(pixmap));
            setPalette(pal);
	}
    }
}

#include "YQAlignment.moc"
