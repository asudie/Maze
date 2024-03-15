#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  scene = new QGraphicsScene(QRectF(-5, -5, 510, 510), this);
  scene->setBackgroundBrush(Qt::black);
  ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::paintEvent(QPaintEvent *event) {
  QPen linePen(Qt::green);
  linePen.setWidth(2);
  scene->addLine(0, 0, 500, 0, linePen);
  scene->addLine(0, 0, 0, 500, linePen);
  scene->addLine(0, 500, 500, 500, linePen);
  scene->addLine(500, 0, 500, 500, linePen);

  if (draw_flag) {
    int length_x = 500 / ctr->GetDataSize().second;
    int length_y = 500 / ctr->GetDataSize().first;
    scene->clear();
    scene->addLine(0, 0, length_x * ctr->GetDataSize().second, 0, linePen);
    scene->addLine(0, 0, 0, length_y * ctr->GetDataSize().first, linePen);

    std::vector<int> w = ctr->GetDataWalls();
    std::vector<int> f = ctr->GetDataFloors();
    auto it = w.begin();
    for (int y = 0; y < ctr->GetDataSize().first; y++) {
      for (int x = 1; x <= ctr->GetDataSize().second; x++) {
        if (*it)
          scene->addLine(length_x * x, length_y * y, length_x * x,
                         length_y * (y + 1), linePen);
        if (it != w.end()) it++;
      }
    }
    it = f.begin();
    for (int y = 1; y <= ctr->GetDataSize().first; y++) {
      for (int x = 0; x < ctr->GetDataSize().second; x++) {
        if (*it)
          scene->addLine(length_x * x, length_y * y, length_x * (x + 1),
                         length_y * y, linePen);
        if (it != w.end()) it++;
      }
    }
    if (solve_flag) {
      QPen pathLine(Qt::red);
      pathLine.setWidth(2);
      std::vector<int> r = ctr->GetMazePath();

      auto it_r = r.begin();

      int i = 0;
      int j = 0;
      int i1 = 0;
      int j1 = 0;
      while (it_r != r.end()) {
        j = *it_r / ctr->GetDataSize().second;
        i = *it_r % ctr->GetDataSize().second;
        if (it_r++ == r.end() - 1) break;
        j1 = *it_r / ctr->GetDataSize().second;
        i1 = *it_r % ctr->GetDataSize().second;
        scene->addLine(length_x * i + length_x / 2, length_y * j + length_y / 2,
                       length_x * i1 + length_x / 2,
                       length_y * j1 + length_y / 2, pathLine);
      }
    }
  }
}

void MainWindow::on_openFile_clicked() {
  QString filename = QFileDialog::getOpenFileName(
      this, tr("Open File"), "/", "All files (*.*);; Text File (*.txt)");
  ui->fileName->setText(filename);
  QByteArray file_name_buf = filename.toLocal8Bit();
  char *path = file_name_buf.data();
  try {
    ctr->SetData(path);
  } catch (const std::exception &ex) {
    QMessageBox::critical(this, "Error ", ex.what());
  }

  draw_flag = 1;
  solve_flag = 0;
  scene->clear();
  repaint();
}

void MainWindow::on_Generate_clicked() {
  scene->clear();
  ui->fileName->clear();
  if (ui->gen_r->value() > 1 && ui->gen_r->value() <= 50 &&
      ui->gen_c->value() > 1 && ui->gen_c->value() <= 50) {
    solve_flag = 0;
    ctr->SetMazeSize(ui->gen_r->value(), ui->gen_c->value());
    ctr->GetNewMaze();
    draw_flag = 1;
  } else {
    QMessageBox::about(this, "Error ", "Wrong size of maze");
  }
  repaint();
}

void MainWindow::on_Solve_clicked() {
  scene->clear();
  if ((ui->solve_sr_2->value() <
       ctr->GetDataSize().first * ctr->GetDataSize().second) &&
      (ui->solve_sc_2->value() <
       ctr->GetDataSize().first * ctr->GetDataSize().second) &&
      (ui->solve_sr_2->value() != ui->solve_sc_2->value())) {
    ctr->SetMazePoints(ui->solve_sr_2->value(), ui->solve_sc_2->value());
    solve_flag = 1;
    repaint();
  } else {
    QMessageBox::about(this, "Error ", "Wrong start or finish point");
  }
}

void MainWindow::on_gen_r_valueChanged(int arg1) { ui->gen_r->setValue(arg1); }

void MainWindow::on_gen_c_valueChanged(int arg1) { ui->gen_c->setValue(arg1); }

void MainWindow::on_solve_sr_2_valueChanged(int arg1) {
  ui->solve_sr_2->setValue(arg1);
}

void MainWindow::on_solve_sc_2_valueChanged(int arg1) {
  ui->solve_sc_2->setValue(arg1);
}

void MainWindow::on_save_file_button_clicked() {
  QString dirname =
      QFileDialog::getSaveFileName(this, "Выбeрите папку", "/", ".txt");
  QByteArray file_save_buf = dirname.toLocal8Bit();
  char *path = file_save_buf.data();
  try {
    ctr->SaveMazeMatrix(path);
  } catch (const std::exception &ex) {
    QMessageBox::critical(this, "Error ", ex.what());
  }
}
