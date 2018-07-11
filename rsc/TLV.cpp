#include "TLV.h"
#include "TLVList.h"

using namespace rsc;

TLV::TLV(unsigned char const *buffer)
    : TL(buffer)
{
    unsigned char const *value_begin = buffer + tag_.size() + length_.size();
    unsigned char const *value_end = value_begin + length_.value();
    value_ = std::vector<unsigned char>(value_begin, value_end);
}

TLVList TLV::value_as_tlv_list() const {
    return TLVList(value_);
}
