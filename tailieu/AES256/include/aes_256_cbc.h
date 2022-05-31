// The MIT License (MIT)

// Copyright (c) 2020 Phenikaa Smart Device - MinhhaTech

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// -----------------------------------------------------------------------------------
// This library base on ESP-IDF SDK
// @Creator: Tuan Doan (tuandoan2604@gmail.com)
// -----------------------------------------------------------------------------------
#ifndef __AES_256_CBC_H
#define __AES_256_CBC_H
#include "esp_err.h"
#define ENCRYPT_SUCCESS                 0x01
#define ENCRYPT_INIT_VECTOR_FAIL        0x02
#define ENCRYPT_KEY_FAIL                0x03

/**
 * @brief CBC AES256 mode encryption.
 * @param plain_text    The object to encode.
 * @param _key          Key 256-bit for encryption
 * @param init_vector   Initialization Vector for encryption
 * @note Example:
 *     encrypted("Hello, I'm Tuan Doan","26041998260419982604199826041998","2604199826041998");
 * @return ESP_OK       if encypted success.
 * @return ESP_FAIL     if iv wrong, decrypt fail ... 
*/
esp_err_t encrypt(char *plain_text,char *_key,char *init_vector);
#endif