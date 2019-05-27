#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H

#include <fstream>
#include <iostream>
#include <string>


class QueryResult;

class TextQuery {
public:
	using line_no = sdtd::vector<std::string>::size_type;
	// constractor
	TextQuery(std::ifstream& is);

	QueryResult query(const std::string&) const;

private:
	std::shared_ptr<std::vector<std::string>> file; // input file
	// word map
	std::map<std::string, std::shard_ptr<std::set<line_no>>> wm;
};


class QueryResult {
public:

private:

};


void runQueries(ifstream& infile) {
	TextQuery tq(infile);

	while (true) {
		std::cout << "Enter words to look for or q to quit: " << std::endl;
		string s;
		// if countered EOF or q, break
		if (!(std::cin >> s) || s == "q") break;

		print(std::cout, tq.query(s)) << std::endl;	

	}
}





#endif
