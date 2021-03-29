#ifndef VIDEOPRODUCER_H
#define VIDEOPRODUCER_H

#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>

class VideoProducer : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QAbstractVideoSurface* videoSurface READ videoSurface WRITE setVideoSurface )
public:
    explicit VideoProducer( QObject *parent = 0 );
    ~VideoProducer();

    QAbstractVideoSurface* videoSurface() const;
    void updateFrame(QImage image);
    void setVideoSurface( QAbstractVideoSurface* surface);

private:
    void closeSurface();

private:
    QAbstractVideoSurface* mSurface;
    QVideoSurfaceFormat mFormat;
};
#endif
