#ifndef PORTVIEW_H
#define PORTVIEW_H

#include <QGraphicsItem>
#include <QVariant>

#include "blocks.h"

class BlockView;
class WireView;


class PortView : public QGraphicsPathItem
{
private:
    QString Type;
    BlockView* ParentBlock;
    WireView* CurrentWire;
    QGraphicsTextItem *TextLabel;
    bool isOutputPort;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

public:
    PortView(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    ~PortView();

    void setParentBlock(BlockView* block);
    void setName(const QString &str);
    void setOutput(bool _setOutput);

    bool isOutput();
    bool isConnected();

    void addPort(Port newPort, bool _isOutputPort);

    WireView* getCurrentWire();
    BlockView* getParentBlock() const;


};

#endif // PORTVIEW_H
