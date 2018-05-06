/**
 *  @file       portview.h
 *  @authors    Andrej Nano (xnanoa00), Stanislav Mechl (xmechl00)
 *  @date       2018-05-05
 *  @version    1.0
 * 
 *  @brief ICP 2018, Project - Block Editor. Portview class header.
 *  
 *  @section Description
 * 
 *  @section Usage
 *  
 */

#ifndef PORTVIEW_H
#define PORTVIEW_H

#include <QGraphicsItem>
#include <QGraphicsPathItem>
#include <QVariant>

#include "blocks.h"

class BlockView;
class WireView;


class PortView : public QGraphicsPathItem
{
private:
    QString Name;
    unsigned Id;
    BlockView* ParentBlock;
    WireView* CurrentWire;
    QGraphicsTextItem *TextLabel;
    bool isOutputPort;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

public:
    PortView(QGraphicsItem * parent = 0);
    ~PortView();

    void setParentBlock(BlockView* block);
    void setName(const QString &str);
    void setOutput(bool _setOutput);

    bool isOutput();
    bool isConnected(PortView *next);

    //void addPort(Port newPort, bool _isOutputPort);

    void setId(unsigned id);
    void setCurrentWire(WireView* wire);

    unsigned getId();
    WireView* getCurrentWire();
    BlockView* getParentBlock() const;


};

#endif // PORTVIEW_H
