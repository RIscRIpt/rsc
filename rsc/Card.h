#pragma once

#include "Context.h"

#include <vector>

#include <winscard.h>

namespace rsc {

    class Card {
    public:
        Card(Context const &context, LPCTSTR szReader);
        ~Card();

        inline SCARDHANDLE handle() const noexcept { return hCard_; }
        inline DWORD protocol() const noexcept { return dwActiveProtocol_; }

        LPCSCARD_IO_REQUEST pci() const noexcept;

        std::vector<BYTE> transmit();

        Context const &context;

    private:
        SCARDHANDLE hCard_;
        DWORD dwActiveProtocol_;
    };

}
