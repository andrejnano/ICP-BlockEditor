#ifndef WIREVIEW_H
#define WIREVIEW_H

#include <QGraphicsItem>

#include "portview.h"

class WireView : public QGraphicsPathItem
{
private:
    QPointF SourcePoint;
    QPointF DestPoint;
    PortView* SourcePort;
    PortView* DestPort;

public:
    WireView(QGraphicsItem* parent = 0, QGraphicsScene *scene = 0);

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
