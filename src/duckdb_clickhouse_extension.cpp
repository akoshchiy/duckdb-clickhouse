#define DUCKDB_EXTENSION_MAIN

#include "duckdb_clickhouse_extension.hpp"
#include "duckdb.hpp"
#include "duckdb/common/exception.hpp"
#include "duckdb/function/scalar_function.hpp"

#include "storage/clickhouse_storage_extension.hpp"

namespace duckdb {

static void LoadInternal(ExtensionLoader &loader) {
	auto &db = loader.GetDatabaseInstance();
	auto &config = DBConfig::GetConfig(db);

	config.storage_extensions["clickhouse_scanner"] = make_uniq<ClickhouseStorageExtension>();
}

void DuckdbClickhouseExtension::Load(ExtensionLoader &loader) {
	LoadInternal(loader);
}
std::string DuckdbClickhouseExtension::Name() {
	return "duckdb_clickhouse";
}

std::string DuckdbClickhouseExtension::Version() const {
#ifdef EXT_VERSION_DUCKDB_CLICKHOUSE
	return EXT_VERSION_DUCKDB_CLICKHOUSE;
#else
	return "";
#endif
}

} // namespace duckdb

extern "C" {

DUCKDB_CPP_EXTENSION_ENTRY(duckdb_clickhouse, loader) {
	duckdb::LoadInternal(loader);
}
}
