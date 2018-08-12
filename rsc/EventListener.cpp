#include "EventListener.h"

#include "Readers.h"
#include "AccessStartedEventListener.h"

#include <system_error>

using namespace rsc;

DWORD const EventListener::MAX_TIMEOUT = 1024;
LPCTSTR EventListener::NEW_READER = TEXT("\\\\?PnP?\\Notification");

EventListener::EventListener(DWORD dwContextScope) 
    : context_(dwContextScope, false)
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
    if (newReaders_) {
        readers_.emplace(NEW_READER, SCARD_STATE_UNAWARE);
    } else {
        readers_.erase(NEW_READER);
    }
}

void EventListener::listener() {
    if (newReaders_) {
        readers_.emplace(NEW_READER, SCARD_STATE_UNAWARE);
    }

    AccessStartedEventListener asel;

    while (toListen_) {
        try {
            if (context_.released()) {
                while (toListen_ && !asel.wait(MAX_TIMEOUT))
                    ;

                if (!toListen_)
                    break;

                context_.establish();
            }

            auto readerStates = get_reader_states();

            auto result = SCardGetStatusChange(
                context_,
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
                case SCARD_E_SERVICE_STOPPED:
                    context_.release();
                    break;
                default:
                    throw std::system_error(result, std::generic_category());
            }

        } catch (std::system_error const &e) {
            if (e.code().value() == SCARD_E_SERVICE_STOPPED) {
                context_.release();
            } else {
                throw;
            }
        }
    }

}

std::vector<SCARD_READERSTATE> EventListener::get_reader_states() {
    std::vector<SCARD_READERSTATE> readerStates(readers_.size());
    size_t i = 0;
    for (auto reader = readers_.begin(); reader != readers_.end(); ++reader, i++) {
        auto &state = readerStates[i];
        state.szReader = reader->first.c_str();
        state.dwCurrentState = reader->second;
    }
    return readerStates;
}

void EventListener::process_reader_states(std::vector<SCARD_READERSTATE> &readerStates) {
    bool updateReaders = false;
    for (auto const &readerState : readerStates) {
        update_current_state(readerState);

        if (event_bits(readerState, SCARD_STATE_IGNORE))
            continue;

        if (!wcscmp(readerState.szReader, NEW_READER)) {
            updateReaders = true;
            continue;
        }

        if (event_bits(readerState, SCARD_STATE_UNKNOWN)) {
            readers_.erase(readerState.szReader);
            continue;
        }

        if (filtered_event_occured(readerState)) {
            callback_(readerState.dwEventState & eventFilter_, context_, readerState.szReader);
        }
    }

    if (updateReaders) {
        Readers readers(context_, NULL);
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
