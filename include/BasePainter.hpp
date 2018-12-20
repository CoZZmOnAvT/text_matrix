/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   BasePainter.hpp                                                          */
/*                                                                            */
/*   By: phrytsenko                                                           */
/*                                                                            */
/*   Created: 2018/12/18 17:42:23 by phrytsenko                               */
/*   Updated: 2018/12/20 13:23:33 by phrytsenko                               */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXT_MATRIX_CURSES_BASE_PAINTER_HPP_
#define TEXT_MATRIX_CURSES_BASE_PAINTER_HPP_

#include <functional>
#include <memory>
#include <vector>

namespace curses {

class Window;

class BasePainter {
   public:
    virtual ~BasePainter() = default;
    virtual void Draw() = 0;

    std::function<void(int, int)> ResizeHandler();

   protected:
    virtual void ResizeHandler(int new_width, int new_height) = 0;
    std::vector<std::shared_ptr<Window>> windows_;
};

}  // namespace curses

#endif  //  TEXT_MATRIX_CURSES_BASE_PAINTER_HPP_