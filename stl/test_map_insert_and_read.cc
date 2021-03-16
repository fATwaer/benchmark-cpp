#define CATCH_CONFIG_ENABLE_BENCHMARKING
#define CATCH_CONFIG_MAIN

#include <map>
#include <unordered_map>
#include <random>
#include <vector>

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(1,6);

template<typename MAP>
bool write_map(std::vector<typename MAP::key_type>& input, MAP& map) {
    for (auto& x : input) {
        map[x] = x;
    }
    return true;
}

template<typename MAP>
std::vector<typename MAP::key_type> read_map(MAP& map) {
    std::vector<typename MAP::key_type> ret;
    for (auto kv : map) {
        ret.push_back(kv.second);
    }
    return ret;
}

std::string random_string( size_t length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

TEST_CASE("T") {
    auto n = GENERATE(range(1, 10000);

    std::vector<int> input(n);
    for (int i = 0; i < n; ++i)
        input.push_back(distribution(generator));

    std::unordered_map<int, int> hash_map;
    std::map<int, int> rbtree;

    BENCHMARK("hash_map insert " + std::to_string(n)) {
        return write_map(input, hash_map);
    };

    BENCHMARK("rbtree insert " + std::to_string(n)) {
        return write_map(input, rbtree);
    };

    BENCHMARK("hash_map read " + std::to_string(n)) {
        return read_map(hash_map);
    };

    BENCHMARK("rbtree read " + std::to_string(n)) {
        return read_map(rbtree);
    };
}
