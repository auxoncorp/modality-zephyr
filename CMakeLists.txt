cmake_minimum_required(VERSION 3.13.1)

include_directories("include")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -include 'tracing/tracing.h'")

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(modapp)

list(APPEND CMAKE_MODULE_PATH "/usr/local/modality/cmake")
SET(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
set(MODALITY_PROBE_TARGET_TRIPLE "thumbv7em-none-eabi" CACHE STRING "Target triple")
find_package(ModalityProbe REQUIRED)

target_sources(app PRIVATE src/main.c src/modality_comms.c src/modality_tracing.c)
target_link_libraries(app PRIVATE ModalityProbe::LibModalityProbe)
target_link_libraries(app PRIVATE "-Wl,--allow-multiple-definition")

modality_probe_generate_manifest(
    TARGET app
    DEPENDS src/main.c src/modality_tracing.c
    COMPONENT_NAME "zephyr-example-component"
    OUTPUT_PATH "modality-manifests"
    EXCLUDES "build"
    FILE_EXTENSIONS "c"
    SOURCE_PATH ".")

modality_probe_generate_header(
    TARGET app
    OUTPUT_FILE "include/generated/modality_component_definitions.h"
    COMPONENT_PATH "modality-manifests")

# modality_probe_generate_mutators(
#     TARGET app
#     DEPENDS src/main.c
#     FILE_EXTENSIONS "c"
#     COMPONENT_PATH "zephyr-example-component"
#     OUTPUT_PATH "generated_mutators"
#     EXCLUDES "build"
#     SOURCE_PATH ".")
