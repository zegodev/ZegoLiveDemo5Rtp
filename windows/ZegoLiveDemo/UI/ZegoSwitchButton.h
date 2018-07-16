#pragma once

#include <QPushButton>
#include <QIcon>
#include <QPixmap>

class ZegoSwitchButton : public QPushButton
{
public:
	ZegoSwitchButton(QWidget * parent);
	~ZegoSwitchButton();

	void setButtonIcon(const QString& iconFileName);

private:
	QString iconFilePath;
};

