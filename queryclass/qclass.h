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
#include <algorithm>



/*
definition of query functions from text query
*/
class QueryResult {
friend std::ostream& print(const QueryResult&, std::ostream&);
public:
	using line_no = std::vector<std::string>::size_type;

	// constructor
	QueryResult(std::string s,
				std::shared_ptr<std::set<line_no>> l,
				std::shared_ptr<std::vector<std::string>> f) :
				sought(s), lines(l), file(f) {}

	QueryResult() = default;
	~QueryResult() = default;



	std::shared_ptr<std::vector<std::string>> get_file() const
								{return this->file;} 

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
	TextQuery(std::ifstream &);
	~TextQuery() = default;

	// find result
	QueryResult query(const std::string&) const;


private:
	// input file
	std::shared_ptr<std::vector<std::string>> file;
	// word : set(line_no)
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};


std::ostream& print(const QueryResult&, std::ostream&);


/*
Definition of query class
*/

// abstract base class, all memebers are private
class Query_base {
	// interface class
	friend class Query; 

	protected:
		using line_no = TextQuery::line_no;
		virtual ~Query_base() = default;

	private:
		// eval: returns the QueryResult matches current  Query
		virtual QueryResult eval(const TextQuery&) const = 0; // pure virtual func

		// rep: represent a string to look for
		virtual std::string rep() const = 0;	
};


class Query {
	// following friends need to access constructor that accept
	// shared_ptr, and such function is private
	friend Query operator~ (const Query&);
	friend Query operator| (const Query&, const Query&);
	friend Query operator& (const Query&, const Query&);

	public:
		// constructor
		Query(const std::string&); // construct a new WordQuery

		// interface function, call conresponding Query_base methods
		QueryResult eval(const TextQuery &t) const {return q->eval(t);}
		std::string rep() const {return q->rep();}
		// private constructor
		Query(std::shared_ptr<Query_base> query) : q(query) { }
		std::shared_ptr<Query_base> q;
};


// Query output operator 
std::ostream& operator<<(std::ostream &os, const Query &query) {
	return os << query.rep();
} 


class WordQuery : public Query_base {
	// allow Query to use WordQuery's constructor and privates
	friend class Query;
public:
	// constructor
	WordQuery(const std::string &s) : query_word(s) { }

	QueryResult eval(const TextQuery &t) const
					{return t.query(query_word);}

	std::string rep() const {return query_word;}

private:
	// words to lookup
	std::string query_word;
};


class NotQuery : public Query_base {
	friend Query operator~ (const Query &);
public:
	// constructor
	NotQuery(const Query &q) : query(q) { }

	QueryResult eval(const TextQuery&) const;
	std::string rep() const {return "~(" + query.rep() + ")";}

	Query query;
};



class BinaryQuery : public Query_base {
protected:
	// constructor
	BinaryQuery(const Query &l, const Query &r, std::string s) :
				lhs(l), rhs(r), opSym(s) {}

	std::string rep() const {
		return "(" + lhs.rep() + " " + opSym + " "
				+ rhs.rep() + ")";
	}

	// eval function is not required in this class

    // Query candidate
    Query lhs, rhs;
    // name of operand
    std::string opSym;
};



class AndQuery : public BinaryQuery {
	friend Query operator& (const Query&, const Query&);
public:
	// constructor
	AndQuery(const Query &left, const Query &right) :
			BinaryQuery(left, right, "&") { }

	QueryResult eval(const TextQuery&) const;
};


class OrQuery : public BinaryQuery {
	friend Query operator| (const Query&, const Query&);
public:
	// constructor
	OrQuery(const Query &left, const Query &right) :
			BinaryQuery(left, right, "|") { }

	QueryResult eval(const TextQuery&) const;
};


inline
Query::Query(const std::string &s) : q(new WordQuery(s)) { }


Query operator~ (const Query &operand) {
	return std::shared_ptr<Query_base> (new NotQuery(operand));
}


Query operator& (const Query &lhs, Query &rhs) {
	return std::shared_ptr<Query_base> (new AndQuery(lhs, rhs));
}


Query operator| (const Query &lhs, Query &rhs) {
	return std::shared_ptr<Query_base> (new OrQuery(lhs, rhs)); 
}




#endif 