#pragma once

#include "basic_filter.h"
#include "crop.h"
#include "grayscale.h"
#include "negative.h"
#include "sharpening.h"

#include <queue>

class Controller {
public:
    explicit Controller(const Image& image);

    void Feed(Filter* filter);

    const Image& GetResult();

    ~Controller();

    void ApplyAllFilters();

private:
    Image image_;
    std::queue<Filter*> queue_;

    void DeleteFront();
};
