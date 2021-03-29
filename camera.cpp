#include <QDebug>
#include <QString>
#include "camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{
    qDebug() << Q_FUNC_INFO;
}

void Camera::run()
{
    const std::string normal_url = "rtsp://admin:qwe1010@192.168.1.6:554/live2.sdp"; // FIXME: your camera address
    cv::VideoCapture normal_video;

    forever{
        try {
            if (!normal_video.isOpened()) {
                try {
                    if (!normal_video.open(normal_url, cv::CAP_FFMPEG)) {
                        continue;
                    }
                } catch(...) {
                    return;
                }
                continue;
            }
            cv::Mat normal_frame;
            normal_video >> normal_frame;

            if (normal_frame.empty()) {
                normal_video.release();
                continue;
            }
            videoManager->frameReceived(normal_frame.clone(), normal_frame.clone());
        } catch (cv::Exception& e) {
            normal_video.release();
        } catch (...) {
            normal_video.release();
        }

        if ( QThread::currentThread()->isInterruptionRequested() ) {
            // Returns true if a task running on the thread should be stopped.
            // Interruption can be requested with the requestInterruption() function.
            qDebug() << Q_FUNC_INFO << " terminated";
            return;
        }
    }
}
