#pragma once

#include <QPushButton>
#include <QIcon>
#include <QPixmap>

class ZegoStateButton : public QPushButton
{
public:
	ZegoStateButton(QWidget * parent);
	~ZegoStateButton();

	//void setButtonIcon(const QString& iconFileName, QIcon::Mode mode = QIcon::Mode::Normal, QIcon::State state = QIcon::State::Off);
	void setButtonIcon(const QString& iconFileName);

private:
	QString iconFilePath;
};

