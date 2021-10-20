cmake_minimum_required(VERSION 3.13.1)

list(APPEND ZEPHYR_EXTRA_MODULES ${CMAKE_CURRENT_SOURCE_DIR}/../../)

set(
    MODALITY_PROBE_ROOT
    "/usr/local/modality"
    CACHE
    PATH
    "Modality tar package installation directory")
set(
    MODALITY_PROBE_TARGET_TRIPLE
    "thumbv7m-none-eabi"
    CACHE
    STRING
    "Target triple")

list(APPEND CMAKE_MODULE_PATH "${MODALITY_PROBE_ROOT}/cmake")

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

# We're adding user-level events and will be using Modality helper functions
find_package(ModalityProbe REQUIRED)

project(modality-example LANGUAGES C)
target_sources(app PRIVATE src/main.c)
target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Generate user-level event instrumentation, combined with the provided tracing events
modality_probe_generate_manifest(
    TARGET app
    DEPENDS src/main.c
    COMPONENT_NAME "modality-component"
    OUTPUT_PATH "modality-component"
    EXCLUDES "build"
    FILE_EXTENSIONS "c"
    # Tracing events reserve the range 1..=0xFFFF, user events start after
    EVENT_ID_OFFSET 65536
    SOURCE_PATH src/main.c)

# Generate C definitions for the events
modality_probe_generate_header(
    TARGET app
    OUTPUT_FILE "generated_component_definitions.h"
    COMPONENT_PATH "modality-component")
