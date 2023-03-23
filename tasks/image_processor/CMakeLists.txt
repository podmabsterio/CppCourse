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
)

add_subdirectory(test)