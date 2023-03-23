#include <catch.hpp>

#include "../crop.h"
#include "../file_write.h"
#include "../file_read.h"
#include "../image.h"
#include "../negative.h"
#include "../grayscale.h"
#include "../controller.h"

TEST_CASE("Main") {
    std::string original_path = "/Users/boriszhukov/Downloads/lenna.bmp";
    std::string filtered_path = "/Users/boriszhukov/Downloads/lenna_updated.bmp";
    FileRead reader(original_path);
    Image image = reader.ReadFile();
    Crop cr(10000, 10);
    image = cr.Apply(image);
    FileWrite writer(image, reader.GetHeader());
    writer.WriteFile(filtered_path);
}
