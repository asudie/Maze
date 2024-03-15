#ifndef S21_CONTROLLER_H
#define S21_CONTROLLER_H

#include "maze.h"
#include "mazegenerator.h"
#include "parser.h"

namespace s21 {

class Controller {
 protected:
  static Controller *ctrl_;
  Controller();

 public:
  ~Controller();

  static Controller *make_ctrl();

  std::pair<int, int> GetDataSize();

  const std::vector<int> GetDataWalls();
  const std::vector<int> GetDataFloors();

  void ClearData();
  void ClearSize();

  void SetData(const char *path);
  Data GetData();

  void SetMazePoints(int s, int f);
  std::vector<int> GetMazePath();

  void SetMazeSize(int r, int c);
  Data GetNewMaze();

  void PrintMaze();
  void PrintPath();
  void PrintMazeMatrix();
  void SaveMazeMatrix(const char *path);

 private:
  Data *data_;
  Parser *parser_;
  Maze *maze_;
  MazeGenerator *gen_;
};

}  // namespace s21

#endif
