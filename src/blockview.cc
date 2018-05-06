#include <QDebug>
#include <QGraphicsSceneMouseEvent>

#include "blockview.h"
#include "portview.h"


// copy the data model ptr
BlockView::BlockView(std::shared_ptr<Block> newDataBlock)
{
    DataBlock = newDataBlock;
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

    width = 20;
    height = 5;

}

QRectF BlockView::boundingRect() const
{
    return QRectF(0,0,100,100);
}


void BlockView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);

    QString block_id_text = QString::number(DataBlock->getBlockID());


    painter->fillRect(rec,brush);
    painter->drawText(rec, block_id_text);
}

void BlockView::addPort(Port newPort, bool _isOutputPort)
{
    PortView* portview = new PortView(this);
    portview->setOutput(_isOutputPort);
    portview->setName("Type");
    portview->setParentBlock(this);

    int y = -height / 2 + 5 + 5;

    foreach(QGraphicsItem *port_item, childItems())
    {
        PortView* port = (PortView*)port_item;

        if (port->isOutput())
        {
            port->setPos(width/2 + 5, y);
        }
        else
        {
            port->setPos(-width/2 - 5, y);
        }
        y += 5;
    }
}


void BlockView::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug() << "block pressed";
    update();
    QGraphicsItem::mousePressEvent(mouseEvent);
}

void BlockView::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug() << "block moved";
    update();
    QGraphicsItem::mouseMoveEvent(mouseEvent);
}

void BlockView::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug() << "block released";
    update();
    QGraphicsItem::mouseReleaseEvent(mouseEvent);
}
