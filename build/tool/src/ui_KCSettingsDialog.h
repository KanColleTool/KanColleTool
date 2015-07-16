/********************************************************************************
** Form generated from reading UI file 'KCSettingsDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KCSETTINGSDIALOG_H
#define UI_KCSETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KCSettingsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *minimizeToTrayContainer;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *minimizeToTrayCheckbox;
    QFrame *line;
    QCheckBox *translationCheckbox;
    QLabel *label;
    QFrame *line_4;
    QCheckBox *notifyCheckbox;
    QWidget *notifyContainer;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *notifyRepairsCheckbox;
    QCheckBox *notifyConstructionCheckbox;
    QCheckBox *notifyExpeditionCheckbox;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *notifyExpeditionReminderCheckbox;
    QSpinBox *notifyExpeditionReminderInterval;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_2;
    QWidget *notifyExpeditionReminderContainer;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *notifyExpeditionReminderRepeatCheckbox;
    QSpinBox *notifyExpeditionReminderRepeatInterval;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_3;
    QWidget *notifyExpeditionReminderRepeatContainer;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *notifyExpeditionReminderSuspendCheckbox;
    QSpinBox *notifyExpeditionReminderSuspendInterval;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_8;
    QWidget *notificationSystemContainer;
    QVBoxLayout *verticalLayout_8;
    QFrame *line_2;
    QLabel *label_2;
    QRadioButton *notificationBackendDefaultRadio;
    QLabel *label_3;
    QRadioButton *notificationBackendGrowlRadio;
    QLabel *label_5;
    QSpacerItem *verticalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *KCSettingsDialog)
    {
        if (KCSettingsDialog->objectName().isEmpty())
            KCSettingsDialog->setObjectName(QStringLiteral("KCSettingsDialog"));
        KCSettingsDialog->setWindowModality(Qt::WindowModal);
        KCSettingsDialog->resize(781, 528);
        verticalLayout = new QVBoxLayout(KCSettingsDialog);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        minimizeToTrayContainer = new QWidget(KCSettingsDialog);
        minimizeToTrayContainer->setObjectName(QStringLiteral("minimizeToTrayContainer"));
        verticalLayout_4 = new QVBoxLayout(minimizeToTrayContainer);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        minimizeToTrayCheckbox = new QCheckBox(minimizeToTrayContainer);
        minimizeToTrayCheckbox->setObjectName(QStringLiteral("minimizeToTrayCheckbox"));

        verticalLayout_3->addWidget(minimizeToTrayCheckbox);

        line = new QFrame(minimizeToTrayContainer);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line);


        verticalLayout_4->addLayout(verticalLayout_3);


        verticalLayout->addWidget(minimizeToTrayContainer);

        translationCheckbox = new QCheckBox(KCSettingsDialog);
        translationCheckbox->setObjectName(QStringLiteral("translationCheckbox"));

        verticalLayout->addWidget(translationCheckbox);

        label = new QLabel(KCSettingsDialog);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        label->setFont(font);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(label);

        line_4 = new QFrame(KCSettingsDialog);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_4);

        notifyCheckbox = new QCheckBox(KCSettingsDialog);
        notifyCheckbox->setObjectName(QStringLiteral("notifyCheckbox"));

        verticalLayout->addWidget(notifyCheckbox);

        notifyContainer = new QWidget(KCSettingsDialog);
        notifyContainer->setObjectName(QStringLiteral("notifyContainer"));
        verticalLayout_2 = new QVBoxLayout(notifyContainer);
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(20, 0, 0, 0);
        notifyRepairsCheckbox = new QCheckBox(notifyContainer);
        notifyRepairsCheckbox->setObjectName(QStringLiteral("notifyRepairsCheckbox"));

        verticalLayout_2->addWidget(notifyRepairsCheckbox);

        notifyConstructionCheckbox = new QCheckBox(notifyContainer);
        notifyConstructionCheckbox->setObjectName(QStringLiteral("notifyConstructionCheckbox"));

        verticalLayout_2->addWidget(notifyConstructionCheckbox);

        notifyExpeditionCheckbox = new QCheckBox(notifyContainer);
        notifyExpeditionCheckbox->setObjectName(QStringLiteral("notifyExpeditionCheckbox"));

        verticalLayout_2->addWidget(notifyExpeditionCheckbox);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(2);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        notifyExpeditionReminderCheckbox = new QCheckBox(notifyContainer);
        notifyExpeditionReminderCheckbox->setObjectName(QStringLiteral("notifyExpeditionReminderCheckbox"));

        horizontalLayout_2->addWidget(notifyExpeditionReminderCheckbox);

        notifyExpeditionReminderInterval = new QSpinBox(notifyContainer);
        notifyExpeditionReminderInterval->setObjectName(QStringLiteral("notifyExpeditionReminderInterval"));
        notifyExpeditionReminderInterval->setMaximum(86400);

        horizontalLayout_2->addWidget(notifyExpeditionReminderInterval);

        label_4 = new QLabel(notifyContainer);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_7->addLayout(horizontalLayout_2);

        notifyExpeditionReminderContainer = new QWidget(notifyContainer);
        notifyExpeditionReminderContainer->setObjectName(QStringLiteral("notifyExpeditionReminderContainer"));
        verticalLayout_5 = new QVBoxLayout(notifyExpeditionReminderContainer);
        verticalLayout_5->setSpacing(2);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(20, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        notifyExpeditionReminderRepeatCheckbox = new QCheckBox(notifyExpeditionReminderContainer);
        notifyExpeditionReminderRepeatCheckbox->setObjectName(QStringLiteral("notifyExpeditionReminderRepeatCheckbox"));

        horizontalLayout_3->addWidget(notifyExpeditionReminderRepeatCheckbox);

        notifyExpeditionReminderRepeatInterval = new QSpinBox(notifyExpeditionReminderContainer);
        notifyExpeditionReminderRepeatInterval->setObjectName(QStringLiteral("notifyExpeditionReminderRepeatInterval"));
        notifyExpeditionReminderRepeatInterval->setMaximum(86400);

        horizontalLayout_3->addWidget(notifyExpeditionReminderRepeatInterval);

        label_6 = new QLabel(notifyExpeditionReminderContainer);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_3->addWidget(label_6);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_5->addLayout(horizontalLayout_3);

        notifyExpeditionReminderRepeatContainer = new QWidget(notifyExpeditionReminderContainer);
        notifyExpeditionReminderRepeatContainer->setObjectName(QStringLiteral("notifyExpeditionReminderRepeatContainer"));
        verticalLayout_6 = new QVBoxLayout(notifyExpeditionReminderRepeatContainer);
        verticalLayout_6->setSpacing(5);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(20, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        notifyExpeditionReminderSuspendCheckbox = new QCheckBox(notifyExpeditionReminderRepeatContainer);
        notifyExpeditionReminderSuspendCheckbox->setObjectName(QStringLiteral("notifyExpeditionReminderSuspendCheckbox"));

        horizontalLayout_4->addWidget(notifyExpeditionReminderSuspendCheckbox);

        notifyExpeditionReminderSuspendInterval = new QSpinBox(notifyExpeditionReminderRepeatContainer);
        notifyExpeditionReminderSuspendInterval->setObjectName(QStringLiteral("notifyExpeditionReminderSuspendInterval"));
        notifyExpeditionReminderSuspendInterval->setMaximum(86400);

        horizontalLayout_4->addWidget(notifyExpeditionReminderSuspendInterval);

        label_7 = new QLabel(notifyExpeditionReminderRepeatContainer);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_4->addWidget(label_7);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_6->addLayout(horizontalLayout_4);

        label_8 = new QLabel(notifyExpeditionReminderRepeatContainer);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout_6->addWidget(label_8);


        verticalLayout_5->addWidget(notifyExpeditionReminderRepeatContainer);


        verticalLayout_7->addWidget(notifyExpeditionReminderContainer);


        verticalLayout_2->addLayout(verticalLayout_7);


        verticalLayout->addWidget(notifyContainer);

        notificationSystemContainer = new QWidget(KCSettingsDialog);
        notificationSystemContainer->setObjectName(QStringLiteral("notificationSystemContainer"));
        verticalLayout_8 = new QVBoxLayout(notificationSystemContainer);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        line_2 = new QFrame(notificationSystemContainer);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_8->addWidget(line_2);

        label_2 = new QLabel(notificationSystemContainer);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_8->addWidget(label_2);

        notificationBackendDefaultRadio = new QRadioButton(notificationSystemContainer);
        notificationBackendDefaultRadio->setObjectName(QStringLiteral("notificationBackendDefaultRadio"));
        notificationBackendDefaultRadio->setChecked(true);

        verticalLayout_8->addWidget(notificationBackendDefaultRadio);

        label_3 = new QLabel(notificationSystemContainer);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setIndent(20);

        verticalLayout_8->addWidget(label_3);

        notificationBackendGrowlRadio = new QRadioButton(notificationSystemContainer);
        notificationBackendGrowlRadio->setObjectName(QStringLiteral("notificationBackendGrowlRadio"));

        verticalLayout_8->addWidget(notificationBackendGrowlRadio);

        label_5 = new QLabel(notificationSystemContainer);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setIndent(20);

        verticalLayout_8->addWidget(label_5);


        verticalLayout->addWidget(notificationSystemContainer);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer_2);

        buttonBox = new QDialogButtonBox(KCSettingsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(KCSettingsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), KCSettingsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), KCSettingsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(KCSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *KCSettingsDialog)
    {
        KCSettingsDialog->setWindowTitle(QApplication::translate("KCSettingsDialog", "Settings", 0));
        minimizeToTrayCheckbox->setText(QApplication::translate("KCSettingsDialog", "Keep running in the system tray when closed", 0));
        translationCheckbox->setText(QApplication::translate("KCSettingsDialog", "Enable English Translation", 0));
        label->setText(QApplication::translate("KCSettingsDialog", "Translation provided by Commie.\n"
"If you would like to provide an alternate translation, contact us and we'll work something out.", 0));
        notifyCheckbox->setText(QApplication::translate("KCSettingsDialog", "Notify me...", 0));
        notifyRepairsCheckbox->setText(QApplication::translate("KCSettingsDialog", "...when a reparation finishes", 0));
        notifyConstructionCheckbox->setText(QApplication::translate("KCSettingsDialog", "...when a construction finishes", 0));
        notifyExpeditionCheckbox->setText(QApplication::translate("KCSettingsDialog", "...when an expedition finishes", 0));
        notifyExpeditionReminderCheckbox->setText(QApplication::translate("KCSettingsDialog", "...when I haven't had an expedition out for:", 0));
        label_4->setText(QApplication::translate("KCSettingsDialog", " minutes", 0));
        notifyExpeditionReminderRepeatCheckbox->setText(QApplication::translate("KCSettingsDialog", "...and repeat every:", 0));
        label_6->setText(QApplication::translate("KCSettingsDialog", " minutes", 0));
        notifyExpeditionReminderSuspendCheckbox->setText(QApplication::translate("KCSettingsDialog", "...but only when something has happened in the last:", 0));
        label_7->setText(QApplication::translate("KCSettingsDialog", " minutes", 0));
        label_8->setText(QApplication::translate("KCSettingsDialog", "The last part is recommended if you enable periodic reminders, otherwise they risk becoming a bother.\n"
"\"something has happened\" = \"data has been received from the viewer, or a notification has been shown\".", 0));
        label_2->setText(QApplication::translate("KCSettingsDialog", "Notification System", 0));
        notificationBackendDefaultRadio->setText(QApplication::translate("KCSettingsDialog", "Default", 0));
        label_3->setText(QApplication::translate("KCSettingsDialog", "<html><head/><body><p>The system's default notification system:<br/><span style=\" font-weight:600;\">Mac</span>: Notification Center<br/><span style=\" font-weight:600;\">Windows</span>: Tray Bubbles<br/><span style=\" font-weight:600;\">Linux</span>: libnotify</p></body></html>", 0));
        notificationBackendGrowlRadio->setText(QApplication::translate("KCSettingsDialog", "Growl", 0));
        label_5->setText(QApplication::translate("KCSettingsDialog", "<html><head/><body><p>The third party Growl notification system. Requires manual installation.<br/>Recommended on Windows, a matter of taste on Mac.</p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class KCSettingsDialog: public Ui_KCSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KCSETTINGSDIALOG_H
