/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   MatrixPainter.hpp                                                        */
/*                                                                            */
/*   By: phrytsenko                                                           */
/*                                                                            */
/*   Created: 2018/12/18 17:42:23 by phrytsenko                               */
/*   Updated: 2018/12/20 14:46:54 by phrytsenko                               */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXT_MATRIX_CURSES_MATRIX_PAINTER_HPP_
#define TEXT_MATRIX_CURSES_MATRIX_PAINTER_HPP_

#include <random>
#include <string>
#include <vector>
#include "BasePainter.hpp"

namespace curses {

class MatrixPainter : public BasePainter {
   public:
    MatrixPainter(std::string const& pool);

    void Draw();

   private:
    std::string characters_pool_;
    std::mt19937 random_engine_;
    std::uniform_int_distribution<uint32_t> random_index_;
    std::vector<std::string> buffer_;

    void ResizeHandler(int new_width, int new_height) override;
    void ResizeMatrix(int new_width, int new_height);
    void Step();
};

}  // namespace curses

#endif  //  TEXT_MATRIX_CURSES_MATRIX_PAINTER_HPP_