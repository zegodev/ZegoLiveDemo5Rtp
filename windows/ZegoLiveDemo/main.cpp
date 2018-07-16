#pragma execution_character_set("utf-8")

#include "Dialog/ZegoMainDialog.h"
#include "ZegoLiveDemo.h"
#include <QtWidgets/QApplication>
#include <QLocale>
#include <QTranslator>

QString LoadTranslateFile()
{
	//增加多语言支持  
	QLocale locale;
	QString languagePath;

	if (locale.language() == QLocale::Chinese)
	{
		languagePath = ":/locale/zh_lang";
	}
	else
	{
		languagePath = ":/locale/en_lang";
	}

	return languagePath;
}

int main(int argc, char *argv[])
{
	//禁止本进程QT网络模块轮询网卡
	_putenv("QT_BEARER_POLL_TIMEOUT=-1");

	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

	QApplication app(argc, argv);
	//qreal dpi = app.devicePixelRatio();
	QTranslator *trans = new QTranslator;
	trans->load(LoadTranslateFile());
	app.installTranslator(trans);

	ZegoMainDialog w;
	w.setFixedSize(940, 670);
	w.initDialog();
	w.show();

	return app.exec();
}
