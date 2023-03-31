#pragma once

#include <cstddef>
#include <string>

class PathParser {
public:
    PathParser() = default;

    PathParser(const int argc, char** argv, const size_t begin);

    char* GetInputPath() const;
    char* GetOutputPath() const;

    size_t End() const;

private:
    static const int MINIMUM_ARGUMENTS_REQUIRED = 3;

    char** argv_;

    std::string input_path_;
    std::string output_path_;
    size_t begin_;
};
