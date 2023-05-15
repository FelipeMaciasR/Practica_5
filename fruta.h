#ifndef FRUTA_H
#define FRUTA_H
#include <QGraphicsItem>
#include <QPainter>

class Fruta: public QGraphicsItem
{
public:
    Fruta();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // FRUTA_H
