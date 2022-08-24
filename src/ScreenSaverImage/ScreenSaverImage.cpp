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
  ,config(new ScreenSaverConfig)
  ,timerVisible(config->Visible())
  ,timerState(TimerState::Center)
  ,timeShadowDeep(config->ShadowDeep())
  ,timeShadowBlurRadius(config->shadowBlur())
{

    animation = new QPropertyAnimation(this, "ImageOpacity");
    animation->setDuration(config->Timeout() - 200);
    animation->setEasingCurve(QEasingCurve::InOutQuart);
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);

    timer->setInterval(config->Timeout());
    connect(timer, &QTimer::timeout, this, &ScreenSaverImage::showNext);

    connect(animation, SIGNAL(valueChanged(const QVariant&)), this, SLOT(update()));
    connect(animation, SIGNAL(finished()), timer, SLOT(start()));

    showNext();

    m_timeDateWidget = new TimeDateWidget(this);
    m_timeDateWidget->hide();
    m_timeDateWidget->setShadowDeep(timeShadowDeep);
    m_timeDateWidget->setShadowBlurRadius(timeShadowBlurRadius);

    connect(m_timeDateWidget, &TimeDateWidget::onShadowDeepChanged, this, [=](int val){
        config->setShadowDeep(val);
    });
    connect(m_timeDateWidget, &TimeDateWidget::onShadowBlurChanged, this, [=](int val){
        config->setshadowBlur(val);
    });

    QTimer *timeTimer = new QTimer();
    timeTimer->start(1000);

    //信号和槽
    connect(timeTimer, &QTimer::timeout, this, [=](){
//        m_timeDateWidget->setFontSize(getTimerRect());
        m_timeDateWidget->setStyleSheet(QString("color: %1").arg(getTimerColor().name()));
        if (timerVisible) {
            m_timeDateWidget->show();
        } else {
            m_timeDateWidget->hide();
        }

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
    nextPixmap = config->nextImage();

    animation->start();
}

bool ScreenSaverImage::getTimerVisible() const
{
    int value = config->Visible();
    return value;
}

void ScreenSaverImage::setTimerVisible(bool value)
{
    timerVisible = value;
    config->setVisible(value);
}

int ScreenSaverImage::getTimeShadowDeep() const
{
    int value = config->ShadowDeep();
    return value;
}

void ScreenSaverImage::setTimeShadowDeep(int value)
{
    timeShadowDeep = value;
    m_timeDateWidget->setShadowDeep(value);
}

int ScreenSaverImage::getTimeShadowBlurRadius() const
{
    int value = config->shadowBlur();
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
    QString value = config->Color();
    if (value.isEmpty()) {
        value = "#414D68";
    }
    return QColor(value);
}

void ScreenSaverImage::setTimerColor(const QColor &value)
{
    config->setColor(value.name());
}

int ScreenSaverImage::getTimerRect()
{
    // int value = config->getKeyValueInt(TICK_SIZE);
    return 0;
}

void ScreenSaverImage::setTimerRect(const int value)
{
    // config->setKeyValueInt(TICK_SIZE, value);
}

void ScreenSaverImage::configChanged()
{
    // config->reloadConfig();
    timer->setInterval(config->Timeout());
    animation->setDuration(config->Timeout()-200);
}

void ScreenSaverImage::timerStateSet(int v)
{
    config->setLocation(config->LocationIndexToString(v));
    timerState = ScreenSaverImage::TimerState(v);
}

int ScreenSaverImage::timerStateGet()
{
    int v = config->LocationToIndex(config->Location());
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
