#include <QGraphicsItem>
#include <QPainter>

class pacman : public QGraphicsItem
{
public:
    pacman(int x, int y, int diameter, QColor color, QGraphicsItem *parent = nullptr)
        : QGraphicsItem(parent), m_x(x), m_y(y), m_diameter(diameter), m_color(color), m_direction(0)
    {
        setFlag(QGraphicsItem::ItemIsFocusable, true);
    }

    QRectF boundingRect() const override
    {
        return QRectF(m_x - m_diameter/2, m_y - m_diameter/2, m_diameter, m_diameter);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
    {
        painter->setBrush(m_color);
        painter->setPen(Qt::NoPen);
        painter->drawEllipse(m_x - m_diameter/2, m_y - m_diameter/2, m_diameter, m_diameter);

        painter->setBrush(Qt::black);
        painter->drawEllipse(m_x + m_diameter/4, m_y - m_diameter/4, m_diameter/5, m_diameter/5);
    }

    void move(int direction)
    {
        m_direction = direction;
        switch (direction) {
        case 0: // Move up
            m_y -= m_diameter/10;
            break;
        case 1: // Move down
            m_y += m_diameter/10;
            break;
        case 2: // Move left
            m_x -= m_diameter/10;
            break;
        case 3: // Move right
            m_x += m_diameter/10;
            break;
        }
        update();
    }

    int direction() const { return m_direction; }

private:
    int m_x, m_y, m_diameter, m_direction;
    QColor m_color;
};
