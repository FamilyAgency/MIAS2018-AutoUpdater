import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item
{
    anchors.fill: parent;
    visible : false;

    Rectangle
    {
        anchors.fill: parent;
        opacity: 0.6;
        color: "#ffffff";
    }

    Button
    {
        anchors.fill: parent;
        opacity: 0;
    }

    ProgressBar
    {
        id:meditationProgressBar;
        value: updaterService.updatePercent;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        style: ProgressBarStyle
        {
            background: Rectangle
            {
                radius: 2;
                color: "lightgray";
                border.color: "gray";
                border.width: 1;
                implicitWidth: 500;
                implicitHeight: 60;
            }

            progress: Rectangle
            {
                color: "#000099";
                border.color: "steelblue";
            }
        }
    }

    Connections
    {
        target: updaterService;
        onLoadingStarted:
        {
            visible = true;
        }

        onUpdateComplete:
        {
            visible = false;
            updaterService.updatePercent = 0;
        }
    }
}
