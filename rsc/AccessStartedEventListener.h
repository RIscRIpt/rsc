#pragma once

#include <winscard.h>

class AccessStartedEventListener {
public:
    AccessStartedEventListener();
    ~AccessStartedEventListener();

    bool wait(DWORD timeout) const;

private:
    HANDLE hEvent_;
};
