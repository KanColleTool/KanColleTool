/********************************************************************************
** Form generated from reading UI file 'KVSettingsDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KVSETTINGSDIALOG_H
#define UI_KVSETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KVSettingsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QCheckBox *translationCheckbox;
    QHBoxLayout *horizontalLayout;
    QCheckBox *reportUntranslatedCheckbox;
    QLabel *label;
    QWidget *windowsOnlyContainer;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_4;
    QFrame *line;
    QCheckBox *taskbarProgressCheckbox;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_2;
    QFrame *line_3;
    QCheckBox *uploadScreenshotsCheckbox;
    QWidget *screenshotsPathContainer;
    QGridLayout *gridLayout_2;
    QPushButton *openButton;
    QLineEdit *screenshotsPathEdit;
    QPushButton *browseButton;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *PngRadioButton;
    QRadioButton *JpegRadioButton;
    QSpacerItem *horizontalSpacer;
    QFrame *line_4;
    QCheckBox *cookieHackcheckBox;
    QLabel *label_8;
    QFrame *line_2;
    QCheckBox *proxyCheckbox;
    QWidget *proxyContainer;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QLineEdit *proxyPassEdit;
    QSpinBox *proxyPortBox;
    QLabel *label_7;
    QLabel *label_3;
    QLineEdit *proxyUserEdit;
    QLabel *label_4;
    QLabel *label_5;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *socksProxyRadio;
    QRadioButton *httpProxyRadio;
    QSpacerItem *verticalSpacer_3;
    QLineEdit *proxyServerEdit;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *KVSettingsDialog)
    {
        if (KVSettingsDialog->objectName().isEmpty())
            KVSettingsDialog->setObjectName(QStringLiteral("KVSettingsDialog"));
        KVSettingsDialog->setWindowModality(Qt::WindowModal);
        KVSettingsDialog->resize(693, 486);
        verticalLayout = new QVBoxLayout(KVSettingsDialog);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        translationCheckbox = new QCheckBox(KVSettingsDialog);
        translationCheckbox->setObjectName(QStringLiteral("translationCheckbox"));

        verticalLayout->addWidget(translationCheckbox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(20, -1, -1, -1);
        reportUntranslatedCheckbox = new QCheckBox(KVSettingsDialog);
        reportUntranslatedCheckbox->setObjectName(QStringLiteral("reportUntranslatedCheckbox"));

        horizontalLayout->addWidget(reportUntranslatedCheckbox);


        verticalLayout->addLayout(horizontalLayout);

        label = new QLabel(KVSettingsDialog);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(label);

        windowsOnlyContainer = new QWidget(KVSettingsDialog);
        windowsOnlyContainer->setObjectName(QStringLiteral("windowsOnlyContainer"));
        verticalLayout_2 = new QVBoxLayout(windowsOnlyContainer);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_2->addItem(verticalSpacer_4);

        line = new QFrame(windowsOnlyContainer);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        taskbarProgressCheckbox = new QCheckBox(windowsOnlyContainer);
        taskbarProgressCheckbox->setObjectName(QStringLiteral("taskbarProgressCheckbox"));

        verticalLayout_2->addWidget(taskbarProgressCheckbox);

        label_2 = new QLabel(windowsOnlyContainer);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        label_2->setTextFormat(Qt::RichText);

        verticalLayout_2->addWidget(label_2);


        verticalLayout->addWidget(windowsOnlyContainer);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer_2);

        line_3 = new QFrame(KVSettingsDialog);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        uploadScreenshotsCheckbox = new QCheckBox(KVSettingsDialog);
        uploadScreenshotsCheckbox->setObjectName(QStringLiteral("uploadScreenshotsCheckbox"));

        verticalLayout->addWidget(uploadScreenshotsCheckbox);

        screenshotsPathContainer = new QWidget(KVSettingsDialog);
        screenshotsPathContainer->setObjectName(QStringLiteral("screenshotsPathContainer"));
        gridLayout_2 = new QGridLayout(screenshotsPathContainer);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        openButton = new QPushButton(screenshotsPathContainer);
        openButton->setObjectName(QStringLiteral("openButton"));

        gridLayout_2->addWidget(openButton, 1, 2, 1, 1);

        screenshotsPathEdit = new QLineEdit(screenshotsPathContainer);
        screenshotsPathEdit->setObjectName(QStringLiteral("screenshotsPathEdit"));

        gridLayout_2->addWidget(screenshotsPathEdit, 1, 0, 1, 1);

        browseButton = new QPushButton(screenshotsPathContainer);
        browseButton->setObjectName(QStringLiteral("browseButton"));

        gridLayout_2->addWidget(browseButton, 1, 1, 1, 1);


        verticalLayout->addWidget(screenshotsPathContainer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        PngRadioButton = new QRadioButton(KVSettingsDialog);
        buttonGroup = new QButtonGroup(KVSettingsDialog);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(PngRadioButton);
        PngRadioButton->setObjectName(QStringLiteral("PngRadioButton"));
        PngRadioButton->setChecked(true);

        horizontalLayout_2->addWidget(PngRadioButton);

        JpegRadioButton = new QRadioButton(KVSettingsDialog);
        buttonGroup->addButton(JpegRadioButton);
        JpegRadioButton->setObjectName(QStringLiteral("JpegRadioButton"));

        horizontalLayout_2->addWidget(JpegRadioButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        line_4 = new QFrame(KVSettingsDialog);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_4);

        cookieHackcheckBox = new QCheckBox(KVSettingsDialog);
        cookieHackcheckBox->setObjectName(QStringLiteral("cookieHackcheckBox"));

        verticalLayout->addWidget(cookieHackcheckBox);

        label_8 = new QLabel(KVSettingsDialog);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout->addWidget(label_8);

        line_2 = new QFrame(KVSettingsDialog);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        proxyCheckbox = new QCheckBox(KVSettingsDialog);
        proxyCheckbox->setObjectName(QStringLiteral("proxyCheckbox"));

        verticalLayout->addWidget(proxyCheckbox);

        proxyContainer = new QWidget(KVSettingsDialog);
        proxyContainer->setObjectName(QStringLiteral("proxyContainer"));
        proxyContainer->setMinimumSize(QSize(0, 50));
        gridLayout = new QGridLayout(proxyContainer);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_6 = new QLabel(proxyContainer);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_6, 2, 2, 1, 1);

        proxyPassEdit = new QLineEdit(proxyContainer);
        proxyPassEdit->setObjectName(QStringLiteral("proxyPassEdit"));

        gridLayout->addWidget(proxyPassEdit, 2, 5, 1, 1);

        proxyPortBox = new QSpinBox(proxyContainer);
        proxyPortBox->setObjectName(QStringLiteral("proxyPortBox"));
        proxyPortBox->setMinimum(1);
        proxyPortBox->setMaximum(65535);

        gridLayout->addWidget(proxyPortBox, 1, 7, 1, 1);

        label_7 = new QLabel(proxyContainer);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        label_3 = new QLabel(proxyContainer);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        proxyUserEdit = new QLineEdit(proxyContainer);
        proxyUserEdit->setObjectName(QStringLiteral("proxyUserEdit"));

        gridLayout->addWidget(proxyUserEdit, 2, 1, 1, 1);

        label_4 = new QLabel(proxyContainer);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 6, 1, 1);

        label_5 = new QLabel(proxyContainer);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 2, 6, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        socksProxyRadio = new QRadioButton(proxyContainer);
        socksProxyRadio->setObjectName(QStringLiteral("socksProxyRadio"));
        socksProxyRadio->setChecked(true);

        verticalLayout_3->addWidget(socksProxyRadio);

        httpProxyRadio = new QRadioButton(proxyContainer);
        httpProxyRadio->setObjectName(QStringLiteral("httpProxyRadio"));

        verticalLayout_3->addWidget(httpProxyRadio);

        verticalSpacer_3 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);


        gridLayout->addLayout(verticalLayout_3, 2, 7, 2, 1);

        proxyServerEdit = new QLineEdit(proxyContainer);
        proxyServerEdit->setObjectName(QStringLiteral("proxyServerEdit"));

        gridLayout->addWidget(proxyServerEdit, 1, 1, 1, 5);


        verticalLayout->addWidget(proxyContainer);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(KVSettingsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(KVSettingsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), KVSettingsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), KVSettingsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(KVSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *KVSettingsDialog)
    {
        KVSettingsDialog->setWindowTitle(QApplication::translate("KVSettingsDialog", "Settings", 0));
        translationCheckbox->setText(QApplication::translate("KVSettingsDialog", "Enable English Translation", 0));
        reportUntranslatedCheckbox->setText(QApplication::translate("KVSettingsDialog", "Report untranslated lines", 0));
        label->setText(QApplication::translate("KVSettingsDialog", "Translation provided by Commie.\n"
"If you would like to provide an alternate translation, contact us and we'll work something out.", 0));
        taskbarProgressCheckbox->setText(QApplication::translate("KVSettingsDialog", "Enable Taskbar progress reporting", 0));
        label_2->setText(QApplication::translate("KVSettingsDialog", "This will display the game's loading progress in the Windows Taskbar.<br />This will be displayed every time the game loads <i>anything</i>, so disable it if it gets annoying.", 0));
        uploadScreenshotsCheckbox->setText(QApplication::translate("KVSettingsDialog", "Upload captured screenshots to Imgur (instead of saving to disk)", 0));
        openButton->setText(QApplication::translate("KVSettingsDialog", "Open folder", 0));
        browseButton->setText(QApplication::translate("KVSettingsDialog", "Browse", 0));
        PngRadioButton->setText(QApplication::translate("KVSettingsDialog", "PNG", 0));
        JpegRadioButton->setText(QApplication::translate("KVSettingsDialog", "JPEG", 0));
        cookieHackcheckBox->setText(QApplication::translate("KVSettingsDialog", "Enble cookie hack", 0));
        label_8->setText(QApplication::translate("KVSettingsDialog", "Allows you to get an API link without a VPN.<br />This is obviously unsupported, use on your own risk.", 0));
        proxyCheckbox->setText(QApplication::translate("KVSettingsDialog", "Enable proxy", 0));
        label_6->setText(QApplication::translate("KVSettingsDialog", "Password", 0));
        label_7->setText(QApplication::translate("KVSettingsDialog", "Username", 0));
        label_3->setText(QApplication::translate("KVSettingsDialog", "Server", 0));
        label_4->setText(QApplication::translate("KVSettingsDialog", "Port", 0));
        label_5->setText(QApplication::translate("KVSettingsDialog", "Type", 0));
        socksProxyRadio->setText(QApplication::translate("KVSettingsDialog", "SOCKS5", 0));
        httpProxyRadio->setText(QApplication::translate("KVSettingsDialog", "HTTP", 0));
    } // retranslateUi

};

namespace Ui {
    class KVSettingsDialog: public Ui_KVSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KVSETTINGSDIALOG_H
