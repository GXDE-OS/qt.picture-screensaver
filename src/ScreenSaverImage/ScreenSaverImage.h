#ifndef SCREENSAVEIMAGE_H
#define SCREENSAVEIMAGE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QPropertyAnimation;
class QTiemr;
class QLabel;
class ScreenSaverConfig;
class QLCDNumber;
class TimeDateWidget;
QT_END_NAMESPACE

// TICK == Ttimer
#define TICK_COLOR       "tickColor/value"
#define TICK_SIZE        "tickGeometry/FontSize"
#define TICK_LOCATION    "tickLocation/state"
#define TICK_SHADOW_DEEP "tickShadow/Deep"
#define TICK_SHADOW_BLUR "tickShadow/Blur"

class ScreenSaverImage : public QWidget
{
    Q_OBJECT
public:
    explicit ScreenSaverImage(QWidget *parent = nullptr);
    void configChanged();
//    QLCDNumber *m_timeDateWidget;

    enum TimerState {
        TopLeft = 0,
        TopCenter,
        TopRight,
        Left,
        Center,
        Right,
        BottomLeft,
        BottomCenter,
        BottomRight,
    };

    void timerStateSet(int v);
    int timerStateGet();

    int getTimerRect();
    void setTimerRect(const int value);

    QColor getTimerColor() const;
    void setTimerColor(const QColor &value);

    TimeDateWidget *getTimeDate() const;
    void setTimeDate(TimeDateWidget *timeDateWidget);

    int getTimeShadowDeep() const;
    void setTimeShadowDeep(int value);

    int getTimeShadowBlurRadius() const;
    void setTimeShadowBlurRadius(int value);

private slots:
    void showNext();

private:
    ScreenSaverConfig *privateData;
    QPropertyAnimation *animation;
    QTimer *timer;

    QPixmap currentPixmap;
    QPixmap nextPixmap;

    QRect timerRect;
    QColor timerColor;
    TimerState timerState;
    int timeShadowDeep;
    int timeShadowBlurRadius;

    TimeDateWidget *m_timeDateWidget;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // SCREENSAVEIMAGE_H
