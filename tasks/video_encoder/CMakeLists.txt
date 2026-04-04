add_library(video_encoder
    video_encoder.cpp
)

target_link_libraries(video_encoder PUBLIC ${OpenCV_LIBS} ${GST_LIBRARIES})
target_include_directories(video_encoder PUBLIC ${PROJECT_SOURCE_DIR} ${GST_INCLUDE_DIRS})