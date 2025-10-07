#pragma once
#include <cstdint>
#include <string>
#include <variant>
#include <vector>
#include "dropcopy/opcodes.hpp"

namespace dropcopy {

// === AUTO-UPDATE: HEADER START ===
struct FrameHeader {
  std::uint16_t length;   // bytes including header+payload
  OpCode        opcode;   // message type
  std::uint32_t seq = 0;  // sequence number
  std::uint64_t ts  = 0;  // timestamp in nanoseconds
};
// === AUTO-UPDATE: HEADER END ===

// === AUTO-UPDATE: MESSAGES START ===
struct TradeMsg {
  std::string   symbol;
  std::int64_t  order_number = 0;
  std::int32_t  qty = 0;
  std::int64_t  price_nanos = 0;
  std::string   broker_id;
  std::string   account_number;
  std::string   settlor;
};

struct OrderMsg {
  std::string   symbol;
  std::int64_t  order_id = 0;
  std::int32_t  remaining_qty = 0;
  std::uint8_t  state = 0;
  std::string   account_number;
  std::string   settlor;
};
// === AUTO-UPDATE: MESSAGES END ===

using Payload = std::variant<TradeMsg, OrderMsg>;

struct Message {
  FrameHeader header{};
  Payload     payload;
};

} // namespace dropcopy
