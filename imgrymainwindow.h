#ifndef IMGRYMAINWINDOW_H
#define IMGRYMAINWINDOW_H

#include <QMainWindow>
#include <QMutex>

namespace Ui {
  class ImgRyMainWindow;
}

class ImgRyMainWindow : public QMainWindow
{
    Q_OBJECT


  public:
    explicit ImgRyMainWindow(QWidget *parent = 0);
    ~ImgRyMainWindow();

    void writeTrace(QString text);

    QVector<QString> filePaths;


  private slots:
    void on_btnConvert_clicked();

    void realizeTrace(QString text);


  private:
    Ui::ImgRyMainWindow *ui;

    QMutex traceMtx;
};

#endif // IMGRYMAINWINDOW_H
