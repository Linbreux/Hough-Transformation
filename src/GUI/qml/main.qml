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
      HoughDrawScreen{
          Layout.fillWidth: true
          Layout.preferredWidth: 600
          Layout.minimumHeight: 600
      }
      HoughTransformScreen{
          Layout.fillWidth: true
          Layout.preferredWidth: 600
          Layout.minimumHeight: 600
      }
    }
  }
}
