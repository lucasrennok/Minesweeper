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

private slots:
    void on_actionMultiplayer_triggered();

    void on_actionSingleplayer_triggered();

    void on_actionConfiguration_triggered();

    void on_radioIntermediate_clicked();

    void on_radioBegginer_clicked();

    void on_radioExpert_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
