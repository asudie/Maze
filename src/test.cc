#include <gtest/gtest.h>

#include "backend/controller.h"

TEST(t1, test1) {
  const char *input = "maze10_10.txt";
  s21::Controller *ctr = s21::Controller::make_ctrl();

  ctr->SetData(input);
  ctr->GetData();

  EXPECT_EQ(ctr->GetDataSize().first, 10);
  EXPECT_EQ(ctr->GetDataSize().second, 10);
}

TEST(t2, test2) {
  const char *input = "maze10_10.txt";
  s21::Controller *ctr = s21::Controller::make_ctrl();

  ctr->SetData(input);
  ctr->GetData();
  ctr->ClearData();
  ctr->ClearSize();

  EXPECT_EQ(ctr->GetDataSize().first, 0);
  EXPECT_EQ(ctr->GetDataSize().second, 0);
}

TEST(t3, test3) {
  const char *input = "maze10_10.txt";
  s21::Controller *ctr = s21::Controller::make_ctrl();
  std::vector<int> w{1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0,
                     1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1,
                     0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1,
                     0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1,
                     0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0,
                     1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1};
  std::vector<int> f{0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1,
                     0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0,
                     1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0,
                     0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0,
                     0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0,
                     0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  ctr->SetData(input);
  ctr->GetData();
  EXPECT_EQ(ctr->GetDataSize().first, 10);
  EXPECT_EQ(ctr->GetDataSize().second, 10);
  EXPECT_EQ(ctr->GetDataWalls(), w);
  EXPECT_EQ(ctr->GetDataFloors(), f);
  ctr->PrintMaze();
}

TEST(t4, test4) {
  const char *input = "maze10_1.txt";
  s21::Controller *ctr = s21::Controller::make_ctrl();
  EXPECT_THROW(ctr->SetData(input), std::logic_error);
}
TEST(t5, test5) {
  const char *input = "maze_wrong.txt";
  s21::Controller *ctr = s21::Controller::make_ctrl();
  EXPECT_THROW(ctr->SetData(input), std::logic_error);
}

TEST(t6, test6) {
  const char *input = "maze5_5.txt";
  s21::Controller *ctr = s21::Controller::make_ctrl();

  ctr->SetData(input);
  ctr->GetData();
  EXPECT_EQ(ctr->GetDataSize().first, 5);
  EXPECT_EQ(ctr->GetDataSize().second, 5);

  ctr->SetMazePoints(0, 22);
  std::vector<int> res{0, 1, 6, 7, 12, 13, 18, 17, 22};
  EXPECT_EQ(ctr->GetMazePath(), res);

  ctr->PrintMaze();
}

TEST(t7, test7) {
  int c = 10;
  int r = 10;
  s21::Controller *ctr = s21::Controller::make_ctrl();

  ctr->SetMazeSize(r, c);
  ctr->GetNewMaze();

  EXPECT_EQ(ctr->GetDataSize().first, r);
  EXPECT_EQ(ctr->GetDataSize().second, c);

  ctr->PrintMaze();
}

TEST(t8, test8) {
  int r = 20;
  int c = 30;
  s21::Controller *ctr = s21::Controller::make_ctrl();

  ctr->SetMazeSize(r, c);
  ctr->GetNewMaze();

  EXPECT_EQ(ctr->GetDataSize().first, r);
  EXPECT_EQ(ctr->GetDataSize().second, c);

  ctr->PrintMaze();
}

TEST(t9, test9) {
  int c = 60;
  int r = 70;
  s21::Controller *ctr = s21::Controller::make_ctrl();

  ctr->SetMazeSize(r, c);
  ctr->GetNewMaze();

  EXPECT_EQ(ctr->GetDataSize().first, r);
  EXPECT_EQ(ctr->GetDataSize().second, c);
  ctr->SetMazePoints(2, 4);
  ctr->GetMazePath();
  ctr->PrintPath();
}

TEST(t10, test10) {
  int c = 20;
  int r = 15;
  s21::Controller *ctr = s21::Controller::make_ctrl();

  ctr->SetMazeSize(r, c);
  ctr->GetNewMaze();

  EXPECT_EQ(ctr->GetDataSize().first, r);
  EXPECT_EQ(ctr->GetDataSize().second, c);
  ctr->SetMazePoints(1, 290);
  ctr->GetMazePath();
  ctr->PrintPath();
}

TEST(t11, test11) {
  int c = 46;
  int r = 39;
  s21::Controller *ctr = s21::Controller::make_ctrl();

  ctr->SetMazeSize(r, c);
  ctr->GetNewMaze();

  EXPECT_EQ(ctr->GetDataSize().first, r);
  EXPECT_EQ(ctr->GetDataSize().second, c);
  ctr->PrintMaze();
  ctr->PrintMazeMatrix();
  ctr->SetMazePoints(1, 1781);
  ctr->GetMazePath();
  ctr->PrintPath();
}

TEST(t12, test12) {
  int c = 6;
  int r = 6;
  s21::Controller *ctr = s21::Controller::make_ctrl();

  ctr->SetMazeSize(r, c);
  ctr->GetNewMaze();

  EXPECT_EQ(ctr->GetDataSize().first, r);
  EXPECT_EQ(ctr->GetDataSize().second, c);
  ctr->PrintMaze();
  ctr->PrintMazeMatrix();
  ctr->SetMazePoints(0, 27);
  ctr->GetMazePath();
  ctr->PrintPath();
}

TEST(t13, test13) {
  const char *input = "maze10_10.txt";
  s21::Controller *ctr = s21::Controller::make_ctrl();

  ctr->SetData(input);
  ctr->GetData();
  const char *output = "save_maze_10_10.txt";
  ctr->SaveMazeMatrix(output);

  std::ifstream orig(input);
  std::string origfile((std::istreambuf_iterator<char>(orig)),
                       std::istreambuf_iterator<char>());
  std::ifstream res(output);
  std::string resfile((std::istreambuf_iterator<char>(res)),
                      std::istreambuf_iterator<char>());
  EXPECT_EQ(origfile, resfile);
  orig.close();
  res.close();
}

TEST(t14, test14) {
  int c = 10;
  int r = 10;
  s21::Controller *ctr = s21::Controller::make_ctrl();

  ctr->SetMazeSize(r, c);
  ctr->GetNewMaze();

  EXPECT_EQ(ctr->GetDataSize().first, r);
  EXPECT_EQ(ctr->GetDataSize().second, c);

  EXPECT_THROW(ctr->SetMazePoints(-2, 4);, std::logic_error);
}

TEST(t15, test15) {
  int c = 10;
  int r = 10;
  s21::Controller *ctr = s21::Controller::make_ctrl();

  ctr->SetMazeSize(r, c);
  ctr->GetNewMaze();

  EXPECT_EQ(ctr->GetDataSize().first, r);
  EXPECT_EQ(ctr->GetDataSize().second, c);

  EXPECT_THROW(ctr->SetMazePoints(2, 104);, std::logic_error);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
