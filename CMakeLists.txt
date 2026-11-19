cmake_minimum_required(VERSION 3.20)
project(cpp_interview_prep LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)   # for clangd / VSCode IntelliSense

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# One executable per question: src/<name>.cpp -> <name>
function(add_question name)
  add_executable(${name} src/${name}.cpp)
  target_compile_options(${name} PRIVATE -Wall -Wextra -Wpedantic
    $<$<CONFIG:Debug>:-fsanitize=address,undefined -g>)
  target_link_options(${name} PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address,undefined>)
endfunction()

add_question(abstract_shape_class)
add_question(anagram_counter)
add_question(calendar_merge)
add_question(double_pointer_value)
add_question(employee_class)
add_question(even_numbers)
add_question(first_nonrepeating_character)
add_question(lambda)
add_question(max_value_template)
add_question(move)
add_question(nested_string)
add_question(repeating_characters)
add_question(reverse_string)
add_question(std_future_count)
add_question(triangle_area)
add_question(two_sum)
add_question(two_rectangle_area)
