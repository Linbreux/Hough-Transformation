import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1

Rectangle{
  color: "red"
  Canvas {
    id: canvas
    anchors.fill: parent
    contextType: "2d"
    property bool clear: false
    property var xScale: 3
    property var yScale: 1/3
    property var xOffset: 0
    property var yOffset: 300
    onPaint: {
      var ctx = getContext("2d");
      ctx.fillStyle = "rgba(0, 0, 0, 0.5)";
      var pointToDrawList = canvasController.transformList;

      for (var i = 0; i < pointToDrawList.length; i++){
        var point = pointToDrawList[i];
          ctx.beginPath();
          ctx.arc(point.x*xScale, point.y*yScale+yOffset, 1, 0, 2 * Math.PI); // Draw a circle with radius 5
          ctx.fill();
      }

    }

    MouseArea {
        id: area
        anchors.fill: parent
        hoverEnabled: true
        property var lastpoint: null
        onPositionChanged: (mouse) => {
            if (!lastpoint){
              lastpoint = Qt.point(mouse.x, mouse.y)
              return
            }
            canvasController.addReversePoint(Qt.point(mouse.x/canvas.xScale, (mouse.y-canvas.yOffset)/canvas.yScale))
            lastpoint = Qt.point(mouse.x, mouse.y)
          }
        }
    }

    Connections {
      target: canvasController
      onClearCanvas:{
        canvas.clear = true
        canvas.requestPaint() // Repaint when points change
      }
      onChangedTransform: {
        canvas.requestPaint() // Repaint when points change
      }
    }
  }
