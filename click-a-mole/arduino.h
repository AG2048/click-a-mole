#ifndef ARDUINO
#define ARDUINO
#include <chrono>

inline unsigned long millis()
{
    static auto start = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
    return static_cast<unsigned long>(elapsed);
}
#endif // ARDUINO