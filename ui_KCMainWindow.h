/********************************************************************************
** Form generated from reading UI file 'KCMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KCMAINWINDOW_H
#define UI_KCMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KCMainWindow
{
public:
    QAction *actionShipdex;
    QAction *actionLaunchGame;
    QAction *actionSettings;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *shipsTab;
    QHBoxLayout *horizontalLayout;
    QTreeWidget *treeWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_5;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_6;
    QFrame *line_2;
    QWidget *widget_3;
    QGridLayout *gridLayout;
    QLabel *label_10;
    QLabel *label_13;
    QLabel *label_25;
    QLabel *label_18;
    QLabel *label_17;
    QLabel *label_15;
    QLabel *label_28;
    QLabel *label_19;
    QLabel *label_5;
    QLabel *label_12;
    QLabel *label_14;
    QLabel *label_11;
    QLabel *label_16;
    QLabel *label_20;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_21;
    QLabel *label_27;
    QLabel *label_26;
    QLabel *label_29;
    QLabel *label_30;
    QLabel *label_31;
    QLabel *label_4;
    QLabel *label_24;
    QFrame *line;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_9;
    QToolButton *toolButton;
    QWidget *craftingTab;
    QToolBar *toolBar;

    void setupUi(QMainWindow *KCMainWindow)
    {
        if (KCMainWindow->objectName().isEmpty())
            KCMainWindow->setObjectName(QStringLiteral("KCMainWindow"));
        KCMainWindow->resize(600, 365);
        actionShipdex = new QAction(KCMainWindow);
        actionShipdex->setObjectName(QStringLiteral("actionShipdex"));
        actionLaunchGame = new QAction(KCMainWindow);
        actionLaunchGame->setObjectName(QStringLiteral("actionLaunchGame"));
        actionSettings = new QAction(KCMainWindow);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        centralWidget = new QWidget(KCMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setDocumentMode(true);
        shipsTab = new QWidget();
        shipsTab->setObjectName(QStringLiteral("shipsTab"));
        horizontalLayout = new QHBoxLayout(shipsTab);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(12, -1, 12, 12);
        treeWidget = new QTreeWidget(shipsTab);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setMaximumSize(QSize(200, 16777215));
        treeWidget->header()->setVisible(false);

        horizontalLayout->addWidget(treeWidget);

        widget = new QWidget(shipsTab);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(5);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, 0);
        widget_4 = new QWidget(widget_2);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_4->sizePolicy().hasHeightForWidth());
        widget_4->setSizePolicy(sizePolicy1);
        verticalLayout_3 = new QVBoxLayout(widget_4);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        QFont font;
        font.setItalic(false);
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout_3->addWidget(label_3);

        label_2 = new QLabel(widget_4);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setPointSize(35);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_3->addWidget(label_2);


        horizontalLayout_2->addWidget(widget_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        widget_5 = new QWidget(widget_2);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        formLayout_2 = new QFormLayout(widget_5);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 5, 0);
        label = new QLabel(widget_5);
        label->setObjectName(QStringLiteral("label"));
        QFont font2;
        font2.setPointSize(10);
        label->setFont(font2);
        label->setAlignment(Qt::AlignBottom|Qt::AlignRight|Qt::AlignTrailing);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        label_7 = new QLabel(widget_5);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font2);
        label_7->setAlignment(Qt::AlignBottom|Qt::AlignRight|Qt::AlignTrailing);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_7);

        label_8 = new QLabel(widget_5);
        label_8->setObjectName(QStringLiteral("label_8"));
        QFont font3;
        font3.setPointSize(20);
        font3.setBold(true);
        font3.setWeight(75);
        label_8->setFont(font3);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, label_8);

        label_6 = new QLabel(widget_5);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font3);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, label_6);


        horizontalLayout_2->addWidget(widget_5);


        verticalLayout_2->addWidget(widget_2);

        line_2 = new QFrame(widget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        gridLayout = new QGridLayout(widget_3);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(-1, 5, -1, 5);
        label_10 = new QLabel(widget_3);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 0, 3, 1, 1);

        label_13 = new QLabel(widget_3);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout->addWidget(label_13, 1, 2, 1, 1);

        label_25 = new QLabel(widget_3);
        label_25->setObjectName(QStringLiteral("label_25"));

        gridLayout->addWidget(label_25, 3, 2, 1, 1);

        label_18 = new QLabel(widget_3);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout->addWidget(label_18, 4, 1, 1, 1);

        label_17 = new QLabel(widget_3);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout->addWidget(label_17, 3, 1, 1, 1);

        label_15 = new QLabel(widget_3);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout->addWidget(label_15, 1, 4, 1, 1);

        label_28 = new QLabel(widget_3);
        label_28->setObjectName(QStringLiteral("label_28"));

        gridLayout->addWidget(label_28, 2, 4, 1, 1);

        label_19 = new QLabel(widget_3);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout->addWidget(label_19, 5, 1, 1, 1);

        label_5 = new QLabel(widget_3);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 0, 1, 1, 1);

        label_12 = new QLabel(widget_3);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout->addWidget(label_12, 1, 1, 1, 1);

        label_14 = new QLabel(widget_3);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout->addWidget(label_14, 1, 3, 1, 1);

        label_11 = new QLabel(widget_3);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 0, 4, 1, 1);

        label_16 = new QLabel(widget_3);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout->addWidget(label_16, 2, 1, 1, 1);

        label_20 = new QLabel(widget_3);
        label_20->setObjectName(QStringLiteral("label_20"));

        gridLayout->addWidget(label_20, 2, 3, 1, 1);

        label_22 = new QLabel(widget_3);
        label_22->setObjectName(QStringLiteral("label_22"));

        gridLayout->addWidget(label_22, 4, 3, 1, 1);

        label_23 = new QLabel(widget_3);
        label_23->setObjectName(QStringLiteral("label_23"));

        gridLayout->addWidget(label_23, 5, 3, 1, 1);

        label_21 = new QLabel(widget_3);
        label_21->setObjectName(QStringLiteral("label_21"));

        gridLayout->addWidget(label_21, 3, 3, 1, 1);

        label_27 = new QLabel(widget_3);
        label_27->setObjectName(QStringLiteral("label_27"));

        gridLayout->addWidget(label_27, 5, 2, 1, 1);

        label_26 = new QLabel(widget_3);
        label_26->setObjectName(QStringLiteral("label_26"));

        gridLayout->addWidget(label_26, 4, 2, 1, 1);

        label_29 = new QLabel(widget_3);
        label_29->setObjectName(QStringLiteral("label_29"));

        gridLayout->addWidget(label_29, 3, 4, 1, 1);

        label_30 = new QLabel(widget_3);
        label_30->setObjectName(QStringLiteral("label_30"));

        gridLayout->addWidget(label_30, 4, 4, 1, 1);

        label_31 = new QLabel(widget_3);
        label_31->setObjectName(QStringLiteral("label_31"));

        gridLayout->addWidget(label_31, 5, 4, 1, 1);

        label_4 = new QLabel(widget_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 0, 2, 1, 1);

        label_24 = new QLabel(widget_3);
        label_24->setObjectName(QStringLiteral("label_24"));

        gridLayout->addWidget(label_24, 2, 2, 1, 1);


        verticalLayout_2->addWidget(widget_3);

        line = new QFrame(widget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        widget_6 = new QWidget(widget);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        sizePolicy.setHeightForWidth(widget_6->sizePolicy().hasHeightForWidth());
        widget_6->setSizePolicy(sizePolicy);
        horizontalLayout_3 = new QHBoxLayout(widget_6);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_9 = new QLabel(widget_6);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_3->addWidget(label_9);

        toolButton = new QToolButton(widget_6);
        toolButton->setObjectName(QStringLiteral("toolButton"));

        horizontalLayout_3->addWidget(toolButton);


        verticalLayout_2->addWidget(widget_6);


        horizontalLayout->addWidget(widget);

        tabWidget->addTab(shipsTab, QString());
        craftingTab = new QWidget();
        craftingTab->setObjectName(QStringLiteral("craftingTab"));
        tabWidget->addTab(craftingTab, QString());

        verticalLayout->addWidget(tabWidget);

        KCMainWindow->setCentralWidget(centralWidget);
        toolBar = new QToolBar(KCMainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setMovable(false);
        toolBar->setFloatable(false);
        KCMainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionLaunchGame);
        toolBar->addSeparator();
        toolBar->addAction(actionShipdex);
        toolBar->addAction(actionSettings);

        retranslateUi(KCMainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(KCMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *KCMainWindow)
    {
        KCMainWindow->setWindowTitle(QApplication::translate("KCMainWindow", "KCMainWindow", 0));
        actionShipdex->setText(QApplication::translate("KCMainWindow", "Shipdex", 0));
        actionLaunchGame->setText(QApplication::translate("KCMainWindow", "Launch Game", 0));
        actionSettings->setText(QApplication::translate("KCMainWindow", "Settings", 0));
        label_3->setText(QApplication::translate("KCMainWindow", "\343\201\246\343\202\223\343\202\212\343\202\205\343\201\206", 0));
        label_2->setText(QApplication::translate("KCMainWindow", "\345\244\251\351\276\215", 0));
        label->setText(QApplication::translate("KCMainWindow", "LVL", 0));
        label_7->setText(QApplication::translate("KCMainWindow", "COND", 0));
        label_8->setText(QApplication::translate("KCMainWindow", "49", 0));
        label_6->setText(QApplication::translate("KCMainWindow", "22", 0));
        label_10->setText(QApplication::translate("KCMainWindow", "Firepower", 0));
        label_13->setText(QApplication::translate("KCMainWindow", "42", 0));
        label_25->setText(QApplication::translate("KCMainWindow", "0", 0));
        label_18->setText(QApplication::translate("KCMainWindow", "Speed", 0));
        label_17->setText(QApplication::translate("KCMainWindow", "Aircraft", 0));
        label_15->setText(QApplication::translate("KCMainWindow", "55", 0));
        label_28->setText(QApplication::translate("KCMainWindow", "23", 0));
        label_19->setText(QApplication::translate("KCMainWindow", "Range", 0));
        label_5->setText(QApplication::translate("KCMainWindow", "HP", 0));
        label_12->setText(QApplication::translate("KCMainWindow", "Armor", 0));
        label_14->setText(QApplication::translate("KCMainWindow", "Torpedo", 0));
        label_11->setText(QApplication::translate("KCMainWindow", "36", 0));
        label_16->setText(QApplication::translate("KCMainWindow", "Evasion", 0));
        label_20->setText(QApplication::translate("KCMainWindow", "Anti-Air", 0));
        label_22->setText(QApplication::translate("KCMainWindow", "Line of Sight", 0));
        label_23->setText(QApplication::translate("KCMainWindow", "Luck", 0));
        label_21->setText(QApplication::translate("KCMainWindow", "Anti-Sub", 0));
        label_27->setText(QApplication::translate("KCMainWindow", "-", 0));
        label_26->setText(QApplication::translate("KCMainWindow", "-", 0));
        label_29->setText(QApplication::translate("KCMainWindow", "34", 0));
        label_30->setText(QApplication::translate("KCMainWindow", "18", 0));
        label_31->setText(QApplication::translate("KCMainWindow", "12", 0));
        label_4->setText(QApplication::translate("KCMainWindow", "40", 0));
        label_24->setText(QApplication::translate("KCMainWindow", "50", 0));
        label_9->setText(QApplication::translate("KCMainWindow", "Remodels at Level 20", 0));
        toolButton->setText(QApplication::translate("KCMainWindow", "View Shipdex Data", 0));
        tabWidget->setTabText(tabWidget->indexOf(shipsTab), QApplication::translate("KCMainWindow", "Ships", 0));
        tabWidget->setTabText(tabWidget->indexOf(craftingTab), QApplication::translate("KCMainWindow", "Crafting", 0));
        toolBar->setWindowTitle(QApplication::translate("KCMainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class KCMainWindow: public Ui_KCMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KCMAINWINDOW_H
