#define CATCH_CONFIG_ENABLE_BENCHMARKING
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>

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

TEST_CASE("BOOST Join AND Split") {
    auto n = GENERATE(range(0, 200));
    std::vector<std::string> input(n);
    for (int i = 0; i < n; ++i)
        input[i] = random_string(11);

    BENCHMARK("Join " + std::to_string(n)) {
        return boost::join(input, ",");
    };

    std::string s(boost::join(input, ","));
    std::vector<std::string> output;

    BENCHMARK("Split " + std::to_string(n)) {
        return boost::split(output, s, boost::is_any_of(","));
    };
}