#ifndef WINDOW_H_
#define WINDOW_H_

#include <stdint.h>
#include <ncurses.h>
#include <string>

/**
 * Window objects create and manage ncurses windows.
 */
class Window
{
	public:
		/**
		 * Create a new Window with the specified width and height, at 0,0.
		 *
		 * @param width
		 * @param height
		 */
		Window(uint32_t width, uint32_t height);
		/**
		 * Create a new Window with the specified width and height at x,y.
		 *
		 * @param width
		 * @param height
		 * @param x
		 * @param y
		 */
		Window(uint32_t width, uint32_t height, uint32_t x, uint32_t y);

		/**
		 * Get the width of the Window.
		 *
		 * @return The width.
		 */
		uint32_t getWidth();
		/**
		 * Get the height of the Window.
		 *
		 * @return The height.
		 */
		uint32_t getHeight();

		/**
		 * Get the x position of the Window.
		 *
		 * @return The x coordinate.
		 */
		uint32_t getX();
		/**
		 * Get the y position of the Window.
		 *
		 * @return The y coordinate.
		 */
		uint32_t getY();

		/**
		 * Add the default border around the Window.
		 */
		void addBorder();
		/**
		 * Add the specified border characters around the Window.
		 *
		 * @param sides Left and right sides.
		 * @param topbot Top and bottom edges.
		 * @param corners The corners.
		 */
		void addBorder(char sides, char topbot, char corners);
		/**
		 * Add the specified border characters around the Window.
		 *
		 * @param left The left edge.
		 * @param right The right edge.
		 * @param top The top edge.
		 * @param bottom The bottom edge.
		 * @param topleft The top left corner.
		 * @param topright The top right corner.
		 * @param botleft The bottom left corner.
		 * @param botright The bottom right corner.
		 */
		void addBorder(char left, char right, char top, char bottom, char topleft, char topright, char botleft, char botright);

		/**
		 * Refresh the Window.
		 */
		virtual void refresh();

		/**
		 * Display the character c at the position x,y in the Window.
		 *
		 * @param x
		 * @param y
		 * @param c
		 */
		void add(uint32_t x, uint32_t y, char c);
		/**
		 * Display the string str at the position x,y in the Window.
		 *
		 * @param x
		 * @param y
		 * @param str
		 */
		void add(uint32_t x, uint32_t y, std::string str);

		/**
		 * Display the integer num at the position x,y in the Window.
		 *
		 * @param x
		 * @param y
		 * @param num
		 */
		void addInt(uint32_t x, uint32_t y, int num);

		/**
		 * Erase the character at the position x,y from the Window.
		 *
		 * @param x
		 * @param y
		 */
		void erase(uint32_t x, uint32_t y);
	protected:
		/**
		 * Window's width.
		 */
		uint32_t _width;
		/**
		 * Window's height.
		 */
		uint32_t _height;

		/**
		 * Window's x coordinate.
		 */
		uint32_t _x;
		/**
		 * Window's y coordinate.
		 */
		uint32_t _y;

		/**
		 * Pointer to the Window's ncurses object.
		 */
		WINDOW* _win;
};

#endif
