#pragma once

#include "storage/clickhouse_transaction.hpp"
#include "storage/clickhouse_catalog_set.hpp"

namespace duckdb {

class ClickhouseSchemaSet : public ClickhouseCatalogSet {
public:
    ClickhouseSchemaSet(Catalog &catalog);

protected:
    virtual void LoadEntries(ClickhouseTransaction &transaction);
};
    
} // namespace duckdb
