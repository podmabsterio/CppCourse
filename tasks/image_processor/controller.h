#pragma once

#include "basic_filter.h"
#include "crop.h"
#include "grayscale.h"
#include "negative.h"
#include "sharpening.h"

#include <queue>
#include <memory>

class Controller {
public:
    explicit Controller(const Image& image);

    void Feed(std::unique_ptr<Filter> filter);

    const Image& GetResult();

    void ApplyAllFilters();

private:
    Image image_;
    std::queue<std::unique_ptr<Filter>> queue_;
};
