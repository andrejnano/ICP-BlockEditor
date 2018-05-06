
#include <QGraphicsScene>
#include <QFontMetrics>

#include <QPen>

#include "portview.h"
#include "wireview.h"


QVariant PortView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemScenePositionHasChanged)
    {
        CurrentWire->updatePoints();
        CurrentWire->updatePath();
    }
}

PortView::PortView(QGraphicsItem *parent, QGraphicsScene *scene) :
    QGraphicsPathItem(parent, scene)
{
    TextLabel {new QGraphicsTextItem(this) };

    QPainterPath path;
    path.addEllipse(-5, -5, 10, 10); // small circle
    setPath(path);

    setPen(QPen(Qt::black));
    setBrush(Qt::red);

    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

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
    Type = str;
}

void PortView::setOutput(bool _setOutput)
{
    isOutput = _setOutput;

    // get the text size and create bounding box for it
    QFontMetrics fm(scene()->font());
    QRect r = fm.boundingRect(Type);


    if (isOutput)
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
    return isOutput;
}

bool PortView::isConnected(PortView *next)
{
    if (CurrentWire->SourcePort() == next || CurrentWire->DestPort() == next)
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
