#pragma once

#include <winscard.h>

namespace rsc {

    class Context {
    public:
        Context(DWORD dwScope);
        ~Context();

        Context(Context const &other) = delete;
        Context& operator=(Context const &rhs) = delete;

        inline SCARDCONTEXT handle() const noexcept { return hContext_; }
        inline operator SCARDCONTEXT() const noexcept { return hContext_; }

    private:
        SCARDCONTEXT hContext_;
    };

}
