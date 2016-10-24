#include "workerthread.h"

#include "imgrymainwindow.h"
#include "ui_imgrymainwindow.h"

//#include <QDirIterator>
#include <QString>
//#include <QVector>
//#include <QQueue>
#include <QTime>
//#include <QMutex>
#include <QMutexLocker>
//#include <QThreadPool>

//#include <Magick++.h>

//#include <string>
//#include <iostream>
//#include <sstream>
//#include <thread>
//#include <mutex>

//using namespace Magick;

void WorkerThread::run()
{
  int numOfFiles = 0;
  while (0 < (numOfFiles = imgWnd.filePaths.size()))
  {
    QString tid = QString::number(id);
    QTime begin = QTime::currentTime();
    emit emitTrace(tid + QString(" | Num of remaining files: ") + QString::number(numOfFiles));

    QString filePath;

    {
      QMutexLocker lock(&filePathsMtx);
      if (0 < (numOfFiles = imgWnd.filePaths.size()))
        filePath = imgWnd.filePaths.takeFirst();
    }

    if (!filePath.length())
      continue;

    QImage * image = new QImage();

    if(!image->load(filePath))
    {
      emit emitTrace(tid + QString(" | Could not read image: ") + filePath);
    }

    *image = image->scaledToHeight(image->height() / 5, Qt::SmoothTransformation);

    QString dot = ".";
    filePath.insert(filePath.lastIndexOf(dot), "_1");

    if(!image->save(filePath))
    {
      emit emitTrace(tid + QString(" | Could not save image"));
    }

    delete image;

    int duration = begin.elapsed();

    emit emitTrace(tid + QString(" | Writing file: ") + filePath);
    emit emitTrace(tid + QString(" | Duration: ") + QString::number(duration) + "ms");
  }
}


//void WorkerThread::run()
//{
//  int numOfFiles = 0;
//  while (0 < (numOfFiles = imgWnd.filePaths.size()))
//  {
//    QString tid = QString::number(id);
//    QTime begin = QTime::currentTime();
//    emit emitTrace(tid + QString(" | Num of remaining files: ") + QString::number(numOfFiles));

//    Image image;
//    QString filePath;

//    {
//      QMutexLocker lock(&filePathsMtx);
//      if (0 < (numOfFiles = imgWnd.filePaths.size()))
//        filePath = imgWnd.filePaths.takeFirst();
//    }

//    if (!filePath.length())
//      continue;

//    image.read(filePath.toStdString());
////    Geometry newSize = Geometry(1504, 1000);
//    Geometry newSize = Geometry(752, 500);
//  //  newSize.aspect(true);
//    image.resize(newSize);

//    QString dot = ".";
//    filePath.insert(filePath.lastIndexOf(dot), "_1");

//    image.write(filePath.toStdString());
//    int duration = begin.elapsed();

//    emit emitTrace(tid + QString(" |  writing file: ") + filePath);
//    emit emitTrace(tid + QString(" | Duration: ") + QString::number(duration) + "ms");
//  }
//}