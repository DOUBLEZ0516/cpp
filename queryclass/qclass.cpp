#include "qclass.h"



void remove_punct(std::string &s) {
	for (int i=0, len=s.size(); i<len; i++) {
		if (ispunct(s[i])) {
			s.erase(i--,1);
			len = s.size();
		}
	}
}


TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>) {
	std::string line;

	while(getline(is, line)) {
		(*file).push_back(line);


		auto size = (*file).size() - 1;

		std::istringstream words(line);
		std::string word;
		while(words >> word) {
			remove_punct(word);
			auto &lines = wm[word];

			if (not lines)
				lines.reset(new std::set<line_no>);

			(*lines).insert(size);
		}
	}	
}

QueryResult TextQuery::query(const std::string& sought) const {
	static std::shared_ptr<std::set<line_no>> noData(new std::set<line_no>);
	auto loc = wm.find(sought);

	return loc == wm.end() ? QueryResult(sought, noData, file) :
							 QueryResult(sought, loc->second, file);


}


std::string make_plural(size_t ctr,
						const std::string &word,
						const std::string &ending) {
	return ctr > 1 ? word + ending : word;
}

std::ostream &print(std::ostream &os, const QueryResult &qr) {
	os << qr.sought << " occurs " << qr.lines->size() << " " 
	   << make_plural(qr.lines->size(), "time", "s") << std::endl;


	for (auto num : *qr.lines)
		os << "\t(line " << num+1 << ")"
		   << *(qr.file->begin()+num) << std::endl;

	return os;
}


void runQueries(std::ifstream& infile) {
	TextQuery tq(infile);

	while(true) {
		std::cout << "Enter words to look for or q to quit" << std::endl;

		std::string s;
		if(!(std::cin >> s) || s == "q") break;
		else {

			QueryResult result = (Query("Alice")| Query("hair")).eval(tq);
			print(std::cout, result) << std::endl;

			result = (~Query("Alice")).eval(tq);
			print(std::cout, result) << std::endl;

			result = (Query("fiery") & Query("bird") | Query("wind")).eval(tq);
			print(std::cout, result) << std::endl;
		}
	}
}





// implementation fo eval
QueryResult OrQuery::eval(const TextQuery& text) const {
	auto left = lhs.eval(text), right = rhs.eval(text);

	// copy result from left into result set
	auto ret_lines =
			std::make_shared<std::set<line_no>> (left.lines->begin(), left.lines->end());
	// insert right results
	ret_lines->insert(right.lines->begin(), right.lines->end());

	return QueryResult(rep(), ret_lines, left.get_file());
}





QueryResult AndQuery::eval(const TextQuery& text) const {
	auto left = lhs.eval(text), right = rhs.eval(text);
	auto ret_lines = std::make_shared<std::set<line_no>> ();

	set_intersection(left.lines->begin(), left.lines->end(),
					 right.lines->begin(), right.lines->end(),
					 inserter(*ret_lines, ret_lines->begin()));

	return QueryResult(rep(), ret_lines, left.get_file());
}


QueryResult NotQuery::eval(const TextQuery& text) const {
	auto result = query.eval(text);

	auto ret_lines = std::make_shared<std::set<line_no>> ();

	auto beg = result.lines->begin(), end = result.lines->end();

	auto sz = result.get_file() -> size();
	for (size_t n=0; n != sz; ++n) {
		if (beg == end || *beg != n)
			ret_lines->insert(n);
		else if (beg != end)
			++beg;
	}

	return QueryResult(rep(), ret_lines, result.get_file());
}








