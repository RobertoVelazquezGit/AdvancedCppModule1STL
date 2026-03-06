#include <iostream>
#include <map>
#include <unordered_map>
#include <chrono>
#include <random>

int main()
{
    const int N = 1'000'000;

    using clock = std::chrono::steady_clock;

    // Random number generator
    std::mt19937 rng(123);
    std::uniform_int_distribution<int> dist(0, N);

    // -------- std::map --------
    // Internally implemented as a balanced tree (usually Red-Black Tree)
    // Insert complexity: O(log n)

    std::map<int, int> m;

    auto start_map = clock::now();

    for (int i = 0; i < N; ++i)
    {
        int k = dist(rng);
        m.emplace(k, k);  // O(log n)
    }

    auto end_map = clock::now();

    auto map_time = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_map - start_map);

    std::cout << "map insert time: "
        << map_time.count()
        << " ms\n";


    // -------- std::unordered_map --------
    // Internally implemented as a hash table
    // Average insert complexity: O(1)
    // Worst case (hash collisions): O(n)

    std::unordered_map<int, int> um;

    um.reserve(N);
    // Pre-allocate buckets to reduce rehash operations

    auto start_um = clock::now();

    for (int i = 0; i < N; ++i)
    {
        int k = dist(rng);
        um.emplace(k, k);  // Average O(1)
    }

    auto end_um = clock::now();

    auto um_time = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_um - start_um);

    std::cout << "unordered_map insert time: "
        << um_time.count()
        << " ms\n";


    // Prevent compiler from optimizing containers away
    volatile std::size_t s = m.size() + um.size();
}

// Release
//map insert time : 541 ms
//unordered_map insert time : 86 ms