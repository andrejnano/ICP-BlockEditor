#include "visualblock.h"
#include <QDebug>

void VisualBlock::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "VisualBlock known that key was pressed";
}
