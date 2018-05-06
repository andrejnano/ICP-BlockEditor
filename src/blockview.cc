#include <QDebug>
#include <QGraphicsWidget>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsScene>
#include <QObject>

#include "blockview.h"
#include "portview.h"


/**
 * @brief BlockView constructor
 * @param newDataBlock data model of the block
 */
BlockView::BlockView(std::shared_ptr<Block> newDataBlock)
{
    DataBlock = newDataBlock;
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

    width = 100;
    height = 200;
}

/**
 * @brief data model getter
 * @return pointer to the data block
 */
std::shared_ptr<Block> BlockView::getDataBlock()
{
    return DataBlock;
}


/**
 * @brief BlockView::boundingRect
 * @return
 */
QRectF BlockView::boundingRect() const
{
    return QRectF(0,0,100,200);
}

/**
 * @brief BlockView::paint
 * @param painter
 * @param option
 * @param widget
 */
void BlockView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED( option );
    Q_UNUSED( widget );

    // block rounded rectangle
    QRectF rec = boundingRect();
    QPainterPath path;
    path.addRoundedRect(rec, 5, 5);
    QPen border(Qt::lightGray, 1);
    painter->setPen(border);

    if (Selected)
    {
        painter->fillPath(path, QColor(200,250,200));
    }
    else
    {
        painter->fillPath(path, QColor(255,255,255));
    }
    painter->drawPath(path);

    // block id and type
    QString block_id = QString::number(DataBlock->getBlockID());
    QString block_type = QString::fromStdString(DataBlock->getStringType());

    // set text style
    QPen pen;
    QColor text_color(QColor(9, 12, 29));
    pen.setColor(text_color);
    painter->setFont(QFont("Helvetica", 14, QFont::Bold));
    painter->setPen(pen);

    // draw the ID and Operation type name
    painter->drawText(0, 30, rec.width(), rec.height(), Qt::AlignTop | Qt::AlignHCenter, block_id);
    painter->drawText(rec, Qt::AlignVCenter | Qt::AlignHCenter, block_type);
}

/**
 * @brief Add port to the block view
 * @param newPort data model of the port
 * @param _isOutputPort flag setting [output/input] type of port
 * @return
 */
PortView* BlockView::addPort(Port newPort, bool _isOutputPort)
{
    PortView* portview = new PortView(this);
    portview->setOutput(_isOutputPort);
    portview->setId(newPort.getId());
    portview->setName("Type");
    portview->setParentBlock(this);

    // start with slight margin from top
    int y = height / 4;

    // display ports under each other and on opposite sides
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

/**
 * @brief Select this block
 */
void BlockView::select()
{
    Selected = true;
    update();
}

bool BlockView::isSelected() const
{
    return Selected;
}

/**
 * @brief Deselect this block
 */
void BlockView::deselect()
{
    Selected = false;
    update();
}

/**
 * @brief handle BlockView::mousePressEvent, select this item and deselect all others
 * @param mouseEvent
 */
void BlockView::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug() << "block pressed";

    // get the scene the block is in
    auto parentScene = scene();

    // deselect all the blocks
    for (QGraphicsItem *item : parentScene->items())
    {
        BlockView* blockitem = qgraphicsitem_cast<BlockView*>(item);
        if (!blockitem) continue;

        blockitem->deselect();
    }

    // select this oen
    select();

    QGraphicsItem::mousePressEvent(mouseEvent);
}

//void BlockView::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
//{
//    qDebug() << "block moved";
//    update();
//    QGraphicsItem::mouseMoveEvent(mouseEvent);
//}

void BlockView::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug() << "block released";
    update();
    QGraphicsItem::mouseReleaseEvent(mouseEvent);
}
