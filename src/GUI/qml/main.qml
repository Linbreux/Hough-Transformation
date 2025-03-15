import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
  visible: true
  width: 640
  height: 480
  title: "My QML App"
  ColumnLayout{
    Text{
        padding: 20
        text: "Hough Transformation"
        font.family: "Helvetica"
        font.pointSize: 24
      }
    RowLayout{
      spacing: 2
      ColumnLayout{
        Text{
          padding: 10
          text: "Draw"
          font.family: "Helvetica"
          font.pointSize: 15
        }
        HoughDrawScreen{
          Layout.fillWidth: true
          Layout.preferredWidth: 600
          Layout.minimumHeight: 600
        }
      }

      ColumnLayout{
        Text{
          padding: 10
          text: "Transformation"
          font.family: "Helvetica"
          font.pointSize: 15
        }
        HoughTransformScreen{
          Layout.fillWidth: true
          Layout.preferredWidth: 600
          Layout.minimumHeight: 600
        }
      }
    }
    Button{
      text: "Clear"
      onClicked: canvasController.clearAll()
    }
  }
}
