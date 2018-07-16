#pragma once

#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QScrollBar>
#include "Delegate/NoFocusFrameDelegate.h"

class ZegoRoomList : public QTableView
{
public:
	ZegoRoomList(QWidget * parent);
	~ZegoRoomList();

	void initRoomList();

};
