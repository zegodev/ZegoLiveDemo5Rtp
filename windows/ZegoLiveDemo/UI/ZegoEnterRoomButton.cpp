#include "ZegoEnterRoomButton.h"

ZegoEnterRoomButton::ZegoEnterRoomButton(QWidget  * parent) : QPushButton(parent)
{

}

ZegoEnterRoomButton::~ZegoEnterRoomButton()
{

}

void ZegoEnterRoomButton::initButton()
{
	this->setText(tr("进入"));
	this->setStyleSheet("QPushButton:!hover{"
		                "font-family: 微软雅黑;"
		                "font-size: 14px;"
		                "border: 1px solid #0e88eb;"
		                "border-radius: 2px;"
		                "background-color: #ffffff;"
		                "color: #0e88eb;"
		                "margin: 12px 20px 12px 0;}"
		                "QPushButton:hover{"
		                "font-family: 微软雅黑;"
		                "font-size: 14px;"
		                "border: 1px solid #0d80de;"
		                "border-radius: 2px;"
		                "background-color: #0d80de;"
		                "color: #ffffff;"
		                "margin: 12px 20px 12px 0;}");
	
}
