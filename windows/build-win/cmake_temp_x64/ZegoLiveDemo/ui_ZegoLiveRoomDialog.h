/********************************************************************************
** Form generated from reading UI file 'ZegoLiveRoomDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZEGOLIVEROOMDIALOG_H
#define UI_ZEGOLIVEROOMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <ZegoComboBox.h>
#include <ZegoImageButton.h>
#include <ZegoMicrophoneButton.h>
#include <ZegoSwitchButton.h>

QT_BEGIN_NAMESPACE

class Ui_ZegoLiveRoomDialog
{
public:
    QVBoxLayout *verticalLayout_11;
    QWidget *m_zoneBaseDialog;
    QVBoxLayout *verticalLayout;
    QWidget *m_zoneTitle;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_lbRoomName;
    QHBoxLayout *horizontalLayout;
    ZegoImageButton *m_bMin;
    ZegoImageButton *m_bMax;
    ZegoImageButton *m_bClose;
    QHBoxLayout *horizontalLayout1;
    QWidget *m_zoneLiveView;
    QHBoxLayout *horizontalLayout_ForAVView;
    QWidget *m_zoneLiveView_Inner;
    QHBoxLayout *zoneLiveViewHorizontalLayout;
    QFrame *m_lineBetweenViewAndList;
    QWidget *m_zoneCommonAndUserList;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *m_tabCommonAndUserList;
    QWidget *m_tabContact;
    QVBoxLayout *verticalLayout_3;
    QFrame *m_lineContact;
    QFrame *m_lineLongContact;
    QTableView *m_listChat;
    QWidget *m_tabMember;
    QVBoxLayout *verticalLayout_7;
    QFrame *m_lineMember;
    QFrame *m_lineLongMember;
    QListView *m_listMember;
    QFrame *m_lineMain;
    QHBoxLayout *horizontalLayout2;
    QWidget *m_zoneSettings;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_2;
    QLabel *m_lbEquipment;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_lbMircoPhone;
    QSpacerItem *horizontalSpacer_13;
    ZegoComboBox *m_cbMircoPhone;
    QSpacerItem *m_vSpacer;
    QHBoxLayout *horizontalLayout_6;
    QLabel *m_lbCamera;
    QSpacerItem *horizontalSpacer_14;
    ZegoComboBox *m_cbCamera;
    QSpacerItem *verticalSpacer_17;
    QHBoxLayout *horizontalLayout_7;
    QLabel *m_lbCamera2;
    QSpacerItem *horizontalSpacer_15;
    ZegoComboBox *m_cbCamera2;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer;
    QLabel *m_lbOperation;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_5;
    ZegoMicrophoneButton *m_bProgMircoPhone;
    QSpacerItem *horizontalSpacer_6;
    ZegoSwitchButton *m_bSound;
    QSpacerItem *horizontalSpacer_16;
    ZegoSwitchButton *m_bCamera;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *m_bAux;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *m_bCapture;
    QSpacerItem *horizontalSpacer_12;
    QSpacerItem *verticalSpacer_15;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_10;
    QSpacerItem *verticalSpacer_10;
    QLabel *m_lbFullScreen;
    QSpacerItem *verticalSpacer_11;
    QPushButton *m_bFullScreen;
    QSpacerItem *verticalSpacer_14;
    QSpacerItem *horizontalSpacer_11;
    QVBoxLayout *verticalLayout_6;
    QSpacerItem *verticalSpacer_6;
    QLabel *m_lbShare;
    QSpacerItem *verticalSpacer_7;
    QPushButton *m_bShare;
    QSpacerItem *verticalSpacer_13;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_18;
    QFrame *m_lineBetweenSettingsAndEdit;
    QWidget *m_zoneInput;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *verticalLayout_8;
    QTextEdit *m_edInput;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *m_bRequestJoinLive;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *m_bSendMessage;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *verticalSpacer_9;

    void setupUi(QDialog *ZegoLiveRoomDialog)
    {
        if (ZegoLiveRoomDialog->objectName().isEmpty())
            ZegoLiveRoomDialog->setObjectName(QStringLiteral("ZegoLiveRoomDialog"));
        ZegoLiveRoomDialog->resize(1283, 763);
        ZegoLiveRoomDialog->setStyleSheet(QStringLiteral("border: none;"));
        verticalLayout_11 = new QVBoxLayout(ZegoLiveRoomDialog);
        verticalLayout_11->setSpacing(0);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        m_zoneBaseDialog = new QWidget(ZegoLiveRoomDialog);
        m_zoneBaseDialog->setObjectName(QStringLiteral("m_zoneBaseDialog"));
        m_zoneBaseDialog->setStyleSheet(QStringLiteral("background-color: #0e88eb;"));
        verticalLayout = new QVBoxLayout(m_zoneBaseDialog);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        m_zoneTitle = new QWidget(m_zoneBaseDialog);
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
        QIcon icon;
        icon.addFile(QStringLiteral(":/min"), QSize(), QIcon::Normal, QIcon::Off);
        m_bMin->setIcon(icon);
        m_bMin->setFlat(true);

        horizontalLayout->addWidget(m_bMin);

        m_bMax = new ZegoImageButton(m_zoneTitle);
        m_bMax->setObjectName(QStringLiteral("m_bMax"));
        sizePolicy1.setHeightForWidth(m_bMax->sizePolicy().hasHeightForWidth());
        m_bMax->setSizePolicy(sizePolicy1);
        m_bMax->setMinimumSize(QSize(30, 40));
        m_bMax->setMaximumSize(QSize(30, 40));
        m_bMax->setFocusPolicy(Qt::NoFocus);
        m_bMax->setStyleSheet(QLatin1String("QPushButton{\n"
"    border: 1px solid #0e88eb;\n"
"    background-color: #0e88eb;\n"
"}\n"
"\n"
"QPushButton:checked{\n"
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
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/max"), QSize(), QIcon::Normal, QIcon::Off);
        m_bMax->setIcon(icon1);
        m_bMax->setCheckable(true);
        m_bMax->setFlat(true);

        horizontalLayout->addWidget(m_bMax);

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
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/close"), QSize(), QIcon::Normal, QIcon::Off);
        m_bClose->setIcon(icon2);
        m_bClose->setFlat(true);

        horizontalLayout->addWidget(m_bClose);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(m_zoneTitle);

        horizontalLayout1 = new QHBoxLayout();
        horizontalLayout1->setSpacing(0);
        horizontalLayout1->setObjectName(QStringLiteral("horizontalLayout1"));
        m_zoneLiveView = new QWidget(m_zoneBaseDialog);
        m_zoneLiveView->setObjectName(QStringLiteral("m_zoneLiveView"));
        m_zoneLiveView->setEnabled(true);
        sizePolicy.setHeightForWidth(m_zoneLiveView->sizePolicy().hasHeightForWidth());
        m_zoneLiveView->setSizePolicy(sizePolicy);
        m_zoneLiveView->setAutoFillBackground(false);
        m_zoneLiveView->setStyleSheet(QLatin1String("background-color: #ffffff;\n"
"border: none;"));
        horizontalLayout_ForAVView = new QHBoxLayout(m_zoneLiveView);
        horizontalLayout_ForAVView->setSpacing(0);
        horizontalLayout_ForAVView->setObjectName(QStringLiteral("horizontalLayout_ForAVView"));
        horizontalLayout_ForAVView->setContentsMargins(0, 0, 0, 0);
        m_zoneLiveView_Inner = new QWidget(m_zoneLiveView);
        m_zoneLiveView_Inner->setObjectName(QStringLiteral("m_zoneLiveView_Inner"));
        m_zoneLiveView_Inner->setStyleSheet(QStringLiteral("background-color: #383838;"));
        zoneLiveViewHorizontalLayout = new QHBoxLayout(m_zoneLiveView_Inner);
        zoneLiveViewHorizontalLayout->setSpacing(0);
        zoneLiveViewHorizontalLayout->setObjectName(QStringLiteral("zoneLiveViewHorizontalLayout"));
        zoneLiveViewHorizontalLayout->setContentsMargins(0, 0, 0, 0);

        horizontalLayout_ForAVView->addWidget(m_zoneLiveView_Inner);


        horizontalLayout1->addWidget(m_zoneLiveView);

        m_lineBetweenViewAndList = new QFrame(m_zoneBaseDialog);
        m_lineBetweenViewAndList->setObjectName(QStringLiteral("m_lineBetweenViewAndList"));
        m_lineBetweenViewAndList->setMinimumSize(QSize(1, 0));
        m_lineBetweenViewAndList->setMaximumSize(QSize(1, 16777215));
        m_lineBetweenViewAndList->setStyleSheet(QLatin1String("border: none;\n"
"background-color: #e6e6e6;"));
        m_lineBetweenViewAndList->setFrameShape(QFrame::VLine);
        m_lineBetweenViewAndList->setFrameShadow(QFrame::Sunken);

        horizontalLayout1->addWidget(m_lineBetweenViewAndList);

        m_zoneCommonAndUserList = new QWidget(m_zoneBaseDialog);
        m_zoneCommonAndUserList->setObjectName(QStringLiteral("m_zoneCommonAndUserList"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_zoneCommonAndUserList->sizePolicy().hasHeightForWidth());
        m_zoneCommonAndUserList->setSizePolicy(sizePolicy2);
        m_zoneCommonAndUserList->setMinimumSize(QSize(320, 0));
        m_zoneCommonAndUserList->setMaximumSize(QSize(320, 16777215));
        m_zoneCommonAndUserList->setStyleSheet(QStringLiteral("background-color: #ffffff;"));
        verticalLayout_2 = new QVBoxLayout(m_zoneCommonAndUserList);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        m_tabCommonAndUserList = new QTabWidget(m_zoneCommonAndUserList);
        m_tabCommonAndUserList->setObjectName(QStringLiteral("m_tabCommonAndUserList"));
        m_tabCommonAndUserList->setStyleSheet(QString::fromUtf8("QTabWidget::pane{\n"
"	border: none;\n"
"}\n"
"\n"
"QTabWidget::tab-bar{\n"
"    left: 0px;\n"
"}\n"
"\n"
"QTabBar::tab{\n"
"    width: 160px;\n"
"    height: 40px;\n"
"    margin: 0 0 0 0;\n"
"	font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"	font-size: 16px;\n"
"	color: #333333;\n"
"	background-color: #ffffff;\n"
"}\n"
"\n"
"QTabBar::tab:selected{\n"
"	width: 160px;\n"
"	height: 40px;\n"
"	font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"	font-size: 16px;\n"
"	color: #0e88eb;\n"
"	background-color: #ffffff;\n"
"}"));
        m_tabContact = new QWidget();
        m_tabContact->setObjectName(QStringLiteral("m_tabContact"));
        verticalLayout_3 = new QVBoxLayout(m_tabContact);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        m_lineContact = new QFrame(m_tabContact);
        m_lineContact->setObjectName(QStringLiteral("m_lineContact"));
        m_lineContact->setMinimumSize(QSize(0, 2));
        m_lineContact->setMaximumSize(QSize(16777215, 2));
        m_lineContact->setStyleSheet(QLatin1String("border: none;\n"
"background-color: #0e88eb;\n"
"margin-right: 160px;"));
        m_lineContact->setFrameShape(QFrame::HLine);
        m_lineContact->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(m_lineContact);

        m_lineLongContact = new QFrame(m_tabContact);
        m_lineLongContact->setObjectName(QStringLiteral("m_lineLongContact"));
        m_lineLongContact->setMinimumSize(QSize(0, 1));
        m_lineLongContact->setMaximumSize(QSize(16777215, 1));
        m_lineLongContact->setStyleSheet(QLatin1String("border: none;\n"
"background-color: #e6e6e6;"));
        m_lineLongContact->setFrameShape(QFrame::HLine);
        m_lineLongContact->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(m_lineLongContact);

        m_listChat = new QTableView(m_tabContact);
        m_listChat->setObjectName(QStringLiteral("m_listChat"));
        m_listChat->setStyleSheet(QString::fromUtf8("QTableView{\n"
"font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 14px;\n"
"color: #666666;\n"
"padding-top: 5px;\n"
"padding-left: 14px;\n"
"}\n"
"\n"
"QTableView::item{\n"
"    border: none;\n"
"}\n"
"\n"
"QScrollBar:vertical {                 \n"
"    background:transparent;  \n"
"    width:9px;  \n"
"    margin: 0px 0px 2px 0px;  \n"
"}  \n"
"  \n"
"QScrollBar::handle:vertical {  \n"
"    background: rgb(195, 195, 195);  \n"
"    min-height: 20px;  \n"
"    border-radius: 3px;  \n"
"}  \n"
"  \n"
"QScrollBar::handle:vertical:hover{  \n"
"    background:rgba(0,0,0,30%);  \n"
"}  \n"
"  \n"
"QScrollBar::add-line:vertical {  \n"
"    height: 0px;  \n"
"    subcontrol-position: bottom;  \n"
"    subcontrol-origin: margin;  \n"
"}  \n"
"  \n"
"QScrollBar::sub-line:vertical {  \n"
"    height: 0px;  \n"
"    subcontrol-position: top;  \n"
"    subcontrol-origin: margin;  \n"
"}"));
        m_listChat->setFrameShape(QFrame::NoFrame);
        m_listChat->setShowGrid(false);

        verticalLayout_3->addWidget(m_listChat);

        m_tabCommonAndUserList->addTab(m_tabContact, QString());
        m_tabMember = new QWidget();
        m_tabMember->setObjectName(QStringLiteral("m_tabMember"));
        verticalLayout_7 = new QVBoxLayout(m_tabMember);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        m_lineMember = new QFrame(m_tabMember);
        m_lineMember->setObjectName(QStringLiteral("m_lineMember"));
        m_lineMember->setMinimumSize(QSize(0, 2));
        m_lineMember->setMaximumSize(QSize(16777215, 2));
        m_lineMember->setStyleSheet(QLatin1String("border: none;\n"
"background-color: #0e88eb;\n"
"margin-left: 160px;"));
        m_lineMember->setFrameShape(QFrame::HLine);
        m_lineMember->setFrameShadow(QFrame::Sunken);

        verticalLayout_7->addWidget(m_lineMember);

        m_lineLongMember = new QFrame(m_tabMember);
        m_lineLongMember->setObjectName(QStringLiteral("m_lineLongMember"));
        m_lineLongMember->setMinimumSize(QSize(0, 1));
        m_lineLongMember->setMaximumSize(QSize(16777215, 1));
        m_lineLongMember->setStyleSheet(QLatin1String("border: none;\n"
"background-color: #e6e6e6;"));
        m_lineLongMember->setFrameShape(QFrame::HLine);
        m_lineLongMember->setFrameShadow(QFrame::Sunken);

        verticalLayout_7->addWidget(m_lineLongMember);

        m_listMember = new QListView(m_tabMember);
        m_listMember->setObjectName(QStringLiteral("m_listMember"));
        m_listMember->setStyleSheet(QString::fromUtf8("QListView{\n"
"font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 14px;\n"
"color: #666666;\n"
"padding-left: 14px;\n"
"\n"
"padding-top: 5px;\n"
"}\n"
"\n"
"QListView::item{\n"
"    width: 290px;\n"
"    min-height: 8px;\n"
"    margin-top: 10px;\n"
"}\n"
"\n"
"QScrollBar:vertical {                 \n"
"    background:transparent;  \n"
"    width:9px;  \n"
"    margin: 0px 0px 2px 0px;  \n"
"}  \n"
"  \n"
"QScrollBar::handle:vertical {  \n"
"    background: rgb(195, 195, 195);  \n"
"    min-height: 20px;  \n"
"    border-radius: 3px;  \n"
"}  \n"
"  \n"
"QScrollBar::handle:vertical:hover{  \n"
"    background:rgba(0,0,0,30%);  \n"
"}  \n"
"  \n"
"QScrollBar::add-line:vertical {  \n"
"    height: 0px;  \n"
"    subcontrol-position: bottom;  \n"
"    subcontrol-origin: margin;  \n"
"}  \n"
"  \n"
"QScrollBar::sub-line:vertical {  \n"
"    height: 0px;  \n"
"    subcontrol-position: top;  \n"
"    subcontrol-origin: margin;  \n"
"}"));
        m_listMember->setSelectionMode(QAbstractItemView::NoSelection);
        m_listMember->setSpacing(0);

        verticalLayout_7->addWidget(m_listMember);

        m_tabCommonAndUserList->addTab(m_tabMember, QString());

        verticalLayout_2->addWidget(m_tabCommonAndUserList);


        horizontalLayout1->addWidget(m_zoneCommonAndUserList);


        verticalLayout->addLayout(horizontalLayout1);

        m_lineMain = new QFrame(m_zoneBaseDialog);
        m_lineMain->setObjectName(QStringLiteral("m_lineMain"));
        m_lineMain->setMinimumSize(QSize(0, 1));
        m_lineMain->setMaximumSize(QSize(16777215, 1));
        m_lineMain->setStyleSheet(QLatin1String("border: none;\n"
"background-color: #e6e6e6;"));
        m_lineMain->setFrameShape(QFrame::HLine);
        m_lineMain->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(m_lineMain);

        horizontalLayout2 = new QHBoxLayout();
        horizontalLayout2->setSpacing(0);
        horizontalLayout2->setObjectName(QStringLiteral("horizontalLayout2"));
        horizontalLayout2->setSizeConstraint(QLayout::SetFixedSize);
        m_zoneSettings = new QWidget(m_zoneBaseDialog);
        m_zoneSettings->setObjectName(QStringLiteral("m_zoneSettings"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(m_zoneSettings->sizePolicy().hasHeightForWidth());
        m_zoneSettings->setSizePolicy(sizePolicy3);
        m_zoneSettings->setMinimumSize(QSize(0, 180));
        m_zoneSettings->setMaximumSize(QSize(16777215, 180));
        m_zoneSettings->setStyleSheet(QStringLiteral("background-color: #ffffff;"));
        verticalLayout_12 = new QVBoxLayout(m_zoneSettings);
        verticalLayout_12->setSpacing(0);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(0);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalSpacer = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(-1, -1, -1, 0);
        verticalSpacer_2 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_2);

        m_lbEquipment = new QLabel(m_zoneSettings);
        m_lbEquipment->setObjectName(QStringLiteral("m_lbEquipment"));
        m_lbEquipment->setMinimumSize(QSize(18, 0));
        m_lbEquipment->setMaximumSize(QSize(16777215, 18));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        m_lbEquipment->setFont(font);
        m_lbEquipment->setStyleSheet(QString::fromUtf8("font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 14px;\n"
"color: #666666;"));

        verticalLayout_4->addWidget(m_lbEquipment);

        verticalSpacer_3 = new QSpacerItem(20, 14, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        m_lbMircoPhone = new QLabel(m_zoneSettings);
        m_lbMircoPhone->setObjectName(QStringLiteral("m_lbMircoPhone"));
        m_lbMircoPhone->setStyleSheet(QString::fromUtf8("QLabel:!enabled{\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"    font-size: 14px;\n"
"    color: #cccccc;\n"
" }\n"
" \n"
"QLabel:enabled{\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"    font-size: 14px;\n"
"    color: #666666;\n"
" }"));

        horizontalLayout_3->addWidget(m_lbMircoPhone);

        horizontalSpacer_13 = new QSpacerItem(20, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_13);

        m_cbMircoPhone = new ZegoComboBox(m_zoneSettings);
        m_cbMircoPhone->setObjectName(QStringLiteral("m_cbMircoPhone"));
        m_cbMircoPhone->setMinimumSize(QSize(260, 32));
        m_cbMircoPhone->setMaximumSize(QSize(260, 32));
        m_cbMircoPhone->setFrame(true);

        horizontalLayout_3->addWidget(m_cbMircoPhone);


        verticalLayout_4->addLayout(horizontalLayout_3);

        m_vSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(m_vSpacer);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        m_lbCamera = new QLabel(m_zoneSettings);
        m_lbCamera->setObjectName(QStringLiteral("m_lbCamera"));
        m_lbCamera->setStyleSheet(QString::fromUtf8("QLabel:!enabled{\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"    font-size: 14px;\n"
"    color: #cccccc;\n"
" }\n"
" \n"
"QLabel:enabled{\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"    font-size: 14px;\n"
"    color: #666666;\n"
" }"));

        horizontalLayout_6->addWidget(m_lbCamera);

        horizontalSpacer_14 = new QSpacerItem(20, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_14);

        m_cbCamera = new ZegoComboBox(m_zoneSettings);
        m_cbCamera->setObjectName(QStringLiteral("m_cbCamera"));
        m_cbCamera->setMinimumSize(QSize(260, 32));
        m_cbCamera->setMaximumSize(QSize(260, 32));

        horizontalLayout_6->addWidget(m_cbCamera);


        verticalLayout_4->addLayout(horizontalLayout_6);

        verticalSpacer_17 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_17);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        m_lbCamera2 = new QLabel(m_zoneSettings);
        m_lbCamera2->setObjectName(QStringLiteral("m_lbCamera2"));
        m_lbCamera2->setStyleSheet(QString::fromUtf8("QLabel:!enabled{\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"    font-size: 14px;\n"
"    color: #cccccc;\n"
" }\n"
" \n"
"QLabel:enabled{\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"    font-size: 14px;\n"
"    color: #666666;\n"
" }"));

        horizontalLayout_7->addWidget(m_lbCamera2);

        horizontalSpacer_15 = new QSpacerItem(15, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_15);

        m_cbCamera2 = new ZegoComboBox(m_zoneSettings);
        m_cbCamera2->setObjectName(QStringLiteral("m_cbCamera2"));
        m_cbCamera2->setMinimumSize(QSize(260, 32));
        m_cbCamera2->setMaximumSize(QSize(260, 32));

        horizontalLayout_7->addWidget(m_cbCamera2);


        verticalLayout_4->addLayout(horizontalLayout_7);


        horizontalLayout_9->addLayout(verticalLayout_4);

        horizontalSpacer_2 = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_2);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(-1, 0, -1, -1);
        verticalSpacer = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer);

        m_lbOperation = new QLabel(m_zoneSettings);
        m_lbOperation->setObjectName(QStringLiteral("m_lbOperation"));
        m_lbOperation->setMinimumSize(QSize(0, 18));
        m_lbOperation->setMaximumSize(QSize(16777215, 18));
        m_lbOperation->setFont(font);
        m_lbOperation->setStyleSheet(QString::fromUtf8("font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 14px;\n"
"color: #666666;"));

        verticalLayout_5->addWidget(m_lbOperation);

        verticalSpacer_4 = new QSpacerItem(20, 14, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        m_bProgMircoPhone = new ZegoMicrophoneButton(m_zoneSettings);
        m_bProgMircoPhone->setObjectName(QStringLiteral("m_bProgMircoPhone"));
        sizePolicy1.setHeightForWidth(m_bProgMircoPhone->sizePolicy().hasHeightForWidth());
        m_bProgMircoPhone->setSizePolicy(sizePolicy1);
        m_bProgMircoPhone->setMinimumSize(QSize(32, 32));
        m_bProgMircoPhone->setMaximumSize(QSize(32, 32));
        m_bProgMircoPhone->setCursor(QCursor(Qt::PointingHandCursor));
        m_bProgMircoPhone->setCheckable(true);
        m_bProgMircoPhone->setChecked(true);

        horizontalLayout_5->addWidget(m_bProgMircoPhone);

        horizontalSpacer_6 = new QSpacerItem(14, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);

        m_bSound = new ZegoSwitchButton(m_zoneSettings);
        m_bSound->setObjectName(QStringLiteral("m_bSound"));
        sizePolicy1.setHeightForWidth(m_bSound->sizePolicy().hasHeightForWidth());
        m_bSound->setSizePolicy(sizePolicy1);
        m_bSound->setMinimumSize(QSize(32, 32));
        m_bSound->setMaximumSize(QSize(32, 32));
        m_bSound->setCursor(QCursor(Qt::PointingHandCursor));
        m_bSound->setCheckable(true);
        m_bSound->setChecked(true);

        horizontalLayout_5->addWidget(m_bSound);

        horizontalSpacer_16 = new QSpacerItem(14, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_16);

        m_bCamera = new ZegoSwitchButton(m_zoneSettings);
        m_bCamera->setObjectName(QStringLiteral("m_bCamera"));
        m_bCamera->setMinimumSize(QSize(32, 32));
        m_bCamera->setMaximumSize(QSize(32, 32));
        m_bCamera->setCursor(QCursor(Qt::PointingHandCursor));
        m_bCamera->setCheckable(true);
        m_bCamera->setChecked(true);

        horizontalLayout_5->addWidget(m_bCamera);

        horizontalSpacer_5 = new QSpacerItem(136, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        verticalLayout_5->addLayout(horizontalLayout_5);

        verticalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_4->setContentsMargins(-1, 0, -1, -1);
        m_bAux = new QPushButton(m_zoneSettings);
        m_bAux->setObjectName(QStringLiteral("m_bAux"));
        m_bAux->setMinimumSize(QSize(100, 32));
        m_bAux->setMaximumSize(QSize(100, 32));
        m_bAux->setCursor(QCursor(Qt::PointingHandCursor));
        m_bAux->setStyleSheet(QString::fromUtf8("QPushButton:!enabled{\n"
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

        horizontalLayout_4->addWidget(m_bAux, 0, Qt::AlignTop);

        horizontalSpacer_7 = new QSpacerItem(14, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        m_bCapture = new QPushButton(m_zoneSettings);
        m_bCapture->setObjectName(QStringLiteral("m_bCapture"));
        m_bCapture->setMinimumSize(QSize(100, 32));
        m_bCapture->setMaximumSize(QSize(180, 32));
        m_bCapture->setCursor(QCursor(Qt::PointingHandCursor));
        m_bCapture->setStyleSheet(QString::fromUtf8("QPushButton:!enabled{\n"
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

        horizontalLayout_4->addWidget(m_bCapture, 0, Qt::AlignTop);

        horizontalSpacer_12 = new QSpacerItem(6, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_12);


        verticalLayout_5->addLayout(horizontalLayout_4);

        verticalSpacer_15 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_15);


        horizontalLayout_9->addLayout(verticalLayout_5);

        horizontalSpacer_3 = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(0);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        verticalSpacer_10 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_10->addItem(verticalSpacer_10);

        m_lbFullScreen = new QLabel(m_zoneSettings);
        m_lbFullScreen->setObjectName(QStringLiteral("m_lbFullScreen"));
        m_lbFullScreen->setMinimumSize(QSize(0, 0));
        m_lbFullScreen->setMaximumSize(QSize(16777215, 16777215));
        m_lbFullScreen->setFont(font);
        m_lbFullScreen->setStyleSheet(QString::fromUtf8("font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 14px;\n"
"color: #666666;"));

        verticalLayout_10->addWidget(m_lbFullScreen);

        verticalSpacer_11 = new QSpacerItem(20, 14, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_10->addItem(verticalSpacer_11);

        m_bFullScreen = new QPushButton(m_zoneSettings);
        m_bFullScreen->setObjectName(QStringLiteral("m_bFullScreen"));
        m_bFullScreen->setMinimumSize(QSize(68, 32));
        m_bFullScreen->setMaximumSize(QSize(80, 32));
        m_bFullScreen->setCursor(QCursor(Qt::PointingHandCursor));
        m_bFullScreen->setStyleSheet(QString::fromUtf8("QPushButton:!enabled{\n"
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

        verticalLayout_10->addWidget(m_bFullScreen);

        verticalSpacer_14 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(verticalSpacer_14);


        horizontalLayout_9->addLayout(verticalLayout_10);

        horizontalSpacer_11 = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_11);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(-1, 0, -1, -1);
        verticalSpacer_6 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_6->addItem(verticalSpacer_6);

        m_lbShare = new QLabel(m_zoneSettings);
        m_lbShare->setObjectName(QStringLiteral("m_lbShare"));
        m_lbShare->setMinimumSize(QSize(68, 18));
        m_lbShare->setMaximumSize(QSize(68, 18));
        m_lbShare->setFont(font);
        m_lbShare->setStyleSheet(QString::fromUtf8("font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 14px;\n"
"color: #666666;"));
        m_lbShare->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_6->addWidget(m_lbShare);

        verticalSpacer_7 = new QSpacerItem(20, 14, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_6->addItem(verticalSpacer_7);

        m_bShare = new QPushButton(m_zoneSettings);
        m_bShare->setObjectName(QStringLiteral("m_bShare"));
        m_bShare->setMinimumSize(QSize(68, 32));
        m_bShare->setMaximumSize(QSize(68, 32));
        m_bShare->setCursor(QCursor(Qt::PointingHandCursor));
        m_bShare->setStyleSheet(QString::fromUtf8("QPushButton:!enabled{\n"
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

        verticalLayout_6->addWidget(m_bShare, 0, Qt::AlignTop);

        verticalSpacer_13 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_13);


        horizontalLayout_9->addLayout(verticalLayout_6);

        horizontalSpacer_4 = new QSpacerItem(80, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_4);


        verticalLayout_12->addLayout(horizontalLayout_9);

        verticalSpacer_18 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_12->addItem(verticalSpacer_18);


        horizontalLayout2->addWidget(m_zoneSettings);

        m_lineBetweenSettingsAndEdit = new QFrame(m_zoneBaseDialog);
        m_lineBetweenSettingsAndEdit->setObjectName(QStringLiteral("m_lineBetweenSettingsAndEdit"));
        m_lineBetweenSettingsAndEdit->setMinimumSize(QSize(1, 0));
        m_lineBetweenSettingsAndEdit->setMaximumSize(QSize(1, 16777215));
        m_lineBetweenSettingsAndEdit->setStyleSheet(QLatin1String("border: none;\n"
"background-color: #e6e6e6;"));
        m_lineBetweenSettingsAndEdit->setFrameShape(QFrame::VLine);
        m_lineBetweenSettingsAndEdit->setFrameShadow(QFrame::Sunken);

        horizontalLayout2->addWidget(m_lineBetweenSettingsAndEdit);

        m_zoneInput = new QWidget(m_zoneBaseDialog);
        m_zoneInput->setObjectName(QStringLiteral("m_zoneInput"));
        sizePolicy2.setHeightForWidth(m_zoneInput->sizePolicy().hasHeightForWidth());
        m_zoneInput->setSizePolicy(sizePolicy2);
        m_zoneInput->setMinimumSize(QSize(320, 180));
        m_zoneInput->setMaximumSize(QSize(320, 180));
        m_zoneInput->setStyleSheet(QStringLiteral("background-color: #ffffff;"));
        verticalLayout_9 = new QVBoxLayout(m_zoneInput);
        verticalLayout_9->setSpacing(0);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        m_edInput = new QTextEdit(m_zoneInput);
        m_edInput->setObjectName(QStringLiteral("m_edInput"));
        m_edInput->setStyleSheet(QString::fromUtf8("QTextEdit{\n"
"    font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"    font-size: 14px;\n"
"    padding-left: 10px;\n"
"    color: #333333;\n"
"}\n"
"\n"
"QScrollBar:vertical{\n"
"    border:0px solid grey;\n"
"    width: 10px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical{\n"
"     background-color: #dbdbdb;\n"
"     border-radius: 5px;\n"
"     min-height: 20px;\n"
"     \n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover{\n"
"     background-color: #d0d0d0;\n"
"}"));
        m_edInput->setFrameShape(QFrame::NoFrame);

        verticalLayout_8->addWidget(m_edInput);

        verticalSpacer_8 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_8);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_8);

        m_bRequestJoinLive = new QPushButton(m_zoneInput);
        m_bRequestJoinLive->setObjectName(QStringLiteral("m_bRequestJoinLive"));
        m_bRequestJoinLive->setMinimumSize(QSize(100, 32));
        m_bRequestJoinLive->setMaximumSize(QSize(120, 32));
        m_bRequestJoinLive->setCursor(QCursor(Qt::PointingHandCursor));
        m_bRequestJoinLive->setStyleSheet(QString::fromUtf8("QPushButton:!enabled{\n"
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

        horizontalLayout_8->addWidget(m_bRequestJoinLive);

        horizontalSpacer_9 = new QSpacerItem(14, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_9);

        m_bSendMessage = new QPushButton(m_zoneInput);
        m_bSendMessage->setObjectName(QStringLiteral("m_bSendMessage"));
        sizePolicy1.setHeightForWidth(m_bSendMessage->sizePolicy().hasHeightForWidth());
        m_bSendMessage->setSizePolicy(sizePolicy1);
        m_bSendMessage->setMinimumSize(QSize(68, 32));
        m_bSendMessage->setMaximumSize(QSize(68, 32));
        m_bSendMessage->setCursor(QCursor(Qt::PointingHandCursor));
        m_bSendMessage->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"border: none;\n"
"border-radius: 2px;\n"
"font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 14px;\n"
"background-color: #0e88eb;\n"
"color: #ffffff;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"border: none;\n"
"border-radius: 2px;\n"
"font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 14px;\n"
"background-color: #0f8ff7;\n"
"color: #ffffff;\n"
"}\n"
"\n"
"QPushButton:hover:pressed{\n"
"border: none;\n"
"border-radius: 2px;\n"
"font-family: \345\276\256\350\275\257\351\233\205\351\273\221;\n"
"font-size: 14px;\n"
"background-color: #0d80de;\n"
"color: #ffffff;\n"
"}"));

        horizontalLayout_8->addWidget(m_bSendMessage);

        horizontalSpacer_10 = new QSpacerItem(14, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_10);


        verticalLayout_8->addLayout(horizontalLayout_8);

        verticalSpacer_9 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_9);


        verticalLayout_9->addLayout(verticalLayout_8);


        horizontalLayout2->addWidget(m_zoneInput);

        horizontalLayout2->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout2);

        verticalLayout->setStretch(1, 4);
        verticalLayout->setStretch(3, 1);

        verticalLayout_11->addWidget(m_zoneBaseDialog);


        retranslateUi(ZegoLiveRoomDialog);

        m_tabCommonAndUserList->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ZegoLiveRoomDialog);
    } // setupUi

    void retranslateUi(QDialog *ZegoLiveRoomDialog)
    {
        ZegoLiveRoomDialog->setWindowTitle(QApplication::translate("ZegoLiveRoomDialog", "Dialog", Q_NULLPTR));
        m_lbRoomName->setText(QApplication::translate("ZegoLiveRoomDialog", "Mode", Q_NULLPTR));
        m_bMin->setText(QString());
        m_bMax->setText(QString());
        m_bClose->setText(QString());
        m_tabCommonAndUserList->setTabText(m_tabCommonAndUserList->indexOf(m_tabContact), QApplication::translate("ZegoLiveRoomDialog", "\350\256\250\350\256\272", Q_NULLPTR));
        m_tabCommonAndUserList->setTabText(m_tabCommonAndUserList->indexOf(m_tabMember), QApplication::translate("ZegoLiveRoomDialog", "\346\210\220\345\221\230(0)", Q_NULLPTR));
        m_lbEquipment->setText(QApplication::translate("ZegoLiveRoomDialog", "Equipment", Q_NULLPTR));
        m_lbMircoPhone->setText(QApplication::translate("ZegoLiveRoomDialog", "\351\272\246\345\205\213\351\243\216", Q_NULLPTR));
        m_lbCamera->setText(QApplication::translate("ZegoLiveRoomDialog", "\346\221\204\345\203\217\345\244\264", Q_NULLPTR));
        m_lbCamera2->setText(QApplication::translate("ZegoLiveRoomDialog", "\346\221\204\345\203\217\345\244\2642", Q_NULLPTR));
        m_lbOperation->setText(QApplication::translate("ZegoLiveRoomDialog", "Operation", Q_NULLPTR));
        m_bProgMircoPhone->setText(QString());
        m_bSound->setText(QString());
        m_bCamera->setText(QString());
        m_bAux->setText(QApplication::translate("ZegoLiveRoomDialog", "\345\274\200\345\220\257\346\267\267\351\237\263", Q_NULLPTR));
        m_bCapture->setText(QApplication::translate("ZegoLiveRoomDialog", "\345\243\260\345\215\241\351\207\207\351\233\206", Q_NULLPTR));
        m_lbFullScreen->setText(QApplication::translate("ZegoLiveRoomDialog", "Screen", Q_NULLPTR));
        m_bFullScreen->setText(QApplication::translate("ZegoLiveRoomDialog", "\345\205\250\345\261\217", Q_NULLPTR));
        m_lbShare->setText(QApplication::translate("ZegoLiveRoomDialog", "Share", Q_NULLPTR));
        m_bShare->setText(QApplication::translate("ZegoLiveRoomDialog", "\345\210\206\344\272\253", Q_NULLPTR));
        m_edInput->setPlaceholderText(QApplication::translate("ZegoLiveRoomDialog", "\350\277\207\346\235\245\350\201\212\344\274\232\345\244\251\345\221\200~", Q_NULLPTR));
        m_bRequestJoinLive->setText(QApplication::translate("ZegoLiveRoomDialog", "\350\257\267\346\261\202\350\277\236\351\272\246", Q_NULLPTR));
        m_bSendMessage->setText(QApplication::translate("ZegoLiveRoomDialog", "\345\217\221\351\200\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ZegoLiveRoomDialog: public Ui_ZegoLiveRoomDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZEGOLIVEROOMDIALOG_H
