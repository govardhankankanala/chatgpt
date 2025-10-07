#include "dropcopy/parser.hpp"
#include <cassert>
#include <iostream>

using namespace dropcopy;

static std::vector<std::uint8_t> build_trade_frame() {
  // Build: [len(LE)=2+2+16+4+8=32][opcode=Trade(5000)][symbol(16)][qty(4)][priceNanos(8)]
  std::vector<std::uint8_t> b;
  auto push16 = [&](std::uint16_t v){ b.push_back(v & 0xFF); b.push_back((v>>8)&0xFF); };
  auto push32 = [&](std::uint32_t v){ for (int i=0;i<4;i++) b.push_back((v>>(8*i))&0xFF); };
  auto push64 = [&](std::uint64_t v){ for (int i=0;i<8;i++) b.push_back((v>>(8*i))&0xFF); };

  const std::uint16_t len = 2 + 2 + 16 + 4 + 8;
  push16(len);
  push16(static_cast<std::uint16_t>(OpCode::Trade));

  std::string sym = "NIFTY";
  for (size_t i=0;i<16;i++) b.push_back(i<sym.size()? sym[i] : 0);

  push32(50);         // qty
  push64(2000000000); // priceNanos

  return b;
}

int main() {
  auto buf = build_trade_frame();
  size_t consumed = 0;
  auto parsed = parse_one(buf.data(), buf.size(), consumed);
  assert(parsed.has_value());
  assert(consumed == buf.size());
  const auto& t = std::get<TradeMsg>(parsed->payload);
  assert(t.symbol == "NIFTY");
  assert(t.qty == 50);
  assert(t.price_nanos == 2000000000LL);
  std::cout << "OK\n";
  return 0;
}
