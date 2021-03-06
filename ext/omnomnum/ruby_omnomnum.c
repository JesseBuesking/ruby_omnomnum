/* OmNomNum 0.0.2 -- Gobbles up numbers in strings.
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
 *   * Neither the name of OmNomNum nor the names of its contributors may be used
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
VALUE parse_second_symbol;

ParserState state;
int utf8_encoding;

// for debugging
/*int do_print(VALUE key, VALUE val, VALUE in) {*/
    /*fprintf(*/
        /*stderr,*/
        /*"Key %s => Value %d\n", rb_id2name(SYM2ID(key)), RTEST(val));*/

    /*return ST_CONTINUE;*/
/*}*/

static VALUE ruby_omnomnum_normalize(int argc, VALUE *argv, VALUE self)
{
    // the actual string to be normalized
    VALUE input_string;
    // hash of optional parameters
    VALUE opts;

    // takes in:
    //   '1' 1 required argument (string to normalize)
    //   ':' hash of optional arguments
    rb_scan_args(argc, argv, "1:", &input_string, &opts);

    // if the hash of optional arguments is nil, just set it equal
    // to the default empty hash we've saved globally.
    if (NIL_P(opts)) opts = rb_hash_new();

    // for debugging
    /*rb_hash_foreach(opts, do_print, Qnil);*/

    VALUE ruby_parse_second = rb_hash_aref(opts, parse_second_symbol);
    if (!NIL_P(ruby_parse_second)) {
        state.parse_second = RTEST(ruby_parse_second);
    }

    char *data = StringValuePtr(input_string);
    size_t data_len = RSTRING_LEN(input_string);

    normalize(data, data_len, &state);

    VALUE _string = rb_str_new(state.result, sdslen(state.result));

    resetParserState(&state);

    rb_enc_associate_index(_string, utf8_encoding);
    return _string;
}

void Init_omnomnum()
{
    // initialize our global variables
    parse_second_symbol = ID2SYM(rb_intern("parse_second"));
    utf8_encoding = rb_enc_find_index("UTF-8");

    initOmNomNum();
    initParserState(&state);
    VALUE mOmNomNum = rb_define_module("OmNomNum");
    rb_define_singleton_method(mOmNomNum, "normalize", ruby_omnomnum_normalize, -1);
}
