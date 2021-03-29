import QtQuick 2.0
import QtMultimedia 5.9
import VideoProducer 0.1

Item {
    id: element
    property var mode: VideoOutput.PreserveAspectFit

    function getVideoProducer() {
        return videoProducer
    }
    function getVideoOutput() {
        return videoOutput
    }

    VideoProducer {
        id: videoProducer
    }

    VideoOutput {
        id: videoOutput
        anchors.fill: parent
        source: videoProducer
        fillMode: mode
    }
}
