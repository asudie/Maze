#ifndef S21_MAZEGENERATOR_H
#define S21_MAZEGENERATOR_H
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "data.h"

namespace s21 {

class MazeGenerator {
 public:
  MazeGenerator(Data *obj) { obj_ = obj; };
  ~MazeGenerator(){};
  void SetMazeSize(int r, int c);
  Data GetData();
  void GenerateMaze();

 private:
  Data *obj_;
  int Random(int s, int f);
  void CountSets(std::vector<int> &line, int num,
                 std::vector<int> &count);  //, int pos);
  int CountBorders(std::vector<int> &b, std::vector<int> &count);
  std::vector<int> &SetSequence(std::vector<int> &line, int &counter);
  std::vector<int> &SetRandom(std::vector<int> &line, int s, int f);
  void CombineSets(std::vector<int> &line, std::vector<int> &w);
  void CheckLowerBorders(std::vector<int> &line, std::vector<int> &b);
  void DeleteExtraSets(std::vector<int> &line, std::vector<int> &b);
  void CorrectLastWalls(std::vector<int> &line, std::vector<int> &w);
  int row_;
  int col_;
};
}  // namespace s21

#endif