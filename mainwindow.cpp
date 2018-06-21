#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::abrirPorta(QString portName)
{
    serial = new QSerialPort(this);
    serial->setPortName(portName);
    serial->open(QIODevice::ReadWrite);
    serial->setBaudRate(QSerialPort::Baud9600, QSerialPort::AllDirections);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);


    connect(serial, SIGNAL(readyRead()),
            this, SLOT(dadosRecebidos()));

    return serial->isOpen();
}

void MainWindow::fecharPorta()
{
    serial->close();
}

void MainWindow::enviarComando(QString comando)
{
    QByteArray output = comando.toUtf8();
    serial->write(output);
}

void MainWindow::dadosRecebidos()
{

 // ----------------------Recebendo dados da Serial--------------------------
    QByteArray m_readData;
    m_readData += serial->readLine();
    while (serial->waitForReadyRead(50)) // MUDAR VALOR CASO A STRING SEJA MUITO LONGA
        m_readData += serial->readLine();
    QString data = QString::fromUtf8(m_readData);

//----------------------MANIPULAR DADOS RECEBIDOS-----------------------------
    QStringList dados;
    if (not data.contains("Falhou")){
        dados = data.split(",");

        ui->tempLabel->setText(dados[0] + "º C");
        ui->umidLabel->setText(dados[1] + " % ");
        ui->lumiLabel->setText(dados[2]);

    }
}

void MainWindow::on_btn_openPort_clicked()
{
    QString porta = ui->inputPort->text();
    if( abrirPorta(porta) ){
        ui->connectionStatus->setText("Conexão OK");
    }
}

void MainWindow::on_btn_dimmer_clicked()
{
 QString dimmer = ui->inputDimmer->text();
 enviarComando(dimmer);
}

void MainWindow::on_btn_closePort_clicked()
{
    fecharPorta();
    ui->connectionStatus->setText("Sem Conexão");
}
