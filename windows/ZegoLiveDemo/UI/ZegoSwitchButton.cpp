#include "ZegoSwitchButton.h"
#include <QDebug>

ZegoSwitchButton::ZegoSwitchButton(QWidget *parent) : QPushButton(parent)
{
	
}

ZegoSwitchButton::~ZegoSwitchButton()
{

}

void ZegoSwitchButton::setButtonIcon(const QString& iconFileName)
{
	QIcon icon;
	QString iconDisabled, iconNormal, iconChecked;

	if (this->devicePixelRatio() < 2.0)
	{
		iconDisabled = QStringLiteral(":/%1_disabled").arg(iconFileName);
		iconNormal = QStringLiteral(":/%1_off").arg(iconFileName);
		iconChecked = QStringLiteral(":/%1_on").arg(iconFileName);
	}
	else
	{
		iconDisabled = QStringLiteral(":/%1_disabled_2x").arg(iconFileName);
		iconNormal = QStringLiteral(":/%1_off_2x").arg(iconFileName);
		iconChecked = QStringLiteral(":/%1_on_2x").arg(iconFileName);
	}

	this->setStyleSheet(QString("QPushButton:!enabled{"
		                        "border-image: url(%1);}"
		                        "QPushButton:enabled:!checked{"
		                        "border-image: url(%2);}"
		                        "QPushButton:enabled:checked{"
								"border-image: url(%3);}").arg(iconDisabled).arg(iconNormal).arg(iconChecked));
}