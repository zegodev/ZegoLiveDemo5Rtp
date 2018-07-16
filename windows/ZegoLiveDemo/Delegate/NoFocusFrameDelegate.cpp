#include "Delegate/Nofocusframedelegate.h"
#include <QPainter>
#include <QDebug>

NoFocusFrameDelegate::NoFocusFrameDelegate(QWidget *parent) :
QStyledItemDelegate(parent)
{
}

void NoFocusFrameDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QStyleOptionViewItem itemOption(option);
	if (itemOption.state & QStyle::State_HasFocus)
	{
		itemOption.state ^= QStyle::State_HasFocus;
	}
	
	QStyledItemDelegate::paint(painter, itemOption, index);
}
