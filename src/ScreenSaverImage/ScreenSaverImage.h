#ifndef SCREENSAVEIMAGE_H
#define SCREENSAVEIMAGE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QPropertyAnimation;
class QTiemr;
class QLabel;
class ScreenSaverConfig;
class QLCDNumber;
QT_END_NAMESPACE
class ScreenSaverImage : public QWidget
{
    Q_OBJECT
public:
    explicit ScreenSaverImage(QWidget *parent = nullptr);
    void configChanged();
    QLCDNumber *number;

    enum TimerState {
        TopLeft,
        TopCenter,
        TopRight,
        Left,
        Center,
        Right,
        BottomLeft,
        BottomCenter,
        BottomRight,
    };

    TimerState state;

    void timerStateSet(int v);
    int timerStateGet();

    QRect getTimerRect();
    void setTimerRect(const QRect &value);

private slots:
    void showNext();

private:
    ScreenSaverConfig *privateData;
    QPropertyAnimation *animation;
    QTimer *timer;

    QPixmap currentPixmap;
    QPixmap nextPixmap;

    QRect timerRect;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // SCREENSAVEIMAGE_H
