#ifndef VISUALBLOCK_H
#define VISUALBLOCK_H

#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>


#include "blocks.h"


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

    void addPort(Port newPort, bool isOutputPort);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
};



#endif // VISUALBLOCK_H
