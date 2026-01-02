#include "clickhouse_scan.hpp"

namespace duckdb {

static void ClickhouseScan(ClientContext &context, TableFunctionInput &data, DataChunk &output) {
	throw NotImplementedException("ClickhouseScan");
}

static unique_ptr<FunctionData> ClickhouseBind(ClientContext &context, TableFunctionBindInput &input,
                                               vector<LogicalType> &return_types, vector<string> &names) {
	throw NotImplementedException("ClickhouseBind");
}

static unique_ptr<GlobalTableFunctionState> ClickhouseInitGlobalState(ClientContext &context,
                                                                      TableFunctionInitInput &input) {
	throw NotImplementedException("ClickhouseInitGlobalState");
}

static unique_ptr<LocalTableFunctionState> ClickhouseInitLocalState(ExecutionContext &context,
                                                                    TableFunctionInitInput &input,
                                                                    GlobalTableFunctionState *global_state) {
	throw NotImplementedException("ClickhouseInitLocalState");
}

ClickhouseScanFunction::ClickhouseScanFunction()
    : TableFunction("clickhouse_scan", {LogicalType::VARCHAR, LogicalType::VARCHAR, LogicalType::VARCHAR},
                    ClickhouseScan, ClickhouseBind, ClickhouseInitGlobalState, ClickhouseInitLocalState) {
}

} // namespace duckdb
