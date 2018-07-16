#include "ZegoShareDialog.h"
#include <QDebug>

ZegoShareDialog::ZegoShareDialog(const QString& link, QWidget *parent)
	: m_link(link), QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.m_copy, &QPushButton::clicked, this, &ZegoShareDialog::OnButtonCopy);
	connect(ui.m_quit, &QPushButton::clicked, this, &ZegoShareDialog::OnButtonQuit);
	ui.m_link->adjustSize();
	ui.m_link->setGeometry(QRect(1, 50, 672, 40 * 4));
	ui.m_link->setWordWrap(true);
	ui.m_link->setAlignment(Qt::AlignTop);
	ui.m_link->setText(m_link);
	qDebug() << m_link;
}

ZegoShareDialog::~ZegoShareDialog()
{

}

void ZegoShareDialog::OnButtonCopy()
{
	QClipboard *board = QApplication::clipboard();
	board->setText(m_link);

	QMessageBox::information(NULL, tr("提示"), tr("链接已成功复制到粘贴板"));
	this->close();
}

void ZegoShareDialog::OnButtonQuit()
{
	this->close();
}