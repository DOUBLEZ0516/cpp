#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

#include "sales_data.h"


int main() {
	// SalesData total;
	// if (read(std::cin, total)) {
	// 	SalesData trans;
	// 	while (read(std::cin, trans)) {
	// 		if (total.bookNo == trans.bookNo) {
	// 			total.combine(trans);
	// 		} else {
	// 			print(std::cout, total) << endl;
	// 			total = trans;
	// 		}
	// 	}

	// 	print(std::cout, total) << endl;

	// } else {
	// 	cerr << "NO DATA" << endl;
	// }

	// print(std::cout, total);
	

	/****************************
		example of delegating constructor
	****************************/
	// SalesData test;



	/****************************
		example of account , static member
	****************************/
	Account acc;
	// double Account::todayRate = 10.0;
	// acc.rate(0.5);
	// cout << acc.rate() << endl;

	// Account::todayRate = 20.0;

	cout << Account::todayRate << endl;
	return 0;
}