#pragma once
#include <cstdint>
#include <vector>
#include <optional>
#include "dropcopy/messages.hpp"
#include "dropcopy/types.hpp"
#include "dropcopy/errors.hpp"

namespace dropcopy {

// Parse a single frame from a byte span.
// On success returns Message and advances 'consumed' bytes.
// If not enough data: returns std::nullopt (need more bytes).
std::optional<Message> parse_one(const std::uint8_t* buf, std::size_t len, std::size_t& consumed);

// Parse many frames from a buffer.
std::vector<Message> parse_many(const std::uint8_t* buf, std::size_t len);

} // namespace dropcopy
