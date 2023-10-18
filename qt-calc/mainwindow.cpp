#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_br_open, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_br_close, SIGNAL(clicked()), this, SLOT(button()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::button() {
  QPushButton *button = (QPushButton *)sender();
  QString disp_value;

  disp_value = (ui->display->text() + button->text());
  ui->display->setText(disp_value);
}

void MainWindow::on_pushButton_dot_clicked() {
  if (!ui->display->text().contains('.'))
    ui->display->setText(ui->display->text() + ".");
}

void MainWindow::on_pushButton_C_clicked() {
  ui->display->setText("\0");
}
