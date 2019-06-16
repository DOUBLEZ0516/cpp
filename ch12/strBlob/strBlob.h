#ifndef STRBLOB_H
#define STRBLOB_H
#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <memory>
using std::shared_ptr;
using std::make_shared;
using std::weak_ptr;

#include <initializer_list>
using std::initializer_list;


#include <stdexcept>
using std::out_of_range;
using std::runtime_error;

#include <cstdlib>
using std::size_t;

class StrBlobPtr;
// StrBlobPtr::StrBlobPtr(StrBlob&, size_t);

class StrBlob {
friend class StrBlobPtr;
public:

	typedef vector<string>::size_type size_type;

	// constructors
	StrBlob();
	StrBlob(initializer_list<string> il);

	size_type size() const { return data->size(); }

	bool empty() const { return data->empty(); }

	void push_back(const string& t) { data->push_back(t); }

	void pop_back();

	string& front();
	string& front() const;
	string& back();
	string& back() const;
  StrBlobPtr begin();
  StrBlobPtr end(); 

	~StrBlob() = default;
private:
	shared_ptr<vector<string>> data;

	void check(size_type i, const string& msg) const;
};


class StrBlobPtr {
public:
  StrBlobPtr() : curr(0) { }
  StrBlobPtr(StrBlob& a, size_t sz = 0) :
            wptr(a.data), curr(sz) { }

  string& deref() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
  }

  StrBlobPtr& incre() {
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
  }


  bool operator!=(const StrBlobPtr& p) { return p.curr != curr; }

private:
  shared_ptr<vector<string>> check(size_t i, const string& msg) const {
      auto ret = wptr.lock();
      if (!ret)
        throw runtime_error("unbound StrBlobPtr");
      if ( i >= ret->size())
        throw out_of_range(msg);
      return ret;  // return a shared_ptr points to vector
    }


  weak_ptr<vector<string>> wptr;
  size_t curr;

};





#endif