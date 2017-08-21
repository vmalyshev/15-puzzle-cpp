import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

import Game.ua 1.0

Window {
    visible: true;
    width: 640;
    height: 480;
    title: qsTr("15 Puzzle");

    property int cellSize: height / gameFieldModel.fieldSize;

    GameModel {
        id: gameFieldModel;

        onUserWon: {
            gameFieldModel.shuffleCells();
            console.log("you win")
        }
    }

    Item {
        id: gameField
        width: parent.height;
        height: parent.height;

        GridView {
            id: gameBoard
            anchors.fill: parent;
            cellHeight: cellSize;
            cellWidth: cellSize;
            model: gameFieldModel;

            delegate: Cell {
                height: gameBoard.cellHeight;
                width: gameBoard.cellWidth;

                onItemSelected: {
                    gameFieldModel.checkNeighbours(num)
                }
            }

            move: Transition {
                NumberAnimation {
                    properties: "x,y";
                    duration: 100;
                }
            }
        }
    }

    Button {
        text: "shuffle"

        anchors {
            left: gameField.right
            right: parent.right
            margins: 10
        }

        onClicked: {
            gameFieldModel.shuffleCells();
        }
    }
}
