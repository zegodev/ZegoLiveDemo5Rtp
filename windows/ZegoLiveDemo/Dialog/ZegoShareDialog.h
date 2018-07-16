#pragma execution_character_set("utf-8")

#ifndef ZEGOSHAREDIALOG_H
#define ZEGOSHAREDIALOG_H

#include <QtWidgets/QDialog>
#include "ui_ZegoShareDialog.h"
#include <QClipboard>
#include <QMessageBox>

class ZegoShareDialog : public QDialog
{
	Q_OBJECT

public:
	ZegoShareDialog(const QString& link, QWidget *parent = 0);
	~ZegoShareDialog();

private slots:
    void OnButtonCopy();
    void OnButtonQuit();

private:
	Ui::ZegoShareDialog ui;

	QString m_link;
};

#endif // ZEGOSHAREDIALOG_H
