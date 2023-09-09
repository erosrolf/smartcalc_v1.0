#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(math_operations()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers()
{
    QPushButton *button = (QPushButton *)sender();
    QString disp_value;
    double all_numbers;

    all_numbers = (ui->display->text() + button->text()).toDouble();
    disp_value = QString::number(all_numbers, 'g', 15);
    ui->display->setText(disp_value);
}

void MainWindow::operations()
{
    QPushButton *button = (QPushButton *)sender();
    QString disp_value;
    double all_numbers;

    if(button->text() == "+/-") {
        all_numbers = (ui->display->text()).toDouble();
        all_numbers = all_numbers * -1.0;
        disp_value = QString::number(all_numbers, 'g', 15);
        ui->display->setText(disp_value);
    }
}

void MainWindow::on_pushButton_dot_clicked()
{
    if(!ui->display->text().contains('.'))
        ui->display->setText(ui->display->text() + ".");
}

void MainWindow::math_operations()
{

}

void MainWindow::on_pushButton_C_clicked()
{

}


void MainWindow::on_pushButton_eq_clicked()
{

}

