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

  File:	      YQLayoutBox.cc

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/

#include <QVBoxLayout>
#include <QHBoxLayout>

#define YUILogComponent "qt-ui"
#include <yui/YUILog.h>
#include "YQLayoutBox.h"

#include <QtDebug>


YQLayoutBox::YQLayoutBox( YWidget* parent,
                          YUIDimension  dimension )
    : YLayoutBox( parent, dimension ), _pLayout(0)
{
  QWidget* pParent = (QWidget *) parent->widgetRep();
  
  if (dimension == YD_VERT)
  {
    _pLayout = new QVBoxLayout;
  }
  else
  {
    _pLayout = new QHBoxLayout;
  }
  
  YQLayoutBox *pParentLayout = dynamic_cast<YQLayoutBox*>(parent);
  if (pParentLayout)
  {
    QLayout* pLayout= pParentLayout->layout();
    // parent is itself a layout it should have been already added to parent widget
    QVBoxLayout *pVBoxLayout = dynamic_cast<QVBoxLayout*>(pLayout);
    if (pVBoxLayout)
    {
      pVBoxLayout->addLayout(_pLayout);
    }
    else
    {
      QHBoxLayout *pHBoxLayout = dynamic_cast<QHBoxLayout*>(pLayout);
      if (pHBoxLayout)
      {
        pHBoxLayout->addLayout(_pLayout);
      }
    }
    if (pParent)
    {
      // just to assign a QWidget it shouldn't be needed
      setWidgetRep(pParent);
      pParent->show();
    }
    _pLayout->activate();
    
  }
  else
  {    
    if (pParent)
    {
//       std::cout << "pParent " << parent << " setLayout(_pLayout)" << this << std::endl;
      // this is not a QWidget
      setWidgetRep(pParent);
      pParent->setLayout(_pLayout);
      _pLayout->activate();
      pParent->show();
    }
  }
}


YQLayoutBox::~YQLayoutBox()
{
  YQLayoutBox *pParentLayout = dynamic_cast<YQLayoutBox*>(parent());
  if (pParentLayout)
  {
    QLayout *pLayout = pParentLayout->layout();
    if ( pLayout )
    {
      pLayout->removeItem(_pLayout);
    }
  }

  delete _pLayout;
}


void YQLayoutBox::setEnabled( bool enabled )
{
    YWidget::setEnabled( enabled );
}


void YQLayoutBox::setSize( int newWidth, int newHeight )
{
  YLayoutBox::setSize( newWidth, newHeight );
  QRect rec;
  YQLayoutBox *pParentLayout = dynamic_cast<YQLayoutBox*>(parent());
  if (pParentLayout)
  {
    rec = _pLayout->geometry();
  }
  else
  {
    rec = ((QWidget *)(widgetRep()))->geometry();
  }
  rec.setSize(QSize(newWidth,newHeight));
//   std::cout << "setSize " << this << " w " << newWidth <<" h " << newHeight 
//             << " Rec " << rec.x() << "," << rec.y() << "," << rec.width() << "," << rec.height() << "," << std::endl;
  _pLayout->setGeometry(rec);
  _pLayout->update();
  
//   ((QWidget *)(widgetRep()))->update();
}


void YQLayoutBox::moveChild( YWidget * child, int newX, int newY )
{  
//   std::cout << "moveChild " << this << " child " << child <<" to (x,y) (" << newX << "," << newY <<")" << std::endl;

  QWidget * qw = dynamic_cast<QWidget*>(child);
  if (qw)
    qw->move( newX, newY );
  _pLayout->activate();
}

QLayout* YQLayoutBox::layout()
{
  return _pLayout;
}

