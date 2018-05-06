/**
 *  @file       wireview.h
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    1.0
 * 
 *  @brief ICP 2018, Project - Block Editor. Wireview class header.
 *  
 *  @section Description
 * 
 *  @section Usage
 *  
 */

#ifndef WIREVIEW_H
#define WIREVIEW_H

#include <QGraphicsItem>
#include <QGraphicsPathItem>

#include "portview.h"

class WireView : public QGraphicsPathItem
{
private:
    QPointF SourcePoint;
    QPointF DestPoint;
    PortView* SourcePort;
    PortView* DestPort;

public:
    WireView(QGraphicsItem * parent = 0);

    // setters for points
    void setSourcePoint(const QPointF &point);
    void setDestPoint(const QPointF &point);

    // setters for ports
    void setSourcePort(PortView *port);
    void setDestPort(PortView *port);

    // path update
    void updatePoints();
    void updatePath();

    // connected port's getters
    PortView* getSourcePort();
    PortView* getDestPort();

};

#endif // WIREVIEW_H
