#include "videomanager.h"


VideoManager::VideoManager(QObject *parent) : QObject(parent)
{
}

VideoManager::~VideoManager()
{
    std::cout << "Destory video manager." << std::endl;
}

void VideoManager::initialization() {
    isFrameReady = false;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(process()));
    timer->start(25);
}

void VideoManager::frameReceived(const cv::Mat &rtspFrame, const cv::Mat &thermalFrame) {
    if(isFrameReady)
        return;
    cv::Mat image(rtspFrame);
    cv::Mat thermalImage(thermalFrame);

    if (!image.empty() && !thermalImage.empty()) {
        normalQimage = Mat2QImage(image);
        isFrameReady = true;
    }
}

void VideoManager::process() {
    if(!isFrameReady)
        return;

    if(mainCameraProducer == nullptr) //|| thermalCameraProducer == nullptr)
        return;

    mainCameraProducer->updateFrame(normalQimage.copy());
//    thermalCameraProducer->updateFrame(thermalQimage.copy());

    isFrameReady = false;
}

void VideoManager::setCameraProducer(VideoProducer* producer) {
    mainCameraProducer = producer;
    initialization();
}

QImage VideoManager::Mat2QImage(const cv::Mat &src)
{
    cv::Mat temp; // make the same cv::Mat
    cv::cvtColor(src, temp, cv::COLOR_BGR2BGRA);
    QImage dest((const uchar *)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB32);
    dest.bits(); // enforce deep copy, see documentation
    return dest;
}

