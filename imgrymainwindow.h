#pragma once
#include <QMainWindow>
#include <memory>

class ImageResizer;

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

  private slots:
    void on_btnConvert_clicked();

    void realizeTrace(QString text);

  private:
    Ui::ImgRyMainWindow * m_ui;

    std::unique_ptr<ImageResizer> m_imageResizer;
};
