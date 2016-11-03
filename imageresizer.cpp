#include "imageresizer.h"

#include <QDirIterator>
#include <QImage>
#include <QString>
#include <QTime>

#include <sstream>
#include <thread>


namespace
{
  auto currentTimeAsQString = []()
  {
    return QTime::currentTime().toString();
  };
}


void ImageResizer::run(uint8_t imageRatio)
{
  auto myId = std::this_thread::get_id();
  std::stringstream sstr;
  sstr << myId;
  QString threadIdString = sstr.str().c_str();

  while (m_keepRunning)
  {
    QTime begin = QTime::currentTime();

    std::string filePath = "";

    {
      std::lock_guard<std::mutex> filePathsLock(m_filePathsMutex);

      emit emitTrace(currentTimeAsQString() + " | " + threadIdString +
                     QString(" | Num of remaining files: ") + QString::number(m_filePathsQueue.size()));

      if (m_filePathsQueue.empty())
        break;

      filePath = m_filePathsQueue.front();
      m_filePathsQueue.pop();
    }

    if (filePath.empty())
      continue;

    QImage image;

    if (!image.load(filePath.c_str()))
    {
      emit emitTrace(currentTimeAsQString() + " | " + threadIdString +
                     QString(" | Could not read image: ") + filePath.c_str());
      continue;
    }

    image = image.scaledToHeight(image.height() / imageRatio, Qt::SmoothTransformation);

    filePath.insert(filePath.rfind('.'), "_1");

    if (!image.save(filePath.c_str()))
    {
      emit emitTrace(currentTimeAsQString() + " | " +
                     threadIdString + QString(" | Could not save image"));
    }

    int duration = begin.elapsed();

    emit emitTrace(currentTimeAsQString() + " | " + threadIdString +
                   QString(" | Writing file: ") + filePath.c_str());
    emit emitTrace(currentTimeAsQString() + " | " + threadIdString +
                   QString(" | Duration: ") + QString::number(duration) + "ms");
  }
}


void ImageResizer::start(std::string directoryPath, uint8_t imageRatio)
{
  // Creating a list of filenames should not last too long, so we do it here,
  // starting a thread for this would be inefficient and a bit of an overkill
  QDirIterator dirIt(QString::fromStdString(directoryPath), QDirIterator::NoIteratorFlags);

  while (dirIt.hasNext())
  {
    dirIt.next();

    QFileInfo fileInfo = dirIt.filePath();

    if (fileInfo.isFile() &&
        (fileInfo.suffix().toLower() == "jpg" || fileInfo.suffix().toLower() == "jpeg"))
      enqueue(fileInfo.absoluteFilePath().toStdString());
  }

  // Launch a group of threads
  auto const hwThreadCount = std::thread::hardware_concurrency();
  auto const numThreads = (hwThreadCount != 0U) ? hwThreadCount : 2U;

  for (auto i = 0U; i < numThreads; ++i)
    m_threadPool.push_back(std::thread(&ImageResizer::run, this, imageRatio));
}


void ImageResizer::stop()
{
  m_keepRunning = false;

  std::for_each(m_threadPool.begin(), m_threadPool.end(), std::mem_fn(&std::thread::join));
}


void ImageResizer::enqueue(std::string filePath)
{
  std::lock_guard<std::mutex> fileQueueLock(m_filePathsMutex);
  m_filePathsQueue.push(filePath);
}
