#ifndef VISUALBLOCK_H
#define VISUALBLOCK_H

#include <QWidget>

class VisualBlock : public QWidget
{
public:
    VisualBlock();
    void keyPressEvent(QKeyEvent *event);
};


#endif // VISUALBLOCK_H
