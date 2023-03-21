#include "controller.h"

void Controller::Feed(Filter* filter) {
    queue_.push(filter);
}

const Image& Controller::GetResult() {
    return image_;
}

Controller::Controller(const Image& image) : image_(image) {
}

Controller::~Controller() {
    while (!queue_.empty()) {
        DeleteFront();
    }
}

void Controller::DeleteFront() {
    auto buf = queue_.front();
    queue_.pop();
    delete buf;
}

void Controller::ApplyAllFilters() {
    while (!queue_.empty()) {
        image_ = queue_.front()->Apply(image_);
        DeleteFront();
    }
}
