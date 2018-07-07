#include "Card.h"

#include <system_error>

using namespace rsc;

Card::Card(Context const &context, LPCTSTR szReader)
    : context(context)
{
    if (
        auto result = SCardConnect(
            context.get(),
            szReader,
            SCARD_SHARE_EXCLUSIVE,
            SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1,
            &hCard_,
            &dwActiveProtocol_
        ); result != SCARD_S_SUCCESS
        )
        throw std::system_error(result, std::system_category());
}

Card::~Card() {
    SCardDisconnect(hCard_, SCARD_RESET_CARD);
}

LPCSCARD_IO_REQUEST Card::pci() const noexcept {
    switch (dwActiveProtocol_) {
        case SCARD_PROTOCOL_T0:
            return SCARD_PCI_T0;
        case SCARD_PROTOCOL_T1:
            return SCARD_PCI_T1;
        case SCARD_PROTOCOL_RAW:
            return SCARD_PCI_RAW;
        default:
            return NULL;
    }
}

std::vector<BYTE> Card::transmit() {
    std::vector<BYTE> buffer(256);
    DWORD length = buffer.size();
    if (
        auto result = SCardTransmit(
            hCard_,
            pci(),
            NULL,
            NULL,
            NULL,
            buffer.data(),
            &length
        ); result != SCARD_S_SUCCESS
        )
        throw std::system_error(result, std::system_category());
    return buffer;
}
