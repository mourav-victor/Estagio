#ifndef TESTMICROIMAGESIMULATOR_H
#define TESTMICROIMAGESIMULATOR_H

#include <QObject>
#include <QImage>
#include <QFrame>
#include <QPainter>
#include <QtWidgets>
#include <QtMath>

class TestMicroImageSimulator
{
public:
    TestMicroImageSimulator();
    //QImage spatialConvolution2D(const QImage & image, const kernelMatrix &kernel);
    QImage spatialConvolution2D(const QImage & image, const QVector<float> &kernel);
    static QImage spatialConvolution2D(const QImage &image);    
    void setImage(const QImage &image);


    //testes
    void filter(QImage &img_Reference, const QVector<float> &kernel);
    void filterSL(QImage &img_Reference);




public:
    QImage image;
    QImage image2;
    QImage output;

};

#endif // TESTMICROIMAGESIMULATOR_H
