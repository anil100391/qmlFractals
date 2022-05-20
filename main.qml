import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import MyRenderLibrary 42.0

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
Item
{
    width: 400
    height: 600
    // Fractal
    MeshRenderer
    {
        id : fractal
        mode : view.currentIndex
        anchors.fill : parent
    }

    Rectangle
    {
        id : bottomPanel
        height : 40
        color : Qt.rgba(1.0, 1.0, 1.0, 0.05);
        anchors { bottom : parent.bottom; left : parent.left; right : parent.right }
        SwipeView
        {
            id : view
            currentIndex : 1
            anchors.fill : parent
            Repeater { model : 3; Item{} }
        }
        PageIndicator
        {
            currentIndex : view.currentIndex
            count : view.count
            anchors.centerIn : parent
        }
    }

    Text
    {
        id: label
        color: "white"
        wrapMode: Text.WordWrap
        // text: (fractal.t * 10).toFixed(1)
        text: ["Julia", "Mandelbrot", "Newton"][fractal.mode]
        horizontalAlignment: Text.AlignHCenter
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 20
    }
}
