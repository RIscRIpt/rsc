#pragma once

#include "Context.h"
#include "cAPDU.h"
#include "rAPDU.h"

#include <vector>

#include <winscard.h>

#include <scb/bytes.h>

namespace rsc {

    class Card {
    public:
        Card(Context const &context, LPCTSTR szReader);
        Card(Context const &context, std::wstring const &reader);
        ~Card();

        LPCSCARD_IO_REQUEST pci() const noexcept;

        void warm_reset();
        void cold_reset();
        rAPDU raw_transmit(cAPDU const &capdu);
        rAPDU transmit(cAPDU const &capdu);
        void fetch_status();

        inline SCARDHANDLE handle() const noexcept { return hCard_; }
        inline DWORD protocol() const noexcept { return dwActiveProtocol_; }
        inline DWORD state() const noexcept { return dwState_; }
        inline std::vector<std::wstring> const& reader_names() const noexcept { return readerNames_; }
        inline scb::Bytes const& atr() const noexcept { return atr_; }

        Context const &context;

    private:
        void reset(DWORD dwInitialization);

        SCARDHANDLE hCard_;
        DWORD dwActiveProtocol_;
        DWORD dwState_;

        std::vector<std::wstring> readerNames_;
        scb::Bytes atr_;
    };

}
