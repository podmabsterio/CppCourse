#include "fill_controller.h"
#include "crop.h"
#include "grayscale.h"
#include "negative.h"
#include "sharpening.h"
#include "edge_detection.h"
#include "image_processor_exception.h"

#include <string>
#include <memory>

void FillController(int argc, char** argv, Controller& controller, size_t begin) {
    for (size_t i = begin; i < argc; ++i) {
        std::string filter_name = argv[i];
        if (filter_name == "-crop") {
            size_t width = 0;
            size_t height = 0;
            try {
                width = std::stoull(argv[i + 1]);
                height = std::stoull(argv[i + 2]);
            }
            catch (...) {
                throw ImageProcessorException("Wrong arguments to crop filter");
            }
            controller.Feed(std::make_unique<Crop>(width, height));
            i += 2;
        } else if (filter_name == "-edge") {
            double threshold = 0;
            try {
                threshold = std::stod(argv[i + 1]);
            }
            catch (...) {
                throw ImageProcessorException("Wrong arguments to edge detection filter");
            }
            controller.Feed(std::make_unique<EdgeDetection>(threshold));
            ++i;
        } else if (filter_name == "-neg") {
            controller.Feed(std::make_unique<Negative>());
        } else if (filter_name == "-gs") {
            controller.Feed(std::make_unique<GrayScale>());
        } else if (filter_name == "-sharp") {
            controller.Feed(std::make_unique<Sharpening>());
        } else {
            throw ImageProcessorException("There is no such filter");
        }
    }
}
