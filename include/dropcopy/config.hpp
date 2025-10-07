#pragma once
#include <string>
#include <unordered_map>
#include <optional>

namespace dropcopy {

// Lot/tick table loaded from CSV (data/symbols.csv).
struct SymbolInfo {
  int    lot_size = 0;
  double tick_size = 0.0;
};

class Config {
public:
  // Load "SYMBOL,LOT_SIZE,TICK_SIZE" CSV
  // Returns number of rows loaded.
  int load_symbol_table(const std::string& csv_path);

  std::optional<SymbolInfo> lookup(const std::string& sym) const;

private:
  std::unordered_map<std::string, SymbolInfo> symbols_;
};

} // namespace dropcopy
