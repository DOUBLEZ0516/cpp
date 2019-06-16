#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <algorithm>
using std::find_if;
using std::stable_sort;
using std::for_each;
using std::count_if;

#include <functional>
using std::bind;
using std::ref;
using std::cref;

using namespace std::placeholders;

#include <numeric>
#include <list>

#include "../../ch7/sales_data/sales_data.h"

template <typename Sequence> 
inline std::ostream& println(Sequence const& seq) {
    for (auto const& elem : seq) std::cout << elem << " ";
    std::cout << std::endl;

    return std::cout;
}



void elimdups(std::vector<std::string>& vs)
{
    std::sort(vs.begin(), vs.end());
    auto new_end = std::unique(vs.begin(), vs.end());
    vs.erase(new_end, vs.end());
}


/*******************************************
							10.11
*******************************************/
inline bool is_shorter(std::string const& lhs, std::string const& rhs)
{
    return lhs.size() < rhs.size();
}


/*******************************************
							10.12
*******************************************/
inline bool compareIsbn(const SalesData& lhs, const SalesData& rhs) {
	return lhs.GetIsbn() < rhs.GetIsbn();
}


/*******************************************
							10.13
*******************************************/
bool ForPartition(const std::string& s) {
	return s.size() <= 5;
}

/*******************************************
							10.16
*******************************************/
bool check_size(const string& s, string::size_type sz) {
	return s.size() < sz;
};
void baggies(vector<string>& words, 
             vector<string>::size_type sz) {

	elimdups(words);
	stable_sort(words.begin(), words.end(), 
	            [] (const string& a, const string& b)
	            	 {return a.size() < b.size(); });

	auto wc = find_if(words.begin(), words.end(),
	                  [sz] (const string& a) {
	                  	return a.size() >= sz;});

	// auto count = words.end() - wc;
	// 10.20
	// auto count = count_if(words.begin(), words.end(), 
	                      // [sz] (const string& s) { return s.size() >= sz; });
	// 10.21

	auto count = count_if(words.begin(), words.end(),
	                      bind(check_size, _1, sz));


	for_each(wc, words.end(), 
	         [] (const string& s) {cout << s << endl;});
	cout << endl;

}

int main() {
		cout << "******** Question 10.11 ****************" << endl;
    std::vector<std::string> v{"1234", "1234", "1234", "Hi", "alan", "wang"};
    elimdups(v);
    std::stable_sort(v.begin(), v.end(), is_shorter);
    println(v);
    cout << "****************************************" << endl << endl << endl;


    cout << "******** Question 10.12 **************** " << endl;

    cout << "****************************************" << endl << endl << endl;



    cout << "******** Question 10.13 ****************" << endl;
    	auto testcase = std::vector<std::string>{"a",         "as",        "aasss",
                                      "aaaaassaa", "aaaaaabba", "aaa"};
      auto pivot = std::partition(testcase.begin(), testcase.end(), ForPartition);

      for (auto it = pivot; it < testcase.end(); it++)
      	cout << *it << endl;
    cout << "****************************************" << endl << endl << endl;


    cout << "******** Question 10.14 **************** " << endl;
    int a = 3, b = 4;
    auto f = [&] (const int& lhs, const int& rhs) { return lhs + rhs; };
    cout << "a=" << a << " " << " b=" << b << " sum=" << f(a, b) << endl;
    cout << "****************************************" << endl << endl << endl;



    cout << "******** Question 10.15 **************** " << endl;
    int c = 12;
    auto g = [c] (const int& lhs) { return c + lhs; };
    cout << g(15) << endl;
    cout << "****************************************" << endl << endl << endl;
    
    cout << "******** Question 10.16 **************** " << endl;
    testcase = std::vector<std::string>{"a",         "as",        "aasss",
                                      "aaaaassaa", "aaaaaabba", "aaa"};
    baggies(testcase, 5);
    cout << "****************************************" << endl << endl << endl;

    cout << "******** Question 10.17 **************** " << endl;
    baggies(testcase, 6);
    cout << "****************************************" << endl << endl << endl;

    cout << "******** Question 10.21 **************** " << endl;
    int m = 12;
    cout << "previous " << m << endl;
    auto h = [&] () -> bool
    					{ return --m > 0 ? true : false; };

    while (h())
    	continue;
    cout << "after " << m << endl;
    cout << "****************************************" << endl << endl << endl;



    cout << "******** Question 10.22 **************** " << endl;
    string s = "abcdei";
    vector<int> v2 {1,2,3,4,5,6,11,7,8,9};
    auto iter = find_if(v2.begin(), v2.end(), bind(check_size, s, _1));
    cout << *iter << endl;
    cout << "****************************************" << endl << endl << endl;



    return 0;
}










