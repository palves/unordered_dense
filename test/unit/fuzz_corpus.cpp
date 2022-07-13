#include <fuzz/api.h>

#include <doctest.h>
#include <fmt/format.h>

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string_view>

namespace {

template <typename Op>
void run_corpus(std::string_view name, Op op) {
    auto const* corpus_base_dir = std::getenv("FUZZ_CORPUS_BASE_DIR"); // NOLINT(concurrency-mt-unsafe)
    if (nullptr == corpus_base_dir) {
        throw std::runtime_error("Environment variable FUZZ_CORPUS_BASE_DIR not set!");
    }

    auto path = std::filesystem::path(corpus_base_dir) / name;

    INFO("loading from " << path);
    auto num_files = 0;
    for (auto const& dir_entry : std::filesystem::directory_iterator(path)) {
        auto const& path = dir_entry.path();
        auto f = std::ifstream(path);
        auto content = std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
        INFO("file " << path);
        op(reinterpret_cast<uint8_t const*>(content.data()), content.size());
        ++num_files;
    }
    REQUIRE(0U != num_files);
}

} // namespace

TEST_CASE("fuzz_api") {
    run_corpus("api", fuzz::api);
}