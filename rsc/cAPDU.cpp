#include "cAPDU.h"

#include <scb/ByteStream.h>

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

cAPDU::cAPDU(unsigned char cla, unsigned char ins, unsigned char p1, unsigned char p2, unsigned int le)
    : CLA(cla)
    , INS(ins)
    , P1(p1)
    , P2(p2)
    , Lc(0)
    , Le(le)
{
    init_buffer();
}

cAPDU::cAPDU(unsigned char cla, unsigned char ins, unsigned char p1, unsigned char p2, scb::Bytes const &data)
    : CLA(cla)
    , INS(ins)
    , P1(p1)
    , P2(p2)
    , Lc(this->data.size())
    , Le(0)
    , data(data)
{
    init_buffer();
}

cAPDU::cAPDU(unsigned char cla, unsigned char ins, unsigned char p1, unsigned char p2, scb::Bytes &&data)
    : CLA(cla)
    , INS(ins)
    , P1(p1)
    , P2(p2)
    , Lc(this->data.size())
    , Le(0)
    , data(std::move(data))
{
    init_buffer();
}

cAPDU::cAPDU(unsigned char cla, unsigned char ins, unsigned char p1, unsigned char p2, scb::Bytes const &data, unsigned int le)
    : CLA(cla)
    , INS(ins)
    , P1(p1)
    , P2(p2)
    , Lc(this->data.size())
    , Le(le)
    , data(data)
{
    init_buffer();
}

cAPDU::cAPDU(unsigned char cla, unsigned char ins, unsigned char p1, unsigned char p2, scb::Bytes &&data, unsigned int le)
    : CLA(cla)
    , INS(ins)
    , P1(p1)
    , P2(p2)
    , Lc(this->data.size())
    , Le(le)
    , data(std::move(data))
{
    init_buffer();
}

cAPDU::cAPDU(scb::Bytes const &buffer)
    : cAPDU(from_buffer(buffer))
{}

size_t cAPDU::lc_byte_count() {
    if (Lc == 0)
        return 0;
    else if (Lc > 256)
        return 3;
    else
        return 1; // 256 == 0
}

scb::Bytes cAPDU::lc_bytes() {
    if (lc_byte_count() == 0)
        return {};

    scb::Bytes bytes(lc_byte_count());
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
        return 1; // 256 == 0
}

scb::Bytes rsc::cAPDU::le_bytes() {
    if (le_byte_count() == 0)
        return {};

    scb::Bytes bytes(le_byte_count());
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

cAPDU cAPDU::from_buffer(scb::Bytes const &buffer) {
    scb::Bytes data;
    unsigned int Lc = 0, Le = 0;
    unsigned char CLA, INS, P1, P2;

    scb::ByteStream bs(buffer);

    CLA = bs.next_u8();
    INS = bs.next_u8();
    P1 = bs.next_u8();
    P2 = bs.next_u8();
    
    if (!bs.eob()) {
        Lc = bs.next_u8();
        if (Lc & 0x80) {
            auto lbs = bs.next_bytes(Lc & 0x7F);
            Lc = 0;
            for (auto b : lbs) {
                Lc <<= 8;
                Lc |= b;
            }
        }
    } else {
        return cAPDU(CLA, INS, P1, P2);
    }

    if (!bs.eob()) {
        data = bs.next_bytes(Lc);
    } else {
        // Le = Lc;
        // Lc = 0;
        return cAPDU(CLA, INS, P1, P2, /*Le*/ Lc);
    }

    if (!bs.eob()) {
        Le = bs.next_u8();
        if (!bs.eob()) {
            do {
                Le <<= 8;
                Le |= bs.next_u8();
            } while (!bs.eob());
        } else if (Le == 0) {
            Le = 256;
        }
        return cAPDU(CLA, INS, P1, P2, std::move(data), Le);
    } else {
        return cAPDU(CLA, INS, P1, P2, std::move(data));
    }
}

void cAPDU::init_buffer() {
    buffer_ = scb::Bytes(4 + lc_byte_count() + data.size() + le_byte_count());
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

cAPDU cAPDU::SELECT(scb::Bytes name, bool by_name, bool first) {
    return cAPDU(0x00, 0xA4, by_name ? 0x04 : 0x00, first ? 0x00 : 0x02, std::move(name), 256);
}

cAPDU rsc::cAPDU::GET_RESPONSE(unsigned int Le) {
    return cAPDU(0x00, 0xC0, 0x00, 0x00, Le);
}

std::ostream& operator<<(std::ostream &os, rsc::cAPDU const &capdu) {
    capdu.buffer().print(os, " ");
    return os;
}
