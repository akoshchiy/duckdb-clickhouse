include_directories(include)

add_subdirectory(storage)

add_library(
    clickhouse_ext OBJECT
    duckdb_clickhouse_extension.cpp)

set(ALL_OBJECT_FILES
    ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:clickhouse_ext>
    PARENT_SCOPE)