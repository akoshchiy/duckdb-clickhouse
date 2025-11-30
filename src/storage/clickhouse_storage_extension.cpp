#include "duckdb.hpp"

#include "storage/clickhouse_storage_extension.hpp"
#include "storage/clickhouse_catalog.hpp"
#include "storage/clickhouse_transaction_manager.hpp"

#include <clickhouse/client.h>

using namespace clickhouse;

namespace duckdb {

static unique_ptr<Catalog> ClickhouseAttach(
    optional_ptr<StorageExtensionInfo> storage_info, 
    ClientContext &context,
    AttachedDatabase &db, 
    const string &name, 
    AttachInfo &info,
    AttachOptions &attach_options) {
    auto &config = DBConfig::GetConfig(context);
	if (!config.options.enable_external_access) {
		throw PermissionException("Attaching Clickhouse databases is disabled through configuration");
	}

	string attach_path = info.path;

    // TODO implement
    auto client_options = ClientOptions();
    // Client c;
    return make_uniq<ClickhouseCatalog>(db, std::move(attach_path), attach_options.access_mode, std::move(client_options));
}

static unique_ptr<TransactionManager> ClickhouseCreateTransactionManager(
    optional_ptr<StorageExtensionInfo> storage_info,
    AttachedDatabase &db, 
    Catalog &catalog) {
	return make_uniq<ClickhouseTransactionManager>(db, catalog);
}

ClickhouseStorageExtension::ClickhouseStorageExtension() {
    attach = ClickhouseAttach;
    create_transaction_manager = ClickhouseCreateTransactionManager;
};

}