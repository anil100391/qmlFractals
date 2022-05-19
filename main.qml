import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
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
        mode : julia.checked ? 0 : (mandel.checked ? 1 : 2)
        SequentialAnimation on t
        {
            NumberAnimation { to: 1; duration: 2500; easing.type: Easing.InQuad }
            NumberAnimation { to: 0; duration: 2500; easing.type: Easing.OutQuad }
            loops: Animation.Infinite
            running: true
        }
        anchors.fill : parent
    }

    Rectangle
    {
        id : goLeft
        width : 40
        color : Qt.rgba(1.0, 1.0, 1.0, 0.05);
        anchors
        {
            top : parent.top
            bottom : parent.bottom
            left : parent.left
        }
        MouseArea
        {
            anchors.fill: parent
            onClicked : fractal.mode = (fractal.mode + 2) % 3
        }
    }

    Rectangle
    {
        id : goRight
        width : 40
        color : Qt.rgba(1.0, 1.0, 1.0, 0.05);
        anchors
        {
            top : parent.top
            bottom : parent.bottom
            right : parent.right
        }
        MouseArea
        {
            anchors.fill: parent
            onClicked : {
                fractal.mode = (fractal.mode + 1 ) % 3
            }
        }
    }

    Rectangle
    {
        id : buttonBox
        color : Qt.rgba(1.0, 1.0, 1.0, 0.7);
        anchors.left : parent.left
        anchors.right : parent.right
        anchors.bottom : parent.bottom
        height : 4 * julia.implicitHeight

        // RowLayout
        //{
            ColumnLayout
            {
                id : buttonLayout
                anchors.verticalCenter: buttonBox.verticalCenter
                RadioButton
                {
                    id : julia
                    checked: true
                    text: "Julia"
                    anchors.leftMargin: 5
                }
                RadioButton
                {
                    id : mandel
                    text: "Mandelbrot"
                    anchors.leftMargin: 5
                }
                RadioButton
                {
                    id : newton
                    text: "Newton"
                    anchors.leftMargin: 5
                }
            }
        //}
    }

    /*
    Rectangle
    {
        id : textInfo
        color: Qt.rgba(1, 1, 1, 0.7)
        radius: 0
        border.width: 1
        border.color: "white"
        anchors.fill: label
        anchors.margins: -15
    }*/

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
