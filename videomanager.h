#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <QDebug>
#include <QObject>
#include <QImage>

#include <opencv2/opencv.hpp>
#include "videoproducer.h"
#include "camera.h"

class UserListManager;

class VideoManager : public QObject, public std::enable_shared_from_this<VideoManager>
{
    Q_OBJECT

public:

public:
    explicit VideoManager(QObject *parent = nullptr);
    ~VideoManager();

private:
    static const std::string TAG;
    std::unique_ptr<Camera> mCamera;
    VideoProducer* mCameraProducer = nullptr;

public:
    Q_INVOKABLE void setCameraProducer(VideoProducer* producer);

private:
    void initialization();
    QImage Mat2QImage(const cv::Mat &src);

private slots:
    void frameReceived(const cv::Mat &frame);

};
#endif // THREADMANAGER_HPP
