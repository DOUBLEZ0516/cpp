#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <sstream>


class QueryResult;


class TextQuery {
public:
	using line_no = std::vector<std::string>::size_type;
	// constractor
	TextQuery(std::ifstream& is);

	//
	QueryResult query(const std::string&) const;

private:
	std::shared_ptr<std::vector<std::string>> file; // input file
	// word map: word : line_no
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};


class QueryResult {
friend std::ostream& print(std::ostream&, const QueryResult&);

public:

	using line_no = std::vector<std::string>::size_type;
	// constructor
	QueryResult(std::string s,
		std::shared_ptr<std::set<line_no>> p,
		std::shared_ptr<std::vector<std::string>> f) :
		sought(s), lines(p), file(f) { };

private:
	std::string sought; // word to look for
	std::shared_ptr<std::set<line_no>> lines; // line_no that sought occurs
	std::shared_ptr<std::vector<std::string>> file; // input file

};






#endif
