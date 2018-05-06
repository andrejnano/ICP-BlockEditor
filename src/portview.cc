
#include <QGraphicsScene>
#include <QFontMetrics>

#include <QPen>

#include "portview.h"
#include "wireview.h"



PortView::PortView(QGraphicsItem *parent) :
    QGraphicsPathItem(parent)
{
    CurrentWire = nullptr;
    TextLabel = new QGraphicsTextItem(this);

    // circle path
    QPainterPath path;
    path.addEllipse(-5, -5, 10, 10);
    setPath(path);

    setPen(QPen(Qt::black));
    setBrush(Qt::red);

    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}


// change signal
QVariant PortView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (!CurrentWire)
        return value;

    if (change == ItemScenePositionHasChanged)
    {
        CurrentWire->updatePoints();
        CurrentWire->updatePath();
    }
    return value;
}


PortView::~PortView()
{
    delete CurrentWire;
}

void PortView::setParentBlock(BlockView *block)
{
    ParentBlock = block;
}

void PortView::setName(const QString &str)
{
    Name = str;
}

// set port as output port
void PortView::setOutput(bool _setOutput)
{
    isOutputPort = _setOutput;

    if (isOutputPort)
    {
        TextLabel->setPos(-5 - 2 - TextLabel->boundingRect().width(), TextLabel->boundingRect().height()/2);
    }
    else
    {
        TextLabel->setPos(5 + 2, - TextLabel->boundingRect().height()/2);
    }

}

bool PortView::isOutput()
{
    return isOutputPort;
}

bool PortView::isConnected(PortView *next)
{
    if (CurrentWire->getSourcePort() == next || CurrentWire->getDestPort() == next)
        return true;
    else
        return false;
}

WireView *PortView::getCurrentWire()
{
    return CurrentWire;
}

BlockView *PortView::getParentBlock() const
{
    return ParentBlock;
}


void PortView::setCurrentWire(WireView* wire)
{
    CurrentWire = wire;
}
