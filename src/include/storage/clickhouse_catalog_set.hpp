#pragma once

#include "storage/clickhouse_transaction.hpp"

namespace duckdb {

class ClickhouseCatalogSet {
public:
    void Scan(ClickhouseTransaction &transaction, const std::function<void(CatalogEntry &)> &callback);
    optional_ptr<CatalogEntry> GetEntry(ClickhouseTransaction &transaction, const string &name);

protected:
    virtual void LoadEntries(ClickhouseTransaction &transaction) = 0;

    void TryLoadEntries(ClickhouseTransaction &transaction);

private:
    mutex entry_lock;
	unordered_map<string, shared_ptr<CatalogEntry>> entries;
	case_insensitive_map_t<string> entry_map;
	atomic<bool> is_loaded;
};
    
} // namespace duckdb 

