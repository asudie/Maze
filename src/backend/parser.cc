#include "parser.h"

namespace s21 {

Parser::Parser(Data *obj) {
  obj_ = obj;
  obj_->SetDataSize({0, 0});
};

void Parser::SetData(const char *path) {
  path_ = path;
  FillData();
}

Data Parser::GetData() {
  Data data;
  data.SetDataSize(obj_->GetDataSize());
  data.SetDataWalls(obj_->GetDataWalls());
  data.SetDataFloors(obj_->GetDataFloors());
  return data;
}

void Parser::FillData() {
  std::ifstream file(path_);
  if (!file) throw std::logic_error("Failed to open the file!");
  std::string line;
  int row, col;
  std::getline(file, line);
  std::istringstream iss(line);
  iss >> row >> col;
  if (row > 0 && col > 0) {
    obj_->SetDataSize(std::pair<int, int>(row, col));
  } else {
    file.close();
    throw std::logic_error("Incorrect maze size!");
  }
  obj_->ClearData();
  int num;
  int r = 0;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    while (iss >> num) {
      if (r < row) {
        obj_->PushToWalls(num);
      } else
        obj_->PushToFloors(num);
    }
    ++r;
  }
  file.close();
  if ((int)obj_->GetDataWalls().size() != row * col ||
      (int)obj_->GetDataFloors().size() != row * col)
    throw std::logic_error("Incorrect maze matrix!");
}

}  // namespace s21
