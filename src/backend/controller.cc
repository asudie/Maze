#include "controller.h"

namespace s21 {

Controller *Controller::ctrl_ = nullptr;

Controller *Controller::make_ctrl() {
  if (ctrl_ == nullptr) ctrl_ = new Controller();
  return ctrl_;
}

Controller::Controller() {
  data_ = new Data();
  parser_ = new Parser(data_);
  maze_ = new Maze(data_);
  gen_ = new MazeGenerator(data_);
}

std::pair<int, int> Controller::GetDataSize() { return data_->GetDataSize(); }

const std::vector<int> Controller::GetDataWalls() {
  return data_->GetDataWalls();
}
const std::vector<int> Controller::GetDataFloors() {
  return data_->GetDataFloors();
}

void Controller::ClearData() { data_->ClearData(); }
void Controller::ClearSize() { data_->ClearSize(); }

void Controller::SetData(const char *new_path) { parser_->SetData(new_path); }
Data Controller::GetData() { return parser_->GetData(); }

void Controller::SetMazePoints(int s, int f) { maze_->SetStartFinish(s, f); };
std::vector<int> Controller::GetMazePath() { return maze_->GetPath(); };

void Controller::SetMazeSize(int r, int c) { gen_->SetMazeSize(r, c); };
Data Controller::GetNewMaze() { return gen_->GetData(); }

void Controller::PrintMaze() { data_->PrintMaze(); };
void Controller::PrintPath() { maze_->PrintPath(); };
void Controller::PrintMazeMatrix() { data_->PrintMazeMatrix(); }
void Controller::SaveMazeMatrix(const char *new_path) {
  data_->SaveMazeMatrix(new_path);
}

Controller::~Controller() {
  delete data_;
  delete parser_;
  delete maze_;
  delete gen_;
}

}  // namespace s21
