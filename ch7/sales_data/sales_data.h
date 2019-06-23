#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <string>
using std::string;



class SalesData {

friend SalesData add(const SalesData&, const SalesData&);
friend std::ostream& print(std::ostream&, const SalesData&);
friend std::istream& read(std::istream&, SalesData&);

public:
	// constrctors
	SalesData() : bookNo(""), units_sold(0), revenue(0) { };
	SalesData(const string &s) : bookNo(s) { }
	SalesData(const string &s, unsigned n, double p) :
						bookNo(s), units_sold(n), revenue(n*p) {}

  // copy constructor
  SalesData(const SalesData& orig) :
    bookNo(orig.bookNo),
    units_sold(orig.units_sold),
    revenue(orig.revenue) { }

  // copy-assignment operator
  SalesData& operator= (const SalesData& rhs) {
    bookNo = rhs.bookNo;
    units_sold = rhs.units_sold;
    revenue = rhs.revenue;
    return *this;
  }  

  // deconstructor
  ~SalesData() = default;
	/*****************************************
		uncomment the following constructors to see 7.41, delegating constructor
		****************************************/
	// SalesData(const string &s, unsigned n, double p) :
	// 					bookNo(s), units_sold(n), revenue(n*p) { cout << "base level" << endl; }

	// SalesData() : SalesData("", 0, 0) { cout << "level 1" << endl;}


	SalesData(std::istream& is) {
		double price;
		is >> bookNo >> units_sold >> price;
		revenue = price * units_sold;
	}


	// interface function
	string GetIsbn() const { return this->bookNo; }
	unsigned GetUnits() const { return units_sold; }
	double GetRevenue() const { return revenue; }

	void add(unsigned n) { units_sold += n; }
	void add(double r) { revenue += r; }
	void add(unsigned n, double r) { units_sold += n; revenue += r; }
	SalesData& combine(const SalesData&);


private:
	double avg_price() const;
	string bookNo;
	unsigned units_sold;
	double revenue;	
};

/******************************************************
	the definition in class as a friend member might
	be duplicate with follow definition
	****************************************************/
// SalesData add(const SalesData&, const SalesData&);
// std::ostream& print(std::ostream&, const SalesData&);
// std::istream& read(std::istream&, SalesData&);




/******************************************************
		7.57 account class
	****************************************************/

class Account {
public:
    void calculate() { amount += amount * interestRate; }
    static double rate() { return interestRate; }
    static void rate(double newRate) { interestRate = newRate; }

    static double todayRate;
private:
    std::string owner;
    double amount;
    static double interestRate;
    // static constexpr double todayRate = 42.42;

    // static double initRate() { return todayRate; }
};


#endif
