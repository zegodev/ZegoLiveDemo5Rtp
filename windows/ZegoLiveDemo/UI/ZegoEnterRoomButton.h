#pragma execution_character_set("utf-8")
#pragma once

#include <QPushButton>

class ZegoEnterRoomButton : public QPushButton
{
	Q_OBJECT
public:
	ZegoEnterRoomButton(QWidget  * parent = 0);
	~ZegoEnterRoomButton();

	void initButton();
	
};