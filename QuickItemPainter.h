#ifndef QUICKITEMPAINTER_H
#define QUICKITEMPAINTER_H

class QQuickItem;
class QQuickWindow;
class QPainter;

class QuickItemPainter
{
public:
  QuickItemPainter(QPainter* _painter, QQuickWindow* _window);
  void paintItem(QQuickItem* _item);
private:
  void paintQuickRectangleItem(QQuickItem* _item);
private:
  QPainter* m_painter;
  QQuickWindow* m_window;
};

#endif // QUICKITEMPAINTER_H
