#include "mazegenerator.h"

namespace s21 {

Data MazeGenerator::GetData() {
  Data data;
  data.SetDataSize(obj_->GetDataSize());
  data.SetDataWalls(obj_->GetDataWalls());
  data.SetDataFloors(obj_->GetDataFloors());
  return data;
};

void MazeGenerator::SetMazeSize(int r, int c) {
  row_ = r;
  col_ = c;
  obj_->SetDataSize(std::pair<int, int>(r, c));
  obj_->ClearData();
  GenerateMaze();
};

int MazeGenerator::Random(int s, int f) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(s, f);
  return dist(gen);
};

std::vector<int> &MazeGenerator::SetRandom(std::vector<int> &line, int s,
                                           int f) {
  for (int i = 0; i < (int)line.size(); i++) {
    line[i] = Random(s, f);
  }
  return line;
}

std::vector<int> &MazeGenerator::SetSequence(std::vector<int> &line,
                                             int &counter) {
  for (int i = 0; i < (int)line.size(); i++) {
    if (line[i] == 0) line[i] = counter++;
  }
  return line;
}

void MazeGenerator::CorrectLastWalls(std::vector<int> &line,
                                     std::vector<int> &w) {
  for (int i = 0; i < (int)line.size() - 1; i++) {
    if (line[i] != line[i + 1]) w[i] = 0;
  }
  w[w.size() - 1] = 1;
}

void MazeGenerator::CombineSets(std::vector<int> &line, std::vector<int> &w) {
  for (int i = 0; i < (int)line.size() - 1; i++) {
    if (line[i] == line[i + 1])
      w[i] = 1;
    else {
      w[i] = Random(0, 1);
      if (w[i] == 0) {
        line[i + 1] = line[i];
      }
    }
  }
  w[w.size() - 1] = 1;
}

void MazeGenerator::CountSets(std::vector<int> &line, int num,
                              std::vector<int> &count) {  //, int pos
  count.clear();
  for (int i = 0; i < (int)line.size(); ++i) {
    if (line[i] == num) count.push_back(i);
  }
}

int MazeGenerator::CountBorders(std::vector<int> &b, std::vector<int> &count) {
  int counter = 0;
  for (int i = 0; i < (int)count.size(); ++i) {
    counter += b[count[i]];
  }
  return counter;
}

void MazeGenerator::CheckLowerBorders(std::vector<int> &line,
                                      std::vector<int> &b) {
  std::vector<int> count;
  int last_set = line[0];
  for (int i = 0; i < (int)line.size(); ++i) {
    if ((i == 0) || last_set != line[i]) {
      last_set = line[i];
      CountSets(line, line[i], count);
      if ((int)count.size() == CountBorders(b, count)) {
        b[count[Random(0, count.size() - 1)]] = 0;
      }
    }
  }
}

void MazeGenerator::DeleteExtraSets(std::vector<int> &line,
                                    std::vector<int> &b) {
  for (int i = 0; i < (int)line.size(); ++i) {
    if (b[i] == 1) {
      line[i] = 0;
    }
  }
}

void MazeGenerator::GenerateMaze() {
  std::vector<int> cur_line(col_, 0);
  std::vector<int> right_walls(col_);
  std::vector<int> lower_borders(col_);
  int row = row_;
  int counter = 1;
  while (--row) {
    CombineSets(SetSequence(cur_line, counter), right_walls);
    CheckLowerBorders(cur_line, SetRandom(lower_borders, 1, 1));
    obj_->InsertToWalls(right_walls);
    obj_->InsertToFloors(lower_borders);
    if (row > 1) DeleteExtraSets(cur_line, lower_borders);
  }
  CorrectLastWalls(cur_line, right_walls);
  obj_->InsertToWalls(right_walls);
  obj_->InsertToFloors(SetRandom(lower_borders, 1, 1));
}

}  // namespace s21
