#include <iostream>
using std::cin; using std::cout; using std::endl; using std::cerr;

#include "Sales_Item.h"

int main() {]


  /*
  example 1: initialize an item
  */
  // initialize
  Sales_Item book;

  // read in book no
  cin >> book;
  cout << book << endl;


  /*
  example 2: Sales_Item adder
   */
  Sales_Item item1, item2;
  cin >> item1 >> item2;
  cout << item1 + item2 << endl;


  /*
  example 3: class members
   */
  if (item1.isbn() == item2.isbn()) {
    cout << item1 + item2 << endl;
    return 0;
  } else {
    cerr << "Data must refer to same ISBN" << endl;
    return -1;
  }

}


