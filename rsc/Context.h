#pragma once

#include <winscard.h>

namespace rsc {

    class Context {
    public:
        Context(DWORD dwScope, bool establish = true);
        ~Context() throw();

        Context(Context &&other) = default;
        Context& operator=(Context &&rhs) = default;

        Context(Context const &other) = delete;
        Context& operator=(Context const &rhs) = delete;

        void establish();
        void release();

        inline bool released() const noexcept { return hContext_ == NULL; }
        inline SCARDCONTEXT handle() const noexcept { return hContext_; }
        inline operator SCARDCONTEXT() const noexcept { return hContext_; }

    private:
        SCARDCONTEXT hContext_;
        DWORD dwScope_;
    };

}
