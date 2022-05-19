import QtQuick 2.0
import FractalModule 1.0
import MyRenderLibrary 42.0
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
Item
{
    width: 600
    height: 400

    // Fractal
    MeshRenderer
    {
        id : fractal
        SequentialAnimation on t
        {
            NumberAnimation { to: 1; duration: 2500; easing.type: Easing.InQuad }
            NumberAnimation { to: 0; duration: 2500; easing.type: Easing.OutQuad }
            loops: Animation.Infinite
            running: true
        }
        anchors.fill : parent

        Rectangle
        {
            width : 20
            height : 20
            anchors.centerIn : fractal
            color : "red"
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
        // text: (fractal.t * 10).toFixed(1)
        text: "QmlFractals"
        horizontalAlignment: Text.AlignHCenter
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 20
    }
}
