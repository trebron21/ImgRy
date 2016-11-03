#pragma once
#include <QObject>

class ImageResizer : public QObject
{
  Q_OBJECT

  public:
    ImageResizer() = default;
    ~ImageResizer() = default;

    void start(std::string directoryPath, uint8_t imageRatio);
    void stop();

  signals:
    void emitTrace(QString text);

  private:
    void run(uint8_t imageRatio);
};
