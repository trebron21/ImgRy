#include "imgrymainwindow.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
  QApplication application(argc, argv);
  QApplication::setStyle(QStyleFactory::create("Fusion"));

  ImgRyMainWindow window;
  window.show();

  return application.exec();
}
