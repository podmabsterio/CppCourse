#pragma once

#include <exception>
#include <string>

class ImageProcessorException : public std::exception {
public:
    explicit ImageProcessorException(const char* message);

    const char * what() const noexcept final;

private:
    const char* message_;
};
