#include "storage/clickhouse_schema_entry.hpp"

namespace duckdb {

optional_ptr<CatalogEntry> ClickhouseSchemaEntry::CreateTable(CatalogTransaction transaction, BoundCreateTableInfo &info) {
    throw NotImplementedException("CreateTable");
}
    
optional_ptr<CatalogEntry> ClickhouseSchemaEntry::CreateFunction(CatalogTransaction transaction, CreateFunctionInfo &info) {
    throw NotImplementedException("CreateFunction");
}
    
optional_ptr<CatalogEntry> ClickhouseSchemaEntry::CreateIndex(CatalogTransaction transaction, CreateIndexInfo &info, TableCatalogEntry &table) {
    throw NotImplementedException("CreateIndex");
}

optional_ptr<CatalogEntry> ClickhouseSchemaEntry::CreateView(CatalogTransaction transaction, CreateViewInfo &info) {
    throw NotImplementedException("CreateView");
}

optional_ptr<CatalogEntry> ClickhouseSchemaEntry::CreateSequence(CatalogTransaction transaction, CreateSequenceInfo &info) {
    throw NotImplementedException("CreateSequence");
}

optional_ptr<CatalogEntry> ClickhouseSchemaEntry::CreateTableFunction(CatalogTransaction transaction, CreateTableFunctionInfo &info) {
    throw NotImplementedException("CreateTableFunction");
}

optional_ptr<CatalogEntry> ClickhouseSchemaEntry::CreateCopyFunction(CatalogTransaction transaction, CreateCopyFunctionInfo &info) {
    throw NotImplementedException("CreateCopyFunction");
}

optional_ptr<CatalogEntry> ClickhouseSchemaEntry::CreatePragmaFunction(CatalogTransaction transaction, CreatePragmaFunctionInfo &info) {
    throw NotImplementedException("CreatePragmaFunction");
}
    
optional_ptr<CatalogEntry> ClickhouseSchemaEntry::CreateCollation(CatalogTransaction transaction, CreateCollationInfo &info) {
    throw NotImplementedException("CreateCollation");
}
    
optional_ptr<CatalogEntry> ClickhouseSchemaEntry::CreateType(CatalogTransaction transaction, CreateTypeInfo &info) {
    throw NotImplementedException("CreateType");
}
    
void ClickhouseSchemaEntry::Alter(CatalogTransaction transaction, AlterInfo &info) {
    throw NotImplementedException("Alter");
}
    
void ClickhouseSchemaEntry::Scan(ClientContext &context, CatalogType type, const std::function<void(CatalogEntry &)> &callback) {
    throw NotImplementedException("Scan");
}

void ClickhouseSchemaEntry::Scan(CatalogType type, const std::function<void(CatalogEntry &)> &callback) {
    throw NotImplementedException("Scan");
}
    
void ClickhouseSchemaEntry::DropEntry(ClientContext &context, DropInfo &info) {
    throw NotImplementedException("DropEntry");
}

bool CatalogTypeIsSupported(CatalogType type) {
    switch (type) {
        // case CatalogType::INDEX_ENTRY:
        case CatalogType::TABLE_ENTRY:
        // case CatalogType::VIEW_ENTRY:
            return true;
        default:
            return false;
    }
}
    
optional_ptr<CatalogEntry> ClickhouseSchemaEntry::LookupEntry(CatalogTransaction transaction, const EntryLookupInfo &lookup_info) {
    auto lookup_type = lookup_info.GetCatalogType();
    if (CatalogTypeIsSupported(lookup_type)) {
        return nullptr;
    }





    throw NotImplementedException("LookupEntry");
}

} // namespace duckdb

