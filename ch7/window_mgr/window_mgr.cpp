#include "window_mgr.h"


/*****************************************************************************
												Screen member function
*****************************************************************************/


char Screen::get(pos r, pos c) const {
	pos row = r * width;
	return contents[row + c];  
}

  
Screen& Screen::set(char c) {
	contents[cursor] = c;
	return *this;
}

Screen& Screen::set(pos row, pos col, char c) {
	contents[row*width + col] = c;
	return *this;
}







/*****************************************************************************
											WindowMgr member function
*****************************************************************************/
void WindowMgr::clear(ScreenIndex i) {
	Screen& s = screens[i];
	s.contents = string(s.height * s.width, ' ');
}


WindowMgr::ScreenIndex WindowMgr::addScreen(const Screen& s) {
	screens.push_back(s);	
	return screens.size()-1;
}