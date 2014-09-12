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

