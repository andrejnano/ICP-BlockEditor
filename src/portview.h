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

    void setCurrentWire(WireView* wire);
    WireView* getCurrentWire();
    BlockView* getParentBlock() const;


};

#endif // PORTVIEW_H
