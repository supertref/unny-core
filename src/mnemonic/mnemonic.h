/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MNEMONIC_H
#define MNEMONIC_H

#include <cstddef>
#include <string>
#include <vector>
#include <array>
#include <mnemonic/arrayslice.h>
#include <mnemonic/dictionary.h>

/**
* A valid mnemonic word count is evenly divisible by this number.
*/
static size_t mnemonic_word_multiple = 3;

/**
* A valid seed byte count is evenly divisible by this number.
*/
static size_t mnemonic_seed_multiple = 4;

template <size_t Size>
using byte_array = std::array<uint8_t, Size>;

/**
* Helpful type definitions
*/
typedef std::vector<std::string> word_list;
typedef array_slice<uint8_t> data_slice;
typedef std::vector<uint8_t> data_chunk;
typedef byte_array<64> long_hash;
typedef byte_array<32> hash_digest;
typedef std::initializer_list<data_slice> loaf;

long_hash pkcs5_pbkdf2_hmac_sha512(data_slice passphrase, data_slice salt, size_t iterations);

dictionary string_to_lexicon(const std::string& strLanguage);

/**
* Create a new mnenomic (list of words) from provided entropy and a dictionary
* selection. The mnemonic can later be converted to a seed for use in wallet
* creation. Entropy byte count must be evenly divisible by 4.
*/
word_list create_mnemonic(data_slice entropy, const dictionary &lexicon=language::en);

/**
* Convert a mnemonic to a format for creating a CKey object.
*/
data_chunk key_from_mnemonic(const word_list& words, const dictionary& lexicon=language::en);

/**
* Checks a mnemonic against a dictionary to determine if the
* words are spelled correctly and the checksum matches.
* The words must have been created using mnemonic encoding.
*/
bool validate_mnemonic(const word_list& mnemonic, const dictionary &lexicon);

/**
* Checks that a mnemonic is valid in at least one of the provided languages.
*/
bool validate_mnemonic(const word_list& mnemonic, const dictionary_list& lexicons=language::all);

/**
* Convert a mnemonic with no passphrase to a wallet-generation seed.
*/
long_hash decode_mnemonic(const word_list& mnemonic);
long_hash decode_mnemonic(const std::string& mnemonic);

/**
* Convert a mnemonic and passphrase to a wallet-generation seed.
* Any passphrase can be used and will change the resulting seed.
*/
long_hash decode_mnemonic(const word_list& mnemonic,
    const std::string& passphrase);

/**
 * @brief sentence_to_word_list - converts a sentence in a vector with
 * words
 * @param sentence
 * @return vector of words
 */
word_list sentence_to_word_list(const std::string& sentence);

#endif
