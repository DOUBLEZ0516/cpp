#ifndef WINDOW_MGR_H
#define WINDOW_MGR_H


#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

class WindowMgr;
class Screen;


class WindowMgr {

public:
	using ScreenIndex = vector<Screen>::size_type;
	vector<Screen> GetScreens() const { return screens; }

	void clear(ScreenIndex);

	ScreenIndex addScreen(const Screen&);

private:
	// vector<Screen> screens{Screen(24, 80, ' ')};
  vector<Screen> screens;
};




class Screen {

public:
	typedef string::size_type pos; // defined in public to access outside class


	// friends
	friend class WindowMgr;
	
	// to use a member function as a friend, be sure it has been declared
	// friend void WindowMgr::clear(WindowMgr::ScreenIndex);


	// constructors
	Screen() = default;
	Screen(pos ht, pos wd) : height(ht), width(wd), contents(ht*wd, ' ') {}
	Screen(pos ht, pos wd, char c) : height(ht), width(wd), contents(ht*wd, c) {}


	char get() const { return contents[cursor]; } // implicit inline

	inline char get(pos, pos) const;				 // explicit inline

	inline Screen& move(pos, pos);                    // can be defined as inline in definition elsewhere

 	 
  Screen& set(char);
  Screen& set(pos, pos, char);

	// interface
	pos GetHeight() const { return height; }

	Screen& display(std::ostream& os) {
		do_display(os); return *this; 
	}
	const Screen& display(std::ostream& os) const {
		do_display(os); return *this; 
	}

	// for example of mutable variable
	void some_member() const { ++access_ctr; }
	size_t GetCtr() const { return access_ctr; }

private:
	pos cursor = 0;
	pos height = 0;
	pos width  = 0;
	string contents;
	mutable size_t access_ctr = 0;  // can be modified in a const member function

	void do_display(std::ostream& os) const { os << contents; }
};




// inline function should be defined in header
inline Screen& Screen::move(pos r, pos c) {
	pos row = r * width;
	cursor = row + c;
	return *this;
}         













/* ******************************************************************** */
// class X & Y from text book
struct X;
struct Y;

struct X {
public:
	Y* yptr;
};

struct Y {
public:
	X* xptr;
};

#endif