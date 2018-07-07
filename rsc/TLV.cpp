#include "TLV.h"

using namespace rsc;

TLV::TLV(unsigned char const *buffer)
    : tag_(buffer)
    , length_(buffer + tag_.size())
{
    unsigned char const *value_begin = buffer + tag_.size() + length_.size();
    unsigned char const *value_end = value_begin + length_.value();
    value_ = std::vector<unsigned char>(value_begin, value_end);
}

TLV TLV::value_as_tlv() const {
    return TLV(value_.data());
}
