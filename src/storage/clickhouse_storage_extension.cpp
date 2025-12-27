#include "duckdb.hpp"

#include "duckdb/common/string_util.hpp"

#include "storage/clickhouse_storage_extension.hpp"
#include "storage/clickhouse_catalog.hpp"
#include "storage/clickhouse_transaction_manager.hpp"

#include <clickhouse/client.h>

using namespace clickhouse;

namespace duckdb {

static ClientOptions ParseOptions(const string &attach_path) {
    auto options = ClientOptions();
    auto splits = StringUtil::Split(attach_path, " ");

    for (auto& split : splits) {
        auto kv = StringUtil::Split(split, "=");
        if (kv.size() < 2) {
            throw InvalidInputException("Bad option \"%s\"", split);
        }
        auto& key = kv[0];
        auto& value = kv[1];

        if (key == "host") {
            options.SetHost(value);
        } else if (key == "port") {
            options.SetPort(std::stoul(value));
        } else if (key == "database") {
            options.SetDefaultDatabase(value);
        } else if (key == "user") {
            options.SetUser(value);
        } else if (key == "password") {
            options.SetPassword(value);
        }
    }
    return options;
}

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

    // // check if we have a secret provided
    // string secret_name;
    // for (auto &entry : attach_options.options) {
    //     auto lower_name = StringUtil::Lower(entry.first);
    //     if (lower_name == "secret") {
    //         secret_name = entry.second.ToString();
    //     } else {
    //         throw BinderException("Unrecognized option for MySQL attach: %s", entry.first);
    //     }
    // }


    string attach_path = info.path;

    // TODO implement
    auto client_options = ParseOptions(attach_path);

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