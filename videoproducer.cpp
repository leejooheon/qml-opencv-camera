#include "videoproducer.h"
#include <QDebug>

VideoProducer::VideoProducer( QObject *parent ): QObject( parent ), mSurface(nullptr)
{
}

VideoProducer::~VideoProducer()
{
    closeSurface();
}

QAbstractVideoSurface* VideoProducer::videoSurface() const
{
    return mSurface;
}

void VideoProducer::setVideoSurface( QAbstractVideoSurface* s )
{
    closeSurface();
    mSurface = s;
}

void VideoProducer::closeSurface()
{
    if( mSurface && mSurface->isActive() )
        mSurface->stop();
}

void VideoProducer::updateFrame(QImage image)
{
    if(image.size() != mFormat.frameSize())
    {
        qDebug() << "newSize: " << image.size();
        closeSurface();
        mFormat = QVideoSurfaceFormat( image.size(), QVideoFrame::PixelFormat::Format_RGB32);
        mSurface->start(mFormat);
    }
//    qDebug() << "updateFrame: " << mSurface->nativeResolution();
    mSurface->present( QVideoFrame( image ) );
}
