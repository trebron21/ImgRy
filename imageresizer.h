#pragma once

#include <QObject>

#include <atomic>
#include <mutex>
#include <queue>
#include <thread>


class ImageResizer : public QObject
{
  Q_OBJECT

  public:
    ImageResizer() = default;
    ~ImageResizer() = default;

    void start(std::string directoryPath, uint8_t imageRatio);
    void stop();

  Q_SIGNALS:
    void emitTrace(QString text);

  private:
    void run(uint8_t imageRatio);
    void enqueue(std::string filePath);

    std::mutex m_filePathsMutex;
    std::queue<std::string> m_filePathsQueue;

    std::atomic<bool> m_keepRunning = true;

    std::vector<std::thread> m_threadPool;
};
