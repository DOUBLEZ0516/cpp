#include "sales_data.h"


SalesData& SalesData::combine(const SalesData& data) {
	units_sold += data.units_sold;
	revenue += data.revenue;
	return *this;	
}


inline
double SalesData::avg_price() const {
	if (units_sold)
		return revenue / units_sold;
	else
		return 0;
}



SalesData add(const SalesData& lhs, const SalesData& rhs) {
	SalesData newData = lhs;
	return newData.combine(rhs);
}

std::ostream& print(std::ostream& os, const SalesData& data) {
	os << "isbn: " << data.bookNo << endl
		 << "units sold: " << data.units_sold << endl
		 << "avg price: ";

	if (data.avg_price() != 0.0)
		os << data.avg_price() << endl;
	else
		os << "non record" << endl;

	return os;
}



std::istream& read(std::istream& is, SalesData& data) {
	double price;
	is >> data.bookNo >> data.units_sold >> price;
	data.revenue = price * data.units_sold;
	return is;
}

double Account::todayRate = 0.1; 
double Account::interestRate = 0.05;