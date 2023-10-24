//compiler g++13

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
void measureTime(F&& f)
{
    auto startTime = chrono::steady_clock::now();
    f();
    auto endTime = chrono::steady_clock::now();
    auto timeDiff = endTime - startTime;
    cout << format("{:%S}", timeDiff);
    cout << " ms" << endl;
}

vector<int> generateNumbers(int begin, int end, int inc = 1)
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

template <typename Iterator, typename T>
struct MinBlock
{
    void operator()(Iterator first, Iterator last, T& result)
    {
        result = *min_element(first, last);
    }
};

template <typename Iterator, typename T>
T parallelMin(Iterator first, Iterator last, T init)
{
    size_t length = distance(first, last);
    if (length == 0)
        return init;
    size_t minPerThread = 25;
    size_t maxThreads = (length + minPerThread - 1) / minPerThread;
    size_t hardwareThreads = thread::hardware_concurrency();
    size_t numThreads = min(hardwareThreads != 0 ? hardwareThreads : 2u, maxThreads);
    size_t blockSize = length / numThreads;
    vector<T> results(numThreads, init);
    vector<thread> threads(numThreads - 1);
    Iterator blockStart = first;

    for (size_t i = 0; i < (numThreads - 1); ++i)
    {
        Iterator blockEnd = blockStart;
        advance(blockEnd, blockSize);

        threads[i] = thread([blockStart, blockEnd, &results, i]() {
            MinBlock<Iterator, T>()(blockStart, blockEnd, results[i]);
            });

        blockStart = blockEnd;
    }

    MinBlock<Iterator, T>()(blockStart, last, results[numThreads - 1]);

    for (auto& entry : threads)
        entry.join();

    T finalResult = *min_element(results.begin(), results.end());
    return finalResult;
}

void calculateMinimumValue(const int numRange)
{
    auto numbers = generateNumbers(numRange, 0, -1);

    int minVal = 0;
    cout << "Sequential (" << numRange << "): ";
    measureTime([&numbers, &minVal]()
    {
        std::execution::sequenced_policy seqPolicy;
        minVal = *std::min_element(seqPolicy, numbers.begin(), numbers.end());
    });

    cout << "Parallel (" << numRange << "): ";
    measureTime([&numbers, &minVal]()
    {
        std::execution::parallel_policy parPolicy;
        minVal = *std::min_element(parPolicy, numbers.begin(), numbers.end());
    });

    cout << "Unsequenced (" << numRange << "): ";
    measureTime([&numbers, &minVal]()
    {
        std::execution::unsequenced_policy unseqPolicy;
        minVal = *std::min_element(unseqPolicy, numbers.begin(), numbers.end());
    });

    cout << "Sequential (" << numRange << "): ";
    measureTime([&numbers, &minVal]()
    {
        std::execution::sequenced_policy seqPolicy;
        minVal = *std::min_element(seqPolicy, numbers.begin(), numbers.end());
    });

    cout << "Parallel (" << numRange << "): ";
    measureTime([&numbers, &minVal]()
    {
        std::execution::parallel_policy parPolicy;
        minVal = *std::min_element(parPolicy, numbers.begin(), numbers.end());
    });

    cout << endl;
}

void myParallel()
{
    vector<double> container(100000000LL, 0);

    random_device rd;
    seed_seq seeds{ rd(), rd(), rd(), rd(), rd(), rd() };
    mt19937 engine(seeds);
    uniform_real_distribution<double> dist(-10000, 10);

    for (auto& el : container)
        el = dist(engine);

    int numThreads = thread::hardware_concurrency();

    vector<chrono::duration<double>> executionTimes;

    for (int K = 1; K <= numThreads; K++)
    {
        cout << "K: " << K << endl;
        auto startTime = chrono::steady_clock::now();
        cout << "Execution Time: ";
        double minValue = 0.0;
        measureTime([&]()
            {
                minValue = parallelMin(container.cbegin(), container.cend(), numeric_limits<double>::max());
            });

        auto endTime = chrono::steady_clock::now();
        auto timeDiff = endTime - startTime;

        executionTimes.push_back(chrono::duration_cast<chrono::duration<double>>(timeDiff));
    }

    int bestK = 1;
    double minExecutionTime = executionTimes[0].count();
    for (int K = 1; K < numThreads; K++) {
        double executionTime = executionTimes[K].count();
        if (executionTime < minExecutionTime) {
            minExecutionTime = executionTime;
            bestK = K + 1;
        }
    }

    cout << "K with shortest execution time: " << bestK << endl;
}

int main()
{
    calculateMinimumValue(10000);
    calculateMinimumValue(100000);
    calculateMinimumValue(1000000);
    myParallel();
}
