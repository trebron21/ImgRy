#include "imgrymainwindow.h"
#include "ui_imgrymainwindow.h"
#include "workerthread.h"

#include <QDirIterator>
#include <QTime>
#include <QDebug>


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
//  std::lock_guard<std::mutex> trcLocker(traceMutex);
  QMetaObject::invokeMethod(ui->traceViewer, "append", Qt::AutoConnection, Q_ARG(QString, QTime::currentTime().toString() + " | " + text));
//  ui->traceViewer->append(QTime::currentTime().toString() + " | " + text);
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

  WorkerThread * worker = new WorkerThread(*this); // this memleak has to be fixed, but worker must not be a local variable, because it could go out of scope before the threads finish
  int const thrCnt = 3;

  // Launch a group of threads
  for (int i = 0; i < thrCnt; ++i)
  {
    qInfo() << "starting thread: " <<  i;
    threadPool.push_back(std::thread(&WorkerThread::run, worker));
//    threadPool.at(threadPool.size() - 1).detach();
//    QObject::connect(&worker, SIGNAL(emitTrace(QString)), this, SLOT(realizeTrace(QString)), Qt::AutoConnection);
//    QObject::connect(t[i], SIGNAL(finished()), t[i], SLOT(deleteLater()));
  }

//  std::for_each(threadPool.begin(), threadPool.end(), std::mem_fn(&std::thread::join));
}
