#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include "queryclass/qclass.cpp"

// using namespace std;


int main() {
  std::ifstream input("test.rtf");

  runQueries(input); 
  input.close();

  return 0;
}