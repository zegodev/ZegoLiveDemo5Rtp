#pragma once
#include <QVector>
#include <QString>
#ifdef Q_OS_WIN32
#ifdef Q_PROCESSOR_X86_32
#include <windows.h>
#include <tchar.h>

struct SoftInfo
{
	//软件在注册表中的key值
	QString m_strKeyName;
    // 软件名
    QString m_strSoftName;
    // 软件版本号
    QString m_strSoftVersion;
    // 软件安装目录
    QString m_strInstallLocation;
    // 软件发布厂商
    QString m_strPublisher;
    // 主程序所在完整路径
    QString m_strMainProPath;
    // 卸载exe所在完整路径
    QString m_strUninstallPth;

	SoftInfo& operator=(const SoftInfo& s)//重载运算符  
	{
		this->m_strInstallLocation = s.m_strInstallLocation;
		this->m_strKeyName = s.m_strKeyName;
		this->m_strMainProPath = s.m_strMainProPath;
		this->m_strPublisher = s.m_strPublisher;
		this->m_strSoftName = s.m_strSoftName;
		this->m_strSoftVersion = s.m_strSoftVersion;
		this->m_strUninstallPth = s.m_strUninstallPth;

		return *this;
	}

};

class CSoftInfo
{
private:
    // 保存已安装常用软件安装信息
    QVector<SoftInfo> m_SoftInfoArr;
    // 保存系统补丁信息
	QVector<SoftInfo> m_SystemPatchesArr;

public:
    CSoftInfo();
    ~CSoftInfo(){}

    // 获取一个包含常用软件安装信息的Vector
    QVector<SoftInfo> GetSoftInfo (void) const;
    // 获取所有已安装常用软件名
    void GetSoftName (QVector<LPCTSTR>& lpszSoftName);
    // 获取所有已安装常用软件版本号
    void GetSoftVersion (QVector<LPCTSTR>& lpszSoftVersion);
    // 获取所有已安装常用软件安装目录
    void GetInstallLocation (QVector<LPCTSTR>& lpszInstallLocation);
    // 获取所有已安装常用软件发布厂商
    void GetPublisher (QVector<LPCTSTR>& lpszPublisher);
    // 获取所有已安装常用软件主程序所在路径
    void GetMainProPath (QVector<LPCTSTR>& lpszMainProPath);
    // 获取所有已安装常用软件卸载程序所在路径
    void GetUninstallPth (QVector<LPCTSTR>& lpszSoftName);

    // 获取一个包含系统补丁信息的Vector
    QVector<SoftInfo> GetSystemPatchesInfo (void) const;
    // 获取所有已安装系统补丁名
    void GetSystemPatchesName (QVector<LPCTSTR>& lpszSoftName);
};
#endif
#endif