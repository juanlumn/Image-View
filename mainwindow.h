#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionLoad_Image_triggered();

    void on_verticalSlider_valueChanged(int value);

    void on_pushButton_clicked();

    void on_actionImage_Properties_triggered();

    void on_pushButton_2_clicked();

    void on_actionExit_triggered();

    void on_pushButton_3_clicked();

    void on_actionSave_File_As_triggered();

private:
    Ui::MainWindow *ui;
    QImage Img;
    QMdiSubWindow *subwin;
    QString name;
    void LoadImage (void);
    void SaveImage (void);
    bool run;
};

#endif // MAINWINDOW_H
