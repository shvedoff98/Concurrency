#include <iostream>
#include <numeric>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>


class MyClass
{
    private:
        int a;
        int b;

    public:
        
        MyClass (int par1, int par2) 
        {
            a = par1; 
            b = par2;
        }
        
        int Sum (int& init)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            std::cout << "SUM STARTED\n";

            std::vector<int>vec;
            for (int i = a; i < b; ++i)
            {
           //     std::cout << "Sum\t" << i << "\n";
                vec.push_back (i);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(7000));
            std::cout << "SUM ENDED\n";

            return std::accumulate (vec.begin(), vec.end(), init);
        }
};

int main (int argc, char* argv[])
{
    int a, b, res;
    a = b = res = 0;

    int init = 100;
    std::cin >> a >> b;
    MyClass obj (a, b);
  //  std::thread t (&MyClass::Sum, obj);
    
    std::thread t ([&](){res = obj.Sum(init);});

 //   t.detach();

    for (int i = 0; i < 10; ++i)
    {
        std::cout << "Main\t" << i << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    t.join();

    std::cout << "result = " << res << "\n";

    return 0;
}
