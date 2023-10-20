#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

extern "C" {
#include "../backend/calculate.h"
int calc_expression(char *str, double *res);
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;

private slots:
  void button();
  void button_func();
  void on_pushButton_C_clicked();
  void on_pushButton_eq_clicked();
};
#endif // MAINWINDOW_H