#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_serial(new QSerialPort(this))
{
    ui->setupUi(this);
    connect(ui->btnSend, SIGNAL (clicked(bool)), this, SLOT (sendButtonClicked()));
    connect(ui->btnReceive, SIGNAL (clicked(bool)), this, SLOT (receiveButtonClicked()));
    //serial port stuff
    connect(m_serial, &QSerialPort::errorOccurred, this, &MainWindow::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendButtonClicked()
{
    ui->lblResults->setText("Send Clicked");
}

void MainWindow::receiveButtonClicked()
{
    ui->lblResults->setText("Receive Clicked");
}

void MainWindow::openSerialPort()
{
    m_serial->setPortName("/dev/ttyUSB0");
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::HardwareControl);
    if (m_serial->open(QIODevice::ReadWrite)) {
        showStatusMessage(tr("Connected"));
    } else {
        QMessageBox::critical(this, tr("Error"), m_serial->errorString());

        showStatusMessage(tr("Open error"));
    }
}

void MainWindow::showStatusMessage(const QString &message)
{
    ui->lblResults->setText(message);
}
