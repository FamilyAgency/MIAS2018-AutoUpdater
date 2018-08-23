import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3


ApplicationWindow
{
    visible: true;
    width: 800;
    height: 800;
    title: qsTr("Auto updater");
    flags:  Qt.SplashScreen;


    property int marginLeft: 50;
    property int marginTop: 50;
    property int columnShift: 400;

   Image
   {
       source: "qrc:/resources/UpdaterBG.png";
   }

    UpdaterService
    {
        x:marginLeft;
        y:marginTop * 4;
    }

    ProcessService
    {
        x:marginLeft;
        y:marginTop;
    }

    ServiceButtons
    {
        x:marginLeft;
        y:marginTop * 10;
    }

    Button
    {
        id:closeBtn;
        implicitWidth:100;
        implicitHeight: 100;
        anchors.top: parent.top;
        anchors.right: parent.right;
        contentItem: Text
        {
            id: closeItem;
            z: 1;
            text:"Exit";
            font.pixelSize: 15;
            color: "#ffffff";
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        Rectangle
        {
            anchors.fill: parent;
            color: "#a2a8be";
        }
        enabled: true;
        onClicked:
        {
            Qt.quit();
        }
    }

    LoadingScreen
    {

    }




}
