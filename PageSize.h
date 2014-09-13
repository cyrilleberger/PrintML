/**
 *   Copyright (c) 2014 Cyrille Berger <cberger@cberger.net>
 *
 *   This Source Code Form is subject to the terms of the Mozilla Public
 *   License, v. 2.0. If a copy of the MPL was not distributed with this
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef PAGESIZE_H
#define PAGESIZE_H

#include <QQuickItem>
#include <QPageSize>

class PageSize : public QQuickItem
{
public:
  enum PageSizeId {
      // Existing Qt sizes
      A4,
      B5,
      Letter,
      Legal,
      Executive,
      A0,
      A1,
      A2,
      A3,
      A5,
      A6,
      A7,
      A8,
      A9,
      B0,
      B1,
      B10,
      B2,
      B3,
      B4,
      B6,
      B7,
      B8,
      B9,
      C5E,
      Comm10E,
      DLE,
      Folio,
      Ledger,
      Tabloid,
      Custom,

      // New values derived from PPD standard
      A10,
      A3Extra,
      A4Extra,
      A4Plus,
      A4Small,
      A5Extra,
      B5Extra,

      JisB0,
      JisB1,
      JisB2,
      JisB3,
      JisB4,
      JisB5,
      JisB6,
      JisB7,
      JisB8,
      JisB9,
      JisB10,

      // AnsiA = Letter,
      // AnsiB = Ledger,
      AnsiC,
      AnsiD,
      AnsiE,
      LegalExtra,
      LetterExtra,
      LetterPlus,
      LetterSmall,
      TabloidExtra,

      ArchA,
      ArchB,
      ArchC,
      ArchD,
      ArchE,

      Imperial7x9,
      Imperial8x10,
      Imperial9x11,
      Imperial9x12,
      Imperial10x11,
      Imperial10x13,
      Imperial10x14,
      Imperial12x11,
      Imperial15x11,

      ExecutiveStandard,
      Note,
      Quarto,
      Statement,
      SuperA,
      SuperB,
      Postcard,
      DoublePostcard,
      Prc16K,
      Prc32K,
      Prc32KBig,

      FanFoldUS,
      FanFoldGerman,
      FanFoldGermanLegal,

      EnvelopeB4,
      EnvelopeB5,
      EnvelopeB6,
      EnvelopeC0,
      EnvelopeC1,
      EnvelopeC2,
      EnvelopeC3,
      EnvelopeC4,
      // EnvelopeC5 = C5E,
      EnvelopeC6,
      EnvelopeC65,
      EnvelopeC7,
      // EnvelopeDL = DLE,

      Envelope9,
      // Envelope10 = Comm10E,
      Envelope11,
      Envelope12,
      Envelope14,
      EnvelopeMonarch,
      EnvelopePersonal,

      EnvelopeChou3,
      EnvelopeChou4,
      EnvelopeInvite,
      EnvelopeItalian,
      EnvelopeKaku2,
      EnvelopeKaku3,
      EnvelopePrc1,
      EnvelopePrc2,
      EnvelopePrc3,
      EnvelopePrc4,
      EnvelopePrc5,
      EnvelopePrc6,
      EnvelopePrc7,
      EnvelopePrc8,
      EnvelopePrc9,
      EnvelopePrc10,
      EnvelopeYou4,

      // Last item, with commonly used synynoms from QPagedPrintEngine / QPrinter
      LastPageSize = EnvelopeYou4,
      NPageSize = LastPageSize,
      NPaperSize = LastPageSize,

      // Convenience overloads for naming consistency
      AnsiA = Letter,
      AnsiB = Ledger,
      EnvelopeC5 = C5E,
      EnvelopeDL = DLE,
      Envelope10 = Comm10E
  };

  // NOTE: Must keep in sync with QPageLayout::Unit and QPrinter::Unit
  enum Unit {
      Millimeter,
      Point,
      Inch,
      Pica,
      Didot,
      Cicero
  };
  Q_ENUMS(PageSizeId Unit)
private:
  Q_OBJECT
  Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY pageSizeChanged)
  Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY pageSizeChanged)
  Q_PROPERTY(Unit unit READ unit WRITE setUnit NOTIFY unitChanged)
  Q_PROPERTY(PageSizeId pageSizeId READ pageSizeId WRITE setPageSizeId NOTIFY pageSizeChanged)
public:
  explicit PageSize(QQuickItem *parent = 0);
public:
  qreal width() const { return m_pageSize.size(QPageSize::Unit(m_unit)).width(); }
  void setWidth(qreal _width);
  qreal height() const { return m_pageSize.size(QPageSize::Unit(m_unit)).height(); }
  void setHeight(qreal _height);
  PageSizeId pageSizeId() const { return PageSizeId(m_pageSize.id()); }
  void setPageSizeId(PageSizeId _id);
  Unit unit() const { return m_unit; }
  void setUnit(const Unit _unit) { m_unit = _unit; emit(unitChanged()); }
  QPageSize pageSize() const { return m_pageSize; }
signals:
  void pageSizeChanged();
  void unitChanged();
public slots:

private:
  Unit m_unit;
  QPageSize m_pageSize;
};

#endif // PAGESIZE_H
