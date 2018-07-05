import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import com.app 1.0

Item
{    
    ColumnLayout
    {
        spacing: 10;
        Text
        {
            text: "Process data";
            font.family: "Helvetica";
            font.pixelSize: 17;
            color: "#000099";
        }

        Text
        {
            id:processPath;
            text: "Process path: " + standData.mainConfig.workingDirectory + standData.mainConfig.folderSeparator + processService.processConfig.path;
            font.family: "Helvetica";
            font.pixelSize: 15;
            color: "#999999";
        }

        Text
        {
            text: "Autorun: " + processService.processConfig.autorun;
            font.family: "Helvetica";
            font.pixelSize: 15;
            color: "#999999";
        }


        Text
        {
            id: statusText
            text: "Status: stopped";
            font.family: "Helvetica";
            font.pixelSize: 15;
            color: "#990000";
        }

        Button
        {
            id:startBtn;
            implicitWidth: 200;
            text:"Start";
            enabled: true;
            onClicked:
            {
                processService.startApp();
            }
        }

        Button
        {
            id:stopBtn;
            implicitWidth: 200;
            text:"Stop";
            enabled: false;
            onClicked:
            {
                processService.stopApp();
            }
        }
    }

    Connections
    {
        target:processService;
        onProcessStateChanged:
        {
            switch (processService.processState)
            {

            case ProcessState.Stopped:
                stopBtn.enabled = false;
                startBtn.enabled = true;
                statusText.text = "Process stopped";
                statusText.color = "#990000";
                break;

            case ProcessState.PendingStart:
                stopBtn.enabled = false;
                startBtn.enabled = false;
                statusText.text = "Process starting.....";
                statusText.color = "#999900";
                break;

            case ProcessState.Running:
                stopBtn.enabled = true;
                startBtn.enabled = false;
                statusText.text = "Process running";
                statusText.color = "#009900";
                break;
            }
        }
    }
}
