#include "dropcopy/parser.hpp"
#include <cstring>

namespace dropcopy {

static FrameHeader read_header(ByteReader& rd) {
  FrameHeader h{};

main
  h.length = rd.read_u16();
  h.opcode = static_cast<OpCode>(rd.read_u16());
  h.seq = rd.read_u32();
  h.ts = rd.read_u64();
main
  return h;
}

static TradeMsg decode_trade(ByteReader& rd) {
  TradeMsg t{};
  t.symbol = rd.read_padded_string(16, '\0');
main
  t.qty = static_cast<std::int32_t>(rd.read_u32());
  t.price_nanos = static_cast<std::int64_t>(rd.read_u64());
  t.broker_id = rd.read_padded_string(5, '\0');
  t.account_number = rd.read_padded_string(10, '\0');
  t.settlor = rd.read_padded_string(12, '\0');
  return t;
}

static OrderMsg decode_order(ByteReader& rd) {
  OrderMsg o{};
  o.symbol = rd.read_padded_string(16, '\0');

  o.order_id = static_cast<std::int64_t>(rd.read_u64());
main
  o.remaining_qty = static_cast<std::int32_t>(rd.read_u32());
  o.state = rd.read_u8();
  o.account_number = rd.read_padded_string(10, '\0');
  o.settlor = rd.read_padded_string(12, '\0');
  return o;
}

std::optional<Message> parse_one(const std::uint8_t* buf, std::size_t len, std::size_t& consumed) {
  consumed = 0;
  if (len < 4) return std::nullopt;
  ByteReader rd(buf, buf + len);

  const auto frame_len = [&]() {
    ByteReader tmp(buf, buf + len);
    std::uint16_t L = tmp.read_u16();
    return static_cast<std::size_t>(L);
  }();

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
      fr.read_bytes(fr.remaining());
      msg.payload = OrderMsg{};
      break;
    }
  }

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
