#include "imgrymainwindow.h"
#include "ui_imgrymainwindow.h"
#include "workerthread.h"

#include <QDirIterator>
#include <QTime>
#include <QDebug>


ImgRyMainWindow::ImgRyMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::ImgRyMainWindow()),
  worker(new WorkerThread(*this))
{
  ui->setupUi(this);
  ui->ratioLabel->setNum(ui->horizontalSlider->value());

  QObject::connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),
                   ui->ratioLabel,       SLOT(setNum(int)));

  QObject::connect(worker.get(), SIGNAL(emitTrace(QString)),
                   this,         SLOT(realizeTrace(QString))/*, Qt::AutoConnection*/);
}


ImgRyMainWindow::~ImgRyMainWindow()
{
  delete ui;
}


void ImgRyMainWindow::realizeTrace(QString text)
{
  QMetaObject::invokeMethod(ui->traceViewer, "append", Qt::AutoConnection, Q_ARG(QString, QTime::currentTime().toString() + " | " + text));

//  std::lock_guard<std::mutex> trcLocker(traceMutex); // allegedly this does not work, because Qt's (UI) event loop does not know anything about my mutex
//  ui->traceViewer->append(QTime::currentTime().toString() + " | " + text);
}


void ImgRyMainWindow::on_btnConvert_clicked()
{
  // Creating a list of filenames should not last too long, so we do it here,
  // starting a thread for this would be inefficient and a bit of an overkill
  QDirIterator dirIt(ui->lineEditDirPath->text(), QDirIterator::NoIteratorFlags);

  while (dirIt.hasNext())
  {
    dirIt.next();

    QFileInfo fileInfo = dirIt.filePath();

    if (fileInfo.isFile())
    {
      if (fileInfo.suffix().toLower() == "jpg" || fileInfo.suffix().toLower() == "jpeg")
      {
        filePaths.append(fileInfo.absoluteFilePath());
      }
    }
  }

  // Launch a group of threads
  auto const hwThreadCount = std::thread::hardware_concurrency();
  auto const numThreads = (hwThreadCount != 0U) ? hwThreadCount : 2U;

  for (auto i = 0U; i < numThreads; ++i)
  {
    threadPool.push_back(std::thread(&WorkerThread::run, worker.get(), ui->horizontalSlider->value()));
  }

// todo  std::for_each(threadPool.begin(), threadPool.end(), std::mem_fn(&std::thread::join));
}
