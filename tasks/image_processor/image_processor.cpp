#include "file_read.h"
#include "file_write.h"
#include "controller.h"
#include "path_parser.h"
#include "fill_controller.h"

#include <iostream>
#include <memory>

int main(int argc, char** argv) {
    try {
        PathParser path_parser(argc, argv, 1);

        FileRead reader(path_parser.GetInputPath());

        Controller controller(reader.ReadFile());

        FillController(argc, argv, controller, path_parser.End());

        controller.ApplyAllFilters();
        FileWrite writer(controller.GetResult(), reader.GetHeader());
        writer.WriteFile(path_parser.GetOutputPath());
    } catch (const std::exception& exception) {
        std::cout << exception.what();
    }
}
