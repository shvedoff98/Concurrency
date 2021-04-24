#include <thread>
#include <iostream>
#include <vector>
#include <future>
#include <algorithm>
#include <iterator>

template <typename Iterator, typename F>
auto pprocess(Iterator begin, Iterator end, F&& f)
{
    auto size = std::distance(begin, end);
    if (size <= 10000)
    {
        return std::forward<F>(f)(begin, end); // ???
    }
    else
    {
        int task_count = std::thread::hardware_concurrency();
        std::vector<std::future
            <typename std::iterator_traits<Iterator>::value_type>> tasks;

        auto first = begin;
        auto last = first;
        size /= task_count;
        for (int i=0; i<task_count; ++i)
        {
            first = last;
            if (i == task_count - 1) last = end;
            else std::advance(last, size);

            tasks.emplace_back(std::async(std::launch::async,
                        [first, last, &f] () {
                        return std::forward<F>(f)(first, last);
            }));
        }

        std::vector <typename std::iterator_traits<Iterator>::value_type> mins;

        for (auto& x  : tasks)
            mins.push_back(x.get());

        return std::forward<F>(f)(std::begin(mins), std::end(mins));
    }
}

template <typename Iterator>
auto pmin (Iterator begin, Iterator end)
{
    return pprocess(begin, end,
            [](auto b, auto e) { return *std::min_element(b, e);});
}

template <typename Iterator>
auto pmax (Iterator begin, Iterator end)
{
    return pprocess(begin, end,
            [](auto b, auto e) { return *std::max_element(b, e);});
}

int main(int argc, char* argv[])
{
    std::vector<int> data{1,2,3,4,5,6,7,8,9}; // initializes the data
    auto rmin = pmin(std::begin(data), std::end(data));
    auto rmax = pmax(std::begin(data), std::end(data));
    std::cout << "Max is: " << rmax << "\n";
    std::cout << "Min is: " << rmin << "\n";
}
