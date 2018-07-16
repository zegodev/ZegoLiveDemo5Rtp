#include "ZegoAVView.h"
#include <QDebug>

QZegoAVView::QZegoAVView(ZegoDialogType dialogType, QWidget * parent) : 
    m_dialogType(dialogType), QGraphicsView(parent)
{
	scene = new QZegoAVScene(this);
	scene->setSceneRect(0, 0, dynamic_cast<QZegoAVView *>(scene->parent())->size().width(), dynamic_cast<QZegoAVView *>(scene->parent())->size().height());
    setScene(scene);
	setStyleSheet("background-color: #383838");
	//进房间闪白边的原因
	this->horizontalScrollBar()->setVisible(false);
	this->verticalScrollBar()->setVisible(false);
	m_nAVQuality = -1;

	//设置AVView不接受焦点，可去除因鼠标点击view时闪烁问题
	this->setFocusPolicy(Qt::NoFocus);

}

QZegoAVView::~QZegoAVView()
{
	if (m_menu)
	{
		delete m_menu;
		m_menu = nullptr;
	}
	if (scene)
	{
		delete scene;
		scene = nullptr;
	}
}

void QZegoAVView::setCurrentQuality(int quality)
{
	m_nAVQuality = quality;
}

int QZegoAVView::getCurrentQuality()
{
	return m_nAVQuality;
}

void QZegoAVView::setSurfaceMergeView(bool state)
{
	isSurfaceMergeView = state;
}

bool QZegoAVView::getSurfaceMergeView()
{
	return isSurfaceMergeView;
}

#if (defined Q_OS_WIN32) && (defined Q_PROCESSOR_X86_32) && (defined USE_SURFACE_MERGE)
void QZegoAVView::setSurfaceMergeItemRect(SurfaceMerge::ZegoCaptureItem _screen,
	SurfaceMerge::ZegoCaptureItem _camera)
{
	scene->setSurfaceMergeItemRect(_screen, _camera);
}
#endif

void QZegoAVView::setViewIndex(int index)
{
	viewIndex = index;
}

int QZegoAVView::getViewIndex()
{
	return viewIndex;
}

void QZegoAVView::setViewStreamID(QString streamID)
{
	m_pCurStreamID = streamID;
}

void QZegoAVView::setCurUser()
{
	m_isCurUser = true;
}

bool QZegoAVView::IsCurUser()
{
	return m_isCurUser;
}

void QZegoAVView::SetUseExternalRender(bool bIsUse)
{
	m_isExternalRender = bIsUse;
}

void QZegoAVView::SetOnGetFrameDelegate(OnGetFrameDelegate func)
{
	m_getFrameFunc = func;
}

void QZegoAVView::resizeEvent(QResizeEvent *event)
{
	scene->setSceneRect(0 , 0 , dynamic_cast<QZegoAVView *>(scene->parent())->size().width() , dynamic_cast<QZegoAVView *>(scene->parent())->size().height());
}

void QZegoAVView::drawBackground(QPainter *painter, const QRectF &rect)
{
	if (rect.isNull())
	{
		return;
	}

	if (!m_isExternalRender)
	{
		QGraphicsView::drawBackground(painter, rect);
	}
	else
	{
		if (m_getFrameFunc) {
			VideoFrame new_frame = m_getFrameFunc();
			if (new_frame) {

				m_frame = new_frame;

			}

			if (m_frame) {
				painter->drawImage(rect, m_frame->getCurrentFrame(), QRect(0, 0, m_frame->getCurrentFormat().width, m_frame->getCurrentFormat().height), Qt::NoFormatConversion);
				//painter->drawImage(rect, m_frame->getCurrentFrame());
			}
		}
	}
}

void QZegoAVView::contextMenuEvent(QContextMenuEvent *event)
{
	
	m_menu = new QMenu(this);
	m_menu->setStyleSheet("QMenu{"
		"border: 1px solid #0e88eb;"
		"font-family: 微软雅黑;"
		"font-size: 14px;}"
		"QMenu::item{"
		"background-color: #ffffff;"
		"color: #0e88eb;}"
		"QMenu::item:selected{"
		"background-color: #0e88eb;"
		"color: #ffffff;}");

		QAction *snapShot = m_menu->addAction(tr("截取图像"));
		connect(snapShot, SIGNAL(triggered(bool)), this, SLOT(OnMenuSnapShotTriggered()));
		
		m_menu->move(cursor().pos());
		m_menu->show();
	
}

void QZegoAVView::OnMenuSnapShotTriggered()
{
	if (m_pCurStreamID.size() == 0)
	{
		QMessageBox::information(NULL, tr("提示"), tr("当前房间没有主播正在直播"));
		return;
	}

	switch (m_dialogType)
	{
	case ZEGODIALOG_SingleAnchor:
		emit sigSnapShotPreviewOnSingleAnchor();
		break;

	case ZEGODIALOG_SingleAudience:
		emit sigSnapShotOnSingleAudienceWithStreamID(m_pCurStreamID);
		break;

	case ZEGODIALOG_MoreAnchor:
		if (m_isCurUser)
		    emit sigSnapShotPreviewOnMoreAnchor();
		else
		    emit sigSnapShotOnMoreAnchorWithStreamID(m_pCurStreamID);
		break;

	case ZEGODIALOG_MoreAudience:
		if (m_isCurUser)
			emit sigSnapShotPreviewOnMoreAudience();
		else
			emit sigSnapShotOnMoreAudienceWithStreamID(m_pCurStreamID);
		break;

	case ZEGODIALOG_MixStreamAnchor:
		if (m_isCurUser)
			emit sigSnapShotPreviewOnMixStreamAnchor();
		else
			emit sigSnapShotOnMixStreamAnchorWithStreamID(m_pCurStreamID);
		break;

	case ZEGODIALOG_MixStreamAudience:
		if (m_isCurUser)
			emit sigSnapShotPreviewOnMixStreamAudience();
		else
			emit sigSnapShotOnMixStreamAudienceWithStreamID(m_pCurStreamID);
		break;

	default:
		break;
	}
	
}

/*WId QZegoAVView::getLiveViewWinID()
{
	return this->scene->getLiveViewWinID_Inner();
}*/
/*void QZegoAVView::addActionForKickOut()
{
	if (!m_isCurUser)
	{
		QAction *kickForce = m_menu->addAction(tr("踢出连麦"));
		connect(kickForce, SIGNAL(triggered(bool)), this, SLOT(OnMenukickForceTriggered()));
	}
}*/

void QZegoAVView::OnMenukickForceTriggered()
{

}

QZegoAVScene::QZegoAVScene(QWidget * parent)
	: QGraphicsScene(parent)
{
	/*liveView = new QWidget(parent);
	liveView->setStyleSheet("background-color: none;");
	
	addWidget(liveView)->setZValue(-1);
	qualityLabel = new QLabel(parent);
	qualityLabel->setText("!!!!!!!!!!!aaabbasdf!!!!!!!!");
	qualityLabel->setWindowOpacity(1);
	qualityLabel->setAttribute(Qt::WA_TranslucentBackground);
	
	addWidget(qualityLabel)->setZValue(0);*/
}

QZegoAVScene::~QZegoAVScene()
{

}

/*WId QZegoAVScene::getLiveViewWinID_Inner()
{
	return liveView->winId();
}*/

#if (defined Q_OS_WIN32) && (defined Q_PROCESSOR_X86_32) && (defined USE_SURFACE_MERGE)
void QZegoAVScene::setSurfaceMergeItemRect(ZEGO::SurfaceMerge::ZegoCaptureItem _screen,
	ZEGO::SurfaceMerge::ZegoCaptureItem _camera)
{
	screen = _screen;
	camera = _camera;
}

void QZegoAVScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mouseDoubleClickEvent(event);
	qDebug() << "view clicked!";
    
	//QList <QGraphicsView *> list = this->views();
}

void QZegoAVScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	//qDebug() << "view pressed!";
	QZegoAVView *view = (QZegoAVView *)this->views()[0];
	qDebug() << "this view's width = " << view->width() << " height = " << view->height();
	if (!view->getSurfaceMergeView())
		return;

	QPointF mousePosition = event->scenePos();
	int vx = view->width();
	int vy = view->height();
    
	scaleFactor_X = screen.position.width*(1.0) / view->width();
	scaleFactor_Y = screen.position.height*(1.0) / view->height();
   
	float blackBorderWidth = 0;
	float blackBorderHeight = 0;
	//初始化捕捉camera的范围
	float startPointX = camera.position.xPos / scaleFactor_X;
	float endPointX = (camera.position.xPos + camera.position.width) / scaleFactor_X;
	float startPointY = camera.position.yPos / scaleFactor_Y;
	float endPointY = (camera.position.yPos + camera.position.height) / scaleFactor_Y;

	//比例大于16:9或者4:3的话，黑边出现在左右
	if (view->width() * (1.0) / view->height() > screen.position.width * (1.0) / screen.position.height)
	{
		float screenWholeWidth = view->height() * screen.position.width / screen.position.height;
		blackBorderWidth = (view->width() - screenWholeWidth) / 2;

		startPointX = screenWholeWidth * (camera.position.xPos / scaleFactor_X) / view->width();
		endPointX = screenWholeWidth * ((camera.position.xPos + camera.position.width) / scaleFactor_X) / view->width();

	}
	//比例小于16:9或者4:3的话，黑边出现在上下
	else if (view->width() * (1.0) / view->height() < screen.position.width * (1.0) / screen.position.height)
	{
		float screenWholeHeight = view->width() * screen.position.height / screen.position.width;
		blackBorderHeight = (view->height() - screenWholeHeight) / 2;
		
		startPointY = screenWholeHeight * (camera.position.yPos / scaleFactor_Y) / view->height();
		endPointY = screenWholeHeight * ((camera.position.yPos + camera.position.height) / scaleFactor_Y) / view->height();
	}

	if (mousePosition.x() >= (startPointX + blackBorderWidth) && mousePosition.x() <= (endPointX + blackBorderWidth) && mousePosition.y() >= (startPointY + blackBorderHeight) && mousePosition.y() <= (endPointY + blackBorderHeight))
	{
		qDebug() << "pressed camera!!!";
		isMousePressed = true;
		curMousePosition = mousePosition;
	}

}

void QZegoAVScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QZegoAVView *view = (QZegoAVView *)this->views()[0];
	if (!view->getSurfaceMergeView())
		return;

	if (isMousePressed){
		
		QPointF mousePosition = event->scenePos();

		if (mousePosition.x() >= view->width() || mousePosition.x() < 0)
			return;
		if (mousePosition.y() >= view->height() || mousePosition.y() < 0)
			return;

		QPointF move;
		move.setX(mousePosition.x() - curMousePosition.x());
		move.setY(mousePosition.y() - curMousePosition.y());

		bool isUpdate = false;
		//显示屏幕区域实际宽高
		float screenWholeWidth = view->width();
		float screenWholeHeight = view->height();
		//比例大于16:9或者4:3的话，黑边出现在左右
		if (view->width() * (1.0) / view->height() > screen.position.width * (1.0) / screen.position.height)
		{
			screenWholeWidth = view->height() * screen.position.width / screen.position.height;
		}
		//比例小于16:9或者4:3的话，黑边出现在上下
		else if (view->width() * (1.0) / view->height() < screen.position.width * (1.0) / screen.position.height)
		{
			screenWholeHeight = view->width() * screen.position.height / screen.position.width;
		}
		

		//右移情况
		if (move.x() > 0 && (camera.position.xPos + (move.x() * scaleFactor_X * (view->width() / screenWholeWidth)) + camera.position.width) <= (screen.position.xPos + screen.position.width))
		{
			camera.position.xPos += (int)(move.x() * scaleFactor_X * (view->width() / screenWholeWidth));
			isUpdate = true;
		}
		//右移最大值
		else if (move.x() > 0 && (camera.position.xPos + camera.position.width) < (screen.position.xPos + screen.position.width))
		{
			if (!isUpdate)
			{
				camera.position.xPos = (screen.position.width - camera.position.width);
				isUpdate = true;
			}
		}
        //左移情况
		if (move.x() < 0 && (camera.position.xPos + (move.x() * scaleFactor_X * (view->width() / screenWholeWidth)) >= 0))
        {
			camera.position.xPos += (int)(move.x() * scaleFactor_X * (view->width() / screenWholeWidth));
            isUpdate = true;
        }
        //左移最小值
        else if (move.x() < 0 && camera.position.xPos > 0)
        {
            if (!isUpdate)
            {
                camera.position.xPos = 0;
                isUpdate = true;
            }
        }
        //下移情况
		if (move.y() > 0 && (camera.position.yPos + (move.y() * scaleFactor_Y * (view->height() / screenWholeHeight)) + camera.position.height) <= (screen.position.yPos + screen.position.height))
		{
			camera.position.yPos += (int)(move.y() * scaleFactor_Y * (view->height() / screenWholeHeight));
			isUpdate = true;
		}
        //下移最大值
        else if (move.y() > 0 && (camera.position.yPos + camera.position.height) < (screen.position.yPos + screen.position.height))
        {
            if (!isUpdate)
            {
                camera.position.yPos = (screen.position.height - camera.position.height);
                isUpdate = true;
            }
        }
        //上移情况
		if (move.y() < 0 && (camera.position.yPos + (move.y() * scaleFactor_Y * (view->height() / screenWholeHeight)) >= 0))
        {
			camera.position.yPos += (int)(move.y() * scaleFactor_Y * (view->height() / screenWholeHeight));
            isUpdate = true;
        }
        //上移最小值
        else if (move.y() < 0 && camera.position.yPos > 0)
        {
            if (!isUpdate)
            {
                camera.position.yPos = 0;
                isUpdate = true;
            }
        }

		if (isUpdate)
		{
			SurfaceMerge::ZegoCaptureItem *itemList = new SurfaceMerge::ZegoCaptureItem[2];
			itemList[0] = camera;
			itemList[1] = screen;

			SurfaceMerge::UpdateSurface(itemList, 2);
			delete[]itemList;
		}
		curMousePosition = mousePosition;


	}
}

void QZegoAVScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	isMousePressed = false;
}
#endif