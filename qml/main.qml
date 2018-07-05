import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3


ApplicationWindow
{
    visible: true;
    width: 800;
    height: 600;
    title: qsTr("Auto updater");

    property int marginLeft: 50;
    property int marginTop: 50;
    property int columnShift: 400;

    UpdaterService
    {
        x:marginLeft;
        y:marginTop * 6;
    }

    ProcessService
    {
        x:marginLeft;
        y:marginTop;
    }
}
