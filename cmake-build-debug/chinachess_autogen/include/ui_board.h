/********************************************************************************
** Form generated from reading UI file 'board.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOARD_H
#define UI_BOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_board
{
public:

    void setupUi(QWidget *board)
    {
        if (board->objectName().isEmpty())
            board->setObjectName("board");
        board->setWindowModality(Qt::WindowModality::ApplicationModal);
        board->resize(500, 550);
        board->setMinimumSize(QSize(500, 550));
        board->setMaximumSize(QSize(500, 16777215));

        retranslateUi(board);

        QMetaObject::connectSlotsByName(board);
    } // setupUi

    void retranslateUi(QWidget *board)
    {
        board->setWindowTitle(QCoreApplication::translate("board", "board", nullptr));
    } // retranslateUi

};

namespace Ui {
    class board: public Ui_board {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOARD_H
