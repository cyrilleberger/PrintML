#ifndef PRINTER_H
#define PRINTER_H

#include <QQuickItem>

class QPrinter;

class MiniPage;
class PageSize;

class Printer : public QQuickItem
{
public:
  enum Mode {
    GRAB_IMAGE, //< Print items by taking "screenshot", most accurate solution, but not efficient for PDF
    EFFICIENT   //< Efficient printing of items, but might not be accurate
  };
  Q_ENUMS(Mode)

private:
  Q_OBJECT
  Q_DISABLE_COPY(Printer)
  Q_PROPERTY(QQuickWindow* window READ window WRITE setWindow NOTIFY windowChanged)
  Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged)
  Q_PROPERTY(Mode mode READ mode WRITE setMode NOTIFY modeChanged)
  Q_PROPERTY(PageSize* pageSize READ pageSize)
  Q_PROPERTY(MiniPage* miniPage READ miniPage)
public:
  Printer(QQuickItem *parent = 0);
  ~Printer();
public:
  Q_INVOKABLE void startPrinting();
  Q_INVOKABLE void startNewPage();
  Q_INVOKABLE void printWindow();
  Q_INVOKABLE void endPrinting();
public:
  QQuickWindow* window() const { return m_window; }
  void setWindow(QQuickWindow* _window) { m_window = _window; emit(windowChanged()); }
  QString filename() const { return m_filename; }
  void setFilename(const QString& _filename) { m_filename = _filename; emit(filenameChanged()); }
  Mode mode() const { return m_mode; }
  void setMode(Mode _mode) { m_mode = _mode; emit(modeChanged()); }
  PageSize* pageSize() const { return m_pageSize; }
  MiniPage* miniPage() const { return m_miniPage; }
signals:
  void windowChanged();
  void filenameChanged();
  void modeChanged();
private slots:
  void updatePageSize();
private:
  QQuickWindow* m_window;
  QPrinter*     m_printer;
  QPainter*     m_painter;
  QString       m_filename;
  Mode          m_mode;
  PageSize*     m_pageSize;
  MiniPage*     m_miniPage;
  QList<QRect>  m_miniPages;
  int           m_miniPageIndex;
};

#endif // PRINTER_H

