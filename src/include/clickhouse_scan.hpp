#pragma once

#include "duckdb/function/table_function.hpp"

namespace duckdb {

class ClickhouseScanFunction : public TableFunction {
public:
	ClickhouseScanFunction();
};

} // namespace duckdb
