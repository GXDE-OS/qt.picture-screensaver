#include "ScreenSaverImage.h"

#include <QLabel>
#include <QPaintEvent>
#include <QPropertyAnimation>
#include <QTextStream>
#include <QThread>
#include <QVBoxLayout>
#include <qpainter.h>

#include <QLCDNumber>
#include <QTime>
#include <ScreenSaverConfig>

ScreenSaverImage::ScreenSaverImage(QWidget *parent) : QWidget(parent)
  ,timer(new QTimer)
  ,privateData(new ScreenSaverConfig)
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
    // setMinimumSize(650, 400);

    number = new QLCDNumber(this);
    number->setDigitCount(8);
    number->hide();
    number->setFrameShape(number->NoFrame);
    number->setGeometry(0,0,140,40);

    QTimer *timeTimer = new QTimer();
    //设置定时器每个多少毫秒发送一个timeout()信号
    timeTimer->setInterval(1000);
    //启动定时器
    timeTimer->start();

    //信号和槽
    connect(timeTimer, &QTimer::timeout, this, [=](){
        number->show();
        switch(state){
        case TopLeft:
            number->move(0, 0);
            break;
        case TopCenter:
            number->move((this->width() - number->width())/2, 0);
            break;
        case TopRight:
            number->move(this->width() - number->width(), 0);
            break;
        case Left:
            number->move(0, (this->height() - number->height())/2);
            break;
        case Center:
            number->move((this->width() - number->width())/2, (this->height() - number->height())/2);
            break;
        case Right:
            number->move(this->width() - number->width(), (this->height() - number->height())/2);
            break;
        case BottomLeft:
            number->move(0, this->height() - number->height());
            break;
        case BottomCenter:
            number->move((this->width() - number->width())/2, this->height() - number->height());
            break;
        case BottomRight:
            number->move(this->width() - number->width(), this->height() - number->height());
            break;
        }
        // number->move(this->width() - number->width(), this->height() - number->height());
        QTime time = QTime::currentTime();
        number->display(time.toString("hh:mm:ss"));
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

void ScreenSaverImage::configChanged()
{
    privateData->reloadConfig();
    timer->setInterval(privateData->getTimeout());
    animation->setDuration(privateData->getTimeout()-200);
//    animation->stop();
    //    showNext();
}

void ScreenSaverImage::timerStateSet(int v)
{
    privateData->setKeyValueInt("tickLocation/state", v);
    state = ScreenSaverImage::TimerState(v);
}

int ScreenSaverImage::timerStateGet()
{
    int v = privateData->getKeyValueInt("tickLocation/state");
    state = ScreenSaverImage::TimerState(v);
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
