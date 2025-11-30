#include "storage/clickhouse_transaction.hpp"

#include "storage/clickhouse_catalog.hpp"

namespace duckdb {

ClickhouseTransaction::ClickhouseTransaction(
    Catalog &catalog, 
    TransactionManager &manager, 
    ClientContext &context
) : Transaction(manager, context), client(catalog.Cast<ClickhouseCatalog>().client_options) { }

ClickhouseTransaction::~ClickhouseTransaction() = default;

clickhouse::Client &ClickhouseTransaction::GetClient() {
    return client;
}

ClickhouseTransaction &ClickhouseTransaction::Get(ClientContext &context, Catalog &catalog) {
	return Transaction::Get(context, catalog).Cast<ClickhouseTransaction>();
}

} // namespace duckdb
