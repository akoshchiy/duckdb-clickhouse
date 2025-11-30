#pragma once

#include "duckdb/transaction/transaction.hpp"

#include <clickhouse/client.h>

namespace duckdb {

class ClickhouseTransaction : public Transaction {
public:
    ClickhouseTransaction(Catalog &catalog, TransactionManager &manager, ClientContext &context);
    ~ClickhouseTransaction() override;

    clickhouse::Client &GetClient();

    static ClickhouseTransaction &Get(ClientContext &context, Catalog &catalog);

private:
    clickhouse::Client client;
};

} // namespace duckdb 