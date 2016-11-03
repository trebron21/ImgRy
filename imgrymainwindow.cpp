#include "imgrymainwindow.h"
#include "ui_imgrymainwindow.h"
#include "imageresizer.h"

#include <QDebug>

ImgRyMainWindow::ImgRyMainWindow(QWidget *parent) :
  QMainWindow(parent),
  m_ui(new Ui::ImgRyMainWindow()),
  m_imageResizer(new ImageResizer())
{
  m_ui->setupUi(this);
  m_ui->ratioLabel->setNum(m_ui->imgRatioSlider->value());

  QObject::connect(m_ui->imgRatioSlider, SIGNAL(valueChanged(int)),
                   m_ui->ratioLabel,       SLOT(setNum(int)));

  QObject::connect(m_imageResizer.get(), SIGNAL(emitTrace(QString)),
                   this,         SLOT(realizeTrace(QString))/*, Qt::AutoConnection*/);
}


ImgRyMainWindow::~ImgRyMainWindow()
{
  // Stop the threads if they are still working
  m_imageResizer->stop();

  delete m_ui;
}


void ImgRyMainWindow::realizeTrace(QString text)
{
  QMetaObject::invokeMethod(m_ui->traceViewer, "append", Qt::AutoConnection, Q_ARG(QString, text));

//  Allegedly this does not work, because Qt's (UI) event loop does not know anything about this mutex
//  std::lock_guard<std::mutex> trcLocker(m_traceMutex);
//  ui->traceViewer->append(QTime::currentTime().toString() + " | " + text);
}


void ImgRyMainWindow::on_btnConvert_clicked()
{
  m_imageResizer->start(m_ui->lineEditDirPath->text().toStdString(), m_ui->imgRatioSlider->value());
}
