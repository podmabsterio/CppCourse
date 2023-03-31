add_executable(
    image_processor
    image_processor.cpp
        file_read.cpp
        image.cpp
        file_write.cpp
        crop.cpp
        grayscale.cpp
        matrix_filter.cpp
        sharpening.cpp
        negative.cpp
        controller.cpp
        edge_detection.cpp
        path_parser.cpp
        image_processor_exception.cpp
        fill_controller.cpp)

add_subdirectory(test)