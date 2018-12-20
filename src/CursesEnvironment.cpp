/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   CursesEnvironment.cpp                                                    */
/*                                                                            */
/*   By: phrytsenko                                                           */
/*                                                                            */
/*   Created: 2018/12/18 17:42:27 by phrytsenko                               */
/*   Updated: 2018/12/20 14:32:47 by phrytsenko                               */
/*                                                                            */
/* ************************************************************************** */

#include "CursesEnvironment.hpp"
#include <ncursesw/curses.h>
#include <signal.h>
#include <sys/ioctl.h>
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
