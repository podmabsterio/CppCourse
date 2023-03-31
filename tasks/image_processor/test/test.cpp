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
#include <memory>

namespace {
const int16_t NORMAL_DIFFERENCE = 5;

bool NearColors(const Color<int16_t>& a, const Color<int16_t>& b) {
    return abs(a.Red - b.Red) < NORMAL_DIFFERENCE && abs(a.Green - b.Green) < NORMAL_DIFFERENCE
           && abs(a.Blue - b.Blue) < NORMAL_DIFFERENCE;
}

bool IsSameImages(const Image& a, const Image& b) {
    if (a.Height() != b.Height()) {
        return false;
    }
    if (a.Width() != b.Width()) {
        return false;
    }
    for (size_t i = 0; i < a.Height(); ++i) {
        for (size_t j = 0; j < a.Width(); ++j) {
            if (!NearColors(a[i][j], b[i][j])) {
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

TEST_CASE("Crop") {
    FileRead file_read("../tasks/image_processor/test_script/data/lenna.bmp");
    Controller controller(file_read.ReadFile());

    controller.Feed(std::make_unique<Crop>(999, 1999));
    controller.ApplyAllFilters();

    FileRead correct_file_read("../tasks/image_processor/test_script/data/lenna_crop.bmp");

    REQUIRE(IsSameImages(controller.GetResult(), correct_file_read.ReadFile()));
}

TEST_CASE("EdgeDetection") {
    FileRead file_read("../tasks/image_processor/test_script/data/flag.bmp");
    Controller controller(file_read.ReadFile());

    controller.Feed(std::make_unique<EdgeDetection>(0.1));
    controller.ApplyAllFilters();

    FileRead correct_file_read("../tasks/image_processor/test_script/data/flag_edge.bmp");

    REQUIRE(IsSameImages(controller.GetResult(), correct_file_read.ReadFile()));
}

TEST_CASE("Grayscale") {
    FileRead file_read("../tasks/image_processor/test_script/data/lenna.bmp");
    Controller controller(file_read.ReadFile());

    controller.Feed(std::make_unique<GrayScale>());
    controller.ApplyAllFilters();

    FileRead correct_file_read("../tasks/image_processor/test_script/data/lenna_gs.bmp");

    REQUIRE(IsSameImages(controller.GetResult(), correct_file_read.ReadFile()));
}

TEST_CASE("Negative") {
    FileRead file_read("../tasks/image_processor/test_script/data/lenna.bmp");
    Controller controller(file_read.ReadFile());

    controller.Feed(std::make_unique<Negative>());
    controller.ApplyAllFilters();

    FileRead correct_file_read("../tasks/image_processor/test_script/data/lenna_neg.bmp");

    REQUIRE(IsSameImages(controller.GetResult(), correct_file_read.ReadFile()));
}

TEST_CASE("Sharpening") {
    FileRead file_read("../tasks/image_processor/test_script/data/lenna.bmp");
    Controller controller(file_read.ReadFile());

    controller.Feed(std::make_unique<Sharpening>());
    controller.ApplyAllFilters();

    FileRead correct_file_read("../tasks/image_processor/test_script/data/lenna_sharp.bmp");

    REQUIRE(IsSameImages(controller.GetResult(), correct_file_read.ReadFile()));
}
