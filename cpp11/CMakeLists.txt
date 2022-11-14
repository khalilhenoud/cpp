cmake_minimum_required(VERSION 3.22)

# set the project name
project(CPP11 VERSION 1.0)

# config file
configure_file(config.h.in config.h)

# specify the cpp standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(${PROJECT_NAME} 
			./source/driver.cpp
      ./source/registrar.cpp
      ./source/utils.cpp
			./source/language/attributes.cpp
			./source/language/auto.cpp
			./source/language/char32_t_and_char16_t.cpp
			./source/language/constexpr.cpp
			./source/language/converting_constructors.cpp
			./source/language/decltype_operator.cpp
			./source/language/default_functions.cpp
			./source/language/delegating_constructors.cpp
			./source/language/deleted_functions.cpp
			./source/language/explicit_conversion_functions.cpp
			./source/language/explicit_virtual_overrides.cpp
			./source/language/final_specifier.cpp
			./source/language/forwarding_references.cpp
			./source/language/initializer_lists.cpp
			./source/language/inline_namespaces.cpp
			./source/language/lambda_expressions.cpp
			./source/language/move_semantics.cpp
			./source/language/noexcept_specifier.cpp
			./source/language/non_static_data_member_initializers.cpp
			./source/language/nullptr.cpp
			./source/language/range_based_for_loops.cpp
			./source/language/raw_string_literals.cpp
			./source/language/ref_qualified_member_functions.cpp
			./source/language/right_angle_brackets.cpp
			./source/language/rvalue_references.cpp
			./source/language/special_member_functions_for_move_semantics.cpp
			./source/language/static_assert.cpp
			./source/language/strong_typed_enums.cpp
			./source/language/trailing_return_types.cpp
			./source/language/type_aliases.cpp
			./source/language/user_defined_literals.cpp
			./source/language/variadic_templates.cpp
      ./source/language/alignas_alignof.cpp
      ./source/language/sizeof_member_variables.cpp
      ./source/language/unrestricted_unions.cpp
      ./source/language/thread_local_storage.cpp
      ./source/library/move.cpp
      ./source/library/forward.cpp
      ./source/library/to_string.cpp
      ./source/library/type_traits.cpp
      ./source/library/array.cpp
      ./source/library/tuple.cpp
      ./source/library/tie.cpp
      ./source/library/begin_end.cpp
      ./source/library/unordered_containers.cpp
      ./source/library/chrono.cpp
      ./source/library/ref.cpp
      ./source/library/make_shared.cpp
      ./source/library/smart_pointers.cpp
      ./source/library/forward_list.cpp
      ./source/library/function.cpp
      ./source/library/random.cpp
      ./source/library/regex.cpp
      ./source/library/thread.cpp
      ./source/library/async.cpp
      ./source/library/mutex.cpp
      ./source/library/timed_mutex.cpp
      ./source/library/recursive_mutex.cpp
      ./source/library/recursive_timed_mutex.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC 
							"${PROJECT_BINARY_DIR}"
							"${PROJECT_SOURCE_DIR}/include"
							)