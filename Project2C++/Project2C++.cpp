#include <iostream>
#include <vector>
#include <functional>

#include <execution>
#include <algorithm>
#include <numeric>

#include <chrono>
#include <format>
#include <cmath>

using namespace std;

template <class F>
void timeit(F&& f)
{
    auto time1 = chrono::system_clock::now();
    f();
    auto time2 = chrono::system_clock::now();
    auto tdiff = time2 - time1;
        cout << format("{:%S}", tdiff);
        cout << " sec" << endl;
}

template <class F>
void timeit(F&& f, int repeat)
{
    auto time1 = chrono::system_clock::now();
    while (repeat--)
        f();
    auto time2 = chrono::system_clock::now();
    auto tdiff = time2 - time1;
        cout << format("{:%S}", tdiff);
        cout << " sec" << endl;
}


template <typename ExecutionPolicy, typename T>
T minimum(ExecutionPolicy policy, T begin, T end, long long n)
{
    std::vector<T> numbers;
    double step = static_cast<double>(end - begin) / static_cast<double>(n - 1);

    for (int i = 0; i < n; i++) {
        numbers.push_back(begin + i * step);
    }

    if (numbers.empty()) {
        return T();
    }

    T min = numbers[0];

    for (int i = 1; i < numbers.size(); i++) {
        if (numbers[i] < min) {
            min = numbers[i];
        }
    }

    return min;
}


template <typename T>
T minimum_nopolicy(T begin, T end, long long n)
{
    std::vector<T> numbers;
    double step = static_cast<double>(end - begin) / static_cast<double>(n - 1);

    for (int i = 0; i < n; i++) {
        numbers.push_back(begin + i * step);
    }

    if (numbers.empty()) {
        return T();
    }

    T min = numbers[0];

    for (int i = 1; i < numbers.size(); i++) {
        if (numbers[i] < min) {
            min = numbers[i];
        }
    }

    return min;
}

vector<int> getNumbers(int begin, int end, int inc = 1)
{
    vector<int> numbers;
    if (inc > 0)
        for (int i = begin; i < end; i += inc)
        {
            numbers.push_back(i);
           // cout << i << " ";
        }
    else
        for (int i = begin; i > end; i += inc)
        {
            numbers.push_back(i);
           // cout << i << " ";
        }

    return numbers;
}

std::vector<long long> getLongLong(long long begin, long long count, long step = 1)
{
    std::vector<long long> numbers(count);
    for (auto& el : numbers)
    {
        el = begin;
        begin += step;
    }
    return numbers;
}

template <class Iterable>
void print(Iterable&& it)
{
    for (const auto& i : it)
        cout << i << " ";
    cout << endl;
}

void demo1()
{
    cout << "\n\nDEMO 1" << endl;
    auto numbers = getNumbers(25, -10, -1);
    int cnt = 1;
    int min = numbers[0];
    cout << "no policy" << endl;
    timeit(
        [&numbers, &min]()
        {
            for_each(numbers.begin(), numbers.end(),
            [&min](int x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << min<<endl;

    cout << "sequental" << endl;
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::seq, numbers.begin(), numbers.end(),
            [&min](int x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << min << endl;

    cout << "parallel" << endl;
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::par, numbers.begin(), numbers.end(),
            [&min](int x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << min << endl;


    cout << "unseq" << endl; // SIMD
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::unseq, numbers.begin(), numbers.end(),
            [&min](int x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << min << endl;


    cout << "parallel unseq" << endl;
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::par_unseq, numbers.begin(), numbers.end(),
            [&min](int x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << min << endl;
}

void demo2()
{
    cout << "\n\nDEMO 2" << endl;
    auto numbers = getNumbers(5000, -1000, -2);
    int cnt = 1;
    int min = numbers[0];
    cout << "no policy" << endl;
    timeit(
        [&numbers, &min]()
        {
            for_each(numbers.begin(), numbers.end(),
            [&min](int x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << min << endl;

    cout << "sequental" << endl;
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::seq, numbers.begin(), numbers.end(),
            [&min](int x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << min << endl;

    cout << "parallel" << endl;
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::par, numbers.begin(), numbers.end(),
            [&min](int x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << min << endl;


    cout << "unseq" << endl; // SIMD
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::unseq, numbers.begin(), numbers.end(),
            [&min](int x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << min << endl;


    cout << "parallel unseq" << endl;
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::par_unseq, numbers.begin(), numbers.end(),
            [&min](int x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << min << endl;
}

void demo3()
{
    cout << "\n\nDEMO 3" << endl;
    auto numbers = getNumbers(50000000, 0, -1);
    int cnt = 1;
    int min = numbers[0];
    cout << "no policy" << endl;
    timeit(
        [&numbers, &min]()
        {
            for_each(numbers.begin(), numbers.end(),
            [&min](int x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << min << endl;

    cout << "sequental" << endl;
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::seq, numbers.begin(), numbers.end(),
            [&min](int x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << min << endl;

    cout << "parallel" << endl;
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::par, numbers.begin(), numbers.end(),
            [&min](int x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << min << endl;


    cout << "unseq" << endl; // SIMD
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::unseq, numbers.begin(), numbers.end(),
            [&min](int x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << min << endl;


    cout << "parallel unseq" << endl;
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::par_unseq, numbers.begin(), numbers.end(),
            [&min](int x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << min << endl;
}

void demo4()
{
    cout << "\n\nDEMO 4" << endl;
    auto numbers = getLongLong(50000000000, 10, -1);
    int cnt = 1;
    long long min = numbers[0];
    cout << "no policy" << endl;
    timeit(
        [&numbers, &min]()
        {
            for_each(numbers.begin(), numbers.end(),
            [&min](long long x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << min << endl;

    cout << "sequental" << endl;
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::seq, numbers.begin(), numbers.end(),
            [&min](long long x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << min << endl;

    cout << "parallel" << endl;
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::par, numbers.begin(), numbers.end(),
            [&min](long long x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << min << endl;


    cout << "unseq" << endl; // SIMD
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::unseq, numbers.begin(), numbers.end(),
            [&min](long long x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << min << endl;


    cout << "parallel unseq" << endl;
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::par_unseq, numbers.begin(), numbers.end(),
            [&min](long long x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << min << endl;
}


int main()
{
    //demo1a();
    //demo1b();
    demo1();
    demo2();
    demo3();
    demo4();
}