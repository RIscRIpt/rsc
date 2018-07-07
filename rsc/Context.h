#pragma once

#include <winscard.h>

namespace rsc {

    class Context {
    public:
        Context(DWORD dwScope);
        ~Context();

        inline SCARDCONTEXT get() const noexcept { return hContext_; }

    private:
        SCARDCONTEXT hContext_;
    };

}
