#include "timedatewidget.h"
#include "ui_timedatewidget.h"
#include <QTimer>
#include <QTime>
#include <QGraphicsDropShadowEffect>

TimeDateWidget::TimeDateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeDateWidget)
  , timeFontSize(0)
  , dateFontSize(0)
  , shadowDeep(0)
  , shadowBlurRadius(0)
{
    ui->setupUi(this);

    timeFontSize = ui->timelab->font().pointSize();
    dateFontSize = ui->datelab->font().pointSize();

    QTimer *timeTimer = new QTimer();
    timeTimer->start(1000);

    connect(timeTimer, &QTimer::timeout, this, [=](){
        QTime time = QTime::currentTime();
        ui->timelab->setText(time.toString("hh:mm"));
        ui->datelab->setText(QDateTime::currentDateTime().toString("yyyy.MM.dd dddd"));
        setShadow(ui->timelab);
        setShadow(ui->datelab);
    });
}

TimeDateWidget::~TimeDateWidget()
{
     delete ui;
}

void TimeDateWidget::setFontSize(int val)
{
    QFont font = ui->timelab->font();
    font.setPointSize(timeFontSize + (val*(timeFontSize/dateFontSize)));
    ui->timelab->setFont(font);

    font = ui->datelab->font();
    font.setPointSize(dateFontSize + val);
    ui->datelab->setFont(font);

    int w = rect().width();
    int h = rect().height();

    QRect localQRect = QRect(0, 0, w + ((w/h)*val), h + val);
    setGeometry(localQRect);
}

void TimeDateWidget::setTimeFontSize(int val)
{
    QFont font = ui->timelab->font();
    font.setPointSize(font.pointSize()+val);
    ui->timelab->setFont(font);
}

void TimeDateWidget::setDateFontSize(int val)
{
    QFont font = ui->datelab->font();
    font.setPointSize(font.pointSize()+val);
    ui->datelab->setFont(font);
}

void TimeDateWidget::setShadow(QLabel *label)
{
    QGraphicsDropShadowEffect *shadow_1=new QGraphicsDropShadowEffect();
    shadow_1->setBlurRadius(shadowBlurRadius);
    shadow_1->setColor(QColor(63, 63, 63, shadowDeep));
    shadow_1->setOffset(0.5);
    label->setGraphicsEffect(shadow_1);
}


int TimeDateWidget::getShadowBlurRadius() const
{
    return shadowBlurRadius;
}

void TimeDateWidget::setShadowBlurRadius(int value)
{
    shadowBlurRadius = value;
    setShadow(ui->timelab);
    setShadow(ui->datelab);

    emit onShadowBlurChanged(value);
}

int TimeDateWidget::getShadowDeep() const
{
    return shadowDeep;
}

void TimeDateWidget::setShadowDeep(int value)
{
    shadowDeep = value;
    setShadow(ui->timelab);
    setShadow(ui->datelab);

    emit onShadowDeepChanged(value);
}
