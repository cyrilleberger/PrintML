#include "PrintMLPlugin.h"
#include "Printer.h"

#include <qqml.h>

void PrintMLPlugin::registerTypes(const char *uri)
{
  // @uri org.slidesml.print
  qmlRegisterType<Printer>(uri, 1, 0, "Printer");
}


