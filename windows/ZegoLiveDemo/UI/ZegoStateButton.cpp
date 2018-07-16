#include "ZegoStateButton.h"
#include <QDebug>

ZegoStateButton::ZegoStateButton(QWidget *parent) : QPushButton(parent)
{
	
}

ZegoStateButton::~ZegoStateButton()
{

}

void ZegoStateButton::setButtonIcon(const QString& iconFileName)
{
	QIcon icon;
	QString iconNormal, iconHover, iconSelected;

	if (this->devicePixelRatio() < 2.0)
	{
		iconNormal = QStringLiteral(":/%1_default").arg(iconFileName);
		iconHover = QStringLiteral(":/%1_hover").arg(iconFileName);
		iconSelected = QStringLiteral(":/%1_pressed").arg(iconFileName);
	}
	else
	{
		iconNormal = QStringLiteral(":/%1_default_2x").arg(iconFileName);
		iconHover = QStringLiteral(":/%1_hover_2x").arg(iconFileName);
		iconSelected = QStringLiteral(":/%1_pressed_2x").arg(iconFileName);
	}

	this->setStyleSheet(QString("QPushButton:!hover{"
		                        "border-image: url(%1);}"
		                        "QPushButton:hover:!pressed{"
		                        "border-image: url(%2);}"
		                        "QPushButton:hover:pressed{"
								"border-image: url(%3);}").arg(iconNormal).arg(iconHover).arg(iconSelected));
	qDebug() << "icon file path = " << iconFilePath;

}