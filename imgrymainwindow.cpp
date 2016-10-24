#include "imgrymainwindow.h"
#include "ui_imgrymainwindow.h"

#include <QDirIterator>
//#include <QString>
//#include <QVector>
//#include <QQueue>
#include <QTime>
//#include <QMutex>
#include <QMutexLocker>
//#include <QThreadPool>

#include "workerthread.h"

//#include <Magick++.h>

//#include <string>
//#include <iostream>
//#include <sstream>
//#include <thread>
//#include <mutex>

ImgRyMainWindow::ImgRyMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::ImgRyMainWindow())
{
  ui->setupUi(this);
}


ImgRyMainWindow::~ImgRyMainWindow()
{
  delete ui;
}


void ImgRyMainWindow::realizeTrace(QString text)
{
  QMutexLocker trcLocker(&traceMtx);
  ui->traceViewer->append(QTime::currentTime().toString() + " | " + text);
}


void ImgRyMainWindow::on_btnConvert_clicked()
{
  QDirIterator dirIt(ui->lineEditDirPath->text(), QDirIterator::NoIteratorFlags);

  while (dirIt.hasNext())
  {
    dirIt.next();
    if (QFileInfo(dirIt.filePath()).isFile())
    {
      if (QFileInfo(dirIt.filePath()).suffix().toLower() == "jpg" || QFileInfo(dirIt.filePath()).suffix().toLower() == "jpeg")
      {
        filePaths.append(dirIt.filePath());
      }
    }
  }

  const int thrCnt = 3;

  QThread * t[thrCnt];

  // Launch a group of threads
  for (int i = 0; i < thrCnt; ++i)
  {
    t[i] = new WorkerThread(i, *this);
    QObject::connect(t[i], SIGNAL(emitTrace(QString)), this, SLOT(realizeTrace(QString)));
//    QObject::connect(t[i], SIGNAL(finished()), t[i], SLOT(deleteLater()));
    t[i]->start();
  }
}
