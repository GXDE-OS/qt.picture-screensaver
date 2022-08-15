#include "configpanelwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <config.h>
#include <QTextStream>
#include <QDialog>
#include <QFileDialog>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLCDNumber>

#include <QPaintEvent>
#include <QPropertyAnimation>
#include <QSlider>
#include <ScreenSaveImage>
#include <ScreenSaverConfig>

ConfigPanelWindow::ConfigPanelWindow(QWidget *parent) : QWidget(parent)
  , closePlay(true)
{

    QLineEdit *inputDirEdit = new QLineEdit();
    QPushButton *chooseDirBtn = new QPushButton("选择位置");
    ScreenSaverImage *ssi = new ScreenSaverImage();

    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(100);
    slider->setMaximum(10000);
    slider->setSingleStep(100);
    slider->setFocus();
    QLabel *sliderSpeedLab = new QLabel();

    QGroupBox *box = new QGroupBox("屏保配置");
    QGridLayout *boxLayout = new QGridLayout(box);

    int index = 0;
    boxLayout->addWidget(new QLabel("图片位置:"),index,0);
    boxLayout->addWidget(inputDirEdit, index,1);
    boxLayout->addWidget(chooseDirBtn, index,2);
    index++;
    boxLayout->addWidget(new QLabel("切换速度:"), index, 0);
    boxLayout->addWidget(slider, index, 1);
    boxLayout->addWidget(sliderSpeedLab, index, 2);

    // QSlider *sliderx = new QSlider(Qt::Horizontal);
    // QSlider *slidery = new QSlider(Qt::Horizontal);
    // QSlider *sliderw = new QSlider(Qt::Horizontal);
    // QSlider *sliderh = new QSlider(Qt::Horizontal);

    QComboBox *comb = new QComboBox();
    // comb->addItem("")
    comb->addItem("左上", ScreenSaverImage::TimerState::TopLeft);
    comb->addItem("中上", ScreenSaverImage::TimerState::TopCenter);
    comb->addItem("右上", ScreenSaverImage::TimerState::TopRight);
    comb->addItem("左"  , ScreenSaverImage::TimerState::Left);
    comb->addItem("中"  , ScreenSaverImage::TimerState::Center);
    comb->addItem("右"  , ScreenSaverImage::TimerState::Right);
    comb->addItem("左下", ScreenSaverImage::TimerState::BottomLeft);
    comb->addItem("中下", ScreenSaverImage::TimerState::BottomCenter);
    comb->addItem("右下", ScreenSaverImage::TimerState::BottomRight);
    comb->setCurrentIndex(ssi->timerStateGet());

    index++;
    boxLayout->addWidget(new QLabel("时钟位置:"), index, 0);
    boxLayout->addWidget(comb, index, 1,1,2);

    QGroupBox *previewBox = new QGroupBox("屏保预览");
    QVBoxLayout *previewBoxLayout = new QVBoxLayout(previewBox);
    previewBoxLayout->addWidget(ssi);
    previewBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QWidget *widget = this;
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->addWidget(box);
    layout->addWidget(previewBox);
    layout->setAlignment(Qt::AlignTop);

    widget->setMinimumSize(700, 550);
    widget->setWindowOpacity(0);
    widget->show();

    inputDirEdit->setText(ScreenSaverConfig().getImageDirPath());
    QObject::connect(inputDirEdit, &QLineEdit::textChanged, widget, [=](const QString &path){
        if (inputDirEdit->text().isEmpty()) return;
        ScreenSaverConfig().setImageDirPath(path);
        ssi->configChanged();
    });

    QObject::connect(chooseDirBtn, &QPushButton::clicked, widget, [=](){
        QString path = QFileDialog::getExistingDirectory(widget, "打开屏保预览目录",
                                          getenv("HOME"),
                                          QFileDialog::ShowDirsOnly
                                          | QFileDialog::DontResolveSymlinks);

        if (!path.isEmpty()) {
            inputDirEdit->setText(path);
        }
    });

    QObject::connect(slider, &QAbstractSlider::valueChanged, widget, [=](int val){
        ScreenSaverConfig().setTimeout(val);
        ssi->configChanged();
        sliderSpeedLab->setText(QString("当前速度: %1 秒").arg(val/1000.0));
    });
    slider->setValue(ScreenSaverConfig().getTimeout());

    QPropertyAnimation *animation = new QPropertyAnimation(widget, "windowOpacity");
    animation->setEasingCurve(QEasingCurve::OutQuart);
    animation->setDuration(500);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    QObject::connect(animation, &QPropertyAnimation::valueChanged, widget, [=](const QVariant &value){
        widget->repaint();
        setWindowTitle(QString("(๑•̀ㅁ•́ฅ✧ - %1%").arg(int(value.toFloat() * 100)));
    });
    QObject::connect(animation, &QPropertyAnimation::finished, widget, [=](){
        setWindowTitle(qApp->applicationName());
    });
    animation->start();

    QObject::connect(comb, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), widget, [=](int val){
        ssi->timerStateSet(val);
    });

// QObject::connect(sliderx, &QSlider::valueChanged, widget, [=](int val){
//     QRect rect = ssi->number->rect();
//     rect.setX(val);
//     ssi->number->setGeometry(rect);
// });
// QObject::connect(slidery, &QSlider::valueChanged, widget, [=](int val){
//     QRect rect = ssi->number->rect();
//     rect.setY(val);
//     ssi->number->setGeometry(rect);
// });
// QObject::connect(sliderw, &QSlider::valueChanged, widget, [=](int val){
//     QRect rect = ssi->number->rect();
//     rect.setWidth(val);
//     ssi->number->setGeometry(rect);
// });
// QObject::connect(sliderh, &QSlider::valueChanged, widget, [=](int val){
//     QRect rect = ssi->number->rect();
//     rect.setHeight(val);
//     ssi->number->setGeometry(rect);
// });

}

void ConfigPanelWindow::closeEvent(QCloseEvent *event)
{
    if (closePlay) {
        QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
        animation->setEasingCurve(QEasingCurve::OutQuart);
        animation->setDuration(500);
        animation->setStartValue(1.0);
        animation->setEndValue(0.0);

        QObject::connect(animation, &QPropertyAnimation::valueChanged, this, [=](const QVariant &value){
            this->repaint();
            setWindowTitle(QString("ヾ(⌒∇⌒*)See You♪ - %1%").arg(int(value.toFloat() * 100)));
        });

        QObject::connect(animation, &QPropertyAnimation::finished, this, [=](){
            closePlay = false;
            this->close();
        });
        animation->start();

        event->ignore();
    } else {
        event->accept();
    }
}
