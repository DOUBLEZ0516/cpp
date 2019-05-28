#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include "./TextProgram/textquery.cpp"



int main() {
  std::ifstream input("test.rtf");
  runQueries(input);
  input.close();

  return 0;
}