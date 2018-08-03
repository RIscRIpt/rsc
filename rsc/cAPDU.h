#pragma once

#include <vector>
#include <optional>

#include <scb/Bytes.h>

namespace rsc {

    class cAPDU {
    public:
        cAPDU(unsigned char cla, unsigned char ins, unsigned char p1, unsigned char p2);
        cAPDU(unsigned char cla, unsigned char ins, unsigned char p1, unsigned char p2, unsigned int le);
        cAPDU(unsigned char cla, unsigned char ins, unsigned char p1, unsigned char p2, scb::Bytes const &data);
        cAPDU(unsigned char cla, unsigned char ins, unsigned char p1, unsigned char p2, scb::Bytes &&data);
        cAPDU(unsigned char cla, unsigned char ins, unsigned char p1, unsigned char p2, scb::Bytes const &data, unsigned int le);
        cAPDU(unsigned char cla, unsigned char ins, unsigned char p1, unsigned char p2, scb::Bytes &&data, unsigned int le);
        cAPDU(scb::Bytes const &buffer);

        cAPDU(cAPDU const &rhs) = default;
        cAPDU(cAPDU &&rhs) = default;

        cAPDU& operator=(cAPDU const &rhs) = default;
        cAPDU& operator=(cAPDU &&rhs) = default;

        scb::Bytes const data;
        size_t const Lc, Le;
        unsigned char const CLA, INS, P1, P2;

        inline scb::Bytes const& buffer() const noexcept { return buffer_; }

        size_t lc_byte_count();
        scb::Bytes lc_bytes();

        size_t le_byte_count();
        scb::Bytes le_bytes();

        static cAPDU SELECT(scb::Bytes name, bool by_name = true, bool first = true);
        static cAPDU GET_RESPONSE(unsigned int Le);

    private:
        cAPDU from_buffer(scb::Bytes const &buffer);

        void init_buffer();

        scb::Bytes buffer_;
    };

}

std::ostream& operator<<(std::ostream &os, rsc::cAPDU const &capdu);
