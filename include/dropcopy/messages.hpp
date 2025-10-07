#pragma once
#include <cstdint>
#include <string>
#include <variant>
#include <vector>
#include "dropcopy/opcodes.hpp"

namespace dropcopy {

// === AUTO-UPDATE: HEADER START ===
// Generic frame header (assumed little-endian).
// Adjust fields/order per NSE spec; automation will patch this section.
struct FrameHeader {
  std::uint16_t length;   // bytes including header+payload OR just payload? (see spec)
  OpCode        opcode;   // message type
  std::uint32_t seq = 0;  // optional
  std::uint64_t ts  = 0;  // optional epoch micros
};
// === AUTO-UPDATE: HEADER END ===

// === AUTO-UPDATE: MESSAGES START ===
// Minimal placeholder payloads. Automation will replace/add fields.
struct TradeMsg {
  std::string   symbol;
  std::int32_t  qty = 0;              // signed for sell?
  std::int64_t  price_nanos = 0;      // price * 1e9 as integer
};

struct OrderMsg {
  std::string   symbol;
  std::int64_t  order_id = 0;
  std::int32_t  remaining_qty = 0;
  std::uint8_t  state = 0;            // e.g., 0=new,1=part,2=filled,3=cxl, etc.
};
// === AUTO-UPDATE: MESSAGES END ===

using Payload = std::variant<TradeMsg, OrderMsg>;

struct Message {
  FrameHeader header{};
  Payload     payload;
};

} // namespace dropcopy
