#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <numeric>


int DoWork (int a, int b)
{
    std::vector <int> result;
    for (a; a<=b; ++a)
    {
        std::cout << "DoWork\t" << a << "\n";
        result.push_back (a);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return std::accumulate (result.begin(), result.end(), 0);
}

int main (int argc, char* argv[])
{
    int result = 0;
    std::thread t ([&result](){result = DoWork (0, 9); });
    t.join();

    for (int i = 0; i < 10; ++i)
    {
        std::cout << "Main\t" << i << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "result=" << result << "\n";
}
