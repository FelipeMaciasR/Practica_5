#include "bola.h"

Bola::Bola()
{

}

QRectF Bola::boundingRect() const
{
    return QRectF(-5,-5,10,10);
}

void Bola::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::darkGreen);
    painter->drawEllipse(boundingRect());
}
