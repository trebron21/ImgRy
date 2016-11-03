#ifndef WORKERTHREAD
#define WORKERTHREAD

#include "imgrymainwindow.h"
#include "ui_imgrymainwindow.h"

#include <thread>
#include <mutex>
#include <atomic>

class WorkerThread : public QObject
{
  Q_OBJECT

  public:
    WorkerThread(ImgRyMainWindow & wnd);
    ~WorkerThread();

    void run(uint8_t imageRatio);

  Q_SIGNALS:
    void emitTrace(QString text);

  private:
    ImgRyMainWindow& imgWnd;

    std::mutex filePathsMutex;

    std::atomic<uint32_t> numOfFiles;
};

#endif // WORKERTHREAD
