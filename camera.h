#ifndef OZRAYCAMERA_H
#define OZRAYCAMERA_H
#include <QObject>
#include <QThread>
#include <opencv2/opencv.hpp>
#include "videomanager.h"

class Camera : public QThread
{
    Q_OBJECT
public:
    Camera();
    ~Camera() override;
    void setVideoManager(VideoManager* _videoManager) {videoManager = _videoManager;}

protected:
    void run() override;

private:
    VideoManager* videoManager;
};

#endif // OZRAYCAMERA_H
