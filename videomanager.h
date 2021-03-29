#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <QDebug>
#include <QObject>
#include <QTimer>
#include <QString>
#include <QImage>
#include <QSoundEffect>
#include <QMutex>
#include <opencv2/opencv.hpp>

#include <memory>
#include "videoproducer.h"

class UserListManager;

class VideoManager : public QObject, public std::enable_shared_from_this<VideoManager>
{
    Q_OBJECT

public:
    static const std::string TAG;
    VideoProducer* mainCameraProducer = nullptr;
    VideoProducer* thermalCameraProducer = nullptr;

public:
    explicit VideoManager(QObject *parent = nullptr);
    ~VideoManager();
    void frameReceived(const cv::Mat &rtspFrame, const cv::Mat &thermalFrame);
    Q_INVOKABLE void setMainCameraProducer(VideoProducer* producer);
    Q_INVOKABLE void setThermalCameraProducer(VideoProducer* producer);

private:
    QTimer *timer;
    bool isFrameReady;
    QImage normalQimage;
    QImage thermalQimage;

private:
    void initialization();
    QImage Mat2QImage(const cv::Mat &src);

public slots:
    void process();

};
#endif // THREADMANAGER_HPP
