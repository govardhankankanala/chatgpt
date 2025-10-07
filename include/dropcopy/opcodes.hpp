#pragma once
#include <cstdint>

namespace dropcopy {

// === AUTO-UPDATE: OPCODES START ===
enum class OpCode : std::uint16_t {
  Unknown   = 0,
  Heartbeat = 23506, // Updated for HEARTBEAT
  Trade     = 2222,  // Updated for TRADE_CONFIRMATION
  Order     = 2073,  // Updated for ORDER_CONFIRMATION
  // Add more opcodes as per circular
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
  DCSignonIn = 2500,
  DCSignonOut = 2501,
  GRSecureUserRegistrationRequest = 23008,
  GRSecureUserRegistrationResponse = 23009,
  DCTrdSubscriptionRequest = 8000,
  DCOntSubscriptionRequest = 9000,
  DCErrorResponseOrder = 9006,
  DCErrorResponseTrade = 8006
};
// === AUTO-UPDATE: OPCODES END ===

} // namespace dropcopy
