/**
 *  @file       blockview.cc
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    1.0
 * 
 *  @brief ICP 2018, Project - Block Editor. Blockview class.
 *  
 *  @section Description 
 * 
 */

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsDropShadowEffect>

#include "blockview.h"
#include "portview.h"


// copy the data model ptr
BlockView::BlockView(std::shared_ptr<Block> newDataBlock)
{
    DataBlock = newDataBlock;
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

    width = 100;
    height = 200;

}

std::shared_ptr<Block> BlockView::getDataBlock()
{
    return DataBlock;
}


QRectF BlockView::boundingRect() const
{
    return QRectF(0,0,100,200);
}


void BlockView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // block rounded rectangle
    QRectF rec = boundingRect();
    QPainterPath path;
    path.addRoundedRect(rec, 5, 5);
    QPen border(Qt::lightGray, 1);
    painter->setPen(border);
    painter->fillPath(path, QColor(255,255,255));
    painter->drawPath(path);

    // block id and type
    QString block_id = QString::number(DataBlock->getBlockID());
    QString block_type = QString::fromStdString(DataBlock->getStringType());

    QPen pen;
    QColor text_color(QColor(9, 12, 29));
    pen.setColor(text_color);
    painter->setFont(QFont("Helvetica", 12, QFont::Bold));
    painter->setPen(pen);

    painter->drawText(0, 30, rec.width(), rec.height(), Qt::AlignTop | Qt::AlignHCenter, block_id);
    painter->drawText(rec, Qt::AlignVCenter | Qt::AlignHCenter, block_type);
}

PortView* BlockView::addPort(Port newPort, bool _isOutputPort)
{
    PortView* portview = new PortView(this);
    portview->setOutput(_isOutputPort);
    portview->setId(newPort.getId());
    portview->setName("Type");
    portview->setParentBlock(this);

    // start with slight margin from top
    int y = height / 4;

    foreach(QGraphicsItem *item, childItems())
    {
        PortView* port = qgraphicsitem_cast<PortView*>(item);
        if (!port) continue;

        if (port->isOutput())
        {
            port->setPos(width, y);
        }
        else
        {
            port->setPos(0, y);
        }
        y += 20;
    }

    return portview;
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
