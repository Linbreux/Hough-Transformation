import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1

Rectangle{

  color: "green"
  Canvas {
    id: canvas
    anchors.fill: parent
    contextType: "2d"
    property bool clear: false
    onPaint: {
      var ctx = getContext("2d");
      if (clear == true) {
        ctx.reset();
        canvas.clear = false;
      }
      var pointToDrawList = canvasController.drawList;
      for (var i = 0; i < pointToDrawList.length; i++){
        var drawable = pointToDrawList[i]
        ctx.fillStyle = drawable.color;
        if (drawable.connected){
          //do we need to draw a line
          ctx.beginPath();
          ctx.strokeStyle = drawable.color;  // Line color
          ctx.lineWidth = 5;
          ctx.moveTo(drawable.x2, drawable.y2); 
          ctx.lineTo(drawable.x, drawable.y);
          ctx.stroke();
        } else{
          // or a just a point
          ctx.beginPath();
          ctx.arc(drawable.x, drawable.y, 2.5, 0, 2 * Math.PI); // Draw a circle with radius 5
          ctx.fill();
        }
      }
    }
    MouseArea {
        id: area
        anchors.fill: parent
        property var lastpoint: null
        onPressed: (mouse) => {
          canvasController.addPoint(mouse.x, mouse.y)
          lastpoint = Qt.point(mouse.x, mouse.y)
        }
        onPositionChanged: (mouse) => {
          if (mouse.buttons & Qt.LeftButton) {
            if (!lastpoint){
              lastpoint = Qt.point(mouse.x, mouse.y)
              canvasController.addPoint(lastpoint)
              return
            }
            let dx = mouse.x - lastpoint.x;
            let dy = mouse.y - lastpoint.y;
            if (dx * dx + dy * dy > 100){
              canvasController.addLine(Qt.point(mouse.x, mouse.y))
              lastpoint = Qt.point(mouse.x, mouse.y)
            }
          }
        }
    }

    Connections {
      target: canvasController
      onClearCanvas:{
        canvas.clear = true
        canvas.requestPaint() // Repaint when points change
      }
      onChangedPoints: {
        canvas.requestPaint() // Repaint when points change
      }
    }
  }
}
