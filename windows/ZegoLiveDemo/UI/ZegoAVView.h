#pragma once
#pragma execution_character_set("utf-8")

#include <QPainter>
#include <QColor>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QContextMenuEvent>
#include <QMenu>
#include <QMessageBox>
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QScrollBar>

#include "Model/ZegoVideoFrame.h"

#define USE_SURFACE_MERGE
#if (defined Q_OS_WIN32) && (defined Q_PROCESSOR_X86_32) && (defined USE_SURFACE_MERGE)
#include "ZegoSurfaceMerge.h"
#include "ZegoSurfaceMergeDefine.h"
using namespace ZEGO;
#endif

using OnGetFrameDelegate = std::function<VideoFrame()>;

enum ZegoDialogType
{
	ZEGODIALOG_SingleAnchor = 0,
	ZEGODIALOG_SingleAudience,
	ZEGODIALOG_MoreAnchor,
	ZEGODIALOG_MoreAudience,
	ZEGODIALOG_MixStreamAnchor,
	ZEGODIALOG_MixStreamAudience
};

class QZegoAVScene;
class QZegoAVView : public QGraphicsView
{
	Q_OBJECT
public:
	QZegoAVView(ZegoDialogType dialogType, QWidget * parent = 0);
	~QZegoAVView();

	void setCurrentQuality(int quality);
	int getCurrentQuality();

	void setSurfaceMergeView(bool state);
	bool getSurfaceMergeView();

#if (defined Q_OS_WIN32) && (defined Q_PROCESSOR_X86_32) && (defined USE_SURFACE_MERGE)
	void setSurfaceMergeItemRect(SurfaceMerge::ZegoCaptureItem _screen,
	                         SurfaceMerge::ZegoCaptureItem _camera);
#endif

	void setViewIndex(int index);
	int getViewIndex();

	void setViewStreamID(QString streamID);
	void setCurUser();
	bool IsCurUser();

	void SetUseExternalRender(bool bIsUse);
	void SetOnGetFrameDelegate(OnGetFrameDelegate func);
	//WId getLiveViewWinID();
	//void addActionForKickOut();
signals:
	void sigSnapShotPreviewOnSingleAnchor();
	void sigSnapShotOnSingleAudienceWithStreamID(const QString& streamID);
	void sigSnapShotPreviewOnMoreAnchor();
	void sigSnapShotOnMoreAnchorWithStreamID(const QString& streamID);
	void sigSnapShotPreviewOnMoreAudience();
	void sigSnapShotOnMoreAudienceWithStreamID(const QString& streamID);
	void sigSnapShotPreviewOnMixStreamAnchor();
	void sigSnapShotOnMixStreamAnchorWithStreamID(const QString& streamID);
	void sigSnapShotPreviewOnMixStreamAudience();
	void sigSnapShotOnMixStreamAudienceWithStreamID(const QString& streamID);

private slots:
    void OnMenuSnapShotTriggered();
	void OnMenukickForceTriggered();

protected:
	//virtual void paintEvent(QPaintEvent *event);
	virtual void resizeEvent(QResizeEvent *event);
	virtual void contextMenuEvent(QContextMenuEvent *event);
	void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
	QZegoAVScene *scene;
	int m_nAVQuality;
	bool isSurfaceMergeView = false;
	int viewIndex;
	QString m_pCurStreamID;
	bool m_isCurUser = false;
	ZegoDialogType m_dialogType;
	QMenu *m_menu = nullptr;

	//外部渲染
	bool m_isExternalRender = false;
	VideoFrame m_frame;
	OnGetFrameDelegate m_getFrameFunc;
};

class QZegoAVScene : public QGraphicsScene
{
	Q_OBJECT

public:
	QZegoAVScene(QWidget * parent = 0);
	~QZegoAVScene();

#if (defined Q_OS_WIN32) && (defined Q_PROCESSOR_X86_32) && (defined USE_SURFACE_MERGE)
	void setSurfaceMergeItemRect(SurfaceMerge::ZegoCaptureItem _screen,
		SurfaceMerge::ZegoCaptureItem _camera);

	//WId getLiveViewWinID_Inner();

protected:
	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
#endif

#if (defined Q_OS_WIN32) && (defined Q_PROCESSOR_X86_32) && (defined USE_SURFACE_MERGE)
private:
	bool isMousePressed = false;
	SurfaceMerge::ZegoCaptureItem screen;
	SurfaceMerge::ZegoCaptureItem camera;
	float scaleFactor_X;
	float scaleFactor_Y;
	QPointF curMousePosition;
#endif
    
private:
	QLabel *qualityLabel = nullptr;
	QWidget *liveView = nullptr;
};