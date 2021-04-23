#include <iterator>  //std::forward() | std::distance() | std::advance
#include <iostream> //std::cout | std::cin | 
#include <vector>  // std::vector |
#include <thread> // thread::hardware_concurrency | std::thread
#include <algorithm> // std::transform

template <typename RandomAccessIterator, typename F>
void ptransform(RandomAccessIterator begin, RandomAccessIterator end,
                        F&& f)
{
    auto size = std::distance(begin, end);
    if (size <= 10000)
    {
        std::transform (begin, end, begin, std::forward<F>(f));
    }
    else
    {
        std::vector <std::thread> threads;
        int thread_count = std::thread::hardware_concurrency(); // defien the number of threads available on this hardware
        auto first = begin;
        auto last = first;
        size /= thread_count; // define the size of the data available to put in the thread
        for (int i=0; i<thread_count; ++i)
        {
            first = last;
            if (i == thread_count -1) last = end; // if thread_count equals the number of threads:
                                                // literally "break".
            else std::advance(last, size); // moves the iterator to the certain position

            threads.emplace_back( [first, last, &f]() {
                    std::transform(first, last, first, std::forward<F>(f));
                    }); // add the transfrom function with certain number of elements ib the thread
        }

        for (auto& t : threads) t.join();
    }
}

template <typename T, typename F>
std::vector <T> palter (std::vector<T> data, F&& f)
{                                          //rvalue(double reference) -> std::forward<T>() return rvalue
    ptransform(std::begin(data), std::end(data),
            std::forward<F>(f));
    return data;
}

int main(int argc, char* argv[])
{
    std::vector <int> data (1000000);

    // initialize the vector data
    auto result = palter(data, [] (int const e) { return e * e; });
}
