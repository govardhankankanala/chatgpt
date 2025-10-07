#include "dropcopy/parser.hpp"
#include "dropcopy/config.hpp"
#include <fstream>
#include <iostream>

using namespace dropcopy;

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <binary_file>\n";
    return 1;
  }

  std::ifstream f(argv[1], std::ios::binary);
  if (!f) { std::cerr << "Cannot open " << argv[1] << "\n"; return 1; }
  std::vector<std::uint8_t> buf((std::istreambuf_iterator<char>(f)), {});

  auto msgs = parse_many(buf.data(), buf.size());
  std::cout << "Parsed " << msgs.size() << " message(s)\n";

  Config cfg;
  int loaded = cfg.load_symbol_table("data/symbols.csv");
  std::cout << "Loaded " << loaded << " symbols\n";

  // Dump a tiny view of messages
  for (auto& m : msgs) {
    switch (m.header.opcode) {
      case OpCode::Trade: {
        const auto& t = std::get<TradeMsg>(m.payload);
        std::cout << "TRADE " << t.symbol << " qty=" << t.qty << " pxNanos=" << t.price_nanos << "\n";
        break;
      }
      case OpCode::Order: {
        const auto& o = std::get<OrderMsg>(m.payload);
        std::cout << "ORDER " << o.symbol << " id=" << o.order_id << " rem=" << o.remaining_qty << " st=" << int(o.state) << "\n";
        break;
      }
      default:
        std::cout << "UNKNOWN opcode=" << static_cast<int>(m.header.opcode) << "\n";
        break;
    }
  }
  return 0;
}
