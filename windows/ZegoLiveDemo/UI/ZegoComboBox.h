#pragma execution_character_set("utf-8")
#pragma once

#include <QComboBox>
#include <QStringListModel>

class ZegoComboBox : public QComboBox
{
public:
	ZegoComboBox(QWidget * parent);
	~ZegoComboBox();

	void setCurrentIndexWithoutSignal(int index);
	void setNewModelWithoutSignal();

};