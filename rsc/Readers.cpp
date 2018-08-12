#include "Readers.h"

using namespace rsc;

Readers::Readers(Context const &context, LPCTSTR mszGroups)
    : context(context)
    , groups(mszGroups)
{
    fetch();
}

std::vector<std::wstring> const& Readers::fetch()
{
    LPTSTR mszReaders = NULL;
    DWORD cchReaders = SCARD_AUTOALLOCATE;
    readers_.clear();
    if (
        auto result = SCardListReaders(
            context,
            groups,
            (LPTSTR)&mszReaders,
            &cchReaders
            ); result != SCARD_S_SUCCESS
        )
    {
        if (result != SCARD_E_SERVICE_STOPPED)
            throw std::system_error(result, std::system_category());
    }
    if (mszReaders) {
        for (LPTSTR pReader = mszReaders; *pReader; ) {
            readers_.emplace_back(pReader);
            pReader += readers_.back().length() + 1;
        }
        SCardFreeMemory(context, mszReaders);
    }
    return readers_;
}
