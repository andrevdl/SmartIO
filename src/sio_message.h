/*
 * Copyright (c) 2021 Andre van der Laan (andrevdl). All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

// Tokenizer
constexpr auto ERRROR_UNCLOSED_STRING = "String is not closed";
constexpr auto ERROR_INVALID_TOKEN = "Invalid token";
constexpr auto ERROR_UNEXCEPTED_EOF = "Unexpected end of file";
constexpr auto ERROR_NUMBER_EXPECTED = "Invalid token, a number or seperator charater expected (0-9,.)";
constexpr auto ERROR_INVALID_NUMBER_FORMAT = "Number is invalid formatted";
constexpr auto ERROR_PARSE_BUILD_FAILED = "Error during tokenizing";
constexpr auto INFO_PARSE_BUILD_SUCCES = "Succesfully parsed";

// DFA parser
constexpr auto ERROR_EXPECTED_TOKEN = "The following token expected: {}, but found: {}";
constexpr auto ERROR_EXPECTED_TOKENS = "One of the following tokens expected: {}, but found: {}";
constexpr auto ERROR_EXPECTED_TOKEN_EOF = "The following token expected: {}, but end of file reached";
constexpr auto ERROR_EXPECTED_TOKENS_EOF = "One of the following tokens expected: {}, but end of file reached";
constexpr auto ERROR_EOF_EXPECTED = "End of file expected";