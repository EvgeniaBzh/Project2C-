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
    vector<T> numbers;
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
    vector<T> numbers;
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
        }
    else
        for (int i = begin; i > end; i += inc)
        {
            numbers.push_back(i);
        }

    return numbers;
}

vector<long long> getNumbersLL(long long begin, long long end, long long inc = 1)
{
    vector<long long> numbers;
    if (inc > 0)
        for (long long i = begin; i < end; i += inc)
        {
            numbers.push_back(i);
        }
    else
        for (long long i = begin; i > end; i += inc)
        {
            numbers.push_back(i);
        }

    return numbers;
}

vector<float> getNumbersFloat(float begin, float end, float inc = 1.0f)
{
    vector<float> numbers;
    if (inc > 0.0f)
        for (float i = begin; i < end; i += inc)
        {
            numbers.push_back(i);
        }
    else
        for (float i = begin; i > end; i += inc)
        {
            numbers.push_back(i);
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
    auto numbers = getNumbers(1000, 0, -1);
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

    cout << endl;
}

void demo2()
{
    auto numbers = getNumbers(10000, 0, -1);
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

    cout << endl;
}

void demo3()
{
    auto numbers = getNumbers(1000000, 0, -1);
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

    cout << endl;
}

void demo4()
{
    vector<long long> numbers = getNumbersLL(1000000LL, 0LL, -1LL);
    cout << "\n\nDEMO 4: long long " << numbers.size() << " numbers" << endl;
    long long min = 0LL;

    cout << "No policy: ";
    timeit([&numbers, &min]() {
        ranges::for_each(numbers.begin(), numbers.end(),
        [&min](long long x) {
            if (x < min) {
                min = x;
            }
        });
    });

    min = 0LL;

    cout << "Sequental: ";
    timeit([&numbers, &min]() {
        for_each(execution::seq, numbers.begin(), numbers.end(),
        [&min](long long x) {
            if (x < min) {
                min = x;
            }
        });
    });

    min = 0LL;

    cout << "Parallel: ";
    timeit([&numbers, &min]() {
        for_each(execution::par, numbers.begin(), numbers.end(),
        [&min](long long x) {
            if (x < min) {
                min = x;
            }
        });
    });

    min = 0LL;

    cout << "Unseq: ";
    timeit([&numbers, &min]() {
        for_each(execution::unseq, numbers.begin(), numbers.end(),
        [&min](long long x) {
            if (x < min) {
                min = x;
            }
        });
    });

    min = 0LL;

    cout << "Parallel unseq: ";
    timeit([&numbers, &min]() {
        for_each(execution::par_unseq, numbers.begin(), numbers.end(),
        [&min](long long x) {
            if (x < min) {
                min = x;
            }
        });
    });

    cout << endl;
}

void demo5()
{
    vector<float> numbers = getNumbersFloat(100000.0f, 0.0f, -1.0f);
    cout << "\n\nDEMO 5: float " << numbers.size() << " numbers" << endl;
    float min = 0.0f;

    cout << "No policy: ";
    timeit([&numbers, &min]() {
        ranges::for_each(numbers.begin(), numbers.end(),
        [&min](float x) {
            if (x < min) {
                min = x;
            }
        });
    });

    min = 0.0f;

    cout << "Sequental: ";
    timeit([&numbers, &min]() {
        for_each(execution::seq, numbers.begin(), numbers.end(),
        [&min](float x) {
            if (x < min) {
                min = x;
            }
        });
    });

    min = 0.0f;

    cout << "Parallel: ";
    timeit([&numbers, &min]() {
        for_each(execution::par, numbers.begin(), numbers.end(),
        [&min](float x) {
            if (x < min) {
                min = x;
            }
        });
    });

    min = 0.0f;

    cout << "Unseq: ";
    timeit([&numbers, &min]() {
        for_each(execution::unseq, numbers.begin(), numbers.end(),
        [&min](float x) {
            if (x < min) {
                min = x;
            }
        });
    });

    min = 0.0f;

    cout << "Parallel unseq: ";
    timeit([&numbers, &min]() {
        for_each(execution::par_unseq, numbers.begin(), numbers.end(),
        [&min](float x) {
            if (x < min) {
                min = x;
            }
        });
    });

    cout << endl;
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
    unsigned long const length = distance(first, last);
    if (!length)
        return init;
    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;
    unsigned long const hardware_threads = thread::hardware_concurrency();
    unsigned long const num_threads = min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
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
    vector<double> container(100000000LL, 0);

    random_device r;
    seed_seq seeds{ r(), r(), r(), r(), r(), r() };
    mt19937 e(seeds);
    uniform_real_distribution<double> d(-10000, 10);

    for (auto& el : container)
        el = d(e);

    int num_threads = thread::hardware_concurrency();

    vector<chrono::duration<double>> execution_times;

    for (int K = 1; K <= num_threads; K++)
    {
        cout << "K: " << K << endl;
        auto time1 = chrono::system_clock::now();
        cout << "Executions Time: ";
        double min_value = 0.0;
        timeit([&]()
            {
                // min_value = parallel_min(container.cbegin(), container.cend(), numeric_limits<double>::max());
                parallel_min(container.cbegin(), container.cend(), numeric_limits<double>::max());
            });

        auto time2 = chrono::system_clock::now();
        auto tdiff = time2 - time1;

        execution_times.push_back(chrono::duration_cast<chrono::duration<double>>(tdiff));
    }

    int best_K = 1;
    double min_execution_time = execution_times[0].count();
    for (int K = 1; K < num_threads; K++) {
        double execution_time = execution_times[K].count();
        if (execution_time < min_execution_time) {
            min_execution_time = execution_time;
            best_K = K + 1;
        }
    }

    cout << "K with shortest execution time: " << best_K << endl;
}

int main()
{
    demo1();
    demo2();
    demo3();
    demo4();
    demo5();
    demo6();
}
