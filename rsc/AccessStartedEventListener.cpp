#include "AccessStartedEventListener.h"

#include <system_error>


AccessStartedEventListener::AccessStartedEventListener()
    : hEvent_(SCardAccessStartedEvent())
{
    if (!hEvent_)
        throw std::system_error(GetLastError(), std::generic_category());
}

AccessStartedEventListener::~AccessStartedEventListener() {
    SCardReleaseStartedEvent();
}

bool AccessStartedEventListener::wait(DWORD timeout) const {
    auto result = WaitForSingleObject(hEvent_, timeout);
    switch (result) {
        case WAIT_OBJECT_0:
            return true;
        case WAIT_ABANDONED:
        case WAIT_TIMEOUT:
            break;
        default:
            throw std::system_error(GetLastError(), std::generic_category());
    }
    return false;
}
