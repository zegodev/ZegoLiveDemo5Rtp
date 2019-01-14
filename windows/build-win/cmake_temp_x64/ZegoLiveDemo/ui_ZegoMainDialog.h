/********************************************************************************
** Form generated from reading UI file 'ZegoMainDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZEGOMAINDIALOG_H
#define UI_ZEGOMAINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <ZegoComboBox.h>
#include <ZegoProgressIndicator.h>
#include <ZegoSwitchButton.h>
#include "ZegoImageButton.h"
#include "ZegoRoomList.h"
#include "ZegoSlider.h"
#include "ZegoStateButton.h"

QT_BEGIN_NAMESPACE

class Ui_ZegoMainDialog
{
public:
    QVBoxLayout *verticalLayout_6;
    QWidget *m_zoneTitle;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_lbTitle;
    QFrame *m_lineVer;
    QLabel *m_lbTitleVersion;
    QSpacerItem *horizontalSpacer_34;
    ZegoImageButton *m_bJumpToNet;
    ZegoImageButton *m_bMin;
    ZegoImageButton *m_bClose;
    QHBoxLayout *horizontalLayout_4;
    QWidget *m_zoneCreateRoom;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QLabel *m_lbCreateRoom;
    QSpacerItem *verticalSpacer;
    QLabel *m_lbName;
    QSpacerItem *verticalSpacer_2;
    QLineEdit *m_edRoomName;
    QSpacerItem *verticalSpacer_3;
    QLabel *m_lbMode;
    QSpacerItem *verticalSpacer_4;
    QGridLayout *gridLayout;
    QPushButton *m_bMixMode;
    QPushButton *m_bSingleMode;
    QPushButton *m_bMultiMode;
    QPushButton *m_bPublish2StreamMode;
    QSpacerItem *verticalSpacer_5;
    QFrame *m_lineBeforeCreate;
    QPushButton *m_bCreateRoom;
    QVBoxLayout *verticalLayout;
    QWidget *m_zoneRoomList;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *m_TitleList;
    QSpacerItem *horizontalSpacer_30;
    ZegoProgressIndicator *m_progIndicator;
    ZegoImageButton *m_bRefreshRoomList;
    QSpacerItem *horizontalSpacer_31;
    ZegoRoomList *m_roomList;
    QFrame *m_lineSpread;
    QWidget *m_zoneSettings;
    QVBoxLayout *verticalLayout_7;
    QTabWidget *m_tabSettings;
    QWidget *m_tabVideoConfig;
    QVBoxLayout *verticalLayout_16;
    QFrame *m_lineVideoConfig;
    QFrame *m_lineLongVideoConfig;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout_14;
    QSpacerItem *verticalSpacer_19;
    QPushButton *m_bExtremelyHigh;
    QPushButton *m_bSuperHigh;
    QPushButton *m_bHigh;
    QPushButton *m_bStandard;
    QPushButton *m_bLow;
    QPushButton *m_bSuperLow;
    QPushButton *m_bCustom;
    QSpacerItem *horizontalSpacer_6;
    QVBoxLayout *verticalLayout_15;
    QSpacerItem *verticalSpacer_12;
    QHBoxLayout *horizontalLayout_6;
    QLabel *m_lbResolution;
    QLabel *m_lbValueResolution;
    QSpacerItem *verticalSpacer_13;
    QHBoxLayout *horizontalLayout_8;
    ZegoStateButton *m_bResolutionDown;
    ZegoSlider *m_sliderResolution;
    ZegoStateButton *m_bResolutionUp;
    QSpacerItem *verticalSpacer_14;
    QHBoxLayout *horizontalLayout_9;
    QLabel *m_lbFPS;
    QLabel *m_lbValueFPS;
    QSpacerItem *verticalSpacer_15;
    QHBoxLayout *horizontalLayout_10;
    ZegoStateButton *m_bFPSDown;
    ZegoSlider *m_sliderFPS;
    ZegoStateButton *m_bFPSUp;
    QSpacerItem *verticalSpacer_16;
    QHBoxLayout *horizontalLayout_11;
    QLabel *m_lbBitrate;
    QLabel *m_lbValueBitrate;
    QSpacerItem *verticalSpacer_17;
    QHBoxLayout *horizontalLayout_12;
    ZegoStateButton *m_bBitrateDown;
    ZegoSlider *m_sliderBitrate;
    ZegoStateButton *m_bBitrateUp;
    QSpacerItem *verticalSpacer_18;
    QSpacerItem *horizontalSpacer_7;
    QWidget *m_tabExtraSettings;
    QVBoxLayout *verticalLayout_22;
    QFrame *m_lineExtraSettings;
    QFrame *m_lineLongExtraSettings;
    QHBoxLayout *horizontalLayout_27;
    QSpacerItem *horizontalSpacer_15;
    QVBoxLayout *verticalLayout_17;
    QSpacerItem *verticalSpacer_21;
    QLabel *m_lbEnvironment;
    QSpacerItem *verticalSpacer_22;
    QHBoxLayout *horizontalLayout_14;
    QLabel *m_lbTestEnv;
    QSpacerItem *horizontalSpacer_8;
    ZegoSwitchButton *m_switchTestEnv;
    QSpacerItem *horizontalSpacer_28;
    QSpacerItem *verticalSpacer_23;
    ZegoComboBox *m_cbAppVersion;
    QSpacerItem *verticalSpacer_20;
    QHBoxLayout *horizontalLayout_33;
    QLabel *m_lbAPPID;
    QSpacerItem *horizontalSpacer_35;
    QLineEdit *m_strEdAPPID;
    QSpacerItem *verticalSpacer_24;
    QHBoxLayout *horizontalLayout_34;
    QLabel *m_lbAPPSign;
    QSpacerItem *horizontalSpacer_36;
    QLineEdit *m_strEdAPPSign;
    QSpacerItem *verticalSpacer_33;
    QSpacerItem *horizontalSpacer_17;
    QVBoxLayout *verticalLayout_21;
    QSpacerItem *verticalSpacer_25;
    QLabel *m_lbAdvanced;
    QSpacerItem *verticalSpacer_26;
    QHBoxLayout *horizontalLayout_24;
    QHBoxLayout *horizontalLayout_15;
    QLabel *m_lbCapture;
    QSpacerItem *horizontalSpacer_10;
    ZegoSwitchButton *m_switchCapture;
    QSpacerItem *horizontalSpacer_11;
    QHBoxLayout *horizontalLayout_16;
    QLabel *m_lbFilter;
    QSpacerItem *horizontalSpacer_12;
    ZegoSwitchButton *m_switchFilter;
    QSpacerItem *horizontalSpacer_13;
    QHBoxLayout *horizontalLayout_17;
    QLabel *m_lbVerticalCapture;
    QSpacerItem *horizontalSpacer_14;
    ZegoSwitchButton *m_switchVerticalCapture;
    QSpacerItem *verticalSpacer_27;
    QLabel *m_lbExtra;
    QSpacerItem *verticalSpacer_35;
    QHBoxLayout *horizontalLayout_25;
    QHBoxLayout *horizontalLayout_18;
    QLabel *m_lbSurfaceMerge;
    QSpacerItem *m_spacerSurfaceMergeMid;
    ZegoSwitchButton *m_switchSurfaceMerge;
    QSpacerItem *m_spacerSurfaceMergeRight;
    QHBoxLayout *horizontalLayout_19;
    QLabel *m_lbCameraRotation;
    QSpacerItem *horizontalSpacer_20;
    ZegoComboBox *m_cbRotation;
    QSpacerItem *horizontalSpacer_32;
    QSpacerItem *verticalSpacer_28;
    QHBoxLayout *horizontalLayout_26;
    QVBoxLayout *verticalLayout_18;
    QLabel *m_lbAudioLeft;
    QSpacerItem *verticalSpacer_29;
    QHBoxLayout *horizontalLayout_21;
    QLabel *m_lbReverb;
    QSpacerItem *horizontalSpacer_23;
    ZegoSwitchButton *m_switchReverb;
    QSpacerItem *horizontalSpacer_24;
    QVBoxLayout *verticalLayout_19;
    QSpacerItem *verticalSpacer_30;
    QHBoxLayout *horizontalLayout_22;
    QLabel *m_lbVirtualStereo;
    QSpacerItem *horizontalSpacer_25;
    ZegoSwitchButton *m_switchVirtualStereo;
    QSpacerItem *horizontalSpacer_27;
    QVBoxLayout *verticalLayout_20;
    QLabel *m_lbAudioRight;
    QSpacerItem *verticalSpacer_31;
    QHBoxLayout *horizontalLayout_23;
    QLabel *m_lbNational;
    QSpacerItem *horizontalSpacer_26;
    ZegoSwitchButton *m_switchNational;
    QSpacerItem *verticalSpacer_34;
    QSpacerItem *horizontalSpacer_16;
    QWidget *m_tabUserSettings;
    QVBoxLayout *verticalLayout_13;
    QFrame *m_lineUserSettings;
    QVBoxLayout *verticalLayout_12;
    QFrame *m_lineLongUserSettings;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_10;
    QSpacerItem *verticalSpacer_7;
    QLabel *m_lbAccount;
    QSpacerItem *verticalSpacer_10;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_31;
    QLabel *m_lbUserId;
    QSpacerItem *horizontalSpacer_18;
    QLineEdit *m_strEdUserId;
    QHBoxLayout *horizontalLayout_32;
    QLabel *m_lbUserName;
    QSpacerItem *horizontalSpacer_19;
    QLineEdit *m_strEdUserName;
    QSpacerItem *verticalSpacer_36;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_11;
    QSpacerItem *verticalSpacer_8;
    QLabel *m_lbEquipment;
    QSpacerItem *m_vSpacerUpper;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_28;
    QLabel *m_lbMircoPhone;
    QSpacerItem *horizontalSpacer_9;
    ZegoComboBox *m_cbMircoPhone;
    QSpacerItem *verticalSpacer_37;
    QHBoxLayout *horizontalLayout_29;
    QLabel *m_lbCamera;
    QSpacerItem *horizontalSpacer_29;
    ZegoComboBox *m_cbCamera;
    QSpacerItem *verticalSpacer_38;
    QHBoxLayout *horizontalLayout_30;
    QLabel *m_lbCamera2;
    QSpacerItem *horizontalSpacer_33;
    ZegoComboBox *m_cbCamera2;
    QSpacerItem *m_vSpacerBottom;
    QSpacerItem *verticalSpacer_9;
    QHBoxLayout *horizontalLayout_7;
    QLabel *m_lbVersion;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_bUploadLog;
    QSpacerItem *horizontalSpacer_2;
    QLabel *m_lbTips;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_32;

    void setupUi(QDialog *ZegoMainDialog)
    {
        if (ZegoMainDialog->objectName().isEmpty())
            ZegoMainDialog->setObjectName(QStringLiteral("ZegoMainDialog"));
        ZegoMainDialog->resize(940, 670);
        ZegoMainDialog->setStyleSheet(QStringLiteral("background-color: #ffffff;"));
        verticalLayout_6 = new QVBoxLayout(ZegoMainDialog);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        m_zoneTitle = new QWidget(ZegoMainDialog);
        m_zoneTitle->setObjectName(QStringLiteral("m_zoneTitle"));
        m_zoneTitle->setStyleSheet(QLatin1String("QWidget#m_zoneTitle{\n"
"	background-color: #0e88eb;\n"
" }"));
        horizontalLayout_3 = new QHBoxLayout(m_zoneTitle);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(20, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, 0, -1);
        m_lbTitle = new QLabel(m_zoneTitle);
        m_lbTitle->setObjectName(QStringLiteral("m_lbTitle"));
        m_lbTitle->setMinimumSize(QSize(0, 0));
        m_lbTitle->setMaximumSize(QSize(16777215, 16777215));
        m_lbTitle->setStyleSheet(QString::fromUtf8("QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"	 font-size: 16px;\n"
"     color: #ffffff;\n"
"     background-color: #0e88eb;\n"
" }"));

        horizontalLayout_2->addWidget(m_lbTitle);

        m_lineVer = new QFrame(m_zoneTitle);
        m_lineVer->setObjectName(QStringLiteral("m_lineVer"));
        m_lineVer->setMinimumSize(QSize(1, 20));
        m_lineVer->setMaximumSize(QSize(1, 20));
        m_lineVer->setFrameShape(QFrame::VLine);
        m_lineVer->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(m_lineVer);

        m_lbTitleVersion = new QLabel(m_zoneTitle);
        m_lbTitleVersion->setObjectName(QStringLiteral("m_lbTitleVersion"));
        m_lbTitleVersion->setMinimumSize(QSize(0, 40));
        m_lbTitleVersion->setMaximumSize(QSize(16777215, 40));
        m_lbTitleVersion->setStyleSheet(QString::fromUtf8("QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"	 font-size: 16px;\n"
"     color: #ffffff;\n"
"     background-color: #0e88eb;\n"
" }"));

        horizontalLayout_2->addWidget(m_lbTitleVersion);

        horizontalSpacer_34 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_34);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        m_bJumpToNet = new ZegoImageButton(m_zoneTitle);
        m_bJumpToNet->setObjectName(QStringLiteral("m_bJumpToNet"));
        m_bJumpToNet->setMinimumSize(QSize(40, 40));
        m_bJumpToNet->setMaximumSize(QSize(40, 40));
        m_bJumpToNet->setCursor(QCursor(Qt::WhatsThisCursor));
        m_bJumpToNet->setFocusPolicy(Qt::ClickFocus);
        m_bJumpToNet->setStyleSheet(QLatin1String("QPushButton:!hover{\n"
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
        m_bJumpToNet->setFlat(true);

        horizontalLayout_3->addWidget(m_bJumpToNet);

        m_bMin = new ZegoImageButton(m_zoneTitle);
        m_bMin->setObjectName(QStringLiteral("m_bMin"));
        m_bMin->setMinimumSize(QSize(40, 40));
        m_bMin->setMaximumSize(QSize(40, 40));
        m_bMin->setFocusPolicy(Qt::ClickFocus);
        m_bMin->setStyleSheet(QLatin1String("QPushButton:!hover{\n"
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

        horizontalLayout_3->addWidget(m_bMin);

        m_bClose = new ZegoImageButton(m_zoneTitle);
        m_bClose->setObjectName(QStringLiteral("m_bClose"));
        m_bClose->setMinimumSize(QSize(50, 40));
        m_bClose->setMaximumSize(QSize(50, 40));
        m_bClose->setFocusPolicy(Qt::ClickFocus);
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
        m_bClose->setFlat(false);

        horizontalLayout_3->addWidget(m_bClose);


        verticalLayout_6->addWidget(m_zoneTitle);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        m_zoneCreateRoom = new QWidget(ZegoMainDialog);
        m_zoneCreateRoom->setObjectName(QStringLiteral("m_zoneCreateRoom"));
        m_zoneCreateRoom->setMinimumSize(QSize(280, 0));
        m_zoneCreateRoom->setMaximumSize(QSize(280, 16777215));
        m_zoneCreateRoom->setStyleSheet(QLatin1String("QWidget{\n"
"	background-color: rgb(52, 56, 65);\n"
" }"));
        verticalLayout_5 = new QVBoxLayout(m_zoneCreateRoom);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(20, -1, 20, 0);
        m_lbCreateRoom = new QLabel(m_zoneCreateRoom);
        m_lbCreateRoom->setObjectName(QStringLiteral("m_lbCreateRoom"));
        m_lbCreateRoom->setMinimumSize(QSize(0, 64));
        m_lbCreateRoom->setMaximumSize(QSize(16777215, 64));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        m_lbCreateRoom->setFont(font);
        m_lbCreateRoom->setStyleSheet(QString::fromUtf8("QLabel{\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"    font-size: 24px;\n"
"    border: none;\n"
"    text-align: left;\n"
"    color: #e6e6e6;\n"
" }"));

        verticalLayout_4->addWidget(m_lbCreateRoom);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer);

        m_lbName = new QLabel(m_zoneCreateRoom);
        m_lbName->setObjectName(QStringLiteral("m_lbName"));
        m_lbName->setMinimumSize(QSize(0, 20));
        m_lbName->setMaximumSize(QSize(16777215, 20));
        m_lbName->setFont(font);
        m_lbName->setStyleSheet(QString::fromUtf8("QLabel{\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"    font-size: 16px;\n"
"    text-align: left;\n"
"    border: none;\n"
"    color: #e6e6e6;\n"
"    \n"
" }"));

        verticalLayout_4->addWidget(m_lbName);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_2);

        m_edRoomName = new QLineEdit(m_zoneCreateRoom);
        m_edRoomName->setObjectName(QStringLiteral("m_edRoomName"));
        m_edRoomName->setMinimumSize(QSize(0, 40));
        m_edRoomName->setMaximumSize(QSize(16777215, 40));
        m_edRoomName->setFocusPolicy(Qt::ClickFocus);
        m_edRoomName->setStyleSheet(QString::fromUtf8("QLineEdit#m_edRoomName{\n"
"     padding-left: 20px;\n"
" }\n"
"\n"
" QLineEdit:!hover#m_edRoomName{\n"
"     border: 1px solid #e6e6e6;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #fafafa;\n"
"	 color: #999999;\n"
" }\n"
"\n"
" QLineEdit:hover#m_edRoomName{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #fafafa;\n"
"	 color: #999999;\n"
" }\n"
"\n"
" QLineEdit:focus#m_edRoomName{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #ffffff;\n"
"	 color: #666666;\n"
" }"));

        verticalLayout_4->addWidget(m_edRoomName);

        verticalSpacer_3 = new QSpacerItem(20, 38, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_3);

        m_lbMode = new QLabel(m_zoneCreateRoom);
        m_lbMode->setObjectName(QStringLiteral("m_lbMode"));
        m_lbMode->setMinimumSize(QSize(0, 20));
        m_lbMode->setMaximumSize(QSize(16777215, 20));
        m_lbMode->setFont(font);
        m_lbMode->setStyleSheet(QString::fromUtf8("QLabel{\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"    font-size: 16px;\n"
"    text-align: left;\n"
"    border: none;\n"
"    color: #e6e6e6;\n"
" }"));

        verticalLayout_4->addWidget(m_lbMode);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_4);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(16);
        gridLayout->setVerticalSpacing(20);
        gridLayout->setContentsMargins(-1, -1, -1, 0);
        m_bMixMode = new QPushButton(m_zoneCreateRoom);
        m_bMixMode->setObjectName(QStringLiteral("m_bMixMode"));
        m_bMixMode->setMinimumSize(QSize(0, 50));
        m_bMixMode->setMaximumSize(QSize(16777215, 50));
        m_bMixMode->setFocusPolicy(Qt::ClickFocus);
        m_bMixMode->setStyleSheet(QString::fromUtf8(" QPushButton:!hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"     border: 1px solid #b2b2b2;\n"
"     border-radius: 2px;\n"
"     background-color: #343841;\n"
"     color: #e6e6e6;\n"
" }\n"
"\n"
" QPushButton:hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     background-color: #343841;\n"
"     color: #0e88eb;   \n"
" }\n"
"\n"
" QPushButton:checked{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     background-color: #0e88eb;\n"
"     color: #ffffff;  \n"
" }\n"
"\n"
" QPushButton:!enabled{\n"
"     border: 1px solid #111111;\n"
"     border-radius: 2px;\n"
"     background-color: #343841;\n"
"     color: #111111;  \n"
" }"));
        m_bMixMode->setCheckable(true);

        gridLayout->addWidget(m_bMixMode, 0, 1, 1, 1);

        m_bSingleMode = new QPushButton(m_zoneCreateRoom);
        m_bSingleMode->setObjectName(QStringLiteral("m_bSingleMode"));
        m_bSingleMode->setMinimumSize(QSize(0, 50));
        m_bSingleMode->setMaximumSize(QSize(16777215, 50));
        m_bSingleMode->setFocusPolicy(Qt::ClickFocus);
        m_bSingleMode->setContextMenuPolicy(Qt::DefaultContextMenu);
        m_bSingleMode->setStyleSheet(QString::fromUtf8(" QPushButton:!hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"     border: 1px solid #b2b2b2;\n"
"     border-radius: 2px;\n"
"     background-color: #343841;\n"
"     color: #e6e6e6;\n"
" }\n"
"\n"
" QPushButton:hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     background-color: #343841;\n"
"     color: #0e88eb;   \n"
" }\n"
"\n"
" QPushButton:checked{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     background-color: #0e88eb;\n"
"     color: #ffffff;  \n"
" }\n"
"\n"
" QPushButton:!enabled{\n"
"     border: 1px solid #111111;\n"
"     border-radius: 2px;\n"
"     background-color: #343841;\n"
"     color: #111111;  \n"
" }"));
        m_bSingleMode->setCheckable(true);
        m_bSingleMode->setAutoDefault(true);

        gridLayout->addWidget(m_bSingleMode, 0, 0, 1, 1);

        m_bMultiMode = new QPushButton(m_zoneCreateRoom);
        m_bMultiMode->setObjectName(QStringLiteral("m_bMultiMode"));
        m_bMultiMode->setMinimumSize(QSize(0, 50));
        m_bMultiMode->setMaximumSize(QSize(16777215, 50));
        m_bMultiMode->setFocusPolicy(Qt::ClickFocus);
        m_bMultiMode->setStyleSheet(QString::fromUtf8(" QPushButton:!hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"     border: 1px solid #b2b2b2;\n"
"     border-radius: 2px;\n"
"     background-color: #343841;\n"
"     color: #e6e6e6;\n"
" }\n"
"\n"
" QPushButton:hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     background-color: #343841;\n"
"     color: #0e88eb;   \n"
" }\n"
"\n"
" QPushButton:checked{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     background-color: #0e88eb;\n"
"     color: #ffffff;  \n"
" }\n"
"\n"
" QPushButton:!enabled{\n"
"     border: 1px solid #111111;\n"
"     border-radius: 2px;\n"
"     background-color: #343841;\n"
"     color: #111111;  \n"
" }"));
        m_bMultiMode->setCheckable(true);

        gridLayout->addWidget(m_bMultiMode, 1, 0, 1, 1);

        m_bPublish2StreamMode = new QPushButton(m_zoneCreateRoom);
        m_bPublish2StreamMode->setObjectName(QStringLiteral("m_bPublish2StreamMode"));
        m_bPublish2StreamMode->setMinimumSize(QSize(0, 50));
        m_bPublish2StreamMode->setMaximumSize(QSize(16777215, 50));
        m_bPublish2StreamMode->setStyleSheet(QString::fromUtf8(" QPushButton:!hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"     border: 1px solid #b2b2b2;\n"
"     border-radius: 2px;\n"
"     background-color: #343841;\n"
"     color: #e6e6e6;\n"
" }\n"
"\n"
" QPushButton:hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     background-color: #343841;\n"
"     color: #0e88eb;   \n"
" }\n"
"\n"
" QPushButton:checked{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     background-color: #0e88eb;\n"
"     color: #ffffff;  \n"
" }\n"
"\n"
" QPushButton:!enabled{\n"
"     border: 1px solid #111111;\n"
"     border-radius: 2px;\n"
"     background-color: #343841;\n"
"     color: #111111;  \n"
" }"));
        m_bPublish2StreamMode->setCheckable(true);

        gridLayout->addWidget(m_bPublish2StreamMode, 1, 1, 1, 1);


        verticalLayout_4->addLayout(gridLayout);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_5);


        verticalLayout_5->addLayout(verticalLayout_4);

        m_lineBeforeCreate = new QFrame(m_zoneCreateRoom);
        m_lineBeforeCreate->setObjectName(QStringLiteral("m_lineBeforeCreate"));
        m_lineBeforeCreate->setMinimumSize(QSize(0, 2));
        m_lineBeforeCreate->setMaximumSize(QSize(16777215, 2));
        m_lineBeforeCreate->setStyleSheet(QLatin1String("QFrame#m_lineBeforeCreate{\n"
"     background-color: #b2b2b2;\n"
" }"));
        m_lineBeforeCreate->setFrameShape(QFrame::HLine);
        m_lineBeforeCreate->setFrameShadow(QFrame::Sunken);

        verticalLayout_5->addWidget(m_lineBeforeCreate);

        m_bCreateRoom = new QPushButton(m_zoneCreateRoom);
        m_bCreateRoom->setObjectName(QStringLiteral("m_bCreateRoom"));
        m_bCreateRoom->setMinimumSize(QSize(0, 60));
        m_bCreateRoom->setMaximumSize(QSize(16777215, 60));
        m_bCreateRoom->setFocusPolicy(Qt::StrongFocus);
        m_bCreateRoom->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 18px;\n"
"     border: 1px solid #343841;\n"
"     background-color: #343841;\n"
"     color: #e6e6e6;\n"
" }\n"
"\n"
" QPushButton:hover:!pressed{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 18px;\n"
"     border: 1px solid #343841;\n"
"     background-color: #343841;\n"
"     color: #0e88eb;\n"
" }\n"
"\n"
" QPushButton:hover:pressed{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 18px;\n"
"     border: 1px solid #343841;\n"
"     background-color: #343841;\n"
"     color: #0d80de;\n"
" }"));

        verticalLayout_5->addWidget(m_bCreateRoom);

        verticalLayout_5->setStretch(0, 526);
        verticalLayout_5->setStretch(1, 1);
        verticalLayout_5->setStretch(2, 60);

        horizontalLayout_4->addWidget(m_zoneCreateRoom);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, -1, 0, -1);
        m_zoneRoomList = new QWidget(ZegoMainDialog);
        m_zoneRoomList->setObjectName(QStringLiteral("m_zoneRoomList"));
        m_zoneRoomList->setMinimumSize(QSize(650, 338));
        m_zoneRoomList->setMaximumSize(QSize(16777215, 16777215));
        m_zoneRoomList->setStyleSheet(QLatin1String("QWidget{\n"
"    background-color: #ffffff;\n"
" }"));
        verticalLayout_3 = new QVBoxLayout(m_zoneRoomList);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, -1, 0, -1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(20, -1, 0, -1);
        m_TitleList = new QLabel(m_zoneRoomList);
        m_TitleList->setObjectName(QStringLiteral("m_TitleList"));
        m_TitleList->setMinimumSize(QSize(0, 64));
        m_TitleList->setMaximumSize(QSize(16777215, 64));
        m_TitleList->setStyleSheet(QString::fromUtf8("QLabel{\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"    font-size: 24px;\n"
"    border: none;\n"
"    text-align: left;\n"
"    color: #333333;\n"
" }"));

        horizontalLayout->addWidget(m_TitleList);

        horizontalSpacer_30 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_30);

        m_progIndicator = new ZegoProgressIndicator(m_zoneRoomList);
        m_progIndicator->setObjectName(QStringLiteral("m_progIndicator"));
        m_progIndicator->setMinimumSize(QSize(20, 20));
        m_progIndicator->setMaximumSize(QSize(20, 20));

        horizontalLayout->addWidget(m_progIndicator);

        m_bRefreshRoomList = new ZegoImageButton(m_zoneRoomList);
        m_bRefreshRoomList->setObjectName(QStringLiteral("m_bRefreshRoomList"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_bRefreshRoomList->sizePolicy().hasHeightForWidth());
        m_bRefreshRoomList->setSizePolicy(sizePolicy);
        m_bRefreshRoomList->setMinimumSize(QSize(0, 0));
        m_bRefreshRoomList->setMaximumSize(QSize(16777215, 16777215));
        m_bRefreshRoomList->setCursor(QCursor(Qt::PointingHandCursor));
        m_bRefreshRoomList->setFocusPolicy(Qt::ClickFocus);
        m_bRefreshRoomList->setLayoutDirection(Qt::RightToLeft);
        m_bRefreshRoomList->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"     color: #0e88eb;\n"
"     text-align: top;\n"
"     border: none;\n"
" }\n"
"\n"
"QPushButton:hover{\n"
"    color: #0f8ff7;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"    color: #0d80de;\n"
"}\n"
"\n"
"\n"
"\n"
""));
        m_bRefreshRoomList->setFlat(true);

        horizontalLayout->addWidget(m_bRefreshRoomList);

        horizontalSpacer_31 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_31);


        verticalLayout_2->addLayout(horizontalLayout);

        m_roomList = new ZegoRoomList(m_zoneRoomList);
        m_roomList->setObjectName(QStringLiteral("m_roomList"));
        m_roomList->setMinimumSize(QSize(0, 271));
        m_roomList->setMaximumSize(QSize(16777215, 16777215));
        m_roomList->setStyleSheet(QString::fromUtf8("QTableView{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"     color: #333333; \n"
"     margin-left: 10px;  \n"
"     background-color: #ffffff;\n"
"      \n"
" }\n"
"\n"
"QTableView::item{\n"
"     border: none;\n"
"     border-bottom: 1px solid #e6e6e6;\n"
"     padding-left: 6px;\n"
"     height: 50px;\n"
"     background-color: #ffffff;\n"
" }\n"
"\n"
"QTableView::item:selected{\n"
"     background-color: #0e88eb;\n"
"     color: #ffffff;\n"
"}\n"
"\n"
"QHeaderView{\n"
"     font-size: 14px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     color: #333333;\n"
"     border: none;\n"
"     border-bottom: 1px solid #e6e6e6;\n"
"}\n"
"\n"
"QHeaderView::section:horizontal{\n"
"    height: 30px;\n"
"    background: #ffffff;\n"
"    border: none;\n"
"    padding-left: 10px;\n"
"    border-right: 1px solid #e6e6e6;\n"
"}\n"
" "));
        m_roomList->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
        m_roomList->setShowGrid(false);

        verticalLayout_2->addWidget(m_roomList);


        verticalLayout_3->addLayout(verticalLayout_2);


        verticalLayout->addWidget(m_zoneRoomList);

        m_lineSpread = new QFrame(ZegoMainDialog);
        m_lineSpread->setObjectName(QStringLiteral("m_lineSpread"));
        m_lineSpread->setMinimumSize(QSize(630, 1));
        m_lineSpread->setMaximumSize(QSize(16777215, 1));
        m_lineSpread->setStyleSheet(QLatin1String("background-color: #0e88eb;\n"
"margin-left: 10px;\n"
"margin-right: 10px;"));
        m_lineSpread->setFrameShape(QFrame::HLine);
        m_lineSpread->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(m_lineSpread);

        m_zoneSettings = new QWidget(ZegoMainDialog);
        m_zoneSettings->setObjectName(QStringLiteral("m_zoneSettings"));
        m_zoneSettings->setMinimumSize(QSize(650, 258));
        m_zoneSettings->setMaximumSize(QSize(16777215, 238));
        m_zoneSettings->setStyleSheet(QLatin1String("QWidget{\n"
"    background-color: #ffffff;\n"
" }"));
        verticalLayout_7 = new QVBoxLayout(m_zoneSettings);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        m_tabSettings = new QTabWidget(m_zoneSettings);
        m_tabSettings->setObjectName(QStringLiteral("m_tabSettings"));
        m_tabSettings->setFocusPolicy(Qt::NoFocus);
        m_tabSettings->setAutoFillBackground(false);
        m_tabSettings->setStyleSheet(QString::fromUtf8("QTabWidget::pane{\n"
"	border: none;\n"
"}\n"
"\n"
"QTabWidget::tab-bar{\n"
"    left: 0px;\n"
"}\n"
"QTabBar::tab{\n"
"    width: 210px;\n"
"    height: 30px;\n"
"    margin: 0 0 0 0;\n"
"	font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"	font-size: 14px;\n"
"	color: #333333;\n"
"	background-color: #ffffff;\n"
"}\n"
"\n"
"QTabBar::tab:selected{\n"
"	width: 210px;\n"
"	height: 30px;\n"
"	font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"	font-size: 14px;\n"
"	color: #0e88eb;\n"
"	background-color: #ffffff;\n"
"}"));
        m_tabVideoConfig = new QWidget();
        m_tabVideoConfig->setObjectName(QStringLiteral("m_tabVideoConfig"));
        m_tabVideoConfig->setStyleSheet(QStringLiteral("background-color: #ffffff;"));
        verticalLayout_16 = new QVBoxLayout(m_tabVideoConfig);
        verticalLayout_16->setSpacing(0);
        verticalLayout_16->setContentsMargins(11, 11, 11, 11);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        verticalLayout_16->setContentsMargins(0, 0, 0, 0);
        m_lineVideoConfig = new QFrame(m_tabVideoConfig);
        m_lineVideoConfig->setObjectName(QStringLiteral("m_lineVideoConfig"));
        m_lineVideoConfig->setMinimumSize(QSize(0, 2));
        m_lineVideoConfig->setMaximumSize(QSize(16777215, 2));
        m_lineVideoConfig->setStyleSheet(QLatin1String("margin-left: 63px;\n"
"margin-right:507px;\n"
"border: none;\n"
"background-color: #0e88eb;"));
        m_lineVideoConfig->setFrameShape(QFrame::HLine);
        m_lineVideoConfig->setFrameShadow(QFrame::Sunken);

        verticalLayout_16->addWidget(m_lineVideoConfig);

        m_lineLongVideoConfig = new QFrame(m_tabVideoConfig);
        m_lineLongVideoConfig->setObjectName(QStringLiteral("m_lineLongVideoConfig"));
        m_lineLongVideoConfig->setMinimumSize(QSize(0, 1));
        m_lineLongVideoConfig->setMaximumSize(QSize(16777215, 1));
        m_lineLongVideoConfig->setStyleSheet(QLatin1String("margin-left: 10px;\n"
"margin-right: 10px;\n"
"background-color: #f5f5f5;\n"
"border: none;"));
        m_lineLongVideoConfig->setFrameShape(QFrame::HLine);
        m_lineLongVideoConfig->setFrameShadow(QFrame::Sunken);

        verticalLayout_16->addWidget(m_lineLongVideoConfig);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(0);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(0, -1, 0, -1);
        horizontalSpacer_5 = new QSpacerItem(32, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_5);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(0);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        verticalSpacer_19 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_14->addItem(verticalSpacer_19);

        m_bExtremelyHigh = new QPushButton(m_tabVideoConfig);
        m_bExtremelyHigh->setObjectName(QStringLiteral("m_bExtremelyHigh"));
        m_bExtremelyHigh->setMinimumSize(QSize(140, 28));
        m_bExtremelyHigh->setMaximumSize(QSize(140, 28));
        m_bExtremelyHigh->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
"	 background-color: #ffffff;\n"
"	 border: none;\n"
" }\n"
"\n"
" QPushButton:hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #0e88eb;\n"
"	 border: none;\n"
"	 background-color: #ffffff;\n"
" }\n"
" \n"
" QPushButton:checked{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 border: none;\n"
"	 background-color: #0e88eb;\n"
"     color: #ffffff;\n"
" }"));
        m_bExtremelyHigh->setCheckable(true);

        verticalLayout_14->addWidget(m_bExtremelyHigh);

        m_bSuperHigh = new QPushButton(m_tabVideoConfig);
        m_bSuperHigh->setObjectName(QStringLiteral("m_bSuperHigh"));
        m_bSuperHigh->setMinimumSize(QSize(140, 28));
        m_bSuperHigh->setMaximumSize(QSize(140, 28));
        m_bSuperHigh->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
"	 background-color: #ffffff;\n"
"	 border: none;\n"
" }\n"
"\n"
" QPushButton:hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #0e88eb;\n"
"	 border: none;\n"
"	 background-color: #ffffff;\n"
" }\n"
" \n"
" QPushButton:checked{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 border: none;\n"
"	 background-color: #0e88eb;\n"
"     color: #ffffff;\n"
" }"));
        m_bSuperHigh->setCheckable(true);

        verticalLayout_14->addWidget(m_bSuperHigh);

        m_bHigh = new QPushButton(m_tabVideoConfig);
        m_bHigh->setObjectName(QStringLiteral("m_bHigh"));
        m_bHigh->setMinimumSize(QSize(140, 28));
        m_bHigh->setMaximumSize(QSize(140, 28));
        m_bHigh->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
"	 background-color: #ffffff;\n"
"	 border: none;\n"
" }\n"
"\n"
" QPushButton:hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #0e88eb;\n"
"	 border: none;\n"
"	 background-color: #ffffff;\n"
" }\n"
" \n"
" QPushButton:checked{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 border: none;\n"
"	 background-color: #0e88eb;\n"
"     color: #ffffff;\n"
" }"));
        m_bHigh->setCheckable(true);

        verticalLayout_14->addWidget(m_bHigh);

        m_bStandard = new QPushButton(m_tabVideoConfig);
        m_bStandard->setObjectName(QStringLiteral("m_bStandard"));
        m_bStandard->setMinimumSize(QSize(140, 28));
        m_bStandard->setMaximumSize(QSize(140, 28));
        m_bStandard->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
"	 background-color: #ffffff;\n"
"	 border: none;\n"
" }\n"
"\n"
" QPushButton:hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #0e88eb;\n"
"	 border: none;\n"
"	 background-color: #ffffff;\n"
" }\n"
" \n"
" QPushButton:checked{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 border: none;\n"
"	 background-color: #0e88eb;\n"
"     color: #ffffff;\n"
" }"));
        m_bStandard->setCheckable(true);

        verticalLayout_14->addWidget(m_bStandard);

        m_bLow = new QPushButton(m_tabVideoConfig);
        m_bLow->setObjectName(QStringLiteral("m_bLow"));
        m_bLow->setMinimumSize(QSize(140, 28));
        m_bLow->setMaximumSize(QSize(140, 28));
        m_bLow->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
"	 background-color: #ffffff;\n"
"	 border: none;\n"
" }\n"
"\n"
" QPushButton:hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #0e88eb;\n"
"	 border: none;\n"
"	 background-color: #ffffff;\n"
" }\n"
" \n"
" QPushButton:checked{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 border: none;\n"
"	 background-color: #0e88eb;\n"
"     color: #ffffff;\n"
" }"));
        m_bLow->setCheckable(true);

        verticalLayout_14->addWidget(m_bLow);

        m_bSuperLow = new QPushButton(m_tabVideoConfig);
        m_bSuperLow->setObjectName(QStringLiteral("m_bSuperLow"));
        m_bSuperLow->setMinimumSize(QSize(140, 28));
        m_bSuperLow->setMaximumSize(QSize(140, 28));
        m_bSuperLow->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
"	 background-color: #ffffff;\n"
"	 border: none;\n"
" }\n"
"\n"
" QPushButton:hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #0e88eb;\n"
"	 border: none;\n"
"	 background-color: #ffffff;\n"
" }\n"
" \n"
" QPushButton:checked{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 border: none;\n"
"	 background-color: #0e88eb;\n"
"     color: #ffffff;\n"
" }"));
        m_bSuperLow->setCheckable(true);

        verticalLayout_14->addWidget(m_bSuperLow);

        m_bCustom = new QPushButton(m_tabVideoConfig);
        m_bCustom->setObjectName(QStringLiteral("m_bCustom"));
        m_bCustom->setMinimumSize(QSize(140, 28));
        m_bCustom->setMaximumSize(QSize(140, 28));
        m_bCustom->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
"	 background-color: #ffffff;\n"
"	 border: none;\n"
" }\n"
"\n"
" QPushButton:hover{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #0e88eb;\n"
"	 border: none;\n"
"	 background-color: #ffffff;\n"
" }\n"
" \n"
" QPushButton:checked{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 border: none;\n"
"	 background-color: #0e88eb;\n"
"     color: #ffffff;\n"
" }"));
        m_bCustom->setCheckable(true);

        verticalLayout_14->addWidget(m_bCustom);


        horizontalLayout_13->addLayout(verticalLayout_14);

        horizontalSpacer_6 = new QSpacerItem(84, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_6);

        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setSpacing(0);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        verticalLayout_15->setContentsMargins(0, 0, -1, -1);
        verticalSpacer_12 = new QSpacerItem(22, 22, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_15->addItem(verticalSpacer_12);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        m_lbResolution = new QLabel(m_tabVideoConfig);
        m_lbResolution->setObjectName(QStringLiteral("m_lbResolution"));
        m_lbResolution->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        horizontalLayout_6->addWidget(m_lbResolution);

        m_lbValueResolution = new QLabel(m_tabVideoConfig);
        m_lbValueResolution->setObjectName(QStringLiteral("m_lbValueResolution"));
        m_lbValueResolution->setLayoutDirection(Qt::LeftToRight);
        m_lbValueResolution->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));
        m_lbValueResolution->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(m_lbValueResolution);


        verticalLayout_15->addLayout(horizontalLayout_6);

        verticalSpacer_13 = new QSpacerItem(12, 12, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_15->addItem(verticalSpacer_13);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        m_bResolutionDown = new ZegoStateButton(m_tabVideoConfig);
        m_bResolutionDown->setObjectName(QStringLiteral("m_bResolutionDown"));
        m_bResolutionDown->setMinimumSize(QSize(15, 15));
        m_bResolutionDown->setMaximumSize(QSize(15, 15));
        m_bResolutionDown->setFocusPolicy(Qt::TabFocus);
        m_bResolutionDown->setLayoutDirection(Qt::LeftToRight);
        m_bResolutionDown->setStyleSheet(QStringLiteral(""));
        m_bResolutionDown->setIconSize(QSize(15, 15));
        m_bResolutionDown->setFlat(true);

        horizontalLayout_8->addWidget(m_bResolutionDown);

        m_sliderResolution = new ZegoSlider(m_tabVideoConfig);
        m_sliderResolution->setObjectName(QStringLiteral("m_sliderResolution"));
        m_sliderResolution->setMinimumSize(QSize(240, 0));
        m_sliderResolution->setMaximum(9);
        m_sliderResolution->setPageStep(1);
        m_sliderResolution->setOrientation(Qt::Horizontal);

        horizontalLayout_8->addWidget(m_sliderResolution);

        m_bResolutionUp = new ZegoStateButton(m_tabVideoConfig);
        m_bResolutionUp->setObjectName(QStringLiteral("m_bResolutionUp"));
        m_bResolutionUp->setMinimumSize(QSize(15, 15));
        m_bResolutionUp->setMaximumSize(QSize(15, 15));
        m_bResolutionUp->setStyleSheet(QStringLiteral(""));
        m_bResolutionUp->setFlat(true);

        horizontalLayout_8->addWidget(m_bResolutionUp);


        verticalLayout_15->addLayout(horizontalLayout_8);

        verticalSpacer_14 = new QSpacerItem(16, 16, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_15->addItem(verticalSpacer_14);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        m_lbFPS = new QLabel(m_tabVideoConfig);
        m_lbFPS->setObjectName(QStringLiteral("m_lbFPS"));
        m_lbFPS->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        horizontalLayout_9->addWidget(m_lbFPS);

        m_lbValueFPS = new QLabel(m_tabVideoConfig);
        m_lbValueFPS->setObjectName(QStringLiteral("m_lbValueFPS"));
        m_lbValueFPS->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));
        m_lbValueFPS->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(m_lbValueFPS);


        verticalLayout_15->addLayout(horizontalLayout_9);

        verticalSpacer_15 = new QSpacerItem(12, 12, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_15->addItem(verticalSpacer_15);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        m_bFPSDown = new ZegoStateButton(m_tabVideoConfig);
        m_bFPSDown->setObjectName(QStringLiteral("m_bFPSDown"));
        m_bFPSDown->setMinimumSize(QSize(15, 15));
        m_bFPSDown->setMaximumSize(QSize(15, 15));
        m_bFPSDown->setStyleSheet(QStringLiteral(""));
        m_bFPSDown->setFlat(true);

        horizontalLayout_10->addWidget(m_bFPSDown);

        m_sliderFPS = new ZegoSlider(m_tabVideoConfig);
        m_sliderFPS->setObjectName(QStringLiteral("m_sliderFPS"));
        m_sliderFPS->setMinimumSize(QSize(240, 0));
        m_sliderFPS->setMaximum(5);
        m_sliderFPS->setPageStep(1);
        m_sliderFPS->setOrientation(Qt::Horizontal);

        horizontalLayout_10->addWidget(m_sliderFPS);

        m_bFPSUp = new ZegoStateButton(m_tabVideoConfig);
        m_bFPSUp->setObjectName(QStringLiteral("m_bFPSUp"));
        m_bFPSUp->setMinimumSize(QSize(15, 15));
        m_bFPSUp->setMaximumSize(QSize(15, 15));
        m_bFPSUp->setStyleSheet(QStringLiteral(""));
        m_bFPSUp->setFlat(true);

        horizontalLayout_10->addWidget(m_bFPSUp);


        verticalLayout_15->addLayout(horizontalLayout_10);

        verticalSpacer_16 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_15->addItem(verticalSpacer_16);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        m_lbBitrate = new QLabel(m_tabVideoConfig);
        m_lbBitrate->setObjectName(QStringLiteral("m_lbBitrate"));
        m_lbBitrate->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        horizontalLayout_11->addWidget(m_lbBitrate);

        m_lbValueBitrate = new QLabel(m_tabVideoConfig);
        m_lbValueBitrate->setObjectName(QStringLiteral("m_lbValueBitrate"));
        m_lbValueBitrate->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));
        m_lbValueBitrate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(m_lbValueBitrate);


        verticalLayout_15->addLayout(horizontalLayout_11);

        verticalSpacer_17 = new QSpacerItem(20, 12, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_15->addItem(verticalSpacer_17);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        m_bBitrateDown = new ZegoStateButton(m_tabVideoConfig);
        m_bBitrateDown->setObjectName(QStringLiteral("m_bBitrateDown"));
        m_bBitrateDown->setMinimumSize(QSize(15, 15));
        m_bBitrateDown->setMaximumSize(QSize(15, 15));
        m_bBitrateDown->setStyleSheet(QStringLiteral(""));
        m_bBitrateDown->setFlat(true);

        horizontalLayout_12->addWidget(m_bBitrateDown);

        m_sliderBitrate = new ZegoSlider(m_tabVideoConfig);
        m_sliderBitrate->setObjectName(QStringLiteral("m_sliderBitrate"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_sliderBitrate->sizePolicy().hasHeightForWidth());
        m_sliderBitrate->setSizePolicy(sizePolicy1);
        m_sliderBitrate->setMinimumSize(QSize(240, 0));
        m_sliderBitrate->setMaximum(22);
        m_sliderBitrate->setPageStep(1);
        m_sliderBitrate->setOrientation(Qt::Horizontal);

        horizontalLayout_12->addWidget(m_sliderBitrate);

        m_bBitrateUp = new ZegoStateButton(m_tabVideoConfig);
        m_bBitrateUp->setObjectName(QStringLiteral("m_bBitrateUp"));
        m_bBitrateUp->setMinimumSize(QSize(15, 15));
        m_bBitrateUp->setMaximumSize(QSize(15, 15));
        m_bBitrateUp->setStyleSheet(QStringLiteral(""));
        m_bBitrateUp->setFlat(true);

        horizontalLayout_12->addWidget(m_bBitrateUp);


        verticalLayout_15->addLayout(horizontalLayout_12);

        verticalSpacer_18 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_15->addItem(verticalSpacer_18);


        horizontalLayout_13->addLayout(verticalLayout_15);

        horizontalSpacer_7 = new QSpacerItem(80, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_7);


        verticalLayout_16->addLayout(horizontalLayout_13);

        m_tabSettings->addTab(m_tabVideoConfig, QString());
        m_tabExtraSettings = new QWidget();
        m_tabExtraSettings->setObjectName(QStringLiteral("m_tabExtraSettings"));
        verticalLayout_22 = new QVBoxLayout(m_tabExtraSettings);
        verticalLayout_22->setSpacing(0);
        verticalLayout_22->setContentsMargins(11, 11, 11, 11);
        verticalLayout_22->setObjectName(QStringLiteral("verticalLayout_22"));
        verticalLayout_22->setContentsMargins(0, 0, 0, 0);
        m_lineExtraSettings = new QFrame(m_tabExtraSettings);
        m_lineExtraSettings->setObjectName(QStringLiteral("m_lineExtraSettings"));
        m_lineExtraSettings->setMinimumSize(QSize(0, 2));
        m_lineExtraSettings->setMaximumSize(QSize(16777215, 2));
        m_lineExtraSettings->setStyleSheet(QLatin1String("margin-left: 273px;\n"
"margin-right: 297px;\n"
"background-color: #0e88eb;\n"
"border: none;"));
        m_lineExtraSettings->setFrameShape(QFrame::HLine);
        m_lineExtraSettings->setFrameShadow(QFrame::Sunken);

        verticalLayout_22->addWidget(m_lineExtraSettings);

        m_lineLongExtraSettings = new QFrame(m_tabExtraSettings);
        m_lineLongExtraSettings->setObjectName(QStringLiteral("m_lineLongExtraSettings"));
        m_lineLongExtraSettings->setMinimumSize(QSize(0, 1));
        m_lineLongExtraSettings->setMaximumSize(QSize(16777215, 1));
        m_lineLongExtraSettings->setStyleSheet(QLatin1String("margin-left: 10px;\n"
"margin-right: 10px;\n"
"background-color: #f5f5f5;\n"
"border: none;"));
        m_lineLongExtraSettings->setFrameShape(QFrame::HLine);
        m_lineLongExtraSettings->setFrameShadow(QFrame::Sunken);

        verticalLayout_22->addWidget(m_lineLongExtraSettings);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(0);
        horizontalLayout_27->setObjectName(QStringLiteral("horizontalLayout_27"));
        horizontalLayout_27->setContentsMargins(-1, -1, 0, -1);
        horizontalSpacer_15 = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_27->addItem(horizontalSpacer_15);

        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setSpacing(0);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        verticalLayout_17->setContentsMargins(-1, -1, -1, 0);
        verticalSpacer_21 = new QSpacerItem(18, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_17->addItem(verticalSpacer_21);

        m_lbEnvironment = new QLabel(m_tabExtraSettings);
        m_lbEnvironment->setObjectName(QStringLiteral("m_lbEnvironment"));
        m_lbEnvironment->setMaximumSize(QSize(16777215, 16777215));
        m_lbEnvironment->setFont(font);
        m_lbEnvironment->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        verticalLayout_17->addWidget(m_lbEnvironment);

        verticalSpacer_22 = new QSpacerItem(18, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_17->addItem(verticalSpacer_22);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(0);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        m_lbTestEnv = new QLabel(m_tabExtraSettings);
        m_lbTestEnv->setObjectName(QStringLiteral("m_lbTestEnv"));
        m_lbTestEnv->setMaximumSize(QSize(16777215, 16));
        m_lbTestEnv->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        horizontalLayout_14->addWidget(m_lbTestEnv);

        horizontalSpacer_8 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_8);

        m_switchTestEnv = new ZegoSwitchButton(m_tabExtraSettings);
        m_switchTestEnv->setObjectName(QStringLiteral("m_switchTestEnv"));
        m_switchTestEnv->setMinimumSize(QSize(32, 16));
        m_switchTestEnv->setMaximumSize(QSize(32, 16));
        m_switchTestEnv->setStyleSheet(QStringLiteral(""));
        m_switchTestEnv->setCheckable(true);

        horizontalLayout_14->addWidget(m_switchTestEnv);

        horizontalSpacer_28 = new QSpacerItem(15, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_28);


        verticalLayout_17->addLayout(horizontalLayout_14);

        verticalSpacer_23 = new QSpacerItem(20, 14, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_17->addItem(verticalSpacer_23);

        m_cbAppVersion = new ZegoComboBox(m_tabExtraSettings);
        m_cbAppVersion->setObjectName(QStringLiteral("m_cbAppVersion"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_cbAppVersion->sizePolicy().hasHeightForWidth());
        m_cbAppVersion->setSizePolicy(sizePolicy2);
        m_cbAppVersion->setMinimumSize(QSize(220, 0));
        m_cbAppVersion->setMaximumSize(QSize(220, 16777215));

        verticalLayout_17->addWidget(m_cbAppVersion);

        verticalSpacer_20 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_17->addItem(verticalSpacer_20);

        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setSpacing(0);
        horizontalLayout_33->setObjectName(QStringLiteral("horizontalLayout_33"));
        m_lbAPPID = new QLabel(m_tabExtraSettings);
        m_lbAPPID->setObjectName(QStringLiteral("m_lbAPPID"));
        m_lbAPPID->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        horizontalLayout_33->addWidget(m_lbAPPID);

        horizontalSpacer_35 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_33->addItem(horizontalSpacer_35);

        m_strEdAPPID = new QLineEdit(m_tabExtraSettings);
        m_strEdAPPID->setObjectName(QStringLiteral("m_strEdAPPID"));
        m_strEdAPPID->setMinimumSize(QSize(147, 32));
        m_strEdAPPID->setMaximumSize(QSize(147, 32));
        m_strEdAPPID->setFocusPolicy(Qt::ClickFocus);
        m_strEdAPPID->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"     padding-left: 10px;\n"
" }\n"
"\n"
" QLineEdit:!hover{\n"
"     border: 1px solid #e6e6e6;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #fafafa;\n"
"	 color: #666666;\n"
" }\n"
"\n"
" QLineEdit:hover:!focus{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #fafafa;\n"
"	 color: #666666;\n"
" }\n"
"\n"
" QLineEdit:focus{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #ffffff;\n"
" }"));

        horizontalLayout_33->addWidget(m_strEdAPPID);


        verticalLayout_17->addLayout(horizontalLayout_33);

        verticalSpacer_24 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_17->addItem(verticalSpacer_24);

        horizontalLayout_34 = new QHBoxLayout();
        horizontalLayout_34->setSpacing(0);
        horizontalLayout_34->setObjectName(QStringLiteral("horizontalLayout_34"));
        m_lbAPPSign = new QLabel(m_tabExtraSettings);
        m_lbAPPSign->setObjectName(QStringLiteral("m_lbAPPSign"));
        m_lbAPPSign->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        horizontalLayout_34->addWidget(m_lbAPPSign);

        horizontalSpacer_36 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_34->addItem(horizontalSpacer_36);

        m_strEdAPPSign = new QLineEdit(m_tabExtraSettings);
        m_strEdAPPSign->setObjectName(QStringLiteral("m_strEdAPPSign"));
        m_strEdAPPSign->setMinimumSize(QSize(147, 32));
        m_strEdAPPSign->setMaximumSize(QSize(147, 32));
        m_strEdAPPSign->setFocusPolicy(Qt::ClickFocus);
        m_strEdAPPSign->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"     padding-left: 10px;\n"
" }\n"
"\n"
" QLineEdit:!hover{\n"
"     border: 1px solid #e6e6e6;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #fafafa;\n"
"	 color: #666666;\n"
" }\n"
"\n"
" QLineEdit:hover:!focus{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #fafafa;\n"
"	 color: #666666;\n"
" }\n"
"\n"
" QLineEdit:focus{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #ffffff;\n"
" }"));

        horizontalLayout_34->addWidget(m_strEdAPPSign);


        verticalLayout_17->addLayout(horizontalLayout_34);

        verticalSpacer_33 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_17->addItem(verticalSpacer_33);


        horizontalLayout_27->addLayout(verticalLayout_17);

        horizontalSpacer_17 = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_27->addItem(horizontalSpacer_17);

        verticalLayout_21 = new QVBoxLayout();
        verticalLayout_21->setSpacing(0);
        verticalLayout_21->setObjectName(QStringLiteral("verticalLayout_21"));
        verticalSpacer_25 = new QSpacerItem(18, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_21->addItem(verticalSpacer_25);

        m_lbAdvanced = new QLabel(m_tabExtraSettings);
        m_lbAdvanced->setObjectName(QStringLiteral("m_lbAdvanced"));
        m_lbAdvanced->setFont(font);
        m_lbAdvanced->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        verticalLayout_21->addWidget(m_lbAdvanced);

        verticalSpacer_26 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_21->addItem(verticalSpacer_26);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(0);
        horizontalLayout_24->setObjectName(QStringLiteral("horizontalLayout_24"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(0);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        m_lbCapture = new QLabel(m_tabExtraSettings);
        m_lbCapture->setObjectName(QStringLiteral("m_lbCapture"));
        m_lbCapture->setMinimumSize(QSize(0, 16));
        m_lbCapture->setMaximumSize(QSize(16777215, 16));
        m_lbCapture->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        horizontalLayout_15->addWidget(m_lbCapture);

        horizontalSpacer_10 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_10);

        m_switchCapture = new ZegoSwitchButton(m_tabExtraSettings);
        m_switchCapture->setObjectName(QStringLiteral("m_switchCapture"));
        m_switchCapture->setMinimumSize(QSize(32, 16));
        m_switchCapture->setMaximumSize(QSize(32, 16));
        m_switchCapture->setStyleSheet(QStringLiteral(""));
        m_switchCapture->setCheckable(true);

        horizontalLayout_15->addWidget(m_switchCapture);


        horizontalLayout_24->addLayout(horizontalLayout_15);

        horizontalSpacer_11 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_24->addItem(horizontalSpacer_11);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(0);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        m_lbFilter = new QLabel(m_tabExtraSettings);
        m_lbFilter->setObjectName(QStringLiteral("m_lbFilter"));
        m_lbFilter->setMinimumSize(QSize(0, 16));
        m_lbFilter->setMaximumSize(QSize(16777215, 16));
        m_lbFilter->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        horizontalLayout_16->addWidget(m_lbFilter);

        horizontalSpacer_12 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_12);

        m_switchFilter = new ZegoSwitchButton(m_tabExtraSettings);
        m_switchFilter->setObjectName(QStringLiteral("m_switchFilter"));
        sizePolicy.setHeightForWidth(m_switchFilter->sizePolicy().hasHeightForWidth());
        m_switchFilter->setSizePolicy(sizePolicy);
        m_switchFilter->setMinimumSize(QSize(32, 16));
        m_switchFilter->setMaximumSize(QSize(32, 16));
        m_switchFilter->setStyleSheet(QStringLiteral(""));
        m_switchFilter->setCheckable(true);

        horizontalLayout_16->addWidget(m_switchFilter);


        horizontalLayout_24->addLayout(horizontalLayout_16);

        horizontalSpacer_13 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_24->addItem(horizontalSpacer_13);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(0);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        m_lbVerticalCapture = new QLabel(m_tabExtraSettings);
        m_lbVerticalCapture->setObjectName(QStringLiteral("m_lbVerticalCapture"));
        m_lbVerticalCapture->setMinimumSize(QSize(0, 16));
        m_lbVerticalCapture->setMaximumSize(QSize(16777215, 16));
        m_lbVerticalCapture->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        horizontalLayout_17->addWidget(m_lbVerticalCapture);

        horizontalSpacer_14 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_14);

        m_switchVerticalCapture = new ZegoSwitchButton(m_tabExtraSettings);
        m_switchVerticalCapture->setObjectName(QStringLiteral("m_switchVerticalCapture"));
        m_switchVerticalCapture->setMinimumSize(QSize(32, 16));
        m_switchVerticalCapture->setMaximumSize(QSize(32, 16));
        m_switchVerticalCapture->setStyleSheet(QStringLiteral(""));
        m_switchVerticalCapture->setCheckable(true);

        horizontalLayout_17->addWidget(m_switchVerticalCapture);


        horizontalLayout_24->addLayout(horizontalLayout_17);


        verticalLayout_21->addLayout(horizontalLayout_24);

        verticalSpacer_27 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_21->addItem(verticalSpacer_27);

        m_lbExtra = new QLabel(m_tabExtraSettings);
        m_lbExtra->setObjectName(QStringLiteral("m_lbExtra"));
        m_lbExtra->setFont(font);
        m_lbExtra->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        verticalLayout_21->addWidget(m_lbExtra);

        verticalSpacer_35 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_21->addItem(verticalSpacer_35);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(0);
        horizontalLayout_25->setObjectName(QStringLiteral("horizontalLayout_25"));
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(0);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        m_lbSurfaceMerge = new QLabel(m_tabExtraSettings);
        m_lbSurfaceMerge->setObjectName(QStringLiteral("m_lbSurfaceMerge"));
        m_lbSurfaceMerge->setMinimumSize(QSize(0, 16));
        m_lbSurfaceMerge->setMaximumSize(QSize(16777215, 16));
        m_lbSurfaceMerge->setStyleSheet(QString::fromUtf8("QLabel{\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"    font-size: 14px;\n"
"    color: #666666;\n"
" }"));

        horizontalLayout_18->addWidget(m_lbSurfaceMerge);

        m_spacerSurfaceMergeMid = new QSpacerItem(10, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(m_spacerSurfaceMergeMid);

        m_switchSurfaceMerge = new ZegoSwitchButton(m_tabExtraSettings);
        m_switchSurfaceMerge->setObjectName(QStringLiteral("m_switchSurfaceMerge"));
        m_switchSurfaceMerge->setMinimumSize(QSize(32, 16));
        m_switchSurfaceMerge->setMaximumSize(QSize(32, 16));
        m_switchSurfaceMerge->setStyleSheet(QStringLiteral(""));
        m_switchSurfaceMerge->setCheckable(true);

        horizontalLayout_18->addWidget(m_switchSurfaceMerge);


        horizontalLayout_25->addLayout(horizontalLayout_18);

        m_spacerSurfaceMergeRight = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_25->addItem(m_spacerSurfaceMergeRight);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(0);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        m_lbCameraRotation = new QLabel(m_tabExtraSettings);
        m_lbCameraRotation->setObjectName(QStringLiteral("m_lbCameraRotation"));
        m_lbCameraRotation->setMinimumSize(QSize(0, 0));
        m_lbCameraRotation->setMaximumSize(QSize(16777215, 16777215));
        m_lbCameraRotation->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        horizontalLayout_19->addWidget(m_lbCameraRotation);

        horizontalSpacer_20 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_20);


        horizontalLayout_25->addLayout(horizontalLayout_19);

        m_cbRotation = new ZegoComboBox(m_tabExtraSettings);
        m_cbRotation->setObjectName(QStringLiteral("m_cbRotation"));
        m_cbRotation->setMinimumSize(QSize(80, 0));
        m_cbRotation->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_25->addWidget(m_cbRotation);

        horizontalSpacer_32 = new QSpacerItem(80, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_25->addItem(horizontalSpacer_32);


        verticalLayout_21->addLayout(horizontalLayout_25);

        verticalSpacer_28 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        verticalLayout_21->addItem(verticalSpacer_28);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setSpacing(0);
        horizontalLayout_26->setObjectName(QStringLiteral("horizontalLayout_26"));
        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setSpacing(0);
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        m_lbAudioLeft = new QLabel(m_tabExtraSettings);
        m_lbAudioLeft->setObjectName(QStringLiteral("m_lbAudioLeft"));
        m_lbAudioLeft->setFont(font);
        m_lbAudioLeft->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        verticalLayout_18->addWidget(m_lbAudioLeft);

        verticalSpacer_29 = new QSpacerItem(20, 12, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_18->addItem(verticalSpacer_29);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(0);
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        m_lbReverb = new QLabel(m_tabExtraSettings);
        m_lbReverb->setObjectName(QStringLiteral("m_lbReverb"));
        m_lbReverb->setMinimumSize(QSize(0, 16));
        m_lbReverb->setMaximumSize(QSize(16777215, 16));
        m_lbReverb->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        horizontalLayout_21->addWidget(m_lbReverb);

        horizontalSpacer_23 = new QSpacerItem(14, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_21->addItem(horizontalSpacer_23);

        m_switchReverb = new ZegoSwitchButton(m_tabExtraSettings);
        m_switchReverb->setObjectName(QStringLiteral("m_switchReverb"));
        m_switchReverb->setMinimumSize(QSize(32, 16));
        m_switchReverb->setMaximumSize(QSize(32, 16));
        m_switchReverb->setStyleSheet(QStringLiteral(""));
        m_switchReverb->setCheckable(true);

        horizontalLayout_21->addWidget(m_switchReverb);


        verticalLayout_18->addLayout(horizontalLayout_21);


        horizontalLayout_26->addLayout(verticalLayout_18);

        horizontalSpacer_24 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_26->addItem(horizontalSpacer_24);

        verticalLayout_19 = new QVBoxLayout();
        verticalLayout_19->setSpacing(0);
        verticalLayout_19->setObjectName(QStringLiteral("verticalLayout_19"));
        verticalSpacer_30 = new QSpacerItem(20, 12, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_19->addItem(verticalSpacer_30);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(0);
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        m_lbVirtualStereo = new QLabel(m_tabExtraSettings);
        m_lbVirtualStereo->setObjectName(QStringLiteral("m_lbVirtualStereo"));
        m_lbVirtualStereo->setMinimumSize(QSize(0, 16));
        m_lbVirtualStereo->setMaximumSize(QSize(16777215, 16));
        m_lbVirtualStereo->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        horizontalLayout_22->addWidget(m_lbVirtualStereo);

        horizontalSpacer_25 = new QSpacerItem(14, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_25);

        m_switchVirtualStereo = new ZegoSwitchButton(m_tabExtraSettings);
        m_switchVirtualStereo->setObjectName(QStringLiteral("m_switchVirtualStereo"));
        m_switchVirtualStereo->setMinimumSize(QSize(32, 16));
        m_switchVirtualStereo->setMaximumSize(QSize(32, 16));
        m_switchVirtualStereo->setStyleSheet(QStringLiteral(""));
        m_switchVirtualStereo->setCheckable(true);

        horizontalLayout_22->addWidget(m_switchVirtualStereo);


        verticalLayout_19->addLayout(horizontalLayout_22);


        horizontalLayout_26->addLayout(verticalLayout_19);

        horizontalSpacer_27 = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_26->addItem(horizontalSpacer_27);

        verticalLayout_20 = new QVBoxLayout();
        verticalLayout_20->setSpacing(0);
        verticalLayout_20->setObjectName(QStringLiteral("verticalLayout_20"));
        m_lbAudioRight = new QLabel(m_tabExtraSettings);
        m_lbAudioRight->setObjectName(QStringLiteral("m_lbAudioRight"));
        m_lbAudioRight->setFont(font);
        m_lbAudioRight->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        verticalLayout_20->addWidget(m_lbAudioRight);

        verticalSpacer_31 = new QSpacerItem(20, 12, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_20->addItem(verticalSpacer_31);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(0);
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        m_lbNational = new QLabel(m_tabExtraSettings);
        m_lbNational->setObjectName(QStringLiteral("m_lbNational"));
        m_lbNational->setMinimumSize(QSize(0, 16));
        m_lbNational->setMaximumSize(QSize(16777215, 16));
        m_lbNational->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        horizontalLayout_23->addWidget(m_lbNational);

        horizontalSpacer_26 = new QSpacerItem(14, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_23->addItem(horizontalSpacer_26);

        m_switchNational = new ZegoSwitchButton(m_tabExtraSettings);
        m_switchNational->setObjectName(QStringLiteral("m_switchNational"));
        m_switchNational->setMinimumSize(QSize(32, 16));
        m_switchNational->setMaximumSize(QSize(32, 16));
        m_switchNational->setStyleSheet(QStringLiteral(""));
        m_switchNational->setCheckable(true);

        horizontalLayout_23->addWidget(m_switchNational);


        verticalLayout_20->addLayout(horizontalLayout_23);


        horizontalLayout_26->addLayout(verticalLayout_20);


        verticalLayout_21->addLayout(horizontalLayout_26);

        verticalSpacer_34 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_21->addItem(verticalSpacer_34);


        horizontalLayout_27->addLayout(verticalLayout_21);

        horizontalSpacer_16 = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_27->addItem(horizontalSpacer_16);


        verticalLayout_22->addLayout(horizontalLayout_27);

        m_tabSettings->addTab(m_tabExtraSettings, QString());
        m_tabUserSettings = new QWidget();
        m_tabUserSettings->setObjectName(QStringLiteral("m_tabUserSettings"));
        verticalLayout_13 = new QVBoxLayout(m_tabUserSettings);
        verticalLayout_13->setSpacing(0);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(30, 0, 30, 0);
        m_lineUserSettings = new QFrame(m_tabUserSettings);
        m_lineUserSettings->setObjectName(QStringLiteral("m_lineUserSettings"));
        m_lineUserSettings->setMinimumSize(QSize(0, 2));
        m_lineUserSettings->setMaximumSize(QSize(16777215, 2));
        m_lineUserSettings->setStyleSheet(QLatin1String("margin-left: 453px;\n"
"margin-right: 57px;\n"
"background-color: #0e88eb;\n"
"border: none;"));
        m_lineUserSettings->setFrameShape(QFrame::HLine);
        m_lineUserSettings->setFrameShadow(QFrame::Sunken);

        verticalLayout_13->addWidget(m_lineUserSettings);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(0);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(-1, 0, -1, -1);
        m_lineLongUserSettings = new QFrame(m_tabUserSettings);
        m_lineLongUserSettings->setObjectName(QStringLiteral("m_lineLongUserSettings"));
        m_lineLongUserSettings->setMinimumSize(QSize(0, 1));
        m_lineLongUserSettings->setMaximumSize(QSize(16777215, 1));
        m_lineLongUserSettings->setStyleSheet(QLatin1String("margin-left: 10px;\n"
"margin-right: 10px;\n"
"background-color: #f5f5f5;\n"
"border: none;"));
        m_lineLongUserSettings->setFrameShape(QFrame::HLine);
        m_lineLongUserSettings->setFrameShadow(QFrame::Sunken);

        verticalLayout_12->addWidget(m_lineLongUserSettings);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(0);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(-1, -1, -1, 0);
        verticalSpacer_7 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_10->addItem(verticalSpacer_7);

        m_lbAccount = new QLabel(m_tabUserSettings);
        m_lbAccount->setObjectName(QStringLiteral("m_lbAccount"));
        m_lbAccount->setFont(font);
        m_lbAccount->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        verticalLayout_10->addWidget(m_lbAccount);

        verticalSpacer_10 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(verticalSpacer_10);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(10);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setSpacing(0);
        horizontalLayout_31->setObjectName(QStringLiteral("horizontalLayout_31"));
        m_lbUserId = new QLabel(m_tabUserSettings);
        m_lbUserId->setObjectName(QStringLiteral("m_lbUserId"));
        m_lbUserId->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        horizontalLayout_31->addWidget(m_lbUserId);

        horizontalSpacer_18 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_31->addItem(horizontalSpacer_18);

        m_strEdUserId = new QLineEdit(m_tabUserSettings);
        m_strEdUserId->setObjectName(QStringLiteral("m_strEdUserId"));
        m_strEdUserId->setMinimumSize(QSize(180, 32));
        m_strEdUserId->setMaximumSize(QSize(180, 32));
        m_strEdUserId->setFocusPolicy(Qt::ClickFocus);
        m_strEdUserId->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"     padding-left: 10px;\n"
" }\n"
"\n"
" QLineEdit:!hover{\n"
"     border: 1px solid #e6e6e6;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #fafafa;\n"
"	 color: #666666;\n"
" }\n"
"\n"
" QLineEdit:hover:!focus{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #fafafa;\n"
"	 color: #666666;\n"
" }\n"
"\n"
" QLineEdit:focus{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #ffffff;\n"
" }"));

        horizontalLayout_31->addWidget(m_strEdUserId);


        verticalLayout_8->addLayout(horizontalLayout_31);

        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setSpacing(0);
        horizontalLayout_32->setObjectName(QStringLiteral("horizontalLayout_32"));
        m_lbUserName = new QLabel(m_tabUserSettings);
        m_lbUserName->setObjectName(QStringLiteral("m_lbUserName"));
        m_lbUserName->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        horizontalLayout_32->addWidget(m_lbUserName);

        horizontalSpacer_19 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_32->addItem(horizontalSpacer_19);

        m_strEdUserName = new QLineEdit(m_tabUserSettings);
        m_strEdUserName->setObjectName(QStringLiteral("m_strEdUserName"));
        m_strEdUserName->setMinimumSize(QSize(180, 32));
        m_strEdUserName->setMaximumSize(QSize(180, 32));
        m_strEdUserName->setFocusPolicy(Qt::ClickFocus);
        m_strEdUserName->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"     padding-left: 10px;\n"
" }\n"
"\n"
" QLineEdit:!hover{\n"
"     border: 1px solid #e6e6e6;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #fafafa;\n"
"	 color: #666666;\n"
" }\n"
"\n"
" QLineEdit:hover:!focus{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #fafafa;\n"
"	 color: #666666;\n"
" }\n"
"\n"
" QLineEdit:focus{\n"
"     border: 1px solid #0e88eb;\n"
"     border-radius: 2px;\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 background-color: #ffffff;\n"
" }"));

        horizontalLayout_32->addWidget(m_strEdUserName);


        verticalLayout_8->addLayout(horizontalLayout_32);


        verticalLayout_10->addLayout(verticalLayout_8);

        verticalSpacer_36 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(verticalSpacer_36);


        horizontalLayout_5->addLayout(verticalLayout_10);

        horizontalSpacer_4 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(0);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalSpacer_8 = new QSpacerItem(312, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_11->addItem(verticalSpacer_8);

        m_lbEquipment = new QLabel(m_tabUserSettings);
        m_lbEquipment->setObjectName(QStringLiteral("m_lbEquipment"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(m_lbEquipment->sizePolicy().hasHeightForWidth());
        m_lbEquipment->setSizePolicy(sizePolicy3);
        m_lbEquipment->setFont(font);
        m_lbEquipment->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        verticalLayout_11->addWidget(m_lbEquipment);

        m_vSpacerUpper = new QSpacerItem(312, 30, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_11->addItem(m_vSpacerUpper);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(0);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(-1, -1, -1, 0);
        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setSpacing(0);
        horizontalLayout_28->setObjectName(QStringLiteral("horizontalLayout_28"));
        m_lbMircoPhone = new QLabel(m_tabUserSettings);
        m_lbMircoPhone->setObjectName(QStringLiteral("m_lbMircoPhone"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(m_lbMircoPhone->sizePolicy().hasHeightForWidth());
        m_lbMircoPhone->setSizePolicy(sizePolicy4);
        m_lbMircoPhone->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        horizontalLayout_28->addWidget(m_lbMircoPhone);

        horizontalSpacer_9 = new QSpacerItem(16, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_28->addItem(horizontalSpacer_9);

        m_cbMircoPhone = new ZegoComboBox(m_tabUserSettings);
        m_cbMircoPhone->setObjectName(QStringLiteral("m_cbMircoPhone"));
        sizePolicy3.setHeightForWidth(m_cbMircoPhone->sizePolicy().hasHeightForWidth());
        m_cbMircoPhone->setSizePolicy(sizePolicy3);
        m_cbMircoPhone->setMinimumSize(QSize(250, 32));
        m_cbMircoPhone->setMaximumSize(QSize(250, 32));
        m_cbMircoPhone->setFrame(true);

        horizontalLayout_28->addWidget(m_cbMircoPhone);


        verticalLayout_9->addLayout(horizontalLayout_28);

        verticalSpacer_37 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_9->addItem(verticalSpacer_37);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setSpacing(0);
        horizontalLayout_29->setObjectName(QStringLiteral("horizontalLayout_29"));
        m_lbCamera = new QLabel(m_tabUserSettings);
        m_lbCamera->setObjectName(QStringLiteral("m_lbCamera"));
        sizePolicy4.setHeightForWidth(m_lbCamera->sizePolicy().hasHeightForWidth());
        m_lbCamera->setSizePolicy(sizePolicy4);
        m_lbCamera->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        horizontalLayout_29->addWidget(m_lbCamera);

        horizontalSpacer_29 = new QSpacerItem(16, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_29->addItem(horizontalSpacer_29);

        m_cbCamera = new ZegoComboBox(m_tabUserSettings);
        m_cbCamera->setObjectName(QStringLiteral("m_cbCamera"));
        sizePolicy3.setHeightForWidth(m_cbCamera->sizePolicy().hasHeightForWidth());
        m_cbCamera->setSizePolicy(sizePolicy3);
        m_cbCamera->setMinimumSize(QSize(250, 32));
        m_cbCamera->setMaximumSize(QSize(250, 32));

        horizontalLayout_29->addWidget(m_cbCamera);


        verticalLayout_9->addLayout(horizontalLayout_29);

        verticalSpacer_38 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_9->addItem(verticalSpacer_38);

        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setSpacing(0);
        horizontalLayout_30->setObjectName(QStringLiteral("horizontalLayout_30"));
        m_lbCamera2 = new QLabel(m_tabUserSettings);
        m_lbCamera2->setObjectName(QStringLiteral("m_lbCamera2"));
        m_lbCamera2->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        horizontalLayout_30->addWidget(m_lbCamera2);

        horizontalSpacer_33 = new QSpacerItem(8, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_30->addItem(horizontalSpacer_33);

        m_cbCamera2 = new ZegoComboBox(m_tabUserSettings);
        m_cbCamera2->setObjectName(QStringLiteral("m_cbCamera2"));
        sizePolicy3.setHeightForWidth(m_cbCamera2->sizePolicy().hasHeightForWidth());
        m_cbCamera2->setSizePolicy(sizePolicy3);
        m_cbCamera2->setMinimumSize(QSize(250, 32));
        m_cbCamera2->setMaximumSize(QSize(250, 32));

        horizontalLayout_30->addWidget(m_cbCamera2);


        verticalLayout_9->addLayout(horizontalLayout_30);

        m_vSpacerBottom = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(m_vSpacerBottom);


        verticalLayout_11->addLayout(verticalLayout_9);


        horizontalLayout_5->addLayout(verticalLayout_11);


        verticalLayout_12->addLayout(horizontalLayout_5);

        verticalSpacer_9 = new QSpacerItem(591, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_12->addItem(verticalSpacer_9);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        m_lbVersion = new QLabel(m_tabUserSettings);
        m_lbVersion->setObjectName(QStringLiteral("m_lbVersion"));
        m_lbVersion->setMinimumSize(QSize(0, 0));
        m_lbVersion->setMaximumSize(QSize(16777215, 16777215));
        m_lbVersion->setFont(font);
        m_lbVersion->setStyleSheet(QString::fromUtf8(" QLabel{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #666666;\n"
" }"));

        horizontalLayout_7->addWidget(m_lbVersion);

        horizontalSpacer = new QSpacerItem(18, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        m_bUploadLog = new QPushButton(m_tabUserSettings);
        m_bUploadLog->setObjectName(QStringLiteral("m_bUploadLog"));
        m_bUploadLog->setMinimumSize(QSize(100, 34));
        m_bUploadLog->setMaximumSize(QSize(100, 34));
        m_bUploadLog->setStyleSheet(QString::fromUtf8("QPushButton:!hover#m_bUploadLog{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 border-radius: 2px;\n"
"     border: 1px solid #0e88eb;\n"
"     background-color: #ffffff;\n"
"     color: #0e88eb;\n"
" }\n"
"\n"
" QPushButton:hover:!pressed#m_bUploadLog{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 border-radius: 2px;\n"
"     border: 1px solid #0e88eb;\n"
"     background-color: #0e88eb;\n"
"     color: #ffffff;\n"
" }\n"
"\n"
" QPushButton:hover:pressed#m_bUploadLog{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 16px;\n"
"	 border-radius: 2px;\n"
"     border: 1px solid #0d80de;\n"
"     background-color: #0d80de;\n"
"     color: #ffffff;\n"
" }"));

        horizontalLayout_7->addWidget(m_bUploadLog);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        m_lbTips = new QLabel(m_tabUserSettings);
        m_lbTips->setObjectName(QStringLiteral("m_lbTips"));
        m_lbTips->setStyleSheet(QString::fromUtf8("QLabel#m_lbTips{\n"
"     font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"     font-size: 14px;\n"
"	 color: #b2b2b2;\n"
" }"));

        horizontalLayout_7->addWidget(m_lbTips);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);


        verticalLayout_12->addLayout(horizontalLayout_7);

        verticalSpacer_6 = new QSpacerItem(591, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_12->addItem(verticalSpacer_6);


        verticalLayout_13->addLayout(verticalLayout_12);

        m_tabSettings->addTab(m_tabUserSettings, QString());

        verticalLayout_7->addWidget(m_tabSettings);


        verticalLayout->addWidget(m_zoneSettings);

        verticalSpacer_32 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_32);


        horizontalLayout_4->addLayout(verticalLayout);

        horizontalLayout_4->setStretch(0, 280);
        horizontalLayout_4->setStretch(1, 650);

        verticalLayout_6->addLayout(horizontalLayout_4);


        retranslateUi(ZegoMainDialog);

        m_bSingleMode->setDefault(false);
        m_tabSettings->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ZegoMainDialog);
    } // setupUi

    void retranslateUi(QDialog *ZegoMainDialog)
    {
        ZegoMainDialog->setWindowTitle(QApplication::translate("ZegoMainDialog", "ZegoLiveDemo", Q_NULLPTR));
        m_lbTitle->setText(QApplication::translate("ZegoMainDialog", "ZegoLiveDemo(\345\233\275\345\206\205\347\211\210)", Q_NULLPTR));
        m_lbTitleVersion->setText(QApplication::translate("ZegoMainDialog", "\347\211\210\346\234\254:1.0.0.2", Q_NULLPTR));
        m_bJumpToNet->setText(QString());
        m_bMin->setText(QString());
        m_bClose->setText(QString());
        m_lbCreateRoom->setText(QApplication::translate("ZegoMainDialog", "\345\211\265\345\273\272\346\210\277\351\227\264", Q_NULLPTR));
        m_lbName->setText(QApplication::translate("ZegoMainDialog", "\345\220\215\347\247\260", Q_NULLPTR));
        m_edRoomName->setPlaceholderText(QApplication::translate("ZegoMainDialog", "\350\257\267\350\276\223\345\205\245\346\210\277\351\227\264\345\220\215\347\247\260", Q_NULLPTR));
        m_lbMode->setText(QApplication::translate("ZegoMainDialog", "\346\250\241\345\274\217", Q_NULLPTR));
        m_bMixMode->setText(QApplication::translate("ZegoMainDialog", "\346\267\267\346\265\201\346\250\241\345\274\217", Q_NULLPTR));
        m_bSingleMode->setText(QApplication::translate("ZegoMainDialog", "\345\215\225\344\270\273\346\222\255\346\250\241\345\274\217", Q_NULLPTR));
        m_bMultiMode->setText(QApplication::translate("ZegoMainDialog", "\350\277\236\351\272\246\346\250\241\345\274\217", Q_NULLPTR));
        m_bPublish2StreamMode->setText(QApplication::translate("ZegoMainDialog", "\346\216\250\345\217\214\346\265\201\346\250\241\345\274\217", Q_NULLPTR));
        m_bCreateRoom->setText(QApplication::translate("ZegoMainDialog", "+ \345\210\233\345\273\272\346\210\277\351\227\264", Q_NULLPTR));
        m_TitleList->setText(QApplication::translate("ZegoMainDialog", "\347\233\264\346\222\255\351\227\264\345\210\227\350\241\250", Q_NULLPTR));
        m_bRefreshRoomList->setText(QApplication::translate("ZegoMainDialog", "\345\210\267\346\226\260", Q_NULLPTR));
        m_bExtremelyHigh->setText(QApplication::translate("ZegoMainDialog", "\346\236\201\351\253\230\350\264\250\351\207\217", Q_NULLPTR));
        m_bSuperHigh->setText(QApplication::translate("ZegoMainDialog", "\350\266\205\351\253\230\350\264\250\351\207\217", Q_NULLPTR));
        m_bHigh->setText(QApplication::translate("ZegoMainDialog", "\351\253\230\350\264\250\351\207\217", Q_NULLPTR));
        m_bStandard->setText(QApplication::translate("ZegoMainDialog", "\346\240\207\345\207\206\350\264\250\351\207\217", Q_NULLPTR));
        m_bLow->setText(QApplication::translate("ZegoMainDialog", "\344\275\216\350\264\250\351\207\217", Q_NULLPTR));
        m_bSuperLow->setText(QApplication::translate("ZegoMainDialog", "\350\266\205\344\275\216\350\264\250\351\207\217", Q_NULLPTR));
        m_bCustom->setText(QApplication::translate("ZegoMainDialog", "\350\207\252\345\256\232\344\271\211", Q_NULLPTR));
        m_lbResolution->setText(QApplication::translate("ZegoMainDialog", "\345\210\206\350\276\250\347\216\207", Q_NULLPTR));
        m_lbValueResolution->setText(QApplication::translate("ZegoMainDialog", "unknown", Q_NULLPTR));
        m_bResolutionDown->setText(QString());
        m_bResolutionUp->setText(QString());
        m_lbFPS->setText(QApplication::translate("ZegoMainDialog", "\345\270\247\347\216\207", Q_NULLPTR));
        m_lbValueFPS->setText(QApplication::translate("ZegoMainDialog", "unknown", Q_NULLPTR));
        m_bFPSDown->setText(QString());
        m_bFPSUp->setText(QString());
        m_lbBitrate->setText(QApplication::translate("ZegoMainDialog", "\347\240\201\347\216\207", Q_NULLPTR));
        m_lbValueBitrate->setText(QApplication::translate("ZegoMainDialog", "unknown", Q_NULLPTR));
        m_bBitrateDown->setText(QString());
        m_bBitrateUp->setText(QString());
        m_tabSettings->setTabText(m_tabSettings->indexOf(m_tabVideoConfig), QApplication::translate("ZegoMainDialog", "\350\247\206\351\242\221\345\217\202\346\225\260", Q_NULLPTR));
        m_lbEnvironment->setText(QApplication::translate("ZegoMainDialog", "Environment", Q_NULLPTR));
        m_lbTestEnv->setText(QApplication::translate("ZegoMainDialog", "\346\265\213\350\257\225\347\216\257\345\242\203", Q_NULLPTR));
        m_switchTestEnv->setText(QString());
        m_lbAPPID->setText(QApplication::translate("ZegoMainDialog", "APP ID", Q_NULLPTR));
        m_lbAPPSign->setText(QApplication::translate("ZegoMainDialog", "APP Sign", Q_NULLPTR));
        m_lbAdvanced->setText(QApplication::translate("ZegoMainDialog", "Advanced", Q_NULLPTR));
        m_lbCapture->setText(QApplication::translate("ZegoMainDialog", "\345\244\226\351\203\250\351\207\207\351\233\206&\346\270\262\346\237\223", Q_NULLPTR));
        m_switchCapture->setText(QString());
        m_lbFilter->setText(QApplication::translate("ZegoMainDialog", "\345\244\226\351\203\250\346\273\244\351\225\234", Q_NULLPTR));
        m_switchFilter->setText(QString());
        m_lbVerticalCapture->setText(QApplication::translate("ZegoMainDialog", "\347\253\226\345\261\217\351\207\207\351\233\206", Q_NULLPTR));
        m_switchVerticalCapture->setText(QString());
        m_lbExtra->setText(QApplication::translate("ZegoMainDialog", "Extra", Q_NULLPTR));
        m_lbSurfaceMerge->setText(QApplication::translate("ZegoMainDialog", "\345\261\217\345\271\225\347\233\264\346\222\255", Q_NULLPTR));
        m_switchSurfaceMerge->setText(QString());
        m_lbCameraRotation->setText(QApplication::translate("ZegoMainDialog", "\346\221\204\345\203\217\345\244\264\346\227\213\350\275\254", Q_NULLPTR));
        m_lbAudioLeft->setText(QApplication::translate("ZegoMainDialog", "Audio", Q_NULLPTR));
        m_lbReverb->setText(QApplication::translate("ZegoMainDialog", "\346\267\267\345\223\215", Q_NULLPTR));
        m_switchReverb->setText(QString());
        m_lbVirtualStereo->setText(QApplication::translate("ZegoMainDialog", "\350\231\232\346\213\237\347\253\213\344\275\223\345\243\260", Q_NULLPTR));
        m_switchVirtualStereo->setText(QString());
        m_lbAudioRight->setText(QApplication::translate("ZegoMainDialog", "Audio", Q_NULLPTR));
        m_lbNational->setText(QApplication::translate("ZegoMainDialog", "\345\233\275\351\231\205\347\211\210", Q_NULLPTR));
        m_switchNational->setText(QString());
        m_tabSettings->setTabText(m_tabSettings->indexOf(m_tabExtraSettings), QApplication::translate("ZegoMainDialog", "\351\253\230\347\272\247\350\256\276\347\275\256", Q_NULLPTR));
        m_lbAccount->setText(QApplication::translate("ZegoMainDialog", "Account", Q_NULLPTR));
        m_lbUserId->setText(QApplication::translate("ZegoMainDialog", "\347\224\250\346\210\267ID", Q_NULLPTR));
        m_lbUserName->setText(QApplication::translate("ZegoMainDialog", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        m_lbEquipment->setText(QApplication::translate("ZegoMainDialog", "Equipment", Q_NULLPTR));
        m_lbMircoPhone->setText(QApplication::translate("ZegoMainDialog", "\351\272\246\345\205\213\351\243\216", Q_NULLPTR));
        m_lbCamera->setText(QApplication::translate("ZegoMainDialog", "\346\221\204\345\203\217\345\244\264", Q_NULLPTR));
        m_lbCamera2->setText(QApplication::translate("ZegoMainDialog", "\346\221\204\345\203\217\345\244\2642", Q_NULLPTR));
        m_lbVersion->setText(QApplication::translate("ZegoMainDialog", "Version", Q_NULLPTR));
        m_bUploadLog->setText(QApplication::translate("ZegoMainDialog", "\344\270\212\344\274\240\346\227\245\345\277\227", Q_NULLPTR));
        m_lbTips->setText(QApplication::translate("ZegoMainDialog", "(\345\246\202\351\201\207\347\250\213\345\272\217\345\264\251\346\272\203\347\255\211\351\227\256\351\242\230,\350\257\267\347\202\271\345\207\273\344\270\212\344\274\240\346\227\245\345\277\227,\347\255\211\345\276\205\350\247\243\345\206\263)", Q_NULLPTR));
        m_tabSettings->setTabText(m_tabSettings->indexOf(m_tabUserSettings), QApplication::translate("ZegoMainDialog", "\344\270\252\344\272\272\350\256\276\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ZegoMainDialog: public Ui_ZegoMainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZEGOMAINDIALOG_H
