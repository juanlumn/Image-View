#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QMovie>
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    run=false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Function to get the File Name
QString ImageName(QString file){
    QString Iname;
    int counter=0;
    bool flag=false;
    //Get the last '/'
    for (int i=file.count();i>0;i--){
        if (file[i]!='/'&&flag==false)counter++;
        else flag=true;
    }
    //Read the name from the last '/'
    for (int i=1;i<counter;i++){
        Iname[i]=file[file.count()-counter+i];
    }
    return (Iname);
}

//Function to Load the Image
void MainWindow::LoadImage(void){
    if (run)subwin->close();
    //Dialog to choose the file to Load between PNG,TIFF,JPEG,JPG,BMP or animated GIF
    QString file = QFileDialog::getOpenFileName(NULL,"Load File", NULL,"*.png;;*.tiff;;*.jpeg;;*.jpg;;*.bmp;;*.gif");
    if(!file.isEmpty()){
        run=true;
        //Gets the file name
        name=ImageName(file);
        //Gets the extension
        QString ext;
        for (int i=name.count()-3;i<name.count();i++){
            ext.append(name[i]);
        }
        //Loads the image
        Img.load(file);
        ui->label->setFixedSize(Img.width(),Img.height());
        //If is not a GIF
        if (ext!="gif"&&ext!="GIF"){
            ui->label->setPixmap(QPixmap::fromImage(Img));
            //Enables the zoom slider. the Image properties and the Selection button
            ui->verticalSlider->setEnabled(true);
            ui->actionImage_Properties->setEnabled(true);
            ui->pushButton_2->setEnabled(true);
        }
        //If GIF
        else{
            QMovie *AnimGif = new QMovie(file);
            ui->label->setMovie(AnimGif);
            AnimGif->start();

            //Disables the zoom slider. the Image properties and the Selection button
            ui->verticalSlider->setEnabled(false);
            ui->actionImage_Properties->setEnabled(false);
            ui->pushButton_2->setEnabled(false);
        }
        //Display the Image
        subwin=ui->mdiArea->addSubWindow(ui->label,Qt::WindowTitleHint);
        subwin->setWindowTitle(name);
        subwin->showMaximized();
        subwin->setFixedSize(ui->label->size());
        ui->label->show();

        //Enables the option Save the File
        ui->pushButton_3->setEnabled(true);
        ui->actionSave_File_As->setEnabled(true);

        QString s;
        ui->verticalSlider->setValue(100);
        s.sprintf("1.00");
        ui->label_2->setText(s);
    }
}

void MainWindow::on_actionLoad_Image_triggered()
{
    LoadImage();
}

void MainWindow::on_pushButton_clicked()
{
    LoadImage();
}

//If the zoom slider changes it's value
void MainWindow::on_verticalSlider_valueChanged(int value)
{
    if (!Img.isNull()){
        //Gets the zoom slider value and computes the scale
        float scale=value/100.0;
        QString s;
        s.sprintf("%2.2f",scale);
        ui->label_2->setText(s);

        //Scales the New Image and displays it in the subwin
        QImage NewImg=Img.scaled(Img.width()*scale,Img.height()*scale);

        ui->label->setPixmap(QPixmap::fromImage(NewImg));
        ui->label->setFixedSize(NewImg.width(),NewImg.height());
        subwin->setFixedSize(ui->label->size());
    }
}

//Displays some Image Properties
void MainWindow::on_actionImage_Properties_triggered()
{
    QString prop;
    prop.append("Name: ");prop.append(name);prop.append("\n\n");
    prop.append("Width: ");prop.append(QString("%1 pixels").arg(Img.width()));prop.append("\n");
    prop.append("Height: ");prop.append(QString("%1 pixels").arg(Img.height()));prop.append("\n\n");
    prop.append("Image Size: ");prop.append(QString("%1 pixels").arg(Img.height()*Img.width()));prop.append("\n");
    QMessageBox::information(this, ("File Properties"),tr("%1").arg(prop));
}

//Copy to clipboard the Image
void MainWindow::on_pushButton_2_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setPixmap(QPixmap::grabWidget(ui->label));
}

//Exit
void MainWindow::on_actionExit_triggered()
{
    qApp->exit();
}
//Function to Save the Image
void MainWindow::SaveImage(void){
    QString file = QFileDialog::getSaveFileName(NULL,"Save Image As",NULL);
    if(file.isEmpty()==false){
        Img.save(file);
        name=ImageName(file);
        subwin->setWindowTitle(name);
    }
}
//Save the Image As...
void MainWindow::on_pushButton_3_clicked()
{
    SaveImage();
}

void MainWindow::on_actionSave_File_As_triggered()
{
    SaveImage();
}
