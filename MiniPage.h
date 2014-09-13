/**
 *   Copyright (c) 2014 Cyrille Berger <cberger@cberger.net>
 *
 *   This Source Code Form is subject to the terms of the Mozilla Public
 *   License, v. 2.0. If a copy of the MPL was not distributed with this
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef MINIPAGE_H
#define MINIPAGE_H

#include <QQuickItem>

class MiniPage : public QQuickItem
{
  Q_OBJECT
  Q_PROPERTY(int rows READ rows WRITE setRows NOTIFY rowsChanged)
  Q_PROPERTY(int columns READ columns WRITE setColumns NOTIFY columnsChanged)
  Q_PROPERTY(int margin READ margin WRITE setMargin NOTIFY marginChanged)
public:
  explicit MiniPage(QQuickItem *parent = 0);

public:
  int rows() const { return m_rows; }
  void setRows(int _rows) { m_rows = _rows; emit(rowsChanged()); }
  int columns() const { return m_columns; }
  void setColumns(int _columns) { m_columns = _columns; emit(columnsChanged()); }
  int margin() const { return m_margin; }
  void setMargin(int _margin) { m_margin = _margin; emit(marginChanged()); }
signals:
  void rowsChanged();
  void columnsChanged();
  void marginChanged();
private:
  int m_rows, m_columns, m_margin;

};

#endif // MINIPAGE_H
