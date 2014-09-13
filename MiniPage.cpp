/**
 *   Copyright (c) 2014 Cyrille Berger <cberger@cberger.net>
 *
 *   This Source Code Form is subject to the terms of the Mozilla Public
 *   License, v. 2.0. If a copy of the MPL was not distributed with this
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "MiniPage.h"

MiniPage::MiniPage(QQuickItem *parent) :
  QQuickItem(parent), m_rows(1), m_columns(1), m_margin(0)
{
}
