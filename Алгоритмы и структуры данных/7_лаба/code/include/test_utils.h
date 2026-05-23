#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <chrono>
#include <vector>

struct SearchResults {
    double avgExistingTime;
    double avgMissingTime;
};

template<typename Func>
double measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

SearchResults testLinearSearch(const std::vector<int>& data,
                           const std::vector<int>& existing,
                           const std::vector<int>& missing) {
    SearchResults results{0, 0};

    // Successful searches
    for (int val : existing) {
        results.avgExistingTime += measureTime([&]() {
            linearSearch(data.data(), data.size(), val);
        });
    }
    results.avgExistingTime /= existing.size();

    // Unsuccessful searches
    for (int val : missing) {
        results.avgMissingTime += measureTime([&]() {
            linearSearch(data.data(), data.size(), val);
        });
    }
    results.avgMissingTime /= missing.size();

    return results;
}

#endif
