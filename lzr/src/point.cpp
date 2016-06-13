
#include "point.h"
#include "settings.h"


Point::Point(lzr::Point p, Grid* g) : QGraphicsObject(0)
{
    init();
    setPos(p.x, p.y);
    color = QColor(p.r, p.g, p.b, p.i);
    grid = g;
}

Point::Point(QPointF p, QColor c, Grid* g) : QGraphicsObject(0)
{
    init();
    setPos(p);
    color = c;
    grid = g;
}

void Point::init()
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setFlag(QGraphicsItem::ItemIgnoresTransformations);
    setAcceptHoverEvents(true);
    hovered = false;
}

void Point::setColor(const QColor& c)
{
    color = c;
}

QColor Point::getColor() const
{
    return color;
}

lzr::Point Point::to_LZR() const
{
    return lzr::Point(x(),
                      y(),
                      color.red(),
                      color.green(),
                      color.blue(),
                      color.alpha());
}

QRectF Point::boundingRect() const
{
    return QRectF(-POINT_RADIUS, -POINT_RADIUS, POINT_DIAMETER, POINT_DIAMETER);
}


void Point::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(hovered)
    {
        painter->setPen(POINT_HANDLE_COLOR);
        painter->drawEllipse(-POINT_RADIUS, -POINT_RADIUS, POINT_DIAMETER, POINT_DIAMETER);
    }

    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawEllipse(-POINT_INNER_RADIUS, -POINT_INNER_RADIUS, POINT_INNER_DIAMETER, POINT_INNER_DIAMETER);
}


QVariant Point::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(scene() && change == ItemPositionChange)
    {
        // Keep the item inside the scene rect.
        QPointF pos = grid->constrain_and_maybe_snap(value.toPointF());

        //if the point changed, return the changed point
        if(value.toPointF() != pos)
        {
            return pos;
        }
    }
    else if(scene() && change == ItemPositionHasChanged)
    {
        //moving the child should trigger a change in the parent,
        //to redraw the connecting lines
        emit changed();
    }

    //call default handler
    return QGraphicsItem::itemChange(change, value);
}


void Point::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    hovered = true;
    return QGraphicsItem::hoverEnterEvent(event);
}


void Point::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    hovered = false;
    return QGraphicsItem::hoverEnterEvent(event);
}
