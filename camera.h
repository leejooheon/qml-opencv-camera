#ifndef CAMERA_H
#define CAMERA_H
#include <QObject>
#include <QThread>
#include <opencv2/opencv.hpp>

class Camera : public QThread
{
    Q_OBJECT
public:
    Camera();
    ~Camera() override;

protected:
    void run() override;

signals:
    void updateCameraFrame(cv::Mat mat);
};

#endif // CAMERA_H
