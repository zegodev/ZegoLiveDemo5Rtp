#include "ZegoMicrophoneButton.h"

ZegoMicrophoneButton::ZegoMicrophoneButton(QWidget  * parent) : QPushButton(parent)
{
	m_progValue = 0;
	isEabled = true;

	QIcon icon;
	QString iconDisabled, iconOff, iconOn;

	if (this->devicePixelRatio() < 2.0)
	{
		iconDisabled = QStringLiteral(":/microphone_disabled");
		iconOff = QStringLiteral(":/microphone_off");
		iconOn = QStringLiteral(":/microphone_on");
	}
	else
	{
		iconDisabled = QStringLiteral(":/microphone_disabled_2x");
		iconOff = QStringLiteral(":/microphone_off_2x");
		iconOn = QStringLiteral(":/microphone_on_2x");
	}

	this->setStyleSheet(QString("QPushButton:!enabled{"
		"border-image: url(%1);}"
		"QPushButton:enabled:!checked{"
		"border-image: url(%2);}"
		"QPushButton:enabled:checked{"
		"border-image: url(%3);}").arg(iconDisabled).arg(iconOff).arg(iconOn));
}

ZegoMicrophoneButton::~ZegoMicrophoneButton()
{
 
}

void ZegoMicrophoneButton::paintEvent(QPaintEvent *event)
{
	//先绘制父控件图
	QPushButton::paintEvent(event);

	if (m_progValue > 15 && isEabled)
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;

		QColor color(14, 136, 235);
		painter.setPen(QPen(color, 0, Qt::SolidLine));
		painter.setBrush(QBrush(color, Qt::SolidPattern));

		int height = 19 * m_progValue / 100.0;
		int y = 3 + (18 - height);

		if (m_progValue > 80)
			painter.drawRoundedRect(12, y, 9, height, 8, 3);
		else if (m_progValue <= 80 && m_progValue > 15)
			painter.drawRoundedRect(12, y - 3, 9, height + 3, 8, 3);
		else if (m_progValue <= 15 && m_progValue > 5)
			painter.drawRoundedRect(12, y - 3, 9, height + 3, 15, 3);
		else
			painter.drawRoundedRect(13, y - 3, 7, height + 3, 15, 3);
	}
}

void ZegoMicrophoneButton::setProgValue(int value)
{
	m_progValue = value;
}

void ZegoMicrophoneButton::setMyEnabled(bool state)
{
	isEabled = state;
}