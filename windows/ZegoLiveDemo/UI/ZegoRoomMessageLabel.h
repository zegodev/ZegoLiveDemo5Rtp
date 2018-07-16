#pragma once
#include <QLabel>

class ZegoRoomMessageLabel : public QLabel
{
	Q_OBJECT
public:
	ZegoRoomMessageLabel();
	~ZegoRoomMessageLabel();

	void setTextContent(QString user, QString content);
	QString handleChatStringContent(QString content, int userSize, int &userStringIncrease);
	int getHeightNum();

private:
	int heightNum;
};