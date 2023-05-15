#ifndef BOLA_H
#define BOLA_H
#include <QGraphicsItem>
#include <QPainter>


class Bola: public QGraphicsItem
{
public:
    Bola();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // BOLA_H
