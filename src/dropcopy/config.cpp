#include "dropcopy/config.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>

namespace dropcopy {

static inline std::string trim(std::string s) {
  auto issp = [](unsigned char c){ return c==' '||c=='\t'||c=='\r'||c=='\n'; };
  while (!s.empty() && issp(s.front())) s.erase(s.begin());
  while (!s.empty() && issp(s.back()))  s.pop_back();
  return s;
}

int Config::load_symbol_table(const std::string& csv_path) {
  std::ifstream f(csv_path);
  if (!f) return 0;
  std::string line;
  int count = 0;
  bool header_skipped = false;
  while (std::getline(f, line)) {
    if (!header_skipped) { header_skipped = true; continue; }
    std::stringstream ss(line);
    std::string sym, lot, tick;
    if (!std::getline(ss, sym, ',')) continue;
    if (!std::getline(ss, lot, ',')) continue;
    if (!std::getline(ss, tick, ',')) continue;
    sym  = trim(sym);
    lot  = trim(lot);
    tick = trim(tick);
    if (sym.empty()) continue;
    SymbolInfo info{};
    info.lot_size = std::stoi(lot);
    info.tick_size = std::stod(tick);
    symbols_[sym] = info;
    ++count;
  }
  return count;
}

std::optional<SymbolInfo> Config::lookup(const std::string& sym) const {
  auto it = symbols_.find(sym);
  if (it == symbols_.end()) return std::nullopt;
  return it->second;
}

} // namespace dropcopy
