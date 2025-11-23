#define DUCKDB_EXTENSION_MAIN

#include "duckdb_clickhouse_extension.hpp"
#include "duckdb.hpp"
#include "duckdb/common/exception.hpp"
#include "duckdb/function/scalar_function.hpp"
#include <duckdb/parser/parsed_data/create_scalar_function_info.hpp>

// OpenSSL linked through vcpkg
// #include <openssl/opensslv.h>

#include <clickhouse/client.h>

using namespace clickhouse;

namespace duckdb {

inline void DuckdbClickhouseScalarFun(DataChunk &args, ExpressionState &state, Vector &result) {
	auto &name_vector = args.data[0];
	UnaryExecutor::Execute<string_t, string_t>(name_vector, result, args.size(), [&](string_t name) {
		return StringVector::AddString(result, "DuckdbClickhouse " + name.GetString() + " 🐥");
	});
}

inline void DuckdbClickhouseOpenSSLVersionScalarFun(DataChunk &args, ExpressionState &state, Vector &result) {

	// auto &name_vector = args.data[0];
	// UnaryExecutor::Execute<string_t, string_t>(name_vector, result, args.size(), [&](string_t name) {
	// 	return StringVector::AddString(result, "DuckdbClickhouse " + name.GetString() + ", my linked OpenSSL version is " +
	// 	                                           OPENSSL_VERSION_TEXT);
	// });
}

static void LoadInternal(ExtensionLoader &loader) {
	/// Initialize client connection.
    Client client(ClientOptions().SetHost("localhost"));
	
	// Register a scalar function
	auto duckdb_clickhouse_scalar_function = ScalarFunction("duckdb_clickhouse", {LogicalType::VARCHAR}, LogicalType::VARCHAR, DuckdbClickhouseScalarFun);
	loader.RegisterFunction(duckdb_clickhouse_scalar_function);

	// Register another scalar function
	auto duckdb_clickhouse_openssl_version_scalar_function = ScalarFunction("duckdb_clickhouse_openssl_version", {LogicalType::VARCHAR},
	                                                            LogicalType::VARCHAR, DuckdbClickhouseOpenSSLVersionScalarFun);
	loader.RegisterFunction(duckdb_clickhouse_openssl_version_scalar_function);
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
