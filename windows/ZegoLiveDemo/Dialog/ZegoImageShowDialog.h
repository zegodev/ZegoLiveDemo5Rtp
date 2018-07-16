#pragma execution_character_set("utf-8")

#ifndef ZEGOIMAGESHOWDIALOG_H
#define ZEGOIMAGESHOWDIALOG_H

#include "ui_ZegoImageShowDialog.h"
#include "Settings/ZegoSettingsModel.h"

#include <QtWidgets/QDialog>
#include <QImage>
#include <QPixmap>
#include <QMouseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>

//标题栏坐标范围
#define pos_min_x  0
#define pos_max_x  ui.m_zoneTitle->size().width()
#define pos_min_y  0
#define pos_max_y  ui.m_zoneTitle->size().height()

class ZegoImageShowDialog : public QDialog
{
	Q_OBJECT

public:
	ZegoImageShowDialog(QImage *image, int width, int height, SettingsPtr settings, QWidget *parent = 0);
	~ZegoImageShowDialog();
	void initDialog();

signals:
	

protected slots :
	void OnButtonSaveImage();
    void OnButtonClose();
	void OnButtonMinimum();

protected:
	virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseMoveEvent(QMouseEvent *e);
	virtual void mouseReleaseEvent(QMouseEvent *e);

private slots:
	

private:
	void initButtonIcon();

private:
	Ui::ZegoImageShowDialog ui;
	QImage *m_image;
	QPixmap *m_pixmap;
	int m_width;
	int m_height;

	//实现自定义标题栏的拖动
	bool isMousePressed;
	QPoint mousePosition;

	SettingsPtr m_settings;
};

#endif
