/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   MatrixPainter.cpp                                                        */
/*                                                                            */
/*   By: phrytsenko                                                           */
/*                                                                            */
/*   Created: 2018/12/18 17:42:27 by phrytsenko                               */
/*   Updated: 2018/12/20 14:46:59 by phrytsenko                               */
/*                                                                            */
/* ************************************************************************** */

#include "MatrixPainter.hpp"
#include "Window.hpp"

namespace curses {

MatrixPainter::MatrixPainter(std::string const& pool)
    : characters_pool_(pool), random_engine_(1729), random_index_(0, characters_pool_.length() - 1)
{
    windows_.push_back(std::make_shared<Window>(stdscr));
    auto win_size = windows_[0]->GetSize();
    ResizeMatrix(win_size.first, win_size.second);
}

void MatrixPainter::Step()
{
    for (auto& line : buffer_) {
        line.insert(line.begin(), characters_pool_[random_index_(random_engine_)]);
        line.pop_back();
    }
}

void MatrixPainter::Draw()
{
    auto& win = windows_[0];
    int line_num = 0;

    win->Clear();
    Step();
    for (auto const& line : buffer_) {
        win->DrawLine(0, line_num++, line);
    }
    win->Update();
}

void MatrixPainter::ResizeMatrix(int new_width, int new_height)
{
    buffer_.resize(new_height);
    for (auto& line : buffer_) {
        line.resize(new_width - 1);
    }
}

void MatrixPainter::ResizeHandler(int new_width, int new_height)
{
    windows_[0]->Resize(new_width, new_height);
    ResizeMatrix(new_width, new_height);
}

}  // namespace curses
