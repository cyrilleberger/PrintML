/**
 *   Copyright (c) 2014 Cyrille Berger <cberger@cberger.net>
 *
 *   This Source Code Form is subject to the terms of the Mozilla Public
 *   License, v. 2.0. If a copy of the MPL was not distributed with this
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

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


