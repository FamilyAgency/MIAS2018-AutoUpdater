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

        Button
        {
            id:startBtn;
            implicitWidth: 200;
            implicitHeight: 50;
            contentItem: Text
            {
                id: textItem;
                z: 1;
                text:"Start explorer";
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
                processService.startExplorer();
            }
        }

        Button
        {
            id:keyboardBtn;
            implicitWidth: 200;
            implicitHeight: 50;
            contentItem: Text
            {
                id: keyboardItem;
                z: 1;
                text:"Start keyborad";
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
                processService.showKeyboard();
            }
        }
    }

}
