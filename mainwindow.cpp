#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    n.setBlue(255);
    n.setId(1);
    n.setGreen(255);
    n.setPosicionX(34);
    n.setPosicionY(21);
    n.setVoltaje(213.43);
    n.setRed(543);

    //creamos una neurona y agregamos datos, despues lo metemos en la lista

    lista.insertData(lista.getFirstPos(),n); // se inserta al principio

    lista.insertData(lista.getLastPos(),n); // se inserta al final
    lista.toString(); //este el metodo mostrar
}

