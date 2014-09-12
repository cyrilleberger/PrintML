#include "PageSize.h"

PageSize::PageSize(QQuickItem *parent) :
  QQuickItem(parent), m_unit(Point), m_pageSize(QPageSize::A4)
{
}

void PageSize::setWidth(qreal _width)
{
  m_pageSize = QPageSize(QSizeF(_width, height()), QPageSize::Unit(m_unit));
  emit(pageSizeChanged());
}

void PageSize::setHeight(qreal _height)
{
  m_pageSize = QPageSize(QSizeF(width(), _height), QPageSize::Unit(m_unit));
  emit(pageSizeChanged());
}

void PageSize::setPageSizeId(PageSizeId _id)
{
  m_pageSize = QPageSize(QPageSize::PageSizeId(_id));
  emit(pageSizeChanged());
}


