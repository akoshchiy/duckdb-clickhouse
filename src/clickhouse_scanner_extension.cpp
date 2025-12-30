#define DUCKDB_EXTENSION_MAIN

#include "clickhouse_scanner_extension.hpp"
#include "duckdb.hpp"
#include "duckdb/common/exception.hpp"
#include "duckdb/function/scalar_function.hpp"

#include "storage/clickhouse_storage_extension.hpp"

namespace duckdb {

// unique_ptr<BaseSecret> CreateClickhouseSecretFunction(ClientContext &, CreateSecretInput &input) {
//     vector<string> prefix_paths;
//     auto result = make_uniq<KeyValueSecret>(prefix_paths, "clickhouse", "config", input.name);
//     for (const auto &named_param : input.options) {
//         auto lower_name = StringUtil::Lower(named_param.first);

//         if (lower_name == "host") {
//             result->secret_map["host"] = named_param.second.ToString();
//         } else if (lower_name == "user") {
//             result->secret_map["user"] = named_param.second.ToString();
//         } else if (lower_name == "database") {
//             result->secret_map["database"] = named_param.second.ToString();
//         } else if (lower_name == "password") {
//             result->secret_map["password"] = named_param.second.ToString();
//         } else if (lower_name == "port") {
//             result->secret_map["port"] = named_param.second.ToString();
//         } else {
//             throw InternalException("Unknown named parameter passed to CreateClickhouseSecretFunction: " +
//             lower_name);
//         }
//     }

//     //! Set redact keys
//     result->redact_keys = {"password"};
//     return std::move(result);
// }

// void SetClickhouseSecretParameters(CreateSecretFunction &function) {
//     function.named_parameters["host"] = LogicalType::VARCHAR;
//     function.named_parameters["port"] = LogicalType::VARCHAR;
//     function.named_parameters["password"] = LogicalType::VARCHAR;
//     function.named_parameters["user"] = LogicalType::VARCHAR;
//     function.named_parameters["database"] = LogicalType::VARCHAR;
// }

static void LoadInternal(ExtensionLoader &loader) {
	// SecretType secret_type;
	// secret_type.name = "clickhouse";
	// secret_type.deserializer = KeyValueSecret::Deserialize<KeyValueSecret>;
	// secret_type.default_provider = "config";

	// loader.RegisterSecretType(secret_type);

	// CreateSecretFunction ch_secret_function = {"clickhouse", "config", CreateClickhouseSecretFunction};
	// SetClickhouseSecretParameters(ch_secret_function);
	// loader.RegisterFunction(ch_secret_function);

	auto &db = loader.GetDatabaseInstance();
	auto &config = DBConfig::GetConfig(db);

	config.storage_extensions["clickhouse_scanner"] = make_uniq<ClickhouseStorageExtension>();
}

void ClickhouseScannerExtension::Load(ExtensionLoader &loader) {
	LoadInternal(loader);
}
std::string ClickhouseScannerExtension::Name() {
	return "clickhouse_scanner";
}

std::string ClickhouseScannerExtension::Version() const {
#ifdef EXT_VERSION_CLICKHOUSE_SCANNER
	return EXT_VERSION_CLICKHOUSE_SCANNER;
#else
	return "";
#endif
}

} // namespace duckdb

extern "C" {

DUCKDB_CPP_EXTENSION_ENTRY(clickhouse_scanner, loader) {
	duckdb::LoadInternal(loader);
}
}
