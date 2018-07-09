#pragma once

#include <vector>
#include <optional>

namespace rsc {

    class cAPDU {
    public:
        cAPDU(unsigned char cla, unsigned char ins, unsigned char p1, unsigned char p2);
        cAPDU(unsigned char cla, unsigned char ins, unsigned char p1, unsigned char p2, std::vector<unsigned char> const &data);
        cAPDU(unsigned char cla, unsigned char ins, unsigned char p1, unsigned char p2, std::vector<unsigned char> &&data);
        cAPDU(unsigned char cla, unsigned char ins, unsigned char p1, unsigned char p2, std::vector<unsigned char> const &data, unsigned int le);
        cAPDU(unsigned char cla, unsigned char ins, unsigned char p1, unsigned char p2, std::vector<unsigned char> &&data, unsigned int le);

        cAPDU(cAPDU const &rhs) = default;
        cAPDU(cAPDU &&rhs) = default;

        cAPDU& operator=(cAPDU const &rhs) = default;
        cAPDU& operator=(cAPDU &&rhs) = default;

        std::vector<unsigned char> const data;
        size_t const Lc, Le;
        unsigned char const CLA, INS, P1, P2;

        inline std::vector<unsigned char> const& buffer() const noexcept { return buffer_; }

        size_t lc_byte_count();
        std::vector<unsigned char> lc_bytes();

        size_t le_byte_count();
        std::vector<unsigned char> le_bytes();

    private:
        void init_buffer();

        std::vector<unsigned char> buffer_;
    };

}
