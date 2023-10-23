#include "graph.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) : QWidget(parent), ui(new Ui::Graph) {
  ui->setupUi(this);

  ui->widget->addGraph();
  ui->widget->graph(0)->setLineStyle(QCPGraph::lsLine);
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("-<");

  ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                              QCP::iSelectPlottables);

  double xVal[21] = {-10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0,
                     1,   2,  3,  4,  5,  6,  7,  8,  9,  10};
  double yVal[21];
  for (int i = 0; i < 21; i++) {
    // yVal[i] = xVal[i] * xVal[i];
    calc_expression("X^2", &yVal[i], xVal[i]);
  }
  QVector<double> x(std::begin(xVal), std::end(xVal));
  QVector<double> y(std::begin(yVal), std::end(yVal));

  ui->widget->graph(0)->setData(x, y);
  ui->widget->rescaleAxes();
  ui->widget->replot();
  ui->widget->update();
}

Graph::~Graph() { delete ui; }
