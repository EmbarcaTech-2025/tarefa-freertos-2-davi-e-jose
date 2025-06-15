add_library(temperature_handler STATIC
  temperature_handler.c
)

target_link_libraries(temperature_handler
  pico_stdlib
  hardware_adc
  FreeRTOS-Kernel-Heap4
)

target_include_directories(temperature_handler PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)
