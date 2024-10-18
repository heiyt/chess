//
// Created by heiyt_R9000P on 24-10-14.
//

#ifndef CHINACHESS_BOARD_H
#define CHINACHESS_BOARD_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "T_ChineseChess/chinachess.h"

QT_BEGIN_NAMESPACE
namespace Ui { class board; }
QT_END_NAMESPACE

class board : public QWidget {
Q_OBJECT

public:
    explicit board(QWidget *parent = nullptr);
    ~board() override;
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

    ChinaChess chinaChess;
    int selected_id = 0;
    static void drawChess(QPainter &chess_painter, Chess chess);

private:
    Ui::board *ui;
    unsigned int playStep = 0;
    static void xy2cr(int x, int y, int &col, int &rol);
    static void cr2xy(int col, int row, int &x, int &y);
    bool is_ClickOnChess(QPoint qPoint, int &row, int &col, int &id);
    void after_selected_chess(int id);
    void flash_chess(int id);
    void show_destination(int id);
    void moveChess(int row, int col);
    void delete_selected_chess(int id);
    bool canEat(int id, int row, int col);
    void eat_chess(int id);
    bool canMove(int id, int row, int col);

    static bool SoldierWay(Chess chess, int row, int col);
    bool CannonWay(Chess chess, int row, int col);
    bool CarWay(Chess chess, int row, int col);
    bool HorseWay(Chess chess, int row, int col);
    bool ElephantWay(Chess chess, int row, int col);
    static bool GuardWay(Chess chess, int row, int col);
    static bool GeneralWay(Chess chess, int row, int col);
};

#endif //CHINACHESS_BOARD_H
