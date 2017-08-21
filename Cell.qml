import QtQuick 2.0

Item {
    signal itemSelected(int num);

    Rectangle {
        id: rect;
        anchors.fill: parent;

        border.color: Qt.lighter(color);

        Text {
            id: cellValue;
            anchors.fill: parent;

            font.pixelSize: 20

            color: "yellow"

            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;

            Component.onCompleted: {
                cellValue.text = (value === 0 ? '' : model.value);
            }
        }

        Component.onCompleted: {
           rect.color = (value === 0 ? 'transparent': 'green');
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                itemSelected(model.index);
            }
        }

    }
}
