#include "./textquery.h"




TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>) {
	// this function map the words and the lines it appears
	std::string text;
	while(getline(is, text)) {
		// store each line in file
		file->push_back(text);

		// extract string from each line
		std::istringstream line(text);
		int curN = file->size() - 1;
		std::string word;

		while(line >> word) {
			auto &lines = wm[word];
			if (!lines)
				// must allocate space with new
				lines.reset(new std::set<line_no>);

			lines->insert(curN);
		}


	}
}

QueryResult TextQuery::query(const std::string &sought) const {
	// if sought is not found, return a empty set noData
	static std::shared_ptr<std::set<line_no>> noData(new std::set<line_no>);
	auto loc = wm.find(sought);

	return loc == wm.end() ? QueryResult(sought, noData, file) :
							 QueryResult(sought, loc->second, file);
}

std::string make_plural(size_t ctr, const std::string &word,
						const std::string &ending) {
	return ctr > 1 ? word+ending : word;
}

std::ostream &print(std::ostream &os, const QueryResult &qr) {
	// if found words, print out times and location
	os << qr.sought << " occurs " << qr.lines->size() << " "
	   << make_plural(qr.lines->size(), "times", "s") << std::endl;

	for (auto num : *qr.lines) 
		os << "\t(line " << num+1 << ") " 
		   << *(qr.file->begin()+num) << std::endl;

	return os;
}




void runQueries(std::ifstream& infile) {
	TextQuery tq(infile);

	while (true) {
		std::cout << "Enter words to look for or q to quit: " << std::endl;
		std::string s;
		// if countered EOF or q, break
		if (!(std::cin >> s) || s == "q") break;

		print(std::cout, tq.query(s)) << std::endl;	

	}
}
