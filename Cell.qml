import QtQuick 2.0

Item {
    signal itemSelected(int num)

    Rectangle {
        id: fgrFont

        anchors.fill: parent
        border.color: Qt.lighter(color)

        Text {
            id: cellValue
            anchors.fill: parent

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            color: "yellow"
            font.pixelSize: 20

            Component.onCompleted: {
                cellValue.text = (value === 0 ? '' : model.value);
            }
        }

        Component.onCompleted: {
           fgrFont.color = (value === 0 ? 'transparent': 'green');
        }

        MouseArea {
            anchors.fill: parent

            onClicked: {
                itemSelected(model.index);
            }
        }

    }
}
