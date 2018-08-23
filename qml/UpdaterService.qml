import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick 2.2
import QtQuick.Controls.Styles 1.1

Item
{
    ColumnLayout
    {
        spacing: 10;

        //        Text
        //        {
        //            text: "Updater data";
        //            font.family: "Helvetica";
        //            font.pixelSize: 17;
        //            color: "#000099";
        //        }

        //        Text
        //        {
        //            text: "Last update: " + updaterService.updateConfig.lastUpdateDate;
        //            font.family: "Helvetica";
        //            font.pixelSize: 15;
        //            color: "#999999";
        //            visible: false;
        //        }

        Text
        {
            text: "Config version: " + standData.mainConfig.version;
            font.family: "Helvetica";
            font.pixelSize: 20;
            color: "#009900";
        }

        Text
        {
            text: "Time to next check: " + updaterService.timeToUpdate;
            font.family: "Helvetica";
            font.pixelSize: 20;
            color: "#999999";
        }

        //        CheckBox
        //        {
        //            implicitWidth: 200;
        //            text: "Auto check";
        //            checked: updaterService.updateConfig.autocheck;
        //            onCheckStateChanged:
        //            {
        //                updaterService.autoCheckChanged(checked);
        //            }
        //        }

        Button
        {
            implicitWidth: 200;
            implicitHeight: 50;
            opacity: enabled ? 1 : 0.2;


            contentItem: Text
            {
                id: btnItem;
                z: 1;
                text:"Check now";
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
            onClicked:
            {
                updaterService.forceCheckUpdate();
            }
        }

        Text
        {
            text: "Has new version: " + updaterService.needUpdate;
            color: updaterService.needUpdate ? "#009900" : "#990000";
            font.family: "Helvetica";
            font.pixelSize: 15;
        }

        Button
        {
            implicitWidth: 200;
            implicitHeight: 50;
            opacity: enabled ? 1 : 0.2;


            contentItem: Text
            {
                id: updateItem;
                z: 1;
                text: "Start Update";
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
            enabled: updaterService.needUpdate;


            onClicked:
            {
                updaterService.forceStartUpdate();
            }
        }
    }
}
