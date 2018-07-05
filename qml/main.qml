import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3


ApplicationWindow
{
    visible: true
    width: 1280
    height: 720
    title: qsTr("Auto updater")

    property int marginLeft:50;
    property int marginTop:10;
    property int columnShift:400;

    UpdaterService
    {
        x:marginLeft;
        y:marginTop;
    }

    ProcessService
    {
        x:marginLeft * 7;
        y:marginTop;
    }
}
