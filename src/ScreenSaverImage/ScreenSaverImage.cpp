#include "ScreenSaverImage.h"

#include <QLabel>
#include <QPaintEvent>
#include <QPropertyAnimation>
#include <QTextStream>
#include <QThread>
#include <QVBoxLayout>
#include <qpainter.h>

#include <QGraphicsDropShadowEffect>
#include <QLCDNumber>
#include <QTime>
#include <ScreenSaverConfig>
#include <timedatewidget.h>

ScreenSaverImage::ScreenSaverImage(QWidget *parent) : QWidget(parent)
  ,timer(new QTimer)
  ,privateData(new ScreenSaverConfig)
  ,timerState(TimerState::Center)
  ,timeShadowDeep(privateData->getKeyValueInt(TICK_SHADOW_DEEP))
  ,timeShadowBlurRadius(privateData->getKeyValueInt(TICK_SHADOW_BLUR))
{

    animation = new QPropertyAnimation(this, "ImageOpacity");
    animation->setDuration(privateData->getTimeout() - 200);
    animation->setEasingCurve(QEasingCurve::InOutQuart);
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);

    timer->setInterval(privateData->getTimeout());
    connect(timer, &QTimer::timeout, this, &ScreenSaverImage::showNext);

    connect(animation, SIGNAL(valueChanged(const QVariant&)), this, SLOT(update()));
    connect(animation, SIGNAL(finished()), timer, SLOT(start()));

    showNext();

    m_timeDateWidget = new TimeDateWidget(this);
    m_timeDateWidget->hide();
    m_timeDateWidget->setShadowDeep(timeShadowDeep);
    m_timeDateWidget->setShadowBlurRadius(timeShadowBlurRadius);

    connect(m_timeDateWidget, &TimeDateWidget::onShadowDeepChanged, this, [=](int val){
        privateData->setKeyValueInt(TICK_SHADOW_DEEP, val);
    });
    connect(m_timeDateWidget, &TimeDateWidget::onShadowBlurChanged, this, [=](int val){
        privateData->setKeyValueInt(TICK_SHADOW_BLUR, val);
    });

    QTimer *timeTimer = new QTimer();
    timeTimer->start(1000);

    //信号和槽
    connect(timeTimer, &QTimer::timeout, this, [=](){
//        m_timeDateWidget->setFontSize(getTimerRect());
        m_timeDateWidget->setStyleSheet(QString("color: %1").arg(getTimerColor().name()));
        m_timeDateWidget->show();

        switch(timerState){
        case TopLeft:
            m_timeDateWidget->move(0, 0);
            break;
        case TopCenter:
            m_timeDateWidget->move((this->width() - m_timeDateWidget->width())/2, 0);
            break;
        case TopRight:
            m_timeDateWidget->move(this->width() - m_timeDateWidget->width(), 0);
            break;
        case Left:
            m_timeDateWidget->move(0, (this->height() - m_timeDateWidget->height())/2);
            break;
        case Center:
            m_timeDateWidget->move((this->width() - m_timeDateWidget->width())/2, (this->height() - m_timeDateWidget->height())/2);
            break;
        case Right:
            m_timeDateWidget->move(this->width() - m_timeDateWidget->width(), (this->height() - m_timeDateWidget->height())/2);
            break;
        case BottomLeft:
            m_timeDateWidget->move(0, this->height() - m_timeDateWidget->height());
            break;
        case BottomCenter:
            m_timeDateWidget->move((this->width() - m_timeDateWidget->width())/2, this->height() - m_timeDateWidget->height());
            break;
        case BottomRight:
            m_timeDateWidget->move(this->width() - m_timeDateWidget->width(), this->height() - m_timeDateWidget->height());
            break;
        }
    });

    timerStateGet();
}

void ScreenSaverImage::showNext()
{
    timer->stop();

    currentPixmap = nextPixmap;
    nextPixmap = privateData->nextImage();

    animation->start();
}

int ScreenSaverImage::getTimeShadowDeep() const
{
    int value = privateData->getKeyValueInt(TICK_SHADOW_DEEP);
    return value;
}

void ScreenSaverImage::setTimeShadowDeep(int value)
{
    timeShadowDeep = value;
    m_timeDateWidget->setShadowDeep(value);
}

int ScreenSaverImage::getTimeShadowBlurRadius() const
{
    int value = privateData->getKeyValueInt(TICK_SHADOW_BLUR);
    return value;
}

void ScreenSaverImage::setTimeShadowBlurRadius(int value)
{
    timeShadowBlurRadius = value;
    m_timeDateWidget->setShadowBlurRadius(value);
}

TimeDateWidget *ScreenSaverImage::getTimeDate() const
{
    return m_timeDateWidget;
}

void ScreenSaverImage::setTimeDate(TimeDateWidget *timeDateWidget)
{
    m_timeDateWidget = timeDateWidget;
}

QColor ScreenSaverImage::getTimerColor() const
{
    QString value = privateData->getKeyValueString(TICK_COLOR);
    if (value.isEmpty()) {
        value = "#414D68";
    }
    return QColor(value);
}

void ScreenSaverImage::setTimerColor(const QColor &value)
{
    privateData->setKeyValueString(TICK_COLOR, value.name());
}

int ScreenSaverImage::getTimerRect()
{
    int value = privateData->getKeyValueInt(TICK_SIZE);
    return value;
}

void ScreenSaverImage::setTimerRect(const int value)
{
    privateData->setKeyValueInt(TICK_SIZE, value);
}

void ScreenSaverImage::configChanged()
{
    privateData->reloadConfig();
    timer->setInterval(privateData->getTimeout());
    animation->setDuration(privateData->getTimeout()-200);
}

void ScreenSaverImage::timerStateSet(int v)
{
    privateData->setKeyValueInt(TICK_LOCATION, v);
    timerState = ScreenSaverImage::TimerState(v);
}

int ScreenSaverImage::timerStateGet()
{
    int v = privateData->getKeyValueInt(TICK_LOCATION);
    timerState = ScreenSaverImage::TimerState(v);
    return v;
}

void ScreenSaverImage::resizeEvent(QResizeEvent *event)
{

}

void ScreenSaverImage::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    painter.save();

    if (currentPixmap == nextPixmap || nextPixmap.isNull()) {
        if (!currentPixmap.isNull())
            painter.drawPixmap(rect(), currentPixmap);
    } else {
        float imageOpacity = this->property("ImageOpacity").toFloat();
        painter.setOpacity(1);

        painter.drawPixmap(rect(), nextPixmap);
        painter.setOpacity(imageOpacity);
        painter.drawPixmap(rect(), currentPixmap);
    }
    painter.restore();
}
