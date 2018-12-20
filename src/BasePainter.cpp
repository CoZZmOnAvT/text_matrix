/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   BasePainter.cpp                                                          */
/*                                                                            */
/*   By: phrytsenko                                                           */
/*                                                                            */
/*   Created: 2018/12/18 17:42:27 by phrytsenko                               */
/*   Updated: 2018/12/20 13:23:27 by phrytsenko                               */
/*                                                                            */
/* ************************************************************************** */

#include "BasePainter.hpp"
#include "Window.hpp"

namespace curses {

std::function<void(int, int)> BasePainter::ResizeHandler()
{
    using namespace std::placeholders;
    return std::bind(static_cast<void (BasePainter::*)(int, int)>(&BasePainter::ResizeHandler), this, _1, _2);
}

}  // namespace curses
