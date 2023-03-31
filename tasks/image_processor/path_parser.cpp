#include "path_parser.h"
#include "image_processor_exception.h"

PathParser::PathParser(const int argc, char** argv, const size_t begin) : argv_(argv), begin_(begin) {
    if (argc < MINIMUM_ARGUMENTS_REQUIRED) {
        throw ImageProcessorException("Too few arguments");
    }
}

char* PathParser::GetInputPath() const {
    return argv_[begin_];
}

char* PathParser::GetOutputPath() const {
    return argv_[begin_ + 1];
}

size_t PathParser::End() const {
    return begin_ + 2;
}
