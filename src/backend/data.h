#ifndef S21_DATA_H
#define S21_DATA_H
#include <fstream>
#include <iostream>
#include <vector>

namespace s21 {
class Data {
 public:
  Data(){};
  ~Data(){};

  void ClearData();
  void ClearSize();

  void SetDataSize(std::pair<int, int> size);
  void SetDataWalls(std::vector<int> &walls);
  void SetDataFloors(std::vector<int> &floors);

  void PushToWalls(int);
  void PushToFloors(int);

  void InsertToWalls(std::vector<int> &add);
  void InsertToFloors(std::vector<int> &add);

  std::pair<int, int> GetDataSize();
  std::vector<int> &GetDataWalls();
  std::vector<int> &GetDataFloors();
  void PrintWalls();
  void PrintFloors();
  void PrintMaze();
  void PrintMazeMatrix();
  void SaveMazeMatrix(const char *path);

 private:
  std::pair<int, int> size_{};  // first = row, second = col
  std::vector<int> walls_{};
  std::vector<int> floors_{};
};
}  // namespace s21

#endif