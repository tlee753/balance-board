/********************************************************************************
** Form generated from reading UI file 'wii-balance.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WII_2D_BALANCE_H
#define UI_WII_2D_BALANCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WiiBalance
{
public:
    QAction *actionClose;
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QFrame *line;
    QFrame *line_2;

    void setupUi(QMainWindow *WiiBalance)
    {
        if (WiiBalance->objectName().isEmpty())
            WiiBalance->setObjectName(QString::fromUtf8("WiiBalance"));
        WiiBalance->resize(840, 640);
        WiiBalance->setAutoFillBackground(false);
        actionClose = new QAction(WiiBalance);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        centralWidget = new QWidget(WiiBalance);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(20, 20, 800, 600));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(20, 315, 800, 10));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(1);
        line->setFrameShape(QFrame::HLine);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(415, 20, 10, 600));
        line_2->setFrameShadow(QFrame::Plain);
        line_2->setLineWidth(1);
        line_2->setFrameShape(QFrame::VLine);
        WiiBalance->setCentralWidget(centralWidget);

        retranslateUi(WiiBalance);

        QMetaObject::connectSlotsByName(WiiBalance);
    } // setupUi

    void retranslateUi(QMainWindow *WiiBalance)
    {
        WiiBalance->setWindowTitle(QCoreApplication::translate("WiiBalance", "WiiBalance", nullptr));
        actionClose->setText(QCoreApplication::translate("WiiBalance", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WiiBalance: public Ui_WiiBalance {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WII_2D_BALANCE_H
