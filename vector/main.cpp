
#include <iostream>

#include <memory>
using std::allocator;
#include "myvector.h"


int main() {

  std::cout << "init, push_back, insert: " << std::endl;
  MyVector<int> t(4);
  t.push_back(3); 
  t.insert(t.begin(), 1, 2);
  for (auto num : t)
    std::cout << num << " ";

  std::cout << std::endl;
  std::cout << "<< operator: " << t[3] << std::endl;

  std::cout << "erase test " << std::endl;
  t.erase(t.begin()+2);
  for (auto num : t)
    std::cout << num << " ";
  std::cout << std::endl;

  std::cout << "pop_back test:  " << std::endl;
  std::cout << t.size() << std::endl;
  t.pop_back();
  std::cout << t.size() << std::endl;


  std::cout << "resize and capacity " << std::endl;
  auto n = t.capacity();
  t.resize(2*n, 6);
  for (auto num : t)
    std::cout << num << " ";
  std::cout << std::endl;
  return 0;
}