#pragma once

#include <QWidget>  
#include <QColor> 

class ZegoProgressIndicator : public QWidget  
{  
    Q_OBJECT  
    Q_PROPERTY(int delay READ animationDelay WRITE setAnimationDelay)  
    Q_PROPERTY(bool displayedWhenStopped READ isDisplayedWhenStopped WRITE setDisplayedWhenStopped)  
    Q_PROPERTY(QColor color READ color WRITE setColor)  
public:  
	ZegoProgressIndicator(QWidget* parent = 0);
  
    int animationDelay() const { return delay_; }  
  
    /*  动画是否正在进行中  */  
    bool isAnimated () const;  
  
    /*  动画完毕后，是否隐藏菊花转  */  
    bool isDisplayedWhenStopped() const;  
  
    /*  当前菊花转的颜色  */  
    const QColor & color() const { return color_; }  
  
    /*  虚函数：当前大小  */  
    virtual QSize sizeHint() const;  
  
    void setBackground(const QString& _icon) {  
        currentPix_ = QPixmap(_icon);  
    }  
signals:  
    void Finished(void);  
public slots:  
  
    /*  开始动画  */  
    void startAnimation();  
  
    /*  停止动画  */  
    void stopAnimation();  
  
    /*  设置菊花转的转速  */  
    void setAnimationDelay(int delay);  
  
    /*  动画完毕后，是否隐藏菊花转  */  
    void setDisplayedWhenStopped(bool state);  
  
    /*  设置菊花转颜色  */  
    void setColor(const QColor & color);  
  
    /* 
     * 进度 
     * 参数 _progress：当前进度 0 < _progress < 100 
    */  
    void onProgress(short _progress) { progress_ = _progress; }  
protected:  
    /*  系统基类函数 */  
    virtual void timerEvent(QTimerEvent * event);  
    virtual void paintEvent(QPaintEvent * event);  
private:  
    /*  角度  */  
    unsigned int angle_;  
    /*  定时器ID  */  
    int timerId_;  
    /*  转速  */  
    int delay_;  
    /*  是否隐藏  */  
    bool displayedWhenStopped_;  
    /*  菊花转颜色  */  
    QColor color_;  
    /*  进度  */  
    short progress_;  
    /*  背景图  */  
    QPixmap currentPix_;  
};  
  
