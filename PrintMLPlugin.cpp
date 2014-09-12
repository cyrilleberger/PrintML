#include "PrintMLPlugin.h"
#include "Printer.h"
#include "PageSize.h"

#include <qqml.h>

void PrintMLPlugin::registerTypes(const char *uri)
{
  // @uri org.slidesml.print
  qmlRegisterType<Printer>(uri, 1, 0, "Printer");
  qmlRegisterType<PageSize>(uri, 1, 0, "PageSize");
}


