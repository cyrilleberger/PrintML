/**
 *   Copyright (c) 2014 Cyrille Berger <cberger@cberger.net>
 *
 *   This Source Code Form is subject to the terms of the Mozilla Public
 *   License, v. 2.0. If a copy of the MPL was not distributed with this
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "Printer.h"

#include <QQuickWindow>
#include <QPainter>
#include <QPrinter>

#include "MiniPage.h"
#include "PageSize.h"
#include "QuickItemPainter.h"

Printer::Printer(QQuickItem *parent):
  QQuickItem(parent), m_window(0), m_printer(0), m_painter(0), m_mode(GRAB_IMAGE), m_pageSize(new PageSize), m_miniPage(new MiniPage), m_orientation(Portrait), m_itemPainter(0)
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

void Printer::beginPrinting()
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
//  m_printer->setFullPage(true); // TODO: reintroduce as an option
  m_printer->setOutputFileName(m_filename);
  m_printer->setPageSize(m_pageSize->pageSize());
  m_printer->setOrientation(QPrinter::Orientation(m_orientation));

  // Setup mini pages
  const int miniPageWidth  = m_printer->pageRect().width() / m_miniPage->columns();
  const int miniPageHeight = m_printer->pageRect().height() / m_miniPage->rows();
  const int miniPageMargin = m_miniPage->margin();
  const QMargins miniPageMargins(miniPageMargin, miniPageMargin, miniPageMargin, miniPageMargin);

  for(int r = 0; r < m_miniPage->rows(); ++r)
  {
    for(int c = 0; c < m_miniPage->columns(); ++c)
    {
      QRect rect(c * miniPageWidth + m_printer->pageRect().x(), r * miniPageHeight + m_printer->pageRect().y(), miniPageWidth, miniPageHeight);
      m_miniPages.append(rect.marginsRemoved(miniPageMargins));
    }
  }

  m_painter = new QPainter;
  m_painter->begin(m_printer);
  m_miniPageIndex = 0;

  m_itemPainter = new QuickItemPainter(m_painter, m_window);
}

void Printer::printWindow()
{
  if(not m_printer)
  {
    qWarning() << "Printing not started";
    return;
  }
  QRect pageRect = m_miniPages[m_miniPageIndex];
  QSize targetSize = m_window->size();
  targetSize.scale(pageRect.width(), pageRect.height(), Qt::KeepAspectRatio);
  QSize trans_size = 0.5 * (pageRect.size() - targetSize);
  QPoint trans(trans_size.width(), trans_size.height());
  m_painter->save();
  QRect viewport = QRect(trans + pageRect.topLeft(), targetSize);
  m_painter->setViewport(viewport);
  m_painter->setWindow(0, 0, m_window->width(), m_window->height());

  switch (m_mode)
  {
  case GRAB_IMAGE:
    {
      QImage image = m_window->grabWindow();
      Q_ASSERT(image.size() == m_window->size());
      m_painter->drawImage(0, 0, image);
    }
    break;
  case EFFICIENT:
    {
      m_itemPainter->paintItem(m_window->contentItem());

      break;
    }
  default:
    qWarning() << "Unimplemented printing mode.";
    break;
  }
  m_painter->restore();
}

void Printer::newPage()
{
  if(not m_printer)
  {
    qWarning() << "Printing not started";
    return;
  }
  ++m_miniPageIndex;
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
    m_printer->setPageSize(m_pageSize->pageSize());
  }
}
