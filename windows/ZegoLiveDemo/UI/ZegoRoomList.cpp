#include "ZegoRoomList.h"

ZegoRoomList::ZegoRoomList(QWidget *parent) : QTableView(parent)
{
	
}

ZegoRoomList::~ZegoRoomList()
{

}

void ZegoRoomList::initRoomList()
{
	//设置列宽不可变
	this->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
	this->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
	this->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
	this->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
	//设置每列的宽度
	this->setColumnWidth(0, 310);
	this->setColumnWidth(1, 100);
	this->setColumnWidth(2, 110);
	this->setColumnWidth(3, 120);
	//隐藏列头
	this->verticalHeader()->setVisible(false);
	//表头内容靠左
	this->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	//表头不可点击
	this->horizontalHeader()->setSectionsClickable(false);
	//设置无边框
	this->setFrameShape(QFrame::NoFrame);
	//列表内容不可编辑
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//设置选中时为整行选中        
	this->setSelectionBehavior(QAbstractItemView::SelectRows);
	//点击item时去除虚线框
	this->setItemDelegate(new NoFocusFrameDelegate(this));
	//默认最后一列占满余下的位置
	this->horizontalHeader()->setStretchLastSection(true);
	//隐藏水平滚动条
	this->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal{height: 0px;}");
	this->horizontalScrollBar()->setVisible(false);
	//StyleSheet
	this->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{"
		"background: transparent;"
		"width: 9px;"
		"margin: 0px 0px 2px 0px;}"
		"QScrollBar::handle:vertical{"
		"background: rgb(195, 195, 195);"
		"min-height: 20px;"
		"border-radius: 3px;}"
		"QScrollBar::handle:vertical:hover{"
		"background:rgba(0, 0, 0, 30%);}"
		"QScrollBar::add-line:vertical{"
		"height: 0px;"
		"subcontrol-position: bottom;"
		"subcontrol-origin: margin; }"
		"QScrollBar::sub-line:vertical{"
		"height: 0px;"
		"subcontrol-position: top;"
		"subcontrol-origin: margin; }");

}