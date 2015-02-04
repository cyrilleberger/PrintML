/**
 *   Copyright (c) 2014 Cyrille Berger <cberger@cberger.net>
 *
 *   This Source Code Form is subject to the terms of the Mozilla Public
 *   License, v. 2.0. If a copy of the MPL was not distributed with this
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "PrintMLPlugin.h"

#include "MiniPage.h"
#include "Printer.h"
#include "PageSize.h"

#include <qqml.h>

void PrintMLPlugin::registerTypes(const char *uri)
{
  // @uri org.storyml.print
  qmlRegisterType<MiniPage>(uri, 1, 0, "MiniPage");
  qmlRegisterType<Printer>(uri, 1, 0, "Printer");
  qmlRegisterType<PageSize>(uri, 1, 0, "PageSize");
}


