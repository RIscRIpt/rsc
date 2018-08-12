#pragma once

#include "Context.h"

#include <vector>
#include <unordered_map>
#include <functional>
#include <thread>

#include <winscard.h>

namespace rsc {

    class EventListener {
    public:
        using CallbackFn = std::function<void(DWORD event, Context const &context, std::wstring const &reader)>;

        EventListener(DWORD dwContextScope = SCARD_SCOPE_USER);

        void start(DWORD eventFilter, CallbackFn callback);
        void stop();

        void set_listening_readers(std::vector<std::wstring> const &readers);
        void listen_new_readers(bool toggle);

        inline Context const& context() const noexcept { return context_; }

    private:
        void listener();
        std::vector<SCARD_READERSTATE> get_reader_states();

        void process_reader_states(std::vector<SCARD_READERSTATE> &readerStates);
        bool filtered_event_occured(SCARD_READERSTATE const &state);
        void update_current_state(SCARD_READERSTATE const &state);

        static bool event_bits(SCARD_READERSTATE const &state, DWORD bits);

        Context context_;

        std::thread listeningThread_;
        bool toListen_;

        CallbackFn callback_;
        DWORD eventFilter_;
        bool newReaders_;

        std::unordered_map<std::wstring, DWORD> readers_;

        static DWORD const MAX_TIMEOUT;
        static LPCTSTR NEW_READER;
    };

}
