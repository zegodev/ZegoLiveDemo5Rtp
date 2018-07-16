#include "ZegoImageShowDialog.h"

ZegoImageShowDialog::ZegoImageShowDialog(QImage *image, int width, int height, SettingsPtr settings, QWidget *parent) 
	: m_image(image), m_width(width), m_height(height), m_settings(settings), QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.m_bSave, &QPushButton::clicked, this, &ZegoImageShowDialog::OnButtonSaveImage);
	connect(ui.m_bQuit, &QPushButton::clicked, this, &ZegoImageShowDialog::OnButtonClose);
	connect(ui.m_bClose, &QPushButton::clicked, this, &ZegoImageShowDialog::OnButtonClose);
	connect(ui.m_bMin, &QPushButton::clicked, this, &ZegoImageShowDialog::OnButtonMinimum);

	m_pixmap = new QPixmap;
	//无边框
	this->setWindowFlags(Qt::FramelessWindowHint);
}

ZegoImageShowDialog::~ZegoImageShowDialog()
{
	if (m_image)
	{
		delete m_image;
		m_image = nullptr;
	}
	if (m_pixmap)
	{
		delete m_pixmap;
		m_pixmap = nullptr;
	}
	
}

void ZegoImageShowDialog::initButtonIcon()
{
	ui.m_bClose->setButtonIcon("close");
	ui.m_bMin->setButtonIcon("min");
}

void ZegoImageShowDialog::initDialog()
{
	initButtonIcon();

	m_pixmap->convertFromImage(*m_image);
	//根据图片进行适应label的缩放
	if (m_width > ui.m_ImageShowLabel->maximumWidth() || m_height > ui.m_ImageShowLabel->maximumHeight())
		*m_pixmap = m_pixmap->scaled(ui.m_ImageShowLabel->maximumWidth(), ui.m_ImageShowLabel->maximumHeight(), Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 比例填充
	else
		*m_pixmap = m_pixmap->scaled(m_width, m_height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 比例填充
		
	ui.m_ImageShowLabel->setPixmap(*m_pixmap);
	ui.m_ImageShowLabel->adjustSize();
	this->adjustSize();
}

void ZegoImageShowDialog::OnButtonSaveImage()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("保存文件"), tr("./未命名"), tr("Images (*.png *.jpg *.bmp)") );
	QFileDialog fileDialog;
	
	if (fileName.isEmpty())
		return;

	if (m_image->save(fileName))
	{
		QMessageBox::information(NULL, tr("提示"), tr("文件保存成功"));
	}
	else
	{
		QMessageBox::warning(NULL, tr("提示"), tr("文件保存失败"));
	}

	this->close();
}

void ZegoImageShowDialog::OnButtonMinimum()
{
	this->showMinimized();
}

void ZegoImageShowDialog::OnButtonClose()
{
	this->close();
}

void ZegoImageShowDialog::mousePressEvent(QMouseEvent *event)
{
	mousePosition = event->pos();
	//只对标题栏范围内的鼠标事件进行处理
	if (mousePosition.x() <= pos_min_x)
		return;
	if (mousePosition.x() >= pos_max_x)
		return;
	if (mousePosition.y() <= pos_min_y)
		return;
	if (mousePosition.y() >= pos_max_y)
		return;
	isMousePressed = true;
}

void ZegoImageShowDialog::mouseMoveEvent(QMouseEvent *event)
{
	if (isMousePressed == true)
	{
		QPoint movePot = event->globalPos() - mousePosition;
		move(movePot);
	}
}

void ZegoImageShowDialog::mouseReleaseEvent(QMouseEvent *event)
{
	isMousePressed = false;
}