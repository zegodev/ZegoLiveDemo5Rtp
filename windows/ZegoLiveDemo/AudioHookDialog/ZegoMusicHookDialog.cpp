#include "ZegoMusicHookDialog.h"
#include <QDebug>

#if (defined Q_OS_WIN32) && (defined Q_PROCESSOR_X86_32)
ZegoMusicHookDialog::ZegoMusicHookDialog(QWidget *parent) : QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.m_bClose, &QPushButton::clicked, this, &ZegoMusicHookDialog::OnClose);
	connect(ui.m_bReject, &QPushButton::clicked, this, &ZegoMusicHookDialog::OnClose);


	connect(ui.m_bAccept, &QPushButton::clicked, this, &ZegoMusicHookDialog::OnSendCustomAppPath);

	connect(ui.m_bOpenFile, &QPushButton::clicked, this, &ZegoMusicHookDialog::OnSelectedMusicApp);
	connect(ui.m_bCloudNet, &QPushButton::clicked, this, &ZegoMusicHookDialog::OnSelectedMusicApp);
	connect(ui.m_bKuGou, &QPushButton::clicked, this, &ZegoMusicHookDialog::OnSelectedMusicApp);
	connect(ui.m_bQQMusic, &QPushButton::clicked, this, &ZegoMusicHookDialog::OnSelectedMusicApp);
	connect(ui.m_bKuWo, &QPushButton::clicked, this, &ZegoMusicHookDialog::OnSelectedMusicApp);

    
	this->setFixedSize(QSize(700, 480));
	this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏

	initButtonIcon();
}

ZegoMusicHookDialog::~ZegoMusicHookDialog()
{

}

void ZegoMusicHookDialog::initButtonIcon()
{
	ui.m_bQQMusic->setButtonIcon("QQMusic");
	ui.m_bKuGou->setButtonIcon("KuGou");
	ui.m_bCloudNet->setButtonIcon("CloudNet");
	ui.m_bKuWo->setButtonIcon("KuWo");

	ui.m_bClose->setButtonIcon("close");
}

void ZegoMusicHookDialog::searchMusicAppFromReg()
{
	CSoftInfo allAppInfo;
	QVector<SoftInfo> m_softWareInfo;
	m_softWareInfo = allAppInfo.GetSoftInfo();

	/*for (auto it = m_softWareInfo.begin(); it != m_softWareInfo.end(); it++)
	{
		qDebug() << it->m_strSoftName << " : ";
		qDebug() << "keyName : " << it->m_strKeyName;
		qDebug() << "installLocation : "<<it->m_strInstallLocation;
		qDebug() << "appMainProPath : "<<it->m_strMainProPath;
		qDebug() << "publisher : " << it->m_strPublisher;
		qDebug() << "version : " << it->m_strSoftVersion;
		qDebug() << "uninstallPath : " << it->m_strUninstallPth;
		qDebug() << "-----------------------------------------------------";
	}*/

	for (auto it = m_softWareInfo.begin(); it != m_softWareInfo.end(); it++)
	{
		if (it->m_strKeyName == tr("QQMusic"))
			QQMusic = *it;
		else if (it->m_strKeyName == tr("酷狗音乐"))
			KuGouMusic = *it;
		else if (it->m_strKeyName == tr("网易云音乐"))
			CloudMusic = *it;
		else if (it->m_strKeyName == tr("KwMusic7"))
			KuwoMusic = *it;
	}

}

DWORD ZegoMusicHookDialog::ProcessIsExist(LPTSTR pszProcessPath)
{
	
	DWORD PID = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 procEntry = { 0 };
	procEntry.dwSize = sizeof(PROCESSENTRY32);
	Process32First(hSnap, &procEntry);
	do
	{
		HANDLE hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, procEntry.th32ProcessID);
		if (hProcess == NULL)
			continue;

		TCHAR processFileName[MAX_PATH];
		GetModuleFileNameEx(hProcess, NULL, processFileName, sizeof(processFileName));
		CloseHandle(hProcess);
		if (_tcsicmp(processFileName, pszProcessPath) == 0)
		{
			PID = procEntry.th32ProcessID;
			break;
		}
	} while (Process32Next(hSnap, &procEntry));

	return PID;
}

BOOL ZegoMusicHookDialog::StartProcess(LPTSTR pszProcessPath)
{
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	bool bRet = CreateProcess(
		NULL,
		pszProcessPath,
		NULL,
		NULL,
		FALSE,
		CREATE_DEFAULT_ERROR_MODE,
		NULL,
		NULL,
		&si,
		&pi);

	if (!bRet){
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
	}

	return bRet;

}

BOOL ZegoMusicHookDialog::KillProcess(LPTSTR pszProcessPath)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	DWORD dwExitCode = 0;
	std::vector<DWORD> terminateProcessIDs;

	PROCESSENTRY32 procEntry = { 0 };
	procEntry.dwSize = sizeof(PROCESSENTRY32);
	Process32First(hSnap, &procEntry);
	do
	{
		HANDLE hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, procEntry.th32ProcessID);
		if (hProcess == NULL)
			continue;

		TCHAR processFileName[MAX_PATH];
		GetModuleFileNameEx(hProcess, NULL, processFileName, sizeof(processFileName));
		CloseHandle(hProcess);
		if (_tcsicmp(processFileName, pszProcessPath) == 0)
			terminateProcessIDs.push_back(procEntry.th32ProcessID);

	} while (Process32Next(hSnap, &procEntry));

	for (auto it = terminateProcessIDs.begin(); it != terminateProcessIDs.end(); it++)
	{
		HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE, 0, *it);
		if (hProcess != NULL)
		{
			::GetExitCodeProcess(hProcess, &dwExitCode);
			::TerminateProcess(hProcess, dwExitCode);
			CloseHandle(hProcess);
		}
	}

	if (hSnap != INVALID_HANDLE_VALUE)
		CloseHandle(hSnap);

	return !terminateProcessIDs.empty();
}

void ZegoMusicHookDialog::OnSelectedMusicApp()
{
	QPushButton *button = qobject_cast<QPushButton *>(sender());

	if (button == ui.m_bOpenFile)
	{
		emit sigUseDefaultAux(true);
		this->accept();
	}
	else if (button == ui.m_bCloudNet)
	{
		QString exeName = "cloudmusic.exe";
		if (CloudMusic.m_strUninstallPth.size() == 0)
		{
			QMessageBox::information(NULL, tr("提示"), tr("无法找到 %1").arg(exeName));
			return;
		}

		QString exePath;
		exePath = CloudMusic.m_strUninstallPth.mid(0, CloudMusic.m_strUninstallPth.lastIndexOf('\\'));
		exePath = exePath + "\\" + exeName;
		//若进程已经存在，则kill之
		KillProcess((LPTSTR)exePath.utf16());
		
		emit sigSendMusicAppPath(exePath);
		this->accept();
	}
	else if (button == ui.m_bKuGou)
	{
		QString exeName = "KuGou.exe";
		if (KuGouMusic.m_strUninstallPth.size() == 0)
		{
			QMessageBox::information(NULL, tr("提示"), tr("无法找到 %1").arg(exeName));
			return;
		}

		QString exePath;
		exePath = KuGouMusic.m_strUninstallPth.mid(0, KuGouMusic.m_strUninstallPth.lastIndexOf('\\'));
		exePath = exePath + "\\" + exeName;
		//若进程已经存在，则kill之
		KillProcess((LPTSTR)exePath.utf16());
		
		emit sigSendMusicAppPath(exePath);
		this->accept();
	}
	else if (button == ui.m_bQQMusic)
	{
		QString exeName = "QQMusic.exe";
		if (QQMusic.m_strUninstallPth.size() == 0)
		{
			QMessageBox::information(NULL, tr("提示"), tr("无法找到 %1").arg(exeName));
			return;
		}

		QString exePath;
		exePath = QQMusic.m_strUninstallPth.mid(0, QQMusic.m_strUninstallPth.lastIndexOf('\\'));
		exePath = exePath + "\\" + exeName;
		//若进程已经存在，则kill之
		KillProcess((LPTSTR)exePath.utf16());
		
		emit sigSendMusicAppPath(exePath);
		this->accept();
	}
	else if (button == ui.m_bKuWo)
	{
		//酷我音乐特殊处理，先启动进程，再hook"KwService.exe"
		QString exeName = "KwMusic.exe";
		if (KuwoMusic.m_strUninstallPth.size() == 0)
		{
			QMessageBox::information(NULL, tr("提示"), tr("无法找到 %1").arg(exeName));
			return;
		}

		QString exePath, hookPath;
		exePath = KuwoMusic.m_strUninstallPth.mid(0, KuwoMusic.m_strUninstallPth.lastIndexOf('\\'));
		hookPath = exePath + "\\bin\\KwService.exe";
		exePath = exePath + "\\" + exeName;
		
		//若进程已经存在，则kill之
		KillProcess((LPTSTR)exePath.utf16());
		//重新启动进程
		StartProcess((LPTSTR)exePath.utf16());
		while (!ProcessIsExist((LPTSTR)hookPath.utf16()))
		{
			Sleep(10);
		}
		Sleep(500);
		emit sigSendMusicAppPath(hookPath);
		this->accept();
	}
}

void ZegoMusicHookDialog::OnSendCustomAppPath()
{
	QString exePath = ui.m_edAppPath->text();
	if (exePath.isEmpty())
	{
		QMessageBox::information(NULL, tr("提示"), tr("若需要手动添加路径，则输入框不能为空"));
		return;
	}

	//若进程已经存在，则kill之
	KillProcess((LPTSTR)exePath.utf16());
	emit sigSendMusicAppPath(exePath);
	this->accept();
}

void ZegoMusicHookDialog::OnClose()
{
	this->reject();
}

void ZegoMusicHookDialog::mousePressEvent(QMouseEvent *event)
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

void ZegoMusicHookDialog::mouseMoveEvent(QMouseEvent *event)
{
	if (isMousePressed == true)
	{
		QPoint movePot = event->globalPos() - mousePosition;
		move(movePot);
	}
}

void ZegoMusicHookDialog::mouseReleaseEvent(QMouseEvent *event)
{
	isMousePressed = false;
}

#endif


