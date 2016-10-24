#include "imgrymainwindow.h"
#include <QApplication>
#include <QStyleFactory>
//#include <Magick++.h>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QApplication::setStyle(QStyleFactory::create("Fusion"));
//  Magick::InitializeMagick(*argv);

  ImgRyMainWindow w;
  w.show();

  return a.exec();
}
