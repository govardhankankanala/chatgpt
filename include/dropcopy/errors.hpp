#pragma once
#include <stdexcept>

namespace dropcopy {
struct parse_error : std::runtime_error {
  using std::runtime_error::runtime_error;
};
} // namespace dropcopy
