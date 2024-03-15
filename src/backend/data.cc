#include "data.h"

namespace s21 {

void Data::ClearData() {
  walls_.clear();
  floors_.clear();
};

void Data::ClearSize() {
  size_.first = 0;
  size_.second = 0;
};

void Data::SetDataSize(std::pair<int, int> size) {
  size_.first = size.first;
  size_.second = size.second;
};

void Data::SetDataWalls(std::vector<int> &walls) { walls_ = walls; };
void Data::SetDataFloors(std::vector<int> &floors) { floors_ = floors; };

void Data::PushToWalls(int num) { walls_.push_back(num); };
void Data::PushToFloors(int num) { floors_.push_back(num); };

void Data::InsertToWalls(std::vector<int> &add) {
  walls_.insert(walls_.cend(), add.cbegin(), add.cend());
};

void Data::InsertToFloors(std::vector<int> &add) {
  floors_.insert(floors_.cend(), add.cbegin(), add.cend());
};

std::pair<int, int> Data::GetDataSize() { return size_; };
std::vector<int> &Data::GetDataWalls() { return walls_; };
std::vector<int> &Data::GetDataFloors() { return floors_; };

void Data::PrintWalls() {
  std::cout << "Walls from Data:" << std::endl;
  for (int i = 0; i < (int)walls_.size(); ++i) {
    std::cout << walls_[i] << " ";
  }
  std::cout << std::endl;
};

void Data::PrintFloors() {
  std::cout << "Floors from Data:" << std::endl;
  for (int i = 0; i < (int)floors_.size(); ++i) {
    std::cout << floors_[i] << " ";
  }
  std::cout << std::endl;
};

void Data::PrintMaze() {
  int k = 0;
  while (size_.second > k++) {
    std::cout << "__";
  }
  std::cout << std::endl;
  for (int i = 0; i < size_.first; ++i) {
    std::cout << "|";
    for (int j = 0; j < size_.second; ++j) {
      if (floors_[i * size_.second + j] && walls_[i * size_.second + j])
        std::cout << "_|";
      else if (!floors_[i * size_.second + j] && walls_[i * size_.second + j])
        std::cout << " |";
      else if (floors_[i * size_.second + j] && !walls_[i * size_.second + j])
        std::cout << "__";
      else
        std::cout << "  ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
};

void Data::PrintMazeMatrix() {
  std::cout << size_.first << " " << size_.second << std::endl;
  for (int i = 0; i < size_.first; ++i) {
    for (int j = 0; j < size_.second; ++j) {
      std::cout << walls_[i * size_.second + j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  for (int i = 0; i < size_.first; ++i) {
    for (int j = 0; j < size_.second; ++j) {
      std::cout << floors_[i * size_.second + j] << " ";
    }
    std::cout << std::endl;
  }
};

void Data::SaveMazeMatrix(const char *path) {
  std::ofstream out;
  out.open(path);
  if (out.is_open()) {
    out << size_.first << " " << size_.second << std::endl;
    for (int i = 0; i < size_.first; ++i) {
      for (int j = 0; j < size_.second; ++j) {
        out << walls_[i * size_.second + j] << " ";
      }
      out << std::endl;
    }
    out << std::endl;
    for (int i = 0; i < size_.first; ++i) {
      for (int j = 0; j < size_.second; ++j) {
        out << floors_[i * size_.second + j];
        if (j != size_.second - 1) out << " ";
      }
      if (i != size_.first - 1) out << " " << std::endl;
    }
    out.close();
  } else {
    throw std::logic_error("Can't save file!");
  }
};

}  // namespace s21
