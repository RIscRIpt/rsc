#include "Context.h"

#include <system_error>

using namespace rsc;

Context::Context(DWORD dwScope, bool establish)
    : hContext_(NULL)
    , dwScope_(dwScope)
{
    if (establish)
        this->establish();
}

Context::~Context() {
    release();
}

void Context::establish() {
    release();
    if (auto result = SCardEstablishContext(dwScope_, NULL, NULL, &hContext_); result != SCARD_S_SUCCESS)
        throw std::system_error(result, std::system_category());
}

void Context::release() {
    if (!released()) {
        SCardReleaseContext(hContext_);
        hContext_ = NULL;
    }
}
