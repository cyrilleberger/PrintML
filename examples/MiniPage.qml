import QtQuick 2.0
import QtQuick.Window 2.0
import org.storyml.print 1.0

Item {
  width: 200
  height: 200

  Printer
  {
    id: printer
    window: printwindow
    filename: "testprint.pdf"
    pageSize.pageSizeId: PageSize.A0
    orientation: Printer.Landscape
    miniPage.rows: 2
    miniPage.columns: 3
    miniPage.margin: 10
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
      for(var i = 0; i <4; ++i)
      {
        printer.printWindow();
        printer.newPage();
      }
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
      for(var i = 0; i <4; ++i)
      {
        printer.printWindow();
        printer.newPage();
      }
      printer.endPrinting();
      startPrinting.text = "done";
    }
  }
}
