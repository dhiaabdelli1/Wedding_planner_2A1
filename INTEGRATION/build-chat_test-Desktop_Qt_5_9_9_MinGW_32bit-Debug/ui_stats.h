/********************************************************************************
** Form generated from reading UI file 'stats.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATS_H
#define UI_STATS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_stats
{
public:
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *tabWidget_pie;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_3;
    QFrame *horizontalFrame_sticks;
    QHBoxLayout *horizontalLayout;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_5;
    QFrame *horizontalFrame_pie;
    QHBoxLayout *horizontalLayout_4;

    void setupUi(QDialog *stats)
    {
        if (stats->objectName().isEmpty())
            stats->setObjectName(QStringLiteral("stats"));
        stats->resize(703, 521);
        horizontalLayout_2 = new QHBoxLayout(stats);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        tabWidget_pie = new QTabWidget(stats);
        tabWidget_pie->setObjectName(QStringLiteral("tabWidget_pie"));
        tabWidget_pie->setStyleSheet(QLatin1String("QTabWidget:pane {\n"
"border:4px;\n"
"background-color:#DEA5A4;\n"
"\n"
"\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"color:  rgb(255, 255, 255);\n"
"background-color:rgb(127, 60, 55);\n"
"font: 8pt \"Forte\";\n"
"}\n"
"\n"
"QTabBar::tab:!selected {\n"
"color: rgb(255,255,255);\n"
"background-color:  rgb(255, 117, 117);\n"
"font: 8pt \"Forte\";\n"
"\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
"\n"
""));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        horizontalLayout_3 = new QHBoxLayout(tab);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalFrame_sticks = new QFrame(tab);
        horizontalFrame_sticks->setObjectName(QStringLiteral("horizontalFrame_sticks"));
        horizontalLayout = new QHBoxLayout(horizontalFrame_sticks);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

        horizontalLayout_3->addWidget(horizontalFrame_sticks);

        tabWidget_pie->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        horizontalLayout_5 = new QHBoxLayout(tab_2);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalFrame_pie = new QFrame(tab_2);
        horizontalFrame_pie->setObjectName(QStringLiteral("horizontalFrame_pie"));
        horizontalLayout_4 = new QHBoxLayout(horizontalFrame_pie);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));

        horizontalLayout_5->addWidget(horizontalFrame_pie);

        tabWidget_pie->addTab(tab_2, QString());

        horizontalLayout_2->addWidget(tabWidget_pie);


        retranslateUi(stats);

        tabWidget_pie->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(stats);
    } // setupUi

    void retranslateUi(QDialog *stats)
    {
        stats->setWindowTitle(QApplication::translate("stats", "Dialog", Q_NULLPTR));
        tabWidget_pie->setTabText(tabWidget_pie->indexOf(tab), QApplication::translate("stats", "Sticks", Q_NULLPTR));
        tabWidget_pie->setTabText(tabWidget_pie->indexOf(tab_2), QApplication::translate("stats", "Pie Chart", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class stats: public Ui_stats {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATS_H
