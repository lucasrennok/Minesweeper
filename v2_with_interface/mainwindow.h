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

private slots:
    void on_actionMultiplayer_triggered();

    void on_actionSingleplayer_triggered();

    void on_actionConfiguration_triggered();

    void on_radioIntermediate_clicked();

    void on_radioBeginner_clicked();

    void on_radioExpert_clicked();

    void on_radioCreate_clicked();

    void on_radioConnect_clicked();

    void on_pushButton_clicked();

    void on_radioUnlock_clicked();

    void on_radioFlag_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
