#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void sendButtonClicked();
    void receiveButtonClicked();
    //serial port stuff
    void openSerialPort();
    void closeSerialPort();
    void writeData(const QByteArray &data);
    void readData();
    void handleError(QSerialPort::SerialPortError error);

private:
    void initActionsConnections();

private:
    Ui::MainWindow *ui;
    QSerialPort *m_serial;
};

#endif // MAINWINDOW_H

