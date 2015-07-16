/********************************************************************************
** Form generated from reading UI file 'KCShipDetailsDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KCSHIPDETAILSDIALOG_H
#define UI_KCSHIPDETAILSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_KCShipDetailsDialog
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *KCShipDetailsDialog)
    {
        if (KCShipDetailsDialog->objectName().isEmpty())
            KCShipDetailsDialog->setObjectName(QStringLiteral("KCShipDetailsDialog"));
        KCShipDetailsDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(KCShipDetailsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(KCShipDetailsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), KCShipDetailsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), KCShipDetailsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(KCShipDetailsDialog);
    } // setupUi

    void retranslateUi(QDialog *KCShipDetailsDialog)
    {
        KCShipDetailsDialog->setWindowTitle(QApplication::translate("KCShipDetailsDialog", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class KCShipDetailsDialog: public Ui_KCShipDetailsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KCSHIPDETAILSDIALOG_H
