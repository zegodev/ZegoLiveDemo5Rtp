#pragma once

#include <QPushButton>
#include <QPainter>
#include <QColor>
class ZegoMicrophoneButton : public QPushButton
{
	Q_OBJECT

public:
	ZegoMicrophoneButton(QWidget  * parent);
	~ZegoMicrophoneButton();

protected:
	virtual void paintEvent(QPaintEvent *event);
	
public:
	void setProgValue(int value);
	void setMyEnabled(bool state);

private:
	int m_progValue;
	bool isEabled;
};