#include "EventListener.h"

#include "Readers.h"

#include <system_error>

using namespace rsc;

DWORD const EventListener::MAX_TIMEOUT = 1024;
LPCTSTR EventListener::NEW_READER = TEXT("\\\\?PnP?\\Notification");

EventListener::EventListener(Context const &context) 
    : context(context)
    , newReaders_(true)
{}

void EventListener::start(DWORD eventFilter, CallbackFn callback) {
    eventFilter_ = eventFilter;
    callback_ = callback;
    toListen_ = true;
    listeningThread_ = std::thread(std::bind(&EventListener::listener, this));
}

void EventListener::stop() {
    toListen_ = false;
    listeningThread_.join();
}

void EventListener::set_listening_readers(std::vector<std::wstring> const &readers) {
    readers_.clear();
    for (auto const &reader : readers) {
        readers_.emplace(reader, SCARD_STATE_UNAWARE);
    }
}

void EventListener::listen_new_readers(bool toggle) {
    newReaders_ = toggle;
}

void EventListener::listener() {
    while (toListen_) {
        auto readerStates = get_reader_states();
        auto result = SCardGetStatusChange(
            context,
            MAX_TIMEOUT,
            readerStates.data(),
            readerStates.size()
        );
        switch (result) {
            case SCARD_S_SUCCESS:
                process_reader_states(readerStates);
                break;
            case SCARD_E_TIMEOUT:
                break;
            default:
                throw std::system_error(result, std::generic_category());
        }
    }

}

std::vector<SCARD_READERSTATE> EventListener::get_reader_states() {
    std::vector<SCARD_READERSTATE> readerStates(readers_.size() + newReaders_);
    size_t i = 0;
    for (auto reader = readers_.begin(); reader != readers_.end(); ++reader, i++) {
        auto &state = readerStates[i];
        state.szReader = reader->first.c_str();
        state.dwCurrentState = reader->second;
    }
    if (newReaders_) {
        auto &state = readerStates.back();
        state.szReader = NEW_READER;
    }
    return readerStates;
}

void EventListener::process_reader_states(std::vector<SCARD_READERSTATE> &readerStates) {
    bool updateReaders = false;
    for (auto const &readerState : readerStates) {
        if (!wcscmp(readerState.szReader, NEW_READER)) {
            updateReaders = true;
            continue;
        }

        if (event_bits(readerState, SCARD_STATE_UNKNOWN)) {
            readers_.erase(readerState.szReader);
            continue;
        }

        if (event_bits(readerState, SCARD_STATE_IGNORE))
            continue;

        if (filtered_event_occured(readerState)) {
            callback_(readerState.dwEventState & eventFilter_, readerState.szReader);
        }

        update_current_state(readerState);
    }

    if (updateReaders) {
        Readers readers(context, NULL);
        for (auto const &new_reader : readers.list()) {
            if (readers_.count(new_reader) == 0) {
                readers_.emplace(new_reader, SCARD_STATE_UNAWARE);
            }
        }
    }
}

bool EventListener::filtered_event_occured(SCARD_READERSTATE const &state) {
    return (state.dwEventState & eventFilter_) != (state.dwCurrentState & eventFilter_);
}

void EventListener::update_current_state(SCARD_READERSTATE const &state) {
    if (auto reader = readers_.find(state.szReader); reader != readers_.end()) {
        reader->second = state.dwEventState & ~(SCARD_STATE_IGNORE | SCARD_STATE_CHANGED | SCARD_STATE_UNKNOWN);
    }
}

bool rsc::EventListener::event_bits(SCARD_READERSTATE const &state, DWORD bits) {
    return (state.dwEventState & bits) == bits;
}
