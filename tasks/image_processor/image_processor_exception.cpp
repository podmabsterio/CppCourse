#include "image_processor_exception.h"

ImageProcessorException::ImageProcessorException(const char* message) : message_(message) {
}

const char* ImageProcessorException::what() const noexcept {
    return message_;
}
