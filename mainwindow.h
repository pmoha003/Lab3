#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QtCore>
#include <QPainter>
#include <QtGui>
#include <QByteArray>
#include <QUdpSocket>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QUdpSocket *QSocket;
    QByteArray QBA;

private slots:
    void on_btn_choose_image_clicked();

    void on_adjust_brightness_valueChanged(int value);

    void on_adjust_contrast_valueChanged(int value);

    void on_savebutton_clicked();

    void updatedisplay();
private:
    Ui::MainWindow *ui;
    QImage image1;
    //QImage image2;
};
#endif // MAINWINDOW_H
