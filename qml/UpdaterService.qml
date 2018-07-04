import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4

Item {

    Frame
    {
        ColumnLayout
        {
            spacing: 10;
            Text
            {
                text: "Updater data";
                font.family: "Helvetica";
                font.pixelSize: 17;
                color: "#000099";
            }

            Text
            {
                text: "Last update: " + updaterService.updateConfig.lastUpdateDate;
                font.family: "Helvetica";
                font.pixelSize: 15;
                color: "#999999";
                visible: false;
            }

            Text
            {
                text: "Config version: " + standData.config.version;
                font.family: "Helvetica";
                font.pixelSize: 15;
                color: "#999999";
            }

            Text
            {
                text: "Time to next check: " + updaterService.timeToUpdate;
                font.family: "Helvetica";
                font.pixelSize: 15;
                color: "#999999";
            }

            Text
            {
                text: "Status: checking";
                font.family: "Helvetica";
                font.pixelSize: 15;
                color: "#999999";
            }

            CheckBox
            {
                implicitWidth: 200;
                text: "Auto check";
                checked: updaterService.updateConfig.autocheck;
            }

            Button
            {
                implicitWidth: 200;
                text:"Check now";
                onClicked:
                {
                   updaterService.checkUpdate();
                }
            }

            Text
            {
                text: "Need update: " + updaterService.needUpdate;
                color: updaterService.needUpdate ? "#009900" : "#990000";
                font.family: "Helvetica";
                font.pixelSize: 15;
            }

            Button
            {
                implicitWidth: 200;
                text: "Start Update";
                enabled: updaterService.needUpdate;

                onClicked:
                {

                }
            }

        }
    }
}
