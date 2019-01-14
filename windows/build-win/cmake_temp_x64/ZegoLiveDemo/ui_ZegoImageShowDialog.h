/********************************************************************************
** Form generated from reading UI file 'ZegoImageShowDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZEGOIMAGESHOWDIALOG_H
#define UI_ZEGOIMAGESHOWDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <ZegoImageButton.h>

QT_BEGIN_NAMESPACE

class Ui_ZegoImageShowDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QWidget *m_zoneTitle;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_lbRoomName;
    QHBoxLayout *horizontalLayout;
    ZegoImageButton *m_bMin;
    ZegoImageButton *m_bClose;
    QLabel *m_ImageShowLabel;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_bQuit;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *m_bSave;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *ZegoImageShowDialog)
    {
        if (ZegoImageShowDialog->objectName().isEmpty())
            ZegoImageShowDialog->setObjectName(QStringLiteral("ZegoImageShowDialog"));
        ZegoImageShowDialog->resize(640, 490);
        ZegoImageShowDialog->setMinimumSize(QSize(640, 490));
        ZegoImageShowDialog->setMaximumSize(QSize(960, 670));
        verticalLayout_2 = new QVBoxLayout(ZegoImageShowDialog);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        m_zoneTitle = new QWidget(ZegoImageShowDialog);
        m_zoneTitle->setObjectName(QStringLiteral("m_zoneTitle"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_zoneTitle->sizePolicy().hasHeightForWidth());
        m_zoneTitle->setSizePolicy(sizePolicy);
        m_zoneTitle->setMinimumSize(QSize(0, 40));
        m_zoneTitle->setMaximumSize(QSize(16777215, 40));
        m_zoneTitle->setStyleSheet(QStringLiteral("background-color: #0e88eb;"));
        horizontalLayout_2 = new QHBoxLayout(m_zoneTitle);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        m_lbRoomName = new QLabel(m_zoneTitle);
        m_lbRoomName->setObjectName(QStringLiteral("m_lbRoomName"));
        m_lbRoomName->setStyleSheet(QString::fromUtf8("padding-left: 20px;\n"
"font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 14px;\n"
"color: #ffffff;\n"
"border: none;"));

        horizontalLayout_2->addWidget(m_lbRoomName);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, -1, -1, -1);
        m_bMin = new ZegoImageButton(m_zoneTitle);
        m_bMin->setObjectName(QStringLiteral("m_bMin"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_bMin->sizePolicy().hasHeightForWidth());
        m_bMin->setSizePolicy(sizePolicy1);
        m_bMin->setMinimumSize(QSize(30, 40));
        m_bMin->setMaximumSize(QSize(30, 40));
        m_bMin->setFocusPolicy(Qt::NoFocus);
        m_bMin->setStyleSheet(QLatin1String("QPushButton{\n"
"    border: 1px solid #0e88eb;\n"
"    background-color: #0e88eb;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"    border: 1px solid #0d80de;\n"
"    background-color: #0d80de;\n"
"}\n"
"\n"
"QPushButton:hover:pressed{\n"
"    border: 1px solid #0d79d1;\n"
"    background-color: #0d79d1;\n"
"}"));
        m_bMin->setFlat(true);

        horizontalLayout->addWidget(m_bMin);

        m_bClose = new ZegoImageButton(m_zoneTitle);
        m_bClose->setObjectName(QStringLiteral("m_bClose"));
        m_bClose->setEnabled(true);
        sizePolicy1.setHeightForWidth(m_bClose->sizePolicy().hasHeightForWidth());
        m_bClose->setSizePolicy(sizePolicy1);
        m_bClose->setMinimumSize(QSize(30, 40));
        m_bClose->setMaximumSize(QSize(30, 40));
        m_bClose->setFocusPolicy(Qt::NoFocus);
        m_bClose->setLayoutDirection(Qt::LeftToRight);
        m_bClose->setStyleSheet(QLatin1String("QPushButton{\n"
"    border: 1px solid #0e88eb;\n"
"    background-color: #0e88eb;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"    border: 1px solid #0d80de;\n"
"    background-color: #0d80de;\n"
"}\n"
"\n"
"QPushButton:hover:pressed{\n"
"    border: 1px solid #0d79d1;\n"
"    background-color: #0d79d1;\n"
"}"));
        m_bClose->setFlat(true);

        horizontalLayout->addWidget(m_bClose);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(m_zoneTitle);

        m_ImageShowLabel = new QLabel(ZegoImageShowDialog);
        m_ImageShowLabel->setObjectName(QStringLiteral("m_ImageShowLabel"));
        m_ImageShowLabel->setMinimumSize(QSize(640, 360));
        m_ImageShowLabel->setMaximumSize(QSize(960, 540));
        m_ImageShowLabel->setStyleSheet(QStringLiteral("background-color: #333333;"));
        m_ImageShowLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(m_ImageShowLabel);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        m_bQuit = new QPushButton(ZegoImageShowDialog);
        m_bQuit->setObjectName(QStringLiteral("m_bQuit"));
        m_bQuit->setMinimumSize(QSize(100, 30));
        m_bQuit->setMaximumSize(QSize(100, 30));
        m_bQuit->setStyleSheet(QString::fromUtf8("QPushButton:!enabled{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"     border: 1px solid #e6e6e6;\n"
"     border-radius: 2px;\n"
"     background-color: #ffffff;\n"
"     color: #e6e6e6;   \n"
"}\n"
"QPushButton:enabled:!hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     background-color: #ffffff;\n"
"     color: #0e88eb;   \n"
"}\n"
"\n"
"QPushButton:enabled:hover{\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     background-color: #0e88eb;\n"
"     color: #ffffff;   \n"
"}\n"
"\n"
"QPushButton:enabled:hover:pressed{\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     background-color: #0d8"
                        "0de;\n"
"     color: #ffffff;   \n"
"}"));

        horizontalLayout_3->addWidget(m_bQuit);

        horizontalSpacer_2 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        m_bSave = new QPushButton(ZegoImageShowDialog);
        m_bSave->setObjectName(QStringLiteral("m_bSave"));
        m_bSave->setMinimumSize(QSize(100, 30));
        m_bSave->setMaximumSize(QSize(100, 30));
        m_bSave->setStyleSheet(QString::fromUtf8("QPushButton:!enabled{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"     border: 1px solid #e6e6e6;\n"
"     border-radius: 2px;\n"
"     background-color: #ffffff;\n"
"     color: #e6e6e6;   \n"
"}\n"
"QPushButton:enabled:!hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     background-color: #ffffff;\n"
"     color: #0e88eb;   \n"
"}\n"
"\n"
"QPushButton:enabled:hover{\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     background-color: #0e88eb;\n"
"     color: #ffffff;   \n"
"}\n"
"\n"
"QPushButton:enabled:hover:pressed{\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     background-color: #0d8"
                        "0de;\n"
"     color: #ffffff;   \n"
"}"));

        horizontalLayout_3->addWidget(m_bSave);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(ZegoImageShowDialog);

        QMetaObject::connectSlotsByName(ZegoImageShowDialog);
    } // setupUi

    void retranslateUi(QDialog *ZegoImageShowDialog)
    {
        ZegoImageShowDialog->setWindowTitle(QApplication::translate("ZegoImageShowDialog", "Dialog", Q_NULLPTR));
        m_lbRoomName->setText(QApplication::translate("ZegoImageShowDialog", "\346\210\252\345\233\276\347\273\223\346\236\234", Q_NULLPTR));
        m_bMin->setText(QString());
        m_bClose->setText(QString());
        m_ImageShowLabel->setText(QString());
        m_bQuit->setText(QApplication::translate("ZegoImageShowDialog", "\345\217\226\346\266\210", Q_NULLPTR));
        m_bSave->setText(QApplication::translate("ZegoImageShowDialog", "\344\277\235\345\255\230", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ZegoImageShowDialog: public Ui_ZegoImageShowDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZEGOIMAGESHOWDIALOG_H
