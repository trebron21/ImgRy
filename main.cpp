#include "imgrymainwindow.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QApplication::setStyle(QStyleFactory::create("Fusion"));

  ImgRyMainWindow w;
  w.show();

  return a.exec();
}
