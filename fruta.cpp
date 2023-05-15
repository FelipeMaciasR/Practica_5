#include "fruta.h"

Fruta::Fruta()
{

}

QRectF Fruta::boundingRect() const
{
    return QRectF(-5,-5,5,5);
}

void Fruta::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::darkRed);
    painter->drawEllipse(boundingRect());
}


