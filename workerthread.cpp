#include "workerthread.h"

#include "imgrymainwindow.h"
#include "ui_imgrymainwindow.h"

#include <QString>
#include <QTime>
#include <QDebug>

#include <thread>
#include <sstream>
#include <atomic>


std::mutex filePathsMutex;
std::mutex fileSaveMutex;
std::atomic<int> numOfFiles = 0;

WorkerThread::WorkerThread(ImgRyMainWindow & wnd) :
  imgWnd(wnd)
{ /* empty */ }


WorkerThread::~WorkerThread()
{ /* empty */ }


void WorkerThread::run()
{
  {
    std::lock_guard<std::mutex> locker(filePathsMutex);
    numOfFiles = imgWnd.filePaths.size();
  }

  auto myId = std::this_thread::get_id();
  std::stringstream sstr;
  sstr << myId;
  QString threadIdString = sstr.str().c_str();

  while (true)
  {
    QTime begin = QTime::currentTime();

//    emit emitTrace(threadIdString + QString(" | Num of remaining files: ") + QString::number(numOfFiles));

    QString filePath = "";

    {
      std::lock_guard<std::mutex> lock(filePathsMutex);

      numOfFiles = imgWnd.filePaths.size();
      qInfo() << threadIdString.toStdString().c_str() << " num of remaining files: " << numOfFiles;

      if (!imgWnd.filePaths.isEmpty())
        filePath = imgWnd.filePaths.takeFirst();
    }

    if (!filePath.length())
      break;

    QImage image;// = new QImage();

    if (!image.load(filePath))
    {
//      emit emitTrace(threadIdString + QString(" | Could not read image: ") + filePath);
    }

    image = image.scaledToHeight(image.height() / 3, Qt::SmoothTransformation);

    QString dot = ".";
    filePath.insert(filePath.lastIndexOf(dot), "_1");

    if (!image.save(filePath))
    {
//      emit emitTrace(threadIdString + QString(" | Could not save image"));
    }

//    qInfo() << threadIdString.toStdString().c_str() << " filepath: " << filePath;

//    delete image;
//    image = nullptr;

//    int duration = begin.elapsed();

//    qInfo() << threadIdString.toStdString().c_str() << " | Writing file: " << filePath.toStdString().c_str() << "\n"
//            << threadIdString.toStdString().c_str() << " | Duration: " << duration << "ms";

//    emit emitTrace(threadIdString + QString(" | Writing file: ") + filePath);
//    emit emitTrace(threadIdString + QString(" | Duration: ") + QString::number(duration) + "ms");
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
