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
                text: "Process data";
                font.family: "Helvetica"
                font.pixelSize: 17
                color: "#000099"
            }

            Text
            {
                text: "Porocess path: ";// + userData.exist;
                font.family: "Helvetica"
                font.pixelSize: 15
                color: "#999999"
            }

            Text
            {
                text: "Status: ";// + userData.firstTime;
                font.family: "Helvetica"
                font.pixelSize: 15
                color: "#999999"
            }

            Button
            {
                implicitWidth: 200;
                text:"Start";
                onClicked:
                {
                    processService.startApp();
                }
            }

            Button
            {
                implicitWidth: 200;
                text:"Stop";
                onClicked:
                {
                    processService.stopApp();
                }
            }
        }
    }
}
