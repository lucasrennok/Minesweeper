#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "minesweeper.h"
#include <stdbool.h>
#include <iostream>

using namespace std;

int dif = 1;
bool bool_connect=false, bool_create=false;
QString ip_connect = "";
int m_x=0, m_y=0, mines=0;
pMatriz** matrix;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBoxConfig->hide();
    ui->groupBoxConfig->setDisabled(true);
    ui->groupBoxGameB->hide();
    ui->groupBoxGameB->setDisabled(true);
    ui->groupBoxGameI->hide();
    ui->groupBoxGameI->setDisabled(true);
    ui->groupBoxGameE->hide();
    ui->groupBoxGameE->setDisabled(true);
}

MainWindow::~MainWindow()
{
    if(m_x!=0){
        desalocacao(matrix, m_x);
    }
    delete ui;
}

void MainWindow::on_actionMultiplayer_triggered()
{
    if(bool_connect==false && bool_create==false){
        cout << ">>nothing configured to multiplayer" << endl;
    }else if(bool_connect==true){
        ip_connect = ui->textIP->toPlainText();
        cout << "Connecting to: " << ip_connect.toStdString() << endl;
    }else{
        cout << "Created game" << endl;
    }

    printaCampo(matrix, m_x, m_y, 1, 1, mines);

    if(dif==1){
        ui->groupBoxGameB->show();
        ui->groupBoxGameB->setDisabled(false);
    }else if(dif==2){
        ui->groupBoxGameI->show();
        ui->groupBoxGameI->setDisabled(false);
    }else{
        ui->groupBoxGameE->show();
        ui->groupBoxGameE->setDisabled(false);
    }

    cout << "-Multiplayer Mode-" << endl;
    ui->groupBoxConfig->hide();
    ui->groupBoxConfig->setDisabled(true);
}

void MainWindow::on_actionSingleplayer_triggered()
{
    printaCampo(matrix, m_x, m_y, 1, 1, mines);
    if(dif==1){
        ui->groupBoxGameB->show();
        ui->groupBoxGameB->setDisabled(false);
    }else if(dif==2){
        ui->groupBoxGameI->show();
        ui->groupBoxGameI->setDisabled(false);
    }else{
        ui->groupBoxGameE->show();
        ui->groupBoxGameE->setDisabled(false);
    }
    cout << "-Singleplayer Mode-" << endl;
    ui->groupBoxConfig->hide();
    ui->groupBoxConfig->setDisabled(true);
}

void MainWindow::on_actionConfiguration_triggered()
{
    if(dif==1){
        ui->groupBoxGameB->hide();
        ui->groupBoxGameB->setDisabled(true);
    }else if(dif==2){
        ui->groupBoxGameI->hide();
        ui->groupBoxGameI->setDisabled(true);
    }else{
        ui->groupBoxGameE->hide();
        ui->groupBoxGameE->setDisabled(true);
    }
    cout << "-Configuration Triggered-" << endl;
    ui->groupBoxConfig->show();
    ui->groupBoxConfig->setDisabled(false);
}

void MainWindow::on_radioBeginner_clicked()
{
    if(m_x!=0){
        desalocacao(matrix, m_x);
    }
    dif = 1;m_x=8;m_y=8;mines=10;
    matrix = alocacao(m_x,m_y);
    cout << "Beginner Selected" << endl;
    gerarCampo(matrix,m_x,m_y,mines);
}

void MainWindow::on_radioIntermediate_clicked()
{
    if(m_x!=0){
        desalocacao(matrix, m_x);
    }
    dif = 2;m_x=16;m_y=16;mines=40;
    matrix = alocacao(m_x,m_y);
    cout << "Intermediate Selected" << endl;
    gerarCampo(matrix,m_x,m_y,mines);
}

void MainWindow::on_radioExpert_clicked()
{
    if(m_x!=0){
        desalocacao(matrix, m_x);
    }
    dif = 3;m_x=16;m_y=30;mines=99;
    matrix = alocacao(m_x,m_y);
    cout << "Expert Selected" << endl;
    gerarCampo(matrix,m_x,m_y,mines);
}

void MainWindow::on_radioCreate_clicked()
{
    cout << "Create MULTIPLAYER" << endl;
    bool_create = true;
    bool_connect = false;
}

void MainWindow::on_radioConnect_clicked()
{
    cout << "Connect MULTIPLAYER" << endl;
    bool_connect = true;
    bool_create = false;
}

