#include "Card.h"

#include <system_error>

using namespace rsc;

Card::Card(Context const &context, LPCTSTR szReader)
    : context(context)
{
    if (
        auto result = SCardConnect(
            context.handle(),
            szReader,
            SCARD_SHARE_EXCLUSIVE,
            SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1,
            &hCard_,
            &dwActiveProtocol_
        ); result != SCARD_S_SUCCESS
        )
        throw std::system_error(result, std::system_category());
    fetch_status();
}

Card::Card(Context const &context, std::wstring const &reader)
    : Card(context, reader.c_str())
{}

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

void Card::warm_reset() {
    reset(SCARD_RESET_CARD);
}

void Card::cold_reset() {
    reset(SCARD_UNPOWER_CARD);
}

void Card::reset(DWORD dwInitialization) {
    if (
        auto result = SCardReconnect(
            hCard_,
            SCARD_SHARE_EXCLUSIVE,
            SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1,
            dwInitialization,
            &dwActiveProtocol_
        ); result != SCARD_S_SUCCESS
        )
        throw std::system_error(result, std::system_category());
}

rAPDU Card::raw_transmit(cAPDU const & capdu) {
    rAPDU rapdu;
    DWORD actual_length = rapdu.buffer().size();
    if (
        auto result = SCardTransmit(
            hCard_,
            pci(),
            capdu.buffer().data(),
            capdu.buffer().size(),
            NULL,
            rapdu.buffer().data(),
            &actual_length
        ); result != SCARD_S_SUCCESS
        )
        throw std::system_error(result, std::system_category());
    rapdu.resize(actual_length);
    return rapdu;
}

rAPDU Card::transmit(cAPDU const &capdu) {
    rAPDU result;
    result = raw_transmit(capdu);
    if (result.SW().response_bytes_still_available()) {
        result = raw_transmit(cAPDU(0x00, 0xC0, 0x00, 0x00, result.SW().response_bytes_still_available()));
    }
    return result;
}

void Card::fetch_status() {
    LPTSTR mszReaderNames;
    DWORD cchReaderLen = SCARD_AUTOALLOCATE;
    DWORD cbAtrLen;
    atr_ = scb::Bytes(32);
    if (
        auto result = SCardStatus(
            hCard_,
            (LPTSTR)&mszReaderNames,
            &cchReaderLen,
            &dwState_,
            &dwActiveProtocol_,
            atr_.data(),
            &cbAtrLen
        ); result != SCARD_S_SUCCESS
        )
        throw std::system_error(result, std::system_category());

    atr_.resize(cbAtrLen);
    atr_.shrink_to_fit();

    readerNames_ = {};
    for (LPTSTR pReaderName = mszReaderNames; *pReaderName; ) {
        readerNames_.emplace_back(pReaderName);
        pReaderName += readerNames_.back().length();
    }
    readerNames_.shrink_to_fit();

    if (auto result = SCardFreeMemory(context.handle(), mszReaderNames); result != SCARD_S_SUCCESS)
        throw std::system_error(result, std::system_category());
}

