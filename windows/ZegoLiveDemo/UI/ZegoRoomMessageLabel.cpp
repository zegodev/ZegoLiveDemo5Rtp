#include "ZegoRoomMessageLabel.h"
#include <QDebug>
ZegoRoomMessageLabel::ZegoRoomMessageLabel()
{
	this->setStyleSheet("font-family: Microsoft YaHei;\ncolor: #666666;\nfont-size: 14px;\nmargin: 0 0 0 0;");
}

ZegoRoomMessageLabel::~ZegoRoomMessageLabel()
{

}

void ZegoRoomMessageLabel::setTextContent(QString user, QString content)
{
	user += QStringLiteral("：");
	
	QString handleString = user + content;
	int userStringIncrease = 0;
	QString finalStringContent = handleChatStringContent(handleString, user.size(), userStringIncrease);
	QString userNameAfterHandle = finalStringContent.mid(0, user.size() + userStringIncrease);

	finalStringContent = finalStringContent.mid(user.size() + userStringIncrease);
	
	
	finalStringContent = QString(QStringLiteral("<html> \
												<head> \
												<style> \
												font{color:#0e88eb;} #f{color: #333333;} \
												</style> \
												</head> \
												<body>\
												<font>%1</font><font id=\"f\">%2</font> \
												</body> \
												</html>")).arg(userNameAfterHandle).arg(finalStringContent);

	this->setText(finalStringContent);
	this->setFixedSize(QSize(300, 25 * this->getHeightNum()));
}

QString ZegoRoomMessageLabel::handleChatStringContent(QString content, int userSize, int &userStringIncrease)
{
	QString str, tmp;
	QLabel *label = new QLabel;
	heightNum = 0;
	label->setStyleSheet("font-family: Microsoft YaHei;\ncolor: #666666;\nfont-size: 14px;");
	for (int i = 0; i < content.size(); i++)
	{

		label->setText(tmp);
		label->adjustSize();
		if (label->width() >= 288)
		{
			str += "<br>";
			tmp.clear();
			heightNum++;
			if (i <= userSize - 1)
				userStringIncrease += 4;
			
		}
		if (content.at(i) == '\n')
		{
			str += "<br>";
			tmp.clear();
			heightNum++;
		}
		else
		{
			str.append(content.at(i));
			tmp.append(content.at(i));
		}
	}

	
	heightNum++;

	delete label;
	label = nullptr;
	return str;
}

int ZegoRoomMessageLabel::getHeightNum()
{
	return heightNum;
}