#pragma once

#include <string>
#include <vector>

#include "fmt/core.h"
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <sio_message.h>

#include <parser/sio_tokens.h>

using namespace std;

char const* sio_token_type2str(SIOTokenType type);

template <> struct fmt::formatter<SIOTokenType> : formatter<string_view> {
    // parse is inherited from formatter<string_view>.
    template <typename FormatContext>
    auto format(SIOTokenType c, FormatContext& ctx) {
        //string_view name = "unknown";
        string_view name = sio_token_type2str(c);
        //name = sio_token_type2str(c);

        return formatter<string_view>::format(name, ctx);
    }
};

string create_expected_msg(SIOTokenType expected, SIOTokenType found);
string create_expected_msg(vector<SIOTokenType> expected, SIOTokenType found);