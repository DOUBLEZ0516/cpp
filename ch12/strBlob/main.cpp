#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::istream;


#include <fstream>
#include <string>
using std::string;

#include <memory>
using std::make_shared;

#include <initializer_list>
using std::initializer_list;



#include "strBlob.h"


void process(shared_ptr<int> p) {
  cout << "inside process, use_count: " << p.use_count() << endl; 
}

int main() {

  cout << "******** Question 12.01 **************** " << endl;
  StrBlob b1;
  {
  	StrBlob b2({"a", "an", "the"});
  	b1 = b2;
  	b2.push_back("about");
  }
  cout << "b1 size: " << b1.size() << endl;
  cout << "****************************************" << endl << endl << endl;


  cout << "******** Question 12.02 **************** " << endl;
  const StrBlob test1{"hello", "world"};
  StrBlob test2{"hello", "world", "Mooophy"};

  std::cout << test1.front() << " " << test1.back() << std::endl;
  test2.back() = "test";
  std::cout << test2.front() << " " << test2.back() << std::endl;

  cout << "****************************************" << endl << endl << endl;


  cout << "******** Question 12.06 **************** " << endl;
  auto v = new vector<int> ({ 1, 2, 3});
  for (auto n : *v) cout << n << endl;
  delete v;
  cout << "****************************************" << endl << endl << endl;


  cout << "******** Question 12.07 **************** " << endl;
  auto v2 = make_shared<vector<int>> (initializer_list<int>{1,2});
  v2->push_back(1);
  for (auto n : *v2) cout << n << endl;
  cout << "****************************************" << endl << endl << endl;


  cout << "******** Question 12.10 **************** " << endl;
  shared_ptr<int> p (new int(42));
  cout << "before process, use_count: " << p.use_count() << endl; 
  process(shared_ptr<int>(p));  // made a copy and increment the use_count
  cout << "after process, use_count: " << p.use_count() << endl; 
  cout << "****************************************" << endl << endl << endl;


  cout << "******** Question 12.20 **************** " << endl;
  std::ifstream ifs("test.txt");
  StrBlob blob;
  string line;
  while (std::getline(ifs, line))
    blob.push_back(line);

  for (StrBlobPtr pbeg(blob.begin()), pend(blob.end()); pbeg != pend ; pbeg.incre())
    cout << pbeg.deref() << endl; 
  cout << "****************************************" << endl << endl << endl;


  cout << "******** Question 12.12 **************** " << endl;

  cout << "****************************************" << endl << endl << endl;



  cout << "******** Question 12.13 **************** " << endl;

  cout << "****************************************" << endl << endl << endl;


  cout << "******** Question 12.01 **************** " << endl;

  cout << "****************************************" << endl << endl << endl;



  cout << "******** Question 12.01 **************** " << endl;

  cout << "****************************************" << endl << endl << endl;
	return 0;	
}