#include "image.h"
#include "file_read.h"
#include "file_write.h"
#include "controller.h"
#include "crop.h"
#include "grayscale.h"
#include "negative.h"
#include "sharpening.h"

#include <iostream>
#include <string>
#include <memory>

int main(int argc, char** argv) {
    std::string input_path = argv[1];
    std::string output_path = argv[2];

    FileRead reader(input_path);
    Image image = reader.ReadFile();

    Controller controller(image);

    for (size_t i = 3; i < argc; ++i) {
        std::string filter_name = argv[i];
        if (filter_name == "-crop") {
            size_t width = std::stoull(argv[i + 1]);
            size_t height = std::stoull(argv[i + 2]);
            std::cout << "I got crop with values: " << width << " " << height << "\n";
            controller.Feed(new Crop(width, height));
        } else if (filter_name == "-neg") {
            controller.Feed(new Negative);
        } else if (filter_name == "-gs") {
            controller.Feed(new GrayScale);
        } else if (filter_name == "-sharp") {
            controller.Feed(new Sharpening);
        } else {
            std::cout << "There is no such filter\n";
            return 0;
        }
    }

    controller.ApplyAllFilters();
    FileWrite writer(controller.GetResult(), reader.GetHeader());
    writer.WriteFile(output_path);
}