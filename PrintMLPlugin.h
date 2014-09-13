/**
 *   Copyright (c) 2014 Cyrille Berger <cberger@cberger.net>
 *
 *   This Source Code Form is subject to the terms of the Mozilla Public
 *   License, v. 2.0. If a copy of the MPL was not distributed with this
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef PRINTML_PLUGIN_H
#define PRINTML_PLUGIN_H

#include <QQmlExtensionPlugin>

class PrintMLPlugin : public QQmlExtensionPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
  void registerTypes(const char *uri);
};

#endif // PRINTML_PLUGIN_H

