/**
 *  @file       wireview.cc
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    1.0
 * 
 *  @brief ICP 2018, Project - Block Editor. Wireview class.
 *  
 *  @section Description
 * 
 *  @section Usage
 *  
 */

#include <QGraphicsScene>

#include "wireview.h"
#include "portview.h"

/**
 * @brief WireView constructor
 * @param parent
 */
WireView::WireView(QGraphicsItem *parent) :
    QGraphicsPathItem(parent)
{
    //setSourcePort();
    setPen(QPen(Qt::green, 3));
    SourcePort = 0;
    DestPort = 0;
}

/**
 * @brief Sets the source point of wire
 * @param point
 */
void WireView::setSourcePoint(const QPointF &point)
{
    SourcePoint = point;
}

/**
 * @brief Sets the destination point of wire
 * @param point
 */
void WireView::setDestPoint(const QPointF &point)
{
    DestPoint = point;
}

/**
 * @brief Sets the source port of wire
 * @param point
 */
void WireView::setSourcePort(PortView *port)
{
    SourcePort = port;
}

/**
 * @brief Sets the destination port of wire
 * @param point
 */
void WireView::setDestPort(PortView *port)
{
    DestPort = port;
}

/**
 * @brief Updates both points of the wire from wire's ports
 */
void WireView::updatePoints()
{
    // get point positions from the port positions
    SourcePoint = SourcePort->scenePos();
    DestPoint = DestPort->scenePos();
}

/**
 * @brief Updates the path from the new points
 */
void WireView::updatePath()
{
    QPainterPath path;

    // start pos
    path.moveTo(SourcePoint);

    qreal dx = DestPoint.x() - SourcePoint.x();
    qreal dy = DestPoint.y() - SourcePoint.y();
    QPointF center1(SourcePoint.x() + dx * 0.25, SourcePoint.y() + dy * 0.1);
    QPointF center2(SourcePoint.x() + dx * 0.75, SourcePoint.y() + dy * 0.9);
    path.cubicTo(center1, center2, DestPoint);

    setPath(path);
}

/**
 * @brief Source Portview getter
 */
PortView *WireView::getSourcePort()
{
    return SourcePort;
}

/**
 * @brief Destination Portview getter
 */
PortView *WireView::getDestPort()
{
    return DestPort;
}
