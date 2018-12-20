/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   CursesEnvironment.hpp                                                    */
/*                                                                            */
/*   By: phrytsenko                                                           */
/*                                                                            */
/*   Created: 2018/12/18 17:42:23 by phrytsenko                               */
/*   Updated: 2018/12/20 17:55:34 by phrytsenko                               */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXT_MATRIX_CURSES_ENVIRONMENT_HPP_
#define TEXT_MATRIX_CURSES_ENVIRONMENT_HPP_

#include <atomic>
#include <chrono>
#include <functional>
#include <memory>
#include <thread>
#include <vector>

namespace curses {

namespace color {
    constexpr const short Black = 0;
    constexpr const short Red = 1;
    constexpr const short Green = 2;
    constexpr const short Yellow = 3;
    constexpr const short Blue = 4;
    constexpr const short Magenta = 5;
    constexpr const short Cyan = 6;
    constexpr const short White = 7;
}

class BasePainter;

class Environment {
   public:
    Environment();
    ~Environment();

    void EnableColors() const;

    void Subscribe(std::shared_ptr<BasePainter> const& painter);
    void RegisterResizeHandler(std::function<void(int, int)> handler);
    void CallPainters();

    template <class Rep, class Period>
    void Dispatch(const std::chrono::duration<Rep, Period>& sleep_duration)
    {
        while (loop_) {
            CallPainters();
            std::this_thread::sleep_for(sleep_duration);
        }
    }

    void BreakDispatch();

   private:
    std::atomic<bool> loop_;
    static void ResizeHandler(int);

    static std::vector<std::function<void(int, int)>> resize_handlers_;
    std::vector<std::shared_ptr<BasePainter>> painters_;
};

}  // namespace curses

#endif  //  TEXT_MATRIX_CURSES_ENVIRONMENT_HPP_