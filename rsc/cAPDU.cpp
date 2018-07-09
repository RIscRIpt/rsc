#include "cAPDU.h"

using namespace rsc;

cAPDU::cAPDU(unsigned char cla, unsigned char ins, unsigned char p1, unsigned char p2)
    : CLA(cla)
    , INS(ins)
    , P1(p1)
    , P2(p2)
    , Lc(0)
    , Le(0)
{
    init_buffer();
}

cAPDU::cAPDU(unsigned char cla, unsigned char ins, unsigned char p1, unsigned char p2, std::vector<unsigned char> const &data)
    : CLA(cla)
    , INS(ins)
    , P1(p1)
    , P2(p2)
    , Lc(data.size())
    , Le(0)
    , data(data)
{
    init_buffer();
}

cAPDU::cAPDU(unsigned char cla, unsigned char ins, unsigned char p1, unsigned char p2, std::vector<unsigned char> &&data)
    : CLA(cla)
    , INS(ins)
    , P1(p1)
    , P2(p2)
    , Lc(data.size())
    , Le(0)
    , data(std::move(data))
{
    init_buffer();
}

cAPDU::cAPDU(unsigned char cla, unsigned char ins, unsigned char p1, unsigned char p2, std::vector<unsigned char> const &data, unsigned int le)
    : CLA(cla)
    , INS(ins)
    , P1(p1)
    , P2(p2)
    , Lc(data.size())
    , Le(le)
    , data(data)
{
    init_buffer();
}

cAPDU::cAPDU(unsigned char cla, unsigned char ins, unsigned char p1, unsigned char p2, std::vector<unsigned char> &&data, unsigned int le)
    : CLA(cla)
    , INS(ins)
    , P1(p1)
    , P2(p2)
    , Lc(data.size())
    , Le(le)
    , data(std::move(data))
{
    init_buffer();
}

size_t cAPDU::lc_byte_count() {
    if (Lc == 0)
        return 0;
    else if (Lc > 256)
        return 3;
    else
        return 1;
}

std::vector<unsigned char> cAPDU::lc_bytes() {
    if (lc_byte_count() == 0)
        return {};

    std::vector<unsigned char> bytes(lc_byte_count());
    if (bytes.size() == 3) {
        bytes[0] = 0;
        bytes[1] = static_cast<unsigned char>(Lc >> 8);
        bytes[2] = static_cast<unsigned char>(Lc & 0xFF);
    } else if (bytes.size() == 1) {
        bytes[0] = static_cast<unsigned char>(Lc);
    } else {
        throw std::runtime_error("unexpected bytes.size()");
    }

    return bytes;
}

size_t cAPDU::le_byte_count() {
    if (Le == 0)
        return 0;
    else if (Le > 256)
        return 2;
    else
        return 1;
}

std::vector<unsigned char> rsc::cAPDU::le_bytes() {
    if (le_byte_count() == 0)
        return {};

    std::vector<unsigned char> bytes(le_byte_count());
    if (bytes.size() == 3) {
        bytes[0] = static_cast<unsigned char>(Le >> 8);
        bytes[1] = static_cast<unsigned char>(Le & 0xFF);
    } else if (bytes.size() == 1) {
        bytes[0] = static_cast<unsigned char>(Le);
    } else {
        throw std::runtime_error("unexpected bytes.size()");
    }

    return bytes;
}

void cAPDU::init_buffer() {
    buffer_ = std::vector<unsigned char>(4 + lc_byte_count() + data.size() + le_byte_count());
    buffer_[0] = CLA;
    buffer_[1] = INS;
    buffer_[2] = P1;
    buffer_[3] = P2;
    if (!data.empty()) {
        auto lc = lc_bytes();
        std::copy(lc.begin(), lc.end(), buffer_.begin() + 4);
        std::copy(data.begin(), data.end(), buffer_.begin() + 4 + lc_byte_count());
    }
    if (Le != 0) {
        auto le = le_bytes();
        std::copy(le.begin(), le.end(), buffer_.end() - le.size());
    }
}
