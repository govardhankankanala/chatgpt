#include "dropcopy/parser.hpp"
#include <cstring>

namespace dropcopy {

static FrameHeader read_header(ByteReader& rd) {
  FrameHeader h{};
  // === AUTO-UPDATE: HEADER DECODE START ===
  // Length + opcode (little-endian). Adjust per circulars if needed.
  h.length = rd.read_u16();
  h.opcode = static_cast<OpCode>(rd.read_u16());
  // Optional fields (sequence, timestamp). Keep zero if not present.
  // (Automation may replace this block entirely.)
  // === AUTO-UPDATE: HEADER DECODE END ===
  return h;
}

// Placeholder decoders; automation will expand fields per circulars.
static TradeMsg decode_trade(ByteReader& rd) {
  TradeMsg t{};
  t.symbol = rd.read_padded_string(16, '\0'); // 16-byte sym
  t.qty = static_cast<std::int32_t>(rd.read_u32());
  t.price_nanos = static_cast<std::int64_t>(rd.read_u64());
  return t;
}

static OrderMsg decode_order(ByteReader& rd) {
  OrderMsg o{};
  o.symbol = rd.read_padded_string(16, '\0');
  o.order_id = static_cast<std::int64_t>(rd.read_u64());
  o.remaining_qty = static_cast<std::int32_t>(rd.read_u32());
  o.state = rd.read_u8();
  return o;
}

std::optional<Message> parse_one(const std::uint8_t* buf, std::size_t len, std::size_t& consumed) {
  consumed = 0;
  if (len < 4) return std::nullopt; // need at least length+opcode
  ByteReader rd(buf, buf + len);

  const auto frame_len = [&]() {
    ByteReader tmp(buf, buf + len);
    std::uint16_t L = tmp.read_u16();
    return static_cast<std::size_t>(L);
  }();

  // Protect against inconsistent/short frames.
  if (frame_len == 0 || frame_len > len) return std::nullopt;

  ByteReader fr(buf, buf + frame_len);

  FrameHeader h = read_header(fr);

  Message msg;
  msg.header = h;

  switch (h.opcode) {
    case OpCode::Trade: {
      msg.payload = decode_trade(fr);
      break;
    }
    case OpCode::Order: {
      msg.payload = decode_order(fr);
      break;
    }
    default: {
      // Unknown opcode; consume frame but ignore payload.
      fr.read_bytes(fr.remaining());
      msg.payload = OrderMsg{}; // benign placeholder
      break;
    }
  }

  // Consume exactly this frame.
  consumed = frame_len;
  return msg;
}

std::vector<Message> parse_many(const std::uint8_t* buf, std::size_t len) {
  std::vector<Message> out;
  std::size_t off = 0;
  while (off + 4 <= len) {
    std::size_t used = 0;
    auto one = parse_one(buf + off, len - off, used);
    if (!one) break;
    out.push_back(std::move(*one));
    off += used;
  }
  return out;
}

} // namespace dropcopy
