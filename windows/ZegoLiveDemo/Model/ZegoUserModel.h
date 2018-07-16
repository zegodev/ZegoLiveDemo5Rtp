#pragma once

#include <QObject>
#include <QVariant>
#include <QSharedPointer>
#include <QtGui/qwindowdefs.h>

class QZegoUserModel
{
public :
	QZegoUserModel(const QString &userId, const QString &userName, bool isCurUser = false);
	~QZegoUserModel();

public :
	bool isCurrnetUser(void);
	QString getUserId(void);
	QString getUserName(void);

	bool isPrimary(void);

private :
	bool m_bCurrentUser;
	QString m_strUserId;
	QString m_strUserName;

	bool m_bPrimary;
};

//设置userModel的智能指针，方便管理内存。(QSharedPointer带引用计数)
using UserPtr = QSharedPointer < QZegoUserModel > ;
//Q_DECLARE_METATYPE(QZegoUserModel);