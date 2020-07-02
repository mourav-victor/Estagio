#include <QApplication>
#include <iostream>
#include <cmath>

#include "testmicroimagesimulator.h"
#include <QDebug>
#include <QElapsedTimer>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QElapsedTimer timer;

    //QVector<float> line = {1, 2, 3};
    //QVector<QVector<float>> kernel = {line, line, line};
    //qDebug() << "Kernel Size" << kernel.size();

    QImage img("/Users/moura/Documents/Victor Moura/estágio/beach.jpg");
    QLabel display;
    display.setPixmap(QPixmap::fromImage(img));
    display.show();

    TestMicroImageSimulator MyImage;
    MyImage.setImage(img);
    QLabel display2;
    display2.setPixmap(QPixmap::fromImage(MyImage.image));
    display2.show();

//    timer.start();
//    MyImage.output = TestMicroImageSimulator::spatialConvolution2D(MyImage.image);
//    qDebug() << "Time 2dConvBioax filter: " << timer.elapsed(); //timer1.nsecsElapsed();
//    QLabel display3;
//    display3.setPixmap(QPixmap::fromImage(MyImage.output));
//    display3.show();
//    qDebug() << "Largura: " << MyImage.output.width();
//    qDebug() << "Altura: " << MyImage.output.height();

    timer.start();
    MyImage.filterSL(MyImage.image2);
    qDebug() << "Time 2dConvMine2 filter: " << timer.elapsed(); //timer1.nsecsElapsed();
    QLabel display3;
    display3.setPixmap(QPixmap::fromImage(MyImage.image2));
    display3.show();
    qDebug() << "Largura: " << MyImage.image2.width();
    qDebug() << "Altura: " << MyImage.image2.height();

    QVector<float> kernel_blur = {0.111, 0.111, 0.111, 0.111, 0.111, 0.111, 0.111, 0.111, 0.111};
    timer.restart();
    MyImage.filter(MyImage.image, kernel_blur);
    qDebug() << "Time 2dConvMine filter: " << timer.elapsed(); //timer1.nsecsElapsed();
    QLabel display4;
    display4.setPixmap(QPixmap::fromImage(MyImage.image));
    display4.show();
    qDebug() << "Largura: " << MyImage.image.width();
    qDebug() << "Altura: " << MyImage.image.height();

    return app.exec();
}
