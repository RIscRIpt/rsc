#pragma once

#include "Context.h"

#include <vector>
#include <string>

namespace rsc {

    class Readers {
    public:
        Readers(Context const &context, LPCTSTR mszGroups);

        std::vector<std::wstring> const& fetch();
        inline std::vector<std::wstring> const& list() const noexcept { return readers_; }

        Context const &context;
        LPCTSTR const groups;

    private:
        std::vector<std::wstring> readers_;
    };

}
