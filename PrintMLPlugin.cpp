#include "PrintMLPlugin.h"

#include "MiniPage.h"
#include "Printer.h"
#include "PageSize.h"

#include <qqml.h>

void PrintMLPlugin::registerTypes(const char *uri)
{
  // @uri org.slidesml.print
  qmlRegisterType<MiniPage>(uri, 1, 0, "MiniPage");
  qmlRegisterType<Printer>(uri, 1, 0, "Printer");
  qmlRegisterType<PageSize>(uri, 1, 0, "PageSize");
}


