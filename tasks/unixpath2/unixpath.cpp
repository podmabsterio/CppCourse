#include "unixpath.h"
#include <vector>

std::vector<std::string_view> SplitStringView(std::string_view path) {
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

std::vector<std::string> SplitString(const std::string_view& path) {
    std::vector<std::string> split_path;
    std::string part;
    for (size_t i = 0; i < path.size(); ++i) {
        if (path[i] == '/') {
            part.clear();
        } else {
            part += path[i];
        }
        if (!part.empty() && (i == path.size() - 1 || path[i + 1] == '/')) {
            split_path.emplace_back(part);
        }
    }
    return split_path;
}

std::vector<std::string> FromRelativeToAbsolute(std::vector<std::string> root_dir, std::string_view path) {
    auto path_parts = SplitStringView(path);
    for (auto part : path_parts) {
        if (part == ".." && !root_dir.empty()) {
            root_dir.pop_back();
        } else if (part != ".." && part != ".") {
            root_dir.emplace_back(part);
        }
    }
    return root_dir;
}

std::string AbsolutePathToString(const std::vector<std::string>& path) {
    std::string representation;
    for (size_t i = 0; i < path.size(); ++i) {
        representation += "/";
        representation += path[i];
    }
    if (representation.empty()) {
        return "/";
    }
    return representation;
}

std::string RelativePathToString(const std::vector<std::string>& path) {
    std::string representation;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        representation += path[i];
        representation += "/";
    }
    if (!path.empty()) {
        representation += path.back();
    }
    return representation;
}

UnixPath::UnixPath(std::string_view initial_dir) : root_dir_(SplitString(initial_dir)), current_path_(root_dir_) {
}

void UnixPath::ChangeDirectory(std::string_view path) {
    if (path.empty() || path[0] != '/') {
        current_path_ = FromRelativeToAbsolute(current_path_, path);
    } else {
        current_path_ = FromRelativeToAbsolute({}, path);
    }
}

std::string UnixPath::GetAbsolutePath() const {
    return AbsolutePathToString(current_path_);
}

std::string UnixPath::GetRelativePath() const {
    std::vector<std::string> normalized_path;
    size_t match = 0;
    while (match < current_path_.size() && match < root_dir_.size() && root_dir_[match] == current_path_[match]) {
        ++match;
    }
    if (match == root_dir_.size()) {
        normalized_path.emplace_back(".");
    } else {
        for (size_t i = 0; i < root_dir_.size() - match; ++i) {
            normalized_path.emplace_back("..");
        }
    }
    for (size_t i = match; i < current_path_.size(); ++i) {
        normalized_path.emplace_back(current_path_[i]);
    }
    return RelativePathToString(normalized_path);
}
