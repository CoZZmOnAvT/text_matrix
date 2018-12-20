/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   CursesEnvironment.cpp                                                    */
/*                                                                            */
/*   By: phrytsenko                                                           */
/*                                                                            */
/*   Created: 2018/12/18 17:42:27 by phrytsenko                               */
/*   Updated: 2018/12/20 17:56:34 by phrytsenko                               */
/*                                                                            */
/* ************************************************************************** */

#include "CursesEnvironment.hpp"
#include <ncursesw/curses.h>
#include <signal.h>
#include <sys/ioctl.h>
#include "Window.hpp"
#include "BasePainter.hpp"

namespace curses {

std::vector<std::function<void(int, int)>> Environment::resize_handlers_;

Environment::Environment() : loop_(true)
{
    initscr();
    using namespace std::placeholders;
    signal(SIGWINCH, &Environment::ResizeHandler);
}

Environment::~Environment()
{
    signal(SIGWINCH, SIG_IGN);
    endwin();
}

void Environment::EnableColors() const
{
    if(has_colors() == false) {
        throw std::runtime_error("Terminal does not support colored output");
    }
    start_color();
    init_pair(color::Black, COLOR_BLACK, COLOR_BLACK);
    init_pair(color::Red, COLOR_RED, COLOR_BLACK);
    init_pair(color::Green, COLOR_GREEN, COLOR_BLACK);
    init_pair(color::Yellow, COLOR_YELLOW, COLOR_BLACK);
    init_pair(color::Blue, COLOR_BLUE, COLOR_BLACK);
    init_pair(color::Magenta, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(color::Cyan, COLOR_CYAN, COLOR_BLACK);
    init_pair(color::White, COLOR_WHITE, COLOR_BLACK);
}

void Environment::Subscribe(std::shared_ptr<BasePainter> const &painter)
{
    if (painter == nullptr) {
        throw std::runtime_error("Can't subscribe on nullptr painter");
    }
    painters_.push_back(painter);
    RegisterResizeHandler(painter->ResizeHandler());
}

void Environment::RegisterResizeHandler(std::function<void(int, int)> handler)
{
    resize_handlers_.push_back(handler);
}

void Environment::CallPainters()
{
    for (auto &painter : painters_) {
        painter->Draw();
    }
}

void Environment::BreakDispatch()
{
    loop_ = false;
}

void Environment::ResizeHandler(int)
{
    winsize term_size;

    ioctl(fileno(stdout), TIOCGWINSZ, (char *)&term_size);
    resizeterm(term_size.ws_row, term_size.ws_col);
    for (auto handler : resize_handlers_) {
        handler(term_size.ws_col, term_size.ws_row);
    }
}

}  // namespace curses
