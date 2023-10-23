#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->widget_2->setBackground(QColor(232,228,216,150));
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
  connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_br_open, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_br_close, SIGNAL(clicked()), this, SLOT(button()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(button_func()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(button_func()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(button_func()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(button_func()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(button_func()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(button_func()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(button_func()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(button_func()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(button_func()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::button() {
  QPushButton *button = (QPushButton *)sender();
  QString disp_value;

  disp_value = (ui->display->text() + button->text());
  ui->display->setText(disp_value);
}

void MainWindow::button_func() {
  QPushButton *button = (QPushButton *)sender();
  QString disp_value;

  disp_value = (ui->display->text() + button->text() + "(");
  ui->display->setText(disp_value);
}

void MainWindow::on_pushButton_C_clicked() { ui->display->setText("\0"); }

void MainWindow::on_pushButton_eq_clicked() {
  double x = ui->x_inpt->value();
  QString str = ui->display->text();
  QByteArray arr = str.toLocal8Bit();
  char *inpt = arr.data();
  double res = 0;
  int ret = calc_expression(inpt, &res, x);
  QString result = QString::number(res, 'g', 20);
  if (ret == 0)
    ui->display->setText(result);
  else
    ui->display->setText("err");
}

void MainWindow::on_pushButton_graph_clicked()
{
    ui->widget_2->addGraph();
    ui->widget_2->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->widget_2->xAxis->setLabel("x");
    ui->widget_2->yAxis->setLabel("-<");

    ui->widget_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

  QString str = ui->display->text();
  QByteArray arr = str.toLocal8Bit();
  char *inpt = arr.data();

    double xVal[21] = {-10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double yVal[21];
    for (int i = 0; i < 21; i++){
      calc_expression(inpt, &yVal[i], xVal[i]);
    }
    QVector<double> x(std::begin(xVal), std::end(xVal));
    QVector<double> y(std::begin(yVal), std::end(yVal));

    ui->widget_2->graph(0)->setData(x, y);
    ui->widget_2->rescaleAxes();
    ui->widget_2->replot();
    ui->widget_2->update();
}
