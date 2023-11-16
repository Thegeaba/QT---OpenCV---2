#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QFileDialog>
#include <QMainWindow>
#include <QtGui>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

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
    void on_oglindire_clicked();

    void on_text_clicked();

    void on_salvare_imagine_clicked();

    void on_animatie_clicked();

    void on_setFrame_clicked();

private:
    Ui::MainWindow *ui;

    int k = 0;
    int secventa = 1;

    int backgroundWidth = 600;
    int backgroundHeight = 600;
    int bulaWidth = 300;
    int bulaHeight = 200;

    Mat background;
    Mat bula;


};
#endif // MAINWINDOW_H
