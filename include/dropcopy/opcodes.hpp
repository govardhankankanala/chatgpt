#pragma once
#include <cstdint>

namespace dropcopy {

// === AUTO-UPDATE: OPCODES START ===
enum class OpCode : std::uint16_t {
  Unknown   = 0,
  Heartbeat = 23506,
  Trade     = 2222,
  Order     = 2073,
  // Additional opcodes based on circular
  TradeCancelConfirm = 2282,
  TradeCancelReject = 2286,
  TradeModifyConfirm = 2287,
  OrderModReject = 2042,
  OrderCancelReject = 2072,
  OrderModConfirm = 2074,
  OrderCancelConfirm = 2075,
  FreezeToControl = 2170,
  OnStopNotification = 2212,
  OrderError = 2231,
  BatchOrderCancel = 9002,
  PriceConfirmation = 2012,
  // (add more ops here)
};
// === AUTO-UPDATE: OPCODES END ===

} // namespace dropcopy
