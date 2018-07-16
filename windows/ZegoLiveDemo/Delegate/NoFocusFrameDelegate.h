#ifndef NOFOCUSFRAMEDELEGATE_H
#define NOFOCUSFRAMEDELEGATE_H

#include <QStyledItemDelegate>

/**
* È¥³ýÐéÏß¿ò
*/
class NoFocusFrameDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	explicit NoFocusFrameDelegate(QWidget *parent = 0);

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals: 

	public slots :

};

#endif // NOFOCUSFRAMEDELEGATE_H