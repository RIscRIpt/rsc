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
    if (
        auto result = SCardListReaders(
            context.handle(),
            groups,
            (LPTSTR)mszReaders,
            &cchReaders
            ); result != SCARD_S_SUCCESS
        )
        throw std::system_error(result, std::system_category());
    for (LPTSTR pReader = mszReaders; *pReader; ) {
        readers_.emplace_back(pReader);
        pReader += readers_.back().length();
    }
    return readers_;
}
