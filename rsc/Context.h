#pragma once

#include <winscard.h>

namespace rsc {

    class Context {
    public:
        Context(DWORD dwScope);
        ~Context();

        inline SCARDCONTEXT handle() const noexcept { return hContext_; }

    private:
        SCARDCONTEXT hContext_;
    };

}
