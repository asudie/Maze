#ifndef S21_PARSER_H
#define S21_PARSER_H
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "data.h"

namespace s21 {
class Parser {
 public:
  Parser(Data *obj);
  ~Parser(){};
  void SetData(const char *path);
  Data GetData();
  void FillData();

 private:
  Data *obj_;
  const char *path_;
};
}  // namespace s21

#endif