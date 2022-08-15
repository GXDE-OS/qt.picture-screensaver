#ifndef CONFIGPANELWINDOW_H
#define CONFIGPANELWINDOW_H

#include <QWidget>

class ConfigPanelWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigPanelWindow(QWidget *parent = nullptr);

signals:

public slots:

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
    bool closePlay;
};

#endif // CONFIGPANELWINDOW_H
