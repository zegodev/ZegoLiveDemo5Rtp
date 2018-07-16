#include "ZegoUserModel.h"

QZegoUserModel::QZegoUserModel(const QString &userId, const QString &userName, bool isCurUser) :
m_strUserId(userId),
m_strUserName(userName),
m_bCurrentUser(isCurUser)
{
	m_bPrimary = m_strUserId.indexOf(QStringLiteral("_primary")) != std::string::npos;
}

QZegoUserModel::~QZegoUserModel(){}

bool QZegoUserModel::isCurrnetUser(void)
{
	return m_bCurrentUser;
}

QString QZegoUserModel::getUserId(void)
{
	return m_strUserId;
}

QString QZegoUserModel::getUserName(void)
{
	return m_strUserName;
}

bool QZegoUserModel::isPrimary(void)
{
	return m_bPrimary;
}

