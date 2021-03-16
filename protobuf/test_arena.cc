#include "catch.hpp"
#include "test_message.pb.h"
#include <google/protobuf/arena.h>

int heap_message(std::uint32_t n) {
    test::A msg;
    for (int i = 0; i < n; ++i)
        msg.mutable_val()->Add(n);
    return n;
}

int arena_message(std::uint32_t n) {
    google::protobuf::Arena arena;
    auto* msg = google::protobuf::Arena::CreateMessage<test::A>(&arena);
    for (int i = 0; i < n; ++i)
        msg->mutable_val()->Add(n);
    return n;
}

int insert_vector(std::uint32_t n) {
    std::vector<int> vec;
    for (int i = 0; i < n; ++i) {
        vec.push_back(i);
    }
    return n;
}

TEST_CASE("T") {
    auto n = GENERATE(2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096);

    BENCHMARK("heap_message " + std::to_string(n)) {
        return heap_message(n);
    };

    BENCHMARK("arena_message " + std::to_string(n)) {
        return arena_message(n);
    };

    BENCHMARK("insert_vector " + std::to_string(n)) {
        return insert_vector(n);
    };

}
