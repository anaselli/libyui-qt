/*---------------------------------------------------------------------\
|								       |
|		       __   __	  ____ _____ ____		       |
|		       \ \ / /_ _/ ___|_   _|___ \		       |
|			\ V / _` \___ \ | |   __) |		       |
|			 | | (_| |___) || |  / __/		       |
|			 |_|\__,_|____/ |_| |_____|		       |
|								       |
|				core system			       |
|							 (C) SuSE GmbH |
\----------------------------------------------------------------------/

  File:	      YQProgressBar.h

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/


#ifndef YQProgressBar_h
#define YQProgressBar_h

#include <qvbox.h>
#include "YProgressBar.h"


class QString;
class YQWidgetCaption;
class QProgressBar;

class YQProgressBar : public QVBox, public YProgressBar
{
    Q_OBJECT

public:
    /**
     * Constructor.
     **/
    YQProgressBar( YWidget * 		parent,
		   const string &	label,
		   int			maxValue = 100 );
    /**
     * Destructor.
     **/
    virtual ~YQProgressBar();
    
    /**
     * Set the label (the caption above the progress bar).
     *
     * Reimplemented from YProgressBar.
     **/
    virtual void setLabel( const string & label );

    /**
     * Set the current progress value ( <= maxValue() ).
     *
     * Reimplemented from YProgressBar.
     **/
    virtual void setValue( int newValue );
    
    /**
     * Set enabled/disabled state.
     *
     * Reimplemented from YWidget.
     **/
    virtual void setEnabled( bool enabled );

    /**
     * Preferred width of the widget.
     *
     * Reimplemented from YWidget.
     **/
    virtual int preferredWidth();

    /**
     * Preferred height of the widget.
     *
     * Reimplemented from YWidget.
     **/
    virtual int preferredHeight();

    /**
     * Set the new size of the widget.
     *
     * Reimplemented from YWidget.
     **/
    virtual void setSize( int newWidth, int newHeight );

    /**
     * Accept the keyboard focus.
     **/
    virtual bool setKeyboardFocus();

    
protected:

    YQWidgetCaption *	_caption;
    QProgressBar *	_qt_progressbar;
};

#endif // YQProgressBar_h