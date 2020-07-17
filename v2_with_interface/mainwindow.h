#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void dificulty_show();
    void dificulty_hide();
    void game_begginer_hide();
    void game_begginer_show();
    void multiplayer_config_show();
    void multiplayer_config_hide();

private slots:
    void on_actionMultiplayer_triggered();

    void on_actionSingleplayer_triggered();

    void on_actionConfiguration_triggered();

    void on_radioIntermediate_clicked();

    void on_radioBegginer_clicked();

    void on_radioExpert_clicked();

    void on_radioCreate_clicked();

    void on_radioConnect_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
