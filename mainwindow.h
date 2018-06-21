#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSerialPort>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QSerialPort *serial;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    bool abrirPorta(QString portName);
    void fecharPorta();
    void enviarComando(QString comando);
    void dadosRecebidos();

private slots:
    QString readData();

   void on_btn_openPort_clicked();
   void on_btn_dimmer_clicked();

   void on_btn_closePort_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
