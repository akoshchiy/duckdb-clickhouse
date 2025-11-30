#include "storage/clickhouse_catalog.hpp"

#include "duckdb/storage/database_size.hpp"
#include "storage/clickhouse_schema_entry.hpp"


namespace duckdb {

ClickhouseCatalog::ClickhouseCatalog(
    AttachedDatabase &db, 
    string attach_path, 
    AccessMode access_mode, 
    clickhouse::ClientOptions client_options) 
    : Catalog(db), attach_path(std::move(attach_path)), access_mode(access_mode), client_options(std::move(client_options))  {
}

ClickhouseCatalog::~ClickhouseCatalog() = default;

void ClickhouseCatalog::Initialize(bool load_builtin) {
}

optional_ptr<CatalogEntry> ClickhouseCatalog::CreateSchema(CatalogTransaction transaction, CreateSchemaInfo &info) {
	throw NotImplementedException("CreateSchema");
}

void ClickhouseCatalog::ScanSchemas(ClientContext &context, std::function<void(SchemaCatalogEntry &)> callback) {
	auto &ch_transaction = ClickhouseTransaction::Get(context, *this);
    schemas.Scan(ch_transaction, [&](CatalogEntry &schema) { callback(schema.Cast<ClickhouseSchemaEntry>()); });
}

optional_ptr<SchemaCatalogEntry> ClickhouseCatalog::LookupSchema(
    CatalogTransaction transaction, 
    const EntryLookupInfo &schema_lookup,
    OnEntryNotFound if_not_found) {
	throw NotImplementedException("LookupSchema");
}

PhysicalOperator &ClickhouseCatalog::PlanCreateTableAs(
    ClientContext &context, 
    PhysicalPlanGenerator &planner,
    LogicalCreateTable &op, 
    PhysicalOperator &plan) {
	throw NotImplementedException("PlanCreateTableAs");
}

PhysicalOperator &ClickhouseCatalog::PlanInsert(
    ClientContext &context, 
    PhysicalPlanGenerator &planner, 
    LogicalInsert &op,
    optional_ptr<PhysicalOperator> plan) {
	throw NotImplementedException("PlanInsert");
}

PhysicalOperator &ClickhouseCatalog::PlanDelete(
    ClientContext &context, 
    PhysicalPlanGenerator &planner, 
    LogicalDelete &op,
    PhysicalOperator &plan) {
	throw NotImplementedException("PlanDelete");    
}

PhysicalOperator &ClickhouseCatalog::PlanUpdate(
    ClientContext &context,
    PhysicalPlanGenerator &planner, 
    LogicalUpdate &op,
    PhysicalOperator &plan) {
	throw NotImplementedException("PlanUpdate");    
}

DatabaseSize ClickhouseCatalog::GetDatabaseSize(ClientContext &context) {
	throw NotImplementedException("GetDatabaseSize");    
}

bool ClickhouseCatalog::InMemory() {
    return false;
}

string ClickhouseCatalog::GetDBPath() {
    return attach_path;
}

void ClickhouseCatalog::DropSchema(ClientContext &context, DropInfo &info) {
	throw NotImplementedException("DropSchema");    
}

} // namespace duckdb