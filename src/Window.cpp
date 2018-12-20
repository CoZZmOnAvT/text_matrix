/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Window.cpp                                                               */
/*                                                                            */
/*   By: phrytsenko                                                           */
/*                                                                            */
/*   Created: 2018/12/18 17:42:27 by phrytsenko                               */
/*   Updated: 2018/12/20 17:52:19 by phrytsenko                               */
/*                                                                            */
/* ************************************************************************** */

#include "Window.hpp"
#include <string>

namespace curses {

Window::Window(WINDOW *win) : curses_win_(win, nullptr)
{
    if (curses_win_ == nullptr) {
        throw std::runtime_error("Nullptr window");
    }
}

Window::Window(int width, int height) : curses_win_(newwin(height, width, 0, 0), &delwin)
{
    if (curses_win_ == nullptr) {
        throw std::runtime_error("Unable create the window");
    }
}

void Window::Clear()
{
    if (werase(curses_win_.get()) == ERR) {
        throw std::runtime_error("Unable clear the window");
    }
}

void Window::Update()
{
    if (wrefresh(curses_win_.get()) == ERR) {
        throw std::runtime_error("Unable update the window");
    }
}

void Window::ColorOn(short color)
{
    if (wattron(curses_win_.get(), COLOR_PAIR(color)) == ERR) {
        throw std::runtime_error("Unable to turn on color");
    }
}

void Window::ColorOff(short color)
{
    if (wattroff(curses_win_.get(), COLOR_PAIR(color)) == ERR) {
        throw std::runtime_error("Unable to turn off color");
    }
}

void Window::DrawBorder()
{
    if (wborder(curses_win_.get(), ls_, rs_, ts_, bs_, tl_, tr_, bl_, br_) == ERR) {
        throw std::runtime_error("Unable draw the border");
    }
}

void Window::DrawHorizontalLineBorder(int length)
{
    DrawHorizontalLineBorder(0, length);
}

void Window::DrawHorizontalLineBorder(chtype character, int length)
{
    if (whline(curses_win_.get(), character, length) == ERR) {
        throw std::runtime_error("Unable draw the horizontal line border");
    }
}

void Window::DrawHorizontalLineBorder(int x, int y, int length)
{
    DrawHorizontalLineBorder(x, y, 0, length);
}

void Window::DrawHorizontalLineBorder(int x, int y, chtype character, int length)
{
    if (mvwhline(curses_win_.get(), y, x, character, length) == ERR) {
        throw std::runtime_error("Unable draw the horizontal line border");
    }
}

void Window::DrawVerticalLineBorder(int length)
{
    DrawVerticalLineBorder(0, length);
}

void Window::DrawVerticalLineBorder(chtype character, int length)
{
    if (wvline(curses_win_.get(), character, length) == ERR) {
        throw std::runtime_error("Unable draw the vertical line border");
    }
}

void Window::DrawVerticalLineBorder(int x, int y, int length)
{
    DrawVerticalLineBorder(x, y, 0, length);
}

void Window::DrawVerticalLineBorder(int x, int y, chtype character, int length)
{
    if (mvwvline(curses_win_.get(), y, x, character, length) == ERR) {
        throw std::runtime_error("Unable draw the vertical line border");
    }
}

void Window::SetUpBorder(chtype ls, chtype rs, chtype ts, chtype bs, chtype tl, chtype tr, chtype bl, chtype br)
{
    ls_ = ls, rs_ = rs, ts_ = ts, bs_ = bs, tl_ = tl, tr_ = tr, bl_ = bl, br_ = br;
}

void Window::DrawCharacter(const chtype character)
{
    if (waddch(curses_win_.get(), character) == ERR) {
        throw std::runtime_error("Unable draw the character");
    }
}

void Window::DrawCharacter(int x, int y, const chtype character)
{
    if (mvwaddch(curses_win_.get(), y, x, character) == ERR) {
        throw std::runtime_error("Unable draw the character");
    }
}

void Window::DrawLine(std::string const &str)
{
    if (wprintw(curses_win_.get(), str.c_str()) == ERR) {
        throw std::runtime_error("Unable draw the line");
    }
}

void Window::DrawLine(int x, int y, std::string const &str)
{
    if (mvwprintw(curses_win_.get(), y, x, str.c_str()) == ERR) {
        throw std::runtime_error("Unable draw the line");
    }
}

void Window::Move(int x, int y)
{
    if (mvwin(curses_win_.get(), y, x) == ERR) {
        throw std::runtime_error("Unable move the window to: " + std::to_string(x) + ";" + std::to_string(y));
    }
}

void Window::Resize(int new_width, int new_height)
{
    if (wresize(curses_win_.get(), new_height, new_width) == ERR) {
        throw std::runtime_error("Unable resize the window to: " + std::to_string(new_width) + "x" +
                                 std::to_string(new_height));
    }
}
std::pair<int, int> Window::GetSize() const
{
    int height, width;

    if (getmaxyx(curses_win_.get(), height, width) == ERR) {
        throw std::runtime_error("Unable get the window size");
    }
    return {width, height};
}

std::pair<int, int> Window::GetPosition() const
{
    int y, x;

    if (getyx(curses_win_.get(), y, x) == ERR) {
        throw std::runtime_error("Unable get the window position");
    }
    return {x, y};
}

}  // namespace curses
