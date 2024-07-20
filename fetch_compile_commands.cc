//
// Created by 少鹏 on 2024/6/24.
//
#include <fstream>
#include <filesystem>
#include <vector>

#include "nlohmann/json.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

using nlohmann::json;

int main(int argc, char **argv) {
    if (argc < 2 || argc > 3) {
        spdlog::error("Usage: ./fetch_compile_commands [FILES_TOP_DIR] "
                      "[RESULT_SAVE_DIR]");
        return 1;
    }
    std::filesystem::path input_path(argv[1]);
    std::filesystem::path result_path;
    if (argc == 2) {
        result_path = std::filesystem::path{argv[1]};
    } else {
        result_path = std::filesystem::path{argv[2]};
    }
    result_path.append("compile_commands.json");
    if (!std::filesystem::exists(input_path)) {
        spdlog::error("input path {} does not exist", input_path);
    }
    std::vector<std::filesystem::path> json_elem;
    for (auto const &dir_entry :
         std::filesystem::recursive_directory_iterator(input_path)) {
        if (dir_entry.path().filename() == "compile_commands.json") {
            json_elem.emplace_back(dir_entry.path());
        }
    }
    json res;
    for (const auto &path : json_elem) {
        std::ifstream f(path);
        json temp_elem = json::parse(f);
        for (const auto &elem : temp_elem) {
            res.emplace_back(elem);
        }
    }
    spdlog::info("res json elem have {} compile commands",
                 res.size());

    spdlog::info("res json save in {}", result_path);
    std::ofstream f(result_path);
    f  << std::setw(4) << res << std::endl;
    f.close();
    return 0;
}