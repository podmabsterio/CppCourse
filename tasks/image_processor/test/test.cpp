#include <catch.hpp>

#include "../color.h"
#include "../controller.h"
#include "../crop.h"
#include "../edge_detection.h"
#include "../file_read.h"
#include "../file_write.h"
#include "../fill_controller.h"
#include "../grayscale.h"
#include "../image.h"
#include "../image_processor_exception.h"
#include "../matrix_filter.h"
#include "../negative.h"
#include "../path_parser.h"
#include "../sharpening.h"
#include <iostream>

namespace {
bool IsSameImages(const Image& a, const Image& b) {
    if (a.Height() != b.Height()) {
        return false;
    }
    if (a.Width() != b.Width()) {
        return false;
    }
    for (size_t i = 0; i < a.Height(); ++i) {
        for (size_t j = 0; j < a.Width(); ++j) {
            if (a[i][j].Red != b[i][j].Red || a[i][j].Green != b[i][j].Green || a[i][j].Blue != b[i][j].Blue) {
                return false;
            }
        }
    }
    return true;
}
}  // namespace

TEST_CASE("Wrong path") {
    try {
        FileRead file_read("incorrect path");
        file_read.ReadFile();
    }
    catch (const std::exception& exception) {
        REQUIRE(static_cast<std::string>(exception.what()) == "Path is incorrect");
    }
}

TEST_CASE("Wrong file format") {
    try {
        FileRead file_read("../tasks/image_processor/test/data/test.txt");
        file_read.ReadFile();
    }
    catch (const std::exception& exception) {
        REQUIRE(static_cast<std::string>(exception.what()) == "Wrong file format");
    }
}

TEST_CASE("Reading and Writing") {
    FileRead input_file_read("../tasks/image_processor/test/data/input.bmp");
    Image original_file = input_file_read.ReadFile();

    FileWrite file_write(original_file, input_file_read.GetHeader());
    file_write.WriteFile("../tasks/image_processor/test/data/output.bmp");

    FileRead output_file_read("../tasks/image_processor/test/data/output.bmp");
    Image new_file = output_file_read.ReadFile();

    REQUIRE(IsSameImages(original_file, new_file));
}
