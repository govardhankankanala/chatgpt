#pragma once
#include <cstdint>

namespace dropcopy {

// === AUTO-UPDATE: OPCODES START ===
// Placeholder opcodes. Automation will add/change values per circulars.
enum class OpCode : std::uint16_t {
  Unknown   = 0,
  Heartbeat = 1,
  Trade     = 5000,
  Order     = 5001,
  // (add more ops here)
};
// === AUTO-UPDATE: OPCODES END ===

} // namespace dropcopy
