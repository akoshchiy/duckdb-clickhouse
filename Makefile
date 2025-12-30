PROJ_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

# Configuration of extension
EXT_NAME=clickhouse_scanner
EXT_CONFIG=${PROJ_DIR}extension_config.cmake

include duckdb_extension.Makefile
