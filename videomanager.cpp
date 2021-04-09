#include "videomanager.h"


VideoManager::VideoManager(QObject *parent) : QObject(parent)
{
    mCamera = std::unique_ptr<Camera>(new Camera());
    QObject::connect(mCamera.get(), &Camera::updateCameraFrame,
                     this,          &VideoManager::frameReceived);
}

VideoManager::~VideoManager()
{
    qDebug() << Q_FUNC_INFO << "Destory VideoManager.";
    QObject::disconnect(mCamera.get(), &Camera::updateCameraFrame,
                        this,          &VideoManager::frameReceived);
}

void VideoManager::frameReceived(const cv::Mat &frame) {
    cv::Mat image(frame);
    mCameraProducer->updateFrame(Mat2QImage(image));
}

void VideoManager::setCameraProducer(VideoProducer* producer) {
    mCameraProducer = producer;
    initialization();
}

void VideoManager::initialization() {
    mCamera->start();
}

QImage VideoManager::Mat2QImage(const cv::Mat &src)
{
    cv::Mat temp; // make the same cv::Mat
    cv::cvtColor(src, temp, cv::COLOR_BGR2BGRA);
    QImage dest((const uchar *)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB32);
    dest.bits(); // enforce deep copy, see documentation
    return dest;
}

