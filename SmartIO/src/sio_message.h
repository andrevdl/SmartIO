#pragma once

// Tokenizer
constexpr auto ERRROR_UNCLOSED_STRING = "String is not closed";
constexpr auto ERROR_INVALID_TOKEN = "Invalid token";
constexpr auto ERROR_NUMBER_EXPECTED = "Invalid token, a number or seperator charater expected (0-9,.)";
constexpr auto ERROR_INVALID_NUMBER_FORMAT = "Number is invalid formatted";
constexpr auto ERROR_PARSE_BUILD_FAILED = "Error during tokenizing";
constexpr auto INFO_PARSE_BUILD_SUCCES = "Succesfully parsed";