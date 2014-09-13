import QtQuick 2.0
import QtQuick.Window 2.0
import org.slidesml.print 1.0

Item {
  width: 200
  height: 200

  Printer
  {
    id: printer
    window: printwindow
    filename: "testprint.pdf"
    pageSize.width: 200
    pageSize.height: 70
  }
  Window
  {
    width: 200
    height: 50
    id: printwindow
    visible: true
    Rectangle
    {
      id: rectangleToPrint
      anchors.fill: parent
      color: "red"
      Text {
        id: textToPrint
        text: "Text to be printed"
        color: "green"
        anchors.centerIn: parent
      }
    }
  }

  Text {
    id: startPrinting
    text: "Start Printing !"
    anchors.centerIn: parent
  }
  MouseArea
  {
    anchors.fill: parent
    onClicked:
    {
      printer.beginPrinting();
      printer.printWindow();
      printer.newPage();
      textToPrint.text = "New text";
      rectangleToPrint.color = "blue";
      printwindow.height = 300;
      timer.start();
    }
  }
  Timer
  {
    id: timer
    interval: 1000
    onTriggered:
    {
      printer.printWindow();
      printer.endPrinting();
      startPrinting.text = "done";
    }
  }
}
