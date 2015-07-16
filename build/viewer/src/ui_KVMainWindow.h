/********************************************************************************
** Form generated from reading UI file 'KVMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KVMAINWINDOW_H
#define UI_KVMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KVMainWindow
{
public:
    QAction *actionEnterAPILink;
    QAction *actionClearCache;
    QAction *actionReset;
    QAction *actionSettings;
    QAction *actionExit;
    QAction *actionAbout;
    QAction *actionCheckForUpdates;
    QAction *actionScreenshot;
    QAction *actionGetAPILink;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QMenuBar *menubar;
    QMenu *menuViewer;
    QMenu *menuHelp;

    void setupUi(QMainWindow *KVMainWindow)
    {
        if (KVMainWindow->objectName().isEmpty())
            KVMainWindow->setObjectName(QStringLiteral("KVMainWindow"));
        KVMainWindow->resize(800, 480);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(KVMainWindow->sizePolicy().hasHeightForWidth());
        KVMainWindow->setSizePolicy(sizePolicy);
        actionEnterAPILink = new QAction(KVMainWindow);
        actionEnterAPILink->setObjectName(QStringLiteral("actionEnterAPILink"));
        actionClearCache = new QAction(KVMainWindow);
        actionClearCache->setObjectName(QStringLiteral("actionClearCache"));
        actionReset = new QAction(KVMainWindow);
        actionReset->setObjectName(QStringLiteral("actionReset"));
        actionSettings = new QAction(KVMainWindow);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        actionExit = new QAction(KVMainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionAbout = new QAction(KVMainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionCheckForUpdates = new QAction(KVMainWindow);
        actionCheckForUpdates->setObjectName(QStringLiteral("actionCheckForUpdates"));
        actionScreenshot = new QAction(KVMainWindow);
        actionScreenshot->setObjectName(QStringLiteral("actionScreenshot"));
        actionGetAPILink = new QAction(KVMainWindow);
        actionGetAPILink->setObjectName(QStringLiteral("actionGetAPILink"));
        centralwidget = new QWidget(KVMainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        KVMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(KVMainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuViewer = new QMenu(menubar);
        menuViewer->setObjectName(QStringLiteral("menuViewer"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        KVMainWindow->setMenuBar(menubar);

        menubar->addAction(menuViewer->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuViewer->addAction(actionEnterAPILink);
        menuViewer->addAction(actionGetAPILink);
        menuViewer->addAction(actionClearCache);
        menuViewer->addAction(actionReset);
        menuViewer->addAction(actionScreenshot);
        menuViewer->addSeparator();
        menuViewer->addAction(actionSettings);
        menuViewer->addAction(actionExit);
        menuHelp->addAction(actionAbout);

        retranslateUi(KVMainWindow);

        QMetaObject::connectSlotsByName(KVMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *KVMainWindow)
    {
        KVMainWindow->setWindowTitle(QApplication::translate("KVMainWindow", "KanColleTool Viewer", 0));
        actionEnterAPILink->setText(QApplication::translate("KVMainWindow", "Enter API Link", 0));
        actionEnterAPILink->setShortcut(QApplication::translate("KVMainWindow", "Ctrl+L", 0));
        actionClearCache->setText(QApplication::translate("KVMainWindow", "Clear Cache", 0));
        actionReset->setText(QApplication::translate("KVMainWindow", "Reset", 0));
        actionSettings->setText(QApplication::translate("KVMainWindow", "Settings", 0));
        actionExit->setText(QApplication::translate("KVMainWindow", "Exit", 0));
        actionExit->setShortcut(QApplication::translate("KVMainWindow", "Ctrl+Q", 0));
        actionAbout->setText(QApplication::translate("KVMainWindow", "About", 0));
        actionCheckForUpdates->setText(QApplication::translate("KVMainWindow", "Check for Updates", 0));
        actionScreenshot->setText(QApplication::translate("KVMainWindow", "Screenshot", 0));
        actionScreenshot->setShortcut(QApplication::translate("KVMainWindow", "Ctrl+I", 0));
        actionGetAPILink->setText(QApplication::translate("KVMainWindow", "Get API Link", 0));
        menuViewer->setTitle(QApplication::translate("KVMainWindow", "Game", 0));
        menuHelp->setTitle(QApplication::translate("KVMainWindow", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class KVMainWindow: public Ui_KVMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KVMAINWINDOW_H
