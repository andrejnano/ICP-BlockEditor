#include "wireview.h"


WireView::WireView(QGraphicsItem *parent, QGraphicsScene *scene) :
    QGraphicsPathItem(parent, scene)
{
    setSourcePort();
    setPen(QPen(Qt::green, 3));
    SourcePort = 0;
    DestPort = 0;
}

inline void WireView::setSourcePoint(const QPointF &point)
{
    SourcePoint = point;
}

inline void WireView::setDestPoint(const QPointF &point)
{
    DestPoint = point;
}

inline void WireView::setSourcePort(PortView *port)
{
    SourcePort = port;
}

void WireView::setDestPort(PortView *port)
{
    DestPort = port;
}

void WireView::updatePoints()
{
    // get point positions from the port positions
    SourcePoint = SourcePort->scenePos();
    DestPoint = DestPort->scenePos();
}

void WireView::updatePath()
{
    QPainterPath path;

    // start pos
    path.moveTo(SourcePoint);

    qreal dx = DestPoint.x() - SourcePoint.x();
    qreal dy = DestPoint.y() - SourcePoint.y();

    QPointF ctr1(SourcePoint.x() + dx * 0.25, SourcePoint.y() + dy * 0.1);
    QPointF ctr2(SourcePoint.x() + dx * 0.75, SourcePoint.y() + dy * 0.9);

    path.cubicTo(ctr1, ctr2, DestPoint);

    setPath(path);
}

PortView *WireView::getSourcePort()
{
    return SourcePort;
}

PortView *WireView::getDestPort()
{
    return DestPort;
}
