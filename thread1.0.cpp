#include <string>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std; 

void process()
{
    for (size_t i = 0; i < 150; ++i)
    {
        this_thread::sleep_for(chrono::milliseconds(10));
        cout << "+";
    }
    cout << "\n";
}

int main(const int argc, const char* const argv[])
{
    thread s_th(process);

    for (size_t i = 0; i < 100; ++i)
    {
        this_thread::sleep_for(chrono::milliseconds(10));
        cout << "-";
    }
    cout << "\n";

    s_th.join();
}
