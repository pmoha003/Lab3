#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

QImage brightness (QImage &image , int factor);
QImage contrast (QImage &image, int factor);

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

//FUNCTION TO ADJUST IMAGE BRIGHTNESS PIXEL BY PIXEL
QImage brightness (QImage &image , int factor)
{
    double red, green, blue;
          int pixel;
          unsigned int *data;

          pixel = image.width() * image.height();
          data = (unsigned int *)image.bits();
          for (int i = 0; i < pixel; ++i)
          {
              red =  qRed(data[i]) + factor;
              red = (red < 0x00) ? 0x00 : (red > 0xff) ? 0xff : red;

              green =  qGreen(data[i]) + factor;
              green = (green < 0x00) ? 0x00 : (green > 0xff) ? 0xff : green;

              blue =  qBlue(data[i]) + factor;
              blue = (blue < 0x00) ? 0x00 : (blue > 0xff) ? 0xff : blue;
              data[i]= qRgba(red,green,blue,qAlpha(data[i]));
          }
          return image; //RETURN IMAGE EDITED TO MATCH THE INPUT BRIGHTNESS LEVEL

}

//FUNCTION TO ADJUST IMAGE CONTRAST PIXEL BY PIXEL
QImage contrast (QImage &image , int factor)
{
    double contrast = (100.0+factor)/100.0;
        float red, green, blue;
        int pixel = image.width()*image.height();
        unsigned int *data = (unsigned int *)image.bits();

        for (int i = 0; i < pixel; i++)
        {
            red= 128 + contrast*(qRed(data[i])-128);
            red = (red < 0x00) ? 0x00 : (red > 0xff) ? 0xff : red;

            green= 128 + contrast*(qGreen(data[i])-128);
            green = (green < 0x00) ? 0x00 : (green > 0xff) ? 0xff : green;

            blue= 128 + contrast*(qBlue(data[i])-128);
            blue =  (blue  < 0x00) ? 0x00 : (blue  > 0xff) ? 0xff : blue ;

            data[i] = qRgba(red, green, blue, qAlpha(data[i]));
        }
        return image;  //RETURN IMAGE EDITED TO MATCH THE INPUT CONTRAST LEVEL

}

//BUTTON TO LOAD AND DISPLAY ORIGINAL IMAGE
void MainWindow::on_btn_choose_image_clicked()
{
    const QString &filename = QFileDialog ::getOpenFileName (this,tr ("Upload original image:"),"",(tr("Images(*.bmp)"))); //open the file
    image1.load(filename);
    if (!image1.isNull()) {
        image1= image1.scaled(ui->lbl_original_image->width(), ui->lbl_original_image->height()); //scaling image to the Original Image box
        ui->lbl_original_image->setPixmap(QPixmap::fromImage(image1)); //Display the original image in the Original Image box
        image1=image1.scaled (ui->lbl_modified_image->width(), ui->lbl_modified_image->height());//scaling image to the Enhanced Image box
        ui->lbl_modified_image->setPixmap(QPixmap::fromImage (image1));//Display the original image in the Enhanced Image box
}

}
//Changing brightness with Brightness slider
void MainWindow::on_adjust_brightness_valueChanged(int value)
{
    QPixmap imagePixmap;
    image1 = ui->lbl_original_image -> pixmap()->toImage(); //Get current Enhanced Image
    image1 = brightness(image1,value); //Call brightness function with current Ehanced Image and new brightness value from slider
    imagePixmap = QPixmap::fromImage(image1);
    ui->lbl_modified_image->setPixmap(imagePixmap);//Display Ehnahced Image with new brightness level
    //cout << "brightness value = " << value << endl;
    int d0, d1;
    d0 = value % 10;
    d1 = (value / 10) % 10;
    QBA.resize(4);
    QBA.fill('7');
QBA[0]= ('9');
QBA[1]= ('2');

    switch (d1) {
        case 0: QBA[0] = ('0'); break;
        case 1: QBA[0] = ('1') ;break;
        case 2: QBA[0] = ('2'); break;
        case 3: QBA[0] = ('3'); break;
        case 4: QBA[0] = ('4'); break;
        case 5: QBA[0] = ('5'); break;
        case 6: QBA[0] = ('6'); break;
        case 7: QBA[0] = ('7'); break;
        case 8: QBA[0] = ('8'); break;
        case 9: QBA[0] = ('9'); break;
    }

    switch (d0) {
        case 0: QBA[1] = ('0'); break;
        case 1: QBA[1] = ('1'); break;
        case 2: QBA[1] = ('2'); break;
        case 3: QBA[1] = ('3'); break;
        case 4: QBA[1] = ('4'); break;
        case 5: QBA[1] = ('5'); break;
        case 6: QBA[1] = ('6'); break;
        case 7: QBA[1] = ('7'); break;
        case 8: QBA[1] = ('8'); break;
        case 9: QBA[1] = ('9'); break;
    }

    QSocket = new QUdpSocket(this);
    QSocket->writeDatagram(QBA,QHostAddress("192.168.1.18"),80);
}

//Changing contrast with Contast slider
void MainWindow::on_adjust_contrast_valueChanged(int value)
{
    QPixmap imagePixmap;
    image1 = ui->lbl_original_image -> pixmap()->toImage(); //Get current Enhanced Image
    image1 = contrast(image1,value); //Call Contrast function with current Ehanced Image and new contrast value from slider
    imagePixmap = QPixmap::fromImage(image1);
    ui->lbl_modified_image->setPixmap(imagePixmap);//Display Ehnahced Image with new contrast level
   // cout << "contrast value = " << value << endl;
    int d0, d1;
    d0 = value % 10;
    d1 = (value / 10) % 10;
QBA.resize(4);
    switch (d1) {
        case 0: QBA[2] = ('0');  break;
        case 1: QBA[2] = ('1');  break;
        case 2: QBA[2] = ('2'); break;
        case 3: QBA[2] = ('3'); break;
        case 4: QBA[2] = ('4'); break;
        case 5: QBA[2] = ('5'); break;
        case 6: QBA[2] = ('6'); break;
        case 7: QBA[2] = ('7'); break;
        case 8: QBA[2] = ('8'); break;
        case 9: QBA[2] = ('9'); break;
    }

    switch (d0) {
        case 0: QBA[3] = ('0');  break;
        case 1: QBA[3] = ('1'); break;
        case 2: QBA[3] = ('2'); break;
        case 3: QBA[3] = ('3'); break;
        case 4: QBA[3] = ('4'); break;
        case 5: QBA[3] = ('5'); break;
        case 6: QBA[3] = ('6'); break;
        case 7: QBA[3] = ('7'); break;
        case 8: QBA[3] = ('8'); break;
        case 9: QBA[3] = ('9'); break;
    }

    QSocket = new QUdpSocket(this);
    QSocket->writeDatagram(QBA,QHostAddress("192.168.1.18"),80);
}

//Changing brightness with Brightness slider
/*void MainWindow::on_adjust_brightness_valueChanged(int value)
{
    QPixmap imagePixmap;
    image1 = ui->lbl_original_image -> pixmap()->toImage(); //Get current Enhanced Image
    image1 = brightness(image1,value); //Call brightness function with current Ehanced Image and new brightness value from slider
    imagePixmap = QPixmap::fromImage(image1);
    ui->lbl_modified_image->setPixmap(imagePixmap);//Display Ehnahced Image with new brightness level
    std::cout << "brightness value = " << value;
//updatedisplay();
}
*/
//Changing contrast with Contast slider
/*void MainWindow::on_adjust_contrast_valueChanged(int value)
{
    QPixmap imagePixmap;
    image1 = ui->lbl_original_image -> pixmap()->toImage(); //Get current Enhanced Image
    image1 = contrast(image1,value); //Call Contrast function with current Ehanced Image and new contrast value from slider
    imagePixmap = QPixmap::fromImage(image1);
    ui->lbl_modified_image->setPixmap(imagePixmap);//Display Ehnahced Image with new contrast level
    updatedisplay();
}
*/
//BUTTON TO EHNACED IMAGE
void MainWindow::on_savebutton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Image File"), " ", tr("Image(*.bmp)"));
        if (!filename.isEmpty())
        {
            ui->lbl_modified_image->grab().save(filename);

        }
        else
        {

}
}

void MainWindow::updatedisplay() {
    QBA.resize(4);
    QBA.fill('7');
    QBA[0] = ('1');
    QBA[1] = ('9');
    QSocket = new QUdpSocket(this);
    QSocket->writeDatagram(QBA,QHostAddress("192.168.1.18"),80);


}
