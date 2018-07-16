#include "ZegoSoftWareInfo.h"

#ifdef Q_OS_WIN32
#ifdef Q_PROCESSOR_X86_32
CSoftInfo::CSoftInfo()
{
    struct SoftInfo softinfo;
    HKEY RootKey;            // 主键
    LPCTSTR lpSubKey;        // 子键名称
    HKEY hkResult;            // 将要打开键的句柄 
    HKEY hkRKey;
    LONG lReturn;            // 记录读取注册表是否成功
    QString strBuffer;
    QString strMidReg;

    DWORD index = 0;
    TCHAR szKeyName[255] = {0};        // 注册表项名称
    TCHAR szBuffer[255] = {0};
    DWORD dwKeyLen = 255;
    DWORD dwNameLen = 255;
    DWORD dwType = REG_BINARY|REG_DWORD|REG_EXPAND_SZ|REG_MULTI_SZ|REG_NONE|REG_SZ;
    RootKey = HKEY_LOCAL_MACHINE;
    lpSubKey = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall");

	lReturn = RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_READ, &hkResult);

    if (lReturn == ERROR_SUCCESS)
    {

        while (ERROR_NO_MORE_ITEMS !=RegEnumKeyEx(hkResult, index, szKeyName, &dwKeyLen, 0, NULL, NULL, NULL))
        {
            index++;
            //strBuffer.Format(_T("%s"), szKeyName);
			strBuffer = QString("%1").arg(QString::fromWCharArray(szKeyName)); 
            if (!strBuffer.isEmpty())
            {
				softinfo.m_strKeyName = QString::fromWCharArray(szKeyName);
				strMidReg = QString::fromWCharArray(lpSubKey) + ("\\") + strBuffer;

				if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, (LPCWSTR)strMidReg.utf16(), 0, KEY_READ, &hkRKey) == ERROR_SUCCESS)
                { 
                    RegQueryValueEx(hkRKey, _T("DisplayName"), 0, &dwType, (LPBYTE)szBuffer,&dwNameLen); 
					softinfo.m_strSoftName = QString::fromWCharArray(szBuffer);
                    dwNameLen = 255;
                    memset(szBuffer, 0, 255);

                    RegQueryValueEx(hkRKey, _T("DisplayVersion"), 0, &dwType, (LPBYTE)szBuffer,&dwNameLen); 
					softinfo.m_strSoftVersion = QString::fromWCharArray(szBuffer);
                    dwNameLen = 255;
                    memset(szBuffer, 0, 255);

                    RegQueryValueEx(hkRKey, _T("InstallLocation"), 0, &dwType, (LPBYTE)szBuffer,&dwNameLen); 
					softinfo.m_strInstallLocation = QString::fromWCharArray(szBuffer);
					if (softinfo.m_strInstallLocation.size() == 0)
					{
						RegQueryValueEx(hkRKey, _T("InstallSource"), 0, &dwType, (LPBYTE)szBuffer, &dwNameLen);
						softinfo.m_strInstallLocation = QString::fromWCharArray(szBuffer);
					}
                    dwNameLen = 255;
                    memset(szBuffer, 0, 255);

                    RegQueryValueEx(hkRKey, _T("Publisher"), 0, &dwType, (LPBYTE)szBuffer,&dwNameLen); 
					softinfo.m_strPublisher = QString::fromWCharArray(szBuffer);
                    dwNameLen = 255;

                    RegQueryValueEx(hkRKey, _T("InstallLocation"), 0, &dwType, (LPBYTE)szBuffer,&dwNameLen); 
					softinfo.m_strMainProPath = QString::fromWCharArray(szBuffer);
                    dwNameLen = 255;
                    memset(szBuffer, 0, 255);

                    RegQueryValueEx(hkRKey, _T("UninstallString"), 0, &dwType, (LPBYTE)szBuffer,&dwNameLen); 
					softinfo.m_strUninstallPth = QString::fromWCharArray(szBuffer);
                    dwNameLen = 255;
                    memset(szBuffer, 0, 255);

                    if(!softinfo.m_strSoftName.isEmpty())
                    {
                        if(strBuffer.at(0) == 'K' && strBuffer.at(1) == 'B')
                        {
                            m_SystemPatchesArr.push_back(softinfo);
                        }
                        else
                        {
                            m_SoftInfoArr.push_back(softinfo);
                        }
                    }
                }

                dwKeyLen = 255;
                memset(szKeyName,0, 255);
            }
        }
        RegCloseKey(hkResult);
    }
    else
    {
        ::MessageBox(NULL, _T("打开注册表失败!"), NULL, MB_ICONWARNING);
    }
}

QVector<SoftInfo> CSoftInfo::GetSoftInfo (void) const
{
    return m_SoftInfoArr;
}

void CSoftInfo::GetSoftName (QVector<LPCTSTR>& lpszSoftName)
{
    QVector<SoftInfo>::iterator iter;
    for (iter = m_SoftInfoArr.begin(); iter != m_SoftInfoArr.end(); iter++)
    {
		lpszSoftName.push_back((LPCWSTR)iter->m_strSoftName.utf16());
    }
}

void CSoftInfo::GetSoftVersion (QVector<LPCTSTR>& lpszSoftVersion)
{
    QVector<SoftInfo>::iterator iter;
    for (iter = m_SoftInfoArr.begin(); iter != m_SoftInfoArr.end(); iter++)
    {
        if (!(iter->m_strSoftVersion).isEmpty())
        {
			lpszSoftVersion.push_back((LPCWSTR)iter->m_strSoftVersion.utf16());
        }
    }
}

void CSoftInfo::GetInstallLocation (QVector<LPCTSTR>& lpszInstallLocation)
{
    QVector<SoftInfo>::iterator iter;
    for (iter = m_SoftInfoArr.begin(); iter != m_SoftInfoArr.end(); iter++)
    {
        if (!(iter->m_strInstallLocation).isEmpty())
        {
			lpszInstallLocation.push_back((LPCWSTR)iter->m_strInstallLocation.utf16());
        }
    }
}

void CSoftInfo::GetPublisher (QVector<LPCTSTR>& lpszPublisher)
{
    QVector<SoftInfo>::iterator iter;

    bool bSign;
    for (iter = m_SoftInfoArr.begin(); iter != m_SoftInfoArr.end(); iter++)
    {
        bSign = true;

        // 初步去重复厂商
        QVector<LPCTSTR>::iterator itr;
        for (itr = lpszPublisher.begin(); itr != lpszPublisher.end(); itr++)
        {
			if (iter->m_strPublisher == QString::fromWCharArray(*itr))
            {
                bSign = false;
            }
        }

        if (bSign)
        {
			lpszPublisher.push_back((LPCWSTR)iter->m_strPublisher.utf16());
        }
    }
}

void CSoftInfo::GetMainProPath (QVector<LPCTSTR>& lpszMainProPath)
{
    QVector<SoftInfo>::iterator iter;
    for (iter = m_SoftInfoArr.begin(); iter != m_SoftInfoArr.end(); iter++)
    {
        if (!(iter->m_strMainProPath).isEmpty())
        {
			lpszMainProPath.push_back((LPCWSTR)iter->m_strMainProPath.utf16());
        }
    }
}

void CSoftInfo::GetUninstallPth (QVector<LPCTSTR>& lpszSoftName)
{
    QVector<SoftInfo>::iterator iter;
    for (iter = m_SoftInfoArr.begin(); iter != m_SoftInfoArr.end(); iter++)
    {
        if (!(iter->m_strUninstallPth).isEmpty())
        {
			lpszSoftName.push_back((LPCWSTR)iter->m_strUninstallPth.utf16());
        }
    }
}

QVector<SoftInfo> CSoftInfo::GetSystemPatchesInfo (void) const
{
    return m_SystemPatchesArr;
}

void CSoftInfo::GetSystemPatchesName (QVector<LPCTSTR>& lpszSoftName)
{
    QVector<SoftInfo>::iterator iter;
    for (iter = m_SystemPatchesArr.begin(); iter != m_SystemPatchesArr.end(); iter++)
    {
		lpszSoftName.push_back((LPCWSTR)iter->m_strSoftName.utf16());
    }
}

#endif
#endif