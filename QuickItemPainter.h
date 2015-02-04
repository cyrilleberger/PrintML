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
  void setDebugVerbose(bool _debugVerbose) { m_debugVerbose = _debugVerbose; }
private:
  void paintQuickRectangle(QQuickItem* _item);
  void paintQuickText(QQuickItem* _item);
  void paintQuickImage(QQuickItem* _item);
private:
  QPainter* m_painter;
  QQuickWindow* m_window;
  bool m_debugVerbose;
};

#endif // QUICKITEMPAINTER_H
