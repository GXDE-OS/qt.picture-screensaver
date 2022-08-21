#ifndef CONFIGPANELWINDOW_H
#define CONFIGPANELWINDOW_H

#include <QWidget>

namespace Ui {
class ConfigPanelWindow;
}

class ConfigPanelWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigPanelWindow(QWidget *parent = nullptr);

private:
    Ui::ConfigPanelWindow *ui;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
    bool closePlay;
};

#endif // CONFIGPANELWINDOW_H
