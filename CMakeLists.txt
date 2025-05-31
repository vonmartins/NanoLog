# Create a static library for NanoLog
add_library(NanoLog STATIC
    nlog.c
)

# Include header directories
target_include_directories(NanoLog PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)