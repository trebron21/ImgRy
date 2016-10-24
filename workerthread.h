#ifndef WORKERTHREAD
#define WORKERTHREAD

#include "imgrymainwindow.h"
#include "ui_imgrymainwindow.h"

//#include <QDirIterator>
//#include <QString>
//#include <QVector>
//#include <QQueue>
//#include <QTime>
//#include <QMutex>
//#include <QMutexLocker>
//#include <QThreadPool>
#include <QThread>

//#include <Magick++.h>

//#include <string>
//#include <iostream>
//#include <sstream>
//#include <thread>
//#include <mutex>

class WorkerThread : public QThread
{
  Q_OBJECT

public:
  WorkerThread(int Id, ImgRyMainWindow & wnd) : id(Id), imgWnd(wnd), m_stop(false)
  {
  }

Q_SIGNALS:
  void emitTrace(QString text);

public slots:
  void stop()
  {
//    qDebug()<<"Thread::stop called from main thread: "<<currentThreadId();
    QMutexLocker locker(&m_mutex);
    m_stop = true;
  }

private:
  int id;
  ImgRyMainWindow& imgWnd;
  QMutex m_mutex;
  bool m_stop;

  QMutex traceMtx;
  QMutex filePathsMtx;

  void run();
};

#endif // WORKERTHREAD
