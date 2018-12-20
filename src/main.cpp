/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   main.cpp                                                                 */
/*                                                                            */
/*   By: phrytsenko                                                           */
/*                                                                            */
/*   Created: 2018/12/18 17:40:58 by phrytsenko                               */
/*   Updated: 2018/12/20 17:57:31 by phrytsenko                               */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "CursesEnvironment.hpp"
#include "MatrixPainter.hpp"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <characters_pool>" << std::endl;
        return EXIT_FAILURE;
    }

    try {
        auto curses_env = std::make_unique<curses::Environment>();
        curses_env->EnableColors();

        std::shared_ptr<curses::BasePainter> matrix_painter = std::make_shared<curses::MatrixPainter>(argv[1]);

        curses_env->Subscribe(matrix_painter);
        curses_env->Dispatch(std::chrono::milliseconds(80));
        return EXIT_SUCCESS;
    } catch (std::exception const& e) {
        std::cout << argv[0] << ": " << e.what() << std::endl;
    } catch (...) {
        std::cout << argv[0] << ": Unknown failure occurred. Possible memory corruption!" << std::endl;
    }
    return EXIT_FAILURE;
}
