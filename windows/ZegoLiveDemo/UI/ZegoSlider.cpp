#include "ZegoSlider.h"
#include <QDebug>

ZegoSlider::ZegoSlider(QWidget *parent) : QSlider(parent)
{
	QIcon icon;
	QString iconNormal, iconHover, iconSelected;

	if (this->devicePixelRatio() < 2.0)
	{
		iconNormal = QStringLiteral(":/handle_default");
		iconHover = QStringLiteral(":/handle_hover");
		iconSelected = QStringLiteral(":/handle_pressed");
	}
	else
	{
		iconNormal = QStringLiteral(":/handle_default_2x");
		iconHover = QStringLiteral(":/handle_hover_2x");
		iconSelected = QStringLiteral(":/handle_pressed_2x");
	}

	this->setStyleSheet(QString("QSlider::groove:horizontal{"
		"border: none;"
		"height: 1px;}"

		"QSlider::handle:horizontal:!hover{"
		"border: none;"
		"width: 11px;"
		"height: 11px;"
		"margin: -5px 0;"
		"border-image: url(%1);}"

		"QSlider::handle:horizontal:hover:!pressed{"
		"border: none;"
		"width: 11px;"
		"height: 11px;"
		"margin: -5px 0;"
		"border-image: url(%2);}"

		"QSlider::handle:horizontal:hover:pressed{"
		"border: none;"
		"width: 11px;"
		"height: 11px;"
		"margin: -5px 0;"
		"border-image: url(%3);}"

		"QSlider::add-page:horizontal{"
		"background-color: #e6e6e6;}"

		"QSlider::sub-page:horizontal{"
		"background-color: #0e88eb;}").arg(iconNormal).arg(iconHover).arg(iconSelected));
}

ZegoSlider::~ZegoSlider()
{

}
