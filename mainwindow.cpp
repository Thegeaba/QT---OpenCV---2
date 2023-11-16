#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProcess>
#include <QString>

#include <iostream>
using namespace std;

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

void MainWindow::on_oglindire_clicked()
{
    background = cv::imread("C:/Users/Cristi/Desktop/OpenCV   C++/imagini/oameni.jpg");
    bula = cv::imread("C:/Users/Cristi/Desktop/OpenCV   C++/imagini/text.png");
    cv::flip(bula, bula, 1); // Oglindire
    cv::imwrite("C:/Users/Cristi/Desktop/OpenCV   C++/imagini/text.png", bula);

    cv::resize(background, background, cv::Size(backgroundWidth, backgroundHeight));
    cv::resize(bula, bula, cv::Size(bulaWidth, bulaHeight));

    if(k == 0){
        cv::Mat pozaROI = background(Rect(200, 10, bula.cols, bula.rows));
        addWeighted(pozaROI, 1.0, bula, 0.3, 0., pozaROI);
        cv::imwrite("C:/Users/Cristi/Desktop/OpenCV   C++/imagini/ROI/background.jpg", background);
        k++;
    }
    else{
        cv::Mat pozaROI = background(Rect(100, 10, bula.cols, bula.rows));
        addWeighted(pozaROI, 1.0, bula, 0.3, 0., pozaROI);
        cv::imwrite("C:/Users/Cristi/Desktop/OpenCV   C++/imagini/ROI/background.jpg", background);
        k--;
    }

    ui->frame->setStyleSheet("background-image: url(C:/Users/Cristi/Desktop/OpenCV   C++/imagini/ROI/background.jpg);");
}

void MainWindow::on_text_clicked()
{
    background = cv::imread("C:/Users/Cristi/Desktop/OpenCV   C++/imagini/oameni.jpg");
    bula = cv::imread("C:/Users/Cristi/Desktop/OpenCV   C++/imagini/text.png");

    cv::resize(background, background, cv::Size(backgroundWidth, backgroundHeight));
    cv::resize(bula, bula, cv::Size(bulaWidth, bulaHeight));

    QString text = ui->dialog->toPlainText();
    const cv::String textConst = text.toStdString();
    cv::putText(bula, textConst, cv::Point(30, 100), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255, 166, 100), 2);

    // ROI
    if(k == 0){
        cv::Mat pozaROI = background(Rect(100, 10, bula.cols, bula.rows));
        addWeighted(pozaROI, 1.0, bula, 0.3, 0., pozaROI);
        cv::imwrite("C:/Users/Cristi/Desktop/OpenCV   C++/imagini/ROI/background.jpg", background);
    }
    else{
        cv::Mat pozaROI = background(Rect(200, 10, bula.cols, bula.rows));
        addWeighted(pozaROI, 1.0, bula, 0.3, 0., pozaROI);
        cv::imwrite("C:/Users/Cristi/Desktop/OpenCV   C++/imagini/ROI/background.jpg", background);
    }

    ui->frame->setStyleSheet("background-image: url(C:/Users/Cristi/Desktop/OpenCV   C++/imagini/ROI/background.jpg);");
}

// Salvare imagine
void MainWindow::on_salvare_imagine_clicked()
{
    cv::Mat imagine = cv::imread("C:/Users/Cristi/Desktop/OpenCV   C++/imagini/ROI/background.jpg");
    QString directorSalvare = "C:/Users/Cristi/Desktop/OpenCV   C++/imagini/imagini_pentru_animatie/";
    QString numeImagine = QString("%1background_%2.jpg").arg(directorSalvare).arg(secventa, 4, 10, QChar('0'));
    cv::imwrite(numeImagine.toStdString(), imagine);
    secventa += 1;
}

// Animatie
void MainWindow::on_animatie_clicked()
{
    QString sourceFolderPath = "C:/Users/Cristi/Desktop/OpenCV   C++/imagini/imagini_pentru_animatie";
    QString outputFolderPath = "C:/Users/Cristi/Desktop/OpenCV   C++/imagini/animatie";

    cv::VideoWriter video(outputFolderPath.toStdString() + "/animatie.avi", cv::VideoWriter::fourcc('X', 'V', 'I', 'D'), 1, cv::Size(640, 480));

    QDir sourceDir = sourceFolderPath;
    QStringList filters;
    filters << "*.jpg";
    sourceDir.setNameFilters(filters);
    QStringList imageFiles = sourceDir.entryList(QDir::Files);
    foreach (const QString &fileName, imageFiles) {
        cv::Mat image = cv::imread((sourceFolderPath + "/" + fileName).toStdString());
        video.write(image);
    }
    video.release();
}


void MainWindow::on_setFrame_clicked()
{
    background = cv::imread("C:/Users/Cristi/Desktop/OpenCV   C++/imagini/oameni.jpg");
    cv::resize(background, background, cv::Size(backgroundWidth, backgroundHeight));
    cv::imwrite("C:/Users/Cristi/Desktop/OpenCV   C++/imagini/ROI/background.jpg", background);

    ui->frame->setStyleSheet("background-image: url(C:/Users/Cristi/Desktop/OpenCV   C++/imagini/ROI/background.jpg);");
}

