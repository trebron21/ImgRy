#ifndef IMGRYMAINWINDOW_H
#define IMGRYMAINWINDOW_H

#include <QMainWindow>
#include <thread>
#include <mutex>
#include <memory>

class WorkerThread;

namespace Ui
{
  class ImgRyMainWindow;
}

class ImgRyMainWindow : public QMainWindow
{
    Q_OBJECT


  public:
    explicit ImgRyMainWindow(QWidget * parent = 0);
    ~ImgRyMainWindow();

    void writeTrace(QString text);

    QVector<QString> filePaths;


  private slots:
    void on_btnConvert_clicked();

    void realizeTrace(QString text);


  private:
    Ui::ImgRyMainWindow * ui;

    std::mutex traceMutex;

    std::unique_ptr<WorkerThread> worker;

    std::vector<std::thread> threadPool;
};

#endif // IMGRYMAINWINDOW_H
