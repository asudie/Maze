#include "maze.h"

namespace s21 {

void Maze::ClearMaze() { graph_.clear(); };
void Maze::ClearSize(){};

void Maze::SetStartFinish(int s, int f) {
  if (s < 0 || s > (obj_->GetDataSize().first * obj_->GetDataSize().second - 1))
    throw std::logic_error("The starting point does not exist!");
  else if (f < 0 ||
           f > (obj_->GetDataSize().first * obj_->GetDataSize().second - 1))
    throw std::logic_error("The finishing point does not exist!");
  else
    start_ = s;
  finish_ = f;
};

std::vector<int> &Maze::GetPath() {
  row_ = obj_->GetDataSize().first;
  col_ = obj_->GetDataSize().second;
  walls_ = obj_->GetDataWalls();
  floors_ = obj_->GetDataFloors();
  MakeGraph();
  MakePath();
  return path_;
};

std::vector<std::vector<int>> &Maze::GetMazeGraph() { return graph_; };

void Maze::MakeGraph() {
  std::vector<std::vector<int>> tmp(row_ * col_);
  graph_.swap(tmp);
  for (int i = 0; i < row_; ++i) {
    for (int j = 0; j < col_; ++j) {
      if (!(walls_[i * col_ + j])) {
        graph_[i * col_ + j].push_back(i * col_ + j + 1);
        graph_[i * col_ + j + 1].push_back(i * col_ + j);
      }
      if (!(floors_[i * col_ + j])) {
        graph_[i * col_ + j].push_back((i + 1) * col_ + j);
        graph_[(i + 1) * col_ + j].push_back(i * col_ + j);
      }
    }
  }
}

void Maze::MakePath() {
  path_.clear();
  std::vector<bool> visited(row_ * col_, false);
  std::vector<int> parent(row_ * col_);
  std::queue<int> q;
  int to;
  q.push(start_);
  visited[start_] = true;
  while (!q.empty()) {
    to = q.front();
    q.pop();
    for (int u : graph_[to]) {
      if (!visited[u]) {
        q.push(u);
        visited[u] = visited[to] + 1;
        parent[u] = to;
      }
    }
  }
  if (!visited[finish_])
    throw std::logic_error("There is no way between these points!");
  else {
    int f = finish_;
    while (f != start_) {
      path_.push_back(f);
      f = parent[f];
    }
    path_.push_back(start_);
    std::reverse(path_.begin(), path_.end());
  }
}

void Maze::PrintPath() {
  for (int i = 0; i < (int)path_.size(); ++i) {
    std::cout << path_[i] << " ";
  }
  std::cout << std::endl;
};

}  // namespace s21
