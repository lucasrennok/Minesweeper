#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "minesweeper.h"
#include <stdbool.h>
#include <iostream>

using namespace std;

int dif = 1;
bool bool_connect=false, bool_create=false;
QString ip_connect = "";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dificulty_hide();
    multiplayer_config_hide();
    game_begginer_hide();
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

void MainWindow::multiplayer_config_hide(){
    ui->labelMultiplayer->hide();
    ui->radioCreate->hide();
    ui->radioConnect->hide();
    ui->textIP->hide();
}

void MainWindow::multiplayer_config_show(){
    ui->labelMultiplayer->show();
    ui->radioCreate->show();
    ui->radioConnect->show();
    ui->textIP->show();
}

void MainWindow::game_begginer_hide(){
    ui->labelGame->hide();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();
    ui->pushButton_6->hide();
    ui->pushButton_7->hide();
    ui->pushButton_8->hide();
    ui->pushButton_9->hide();
    ui->pushButton_10->hide();
    ui->pushButton_11->hide();
    ui->pushButton_12->hide();
    ui->pushButton_13->hide();
    ui->pushButton_14->hide();
    ui->pushButton_15->hide();
    ui->pushButton_16->hide();
    ui->pushButton_17->hide();
    ui->pushButton_18->hide();
    ui->pushButton_19->hide();
    ui->pushButton_20->hide();
    ui->pushButton_21->hide();
    ui->pushButton_22->hide();
    ui->pushButton_23->hide();
    ui->pushButton_24->hide();
    ui->pushButton_25->hide();
    ui->pushButton_26->hide();
    ui->pushButton_27->hide();
    ui->pushButton_28->hide();
    ui->pushButton_29->hide();
    ui->pushButton_30->hide();
    ui->pushButton_31->hide();
    ui->pushButton_32->hide();
    ui->pushButton_33->hide();
    ui->pushButton_34->hide();
    ui->pushButton_35->hide();
    ui->pushButton_36->hide();
    ui->pushButton_37->hide();
    ui->pushButton_38->hide();
    ui->pushButton_39->hide();
    ui->pushButton_40->hide();
    ui->pushButton_41->hide();
    ui->pushButton_42->hide();
    ui->pushButton_43->hide();
    ui->pushButton_44->hide();
    ui->pushButton_45->hide();
    ui->pushButton_46->hide();
    ui->pushButton_47->hide();
    ui->pushButton_48->hide();
    ui->pushButton_49->hide();
    ui->pushButton_50->hide();
    ui->pushButton_51->hide();
    ui->pushButton_52->hide();
    ui->pushButton_53->hide();
    ui->pushButton_54->hide();
    ui->pushButton_55->hide();
    ui->pushButton_56->hide();
    ui->pushButton_57->hide();
    ui->pushButton_58->hide();
    ui->pushButton_59->hide();
    ui->pushButton_60->hide();
    ui->pushButton_61->hide();
    ui->pushButton_62->hide();
    ui->pushButton_63->hide();
    ui->pushButton_64->hide();
}

void MainWindow::game_begginer_show(){
    ui->labelGame->show();
    ui->pushButton->show();
    ui->pushButton_2->show();
    ui->pushButton_3->show();
    ui->pushButton_4->show();
    ui->pushButton_5->show();
    ui->pushButton_6->show();
    ui->pushButton_7->show();
    ui->pushButton_8->show();
    ui->pushButton_9->show();
    ui->pushButton_10->show();
    ui->pushButton_11->show();
    ui->pushButton_12->show();
    ui->pushButton_13->show();
    ui->pushButton_14->show();
    ui->pushButton_15->show();
    ui->pushButton_16->show();
    ui->pushButton_17->show();
    ui->pushButton_18->show();
    ui->pushButton_19->show();
    ui->pushButton_20->show();
    ui->pushButton_21->show();
    ui->pushButton_22->show();
    ui->pushButton_23->show();
    ui->pushButton_24->show();
    ui->pushButton_25->show();
    ui->pushButton_26->show();
    ui->pushButton_27->show();
    ui->pushButton_28->show();
    ui->pushButton_29->show();
    ui->pushButton_30->show();
    ui->pushButton_31->show();
    ui->pushButton_32->show();
    ui->pushButton_33->show();
    ui->pushButton_34->show();
    ui->pushButton_35->show();
    ui->pushButton_36->show();
    ui->pushButton_37->show();
    ui->pushButton_38->show();
    ui->pushButton_39->show();
    ui->pushButton_40->show();
    ui->pushButton_41->show();
    ui->pushButton_42->show();
    ui->pushButton_43->show();
    ui->pushButton_44->show();
    ui->pushButton_45->show();
    ui->pushButton_46->show();
    ui->pushButton_47->show();
    ui->pushButton_48->show();
    ui->pushButton_49->show();
    ui->pushButton_50->show();
    ui->pushButton_51->show();
    ui->pushButton_52->show();
    ui->pushButton_53->show();
    ui->pushButton_54->show();
    ui->pushButton_55->show();
    ui->pushButton_56->show();
    ui->pushButton_57->show();
    ui->pushButton_58->show();
    ui->pushButton_59->show();
    ui->pushButton_60->show();
    ui->pushButton_61->show();
    ui->pushButton_62->show();
    ui->pushButton_63->show();
    ui->pushButton_64->show();
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

    cout << "-Multiplayer Mode-" << endl;
    dificulty_hide();
    multiplayer_config_hide();
    ui->labelName->hide();
}

void MainWindow::on_actionSingleplayer_triggered()
{
    if(dif==1)
        game_begginer_show();
    cout << "-Singleplayer Mode-" << endl;
    dificulty_hide();
    multiplayer_config_hide();
    ui->labelName->hide();
}

void MainWindow::on_actionConfiguration_triggered()
{
    game_begginer_hide();
    cout << "-Configuration Triggered-" << endl;
    ui->labelName->hide();
    dificulty_show();
    multiplayer_config_show();
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
