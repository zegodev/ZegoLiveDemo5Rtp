#include "ZegoImageButton.h"
#include <QDebug>

ZegoImageButton::ZegoImageButton(QWidget *parent) : QPushButton(parent)
{
	
}

ZegoImageButton::~ZegoImageButton()
{

}

void ZegoImageButton::setButtonIcon(const QString& iconFileName, QIcon::Mode mode, QIcon::State state)
{
	QIcon icon;
	if (this->devicePixelRatio() < 2.0)
	    iconFilePath = QStringLiteral(":/%1").arg(iconFileName);
	else
		iconFilePath = QStringLiteral(":/%1_2x").arg(iconFileName);

	icon.addFile(iconFilePath, QSize(), mode, state);

	//QPixmap pixmap;
	//pixmap.setDevicePixelRatio(m_dpi);
	//icon.addPixmap(pixmap);

	this->setIcon(icon);
}
