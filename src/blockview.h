/**
 *  @file       blockview.h
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    1.0
 * 
 *  @brief ICP 2018, Project - Block Editor. Blockview class header.
 *  
 *  @section Description 
 * 
 */

#ifndef VISUALBLOCK_H
#define VISUALBLOCK_H

#include <memory>

#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>


#include "blocks.h"
#include "portview.h"


class BlockView : public QGraphicsItem
{
private:
    std::shared_ptr<Block> DataBlock; // data model that is represented
    int width;
    int height;

public:
    BlockView(std::shared_ptr<Block> newDataBlock);
    
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    std::shared_ptr<Block> getDataBlock();
    PortView* addPort(Port newPort, bool isOutputPort);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
};



#endif // VISUALBLOCK_H
