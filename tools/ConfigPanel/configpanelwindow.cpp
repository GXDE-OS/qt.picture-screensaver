#include "configpanelwindow.h"
#include "ui_configpanelwindow.h"
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

#include <QColorDialog>
#include <QPaintEvent>
#include <QPropertyAnimation>
#include <QRgb>
#include <QSlider>
#include <ScreenSaveImage>
#include <ScreenSaverConfig>
#include <timedatewidget.h>

ConfigPanelWindow::ConfigPanelWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigPanelWindow)
  , closePlay(true)
{
    ui->setupUi(this);

    ScreenSaverImage *ssi = new ScreenSaverImage();
    TimeDateWidget *timeDate = ssi->getTimeDate();

    ui->comb->setCurrentIndex(ssi->timerStateGet());

    QLineEdit *inputDirEdit = ui->inputDirEdit;
    QPushButton *chooseDirBtn = ui->chooseDirBtn;
    QSlider *sliderSpeed = ui->sliderSpeed;
    QLabel *sliderSpeedLab = ui->sliderSpeedLab;

    QComboBox *comb = ui->comb;
    QSlider *sliderSize = ui->sliderSize;
    QPushButton *colorBtn = ui->colorBtn;

    QSlider *sliderShadow = ui->sliderShadow;
    QSlider *sliderShadowRadius = ui->sliderShadowRadius;


    QGroupBox *previewBox = ui->previewBox;
    previewBox->layout()->addWidget(ssi);
    previewBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QWidget *widget = this;
    widget->setMinimumSize(700, 550);
    widget->setWindowOpacity(0);
    widget->show();

    QObject::connect(sliderSize, &QAbstractSlider::valueChanged, widget, [=](int val){
        ssi->setTimerRect(val);
    });
    sliderSize->setValue(ssi->getTimerRect());

    QObject::connect(colorBtn, &QPushButton::clicked, widget, [=](){
        QColor defaultColor = QColor("#008B8B");
            QColorDialog colorDlg(this);
            colorDlg.setGeometry(200,200,300,280);//此句注释掉之后会再程序运行的时候提示信息
            colorDlg.setWindowTitle(QStringLiteral("颜色选择对话框"));
            colorDlg.setCurrentColor(defaultColor);
            if (colorDlg.exec() == QColorDialog::Accepted) {
                QColor color = colorDlg.selectedColor();
                colorBtn->setStyleSheet(QString("background-color: %1").arg(color.name()));
                QTextStream(stdout) << QString("color: %1").arg(color.name()) << "\n";
                ssi->setTimerColor(color);
//                qDebug()<<QStringLiteral("选择的颜色:红")<<m_color.red()<<QStringLiteral("绿：")<<m_color.green()<<QStringLiteral("蓝：")<<m_color.blue();
            }

    });
    colorBtn->setStyleSheet(QString("background-color: %1").arg(ssi->getTimerColor().name()));


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

    QObject::connect(sliderSpeed, &QAbstractSlider::valueChanged, widget, [=](int val){
        ScreenSaverConfig().setTimeout(val);
        ssi->configChanged();
        sliderSpeedLab->setText(QString("当前速度: %1 秒").arg(val/1000.0));
    });
    sliderSpeed->setValue(ScreenSaverConfig().getTimeout());

    QObject::connect(ui->timerVisible, &QGroupBox::clicked, widget, [=](){
        if (ui->timerVisible->isChecked()) {
            ssi->setTimerVisible(true);
        } else {
            ssi->setTimerVisible(false);
        }
    });
    ui->timerVisible->setChecked(ssi->getTimerVisible());

    QObject::connect(sliderShadow, &QAbstractSlider::valueChanged, widget, [=](int val){
        ssi->setTimeShadowDeep(val);
    });
    sliderShadow->setValue(ssi->getTimeShadowDeep());

    QObject::connect(sliderShadowRadius, &QAbstractSlider::valueChanged, widget, [=](int val){
        ssi->setTimeShadowBlurRadius(val);
    });
    sliderShadowRadius->setValue(ssi->getTimeShadowBlurRadius());

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
//     QRect rect = ssi->m_timeDateWidget->rect();
//     rect.setX(val);
//     ssi->m_timeDateWidget->setGeometry(rect);
// });
// QObject::connect(slidery, &QSlider::valueChanged, widget, [=](int val){
//     QRect rect = ssi->m_timeDateWidget->rect();
//     rect.setY(val);
//     ssi->m_timeDateWidget->setGeometry(rect);
// });
// QObject::connect(sliderw, &QSlider::valueChanged, widget, [=](int val){
//     QRect rect = ssi->m_timeDateWidget->rect();
//     rect.setWidth(val);
//     ssi->m_timeDateWidget->setGeometry(rect);
// });
// QObject::connect(sliderh, &QSlider::valueChanged, widget, [=](int val){
//     QRect rect = ssi->m_timeDateWidget->rect();
//     rect.setHeight(val);
//     ssi->m_timeDateWidget->setGeometry(rect);
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
