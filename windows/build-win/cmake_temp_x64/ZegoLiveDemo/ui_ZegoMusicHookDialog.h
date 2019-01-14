/********************************************************************************
** Form generated from reading UI file 'ZegoMusicHookDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZEGOMUSICHOOKDIALOG_H
#define UI_ZEGOMUSICHOOKDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ZegoImageButton.h"

QT_BEGIN_NAMESPACE

class Ui_ZegoMusicHookDialog
{
public:
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QWidget *m_zoneTitle;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_9;
    QLabel *m_lbTitle;
    QSpacerItem *horizontalSpacer_10;
    ZegoImageButton *m_bClose;
    QSpacerItem *verticalSpacer;
    QLabel *m_lbTitleMain;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_12;
    ZegoImageButton *m_bCloudNet;
    QSpacerItem *horizontalSpacer_13;
    QLabel *m_lbCloudNet;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_14;
    ZegoImageButton *m_bKuGou;
    QSpacerItem *horizontalSpacer_15;
    QLabel *m_lbKuGou;
    QSpacerItem *horizontalSpacer_6;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_16;
    ZegoImageButton *m_bQQMusic;
    QSpacerItem *horizontalSpacer_17;
    QLabel *m_lbQQMusic;
    QSpacerItem *horizontalSpacer_8;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_18;
    ZegoImageButton *m_bKuWo;
    QSpacerItem *horizontalSpacer_19;
    QLabel *m_lbKuWo;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_3;
    QLabel *m_lbTitleSub;
    QSpacerItem *verticalSpacer_4;
    QLineEdit *m_edAppPath;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *m_bOpenFile;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_bReject;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *m_bAccept;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_6;

    void setupUi(QDialog *ZegoMusicHookDialog)
    {
        if (ZegoMusicHookDialog->objectName().isEmpty())
            ZegoMusicHookDialog->setObjectName(QStringLiteral("ZegoMusicHookDialog"));
        ZegoMusicHookDialog->resize(700, 480);
        ZegoMusicHookDialog->setStyleSheet(QStringLiteral("background-color:#ffffff;"));
        verticalLayout_6 = new QVBoxLayout(ZegoMusicHookDialog);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        m_zoneTitle = new QWidget(ZegoMusicHookDialog);
        m_zoneTitle->setObjectName(QStringLiteral("m_zoneTitle"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_zoneTitle->sizePolicy().hasHeightForWidth());
        m_zoneTitle->setSizePolicy(sizePolicy);
        m_zoneTitle->setMinimumSize(QSize(0, 40));
        m_zoneTitle->setMaximumSize(QSize(16777215, 40));
        m_zoneTitle->setStyleSheet(QStringLiteral("background-color: #0e88eb;"));
        horizontalLayout_5 = new QHBoxLayout(m_zoneTitle);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_9 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);

        m_lbTitle = new QLabel(m_zoneTitle);
        m_lbTitle->setObjectName(QStringLiteral("m_lbTitle"));
        m_lbTitle->setStyleSheet(QString::fromUtf8("font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"	 font-size: 16px;\n"
"     color: #ffffff;"));

        horizontalLayout_4->addWidget(m_lbTitle);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_10);

        m_bClose = new ZegoImageButton(m_zoneTitle);
        m_bClose->setObjectName(QStringLiteral("m_bClose"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_bClose->sizePolicy().hasHeightForWidth());
        m_bClose->setSizePolicy(sizePolicy1);
        m_bClose->setMinimumSize(QSize(50, 40));
        m_bClose->setMaximumSize(QSize(50, 40));
        m_bClose->setStyleSheet(QLatin1String("QPushButton:!hover{\n"
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

        horizontalLayout_4->addWidget(m_bClose);


        horizontalLayout_5->addLayout(horizontalLayout_4);


        verticalLayout_5->addWidget(m_zoneTitle);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer);

        m_lbTitleMain = new QLabel(ZegoMusicHookDialog);
        m_lbTitleMain->setObjectName(QStringLiteral("m_lbTitleMain"));
        m_lbTitleMain->setStyleSheet(QString::fromUtf8("font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 20px;\n"
"color: #666666;"));
        m_lbTitleMain->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(m_lbTitleMain);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_2);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_12);

        m_bCloudNet = new ZegoImageButton(ZegoMusicHookDialog);
        m_bCloudNet->setObjectName(QStringLiteral("m_bCloudNet"));
        m_bCloudNet->setMinimumSize(QSize(80, 80));
        m_bCloudNet->setMaximumSize(QSize(80, 80));
        m_bCloudNet->setCursor(QCursor(Qt::PointingHandCursor));
        m_bCloudNet->setStyleSheet(QStringLiteral("border: none;"));
        m_bCloudNet->setIconSize(QSize(80, 80));

        horizontalLayout->addWidget(m_bCloudNet);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_13);


        verticalLayout->addLayout(horizontalLayout);

        m_lbCloudNet = new QLabel(ZegoMusicHookDialog);
        m_lbCloudNet->setObjectName(QStringLiteral("m_lbCloudNet"));
        m_lbCloudNet->setStyleSheet(QString::fromUtf8("font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 16px;\n"
"color: #666666;"));
        m_lbCloudNet->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(m_lbCloudNet);


        horizontalLayout_8->addLayout(verticalLayout);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_5);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_14);

        m_bKuGou = new ZegoImageButton(ZegoMusicHookDialog);
        m_bKuGou->setObjectName(QStringLiteral("m_bKuGou"));
        m_bKuGou->setMinimumSize(QSize(80, 80));
        m_bKuGou->setMaximumSize(QSize(80, 80));
        m_bKuGou->setCursor(QCursor(Qt::PointingHandCursor));
        m_bKuGou->setStyleSheet(QStringLiteral("border: none;"));
        m_bKuGou->setIconSize(QSize(80, 80));

        horizontalLayout_3->addWidget(m_bKuGou);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_15);


        verticalLayout_2->addLayout(horizontalLayout_3);

        m_lbKuGou = new QLabel(ZegoMusicHookDialog);
        m_lbKuGou->setObjectName(QStringLiteral("m_lbKuGou"));
        m_lbKuGou->setStyleSheet(QString::fromUtf8("font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 16px;\n"
"color: #666666;"));
        m_lbKuGou->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(m_lbKuGou);


        horizontalLayout_8->addLayout(verticalLayout_2);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_6);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_16);

        m_bQQMusic = new ZegoImageButton(ZegoMusicHookDialog);
        m_bQQMusic->setObjectName(QStringLiteral("m_bQQMusic"));
        m_bQQMusic->setMinimumSize(QSize(80, 80));
        m_bQQMusic->setMaximumSize(QSize(80, 80));
        m_bQQMusic->setCursor(QCursor(Qt::PointingHandCursor));
        m_bQQMusic->setStyleSheet(QStringLiteral("border: none;"));
        m_bQQMusic->setIconSize(QSize(80, 80));

        horizontalLayout_6->addWidget(m_bQQMusic);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_17);


        verticalLayout_3->addLayout(horizontalLayout_6);

        m_lbQQMusic = new QLabel(ZegoMusicHookDialog);
        m_lbQQMusic->setObjectName(QStringLiteral("m_lbQQMusic"));
        m_lbQQMusic->setStyleSheet(QString::fromUtf8("font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 16px;\n"
"color: #666666;"));
        m_lbQQMusic->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(m_lbQQMusic);


        horizontalLayout_8->addLayout(verticalLayout_3);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_8);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_18);

        m_bKuWo = new ZegoImageButton(ZegoMusicHookDialog);
        m_bKuWo->setObjectName(QStringLiteral("m_bKuWo"));
        m_bKuWo->setMinimumSize(QSize(80, 80));
        m_bKuWo->setMaximumSize(QSize(80, 80));
        m_bKuWo->setCursor(QCursor(Qt::PointingHandCursor));
        m_bKuWo->setStyleSheet(QStringLiteral("border: none;"));
        m_bKuWo->setIconSize(QSize(80, 80));

        horizontalLayout_7->addWidget(m_bKuWo);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_19);


        verticalLayout_4->addLayout(horizontalLayout_7);

        m_lbKuWo = new QLabel(ZegoMusicHookDialog);
        m_lbKuWo->setObjectName(QStringLiteral("m_lbKuWo"));
        m_lbKuWo->setStyleSheet(QString::fromUtf8("font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 16px;\n"
"color: #666666;"));
        m_lbKuWo->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(m_lbKuWo);


        horizontalLayout_8->addLayout(verticalLayout_4);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_7);


        verticalLayout_5->addLayout(horizontalLayout_8);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_3);

        m_lbTitleSub = new QLabel(ZegoMusicHookDialog);
        m_lbTitleSub->setObjectName(QStringLiteral("m_lbTitleSub"));
        m_lbTitleSub->setStyleSheet(QString::fromUtf8("font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 16px;\n"
"color: #666666;\n"
"padding-left: 20px;"));

        verticalLayout_5->addWidget(m_lbTitleSub);

        verticalSpacer_4 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_4);

        m_edAppPath = new QLineEdit(ZegoMusicHookDialog);
        m_edAppPath->setObjectName(QStringLiteral("m_edAppPath"));
        m_edAppPath->setMinimumSize(QSize(0, 32));
        m_edAppPath->setMaximumSize(QSize(16777215, 32));
        m_edAppPath->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"     margin-left: 20px;\n"
"     margin-right: 20px;\n"
"     padding-left: 10px;\n"
" }\n"
"\n"
" QLineEdit:!hover{\n"
"     border: 1px solid #e6e6e6;\n"
"     border-radius: 6px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #fdfdfd;\n"
"	 color: #666666;\n"
" }\n"
"\n"
" QLineEdit:hover:!focus{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 6px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #fdfdfd;\n"
"	 color: #666666;\n"
" }\n"
"\n"
" QLineEdit:focus{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 6px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #ffffff;\n"
" }"));

        verticalLayout_5->addWidget(m_edAppPath);

        verticalSpacer_5 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_11 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_11);

        m_bOpenFile = new QPushButton(ZegoMusicHookDialog);
        m_bOpenFile->setObjectName(QStringLiteral("m_bOpenFile"));
        m_bOpenFile->setMinimumSize(QSize(120, 32));
        m_bOpenFile->setMaximumSize(QSize(200, 32));
        m_bOpenFile->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"    padding-left: 10px;\n"
"    padding-right: 10px;\n"
"}\n"
"\n"
"QPushButton:!hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 border-radius: 2px;\n"
"     border: 1px solid #0e88eb;\n"
"     background-color: #ffffff;\n"
"     color: #0e88eb;\n"
" }\n"
"\n"
" QPushButton:hover:!pressed{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 border-radius: 2px;\n"
"     border: 1px solid #0e88eb;\n"
"     background-color: #0e88eb;\n"
"     color: #ffffff;\n"
" }\n"
"\n"
" QPushButton:hover:pressed{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 border-radius: 2px;\n"
"     border: 1px solid #0d80de;\n"
"     background-color: #0d80de;\n"
"     color: #ffffff;\n"
" }"));

        horizontalLayout_2->addWidget(m_bOpenFile);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        m_bReject = new QPushButton(ZegoMusicHookDialog);
        m_bReject->setObjectName(QStringLiteral("m_bReject"));
        m_bReject->setMinimumSize(QSize(120, 32));
        m_bReject->setMaximumSize(QSize(120, 32));
        m_bReject->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 border-radius: 2px;\n"
"     border: 1px solid #0e88eb;\n"
"     background-color: #ffffff;\n"
"     color: #0e88eb;\n"
" }\n"
"\n"
" QPushButton:hover:!pressed{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 border-radius: 2px;\n"
"     border: 1px solid #0e88eb;\n"
"     background-color: #0e88eb;\n"
"     color: #ffffff;\n"
" }\n"
"\n"
" QPushButton:hover:pressed{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 border-radius: 2px;\n"
"     border: 1px solid #0d80de;\n"
"     background-color: #0d80de;\n"
"     color: #ffffff;\n"
" }"));

        horizontalLayout_2->addWidget(m_bReject);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        m_bAccept = new QPushButton(ZegoMusicHookDialog);
        m_bAccept->setObjectName(QStringLiteral("m_bAccept"));
        m_bAccept->setMinimumSize(QSize(120, 32));
        m_bAccept->setMaximumSize(QSize(120, 32));
        m_bAccept->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 border-radius: 2px;\n"
"     border: 1px solid #0e88eb;\n"
"     background-color: #ffffff;\n"
"     color: #0e88eb;\n"
" }\n"
"\n"
" QPushButton:hover:!pressed{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 border-radius: 2px;\n"
"     border: 1px solid #0e88eb;\n"
"     background-color: #0e88eb;\n"
"     color: #ffffff;\n"
" }\n"
"\n"
" QPushButton:hover:pressed{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 border-radius: 2px;\n"
"     border: 1px solid #0d80de;\n"
"     background-color: #0d80de;\n"
"     color: #ffffff;\n"
" }"));

        horizontalLayout_2->addWidget(m_bAccept);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout_2);

        verticalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_6);


        verticalLayout_6->addLayout(verticalLayout_5);


        retranslateUi(ZegoMusicHookDialog);

        QMetaObject::connectSlotsByName(ZegoMusicHookDialog);
    } // setupUi

    void retranslateUi(QDialog *ZegoMusicHookDialog)
    {
        ZegoMusicHookDialog->setWindowTitle(QApplication::translate("ZegoMusicHookDialog", "Dialog", Q_NULLPTR));
        ZegoMusicHookDialog->setWindowFilePath(QString());
        m_lbTitle->setText(QApplication::translate("ZegoMusicHookDialog", "\351\200\211\346\213\251\346\267\267\351\237\263\346\226\271\345\274\217", Q_NULLPTR));
        m_bClose->setText(QString());
        m_lbTitleMain->setText(QApplication::translate("ZegoMusicHookDialog", "\350\257\267\351\200\211\346\213\251\351\237\263\351\242\221\350\275\257\344\273\266", Q_NULLPTR));
        m_bCloudNet->setText(QString());
        m_lbCloudNet->setText(QApplication::translate("ZegoMusicHookDialog", "\347\275\221\346\230\223\344\272\221\351\237\263\344\271\220", Q_NULLPTR));
        m_bKuGou->setText(QString());
        m_lbKuGou->setText(QApplication::translate("ZegoMusicHookDialog", "\351\205\267\347\213\227\351\237\263\344\271\220", Q_NULLPTR));
        m_bQQMusic->setText(QString());
        m_lbQQMusic->setText(QApplication::translate("ZegoMusicHookDialog", "QQ\351\237\263\344\271\220", Q_NULLPTR));
        m_bKuWo->setText(QString());
        m_lbKuWo->setText(QApplication::translate("ZegoMusicHookDialog", "\351\205\267\346\210\221\351\237\263\344\271\220", Q_NULLPTR));
        m_lbTitleSub->setText(QApplication::translate("ZegoMusicHookDialog", "\346\211\213\345\212\250\346\267\273\345\212\240\345\234\260\345\235\200\357\274\232", Q_NULLPTR));
        m_edAppPath->setPlaceholderText(QApplication::translate("ZegoMusicHookDialog", "\350\257\267\350\276\223\345\205\245\351\237\263\351\242\221\350\275\257\344\273\266\345\256\214\346\225\264\345\234\260\345\235\200(\345\214\205\345\220\253.exe)", Q_NULLPTR));
        m_bOpenFile->setText(QApplication::translate("ZegoMusicHookDialog", "\346\211\223\345\274\200\346\267\267\351\237\263\346\226\207\344\273\266", Q_NULLPTR));
        m_bReject->setText(QApplication::translate("ZegoMusicHookDialog", "\345\217\226\346\266\210", Q_NULLPTR));
        m_bAccept->setText(QApplication::translate("ZegoMusicHookDialog", "\347\241\256\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ZegoMusicHookDialog: public Ui_ZegoMusicHookDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZEGOMUSICHOOKDIALOG_H
