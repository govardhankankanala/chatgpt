#pragma once
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include <string_view>

namespace dropcopy {

// ByteReader: bounds-checked little-endian reader.
// NOTE: If NSE protocol specifies BIG endian, change read_u16/32/64 accordingly
// (your automation can update this).
class ByteReader {
  const std::uint8_t* p_;
  const std::uint8_t* end_;
public:
  ByteReader(const std::uint8_t* begin, const std::uint8_t* end) : p_(begin), end_(end) {}

  std::size_t remaining() const { return static_cast<std::size_t>(end_ - p_); }
  const std::uint8_t* data() const { return p_; }

  void require(std::size_t n) {
    if (remaining() < n) throw std::out_of_range("buffer underflow");
  }

  std::uint8_t  read_u8()  { require(1); return *p_++; }
  std::uint16_t read_u16() { require(2); std::uint16_t v = p_[0] | (std::uint16_t(p_[1])<<8); p_ += 2; return v; }
  std::uint32_t read_u32() { require(4); std::uint32_t v = p_[0] | (std::uint32_t(p_[1])<<8) | (std::uint32_t(p_[2])<<16) | (std::uint32_t(p_[3])<<24); p_ += 4; return v; }
  std::uint64_t read_u64() {
    require(8);
    std::uint64_t v = 0;
    for (int i=0;i<8;i++) v |= (std::uint64_t(p_[i]) << (8*i));
    p_ += 8; return v;
  }

  std::string read_padded_string(std::size_t n, char pad = '\0') {
    require(n);
    std::string s(reinterpret_cast<const char*>(p_), n);
    p_ += n;
    // trim trailing pad or spaces
    while (!s.empty() && (s.back() == pad || s.back() == ' ')) s.pop_back();
    return s;
  }

  std::string read_bytes(std::size_t n) {
    require(n);
    std::string s(reinterpret_cast<const char*>(p_), n);
    p_ += n; return s;
  }
};

} // namespace dropcopy
