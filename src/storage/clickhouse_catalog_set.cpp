#include "storage/clickhouse_catalog_set.hpp"

namespace duckdb {

void ClickhouseCatalogSet::Scan(
    ClickhouseTransaction &transaction, 
    const std::function<void(CatalogEntry &)> &callback) {
	TryLoadEntries(transaction);
	lock_guard<mutex> l(entry_lock);
	for (auto &entry : entries) {
		callback(*entry.second);
	}
}

optional_ptr<CatalogEntry> ClickhouseCatalogSet::GetEntry(
    ClickhouseTransaction &transaction, 
    const string &name) {
    TryLoadEntries(transaction);
    auto entry = entries.find(name);
    if (entry == entries.end()) {
        return nullptr;
    }
    return entry->second.get();
}


void ClickhouseCatalogSet::TryLoadEntries(ClickhouseTransaction &transaction) {
    if (is_loaded) {
        return;
    }
    LoadEntries(transaction);
    is_loaded = true;
}
    

} // namespace duckdb 
