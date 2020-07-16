#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "minesweeper.h"
#include <iostream>

using namespace std;

int dif = 1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dificulty_hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dificulty_show(){
    ui->labelDifficulty->show();
    ui->radioBegginer->show();
    ui->radioIntermediate->show();
    ui->radioExpert->show();
}

void MainWindow::dificulty_hide(){
    ui->labelDifficulty->hide();
    ui->radioBegginer->hide();
    ui->radioIntermediate->hide();
    ui->radioExpert->hide();
}

void MainWindow::on_actionMultiplayer_triggered()
{
    cout << "-Multiplayer Mode-" << endl;
    dificulty_hide();
    ui->labelName->hide();
}

void MainWindow::on_actionSingleplayer_triggered()
{
    cout << "-Singleplayer Mode-" << endl;
    dificulty_hide();
    ui->labelName->hide();
}

void MainWindow::on_actionConfiguration_triggered()
{
    cout << "-Configuration Triggered-" << endl;
    ui->labelName->hide();
    dificulty_show();
}

void MainWindow::on_radioBegginer_clicked()
{
    dif = 1;
    cout << "Begginer Selected" << endl;
}

void MainWindow::on_radioIntermediate_clicked()
{
    dif = 2;
    cout << "Intermediate Selected" << endl;
}

void MainWindow::on_radioExpert_clicked()
{
    dif = 3;
    cout << "Expert Selected" << endl;
}
