#include "Printer.h"

#include <QQuickWindow>
#include <QPainter>
#include <QPrinter>

#include "MiniPage.h"
#include "PageSize.h"

Printer::Printer(QQuickItem *parent):
  QQuickItem(parent), m_window(0), m_printer(0), m_painter(0), m_mode(GRAB_IMAGE), m_pageSize(new PageSize), m_miniPage(new MiniPage), m_orientation(Portrait)
{
  // By default, QQuickItem does not draw anything. If you subclass
  // QQuickItem to create a visual item, you will need to uncomment the
  // following line and re-implement updatePaintNode()

  // setFlag(ItemHasContents, true);
  connect(m_pageSize, SIGNAL(pageSizeChanged()), this, SLOT(updatePageSize()));
}

Printer::~Printer()
{
  endPrinting();
}

void Printer::startPrinting()
{
  if(not m_window)
  {
    qWarning() << "Window is not set, cannot print!";
    return;
  }
  if(m_printer)
  {
    qWarning() << "Printing is already started!";
    return;
  }
  if(m_filename.isEmpty())
  {
    qWarning() << "No filenames specified";
    return;
  }
  m_printer = new QPrinter;
  m_printer->setFullPage(true);
  m_printer->setOutputFileName(m_filename);
  m_printer->setPageSize(m_pageSize->pageSize());
  m_printer->setOrientation(QPrinter::Orientation(m_orientation));

  // Setup mini pages
  const int miniPageWidth  = m_pageSize->width() / m_miniPage->columns();
  const int miniPageHeight = m_pageSize->height() / m_miniPage->rows();
  const int miniPageMargin = m_miniPage->margin();
  const QMargins miniPageMargins(miniPageMargin, miniPageMargin, miniPageMargin, miniPageMargin);

  for(int r = 0; r < m_miniPage->rows(); ++r)
  {
    for(int c = 0; c < m_miniPage->columns(); ++c)
    {
      QRect rect(c * miniPageWidth, r * miniPageHeight, miniPageWidth, miniPageHeight);
      rect.marginsRemoved(miniPageMargins);
      m_miniPages.append(rect);
    }
  }

  m_painter = new QPainter;
  m_painter->begin(m_printer);
  m_painter->setWindow(0, 0, m_pageSize->width(), m_pageSize->height());
  m_miniPageIndex = 0;
}

void Printer::printWindow()
{
  if(not m_printer)
  {
    qWarning() << "Printing not started";
    return;
  }
  switch (m_mode)
  {
  case GRAB_IMAGE:
    {
      QImage image = m_window->grabWindow();

      QRect pageRect = m_miniPages[m_miniPageIndex];
      QSize targetSize = image.size();
      targetSize.scale(pageRect.width(), pageRect.height(), Qt::KeepAspectRatio);
      QSize trans_size = 0.5 * (pageRect.size() - targetSize);
      QPoint trans(trans_size.width(), trans_size.height());
      m_painter->drawImage(QRectF(trans + pageRect.topLeft(), targetSize), image);
    }
    break;
  default:
    qWarning() << "Unimplemented printing mode.";
    break;
  }
}

void Printer::startNewPage()
{
  if(not m_printer)
  {
    qWarning() << "Printing not started";
    return;
  }
  ++m_miniPageIndex;
  qDebug() << m_miniPageIndex << m_miniPages.size();
  if(m_miniPageIndex >= m_miniPages.size())
  {
    m_miniPageIndex = 0;
    m_printer->newPage();
  }
}

void Printer::endPrinting()
{
  if(m_printer)
  {
    m_painter->end();
    delete m_painter;
    m_painter = 0;
    delete m_printer;
    m_printer = 0;
  }
}

void Printer::updatePageSize()
{
  if(m_printer)
  {
    qDebug() << "updatePageSize" << m_pageSize->width() << " " << m_pageSize->height();
    m_printer->setPageSize(m_pageSize->pageSize());
  }
}
