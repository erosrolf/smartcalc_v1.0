#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>

extern "C" {
#include "../backend/calculate.h"
int calc_expression(char *str, double *res, double x);
}

namespace Ui {
class Graph;
}

class Graph : public QWidget {
  Q_OBJECT

public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();

private:
  Ui::Graph *ui;
  double xBegin, xEnd, dotStep, tmpX;
  int dotCount;

  QVector<double> x, y;
};

#endif // GRAPH_H
