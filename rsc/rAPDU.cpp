#include "rAPDU.h"

using namespace rsc;

rAPDU::rAPDU(size_t Le)
    : buffer_(Le + 2)
{
    buffer_[buffer_.size() - 2] = 0x90;
    buffer_[buffer_.size() - 1] = 0x00;
}

SW rAPDU::SW() const noexcept {
    return (SW1() << 8) | SW2();
}

uint8_t rAPDU::SW1() const noexcept {
    return buffer_[buffer_.size() - 2];
}

uint8_t rAPDU::SW2() const noexcept {
    return buffer_[buffer_.size() - 1];
}

void rAPDU::resize(size_t actual_length) {
    buffer_.resize(actual_length);
    buffer_.shrink_to_fit();
}

TLVList rAPDU::tlv_list() const {
    return TLVList(buffer_.begin(), buffer_.end() - 2);
}
