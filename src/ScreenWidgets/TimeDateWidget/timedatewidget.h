#ifndef TIMEDATEWIDGET_H
#define TIMEDATEWIDGET_H

#include <QWidget>

namespace Ui {
class TimeDateWidget;
}

class QLabel;
class TimeDateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimeDateWidget(QWidget *parent = nullptr);
    ~TimeDateWidget();
    
    void setFontSize(int val);
    void setTimeFontSize(int val);
    void setDateFontSize(int val);

    void setShadow(QLabel *label);

    int getShadowBlurRadius() const;
    void setShadowBlurRadius(int value);

    int getShadowDeep() const;
    void setShadowDeep(int value);

signals:
    void onShadowDeepChanged(int val);
    void onShadowBlurChanged(int val);

private:
    Ui::TimeDateWidget *ui;
    int timeFontSize;
    int dateFontSize;

    int shadowDeep;
    int shadowBlurRadius;
};

#endif // TIMEDATEWIDGET_H
