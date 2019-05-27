#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>


class QueryResult;

class TextQuery {
public:
	using line_no = std::vector<std::string>::size_type;
	// constractor
	TextQuery(std::ifstream& is);

	QueryResult query(const std::string&) const;

private:
	std::shared_ptr<std::vector<std::string>> file; // input file
	// word map: word : line_no
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};


class QueryResult {
public:
	using line_no = std::vector<std::string>::size_type;

private:
	std::string sought; // word to look for
	std::shared_ptr<std::set<line_no>> lines; // line_no that sought occurs
	std::shared_ptr<std::vector<std::string>> file; // input file

};


void runQueries(std::ifstream& infile) {
	TextQuery tq(infile);

	while (true) {
		std::cout << "Enter words to look for or q to quit: " << std::endl;
		std::string s;
		// if countered EOF or q, break
		if (!(std::cin >> s) || s == "q") break;

		// print(std::cout, tq.query(s)) << std::endl;	

	}
}





#endif
