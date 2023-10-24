#include <iostream>
#include <vector>
#include <functional>
#include <thread>

#include <execution>
#include <algorithm>
#include <numeric>

#include <chrono>
#include <format>
#include <cmath>

#include <random>

using namespace std;

template <class F>
void timeit(F&& f)
{
    auto time1 = chrono::system_clock::now();
    f();
    auto time2 = chrono::system_clock::now();
    auto tdiff = time2 - time1;
        cout << format("{:%S}", tdiff);
        cout << " ms" << endl;
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

void demo1()
{
    auto numbers = getNumbers(25, -10, -1);
    cout << "\n\nDEMO 1: int, " << numbers.size() << " numbers" << endl;
    int min = 0;
    cout << "No policy: ";
    timeit(
        [&numbers, &min]()
        {
            ranges::for_each(numbers.begin(), numbers.end(),
            [&min](int x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << "Min: " << min << endl;
    min = 0;
    cout << "Sequental: ";
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
    cout << "Min: " << min << endl;
    min = 0;
    cout << "Parallel: ";
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
    cout << "Min: " << min << endl;
    min = 0;

    cout << "Unseq: ";
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
    cout << "Min: " << min << endl;
    min = 0;

    cout << "Parallel unseq: ";
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
    cout << "Min: " << min << endl;
    std::cout << std::endl;
}

void demo2()
{
    auto numbers = getNumbers(5000, -1000, -2);
    cout << "\n\nDEMO 2: int, " << numbers.size() << " numbers" << endl;
    int min = numbers[0];
    cout << "No policy: ";
    timeit(
        [&numbers, &min]()
        {
            ranges::for_each(numbers.begin(), numbers.end(),
            [&min](int x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << "Min: " << min << endl;

    cout << "Sequental: ";
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
    cout << "Min: " << min << endl;
    min = 0;

    cout << "Parallel: ";
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
    cout << "Min: " << min << endl;
    min = 0;

    cout << "Unseq: ";
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
    cout << "Min: " << min << endl;
    min = 0;

    cout << "Parallel unseq: ";
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
    cout << "Min: " << min << endl;
    std::cout << std::endl;
}

void demo3()
{
    auto numbers = getNumbers(50000000, 0, -1);
    cout << "\n\nDEMO 3: int, " << numbers.size() << " numbers" << endl;
    int min = numbers[0];
    cout << "No policy: ";
    timeit(
        [&numbers, &min]()
        {
            ranges::for_each(numbers.begin(), numbers.end(),
            [&min](int x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << "Min: " << min << endl;
    min = numbers[0];
    cout << "Sequental: ";
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
    cout << "Min: " << min << endl;
    min = numbers[0];

    cout << "Parallel: ";
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
    cout << "Min: " << min << endl;
    min = numbers[0];

    cout << "Unseq: ";
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
    cout << "Min: " << min << endl;
    min = numbers[0];

    cout << "Parallel unseq: ";
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
    cout << "Min: " << min << endl;
    std::cout << std::endl;
}

void demo4()
{
    auto numbers = getLongLong(50000000000, 100, -1);
    cout << "\n\nDEMO 4: long long, " << numbers.size() << " numbers" << endl;
    long long min = numbers[0]; 
    cout << "No policy: ";
    timeit(
        [&numbers, &min]()
        {
            for_each(numbers.begin(), numbers.end(),
            [&min](long long x)
                {
                    if (static_cast<long long>(x) < min) {
                        min = static_cast<long long>(x);
                    }
                });
        });
    cout << "Min: " << min << endl;
    min = numbers[0];

    cout << "Sequental: ";
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::seq, numbers.begin(), numbers.end(),
            [&min](long long x)
                {
                    if (static_cast<long long>(x) < min) {
                        min = static_cast<long long>(x);
                    }
                });
        });
    cout << "Min: " << min << endl;
    min = numbers[0];

    cout << "Parallel: ";
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::par, numbers.begin(), numbers.end(),
            [&min](long long x)
                {
                    if (static_cast<long long>(x) < min) {
                        min = static_cast<long long>(x);
                    }
                });
        });
    cout << "Min: " << min << endl;
    min = numbers[0];

    cout << "Unseq: ";
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::unseq, numbers.begin(), numbers.end(),
            [&min](long long x)
                {
                    if (static_cast<long long>(x) < min) {
                        min = static_cast<long long>(x);
                    }
                });
        });
    cout << "Min: " << min << endl;
    min = numbers[0];

    cout << "Parallel unseq: ";
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::par_unseq, numbers.begin(), numbers.end(),
            [&min](long long x)
                {
                    if (static_cast<long long>(x) < min) {
                        min = static_cast<long long>(x);
                    }
                });
        });
    cout << "Min: " << min << endl;
    std::cout << std::endl;
}


void demo5()
{
    auto numbers = getFloats(12345.45f, 3, -1);
    cout << "\n\nDEMO 5: float, " << numbers.size() << " numbers" << endl;
    float min = numbers[0];
    cout << "No policy: ";
    timeit(
        [&numbers, &min]()
        {
            ranges::for_each(numbers.begin(), numbers.end(),
            [&min](float x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << "Min: " << min << endl;
    min = numbers[0];

    cout << "Sequental: ";
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::seq, numbers.begin(), numbers.end(),
            [&min](float x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << "Min: " << min << endl;
    min = numbers[0];

    cout << "Parallel: ";
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::par, numbers.begin(), numbers.end(),
            [&min](float x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << "Min: " << min << endl;
    min = numbers[0];

    cout << "Unseq: ";
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::unseq, numbers.begin(), numbers.end(),
            [&min](float x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << "Min: " << min << endl;
    min = numbers[0];

    cout << "Parallel unseq: ";
    timeit(
        [&numbers, &min]()
        {
            for_each(execution::par_unseq, numbers.begin(), numbers.end(),
            [&min](float x)
                {
                    if (x < min) {
                        min = x;
                    }
                });
        });
    cout << "Min: " << min << endl;
    std::cout << std::endl;
}

template <typename Iterator, typename T>
struct min_block
{
    void operator()(Iterator first, Iterator last, T& result)
    {
        result = *min_element(first, last);
    }
};

template <typename Iterator, typename T>
T parallel_min(Iterator first, Iterator last, T init)
{
    unsigned long const length = std::distance(first, last);
    if (!length)
        return init;
    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    unsigned long const num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
    unsigned long const block_size = length / num_threads;
    vector<T> results(num_threads, init);
    vector<thread> threads(num_threads - 1);
    Iterator block_start = first;

    for (unsigned long i = 0; i < (num_threads - 1); ++i)
    {
        Iterator block_end = block_start;
        advance(block_end, block_size);

        threads[i] = thread([block_start, block_end, &results, i]() {
            min_block<Iterator, T>()(block_start, block_end, results[i]);
            });

        block_start = block_end;
    }

    min_block<Iterator, T>()(block_start, last, results[num_threads - 1]);

    for (auto& entry : threads)
        entry.join();

    T final_result = *min_element(results.begin(), results.end());
    return final_result;
}

void demo6()
{
    const int num_samples = 10;
    std::vector<double> container(100000000LL, 0);

    std::random_device r;
    std::seed_seq seeds{ r(), r(), r(), r(), r(), r() };
    std::mt19937 e(seeds);
    std::uniform_real_distribution<double> d(-10000, 10);

    for (auto& el : container)
        el = d(e);

    int num_threads = std::thread::hardware_concurrency();

    std::vector<double> min_values;

    for (int K = 1; K <= num_threads; K++)
    {
        std::cout << "K: "<< K << endl;
        std::cout << "Executions Time: ";
        double min_value = 0.0;
        timeit([&]()
            {
                min_value = parallel_min(container.cbegin(), container.cend(), std::numeric_limits<double>::max());

            });


        min_values.push_back(min_value);
        std::cout << "Min Value: " << min_value  << std::endl;
    }
    double global_min = *std::min_element(min_values.begin(), min_values.end());
    
    std::cout << endl;
    std::cout << "Global Min: " << global_min << std::endl;

    double ratio = static_cast<double>(global_min) / num_threads;
    std::cout << "K / Num Threads Ratio: " << ratio << std::endl;
}


int main()
{
    //demo1a();
    //demo1b();
    demo1();
    demo2();
    demo3();
    demo4();
    demo5();
    demo6();
}