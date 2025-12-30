#include "storage/clickhouse_table_entry.hpp"

namespace duckdb {

ClickhouseTableEntry::ClickhouseTableEntry(Catalog &catalog, SchemaCatalogEntry &schema, CreateTableInfo &info)
    : TableCatalogEntry(catalog, schema, info) {
}

unique_ptr<BaseStatistics> ClickhouseTableEntry::GetStatistics(ClientContext &context, column_t column_id) {
	throw NotImplementedException("GetStatistics");
}

TableFunction ClickhouseTableEntry::GetScanFunction(ClientContext &context, unique_ptr<FunctionData> &bind_data) {
	throw NotImplementedException("GetScanFunction");
}

TableStorageInfo ClickhouseTableEntry::GetStorageInfo(ClientContext &context) {
	throw NotImplementedException("GetStorageInfo");
}

void ClickhouseTableEntry::BindUpdateConstraints(Binder &binder, LogicalGet &get, LogicalProjection &proj,
                                                 LogicalUpdate &update, ClientContext &context) {
}

} // namespace duckdb
