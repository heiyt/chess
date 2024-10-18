#include <QApplication>
#include "board.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    board b;
    b.setFixedSize(500, 550);
    b.setWindowTitle("象棋");
    b.show();
    return QApplication::exec();
}
