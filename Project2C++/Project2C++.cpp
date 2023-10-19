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

vector<float> getFloats(float begin, long long count, float step = 0.1)
{
    vector<float> numbers(count);
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

void demo1a()
{
    cout << "\n\nDEMO 1a" << endl;
    auto numbers = getNumbers(25, 0, -1);
    int cnt = 1;
    cout << "\nVector traversal using different policies" << endl;

    cout << "no policy" << endl;
    timeit(
        [&numbers]()
        { minimum_nopolicy(numbers.begin(), numbers.end(), numbers.size()); },
        cnt);
    // cout << endl;

    cout << "sequental" << endl;
    timeit(
        [&numbers]()
        { minimum(execution::seq, numbers.begin(), numbers.end(), numbers.size()); },
        cnt);
    // cout << endl;

    cout << "parallel" << endl;
    timeit(
        [&numbers]()
        { minimum(execution::par, numbers.begin(), numbers.end(), numbers.size()); },
        cnt);
    // cout << endl;

    cout << "unseq" << endl; // SIMD
    timeit(
        [&numbers]()
        { minimum(execution::unseq, numbers.begin(), numbers.end(), numbers.size()); },
        cnt);
    // cout << endl;

    cout << "parallel unseq" << endl;
    timeit(
        [&numbers]()
        { minimum(execution::par_unseq, numbers.begin(), numbers.end(), numbers.size()); },
        cnt);
    // cout << endl;
}

void demo1b()
{
    cout << "\n\nDEMO 1b" << endl;
    auto numbers = getNumbers(1000, 0, -1);
    int cnt = 1;
    cout << "\nVector traversal using different policies" << endl;

    cout << "no policy" << endl;
    timeit(
        [&numbers]()
        { minimum_nopolicy(numbers.begin(), numbers.end(), numbers.size()); },
        cnt);
    // cout << endl;

    cout << "sequental" << endl;
    timeit(
        [&numbers]()
        { minimum(execution::seq, numbers.begin(), numbers.end(), numbers.size()); },
        cnt);
    // cout << endl;

    cout << "parallel" << endl;
    timeit(
        [&numbers]()
        { minimum(execution::par, numbers.begin(), numbers.end(), numbers.size()); },
        cnt);
    // cout << endl;

    cout << "unseq" << endl; // SIMD
    timeit(
        [&numbers]()
        { minimum(execution::unseq, numbers.begin(), numbers.end(), numbers.size()); },
        cnt);
    // cout << endl;

    cout << "parallel unseq" << endl;
    timeit(
        [&numbers]()
        { minimum(execution::par_unseq, numbers.begin(), numbers.end(), numbers.size()); },
        cnt);
    // cout << endl;
}

void demo2()
{
    cout << "\n\nDEMO 2" << endl;
    auto numbers = getNumbers(100000, 0, -1);
    int cnt = 1;

    cout << "no policy" << endl;
    timeit(
        [&numbers]()
        { minimum_nopolicy(numbers.begin(), numbers.end(), numbers.size()); },
        cnt);
    // cout << endl;

    cout << "sequental" << endl;
    timeit(
        [&numbers]()
        { minimum(execution::seq, numbers.begin(), numbers.end(), numbers.size()); },
        cnt);
    // cout << endl;

    cout << "parallel" << endl;
    timeit(
        [&numbers]()
        { minimum(execution::par, numbers.begin(), numbers.end(), numbers.size()); },
        cnt);
    // cout << endl;

    cout << "unseq" << endl; // SIMD
    timeit(
        [&numbers]()
        { minimum(execution::unseq, numbers.begin(), numbers.end(), numbers.size()); },
        cnt);
    // cout << endl;

    cout << "parallel unseq" << endl;
    timeit(
        [&numbers]()
        { minimum(execution::par_unseq, numbers.begin(), numbers.end(), numbers.size()); },
        cnt);
    // cout << endl;
}

void demo3()
{
    cout << "\n\nDEMO 3" << endl;
    auto numbers = getFloats(2.34, 10.1);
    //print(numbers);

    auto f = [](int a, int b)
        { cout << a << "*" << b << " "; return a * b; };

    // послідовний алгоритм
    cout << "accumulate" << endl;
    int res = accumulate(numbers.begin(), numbers.end(), 1, f);
    cout << endl
        << res << endl
        << endl;

    // його паралельний алгоритм
    // використання політики seq не дуже вплине на хід множень
    cout << "reduce, no policy" << endl;
    res = reduce(numbers.begin(), numbers.end(), 1, f);
    cout << endl
        << res << endl
        << endl;

    cout << "reduce, seq" << endl;
    res = reduce(execution::seq, numbers.begin(), numbers.end(), 1, f);
    cout << endl
        << res << endl
        << endl;

    cout << "reduce, parallel" << endl;
    res = reduce(execution::par, numbers.begin(), numbers.end(), 1, f);
    cout << endl
        << res << endl
        << endl;

    cout << "reduce, parallel unsequenced" << endl;
    res = reduce(execution::par_unseq, numbers.begin(), numbers.end(), 1, f);
    cout << endl
        << res << endl
        << endl;

    cout << "reduce, unsequenced" << endl;
    res = reduce(execution::unseq, numbers.begin(), numbers.end(), 1, f);
    cout << endl
        << res << endl
        << endl;
}

void demo4()
{
    cout << "\n\nDEMO 4" << endl;
    auto numbers = getNumbers(2, 100000);

    auto f = [](int a, int b)
        { return a + b; };

    // послідовний алгоритм
    cout << "accumulate                ";
    timeit([&numbers, &f]()
        { accumulate(numbers.begin(), numbers.end(), 1, f); });

    // його паралельний алгоритм
    // використання політики seq не дуже вплине на хід 
    cout << "reduce, no policy         ";
    timeit([&numbers, &f]()
        { reduce(numbers.begin(), numbers.end(), 1, f); });

    cout << "reduce, seq               ";
    timeit([&numbers, &f]()
        { reduce(execution::seq, numbers.begin(), numbers.end(), 1, f); });

    cout << "reduce, parallel          ";
    timeit([&numbers, &f]()
        { reduce(execution::par, numbers.begin(), numbers.end(), 1, f); });

    cout << "reduce, unsequenced       ";
    timeit([&numbers, &f]()
        { reduce(execution::unseq, numbers.begin(), numbers.end(), 1, f); });

    cout << "reduce, parallel unsequenced ";
    timeit([&numbers, &f]()
        { reduce(execution::par_unseq, numbers.begin(), numbers.end(), 1, f); });
}

void demo5()
{
    cout << "\n\nDEMO 5" << endl;
    long long cnt = 500000000LL;
    auto numbers = getFloats(1, cnt, 0.1);

    auto f = [](float arg)
        { return arg * arg * arg * arg; };

    cout << "transform, no policy      ";
    timeit([&numbers, &f]()
        { transform(numbers.begin(), numbers.end(), numbers.begin(), f); });

    cout << "transform, seq            ";
    numbers = getFloats(1, cnt, 0.1);
    timeit([&numbers, &f]()
        { transform(execution::seq, numbers.begin(), numbers.end(), numbers.begin(), f); });

    cout << "transform, parallel       ";
    numbers = getFloats(1, cnt, 0.1);
    timeit([&numbers, &f]()
        { transform(execution::par, numbers.begin(), numbers.end(), numbers.begin(), f); });

    cout << "transform, unsequenced    ";
    numbers = getFloats(1, cnt, 0.1);
    timeit([&numbers, &f]()
        { transform(execution::unseq, numbers.begin(), numbers.end(), numbers.begin(), f); });

    cout << "transform, parallel unsequenced ";
    numbers = getFloats(1, cnt, 0.1);
    timeit([&numbers, &f]()
        { transform(execution::par_unseq, numbers.begin(), numbers.end(), numbers.begin(), f); });
}

int main()
{
    demo1a();
    demo1b();
    demo2();
}