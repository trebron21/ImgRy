#ifndef WORKERTHREAD
#define WORKERTHREAD

#include "imgrymainwindow.h"
#include "ui_imgrymainwindow.h"

#include <thread>
#include <mutex>

class WorkerThread : public QObject
{
  Q_OBJECT

  public:
    WorkerThread(ImgRyMainWindow & wnd);
    ~WorkerThread();

    void run();

  Q_SIGNALS:
    void emitTrace(QString text);

  private:
    ImgRyMainWindow& imgWnd;

//    std::mutex filePathsMutex;

//    int numOfFiles;
};

#endif // WORKERTHREAD
