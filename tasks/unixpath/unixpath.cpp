#include "unixpath.h"
#include <vector>

std::vector<std::string_view> Split(std::string_view path) {
    std::vector<std::string_view> split_path;
    size_t part_length = 0;
    auto part_begin = path.begin();
    for (auto it = path.begin(); it != path.end(); ++it) {
        if (*it == '/') {
            part_length = 0;
        } else {
            if (part_length == 0) {
                part_begin = it;
            }
            ++part_length;
        }
        if (part_length > 0 && (it == path.end() - 1 || *(it + 1) == '/')) {
            split_path.emplace_back(part_begin, part_length);
        }
    }
    return split_path;
}

std::string RelativePath(std::string_view current_working_dir, std::string_view path) {
    auto dir_parts = Split(current_working_dir);
    auto path_parts = Split(path);
    for (auto part : path_parts) {
        if (part == ".." && !dir_parts.empty()) {
            dir_parts.pop_back();
        } else if (part != ".." && part != ".") {
            dir_parts.emplace_back(part);
        }
    }
    std::string normalized_path;
    for (auto& expression : dir_parts) {
        normalized_path += "/";
        normalized_path += expression;
    }
    if (normalized_path.empty()) {
        return "/";
    }
    return normalized_path;
}

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    if (path.empty() || path[0] != '/') {
        return RelativePath(current_working_dir, path);
    }
    return RelativePath("", path);
}
