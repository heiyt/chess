//
// Created by heiyt_R9000P on 24-10-14.
//

// You may need to build the project (run Qt uic code generator) to get "ui_board.h" resolved

#include "board.h"
#include "ui_board.h"

board::board(QWidget *parent) : QWidget(parent), ui(new Ui::board) {
    ui->setupUi(this);
    playStep = 1;
}
board::~board() {
    delete ui;
}
void board::paintEvent(QPaintEvent *event) {
    // 画棋盘
    QPainter board_painter(this);
    for (int i = 0; i < 10; i++) {
        board_painter.drawLine(50, 50 * i + 50, 450, 50 * i + 50);
    }
    for (int i = 0; i < 9; i++) {
        board_painter.drawLine(50 * i + 50, 50, 50 * i + 50, 250);
    }
    for (int i = 0; i < 9; i++) {
        board_painter.drawLine(50 * i + 50, 300, 50 * i + 50, 500);
    }
    board_painter.drawLine(50, 250, 50, 300);
    board_painter.drawLine(450, 250, 450, 300);
    // 四条斜线
    board_painter.drawLine(200, 50, 300, 150);
    board_painter.drawLine(300, 50, 200, 150);
    board_painter.drawLine(200, 400, 300, 500);
    board_painter.drawLine(300, 400, 200, 500);
    // 画棋子
    for (const auto & chess : chinaChess.chesses) {
        drawChess(board_painter,chess);
    }
}
void board::drawChess(QPainter &chess_painter,Chess chess) {
    if (chess.is_died) {
        return;
    }
    int x,y;
    cr2xy(chess.col, chess.row, x, y);
    QString chess_name;
    QPen ppp;
    QRect rect = QRect(x - 23, y - 23, 46, 46);
    ppp.setWidth(3);
    if(chess.player == RED_PLAYER) {
        ppp.setColor(Qt::red);
    } else {
        ppp.setColor(Qt::black);
    }
    chess_painter.setBrush(QBrush(Qt::yellow));
    chess_painter.setPen(ppp);
    chess_painter.drawEllipse(x - 23, y - 23, 46, 46);
    switch (chess.chessPiece) {
        case SOLDIER:chess_name = "兵";break;
        case CANNON:chess_name = "炮";break;
        case CAR:chess_name = "车";break;
        case HORSE:chess_name = "马";break;
        case ELEPHANT:chess_name = "象";break;
        case GUARD:chess_name = "士";break;
        case GENERAL:chess_name = "将";break;
    }
    chess_painter.setFont(QFont("宋体", 20, QFont::Bold));
    chess_painter.drawText(rect, chess_name, QTextOption(Qt::AlignCenter));
}
void board::mousePressEvent(QMouseEvent *event) {
    if(event->button() != Qt::LeftButton) {
        return;
    }
    int row = 0, col = 0, id = 0;
    if (is_ClickOnChess(event->pos(), row, col, id)) {
        // 如果点击的是棋子
        if (selected_id == id) {
            // 取消选中棋子
            selected_id = 0;
            delete_selected_chess(id);
            qDebug() <<"取消选中"<< chinaChess.chesses[id - 1].player << " " << chinaChess.chesses[id - 1].chessPiece;
        } else if ((chinaChess.chesses[selected_id - 1].player == chinaChess.chesses[id - 1].player ||
                   selected_id == 0)) {
            // 选中棋子
            if (playStep % 2 != 0 && chinaChess.chesses[id - 1].player == RED_PLAYER) {
                selected_id = id;
                after_selected_chess(id);
                qDebug() << "选中的是" << chinaChess.chesses[id - 1].player << " " << chinaChess.chesses[id - 1].chessPiece;
            }
            if (playStep % 2 == 0 && chinaChess.chesses[id - 1].player == BLACK_PLAYER) {
                selected_id = id;
                after_selected_chess(id);
                qDebug() << "选中的是" << chinaChess.chesses[id - 1].player << " " << chinaChess.chesses[id - 1].chessPiece;
            }
        } else if (canEat(selected_id, row, col)) {
            // 吃掉棋子
            eat_chess(id);
            moveChess(row, col);
            selected_id = 0;
        }
    } else {
        // 如果点击的是棋盘
        qDebug() << "board";
        if (selected_id != 0) {
            // 如果选中了棋子则移动棋子
            if (canMove(selected_id, row, col)) {
                moveChess(row, col);
            } else {
                qDebug() << "请移动到正确的位置";
            }
        }
    }
}
bool board::is_ClickOnChess(QPoint qPoint, int &row, int &col, int &id) {
    int qx, qy;
    qx = qPoint.x();
    qy = qPoint.y();
    xy2cr(qx, qy, col, row);
    if (qx % 50 > 25) {
        col = col + 1;
    }
    if (qy % 50 > 25) {
        row = row + 1;
    }
    for (auto & chess : chinaChess.chesses) {
        if (!chess.is_died) {
            if (chess.row == row && chess.col == col) {
                id = chess.id;
                return true;
            }
        }
    }
    return false;
}
void board::xy2cr(int x, int y, int &col, int &row) {
    col = x / 50;
    row = y / 50;
}
void board::cr2xy(int col, int row, int &x, int &y) {
    x = col * 50;
    y = row * 50;
}

// 移动棋子
void board::moveChess(int row,int col) {
    chinaChess.chesses[selected_id - 1].row = row;
    chinaChess.chesses[selected_id - 1].col = col;
    selected_id = 0;
    playStep++;
    update();
    qDebug() << "已经移动到正确位置";
}
void board::after_selected_chess(int id) {
    // 使选中的棋子闪烁
    flash_chess(id);
    // 在棋盘种显示选中的棋子可以移动到的位置
    show_destination(id);
}
// 使得选中的棋子闪烁
void board::flash_chess(int id) {

}
// 在棋盘上显示可以移动到的位置
void board::show_destination(int id) {
//    for (int i = 0; i < 10; i++) {
//        for (int j = 0; j < 9; j++) {
//            if (canMove(id, j, i)) {
//                cBoard[i][j] = true;
//            }
//        }
//    }
//    update();
}
// 取消选中棋子
void board::delete_selected_chess(int id) {

}

bool board::canEat(int id, int row, int col) {
    if (chinaChess.chesses[id-1].chessPiece != CANNON) {
        return canMove(id, row, col);
    } else {
        // 如果是炮，则需要特别判断
        return CannonWay(chinaChess.chesses[id - 1], row, col);
    }
}

void board::eat_chess(int id) {
    chinaChess.chesses[id - 1].is_died = true;
    chinaChess.chesses[id - 1].col = -1;
    chinaChess.chesses[id - 1].row = -1;
    if (chinaChess.chesses[id - 1].chessPiece == GENERAL) {
        qDebug() << !chinaChess.chesses[id - 1].player << "胜利！";
    }
}
bool board::canMove(int id,int row,int col) {
    // 移动的各种规则
    Chess chess = chinaChess.chesses[id - 1];
    // 超出棋盘范围就不管了
    if (row < 1 || col < 1 || row > 10 || col > 9) {
        return false;
    }
    // 将帅不能面对面
    int c = 0, cc = 0;
    if (chinaChess.chesses[30].col == chinaChess.chesses[31].col) {
        for (int i = 0; i < 30; i++) {
            if (chinaChess.chesses[i].col == chinaChess.chesses[30].col) {
                c++;
                cc = i;
            }
        }
        if (c == 1 && cc == id - 1 && chinaChess.chesses[cc].col != col) {
            return false;
        }
        if (c == 1 && (id == 31 || id == 32) && chinaChess.chesses[cc].row == row) {
            return false;
        }
    }
    switch (chess.chessPiece) {
        case SOLDIER:return SoldierWay(chess, row, col);
        case CANNON:return CannonWay(chess, row, col);
        case CAR:return CarWay(chess, row, col);
        case HORSE:return HorseWay(chess, row, col);
        case ELEPHANT:return ElephantWay(chess, row, col);
        case GUARD:return GuardWay(chess, row, col);
        case GENERAL:return GeneralWay(chess, row, col);
    }
    return false;
}

bool board::SoldierWay(Chess chess,int row,int col) {
    // 兵的规则
    if (chess.player == RED_PLAYER) {
        if (abs(row - chess.row) + abs(col - chess.col) == 1 && row <= chess.row) {
            if (row > 5 && row != chess.row - 1) {
                return false;
            }
            return true;
        }
    } else {
        if (abs(row - chess.row) + abs(col - chess.col) == 1 && row >= chess.row) {
            if (row < 6 && row != chess.row + 1) {
                return false;
            }
            return true;
        }
    }
    return false;
}
bool board::CannonWay(Chess chess, int row, int col) {
    if (row < 1 || col < 1 || row > 10 || col > 9) {
        return false;
    }
    int geShu = 0;
    if (chess.row == row && chess.col != col) {
        if (col > chess.col) {
            for (int i = 0; i < 32; i++) {
                if (chinaChess.chesses[i].id != chess.id && chinaChess.chesses[i].row == row && chinaChess.chesses[i].col > chess.col && chinaChess.chesses[i].col < col) {
                    geShu++;
                }
            }
        }
        if (col < chess.col) {
            for (int i = 0; i < 32; i++) {
                if (chinaChess.chesses[i].id != chess.id && chinaChess.chesses[i].row == row && chinaChess.chesses[i].col < chess.col && chinaChess.chesses[i].col > col) {
                    geShu++;                    }
            }
        }
    }
    if (chess.row != row && chess.col == col) {
        if (row > chess.row) {
            for (int i = 0; i < 32; i++) {
                if (chinaChess.chesses[i].id != chess.id && chinaChess.chesses[i].col == col && chinaChess.chesses[i].row > chess.row && chinaChess.chesses[i].row < row) {
                    geShu++;
                }
            }
        }
        if (row < chess.row) {
            for (int i = 0; i < 32; i++) {
                if (chinaChess.chesses[i].id != chess.id && chinaChess.chesses[i].col == col && chinaChess.chesses[i].row < chess.row && chinaChess.chesses[i].row > row) {
                    geShu++;
                }
            }
        }
    }
    if (geShu == 1) {
        for (int i = 0; i < 32; i++) {
            if (chinaChess.chesses[i].row == row && chinaChess.chesses[i].col == col) {
                return true;
            }
        }
        return false;
    }
    if (geShu == 0) {
        for (int i = 0; i < 32; i++) {
            if (chinaChess.chesses[i].row == row && chinaChess.chesses[i].col == col) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}
bool board::CarWay(Chess chess, int row, int col) {
    if (chess.row == row && chess.col != col) {
        if (col > chess.col) {
            for (int i = 0; i < 32; i++) {
                if (chinaChess.chesses[i].id !=chess.id && chinaChess.chesses[i].row == row && chinaChess.chesses[i].col > chess.col && chinaChess.chesses[i].col < col) {
                    return false;
                }
            }
            return true;
        }
        if (col < chess.col) {
            for (int i = 0; i < 32; i++) {
                if (chinaChess.chesses[i].id !=chess.id && chinaChess.chesses[i].row == row && chinaChess.chesses[i].col < chess.col && chinaChess.chesses[i].col > col) {
                    return false;
                }
            }
            return true;
        }
    }
    if (chess.row != row && chess.col == col) {
        if (row > chess.row) {
            for (int i = 0; i < 32; i++) {
                if (chinaChess.chesses[i].id !=chess.id && chinaChess.chesses[i].col == col && chinaChess.chesses[i].row > chess.row && chinaChess.chesses[i].row < row) {
                    return false;
                }
            }
            return true;
        }
        if (row < chess.row) {
            for (int i = 0; i < 32; i++) {
                if (chinaChess.chesses[i].id !=chess.id && chinaChess.chesses[i].col == col && chinaChess.chesses[i].row < chess.row && chinaChess.chesses[i].row > row) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}
bool board::HorseWay(Chess chess, int row, int col) {
    if (abs(chess.row - row) == 2 && abs(chess.col - col) == 1) {
        for (int i = 0; i < 32; i++) {
            if (chinaChess.chesses[i].id != chess.id && 2 * chinaChess.chesses[i].row == (row + chess.row) && chinaChess.chesses[i].col == chess.col) {
                return false;
            }
        }
        return true;
    }
    if (abs(chess.col - col) == 2 && abs(chess.row - row) == 1) {
        for (int i = 0; i < 32; i++) {
            if (chinaChess.chesses[i].id != chess.id && 2 * chinaChess.chesses[i].col == (col + chess.col) && chinaChess.chesses[i].row == chess.row) {
                return false;
            }
        }
        return true;
    }
    return false;
}
bool board::ElephantWay(Chess chess, int row, int col) {
    if ((chess.player == RED_PLAYER && row < 6) || (chess.player == BLACK_PLAYER && row > 5)) {
        return false;
    }
    if (abs(chess.row - row) == 2 && abs(chess.col - col) == 2) {
        for (int i = 0; i < 32; i++) {
            if ((2 * chinaChess.chesses[i].row == row + chess.row) && (2 * chinaChess.chesses[i].col == col + chess.col)) {
                return false;
            }
        }
        return true;
    }
    return false;
}
bool board::GuardWay(Chess chess, int row, int col) {
    if (chess.player == RED_PLAYER) {
        if (row < 8 || col < 4 || col > 6) {
            return false;
        }
    } else {
        if (row > 3 || col < 4 || col > 6) {
            return false;
        }
    }
    if (abs(chess.row - row) == 1 && abs(chess.col - col) == 1) {
        return true;
    }
    return false;
}
bool board::GeneralWay(Chess chess, int row, int col) {
    if (chess.player == RED_PLAYER) {
        if (row < 8 || col < 4 || col > 6) {
            return false;
        }
    } else {
        if (row > 3 || col < 4 || col > 6) {
            return false;
        }
    }
    if (abs(chess.row - row) + abs(chess.col - col) == 1) {
        return true;
    }
    return false;
}