#include "QuickItemPainter.h"

#include <QPainter>
#include <QQuickItem>
#include <QQuickWindow>

QuickItemPainter::QuickItemPainter(QPainter* _painter, QQuickWindow* _window) : m_painter(_painter), m_window(_window)
{
}

namespace {
  bool inherits(const QMetaObject* _metaObject, const QString& _name)
  {
    if(_metaObject->className() == _name)
    {
      return true;
    } else if(_metaObject->superClass()) {
      return inherits(_metaObject->superClass(), _name);
    } else {
      return false;
    }
  }
}

void QuickItemPainter::paintQuickRectangleItem(QQuickItem* _item)
{
  // Print rectangle
  const QRect rect = _item->mapRectToScene(_item->boundingRect()).toRect(); // TODO should it be set on the QPainter ?
  const QColor color = _item->property("color").value<QColor>();
  const QObject* border = _item->property("border").value<QObject*>();
  const int border_width = border->property("width").value<int>();
  const QColor border_color = border->property("color").value<QColor>();
  const qreal radius = _item->property("radius").value<qreal>();

  m_painter->setBrush(color);

  if(border_width > 0 and not (border_width == 1 and border_color == QColor(Qt::black))) // FIXME this is wrong, but there is no other clean way to detect if a border is valid or not
  {
    m_painter->setPen(QPen(border_color, border_width));
  } else {
    m_painter->setPen(Qt::NoPen);
  }

  if(radius > 0)
  {
    m_painter->drawRoundedRect(rect, radius, radius);
  } else {
    m_painter->drawRect(rect);
  }

}

void QuickItemPainter::paintQuickTextItem(QQuickItem* _item)
{
  const QRect rect = _item->mapRectToScene(_item->boundingRect()).toRect(); // TODO should it be set on the QPainter ?
  const QFont font = _item->property("font").value<QFont>();
  const QString text = _item->property("text").value<QString>();
  const QColor color = _item->property("color").value<QColor>();
  const int wrapMode = _item->property("wrapMode").value<int>();

  QTextOption textOption;

  textOption.setWrapMode(QTextOption::WrapMode(wrapMode));

  m_painter->setFont(font);
  m_painter->setPen(color);
  m_painter->drawText(rect, text, textOption);
}

void QuickItemPainter::paintItem(QQuickItem* _item)
{
  if(_item->flags().testFlag(QQuickItem::ItemHasContents))
  {
    if(_item->clip())
    {
      m_painter->setClipping(true);
      m_painter->setClipRect(_item->clipRect());
    }
    if(inherits(_item->metaObject(), "QQuickRectangle"))
    {
      paintQuickRectangleItem(_item);
    } else if(inherits(_item->metaObject(), "QQuickText"))
    {
      paintQuickTextItem(_item);
    } else {
      // Fallback
      qWarning() << "No QuickItemPainter::paintItem implementation for " << _item << " fallback to image grab";
      QRect rect = _item->mapRectToScene(_item->boundingRect()).toRect();
      QImage image = m_window->grabWindow();
      m_painter->drawImage(rect.x(), rect.y(), image, rect.x(), rect.y(), rect.width(), rect.height());
    }
  }
  foreach(QQuickItem* child, _item->childItems()) // TODO reorder to take into account z-order
  {
    if(child and child->isVisible())
    {
      m_painter->save();
      paintItem(child);
      m_painter->restore();
    }
  }
}
