#ifndef Q_CLASS_H
#define Q_CLASS_H

#include <fstream>
#include <iostream>
#include <sstream>

#include <memory>
#include <map>
#include <string>
#include <vector>
#include <set>






class QueryResult {
friend std::ostream& print(const QueryResult&, std::ostream&);
public:
	using line_no = std::vector<std::string>::size_type;

	// constructor
	QueryResult(std::string s,
				std::shared_ptr<std::set<line_no>> l,
				std::shared_ptr<std::vector<std::string>> f) :
				sought(s), lines(l), file(f) {};

	QueryResult() = default;
	~QueryResult() = default;


private:
	std::string sought;
	// line_no that sought occurs
	std::shared_ptr<std::set<line_no>> lines;
	// input file
	std::shared_ptr<std::vector<std::string>> file;
};


class TextQuery {
public:
	using line_no = std::vector<std::string>::size_type;
	TextQuery() = default;
	~TextQuery() = default;


	QueryResult query(const std::string&) const;

private:
	// input file
	std::shared_ptr<std::vector<std::string>> file;
	// word : set(line_no)
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};


std::ostream& print(const QueryResult&, std::ostream&);

#endif 