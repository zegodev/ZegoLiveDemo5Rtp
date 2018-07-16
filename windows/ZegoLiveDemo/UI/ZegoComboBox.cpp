#include "ZegoComboBox.h"
#include <QDebug>

ZegoComboBox::ZegoComboBox(QWidget *parent) : QComboBox(parent)
{
	QString iconDownArrow;
	if (this->devicePixelRatio() < 2.0)
	{
		iconDownArrow = ":/down_arrow";
	}
	else
	{
		iconDownArrow = ":/down_arrow_2x";
	}

	this->setStyleSheet(QString("QComboBox{"
		                            "padding-left: 10px;"
		                            "border: 1px solid #e6e6e6;"
		                            "border-radius: 2px;"
		                            "font-family: Î¢ÈíÑÅºÚ;"
									"font-size: 16px;"
		                            "background-color: #fafafa;"
		                            "color: #666666;}"
		                        "QComboBox:!enabled{ color: #cccccc;}"
		                        "QComboBox:enabled:hover{border: 1px solid #0e88eb;}"
		                        "QComboBox::drop-down{"
		                            "subcontrol-origin: padding;"
		                            "subcontrol-position: top right;"
		                            "width: 20px;"
		                            "border-left-width: 1px;"
		                            "border-top-right-radius: 2px;"
		                            "border-bottom-right-radius: 2px;}"
		                        "QComboBox::down-arrow{"
		                            "border-image: url(%1);}"
		                        "QComboBox QAbstractItemView{"
		                            "font-family: Î¢ÈíÑÅºÚ;"
		                            "font-size: 14px;"
		                            "border: 1px solid #0e88eb;"
		                            "background-color: #ffffff;"
		                            "border-radius: 2px;}"
		                        "QComboBox QAbstractItemView::item{"
		                            "height: 32px;"
		                            "font-family: Î¢ÈíÑÅºÚ;"
		                            "font-size: 14px;"
		                            "color: #666666;"
		                            "background-color: #ffffff;"
		                            "padding-left: 10px;"
		                            "padding-right: 10px;}"
		                        "QComboBox QAbstractItemView::item:hover{"
		                            "height: 32px;"
		                            "font-family: Î¢ÈíÑÅºÚ;"
		                            "font-size: 14px;"
		                            "color: #ffffff;"
		                            "background-color: #0e88eb;"
		                            "padding-left: 10px;"
		                            "padding-right: 10px;}").arg(iconDownArrow));
}

ZegoComboBox::~ZegoComboBox()
{

}

void ZegoComboBox::setCurrentIndexWithoutSignal(int index)
{
	this->blockSignals(true);
	this->setCurrentIndex(index);
	this->blockSignals(false);
}

void ZegoComboBox::setNewModelWithoutSignal()
{
	this->blockSignals(true);
	this->setModel(new QStringListModel(this));
	this->blockSignals(false);
}

