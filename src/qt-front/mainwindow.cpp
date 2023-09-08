#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_1,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_2,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_3,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_4,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_5,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_6,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_7,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_8,SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_9,SIGNAL(clicked()), this,SLOT(digits_numbers()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::digits_numbers()
{
    QPushButton *button = (QPushButton *)sender();
    double all_numbers;
    QString input_calc;

    all_numbers = (ui->result_show->text() + button->text()).toDouble();
    input_calc = QString::number(all_numbers, 'g', 10);
    ui->result_show->setText(input_calc);
}

