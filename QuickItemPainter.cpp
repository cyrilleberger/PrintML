#include "QuickItemPainter.h"

#include <QPainter>
#include <QQuickItem>
#include <QQuickWindow>

QuickItemPainter::QuickItemPainter(QPainter* _painter, QQuickWindow* _window) : m_painter(_painter), m_window(_window)
{
}

void QuickItemPainter::paintItem(QQuickItem* _item)
{
  if(_item->flags().testFlag(QQuickItem::ItemHasContents))
  {
    qDebug() << _item->objectName() << _item->metaObject()->className();
    if(false)
    {

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
