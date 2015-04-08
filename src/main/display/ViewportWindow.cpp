#include <ncurses.h>

#include "display/ViewportWindow.h"

ViewportWindow::ViewportWindow(uint32_t win_width, uint32_t win_height,
	uint32_t view_width, uint32_t view_height) : Window(win_width, win_height)
{
	//Save viewport's height and width for later
	_view_width = view_width;
	_view_height = view_height;

	//Initialize our x and y values
	//NB: Probably don't have to do this, as Window does it, but can't hurt.
	_x = 0;
	_y = 0;

	//Create our viewport
	_view = subwin(_win, _view_height, _view_width, _y, _x);
}

ViewportWindow::ViewportWindow(uint32_t win_width, uint32_t win_height,
	uint32_t view_width, uint32_t view_height,
	uint32_t view_x, uint32_t view_y) : Window(win_width, win_height)
{
	//Save viewport's height and width for later
	_view_width = view_width;
	_view_height = view_height;

	//Initialize our x and y values
	_x = view_x;
	_y = view_y;

	//Create our viewport
	_view = subwin(_win, _view_height, _view_width, _y, _x);
}

uint32_t ViewportWindow::getViewWidth()
{
	return _view_width;
}

uint32_t ViewportWindow::getViewHeight()
{
	return _view_height;
}

void ViewportWindow::refresh()
{
	//Refresh the viewport, not the parent window.
	//Refreshing the parent window would cause it to be displayed on the screen,
	//much to the dismay of everything and everyone!
	wrefresh(_view);
}

void ViewportWindow::move(uint32_t x, uint32_t y)
{
	//Make sure our viewport won't leave our window's boundaries.
	//Don't need to check lower bounds because we're using uints.
	if(x < _width - _view_width && y < _height - _view_height)
	{
		//Move the viewport relative to the window.
		mvderwin(_view, y, x);
	}
}
