/* OmNomNum 0.0.1 -- Gobbles up numbers in strings.
 *
 * Copyright (c) 2017, Jesse Buesking <jessebuesking at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "ruby_omnomnum.h"
#include <ruby/encoding.h>

VALUE mOmNomNum;

ParserState state;
int utf8_encoding;

static VALUE ruby_omnomnum_normalize(VALUE self, VALUE obj)
{
    char *data = StringValuePtr(obj);
    size_t data_len = RSTRING_LEN(obj);

    normalize(data, data_len, &state);

    VALUE _string = rb_str_new(state.result, sdslen(state.result));

    resetParserState(&state);

    rb_enc_associate_index(_string, utf8_encoding);
    return _string;
}

void Init_omnomnum()
{
    utf8_encoding = rb_enc_find_index("UTF-8");
    initOmNomNum();
    initParserState(&state);
    VALUE mOmNomNum = rb_define_module("OmNomNum");
    rb_define_singleton_method(mOmNomNum, "normalize", ruby_omnomnum_normalize, 1);
}
