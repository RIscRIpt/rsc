#include "Context.h"

#include <system_error>

using namespace rsc;

Context::Context(DWORD dwScope) {
    if (auto result = SCardEstablishContext(dwScope, NULL, NULL, &hContext_); result != SCARD_S_SUCCESS)
        throw std::system_error(result, std::system_category());
}

Context::~Context() {
    if (hContext_ != NULL) {
        SCardReleaseContext(hContext_);
        hContext_ = NULL;
    }
}
