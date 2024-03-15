#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>

#include "../backend/controller.h"
#include "../backend/data.h"
#include "../backend/maze.h"
#include "../backend/parser.h"

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
  virtual void paintEvent(QPaintEvent *event);
 private slots:
  void on_openFile_clicked();

  void on_Generate_clicked();

  void on_Solve_clicked();

  void on_gen_r_valueChanged(int arg1);

  void on_gen_c_valueChanged(int arg1);

  void on_solve_sr_2_valueChanged(int arg1);

  void on_solve_sc_2_valueChanged(int arg1);

  void on_save_file_button_clicked();

 private:
  Ui::MainWindow *ui;
  QGraphicsScene *scene;
  bool draw_flag = 0;
  bool solve_flag = 0;
  s21::Controller *ctr = s21::Controller::make_ctrl();
};
#endif  // MAINWINDOW_H
