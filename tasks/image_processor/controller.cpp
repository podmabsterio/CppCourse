#include "controller.h"

void Controller::Feed(std::unique_ptr<Filter> filter) {
    queue_.emplace(std::move(filter));
}

const Image& Controller::GetResult() {
    return image_;
}

Controller::Controller(const Image& image) : image_(image) {
}

void Controller::ApplyAllFilters() {
    while (!queue_.empty()) {
        image_ = queue_.front()->Apply(image_);
        queue_.pop();
    }
}
