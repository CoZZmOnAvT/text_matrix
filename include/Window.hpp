/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Window.hpp                                                               */
/*                                                                            */
/*   By: phrytsenko                                                           */
/*                                                                            */
/*   Created: 2018/12/18 17:42:23 by phrytsenko                               */
/*   Updated: 2018/12/20 14:47:14 by phrytsenko                               */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXT_MATRIX_CURSES_WINDOW_HPP_
#define TEXT_MATRIX_CURSES_WINDOW_HPP_

#include <ncursesw/curses.h>
#include <memory>
#include <utility>

namespace curses {

class Window {
   public:
    using low_level_pointer = std::unique_ptr<WINDOW, decltype(&delwin)>;

    Window(WINDOW *win);
    Window(int width, int height);

    void Clear();
    void Update();

    void DrawBorder();

    void DrawHorizontalLineBorder(int length);
    void DrawHorizontalLineBorder(chtype character, int length);

    void DrawHorizontalLineBorder(int x, int y, int length);
    void DrawHorizontalLineBorder(int x, int y, chtype character, int length);

    void DrawVerticalLineBorder(int length);
    void DrawVerticalLineBorder(chtype character, int length);

    void DrawVerticalLineBorder(int x, int y, int length);
    void DrawVerticalLineBorder(int x, int y, chtype character, int length);

    void SetUpBorder(chtype ls, chtype rs, chtype ts, chtype bs, chtype tl, chtype tr, chtype bl, chtype br);

    void DrawCharacter(const chtype character);
    void DrawCharacter(int x, int y, const chtype character);

    void DrawLine(std::string const &str);
    void DrawLine(int x, int y, std::string const &str);

    void Move(int x, int y);
    void Resize(int new_width, int new_height);

    std::pair<int, int> GetSize() const;
    std::pair<int, int> GetPosition() const;

   private:
    /*
     * ls - left side,
     * rs - right side,
     * ts - top side,
     * bs - bottom side,
     * tl - top left-hand corner,
     * tr - top right-hand corner,
     * bl - bottom left-hand corner, and
     * br - bottom right-hand corner.
     */
    chtype ls_, rs_, ts_, bs_, tl_, tr_, bl_, br_;
    low_level_pointer curses_win_;
};

}  // namespace curses

#endif  //  TEXT_MATRIX_CURSES_WINDOW_HPP_