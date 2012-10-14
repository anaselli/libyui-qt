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

  File:	      YQSpacing.cc

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/


#include <QLayout>
#include <QtGui/QSpacerItem>
#include "YQSpacing.h"
#include "YQLayoutBox.h"


YQSpacing::YQSpacing( YWidget *		parent,
                      YUIDimension 	dim,
                      bool 		stretchable,
                      YLayoutSize_t 	layoutUnits )
    : YSpacing( parent, dim, stretchable, layoutUnits ), _spacer(0)
{
  QWidget* pParent = (QWidget *) parent->widgetRep();
  // nearest QWidget
  setWidgetRep ( pParent );

  YQLayoutBox *pParentLayout = dynamic_cast<YQLayoutBox*>(parent);
  if (pParentLayout)
  {
    QLayout *pLayout = pParentLayout->layout();
    if ( pLayout )
    {

      //TODO fix layoutUnits
      if ( dim == YD_HORIZ )
      {
        _spacer = new QSpacerItem ( 20, 20, ( stretchable ? QSizePolicy::Expanding : QSizePolicy::Fixed ), QSizePolicy::Fixed );
      }
      else
      {
        _spacer = new QSpacerItem ( 20, 20, QSizePolicy::Fixed, ( stretchable ? QSizePolicy::Expanding : QSizePolicy::Fixed ) );
      }
      pLayout->addItem ( _spacer );
      if ( pParent )
        pParent->show();
    }
  }      
}


YQSpacing::~YQSpacing()
{
  YQLayoutBox *pParentLayout = dynamic_cast<YQLayoutBox*>(parent());
  if (pParentLayout)
  {
    QLayout *pLayout = pParentLayout->layout();
    if ( pLayout )
    {
      pLayout->removeItem(_spacer);
      delete _spacer;
    }
  }
}


void YQSpacing::setSize( int newWidth, int newHeight )
{
  if ( stretchable( YD_HORIZ ) || stretchable( YD_VERT  ) )
  {
    QRect rec;
    rec.setSize(QSize(newWidth,newHeight));
    std::cout << "setSize " << this << " w " << newWidth <<" h " << newHeight 
            << " Rec " << rec.x() << "," << rec.y() << "," << rec.width() << "," << rec.height() << "," << std::endl;
    _spacer->setGeometry(rec);
  }
//   _spacer->invalidate();
  
//   _spacer->changeSize(newWidth,newHeight);
//    _spacer->invalidate();  
//  ((QWidget *)(widgetRep()))->show();
  
}

