add_executable(
    image_processor
    image_processor.cpp
        color.h file_read.cpp file_read.h image.cpp image.h file_write.cpp file_write.h basic_filter.h crop.cpp crop.h grayscale.cpp grayscale.h matrix_filter.cpp matrix_filter.h sharpening.cpp sharpening.h negative.cpp negative.h controller.cpp controller.h)
