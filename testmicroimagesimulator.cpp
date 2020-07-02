#include "testmicroimagesimulator.h"

TestMicroImageSimulator::TestMicroImageSimulator()
{

}

void TestMicroImageSimulator::setImage(const QImage &img){
    image = img;
    image2 = img;
}

QImage TestMicroImageSimulator::spatialConvolution2D(const QImage &image, const QVector<float> &kernel) {
   const auto _cropSize = qSqrt(kernel.size());
   const auto _halfCropSize = int((_cropSize - 1) / 2);
   const auto _blackMarginSize = int(_cropSize - 1);

   // ------------------------------------------------------------
   // create a output image that will hold the convoluted result
   // ------------------------------------------------------------
   //const QImage _inputImageGrayed = image;
   const QImage _inputImageGrayed = image.convertToFormat(QImage::Format_RGB32);

   QImage _inputImageGrayedAndExtended(_inputImageGrayed.width() + _blackMarginSize, _inputImageGrayed.height() + _blackMarginSize, QImage::Format::Format_RGB32);
   _inputImageGrayedAndExtended.fill(Qt::black);

   QPainter __painter( & _inputImageGrayedAndExtended);
   const QPoint __destPos(_halfCropSize, _halfCropSize);
   __painter.drawImage(__destPos, _inputImageGrayed);
   __painter.end();

   QImage _outputImage = _inputImageGrayedAndExtended;
   const auto _step = (4 * sizeof(uchar) * _inputImageGrayedAndExtended.width());

   for (int row = _halfCropSize; row < _inputImageGrayedAndExtended.height() - _halfCropSize; row++) {
      const uchar * scan = _inputImageGrayedAndExtended.scanLine(row);

      for (int column = _halfCropSize; column < _inputImageGrayedAndExtended.width() - _halfCropSize; column++) {
         int _red = 0;
         int _grn = 0;
         int _blu = 0;
         int i = 0;
         int j = 0;
         // -----------------------------------------
         // accumulate result from convoluted kernel
         // -----------------------------------------

         QVector<float> line = {0.111, 0.111, 0.111};
         QVector<QVector<float>> kernel = {line, line, line};

         for (const auto & _rowElement: kernel) {
            for (const auto & _colElementData: _rowElement) {
               if (auto * curPixel = reinterpret_cast < QRgb * > ((void * )(scan + (i - _halfCropSize) * _step + (column + j - _halfCropSize) * 4))) {
                  _red += _colElementData * qRed( * curPixel);
                  _grn += _colElementData * qGreen( * curPixel);
                  _blu += _colElementData * qBlue( * curPixel);
               }
               j++;
            }

            i++;
         }

         _red = (_red < 0 ? 0 : (_red > 255 ? 255 : _red));
         _grn = (_grn < 0 ? 0 : (_grn > 255 ? 255 : _grn));
         _blu = (_blu < 0 ? 0 : (_blu > 255 ? 255 : _blu));

         _outputImage.setPixel(
            column + 10 * _halfCropSize,
            row,
            QColor(_red, _grn, _blu).rgb()
         );
      }
   }

   return _outputImage;
}

QImage TestMicroImageSimulator::spatialConvolution2D(const QImage &image) {
   QVector<float> line = {0.111, 0.111, 0.111};
   QVector<QVector<float>> kernel = {line, line, line};
   const auto _cropSize = kernel.size();
   const auto _halfCropSize = int((_cropSize - 1) / 2);
   const auto _blackMarginSize = int(_cropSize - 1);

   // ------------------------------------------------------------
   // create a output image that will hold the convoluted result
   // ------------------------------------------------------------
   //const QImage _inputImageGrayed = image;
   const QImage _inputImageGrayed = image.convertToFormat(QImage::Format_RGB32);

   QImage _inputImageGrayedAndExtended(_inputImageGrayed.width() + _blackMarginSize, _inputImageGrayed.height() + _blackMarginSize, QImage::Format::Format_RGB32);
   _inputImageGrayedAndExtended.fill(Qt::black);

   QPainter __painter( & _inputImageGrayedAndExtended);
   const QPoint __destPos(_halfCropSize, _halfCropSize);
   __painter.drawImage(__destPos, _inputImageGrayed);
   __painter.end();

   //QImage _outputImage = image;
   QImage _outputImage = _inputImageGrayedAndExtended;
   const auto _step = (4 * sizeof(uchar) * _inputImageGrayedAndExtended.width());

   for (int row = _halfCropSize; row < _inputImageGrayedAndExtended.height() - _halfCropSize; row++) {
      const uchar * scan = _inputImageGrayedAndExtended.scanLine(row);

      for (int column = _halfCropSize; column < _inputImageGrayedAndExtended.width() - _halfCropSize; column++) {
         int _red = 0;
         int _grn = 0;
         int _blu = 0;
         int i = 0;
         int j = 0;
         // -----------------------------------------
         // accumulate result from convoluted kernel
         // -----------------------------------------
         for (const auto & _rowElement: kernel) {
            for (const auto & _colElementData: _rowElement) {
               if (auto * curPixel = reinterpret_cast < QRgb * > ((void * )(scan + (i - _halfCropSize) * _step + (column + j - _halfCropSize) * 4))) {
                  _red += _colElementData * qRed( * curPixel);
                  _grn += _colElementData * qGreen( * curPixel);
                  _blu += _colElementData * qBlue( * curPixel);
               }
               j++;
            }

            i++;
         }

         _red = (_red < 0 ? 0 : (_red > 255 ? 255 : _red));
         _grn = (_grn < 0 ? 0 : (_grn > 255 ? 255 : _grn));
         _blu = (_blu < 0 ? 0 : (_blu > 255 ? 255 : _blu));

         _outputImage.setPixel(column + 10 * _halfCropSize, row, QColor(_red, _grn, _blu).rgb());
         //_outputImage.setPixel(column + 10 * _halfCropSize, row, QColor(_red, _grn, _blu).rgb());
         //_outputImage.setPixel((column-_halfCropSize), row-_halfCropSize, QColor(_red, _grn, _blu).rgb());

      }
   }

   return _outputImage;
}

void TestMicroImageSimulator::filter(QImage &img_Reference, const QVector<float> &kernel){
    int pad_margin = (qSqrt(kernel.size()) - 1)/2;
    // CRIA IMAGEM PRETA COM DIMENSOES ADEQUADAS
    QImage padded_img(img_Reference.width() + 2*pad_margin, img_Reference.height() + 2*pad_margin, QImage::Format::Format_RGB32);

    // DESENHA A IMAGEM DEIXANDO AS BORDAS OK
    QPainter painter(&padded_img);
    const QPoint position(pad_margin, pad_margin);
    painter.drawImage(position, img_Reference);
    painter.end();

    // APLICA O FILTRO
    //QImage blur_image = imagem;
    for (int j = pad_margin; j < padded_img.height() - pad_margin; j++) {
        for (int i = pad_margin; i < padded_img.width() - pad_margin; i++) {
            float red = 0; float blue = 0; float green = 0;
            int count = 0;

            for (int k=-pad_margin; k<=pad_margin; k++){
                for(int l=-pad_margin; l<=pad_margin; l++){
                    red = red + padded_img.pixelColor(i+k,j+l).red() * kernel[count];
                    green = green + padded_img.pixelColor(i+k,j+l).green() * kernel[count];
                    blue = blue + padded_img.pixelColor(i+k,j+l).blue() * kernel[count];
                    count++;
                }
            }

            red = (red < 0 ? 0 : (red > 255 ? 255 : red));
            green = (green < 0 ? 0 : (green > 255 ? 255 : green));
            blue = (blue < 0 ? 0 : (blue > 255 ? 255 : blue));

            QColor pix((int)red, (int)green, (int)blue);
            img_Reference.setPixelColor(i-pad_margin,j-pad_margin,pix);

        }
    }
}

void TestMicroImageSimulator::filterSL(QImage &img_Reference){

    // Define Kernel Parameters
    const QVector<float> kernel = {0.111, 0.111, 0.111,
                                   0.111, 0.111, 0.111,
                                   0.111, 0.111, 0.111};
    int kernel_size = qSqrt(kernel.size());
    qDebug() << "Kernel Dim: " << kernel_size;
    int pad_margin = (kernel_size - 1)/2;
    qDebug() << "Pad Dim: " << pad_margin;

    // BLACK IMAGE CREATION WITH EXTENDED DIMENSIONS
    QImage padded_img(img_Reference.width() + 2*pad_margin, img_Reference.height() + 2*pad_margin, QImage::Format::Format_RGB32);

    // PADDED IMAGE CREATION WITH EXTENDED DIMENSIONS
    QPainter painter(&padded_img);
    const QPoint position(pad_margin, pad_margin);
    painter.drawImage(position, img_Reference);
    painter.end();

    // CONVOULUTION PROCESS
    for (int y = 0; y < img_Reference.height(); y++) {
        QRgb *outLine = (QRgb *) img_Reference.scanLine(y);

        for (int x = 0; x < img_Reference.width(); x++) {
            qreal pixelR = 0;
            qreal pixelG = 0;
            qreal pixelB = 0;

            // INSIDE PIXELS, FOR EACH CHANNEL
            for (int j = 0; j < kernel_size; j++) {
                const QRgb *inLine = (QRgb *) padded_img.constScanLine(y + j);

                for (int i = 0; i < kernel_size; i++) {
                    qreal k = kernel[i + j * kernel_size];
                    QRgb pixel = inLine[x + i];

                    pixelR += k * qRed(pixel);
                    pixelG += k * qGreen(pixel);
                    pixelB += k * qBlue(pixel);
                }
            }

            quint8 r = qBound(0., pixelR, 255.);
            quint8 g = qBound(0., pixelG, 255.);
            quint8 b = qBound(0., pixelB, 255.);
            outLine[x] = qRgb(r, g, b);
        }
    }
}

