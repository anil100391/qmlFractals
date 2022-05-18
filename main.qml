import QtQuick 2.0
import FractalModule 1.0

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
Item
{
    width: 400
    height: 600

    Fractal
    {
        id : fractal
        SequentialAnimation on t
        {
            NumberAnimation { to: 1; duration: 2500; easing.type: Easing.InQuad }
            NumberAnimation { to: 0; duration: 2500; easing.type: Easing.OutQuad }
            loops: Animation.Infinite
            running: true
        }
    }

    Rectangle
    {
        color: Qt.rgba(1, 1, 1, 0.7)
        radius: 0
        border.width: 1
        border.color: "white"
        anchors.fill: label
        anchors.margins: -15
    }

    Text
    {
        id: label
        color: "black"
        wrapMode: Text.WordWrap
        text: (fractal.t * 10).toFixed(1)
        horizontalAlignment: Text.AlignHCenter
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 20
    }
}
