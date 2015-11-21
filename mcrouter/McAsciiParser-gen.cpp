
#line 1 "src/mcrouter/lib/network/McAsciiParser.rl"
/*
 *  Copyright (c) 2015, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#include "mcrouter/lib/network/McAsciiParser.h"

#include <arpa/inet.h>

#include "mcrouter/lib/mc/msg.h"
#include "mcrouter/lib/McOperation.h"
#include "mcrouter/lib/McReply.h"

namespace facebook { namespace memcache {

/**
 * %%{}%% blocks are going to be processed by Ragel.
 * A lot of different building blocks are used here, their complete
 * documentation can be found on the official webpage of Ragel.
 * The most important constructs are actions and code snippets.
 * There are 4 base types of them used here:
 *   >name or >{} - execute action with name 'name', or code snippet before
 *                  entering machine.
 *   $name or ${} - on each transition of machine.
 *   %name or %{} - on each transition from machine via final state.
 *   @name or @{} - on each transition into final state.
 */


#line 210 "src/mcrouter/lib/network/McAsciiParser.rl"


namespace {

/**
 * Trim IOBuf to reference only data from range [posStart, posEnd).
 */
inline void trimIOBufToRange(folly::IOBuf& buffer, const char* posStart,
                             const char* posEnd) {
  buffer.trimStart(posStart - reinterpret_cast<const char*>(buffer.data()));
  buffer.trimEnd(buffer.length() - (posEnd - posStart));
}

/**
 * Append piece of IOBuf in range [posStart, posEnd) to destination IOBuf.
 */
inline void appendKeyPiece(const folly::IOBuf& from, folly::IOBuf& to,
                           const char* posStart, const char* posEnd) {
  // No need to process empty piece.
  if (UNLIKELY(posEnd == posStart)) {
    return;
  }

  if (LIKELY(to.length() == 0)) {
    from.cloneOneInto(to);
    trimIOBufToRange(to, posStart, posEnd);
  } else {
    auto nextPiece = from.cloneOne();
    trimIOBufToRange(*nextPiece, posStart, posEnd);
    to.prependChain(std::move(nextPiece));
  }
}

inline void initFirstCharIOBuf(const folly::IOBuf& from, folly::IOBuf& to,
                               const char* pos) {
  // Copy current IOBuf.
  from.cloneOneInto(to);
  trimIOBufToRange(to, pos, pos + 1);
}

inline void appendCurrentCharTo(const folly::IOBuf& from, folly::IOBuf& to,
                                const char* pos) {
  // If it is just a next char in the same memory chunk, just append it.
  // Otherwise we need to append new IOBuf.
  if (to.prev()->data() + to.prev()->length() ==
        reinterpret_cast<const void*>(pos) && to.prev()->tailroom() > 0) {
    to.prev()->append(1);
  } else {
    auto nextPiece = from.cloneOne();
    trimIOBufToRange(*nextPiece, pos, pos + 1);
    to.prependChain(std::move(nextPiece));
  }
}

}  // anonymous

// McGet reply.

#line 96 "McAsciiParser-gen.cpp"
static const int mc_ascii_get_reply_start = 1;
static const int mc_ascii_get_reply_first_final = 59;
static const int mc_ascii_get_reply_error = 0;

static const int mc_ascii_get_reply_en_get_reply = 1;


#line 274 "src/mcrouter/lib/network/McAsciiParser.rl"


template<>
void McClientAsciiParser::consumeMessage<McReply, McOperation<mc_op_get>>(
    folly::IOBuf& buffer) {
  McReply& message = currentMessage_.get<McReply>();
  
#line 112 "McAsciiParser-gen.cpp"
	{
	}

#line 116 "McAsciiParser-gen.cpp"
	{
	if ( ( p_) == ( pe_) )
		goto _test_eof;
	if ( ( savedCs_) == 0 )
		goto _out;
_resume:
	switch ( ( savedCs_) ) {
case 1:
	switch( (*( p_)) ) {
		case 67: goto tr0;
		case 69: goto tr2;
		case 83: goto tr3;
		case 86: goto tr4;
	}
	goto tr1;
case 0:
	goto _out;
case 2:
	if ( (*( p_)) == 76 )
		goto tr5;
	goto tr1;
case 3:
	if ( (*( p_)) == 73 )
		goto tr6;
	goto tr1;
case 4:
	if ( (*( p_)) == 69 )
		goto tr7;
	goto tr1;
case 5:
	if ( (*( p_)) == 78 )
		goto tr8;
	goto tr1;
case 6:
	if ( (*( p_)) == 84 )
		goto tr9;
	goto tr1;
case 7:
	if ( (*( p_)) == 95 )
		goto tr10;
	goto tr1;
case 8:
	if ( (*( p_)) == 69 )
		goto tr11;
	goto tr1;
case 9:
	if ( (*( p_)) == 82 )
		goto tr12;
	goto tr1;
case 10:
	if ( (*( p_)) == 82 )
		goto tr13;
	goto tr1;
case 11:
	if ( (*( p_)) == 79 )
		goto tr14;
	goto tr1;
case 12:
	if ( (*( p_)) == 82 )
		goto tr15;
	goto tr1;
case 13:
	switch( (*( p_)) ) {
		case 10: goto tr17;
		case 13: goto tr18;
		case 32: goto tr19;
	}
	goto tr16;
case 14:
	switch( (*( p_)) ) {
		case 10: goto tr21;
		case 13: goto tr22;
	}
	goto tr20;
case 59:
	goto tr1;
case 15:
	if ( (*( p_)) == 10 )
		goto tr23;
	goto tr1;
case 16:
	switch( (*( p_)) ) {
		case 10: goto tr17;
		case 13: goto tr18;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr24;
	goto tr16;
case 17:
	switch( (*( p_)) ) {
		case 10: goto tr21;
		case 13: goto tr22;
		case 32: goto tr25;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr26;
	goto tr20;
case 18:
	switch( (*( p_)) ) {
		case 10: goto tr17;
		case 13: goto tr18;
		case 32: goto tr27;
	}
	goto tr16;
case 19:
	switch( (*( p_)) ) {
		case 10: goto tr17;
		case 13: goto tr18;
	}
	goto tr16;
case 20:
	switch( (*( p_)) ) {
		case 78: goto tr28;
		case 82: goto tr29;
	}
	goto tr1;
case 21:
	if ( (*( p_)) == 68 )
		goto tr30;
	goto tr1;
case 22:
	switch( (*( p_)) ) {
		case 10: goto tr23;
		case 13: goto tr31;
	}
	goto tr1;
case 23:
	if ( (*( p_)) == 82 )
		goto tr32;
	goto tr1;
case 24:
	if ( (*( p_)) == 79 )
		goto tr33;
	goto tr1;
case 25:
	if ( (*( p_)) == 82 )
		goto tr34;
	goto tr1;
case 26:
	if ( (*( p_)) == 69 )
		goto tr35;
	goto tr1;
case 27:
	if ( (*( p_)) == 82 )
		goto tr36;
	goto tr1;
case 28:
	if ( (*( p_)) == 86 )
		goto tr37;
	goto tr1;
case 29:
	if ( (*( p_)) == 69 )
		goto tr38;
	goto tr1;
case 30:
	if ( (*( p_)) == 82 )
		goto tr39;
	goto tr1;
case 31:
	if ( (*( p_)) == 95 )
		goto tr40;
	goto tr1;
case 32:
	if ( (*( p_)) == 69 )
		goto tr41;
	goto tr1;
case 33:
	if ( (*( p_)) == 82 )
		goto tr42;
	goto tr1;
case 34:
	if ( (*( p_)) == 82 )
		goto tr43;
	goto tr1;
case 35:
	if ( (*( p_)) == 79 )
		goto tr44;
	goto tr1;
case 36:
	if ( (*( p_)) == 82 )
		goto tr45;
	goto tr1;
case 37:
	switch( (*( p_)) ) {
		case 10: goto tr47;
		case 13: goto tr48;
		case 32: goto tr49;
	}
	goto tr46;
case 38:
	switch( (*( p_)) ) {
		case 10: goto tr51;
		case 13: goto tr52;
	}
	goto tr50;
case 39:
	switch( (*( p_)) ) {
		case 10: goto tr47;
		case 13: goto tr48;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr53;
	goto tr46;
case 40:
	switch( (*( p_)) ) {
		case 10: goto tr51;
		case 13: goto tr52;
		case 32: goto tr54;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr55;
	goto tr50;
case 41:
	switch( (*( p_)) ) {
		case 10: goto tr47;
		case 13: goto tr48;
		case 32: goto tr56;
	}
	goto tr46;
case 42:
	switch( (*( p_)) ) {
		case 10: goto tr47;
		case 13: goto tr48;
	}
	goto tr46;
case 43:
	if ( (*( p_)) == 65 )
		goto tr57;
	goto tr1;
case 44:
	if ( (*( p_)) == 76 )
		goto tr58;
	goto tr1;
case 45:
	if ( (*( p_)) == 85 )
		goto tr59;
	goto tr1;
case 46:
	if ( (*( p_)) == 69 )
		goto tr60;
	goto tr1;
case 47:
	if ( (*( p_)) == 32 )
		goto tr61;
	goto tr1;
case 48:
	switch( (*( p_)) ) {
		case 32: goto tr63;
		case 127: goto tr1;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr1;
	goto tr62;
case 49:
	switch( (*( p_)) ) {
		case 32: goto tr64;
		case 127: goto tr1;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr1;
	goto tr62;
case 50:
	if ( (*( p_)) == 32 )
		goto tr64;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr65;
	goto tr1;
case 51:
	if ( (*( p_)) == 32 )
		goto tr66;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr67;
	goto tr1;
case 52:
	if ( (*( p_)) == 32 )
		goto tr68;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr69;
	goto tr1;
case 53:
	switch( (*( p_)) ) {
		case 10: goto tr70;
		case 13: goto tr71;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr72;
	goto tr1;
case 54:
	switch( (*( p_)) ) {
		case 10: goto tr73;
		case 13: goto tr74;
	}
	goto tr1;
case 55:
	if ( (*( p_)) == 69 )
		goto tr75;
	goto tr1;
case 56:
	if ( (*( p_)) == 78 )
		goto tr28;
	goto tr1;
case 57:
	if ( (*( p_)) == 10 )
		goto tr73;
	goto tr1;
case 58:
	if ( (*( p_)) == 10 )
		goto tr76;
	goto tr1;
	}

	tr1: ( savedCs_) = 0; goto _again;
	tr0: ( savedCs_) = 2; goto _again;
	tr5: ( savedCs_) = 3; goto _again;
	tr6: ( savedCs_) = 4; goto _again;
	tr7: ( savedCs_) = 5; goto _again;
	tr8: ( savedCs_) = 6; goto _again;
	tr9: ( savedCs_) = 7; goto _again;
	tr10: ( savedCs_) = 8; goto _again;
	tr11: ( savedCs_) = 9; goto _again;
	tr12: ( savedCs_) = 10; goto _again;
	tr13: ( savedCs_) = 11; goto _again;
	tr14: ( savedCs_) = 12; goto _again;
	tr15: ( savedCs_) = 13; goto _again;
	tr16: ( savedCs_) = 14; goto f1;
	tr20: ( savedCs_) = 14; goto f4;
	tr31: ( savedCs_) = 15; goto _again;
	tr18: ( savedCs_) = 15; goto f3;
	tr22: ( savedCs_) = 15; goto f6;
	tr48: ( savedCs_) = 15; goto f13;
	tr52: ( savedCs_) = 15; goto f15;
	tr19: ( savedCs_) = 16; goto f1;
	tr24: ( savedCs_) = 17; goto f8;
	tr26: ( savedCs_) = 17; goto f10;
	tr25: ( savedCs_) = 18; goto f9;
	tr27: ( savedCs_) = 19; goto f1;
	tr2: ( savedCs_) = 20; goto f0;
	tr28: ( savedCs_) = 21; goto _again;
	tr30: ( savedCs_) = 22; goto _again;
	tr34: ( savedCs_) = 22; goto f11;
	tr29: ( savedCs_) = 23; goto _again;
	tr32: ( savedCs_) = 24; goto _again;
	tr33: ( savedCs_) = 25; goto _again;
	tr3: ( savedCs_) = 26; goto _again;
	tr35: ( savedCs_) = 27; goto _again;
	tr36: ( savedCs_) = 28; goto _again;
	tr37: ( savedCs_) = 29; goto _again;
	tr38: ( savedCs_) = 30; goto _again;
	tr39: ( savedCs_) = 31; goto _again;
	tr40: ( savedCs_) = 32; goto _again;
	tr41: ( savedCs_) = 33; goto _again;
	tr42: ( savedCs_) = 34; goto _again;
	tr43: ( savedCs_) = 35; goto _again;
	tr44: ( savedCs_) = 36; goto _again;
	tr45: ( savedCs_) = 37; goto _again;
	tr46: ( savedCs_) = 38; goto f1;
	tr50: ( savedCs_) = 38; goto f4;
	tr49: ( savedCs_) = 39; goto f1;
	tr53: ( savedCs_) = 40; goto f8;
	tr55: ( savedCs_) = 40; goto f10;
	tr54: ( savedCs_) = 41; goto f9;
	tr56: ( savedCs_) = 42; goto f1;
	tr4: ( savedCs_) = 43; goto f0;
	tr57: ( savedCs_) = 44; goto _again;
	tr58: ( savedCs_) = 45; goto _again;
	tr59: ( savedCs_) = 46; goto _again;
	tr60: ( savedCs_) = 47; goto _again;
	tr63: ( savedCs_) = 48; goto _again;
	tr61: ( savedCs_) = 48; goto f16;
	tr62: ( savedCs_) = 49; goto _again;
	tr64: ( savedCs_) = 50; goto _again;
	tr65: ( savedCs_) = 51; goto f17;
	tr67: ( savedCs_) = 51; goto f19;
	tr68: ( savedCs_) = 52; goto _again;
	tr66: ( savedCs_) = 52; goto f18;
	tr69: ( savedCs_) = 53; goto f17;
	tr72: ( savedCs_) = 53; goto f19;
	tr70: ( savedCs_) = 54; goto f20;
	tr76: ( savedCs_) = 54; goto f22;
	tr73: ( savedCs_) = 55; goto _again;
	tr75: ( savedCs_) = 56; goto _again;
	tr74: ( savedCs_) = 57; goto _again;
	tr71: ( savedCs_) = 58; goto f21;
	tr17: ( savedCs_) = 59; goto f2;
	tr21: ( savedCs_) = 59; goto f5;
	tr23: ( savedCs_) = 59; goto f7;
	tr47: ( savedCs_) = 59; goto f12;
	tr51: ( savedCs_) = 59; goto f14;

f22:
#line 42 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // We have value field, so emplace IOBuf for value.
  message.valueData_.emplace();
  if (!readValue(buffer, message.valueData_.value())) {
    {( p_)++; goto _out; }
  }
}
	goto _again;
f4:
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f7:
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f19:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
	goto _again;
f18:
#line 137 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setFlags(currentUInt_);
}
	goto _again;
f21:
#line 154 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  remainingIOBufLength_ = static_cast<size_t>(currentUInt_);
}
	goto _again;
f16:
#line 179 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_found); }
	goto _again;
f11:
#line 187 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // This is unexpected error reply, just put ourself into error state.
  state_ = State::ERROR;
  currentErrorDescription_ = "ERROR reply received from server.";
  {( p_)++; goto _out; }
}
	goto _again;
f15:
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
	goto _again;
f6:
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
	goto _again;
f0:
#line 271 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_notfound); }
	goto _again;
f1:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f13:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
	goto _again;
f3:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
	goto _again;
f17:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ currentUInt_ = 0; }
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
	goto _again;
f10:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f20:
#line 154 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  remainingIOBufLength_ = static_cast<size_t>(currentUInt_);
}
#line 42 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // We have value field, so emplace IOBuf for value.
  message.valueData_.emplace();
  if (!readValue(buffer, message.valueData_.value())) {
    {( p_)++; goto _out; }
  }
}
	goto _again;
f9:
#line 171 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setAppSpecificErrorCode(static_cast<uint32_t>(currentUInt_));
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f14:
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f5:
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f12:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f2:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f8:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ currentUInt_ = 0; }
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;

_again:
	if ( ( savedCs_) == 0 )
		goto _out;
	if ( ++( p_) != ( pe_) )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 284 "src/mcrouter/lib/network/McAsciiParser.rl"

}

// McGets reply.

#line 785 "McAsciiParser-gen.cpp"
static const int mc_ascii_gets_reply_start = 1;
static const int mc_ascii_gets_reply_first_final = 61;
static const int mc_ascii_gets_reply_error = 0;

static const int mc_ascii_gets_reply_en_gets_reply = 1;


#line 295 "src/mcrouter/lib/network/McAsciiParser.rl"


template<>
void McClientAsciiParser::consumeMessage<McReply, McOperation<mc_op_gets>>(
    folly::IOBuf& buffer) {
  McReply& message = currentMessage_.get<McReply>();
  
#line 801 "McAsciiParser-gen.cpp"
	{
	}

#line 805 "McAsciiParser-gen.cpp"
	{
	if ( ( p_) == ( pe_) )
		goto _test_eof;
	if ( ( savedCs_) == 0 )
		goto _out;
_resume:
	switch ( ( savedCs_) ) {
case 1:
	switch( (*( p_)) ) {
		case 67: goto tr0;
		case 69: goto tr2;
		case 83: goto tr3;
		case 86: goto tr4;
	}
	goto tr1;
case 0:
	goto _out;
case 2:
	if ( (*( p_)) == 76 )
		goto tr5;
	goto tr1;
case 3:
	if ( (*( p_)) == 73 )
		goto tr6;
	goto tr1;
case 4:
	if ( (*( p_)) == 69 )
		goto tr7;
	goto tr1;
case 5:
	if ( (*( p_)) == 78 )
		goto tr8;
	goto tr1;
case 6:
	if ( (*( p_)) == 84 )
		goto tr9;
	goto tr1;
case 7:
	if ( (*( p_)) == 95 )
		goto tr10;
	goto tr1;
case 8:
	if ( (*( p_)) == 69 )
		goto tr11;
	goto tr1;
case 9:
	if ( (*( p_)) == 82 )
		goto tr12;
	goto tr1;
case 10:
	if ( (*( p_)) == 82 )
		goto tr13;
	goto tr1;
case 11:
	if ( (*( p_)) == 79 )
		goto tr14;
	goto tr1;
case 12:
	if ( (*( p_)) == 82 )
		goto tr15;
	goto tr1;
case 13:
	switch( (*( p_)) ) {
		case 10: goto tr17;
		case 13: goto tr18;
		case 32: goto tr19;
	}
	goto tr16;
case 14:
	switch( (*( p_)) ) {
		case 10: goto tr21;
		case 13: goto tr22;
	}
	goto tr20;
case 61:
	goto tr1;
case 15:
	if ( (*( p_)) == 10 )
		goto tr23;
	goto tr1;
case 16:
	switch( (*( p_)) ) {
		case 10: goto tr17;
		case 13: goto tr18;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr24;
	goto tr16;
case 17:
	switch( (*( p_)) ) {
		case 10: goto tr21;
		case 13: goto tr22;
		case 32: goto tr25;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr26;
	goto tr20;
case 18:
	switch( (*( p_)) ) {
		case 10: goto tr17;
		case 13: goto tr18;
		case 32: goto tr27;
	}
	goto tr16;
case 19:
	switch( (*( p_)) ) {
		case 10: goto tr17;
		case 13: goto tr18;
	}
	goto tr16;
case 20:
	switch( (*( p_)) ) {
		case 78: goto tr28;
		case 82: goto tr29;
	}
	goto tr1;
case 21:
	if ( (*( p_)) == 68 )
		goto tr30;
	goto tr1;
case 22:
	switch( (*( p_)) ) {
		case 10: goto tr23;
		case 13: goto tr31;
	}
	goto tr1;
case 23:
	if ( (*( p_)) == 82 )
		goto tr32;
	goto tr1;
case 24:
	if ( (*( p_)) == 79 )
		goto tr33;
	goto tr1;
case 25:
	if ( (*( p_)) == 82 )
		goto tr34;
	goto tr1;
case 26:
	if ( (*( p_)) == 69 )
		goto tr35;
	goto tr1;
case 27:
	if ( (*( p_)) == 82 )
		goto tr36;
	goto tr1;
case 28:
	if ( (*( p_)) == 86 )
		goto tr37;
	goto tr1;
case 29:
	if ( (*( p_)) == 69 )
		goto tr38;
	goto tr1;
case 30:
	if ( (*( p_)) == 82 )
		goto tr39;
	goto tr1;
case 31:
	if ( (*( p_)) == 95 )
		goto tr40;
	goto tr1;
case 32:
	if ( (*( p_)) == 69 )
		goto tr41;
	goto tr1;
case 33:
	if ( (*( p_)) == 82 )
		goto tr42;
	goto tr1;
case 34:
	if ( (*( p_)) == 82 )
		goto tr43;
	goto tr1;
case 35:
	if ( (*( p_)) == 79 )
		goto tr44;
	goto tr1;
case 36:
	if ( (*( p_)) == 82 )
		goto tr45;
	goto tr1;
case 37:
	switch( (*( p_)) ) {
		case 10: goto tr47;
		case 13: goto tr48;
		case 32: goto tr49;
	}
	goto tr46;
case 38:
	switch( (*( p_)) ) {
		case 10: goto tr51;
		case 13: goto tr52;
	}
	goto tr50;
case 39:
	switch( (*( p_)) ) {
		case 10: goto tr47;
		case 13: goto tr48;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr53;
	goto tr46;
case 40:
	switch( (*( p_)) ) {
		case 10: goto tr51;
		case 13: goto tr52;
		case 32: goto tr54;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr55;
	goto tr50;
case 41:
	switch( (*( p_)) ) {
		case 10: goto tr47;
		case 13: goto tr48;
		case 32: goto tr56;
	}
	goto tr46;
case 42:
	switch( (*( p_)) ) {
		case 10: goto tr47;
		case 13: goto tr48;
	}
	goto tr46;
case 43:
	if ( (*( p_)) == 65 )
		goto tr57;
	goto tr1;
case 44:
	if ( (*( p_)) == 76 )
		goto tr58;
	goto tr1;
case 45:
	if ( (*( p_)) == 85 )
		goto tr59;
	goto tr1;
case 46:
	if ( (*( p_)) == 69 )
		goto tr60;
	goto tr1;
case 47:
	if ( (*( p_)) == 32 )
		goto tr61;
	goto tr1;
case 48:
	switch( (*( p_)) ) {
		case 32: goto tr63;
		case 127: goto tr1;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr1;
	goto tr62;
case 49:
	switch( (*( p_)) ) {
		case 32: goto tr64;
		case 127: goto tr1;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr1;
	goto tr62;
case 50:
	if ( (*( p_)) == 32 )
		goto tr64;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr65;
	goto tr1;
case 51:
	if ( (*( p_)) == 32 )
		goto tr66;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr67;
	goto tr1;
case 52:
	if ( (*( p_)) == 32 )
		goto tr68;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr69;
	goto tr1;
case 53:
	if ( (*( p_)) == 32 )
		goto tr70;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr71;
	goto tr1;
case 54:
	if ( (*( p_)) == 32 )
		goto tr72;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr73;
	goto tr1;
case 55:
	switch( (*( p_)) ) {
		case 10: goto tr74;
		case 13: goto tr75;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr76;
	goto tr1;
case 56:
	switch( (*( p_)) ) {
		case 10: goto tr77;
		case 13: goto tr78;
	}
	goto tr1;
case 57:
	if ( (*( p_)) == 69 )
		goto tr79;
	goto tr1;
case 58:
	if ( (*( p_)) == 78 )
		goto tr28;
	goto tr1;
case 59:
	if ( (*( p_)) == 10 )
		goto tr77;
	goto tr1;
case 60:
	if ( (*( p_)) == 10 )
		goto tr80;
	goto tr1;
	}

	tr1: ( savedCs_) = 0; goto _again;
	tr0: ( savedCs_) = 2; goto _again;
	tr5: ( savedCs_) = 3; goto _again;
	tr6: ( savedCs_) = 4; goto _again;
	tr7: ( savedCs_) = 5; goto _again;
	tr8: ( savedCs_) = 6; goto _again;
	tr9: ( savedCs_) = 7; goto _again;
	tr10: ( savedCs_) = 8; goto _again;
	tr11: ( savedCs_) = 9; goto _again;
	tr12: ( savedCs_) = 10; goto _again;
	tr13: ( savedCs_) = 11; goto _again;
	tr14: ( savedCs_) = 12; goto _again;
	tr15: ( savedCs_) = 13; goto _again;
	tr16: ( savedCs_) = 14; goto f1;
	tr20: ( savedCs_) = 14; goto f4;
	tr31: ( savedCs_) = 15; goto _again;
	tr18: ( savedCs_) = 15; goto f3;
	tr22: ( savedCs_) = 15; goto f6;
	tr48: ( savedCs_) = 15; goto f13;
	tr52: ( savedCs_) = 15; goto f15;
	tr19: ( savedCs_) = 16; goto f1;
	tr24: ( savedCs_) = 17; goto f8;
	tr26: ( savedCs_) = 17; goto f10;
	tr25: ( savedCs_) = 18; goto f9;
	tr27: ( savedCs_) = 19; goto f1;
	tr2: ( savedCs_) = 20; goto f0;
	tr28: ( savedCs_) = 21; goto _again;
	tr30: ( savedCs_) = 22; goto _again;
	tr34: ( savedCs_) = 22; goto f11;
	tr29: ( savedCs_) = 23; goto _again;
	tr32: ( savedCs_) = 24; goto _again;
	tr33: ( savedCs_) = 25; goto _again;
	tr3: ( savedCs_) = 26; goto _again;
	tr35: ( savedCs_) = 27; goto _again;
	tr36: ( savedCs_) = 28; goto _again;
	tr37: ( savedCs_) = 29; goto _again;
	tr38: ( savedCs_) = 30; goto _again;
	tr39: ( savedCs_) = 31; goto _again;
	tr40: ( savedCs_) = 32; goto _again;
	tr41: ( savedCs_) = 33; goto _again;
	tr42: ( savedCs_) = 34; goto _again;
	tr43: ( savedCs_) = 35; goto _again;
	tr44: ( savedCs_) = 36; goto _again;
	tr45: ( savedCs_) = 37; goto _again;
	tr46: ( savedCs_) = 38; goto f1;
	tr50: ( savedCs_) = 38; goto f4;
	tr49: ( savedCs_) = 39; goto f1;
	tr53: ( savedCs_) = 40; goto f8;
	tr55: ( savedCs_) = 40; goto f10;
	tr54: ( savedCs_) = 41; goto f9;
	tr56: ( savedCs_) = 42; goto f1;
	tr4: ( savedCs_) = 43; goto f0;
	tr57: ( savedCs_) = 44; goto _again;
	tr58: ( savedCs_) = 45; goto _again;
	tr59: ( savedCs_) = 46; goto _again;
	tr60: ( savedCs_) = 47; goto _again;
	tr63: ( savedCs_) = 48; goto _again;
	tr61: ( savedCs_) = 48; goto f16;
	tr62: ( savedCs_) = 49; goto _again;
	tr64: ( savedCs_) = 50; goto _again;
	tr65: ( savedCs_) = 51; goto f17;
	tr67: ( savedCs_) = 51; goto f19;
	tr68: ( savedCs_) = 52; goto _again;
	tr66: ( savedCs_) = 52; goto f18;
	tr69: ( savedCs_) = 53; goto f17;
	tr71: ( savedCs_) = 53; goto f19;
	tr72: ( savedCs_) = 54; goto _again;
	tr70: ( savedCs_) = 54; goto f20;
	tr73: ( savedCs_) = 55; goto f17;
	tr76: ( savedCs_) = 55; goto f19;
	tr74: ( savedCs_) = 56; goto f21;
	tr80: ( savedCs_) = 56; goto f23;
	tr77: ( savedCs_) = 57; goto _again;
	tr79: ( savedCs_) = 58; goto _again;
	tr78: ( savedCs_) = 59; goto _again;
	tr75: ( savedCs_) = 60; goto f22;
	tr17: ( savedCs_) = 61; goto f2;
	tr21: ( savedCs_) = 61; goto f5;
	tr23: ( savedCs_) = 61; goto f7;
	tr47: ( savedCs_) = 61; goto f12;
	tr51: ( savedCs_) = 61; goto f14;

f23:
#line 42 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // We have value field, so emplace IOBuf for value.
  message.valueData_.emplace();
  if (!readValue(buffer, message.valueData_.value())) {
    {( p_)++; goto _out; }
  }
}
	goto _again;
f4:
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f7:
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f19:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
	goto _again;
f18:
#line 137 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setFlags(currentUInt_);
}
	goto _again;
f20:
#line 154 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  remainingIOBufLength_ = static_cast<size_t>(currentUInt_);
}
	goto _again;
f22:
#line 158 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setCas(currentUInt_);
}
	goto _again;
f16:
#line 179 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_found); }
	goto _again;
f11:
#line 187 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // This is unexpected error reply, just put ourself into error state.
  state_ = State::ERROR;
  currentErrorDescription_ = "ERROR reply received from server.";
  {( p_)++; goto _out; }
}
	goto _again;
f15:
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
	goto _again;
f6:
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
	goto _again;
f0:
#line 292 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_notfound); }
	goto _again;
f1:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f13:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
	goto _again;
f3:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
	goto _again;
f17:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ currentUInt_ = 0; }
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
	goto _again;
f10:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f21:
#line 158 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setCas(currentUInt_);
}
#line 42 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // We have value field, so emplace IOBuf for value.
  message.valueData_.emplace();
  if (!readValue(buffer, message.valueData_.value())) {
    {( p_)++; goto _out; }
  }
}
	goto _again;
f9:
#line 171 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setAppSpecificErrorCode(static_cast<uint32_t>(currentUInt_));
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f14:
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f5:
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f12:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f2:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f8:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ currentUInt_ = 0; }
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;

_again:
	if ( ( savedCs_) == 0 )
		goto _out;
	if ( ++( p_) != ( pe_) )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 305 "src/mcrouter/lib/network/McAsciiParser.rl"

}

// McLeaseGet reply.

#line 1496 "McAsciiParser-gen.cpp"
static const int mc_ascii_lease_get_reply_start = 1;
static const int mc_ascii_lease_get_reply_first_final = 76;
static const int mc_ascii_lease_get_reply_error = 0;

static const int mc_ascii_lease_get_reply_en_lease_get_reply = 1;


#line 322 "src/mcrouter/lib/network/McAsciiParser.rl"


template<>
void McClientAsciiParser::consumeMessage<McReply, McOperation<mc_op_lease_get>>(
    folly::IOBuf& buffer) {
  McReply& message = currentMessage_.get<McReply>();
  
#line 1512 "McAsciiParser-gen.cpp"
	{
	}

#line 1516 "McAsciiParser-gen.cpp"
	{
	if ( ( p_) == ( pe_) )
		goto _test_eof;
	if ( ( savedCs_) == 0 )
		goto _out;
_resume:
	switch ( ( savedCs_) ) {
case 1:
	switch( (*( p_)) ) {
		case 67: goto tr0;
		case 69: goto tr2;
		case 76: goto tr3;
		case 83: goto tr4;
		case 86: goto tr5;
	}
	goto tr1;
case 0:
	goto _out;
case 2:
	if ( (*( p_)) == 76 )
		goto tr6;
	goto tr1;
case 3:
	if ( (*( p_)) == 73 )
		goto tr7;
	goto tr1;
case 4:
	if ( (*( p_)) == 69 )
		goto tr8;
	goto tr1;
case 5:
	if ( (*( p_)) == 78 )
		goto tr9;
	goto tr1;
case 6:
	if ( (*( p_)) == 84 )
		goto tr10;
	goto tr1;
case 7:
	if ( (*( p_)) == 95 )
		goto tr11;
	goto tr1;
case 8:
	if ( (*( p_)) == 69 )
		goto tr12;
	goto tr1;
case 9:
	if ( (*( p_)) == 82 )
		goto tr13;
	goto tr1;
case 10:
	if ( (*( p_)) == 82 )
		goto tr14;
	goto tr1;
case 11:
	if ( (*( p_)) == 79 )
		goto tr15;
	goto tr1;
case 12:
	if ( (*( p_)) == 82 )
		goto tr16;
	goto tr1;
case 13:
	switch( (*( p_)) ) {
		case 10: goto tr18;
		case 13: goto tr19;
		case 32: goto tr20;
	}
	goto tr17;
case 14:
	switch( (*( p_)) ) {
		case 10: goto tr22;
		case 13: goto tr23;
	}
	goto tr21;
case 76:
	goto tr1;
case 15:
	if ( (*( p_)) == 10 )
		goto tr24;
	goto tr1;
case 16:
	switch( (*( p_)) ) {
		case 10: goto tr18;
		case 13: goto tr19;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr25;
	goto tr17;
case 17:
	switch( (*( p_)) ) {
		case 10: goto tr22;
		case 13: goto tr23;
		case 32: goto tr26;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr27;
	goto tr21;
case 18:
	switch( (*( p_)) ) {
		case 10: goto tr18;
		case 13: goto tr19;
		case 32: goto tr28;
	}
	goto tr17;
case 19:
	switch( (*( p_)) ) {
		case 10: goto tr18;
		case 13: goto tr19;
	}
	goto tr17;
case 20:
	if ( (*( p_)) == 82 )
		goto tr29;
	goto tr1;
case 21:
	if ( (*( p_)) == 82 )
		goto tr30;
	goto tr1;
case 22:
	if ( (*( p_)) == 79 )
		goto tr31;
	goto tr1;
case 23:
	if ( (*( p_)) == 82 )
		goto tr32;
	goto tr1;
case 24:
	switch( (*( p_)) ) {
		case 10: goto tr24;
		case 13: goto tr33;
	}
	goto tr1;
case 25:
	if ( (*( p_)) == 86 )
		goto tr34;
	goto tr1;
case 26:
	if ( (*( p_)) == 65 )
		goto tr35;
	goto tr1;
case 27:
	if ( (*( p_)) == 76 )
		goto tr36;
	goto tr1;
case 28:
	if ( (*( p_)) == 85 )
		goto tr37;
	goto tr1;
case 29:
	if ( (*( p_)) == 69 )
		goto tr38;
	goto tr1;
case 30:
	if ( (*( p_)) == 32 )
		goto tr39;
	goto tr1;
case 31:
	switch( (*( p_)) ) {
		case 32: goto tr39;
		case 127: goto tr1;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr1;
	goto tr40;
case 32:
	switch( (*( p_)) ) {
		case 32: goto tr41;
		case 127: goto tr1;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr1;
	goto tr40;
case 33:
	if ( (*( p_)) == 32 )
		goto tr41;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr42;
	goto tr1;
case 34:
	if ( (*( p_)) == 32 )
		goto tr43;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr44;
	goto tr1;
case 35:
	if ( (*( p_)) == 32 )
		goto tr45;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr46;
	goto tr1;
case 36:
	if ( (*( p_)) == 32 )
		goto tr47;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr48;
	goto tr1;
case 37:
	if ( (*( p_)) == 32 )
		goto tr49;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr50;
	goto tr1;
case 38:
	switch( (*( p_)) ) {
		case 10: goto tr51;
		case 13: goto tr52;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr53;
	goto tr1;
case 39:
	switch( (*( p_)) ) {
		case 10: goto tr54;
		case 13: goto tr55;
	}
	goto tr1;
case 40:
	if ( (*( p_)) == 69 )
		goto tr56;
	goto tr1;
case 41:
	if ( (*( p_)) == 78 )
		goto tr57;
	goto tr1;
case 42:
	if ( (*( p_)) == 68 )
		goto tr58;
	goto tr1;
case 43:
	if ( (*( p_)) == 10 )
		goto tr54;
	goto tr1;
case 44:
	if ( (*( p_)) == 10 )
		goto tr59;
	goto tr1;
case 45:
	if ( (*( p_)) == 69 )
		goto tr60;
	goto tr1;
case 46:
	if ( (*( p_)) == 82 )
		goto tr61;
	goto tr1;
case 47:
	if ( (*( p_)) == 86 )
		goto tr62;
	goto tr1;
case 48:
	if ( (*( p_)) == 69 )
		goto tr63;
	goto tr1;
case 49:
	if ( (*( p_)) == 82 )
		goto tr64;
	goto tr1;
case 50:
	if ( (*( p_)) == 95 )
		goto tr65;
	goto tr1;
case 51:
	if ( (*( p_)) == 69 )
		goto tr66;
	goto tr1;
case 52:
	if ( (*( p_)) == 82 )
		goto tr67;
	goto tr1;
case 53:
	if ( (*( p_)) == 82 )
		goto tr68;
	goto tr1;
case 54:
	if ( (*( p_)) == 79 )
		goto tr69;
	goto tr1;
case 55:
	if ( (*( p_)) == 82 )
		goto tr70;
	goto tr1;
case 56:
	switch( (*( p_)) ) {
		case 10: goto tr72;
		case 13: goto tr73;
		case 32: goto tr74;
	}
	goto tr71;
case 57:
	switch( (*( p_)) ) {
		case 10: goto tr76;
		case 13: goto tr77;
	}
	goto tr75;
case 58:
	switch( (*( p_)) ) {
		case 10: goto tr72;
		case 13: goto tr73;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr78;
	goto tr71;
case 59:
	switch( (*( p_)) ) {
		case 10: goto tr76;
		case 13: goto tr77;
		case 32: goto tr79;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr80;
	goto tr75;
case 60:
	switch( (*( p_)) ) {
		case 10: goto tr72;
		case 13: goto tr73;
		case 32: goto tr81;
	}
	goto tr71;
case 61:
	switch( (*( p_)) ) {
		case 10: goto tr72;
		case 13: goto tr73;
	}
	goto tr71;
case 62:
	if ( (*( p_)) == 65 )
		goto tr82;
	goto tr1;
case 63:
	if ( (*( p_)) == 76 )
		goto tr83;
	goto tr1;
case 64:
	if ( (*( p_)) == 85 )
		goto tr84;
	goto tr1;
case 65:
	if ( (*( p_)) == 69 )
		goto tr85;
	goto tr1;
case 66:
	if ( (*( p_)) == 32 )
		goto tr86;
	goto tr1;
case 67:
	switch( (*( p_)) ) {
		case 32: goto tr88;
		case 127: goto tr1;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr1;
	goto tr87;
case 68:
	switch( (*( p_)) ) {
		case 32: goto tr89;
		case 127: goto tr1;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr1;
	goto tr87;
case 69:
	if ( (*( p_)) == 32 )
		goto tr89;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr90;
	goto tr1;
case 70:
	if ( (*( p_)) == 32 )
		goto tr91;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr92;
	goto tr1;
case 71:
	if ( (*( p_)) == 32 )
		goto tr93;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr94;
	goto tr1;
case 72:
	switch( (*( p_)) ) {
		case 10: goto tr95;
		case 13: goto tr96;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr97;
	goto tr1;
case 73:
	switch( (*( p_)) ) {
		case 10: goto tr98;
		case 13: goto tr99;
	}
	goto tr1;
case 74:
	if ( (*( p_)) == 10 )
		goto tr98;
	goto tr1;
case 75:
	if ( (*( p_)) == 10 )
		goto tr100;
	goto tr1;
	}

	tr1: ( savedCs_) = 0; goto _again;
	tr0: ( savedCs_) = 2; goto _again;
	tr6: ( savedCs_) = 3; goto _again;
	tr7: ( savedCs_) = 4; goto _again;
	tr8: ( savedCs_) = 5; goto _again;
	tr9: ( savedCs_) = 6; goto _again;
	tr10: ( savedCs_) = 7; goto _again;
	tr11: ( savedCs_) = 8; goto _again;
	tr12: ( savedCs_) = 9; goto _again;
	tr13: ( savedCs_) = 10; goto _again;
	tr14: ( savedCs_) = 11; goto _again;
	tr15: ( savedCs_) = 12; goto _again;
	tr16: ( savedCs_) = 13; goto _again;
	tr17: ( savedCs_) = 14; goto f0;
	tr21: ( savedCs_) = 14; goto f3;
	tr33: ( savedCs_) = 15; goto _again;
	tr19: ( savedCs_) = 15; goto f2;
	tr23: ( savedCs_) = 15; goto f5;
	tr73: ( savedCs_) = 15; goto f20;
	tr77: ( savedCs_) = 15; goto f22;
	tr20: ( savedCs_) = 16; goto f0;
	tr25: ( savedCs_) = 17; goto f7;
	tr27: ( savedCs_) = 17; goto f9;
	tr26: ( savedCs_) = 18; goto f8;
	tr28: ( savedCs_) = 19; goto f0;
	tr2: ( savedCs_) = 20; goto _again;
	tr29: ( savedCs_) = 21; goto _again;
	tr30: ( savedCs_) = 22; goto _again;
	tr31: ( savedCs_) = 23; goto _again;
	tr58: ( savedCs_) = 24; goto _again;
	tr32: ( savedCs_) = 24; goto f10;
	tr3: ( savedCs_) = 25; goto _again;
	tr34: ( savedCs_) = 26; goto _again;
	tr35: ( savedCs_) = 27; goto _again;
	tr36: ( savedCs_) = 28; goto _again;
	tr37: ( savedCs_) = 29; goto _again;
	tr38: ( savedCs_) = 30; goto _again;
	tr39: ( savedCs_) = 31; goto _again;
	tr40: ( savedCs_) = 32; goto _again;
	tr41: ( savedCs_) = 33; goto _again;
	tr42: ( savedCs_) = 34; goto f11;
	tr44: ( savedCs_) = 34; goto f13;
	tr45: ( savedCs_) = 35; goto _again;
	tr43: ( savedCs_) = 35; goto f12;
	tr46: ( savedCs_) = 36; goto f11;
	tr48: ( savedCs_) = 36; goto f13;
	tr49: ( savedCs_) = 37; goto _again;
	tr47: ( savedCs_) = 37; goto f14;
	tr50: ( savedCs_) = 38; goto f11;
	tr53: ( savedCs_) = 38; goto f13;
	tr51: ( savedCs_) = 39; goto f15;
	tr59: ( savedCs_) = 39; goto f18;
	tr98: ( savedCs_) = 40; goto _again;
	tr54: ( savedCs_) = 40; goto f17;
	tr56: ( savedCs_) = 41; goto _again;
	tr57: ( savedCs_) = 42; goto _again;
	tr55: ( savedCs_) = 43; goto _again;
	tr52: ( savedCs_) = 44; goto f16;
	tr4: ( savedCs_) = 45; goto _again;
	tr60: ( savedCs_) = 46; goto _again;
	tr61: ( savedCs_) = 47; goto _again;
	tr62: ( savedCs_) = 48; goto _again;
	tr63: ( savedCs_) = 49; goto _again;
	tr64: ( savedCs_) = 50; goto _again;
	tr65: ( savedCs_) = 51; goto _again;
	tr66: ( savedCs_) = 52; goto _again;
	tr67: ( savedCs_) = 53; goto _again;
	tr68: ( savedCs_) = 54; goto _again;
	tr69: ( savedCs_) = 55; goto _again;
	tr70: ( savedCs_) = 56; goto _again;
	tr71: ( savedCs_) = 57; goto f0;
	tr75: ( savedCs_) = 57; goto f3;
	tr74: ( savedCs_) = 58; goto f0;
	tr78: ( savedCs_) = 59; goto f7;
	tr80: ( savedCs_) = 59; goto f9;
	tr79: ( savedCs_) = 60; goto f8;
	tr81: ( savedCs_) = 61; goto f0;
	tr5: ( savedCs_) = 62; goto _again;
	tr82: ( savedCs_) = 63; goto _again;
	tr83: ( savedCs_) = 64; goto _again;
	tr84: ( savedCs_) = 65; goto _again;
	tr85: ( savedCs_) = 66; goto _again;
	tr88: ( savedCs_) = 67; goto _again;
	tr86: ( savedCs_) = 67; goto f23;
	tr87: ( savedCs_) = 68; goto _again;
	tr89: ( savedCs_) = 69; goto _again;
	tr90: ( savedCs_) = 70; goto f11;
	tr92: ( savedCs_) = 70; goto f13;
	tr93: ( savedCs_) = 71; goto _again;
	tr91: ( savedCs_) = 71; goto f14;
	tr94: ( savedCs_) = 72; goto f11;
	tr97: ( savedCs_) = 72; goto f13;
	tr95: ( savedCs_) = 73; goto f15;
	tr100: ( savedCs_) = 73; goto f18;
	tr99: ( savedCs_) = 74; goto _again;
	tr96: ( savedCs_) = 75; goto f16;
	tr18: ( savedCs_) = 76; goto f1;
	tr22: ( savedCs_) = 76; goto f4;
	tr24: ( savedCs_) = 76; goto f6;
	tr72: ( savedCs_) = 76; goto f19;
	tr76: ( savedCs_) = 76; goto f21;

f18:
#line 42 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // We have value field, so emplace IOBuf for value.
  message.valueData_.emplace();
  if (!readValue(buffer, message.valueData_.value())) {
    {( p_)++; goto _out; }
  }
}
	goto _again;
f3:
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f6:
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f13:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
	goto _again;
f14:
#line 137 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setFlags(currentUInt_);
}
	goto _again;
f16:
#line 154 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  remainingIOBufLength_ = static_cast<size_t>(currentUInt_);
}
	goto _again;
f12:
#line 166 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // NOTE: we don't support -1 lease token.
  message.setLeaseToken(currentUInt_);
}
	goto _again;
f23:
#line 179 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_found); }
	goto _again;
f10:
#line 187 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // This is unexpected error reply, just put ourself into error state.
  state_ = State::ERROR;
  currentErrorDescription_ = "ERROR reply received from server.";
  {( p_)++; goto _out; }
}
	goto _again;
f22:
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
	goto _again;
f5:
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
	goto _again;
f17:
#line 316 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_notfound); }
	goto _again;
f0:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f20:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
	goto _again;
f2:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
	goto _again;
f11:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ currentUInt_ = 0; }
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
	goto _again;
f9:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f15:
#line 154 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  remainingIOBufLength_ = static_cast<size_t>(currentUInt_);
}
#line 42 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // We have value field, so emplace IOBuf for value.
  message.valueData_.emplace();
  if (!readValue(buffer, message.valueData_.value())) {
    {( p_)++; goto _out; }
  }
}
	goto _again;
f8:
#line 171 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setAppSpecificErrorCode(static_cast<uint32_t>(currentUInt_));
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f21:
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f4:
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f19:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f1:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f7:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ currentUInt_ = 0; }
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;

_again:
	if ( ( savedCs_) == 0 )
		goto _out;
	if ( ++( p_) != ( pe_) )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 332 "src/mcrouter/lib/network/McAsciiParser.rl"

}

// McStorage reply.

#line 2307 "McAsciiParser-gen.cpp"
static const int mc_ascii_storage_reply_start = 1;
static const int mc_ascii_storage_reply_first_final = 78;
static const int mc_ascii_storage_reply_error = 0;

static const int mc_ascii_storage_reply_en_storage_reply = 1;


#line 349 "src/mcrouter/lib/network/McAsciiParser.rl"


void McClientAsciiParser::consumeStorageReplyCommon(folly::IOBuf& buffer) {
  McReply& message = currentMessage_.get<McReply>();
  
#line 2321 "McAsciiParser-gen.cpp"
	{
	}

#line 2325 "McAsciiParser-gen.cpp"
	{
	if ( ( p_) == ( pe_) )
		goto _test_eof;
	if ( ( savedCs_) == 0 )
		goto _out;
_resume:
	switch ( ( savedCs_) ) {
case 1:
	switch( (*( p_)) ) {
		case 67: goto tr0;
		case 68: goto tr2;
		case 69: goto tr3;
		case 78: goto tr4;
		case 83: goto tr5;
	}
	goto tr1;
case 0:
	goto _out;
case 2:
	if ( (*( p_)) == 76 )
		goto tr6;
	goto tr1;
case 3:
	if ( (*( p_)) == 73 )
		goto tr7;
	goto tr1;
case 4:
	if ( (*( p_)) == 69 )
		goto tr8;
	goto tr1;
case 5:
	if ( (*( p_)) == 78 )
		goto tr9;
	goto tr1;
case 6:
	if ( (*( p_)) == 84 )
		goto tr10;
	goto tr1;
case 7:
	if ( (*( p_)) == 95 )
		goto tr11;
	goto tr1;
case 8:
	if ( (*( p_)) == 69 )
		goto tr12;
	goto tr1;
case 9:
	if ( (*( p_)) == 82 )
		goto tr13;
	goto tr1;
case 10:
	if ( (*( p_)) == 82 )
		goto tr14;
	goto tr1;
case 11:
	if ( (*( p_)) == 79 )
		goto tr15;
	goto tr1;
case 12:
	if ( (*( p_)) == 82 )
		goto tr16;
	goto tr1;
case 13:
	switch( (*( p_)) ) {
		case 10: goto tr18;
		case 13: goto tr19;
		case 32: goto tr20;
	}
	goto tr17;
case 14:
	switch( (*( p_)) ) {
		case 10: goto tr22;
		case 13: goto tr23;
	}
	goto tr21;
case 78:
	goto tr1;
case 15:
	if ( (*( p_)) == 10 )
		goto tr24;
	goto tr1;
case 16:
	switch( (*( p_)) ) {
		case 10: goto tr18;
		case 13: goto tr19;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr25;
	goto tr17;
case 17:
	switch( (*( p_)) ) {
		case 10: goto tr22;
		case 13: goto tr23;
		case 32: goto tr26;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr27;
	goto tr21;
case 18:
	switch( (*( p_)) ) {
		case 10: goto tr18;
		case 13: goto tr19;
		case 32: goto tr28;
	}
	goto tr17;
case 19:
	switch( (*( p_)) ) {
		case 10: goto tr18;
		case 13: goto tr19;
	}
	goto tr17;
case 20:
	if ( (*( p_)) == 69 )
		goto tr29;
	goto tr1;
case 21:
	if ( (*( p_)) == 76 )
		goto tr30;
	goto tr1;
case 22:
	if ( (*( p_)) == 69 )
		goto tr31;
	goto tr1;
case 23:
	if ( (*( p_)) == 84 )
		goto tr32;
	goto tr1;
case 24:
	if ( (*( p_)) == 69 )
		goto tr33;
	goto tr1;
case 25:
	if ( (*( p_)) == 68 )
		goto tr34;
	goto tr1;
case 26:
	switch( (*( p_)) ) {
		case 10: goto tr24;
		case 13: goto tr35;
	}
	goto tr1;
case 27:
	switch( (*( p_)) ) {
		case 82: goto tr36;
		case 88: goto tr37;
	}
	goto tr1;
case 28:
	if ( (*( p_)) == 82 )
		goto tr38;
	goto tr1;
case 29:
	if ( (*( p_)) == 79 )
		goto tr39;
	goto tr1;
case 30:
	if ( (*( p_)) == 82 )
		goto tr40;
	goto tr1;
case 31:
	if ( (*( p_)) == 73 )
		goto tr41;
	goto tr1;
case 32:
	if ( (*( p_)) == 83 )
		goto tr42;
	goto tr1;
case 33:
	if ( (*( p_)) == 84 )
		goto tr43;
	goto tr1;
case 34:
	if ( (*( p_)) == 83 )
		goto tr44;
	goto tr1;
case 35:
	if ( (*( p_)) == 79 )
		goto tr45;
	goto tr1;
case 36:
	if ( (*( p_)) == 84 )
		goto tr46;
	goto tr1;
case 37:
	if ( (*( p_)) == 95 )
		goto tr47;
	goto tr1;
case 38:
	switch( (*( p_)) ) {
		case 70: goto tr48;
		case 83: goto tr49;
	}
	goto tr1;
case 39:
	if ( (*( p_)) == 79 )
		goto tr50;
	goto tr1;
case 40:
	if ( (*( p_)) == 85 )
		goto tr51;
	goto tr1;
case 41:
	if ( (*( p_)) == 78 )
		goto tr52;
	goto tr1;
case 42:
	if ( (*( p_)) == 68 )
		goto tr53;
	goto tr1;
case 43:
	if ( (*( p_)) == 84 )
		goto tr54;
	goto tr1;
case 44:
	if ( (*( p_)) == 79 )
		goto tr55;
	goto tr1;
case 45:
	if ( (*( p_)) == 82 )
		goto tr56;
	goto tr1;
case 46:
	if ( (*( p_)) == 69 )
		goto tr57;
	goto tr1;
case 47:
	if ( (*( p_)) == 68 )
		goto tr58;
	goto tr1;
case 48:
	switch( (*( p_)) ) {
		case 69: goto tr59;
		case 84: goto tr60;
	}
	goto tr1;
case 49:
	if ( (*( p_)) == 82 )
		goto tr61;
	goto tr1;
case 50:
	if ( (*( p_)) == 86 )
		goto tr62;
	goto tr1;
case 51:
	if ( (*( p_)) == 69 )
		goto tr63;
	goto tr1;
case 52:
	if ( (*( p_)) == 82 )
		goto tr64;
	goto tr1;
case 53:
	if ( (*( p_)) == 95 )
		goto tr65;
	goto tr1;
case 54:
	if ( (*( p_)) == 69 )
		goto tr66;
	goto tr1;
case 55:
	if ( (*( p_)) == 82 )
		goto tr67;
	goto tr1;
case 56:
	if ( (*( p_)) == 82 )
		goto tr68;
	goto tr1;
case 57:
	if ( (*( p_)) == 79 )
		goto tr69;
	goto tr1;
case 58:
	if ( (*( p_)) == 82 )
		goto tr70;
	goto tr1;
case 59:
	switch( (*( p_)) ) {
		case 10: goto tr72;
		case 13: goto tr73;
		case 32: goto tr74;
	}
	goto tr71;
case 60:
	switch( (*( p_)) ) {
		case 10: goto tr76;
		case 13: goto tr77;
	}
	goto tr75;
case 61:
	switch( (*( p_)) ) {
		case 10: goto tr72;
		case 13: goto tr73;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr78;
	goto tr71;
case 62:
	switch( (*( p_)) ) {
		case 10: goto tr76;
		case 13: goto tr77;
		case 32: goto tr79;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr80;
	goto tr75;
case 63:
	switch( (*( p_)) ) {
		case 10: goto tr72;
		case 13: goto tr73;
		case 32: goto tr81;
	}
	goto tr71;
case 64:
	switch( (*( p_)) ) {
		case 10: goto tr72;
		case 13: goto tr73;
	}
	goto tr71;
case 65:
	switch( (*( p_)) ) {
		case 65: goto tr82;
		case 79: goto tr83;
	}
	goto tr1;
case 66:
	if ( (*( p_)) == 76 )
		goto tr84;
	goto tr1;
case 67:
	if ( (*( p_)) == 69 )
		goto tr85;
	goto tr1;
case 68:
	if ( (*( p_)) == 95 )
		goto tr86;
	goto tr1;
case 69:
	if ( (*( p_)) == 83 )
		goto tr87;
	goto tr1;
case 70:
	if ( (*( p_)) == 84 )
		goto tr88;
	goto tr1;
case 71:
	if ( (*( p_)) == 79 )
		goto tr89;
	goto tr1;
case 72:
	if ( (*( p_)) == 82 )
		goto tr90;
	goto tr1;
case 73:
	if ( (*( p_)) == 69 )
		goto tr91;
	goto tr1;
case 74:
	if ( (*( p_)) == 68 )
		goto tr92;
	goto tr1;
case 75:
	if ( (*( p_)) == 82 )
		goto tr93;
	goto tr1;
case 76:
	if ( (*( p_)) == 69 )
		goto tr94;
	goto tr1;
case 77:
	if ( (*( p_)) == 68 )
		goto tr95;
	goto tr1;
	}

	tr1: ( savedCs_) = 0; goto _again;
	tr0: ( savedCs_) = 2; goto _again;
	tr6: ( savedCs_) = 3; goto _again;
	tr7: ( savedCs_) = 4; goto _again;
	tr8: ( savedCs_) = 5; goto _again;
	tr9: ( savedCs_) = 6; goto _again;
	tr10: ( savedCs_) = 7; goto _again;
	tr11: ( savedCs_) = 8; goto _again;
	tr12: ( savedCs_) = 9; goto _again;
	tr13: ( savedCs_) = 10; goto _again;
	tr14: ( savedCs_) = 11; goto _again;
	tr15: ( savedCs_) = 12; goto _again;
	tr16: ( savedCs_) = 13; goto _again;
	tr17: ( savedCs_) = 14; goto f0;
	tr21: ( savedCs_) = 14; goto f3;
	tr35: ( savedCs_) = 15; goto _again;
	tr19: ( savedCs_) = 15; goto f2;
	tr23: ( savedCs_) = 15; goto f5;
	tr73: ( savedCs_) = 15; goto f16;
	tr77: ( savedCs_) = 15; goto f18;
	tr20: ( savedCs_) = 16; goto f0;
	tr25: ( savedCs_) = 17; goto f7;
	tr27: ( savedCs_) = 17; goto f9;
	tr26: ( savedCs_) = 18; goto f8;
	tr28: ( savedCs_) = 19; goto f0;
	tr2: ( savedCs_) = 20; goto _again;
	tr29: ( savedCs_) = 21; goto _again;
	tr30: ( savedCs_) = 22; goto _again;
	tr31: ( savedCs_) = 23; goto _again;
	tr32: ( savedCs_) = 24; goto _again;
	tr33: ( savedCs_) = 25; goto _again;
	tr34: ( savedCs_) = 26; goto f10;
	tr40: ( savedCs_) = 26; goto f11;
	tr44: ( savedCs_) = 26; goto f12;
	tr53: ( savedCs_) = 26; goto f13;
	tr58: ( savedCs_) = 26; goto f14;
	tr92: ( savedCs_) = 26; goto f19;
	tr95: ( savedCs_) = 26; goto f20;
	tr3: ( savedCs_) = 27; goto _again;
	tr36: ( savedCs_) = 28; goto _again;
	tr38: ( savedCs_) = 29; goto _again;
	tr39: ( savedCs_) = 30; goto _again;
	tr37: ( savedCs_) = 31; goto _again;
	tr41: ( savedCs_) = 32; goto _again;
	tr42: ( savedCs_) = 33; goto _again;
	tr43: ( savedCs_) = 34; goto _again;
	tr4: ( savedCs_) = 35; goto _again;
	tr45: ( savedCs_) = 36; goto _again;
	tr46: ( savedCs_) = 37; goto _again;
	tr47: ( savedCs_) = 38; goto _again;
	tr48: ( savedCs_) = 39; goto _again;
	tr50: ( savedCs_) = 40; goto _again;
	tr51: ( savedCs_) = 41; goto _again;
	tr52: ( savedCs_) = 42; goto _again;
	tr49: ( savedCs_) = 43; goto _again;
	tr54: ( savedCs_) = 44; goto _again;
	tr55: ( savedCs_) = 45; goto _again;
	tr56: ( savedCs_) = 46; goto _again;
	tr57: ( savedCs_) = 47; goto _again;
	tr5: ( savedCs_) = 48; goto _again;
	tr59: ( savedCs_) = 49; goto _again;
	tr61: ( savedCs_) = 50; goto _again;
	tr62: ( savedCs_) = 51; goto _again;
	tr63: ( savedCs_) = 52; goto _again;
	tr64: ( savedCs_) = 53; goto _again;
	tr65: ( savedCs_) = 54; goto _again;
	tr66: ( savedCs_) = 55; goto _again;
	tr67: ( savedCs_) = 56; goto _again;
	tr68: ( savedCs_) = 57; goto _again;
	tr69: ( savedCs_) = 58; goto _again;
	tr70: ( savedCs_) = 59; goto _again;
	tr71: ( savedCs_) = 60; goto f0;
	tr75: ( savedCs_) = 60; goto f3;
	tr74: ( savedCs_) = 61; goto f0;
	tr78: ( savedCs_) = 62; goto f7;
	tr80: ( savedCs_) = 62; goto f9;
	tr79: ( savedCs_) = 63; goto f8;
	tr81: ( savedCs_) = 64; goto f0;
	tr60: ( savedCs_) = 65; goto _again;
	tr82: ( savedCs_) = 66; goto _again;
	tr84: ( savedCs_) = 67; goto _again;
	tr85: ( savedCs_) = 68; goto _again;
	tr86: ( savedCs_) = 69; goto _again;
	tr87: ( savedCs_) = 70; goto _again;
	tr88: ( savedCs_) = 71; goto _again;
	tr89: ( savedCs_) = 72; goto _again;
	tr90: ( savedCs_) = 73; goto _again;
	tr91: ( savedCs_) = 74; goto _again;
	tr83: ( savedCs_) = 75; goto _again;
	tr93: ( savedCs_) = 76; goto _again;
	tr94: ( savedCs_) = 77; goto _again;
	tr18: ( savedCs_) = 78; goto f1;
	tr22: ( savedCs_) = 78; goto f4;
	tr24: ( savedCs_) = 78; goto f6;
	tr72: ( savedCs_) = 78; goto f15;
	tr76: ( savedCs_) = 78; goto f17;

f3:
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f6:
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f13:
#line 176 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_notfound); }
	goto _again;
f10:
#line 177 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_deleted); }
	goto _again;
f11:
#line 187 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // This is unexpected error reply, just put ourself into error state.
  state_ = State::ERROR;
  currentErrorDescription_ = "ERROR reply received from server.";
  {( p_)++; goto _out; }
}
	goto _again;
f18:
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
	goto _again;
f5:
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
	goto _again;
f20:
#line 340 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_stored); }
	goto _again;
f19:
#line 341 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_stalestored); }
	goto _again;
f14:
#line 342 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_notstored); }
	goto _again;
f12:
#line 343 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_exists); }
	goto _again;
f0:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f16:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
	goto _again;
f2:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
	goto _again;
f9:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f8:
#line 171 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setAppSpecificErrorCode(static_cast<uint32_t>(currentUInt_));
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f17:
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f4:
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f15:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f1:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f7:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ currentUInt_ = 0; }
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;

_again:
	if ( ( savedCs_) == 0 )
		goto _out;
	if ( ++( p_) != ( pe_) )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 357 "src/mcrouter/lib/network/McAsciiParser.rl"

}

// McArithm reply.

#line 3042 "McAsciiParser-gen.cpp"
static const int mc_ascii_arithm_reply_start = 1;
static const int mc_ascii_arithm_reply_first_final = 52;
static const int mc_ascii_arithm_reply_error = 0;

static const int mc_ascii_arithm_reply_en_arithm_reply = 1;


#line 369 "src/mcrouter/lib/network/McAsciiParser.rl"


void McClientAsciiParser::consumeArithmReplyCommon(folly::IOBuf& buffer) {
  McReply& message = currentMessage_.get<McReply>();
  
#line 3056 "McAsciiParser-gen.cpp"
	{
	}

#line 3060 "McAsciiParser-gen.cpp"
	{
	if ( ( p_) == ( pe_) )
		goto _test_eof;
	if ( ( savedCs_) == 0 )
		goto _out;
_resume:
	switch ( ( savedCs_) ) {
case 1:
	switch( (*( p_)) ) {
		case 67: goto tr2;
		case 69: goto tr3;
		case 78: goto tr4;
		case 83: goto tr5;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr0;
	goto tr1;
case 0:
	goto _out;
case 2:
	switch( (*( p_)) ) {
		case 10: goto tr6;
		case 13: goto tr7;
		case 32: goto tr8;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr9;
	goto tr1;
case 52:
	goto tr1;
case 3:
	if ( (*( p_)) == 10 )
		goto tr10;
	goto tr1;
case 4:
	switch( (*( p_)) ) {
		case 10: goto tr10;
		case 13: goto tr11;
		case 32: goto tr12;
	}
	goto tr1;
case 5:
	if ( (*( p_)) == 76 )
		goto tr13;
	goto tr1;
case 6:
	if ( (*( p_)) == 73 )
		goto tr14;
	goto tr1;
case 7:
	if ( (*( p_)) == 69 )
		goto tr15;
	goto tr1;
case 8:
	if ( (*( p_)) == 78 )
		goto tr16;
	goto tr1;
case 9:
	if ( (*( p_)) == 84 )
		goto tr17;
	goto tr1;
case 10:
	if ( (*( p_)) == 95 )
		goto tr18;
	goto tr1;
case 11:
	if ( (*( p_)) == 69 )
		goto tr19;
	goto tr1;
case 12:
	if ( (*( p_)) == 82 )
		goto tr20;
	goto tr1;
case 13:
	if ( (*( p_)) == 82 )
		goto tr21;
	goto tr1;
case 14:
	if ( (*( p_)) == 79 )
		goto tr22;
	goto tr1;
case 15:
	if ( (*( p_)) == 82 )
		goto tr23;
	goto tr1;
case 16:
	switch( (*( p_)) ) {
		case 10: goto tr25;
		case 13: goto tr26;
		case 32: goto tr27;
	}
	goto tr24;
case 17:
	switch( (*( p_)) ) {
		case 10: goto tr29;
		case 13: goto tr30;
	}
	goto tr28;
case 18:
	switch( (*( p_)) ) {
		case 10: goto tr25;
		case 13: goto tr26;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr31;
	goto tr24;
case 19:
	switch( (*( p_)) ) {
		case 10: goto tr29;
		case 13: goto tr30;
		case 32: goto tr32;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr33;
	goto tr28;
case 20:
	switch( (*( p_)) ) {
		case 10: goto tr25;
		case 13: goto tr26;
		case 32: goto tr34;
	}
	goto tr24;
case 21:
	switch( (*( p_)) ) {
		case 10: goto tr25;
		case 13: goto tr26;
	}
	goto tr24;
case 22:
	if ( (*( p_)) == 82 )
		goto tr35;
	goto tr1;
case 23:
	if ( (*( p_)) == 82 )
		goto tr36;
	goto tr1;
case 24:
	if ( (*( p_)) == 79 )
		goto tr37;
	goto tr1;
case 25:
	if ( (*( p_)) == 82 )
		goto tr38;
	goto tr1;
case 26:
	switch( (*( p_)) ) {
		case 10: goto tr10;
		case 13: goto tr11;
	}
	goto tr1;
case 27:
	if ( (*( p_)) == 79 )
		goto tr39;
	goto tr1;
case 28:
	if ( (*( p_)) == 84 )
		goto tr40;
	goto tr1;
case 29:
	if ( (*( p_)) == 95 )
		goto tr41;
	goto tr1;
case 30:
	if ( (*( p_)) == 70 )
		goto tr42;
	goto tr1;
case 31:
	if ( (*( p_)) == 79 )
		goto tr43;
	goto tr1;
case 32:
	if ( (*( p_)) == 85 )
		goto tr44;
	goto tr1;
case 33:
	if ( (*( p_)) == 78 )
		goto tr45;
	goto tr1;
case 34:
	if ( (*( p_)) == 68 )
		goto tr46;
	goto tr1;
case 35:
	if ( (*( p_)) == 69 )
		goto tr47;
	goto tr1;
case 36:
	if ( (*( p_)) == 82 )
		goto tr48;
	goto tr1;
case 37:
	if ( (*( p_)) == 86 )
		goto tr49;
	goto tr1;
case 38:
	if ( (*( p_)) == 69 )
		goto tr50;
	goto tr1;
case 39:
	if ( (*( p_)) == 82 )
		goto tr51;
	goto tr1;
case 40:
	if ( (*( p_)) == 95 )
		goto tr52;
	goto tr1;
case 41:
	if ( (*( p_)) == 69 )
		goto tr53;
	goto tr1;
case 42:
	if ( (*( p_)) == 82 )
		goto tr54;
	goto tr1;
case 43:
	if ( (*( p_)) == 82 )
		goto tr55;
	goto tr1;
case 44:
	if ( (*( p_)) == 79 )
		goto tr56;
	goto tr1;
case 45:
	if ( (*( p_)) == 82 )
		goto tr57;
	goto tr1;
case 46:
	switch( (*( p_)) ) {
		case 10: goto tr59;
		case 13: goto tr60;
		case 32: goto tr61;
	}
	goto tr58;
case 47:
	switch( (*( p_)) ) {
		case 10: goto tr63;
		case 13: goto tr64;
	}
	goto tr62;
case 48:
	switch( (*( p_)) ) {
		case 10: goto tr59;
		case 13: goto tr60;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr65;
	goto tr58;
case 49:
	switch( (*( p_)) ) {
		case 10: goto tr63;
		case 13: goto tr64;
		case 32: goto tr66;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr67;
	goto tr62;
case 50:
	switch( (*( p_)) ) {
		case 10: goto tr59;
		case 13: goto tr60;
		case 32: goto tr68;
	}
	goto tr58;
case 51:
	switch( (*( p_)) ) {
		case 10: goto tr59;
		case 13: goto tr60;
	}
	goto tr58;
	}

	tr1: ( savedCs_) = 0; goto _again;
	tr0: ( savedCs_) = 2; goto f0;
	tr9: ( savedCs_) = 2; goto f3;
	tr11: ( savedCs_) = 3; goto _again;
	tr7: ( savedCs_) = 3; goto f2;
	tr26: ( savedCs_) = 3; goto f7;
	tr30: ( savedCs_) = 3; goto f10;
	tr60: ( savedCs_) = 3; goto f17;
	tr64: ( savedCs_) = 3; goto f19;
	tr12: ( savedCs_) = 4; goto _again;
	tr8: ( savedCs_) = 4; goto f2;
	tr2: ( savedCs_) = 5; goto _again;
	tr13: ( savedCs_) = 6; goto _again;
	tr14: ( savedCs_) = 7; goto _again;
	tr15: ( savedCs_) = 8; goto _again;
	tr16: ( savedCs_) = 9; goto _again;
	tr17: ( savedCs_) = 10; goto _again;
	tr18: ( savedCs_) = 11; goto _again;
	tr19: ( savedCs_) = 12; goto _again;
	tr20: ( savedCs_) = 13; goto _again;
	tr21: ( savedCs_) = 14; goto _again;
	tr22: ( savedCs_) = 15; goto _again;
	tr23: ( savedCs_) = 16; goto _again;
	tr24: ( savedCs_) = 17; goto f5;
	tr28: ( savedCs_) = 17; goto f8;
	tr27: ( savedCs_) = 18; goto f5;
	tr31: ( savedCs_) = 19; goto f11;
	tr33: ( savedCs_) = 19; goto f13;
	tr32: ( savedCs_) = 20; goto f12;
	tr34: ( savedCs_) = 21; goto f5;
	tr3: ( savedCs_) = 22; goto _again;
	tr35: ( savedCs_) = 23; goto _again;
	tr36: ( savedCs_) = 24; goto _again;
	tr37: ( savedCs_) = 25; goto _again;
	tr38: ( savedCs_) = 26; goto f14;
	tr46: ( savedCs_) = 26; goto f15;
	tr4: ( savedCs_) = 27; goto _again;
	tr39: ( savedCs_) = 28; goto _again;
	tr40: ( savedCs_) = 29; goto _again;
	tr41: ( savedCs_) = 30; goto _again;
	tr42: ( savedCs_) = 31; goto _again;
	tr43: ( savedCs_) = 32; goto _again;
	tr44: ( savedCs_) = 33; goto _again;
	tr45: ( savedCs_) = 34; goto _again;
	tr5: ( savedCs_) = 35; goto _again;
	tr47: ( savedCs_) = 36; goto _again;
	tr48: ( savedCs_) = 37; goto _again;
	tr49: ( savedCs_) = 38; goto _again;
	tr50: ( savedCs_) = 39; goto _again;
	tr51: ( savedCs_) = 40; goto _again;
	tr52: ( savedCs_) = 41; goto _again;
	tr53: ( savedCs_) = 42; goto _again;
	tr54: ( savedCs_) = 43; goto _again;
	tr55: ( savedCs_) = 44; goto _again;
	tr56: ( savedCs_) = 45; goto _again;
	tr57: ( savedCs_) = 46; goto _again;
	tr58: ( savedCs_) = 47; goto f5;
	tr62: ( savedCs_) = 47; goto f8;
	tr61: ( savedCs_) = 48; goto f5;
	tr65: ( savedCs_) = 49; goto f11;
	tr67: ( savedCs_) = 49; goto f13;
	tr66: ( savedCs_) = 50; goto f12;
	tr68: ( savedCs_) = 51; goto f5;
	tr6: ( savedCs_) = 52; goto f1;
	tr10: ( savedCs_) = 52; goto f4;
	tr25: ( savedCs_) = 52; goto f6;
	tr29: ( savedCs_) = 52; goto f9;
	tr59: ( savedCs_) = 52; goto f16;
	tr63: ( savedCs_) = 52; goto f18;

f8:
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f4:
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f2:
#line 162 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setDelta(currentUInt_);
}
	goto _again;
f15:
#line 176 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_notfound); }
	goto _again;
f14:
#line 187 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // This is unexpected error reply, just put ourself into error state.
  state_ = State::ERROR;
  currentErrorDescription_ = "ERROR reply received from server.";
  {( p_)++; goto _out; }
}
	goto _again;
f19:
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
	goto _again;
f10:
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
	goto _again;
f5:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f17:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
	goto _again;
f7:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
	goto _again;
f13:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f3:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
#line 365 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_stored); }
	goto _again;
f1:
#line 162 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setDelta(currentUInt_);
}
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f12:
#line 171 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setAppSpecificErrorCode(static_cast<uint32_t>(currentUInt_));
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f18:
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f9:
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f16:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f6:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f0:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ currentUInt_ = 0; }
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
#line 365 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_stored); }
	goto _again;
f11:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ currentUInt_ = 0; }
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;

_again:
	if ( ( savedCs_) == 0 )
		goto _out;
	if ( ++( p_) != ( pe_) )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 377 "src/mcrouter/lib/network/McAsciiParser.rl"

}

// McVersion reply.

#line 3663 "McAsciiParser-gen.cpp"
static const int mc_ascii_version_reply_start = 1;
static const int mc_ascii_version_reply_first_final = 50;
static const int mc_ascii_version_reply_error = 0;

static const int mc_ascii_version_reply_en_version_reply = 1;


#line 390 "src/mcrouter/lib/network/McAsciiParser.rl"


template<>
void McClientAsciiParser::consumeMessage<McReply, McOperation<mc_op_version>>(
    folly::IOBuf& buffer) {
  McReply& message = currentMessage_.get<McReply>();
  
#line 3679 "McAsciiParser-gen.cpp"
	{
	}

#line 3683 "McAsciiParser-gen.cpp"
	{
	if ( ( p_) == ( pe_) )
		goto _test_eof;
	if ( ( savedCs_) == 0 )
		goto _out;
_resume:
	switch ( ( savedCs_) ) {
case 1:
	switch( (*( p_)) ) {
		case 67: goto tr0;
		case 69: goto tr2;
		case 83: goto tr3;
		case 86: goto tr4;
	}
	goto tr1;
case 0:
	goto _out;
case 2:
	if ( (*( p_)) == 76 )
		goto tr5;
	goto tr1;
case 3:
	if ( (*( p_)) == 73 )
		goto tr6;
	goto tr1;
case 4:
	if ( (*( p_)) == 69 )
		goto tr7;
	goto tr1;
case 5:
	if ( (*( p_)) == 78 )
		goto tr8;
	goto tr1;
case 6:
	if ( (*( p_)) == 84 )
		goto tr9;
	goto tr1;
case 7:
	if ( (*( p_)) == 95 )
		goto tr10;
	goto tr1;
case 8:
	if ( (*( p_)) == 69 )
		goto tr11;
	goto tr1;
case 9:
	if ( (*( p_)) == 82 )
		goto tr12;
	goto tr1;
case 10:
	if ( (*( p_)) == 82 )
		goto tr13;
	goto tr1;
case 11:
	if ( (*( p_)) == 79 )
		goto tr14;
	goto tr1;
case 12:
	if ( (*( p_)) == 82 )
		goto tr15;
	goto tr1;
case 13:
	switch( (*( p_)) ) {
		case 10: goto tr17;
		case 13: goto tr18;
		case 32: goto tr19;
	}
	goto tr16;
case 14:
	switch( (*( p_)) ) {
		case 10: goto tr21;
		case 13: goto tr22;
	}
	goto tr20;
case 50:
	goto tr1;
case 15:
	if ( (*( p_)) == 10 )
		goto tr23;
	goto tr1;
case 16:
	switch( (*( p_)) ) {
		case 10: goto tr17;
		case 13: goto tr18;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr24;
	goto tr16;
case 17:
	switch( (*( p_)) ) {
		case 10: goto tr21;
		case 13: goto tr22;
		case 32: goto tr25;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr26;
	goto tr20;
case 18:
	switch( (*( p_)) ) {
		case 10: goto tr17;
		case 13: goto tr18;
		case 32: goto tr27;
	}
	goto tr16;
case 19:
	switch( (*( p_)) ) {
		case 10: goto tr17;
		case 13: goto tr18;
	}
	goto tr16;
case 20:
	if ( (*( p_)) == 82 )
		goto tr28;
	goto tr1;
case 21:
	if ( (*( p_)) == 82 )
		goto tr29;
	goto tr1;
case 22:
	if ( (*( p_)) == 79 )
		goto tr30;
	goto tr1;
case 23:
	if ( (*( p_)) == 82 )
		goto tr31;
	goto tr1;
case 24:
	switch( (*( p_)) ) {
		case 10: goto tr23;
		case 13: goto tr32;
	}
	goto tr1;
case 25:
	if ( (*( p_)) == 69 )
		goto tr33;
	goto tr1;
case 26:
	if ( (*( p_)) == 82 )
		goto tr34;
	goto tr1;
case 27:
	if ( (*( p_)) == 86 )
		goto tr35;
	goto tr1;
case 28:
	if ( (*( p_)) == 69 )
		goto tr36;
	goto tr1;
case 29:
	if ( (*( p_)) == 82 )
		goto tr37;
	goto tr1;
case 30:
	if ( (*( p_)) == 95 )
		goto tr38;
	goto tr1;
case 31:
	if ( (*( p_)) == 69 )
		goto tr39;
	goto tr1;
case 32:
	if ( (*( p_)) == 82 )
		goto tr40;
	goto tr1;
case 33:
	if ( (*( p_)) == 82 )
		goto tr41;
	goto tr1;
case 34:
	if ( (*( p_)) == 79 )
		goto tr42;
	goto tr1;
case 35:
	if ( (*( p_)) == 82 )
		goto tr43;
	goto tr1;
case 36:
	switch( (*( p_)) ) {
		case 10: goto tr45;
		case 13: goto tr46;
		case 32: goto tr47;
	}
	goto tr44;
case 37:
	switch( (*( p_)) ) {
		case 10: goto tr49;
		case 13: goto tr50;
	}
	goto tr48;
case 38:
	switch( (*( p_)) ) {
		case 10: goto tr45;
		case 13: goto tr46;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr51;
	goto tr44;
case 39:
	switch( (*( p_)) ) {
		case 10: goto tr49;
		case 13: goto tr50;
		case 32: goto tr52;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr53;
	goto tr48;
case 40:
	switch( (*( p_)) ) {
		case 10: goto tr45;
		case 13: goto tr46;
		case 32: goto tr54;
	}
	goto tr44;
case 41:
	switch( (*( p_)) ) {
		case 10: goto tr45;
		case 13: goto tr46;
	}
	goto tr44;
case 42:
	if ( (*( p_)) == 69 )
		goto tr55;
	goto tr1;
case 43:
	if ( (*( p_)) == 82 )
		goto tr56;
	goto tr1;
case 44:
	if ( (*( p_)) == 83 )
		goto tr57;
	goto tr1;
case 45:
	if ( (*( p_)) == 73 )
		goto tr58;
	goto tr1;
case 46:
	if ( (*( p_)) == 79 )
		goto tr59;
	goto tr1;
case 47:
	if ( (*( p_)) == 78 )
		goto tr60;
	goto tr1;
case 48:
	if ( (*( p_)) == 32 )
		goto tr61;
	goto tr1;
case 49:
	switch( (*( p_)) ) {
		case 10: goto tr23;
		case 13: goto tr32;
	}
	goto tr62;
	}

	tr1: ( savedCs_) = 0; goto _again;
	tr0: ( savedCs_) = 2; goto _again;
	tr5: ( savedCs_) = 3; goto _again;
	tr6: ( savedCs_) = 4; goto _again;
	tr7: ( savedCs_) = 5; goto _again;
	tr8: ( savedCs_) = 6; goto _again;
	tr9: ( savedCs_) = 7; goto _again;
	tr10: ( savedCs_) = 8; goto _again;
	tr11: ( savedCs_) = 9; goto _again;
	tr12: ( savedCs_) = 10; goto _again;
	tr13: ( savedCs_) = 11; goto _again;
	tr14: ( savedCs_) = 12; goto _again;
	tr15: ( savedCs_) = 13; goto _again;
	tr16: ( savedCs_) = 14; goto f0;
	tr20: ( savedCs_) = 14; goto f3;
	tr32: ( savedCs_) = 15; goto _again;
	tr18: ( savedCs_) = 15; goto f2;
	tr22: ( savedCs_) = 15; goto f5;
	tr46: ( savedCs_) = 15; goto f12;
	tr50: ( savedCs_) = 15; goto f14;
	tr19: ( savedCs_) = 16; goto f0;
	tr24: ( savedCs_) = 17; goto f7;
	tr26: ( savedCs_) = 17; goto f9;
	tr25: ( savedCs_) = 18; goto f8;
	tr27: ( savedCs_) = 19; goto f0;
	tr2: ( savedCs_) = 20; goto _again;
	tr28: ( savedCs_) = 21; goto _again;
	tr29: ( savedCs_) = 22; goto _again;
	tr30: ( savedCs_) = 23; goto _again;
	tr31: ( savedCs_) = 24; goto f10;
	tr3: ( savedCs_) = 25; goto _again;
	tr33: ( savedCs_) = 26; goto _again;
	tr34: ( savedCs_) = 27; goto _again;
	tr35: ( savedCs_) = 28; goto _again;
	tr36: ( savedCs_) = 29; goto _again;
	tr37: ( savedCs_) = 30; goto _again;
	tr38: ( savedCs_) = 31; goto _again;
	tr39: ( savedCs_) = 32; goto _again;
	tr40: ( savedCs_) = 33; goto _again;
	tr41: ( savedCs_) = 34; goto _again;
	tr42: ( savedCs_) = 35; goto _again;
	tr43: ( savedCs_) = 36; goto _again;
	tr44: ( savedCs_) = 37; goto f0;
	tr48: ( savedCs_) = 37; goto f3;
	tr47: ( savedCs_) = 38; goto f0;
	tr51: ( savedCs_) = 39; goto f7;
	tr53: ( savedCs_) = 39; goto f9;
	tr52: ( savedCs_) = 40; goto f8;
	tr54: ( savedCs_) = 41; goto f0;
	tr4: ( savedCs_) = 42; goto _again;
	tr55: ( savedCs_) = 43; goto _again;
	tr56: ( savedCs_) = 44; goto _again;
	tr57: ( savedCs_) = 45; goto _again;
	tr58: ( savedCs_) = 46; goto _again;
	tr59: ( savedCs_) = 47; goto _again;
	tr60: ( savedCs_) = 48; goto _again;
	tr62: ( savedCs_) = 49; goto f3;
	tr61: ( savedCs_) = 49; goto f15;
	tr17: ( savedCs_) = 50; goto f1;
	tr21: ( savedCs_) = 50; goto f4;
	tr23: ( savedCs_) = 50; goto f6;
	tr45: ( savedCs_) = 50; goto f11;
	tr49: ( savedCs_) = 50; goto f13;

f3:
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f6:
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f10:
#line 187 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // This is unexpected error reply, just put ourself into error state.
  state_ = State::ERROR;
  currentErrorDescription_ = "ERROR reply received from server.";
  {( p_)++; goto _out; }
}
	goto _again;
f14:
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
	goto _again;
f5:
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
	goto _again;
f15:
#line 385 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_ok); }
	goto _again;
f0:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f12:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
	goto _again;
f2:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
	goto _again;
f9:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f8:
#line 171 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setAppSpecificErrorCode(static_cast<uint32_t>(currentUInt_));
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f13:
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f4:
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f11:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f1:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f7:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ currentUInt_ = 0; }
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;

_again:
	if ( ( savedCs_) == 0 )
		goto _out;
	if ( ++( p_) != ( pe_) )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 400 "src/mcrouter/lib/network/McAsciiParser.rl"

}

// McDelete reply.

#line 4228 "McAsciiParser-gen.cpp"
static const int mc_ascii_delete_reply_start = 1;
static const int mc_ascii_delete_reply_first_final = 56;
static const int mc_ascii_delete_reply_error = 0;

static const int mc_ascii_delete_reply_en_delete_reply = 1;


#line 412 "src/mcrouter/lib/network/McAsciiParser.rl"


template<>
void McClientAsciiParser::consumeMessage<McReply, McOperation<mc_op_delete>>(
    folly::IOBuf& buffer) {
  McReply& message = currentMessage_.get<McReply>();
  
#line 4244 "McAsciiParser-gen.cpp"
	{
	}

#line 4248 "McAsciiParser-gen.cpp"
	{
	if ( ( p_) == ( pe_) )
		goto _test_eof;
	if ( ( savedCs_) == 0 )
		goto _out;
_resume:
	switch ( ( savedCs_) ) {
case 1:
	switch( (*( p_)) ) {
		case 67: goto tr0;
		case 68: goto tr2;
		case 69: goto tr3;
		case 78: goto tr4;
		case 83: goto tr5;
	}
	goto tr1;
case 0:
	goto _out;
case 2:
	if ( (*( p_)) == 76 )
		goto tr6;
	goto tr1;
case 3:
	if ( (*( p_)) == 73 )
		goto tr7;
	goto tr1;
case 4:
	if ( (*( p_)) == 69 )
		goto tr8;
	goto tr1;
case 5:
	if ( (*( p_)) == 78 )
		goto tr9;
	goto tr1;
case 6:
	if ( (*( p_)) == 84 )
		goto tr10;
	goto tr1;
case 7:
	if ( (*( p_)) == 95 )
		goto tr11;
	goto tr1;
case 8:
	if ( (*( p_)) == 69 )
		goto tr12;
	goto tr1;
case 9:
	if ( (*( p_)) == 82 )
		goto tr13;
	goto tr1;
case 10:
	if ( (*( p_)) == 82 )
		goto tr14;
	goto tr1;
case 11:
	if ( (*( p_)) == 79 )
		goto tr15;
	goto tr1;
case 12:
	if ( (*( p_)) == 82 )
		goto tr16;
	goto tr1;
case 13:
	switch( (*( p_)) ) {
		case 10: goto tr18;
		case 13: goto tr19;
		case 32: goto tr20;
	}
	goto tr17;
case 14:
	switch( (*( p_)) ) {
		case 10: goto tr22;
		case 13: goto tr23;
	}
	goto tr21;
case 56:
	goto tr1;
case 15:
	if ( (*( p_)) == 10 )
		goto tr24;
	goto tr1;
case 16:
	switch( (*( p_)) ) {
		case 10: goto tr18;
		case 13: goto tr19;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr25;
	goto tr17;
case 17:
	switch( (*( p_)) ) {
		case 10: goto tr22;
		case 13: goto tr23;
		case 32: goto tr26;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr27;
	goto tr21;
case 18:
	switch( (*( p_)) ) {
		case 10: goto tr18;
		case 13: goto tr19;
		case 32: goto tr28;
	}
	goto tr17;
case 19:
	switch( (*( p_)) ) {
		case 10: goto tr18;
		case 13: goto tr19;
	}
	goto tr17;
case 20:
	if ( (*( p_)) == 69 )
		goto tr29;
	goto tr1;
case 21:
	if ( (*( p_)) == 76 )
		goto tr30;
	goto tr1;
case 22:
	if ( (*( p_)) == 69 )
		goto tr31;
	goto tr1;
case 23:
	if ( (*( p_)) == 84 )
		goto tr32;
	goto tr1;
case 24:
	if ( (*( p_)) == 69 )
		goto tr33;
	goto tr1;
case 25:
	if ( (*( p_)) == 68 )
		goto tr34;
	goto tr1;
case 26:
	switch( (*( p_)) ) {
		case 10: goto tr24;
		case 13: goto tr35;
	}
	goto tr1;
case 27:
	if ( (*( p_)) == 82 )
		goto tr36;
	goto tr1;
case 28:
	if ( (*( p_)) == 82 )
		goto tr37;
	goto tr1;
case 29:
	if ( (*( p_)) == 79 )
		goto tr38;
	goto tr1;
case 30:
	if ( (*( p_)) == 82 )
		goto tr39;
	goto tr1;
case 31:
	if ( (*( p_)) == 79 )
		goto tr40;
	goto tr1;
case 32:
	if ( (*( p_)) == 84 )
		goto tr41;
	goto tr1;
case 33:
	if ( (*( p_)) == 95 )
		goto tr42;
	goto tr1;
case 34:
	if ( (*( p_)) == 70 )
		goto tr43;
	goto tr1;
case 35:
	if ( (*( p_)) == 79 )
		goto tr44;
	goto tr1;
case 36:
	if ( (*( p_)) == 85 )
		goto tr45;
	goto tr1;
case 37:
	if ( (*( p_)) == 78 )
		goto tr46;
	goto tr1;
case 38:
	if ( (*( p_)) == 68 )
		goto tr47;
	goto tr1;
case 39:
	if ( (*( p_)) == 69 )
		goto tr48;
	goto tr1;
case 40:
	if ( (*( p_)) == 82 )
		goto tr49;
	goto tr1;
case 41:
	if ( (*( p_)) == 86 )
		goto tr50;
	goto tr1;
case 42:
	if ( (*( p_)) == 69 )
		goto tr51;
	goto tr1;
case 43:
	if ( (*( p_)) == 82 )
		goto tr52;
	goto tr1;
case 44:
	if ( (*( p_)) == 95 )
		goto tr53;
	goto tr1;
case 45:
	if ( (*( p_)) == 69 )
		goto tr54;
	goto tr1;
case 46:
	if ( (*( p_)) == 82 )
		goto tr55;
	goto tr1;
case 47:
	if ( (*( p_)) == 82 )
		goto tr56;
	goto tr1;
case 48:
	if ( (*( p_)) == 79 )
		goto tr57;
	goto tr1;
case 49:
	if ( (*( p_)) == 82 )
		goto tr58;
	goto tr1;
case 50:
	switch( (*( p_)) ) {
		case 10: goto tr60;
		case 13: goto tr61;
		case 32: goto tr62;
	}
	goto tr59;
case 51:
	switch( (*( p_)) ) {
		case 10: goto tr64;
		case 13: goto tr65;
	}
	goto tr63;
case 52:
	switch( (*( p_)) ) {
		case 10: goto tr60;
		case 13: goto tr61;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr66;
	goto tr59;
case 53:
	switch( (*( p_)) ) {
		case 10: goto tr64;
		case 13: goto tr65;
		case 32: goto tr67;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr68;
	goto tr63;
case 54:
	switch( (*( p_)) ) {
		case 10: goto tr60;
		case 13: goto tr61;
		case 32: goto tr69;
	}
	goto tr59;
case 55:
	switch( (*( p_)) ) {
		case 10: goto tr60;
		case 13: goto tr61;
	}
	goto tr59;
	}

	tr1: ( savedCs_) = 0; goto _again;
	tr0: ( savedCs_) = 2; goto _again;
	tr6: ( savedCs_) = 3; goto _again;
	tr7: ( savedCs_) = 4; goto _again;
	tr8: ( savedCs_) = 5; goto _again;
	tr9: ( savedCs_) = 6; goto _again;
	tr10: ( savedCs_) = 7; goto _again;
	tr11: ( savedCs_) = 8; goto _again;
	tr12: ( savedCs_) = 9; goto _again;
	tr13: ( savedCs_) = 10; goto _again;
	tr14: ( savedCs_) = 11; goto _again;
	tr15: ( savedCs_) = 12; goto _again;
	tr16: ( savedCs_) = 13; goto _again;
	tr17: ( savedCs_) = 14; goto f0;
	tr21: ( savedCs_) = 14; goto f3;
	tr35: ( savedCs_) = 15; goto _again;
	tr19: ( savedCs_) = 15; goto f2;
	tr23: ( savedCs_) = 15; goto f5;
	tr61: ( savedCs_) = 15; goto f14;
	tr65: ( savedCs_) = 15; goto f16;
	tr20: ( savedCs_) = 16; goto f0;
	tr25: ( savedCs_) = 17; goto f7;
	tr27: ( savedCs_) = 17; goto f9;
	tr26: ( savedCs_) = 18; goto f8;
	tr28: ( savedCs_) = 19; goto f0;
	tr2: ( savedCs_) = 20; goto _again;
	tr29: ( savedCs_) = 21; goto _again;
	tr30: ( savedCs_) = 22; goto _again;
	tr31: ( savedCs_) = 23; goto _again;
	tr32: ( savedCs_) = 24; goto _again;
	tr33: ( savedCs_) = 25; goto _again;
	tr34: ( savedCs_) = 26; goto f10;
	tr39: ( savedCs_) = 26; goto f11;
	tr47: ( savedCs_) = 26; goto f12;
	tr3: ( savedCs_) = 27; goto _again;
	tr36: ( savedCs_) = 28; goto _again;
	tr37: ( savedCs_) = 29; goto _again;
	tr38: ( savedCs_) = 30; goto _again;
	tr4: ( savedCs_) = 31; goto _again;
	tr40: ( savedCs_) = 32; goto _again;
	tr41: ( savedCs_) = 33; goto _again;
	tr42: ( savedCs_) = 34; goto _again;
	tr43: ( savedCs_) = 35; goto _again;
	tr44: ( savedCs_) = 36; goto _again;
	tr45: ( savedCs_) = 37; goto _again;
	tr46: ( savedCs_) = 38; goto _again;
	tr5: ( savedCs_) = 39; goto _again;
	tr48: ( savedCs_) = 40; goto _again;
	tr49: ( savedCs_) = 41; goto _again;
	tr50: ( savedCs_) = 42; goto _again;
	tr51: ( savedCs_) = 43; goto _again;
	tr52: ( savedCs_) = 44; goto _again;
	tr53: ( savedCs_) = 45; goto _again;
	tr54: ( savedCs_) = 46; goto _again;
	tr55: ( savedCs_) = 47; goto _again;
	tr56: ( savedCs_) = 48; goto _again;
	tr57: ( savedCs_) = 49; goto _again;
	tr58: ( savedCs_) = 50; goto _again;
	tr59: ( savedCs_) = 51; goto f0;
	tr63: ( savedCs_) = 51; goto f3;
	tr62: ( savedCs_) = 52; goto f0;
	tr66: ( savedCs_) = 53; goto f7;
	tr68: ( savedCs_) = 53; goto f9;
	tr67: ( savedCs_) = 54; goto f8;
	tr69: ( savedCs_) = 55; goto f0;
	tr18: ( savedCs_) = 56; goto f1;
	tr22: ( savedCs_) = 56; goto f4;
	tr24: ( savedCs_) = 56; goto f6;
	tr60: ( savedCs_) = 56; goto f13;
	tr64: ( savedCs_) = 56; goto f15;

f3:
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f6:
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f12:
#line 176 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_notfound); }
	goto _again;
f10:
#line 177 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_deleted); }
	goto _again;
f11:
#line 187 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // This is unexpected error reply, just put ourself into error state.
  state_ = State::ERROR;
  currentErrorDescription_ = "ERROR reply received from server.";
  {( p_)++; goto _out; }
}
	goto _again;
f16:
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
	goto _again;
f5:
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
	goto _again;
f0:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f14:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
	goto _again;
f2:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
	goto _again;
f9:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f8:
#line 171 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setAppSpecificErrorCode(static_cast<uint32_t>(currentUInt_));
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f15:
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f4:
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f13:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f1:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f7:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ currentUInt_ = 0; }
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;

_again:
	if ( ( savedCs_) == 0 )
		goto _out;
	if ( ++( p_) != ( pe_) )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 422 "src/mcrouter/lib/network/McAsciiParser.rl"

}

//McMetaget reply.

#line 4827 "McAsciiParser-gen.cpp"
static const int mc_ascii_metaget_reply_start = 1;
static const int mc_ascii_metaget_reply_first_final = 107;
static const int mc_ascii_metaget_reply_error = 0;

static const int mc_ascii_metaget_reply_en_metaget_reply = 1;


#line 463 "src/mcrouter/lib/network/McAsciiParser.rl"

template<>
void McClientAsciiParser::consumeMessage<McReply, McOperation<mc_op_metaget>>(
    folly::IOBuf& buffer) {
  McReply& message = currentMessage_.get<McReply>();
  mc_msg_t* mcMsgT = const_cast<mc_msg_t*>(message.msg_.get());
  
#line 4843 "McAsciiParser-gen.cpp"
	{
	}

#line 4847 "McAsciiParser-gen.cpp"
	{
	if ( ( p_) == ( pe_) )
		goto _test_eof;
	if ( ( savedCs_) == 0 )
		goto _out;
_resume:
	switch ( ( savedCs_) ) {
case 1:
	switch( (*( p_)) ) {
		case 67: goto tr0;
		case 69: goto tr2;
		case 77: goto tr3;
		case 83: goto tr4;
	}
	goto tr1;
case 0:
	goto _out;
case 2:
	if ( (*( p_)) == 76 )
		goto tr5;
	goto tr1;
case 3:
	if ( (*( p_)) == 73 )
		goto tr6;
	goto tr1;
case 4:
	if ( (*( p_)) == 69 )
		goto tr7;
	goto tr1;
case 5:
	if ( (*( p_)) == 78 )
		goto tr8;
	goto tr1;
case 6:
	if ( (*( p_)) == 84 )
		goto tr9;
	goto tr1;
case 7:
	if ( (*( p_)) == 95 )
		goto tr10;
	goto tr1;
case 8:
	if ( (*( p_)) == 69 )
		goto tr11;
	goto tr1;
case 9:
	if ( (*( p_)) == 82 )
		goto tr12;
	goto tr1;
case 10:
	if ( (*( p_)) == 82 )
		goto tr13;
	goto tr1;
case 11:
	if ( (*( p_)) == 79 )
		goto tr14;
	goto tr1;
case 12:
	if ( (*( p_)) == 82 )
		goto tr15;
	goto tr1;
case 13:
	switch( (*( p_)) ) {
		case 10: goto tr17;
		case 13: goto tr18;
		case 32: goto tr19;
	}
	goto tr16;
case 14:
	switch( (*( p_)) ) {
		case 10: goto tr21;
		case 13: goto tr22;
	}
	goto tr20;
case 107:
	goto tr1;
case 15:
	if ( (*( p_)) == 10 )
		goto tr23;
	goto tr1;
case 16:
	switch( (*( p_)) ) {
		case 10: goto tr17;
		case 13: goto tr18;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr24;
	goto tr16;
case 17:
	switch( (*( p_)) ) {
		case 10: goto tr21;
		case 13: goto tr22;
		case 32: goto tr25;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr26;
	goto tr20;
case 18:
	switch( (*( p_)) ) {
		case 10: goto tr17;
		case 13: goto tr18;
		case 32: goto tr27;
	}
	goto tr16;
case 19:
	switch( (*( p_)) ) {
		case 10: goto tr17;
		case 13: goto tr18;
	}
	goto tr16;
case 20:
	switch( (*( p_)) ) {
		case 78: goto tr28;
		case 82: goto tr29;
	}
	goto tr1;
case 21:
	if ( (*( p_)) == 68 )
		goto tr30;
	goto tr1;
case 22:
	switch( (*( p_)) ) {
		case 10: goto tr31;
		case 13: goto tr32;
	}
	goto tr1;
case 23:
	switch( (*( p_)) ) {
		case 10: goto tr23;
		case 13: goto tr33;
	}
	goto tr1;
case 24:
	if ( (*( p_)) == 10 )
		goto tr31;
	goto tr1;
case 25:
	if ( (*( p_)) == 82 )
		goto tr34;
	goto tr1;
case 26:
	if ( (*( p_)) == 79 )
		goto tr35;
	goto tr1;
case 27:
	if ( (*( p_)) == 82 )
		goto tr36;
	goto tr1;
case 28:
	if ( (*( p_)) == 69 )
		goto tr37;
	goto tr1;
case 29:
	if ( (*( p_)) == 84 )
		goto tr38;
	goto tr1;
case 30:
	if ( (*( p_)) == 65 )
		goto tr39;
	goto tr1;
case 31:
	if ( (*( p_)) == 32 )
		goto tr40;
	goto tr1;
case 32:
	switch( (*( p_)) ) {
		case 32: goto tr42;
		case 127: goto tr1;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr1;
	goto tr41;
case 33:
	switch( (*( p_)) ) {
		case 32: goto tr43;
		case 127: goto tr1;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr1;
	goto tr41;
case 34:
	switch( (*( p_)) ) {
		case 32: goto tr43;
		case 97: goto tr44;
	}
	goto tr1;
case 35:
	if ( (*( p_)) == 103 )
		goto tr45;
	goto tr1;
case 36:
	if ( (*( p_)) == 101 )
		goto tr46;
	goto tr1;
case 37:
	if ( (*( p_)) == 58 )
		goto tr47;
	goto tr1;
case 38:
	switch( (*( p_)) ) {
		case 32: goto tr47;
		case 117: goto tr49;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr48;
	goto tr1;
case 39:
	if ( (*( p_)) == 59 )
		goto tr51;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr50;
	goto tr1;
case 40:
	switch( (*( p_)) ) {
		case 32: goto tr52;
		case 101: goto tr53;
	}
	goto tr1;
case 41:
	if ( (*( p_)) == 120 )
		goto tr54;
	goto tr1;
case 42:
	if ( (*( p_)) == 112 )
		goto tr55;
	goto tr1;
case 43:
	if ( (*( p_)) == 116 )
		goto tr56;
	goto tr1;
case 44:
	if ( (*( p_)) == 105 )
		goto tr57;
	goto tr1;
case 45:
	if ( (*( p_)) == 109 )
		goto tr58;
	goto tr1;
case 46:
	if ( (*( p_)) == 101 )
		goto tr59;
	goto tr1;
case 47:
	if ( (*( p_)) == 58 )
		goto tr60;
	goto tr1;
case 48:
	if ( (*( p_)) == 32 )
		goto tr60;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr61;
	goto tr1;
case 49:
	if ( (*( p_)) == 59 )
		goto tr63;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr62;
	goto tr1;
case 50:
	switch( (*( p_)) ) {
		case 32: goto tr64;
		case 102: goto tr65;
	}
	goto tr1;
case 51:
	if ( (*( p_)) == 114 )
		goto tr66;
	goto tr1;
case 52:
	if ( (*( p_)) == 111 )
		goto tr67;
	goto tr1;
case 53:
	if ( (*( p_)) == 109 )
		goto tr68;
	goto tr1;
case 54:
	if ( (*( p_)) == 58 )
		goto tr69;
	goto tr1;
case 55:
	switch( (*( p_)) ) {
		case 32: goto tr69;
		case 46: goto tr70;
		case 117: goto tr71;
	}
	if ( (*( p_)) < 65 ) {
		if ( 48 <= (*( p_)) && (*( p_)) <= 58 )
			goto tr70;
	} else if ( (*( p_)) > 70 ) {
		if ( 97 <= (*( p_)) && (*( p_)) <= 102 )
			goto tr70;
	} else
		goto tr70;
	goto tr1;
case 56:
	switch( (*( p_)) ) {
		case 46: goto tr70;
		case 59: goto tr72;
	}
	if ( (*( p_)) < 65 ) {
		if ( 48 <= (*( p_)) && (*( p_)) <= 58 )
			goto tr70;
	} else if ( (*( p_)) > 70 ) {
		if ( 97 <= (*( p_)) && (*( p_)) <= 102 )
			goto tr70;
	} else
		goto tr70;
	goto tr1;
case 57:
	switch( (*( p_)) ) {
		case 32: goto tr73;
		case 105: goto tr74;
	}
	goto tr1;
case 58:
	if ( (*( p_)) == 115 )
		goto tr75;
	goto tr1;
case 59:
	if ( (*( p_)) == 95 )
		goto tr76;
	goto tr1;
case 60:
	if ( (*( p_)) == 116 )
		goto tr77;
	goto tr1;
case 61:
	if ( (*( p_)) == 114 )
		goto tr78;
	goto tr1;
case 62:
	if ( (*( p_)) == 97 )
		goto tr79;
	goto tr1;
case 63:
	if ( (*( p_)) == 110 )
		goto tr80;
	goto tr1;
case 64:
	if ( (*( p_)) == 115 )
		goto tr81;
	goto tr1;
case 65:
	if ( (*( p_)) == 105 )
		goto tr82;
	goto tr1;
case 66:
	if ( (*( p_)) == 101 )
		goto tr83;
	goto tr1;
case 67:
	if ( (*( p_)) == 110 )
		goto tr84;
	goto tr1;
case 68:
	if ( (*( p_)) == 116 )
		goto tr85;
	goto tr1;
case 69:
	if ( (*( p_)) == 58 )
		goto tr86;
	goto tr1;
case 70:
	if ( (*( p_)) == 32 )
		goto tr86;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr87;
	goto tr1;
case 71:
	switch( (*( p_)) ) {
		case 10: goto tr88;
		case 13: goto tr89;
		case 32: goto tr90;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr91;
	goto tr1;
case 72:
	if ( (*( p_)) == 69 )
		goto tr92;
	goto tr1;
case 73:
	if ( (*( p_)) == 78 )
		goto tr28;
	goto tr1;
case 74:
	if ( (*( p_)) == 10 )
		goto tr93;
	goto tr1;
case 75:
	switch( (*( p_)) ) {
		case 10: goto tr93;
		case 13: goto tr94;
		case 32: goto tr95;
	}
	goto tr1;
case 76:
	if ( (*( p_)) == 110 )
		goto tr96;
	goto tr1;
case 77:
	if ( (*( p_)) == 107 )
		goto tr97;
	goto tr1;
case 78:
	if ( (*( p_)) == 110 )
		goto tr98;
	goto tr1;
case 79:
	if ( (*( p_)) == 111 )
		goto tr99;
	goto tr1;
case 80:
	if ( (*( p_)) == 119 )
		goto tr100;
	goto tr1;
case 81:
	if ( (*( p_)) == 110 )
		goto tr101;
	goto tr1;
case 82:
	if ( (*( p_)) == 59 )
		goto tr73;
	goto tr1;
case 83:
	if ( (*( p_)) == 110 )
		goto tr102;
	goto tr1;
case 84:
	if ( (*( p_)) == 107 )
		goto tr103;
	goto tr1;
case 85:
	if ( (*( p_)) == 110 )
		goto tr104;
	goto tr1;
case 86:
	if ( (*( p_)) == 111 )
		goto tr105;
	goto tr1;
case 87:
	if ( (*( p_)) == 119 )
		goto tr106;
	goto tr1;
case 88:
	if ( (*( p_)) == 110 )
		goto tr107;
	goto tr1;
case 89:
	if ( (*( p_)) == 59 )
		goto tr108;
	goto tr1;
case 90:
	if ( (*( p_)) == 69 )
		goto tr109;
	goto tr1;
case 91:
	if ( (*( p_)) == 82 )
		goto tr110;
	goto tr1;
case 92:
	if ( (*( p_)) == 86 )
		goto tr111;
	goto tr1;
case 93:
	if ( (*( p_)) == 69 )
		goto tr112;
	goto tr1;
case 94:
	if ( (*( p_)) == 82 )
		goto tr113;
	goto tr1;
case 95:
	if ( (*( p_)) == 95 )
		goto tr114;
	goto tr1;
case 96:
	if ( (*( p_)) == 69 )
		goto tr115;
	goto tr1;
case 97:
	if ( (*( p_)) == 82 )
		goto tr116;
	goto tr1;
case 98:
	if ( (*( p_)) == 82 )
		goto tr117;
	goto tr1;
case 99:
	if ( (*( p_)) == 79 )
		goto tr118;
	goto tr1;
case 100:
	if ( (*( p_)) == 82 )
		goto tr119;
	goto tr1;
case 101:
	switch( (*( p_)) ) {
		case 10: goto tr121;
		case 13: goto tr122;
		case 32: goto tr123;
	}
	goto tr120;
case 102:
	switch( (*( p_)) ) {
		case 10: goto tr125;
		case 13: goto tr126;
	}
	goto tr124;
case 103:
	switch( (*( p_)) ) {
		case 10: goto tr121;
		case 13: goto tr122;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr127;
	goto tr120;
case 104:
	switch( (*( p_)) ) {
		case 10: goto tr125;
		case 13: goto tr126;
		case 32: goto tr128;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr129;
	goto tr124;
case 105:
	switch( (*( p_)) ) {
		case 10: goto tr121;
		case 13: goto tr122;
		case 32: goto tr130;
	}
	goto tr120;
case 106:
	switch( (*( p_)) ) {
		case 10: goto tr121;
		case 13: goto tr122;
	}
	goto tr120;
	}

	tr1: ( savedCs_) = 0; goto _again;
	tr0: ( savedCs_) = 2; goto _again;
	tr5: ( savedCs_) = 3; goto _again;
	tr6: ( savedCs_) = 4; goto _again;
	tr7: ( savedCs_) = 5; goto _again;
	tr8: ( savedCs_) = 6; goto _again;
	tr9: ( savedCs_) = 7; goto _again;
	tr10: ( savedCs_) = 8; goto _again;
	tr11: ( savedCs_) = 9; goto _again;
	tr12: ( savedCs_) = 10; goto _again;
	tr13: ( savedCs_) = 11; goto _again;
	tr14: ( savedCs_) = 12; goto _again;
	tr15: ( savedCs_) = 13; goto _again;
	tr16: ( savedCs_) = 14; goto f1;
	tr20: ( savedCs_) = 14; goto f4;
	tr33: ( savedCs_) = 15; goto _again;
	tr18: ( savedCs_) = 15; goto f3;
	tr22: ( savedCs_) = 15; goto f6;
	tr122: ( savedCs_) = 15; goto f21;
	tr126: ( savedCs_) = 15; goto f23;
	tr19: ( savedCs_) = 16; goto f1;
	tr24: ( savedCs_) = 17; goto f8;
	tr26: ( savedCs_) = 17; goto f10;
	tr25: ( savedCs_) = 18; goto f9;
	tr27: ( savedCs_) = 19; goto f1;
	tr2: ( savedCs_) = 20; goto f0;
	tr28: ( savedCs_) = 21; goto _again;
	tr30: ( savedCs_) = 22; goto _again;
	tr31: ( savedCs_) = 23; goto f7;
	tr36: ( savedCs_) = 23; goto f11;
	tr32: ( savedCs_) = 24; goto _again;
	tr29: ( savedCs_) = 25; goto _again;
	tr34: ( savedCs_) = 26; goto _again;
	tr35: ( savedCs_) = 27; goto _again;
	tr3: ( savedCs_) = 28; goto f0;
	tr37: ( savedCs_) = 29; goto _again;
	tr38: ( savedCs_) = 30; goto _again;
	tr39: ( savedCs_) = 31; goto _again;
	tr42: ( savedCs_) = 32; goto _again;
	tr40: ( savedCs_) = 32; goto f12;
	tr41: ( savedCs_) = 33; goto _again;
	tr43: ( savedCs_) = 34; goto _again;
	tr44: ( savedCs_) = 35; goto _again;
	tr45: ( savedCs_) = 36; goto _again;
	tr46: ( savedCs_) = 37; goto _again;
	tr47: ( savedCs_) = 38; goto _again;
	tr48: ( savedCs_) = 39; goto f13;
	tr50: ( savedCs_) = 39; goto f14;
	tr52: ( savedCs_) = 40; goto _again;
	tr51: ( savedCs_) = 40; goto f15;
	tr108: ( savedCs_) = 40; goto f19;
	tr53: ( savedCs_) = 41; goto _again;
	tr54: ( savedCs_) = 42; goto _again;
	tr55: ( savedCs_) = 43; goto _again;
	tr56: ( savedCs_) = 44; goto _again;
	tr57: ( savedCs_) = 45; goto _again;
	tr58: ( savedCs_) = 46; goto _again;
	tr59: ( savedCs_) = 47; goto _again;
	tr60: ( savedCs_) = 48; goto _again;
	tr61: ( savedCs_) = 49; goto f13;
	tr62: ( savedCs_) = 49; goto f14;
	tr64: ( savedCs_) = 50; goto _again;
	tr63: ( savedCs_) = 50; goto f16;
	tr65: ( savedCs_) = 51; goto _again;
	tr66: ( savedCs_) = 52; goto _again;
	tr67: ( savedCs_) = 53; goto _again;
	tr68: ( savedCs_) = 54; goto _again;
	tr69: ( savedCs_) = 55; goto _again;
	tr70: ( savedCs_) = 56; goto f4;
	tr73: ( savedCs_) = 57; goto _again;
	tr72: ( savedCs_) = 57; goto f17;
	tr74: ( savedCs_) = 58; goto _again;
	tr75: ( savedCs_) = 59; goto _again;
	tr76: ( savedCs_) = 60; goto _again;
	tr77: ( savedCs_) = 61; goto _again;
	tr78: ( savedCs_) = 62; goto _again;
	tr79: ( savedCs_) = 63; goto _again;
	tr80: ( savedCs_) = 64; goto _again;
	tr81: ( savedCs_) = 65; goto _again;
	tr82: ( savedCs_) = 66; goto _again;
	tr83: ( savedCs_) = 67; goto _again;
	tr84: ( savedCs_) = 68; goto _again;
	tr85: ( savedCs_) = 69; goto _again;
	tr86: ( savedCs_) = 70; goto _again;
	tr87: ( savedCs_) = 71; goto f13;
	tr91: ( savedCs_) = 71; goto f14;
	tr93: ( savedCs_) = 72; goto _again;
	tr88: ( savedCs_) = 72; goto f18;
	tr92: ( savedCs_) = 73; goto _again;
	tr94: ( savedCs_) = 74; goto _again;
	tr89: ( savedCs_) = 74; goto f18;
	tr95: ( savedCs_) = 75; goto _again;
	tr90: ( savedCs_) = 75; goto f18;
	tr71: ( savedCs_) = 76; goto _again;
	tr96: ( savedCs_) = 77; goto _again;
	tr97: ( savedCs_) = 78; goto _again;
	tr98: ( savedCs_) = 79; goto _again;
	tr99: ( savedCs_) = 80; goto _again;
	tr100: ( savedCs_) = 81; goto _again;
	tr101: ( savedCs_) = 82; goto _again;
	tr49: ( savedCs_) = 83; goto _again;
	tr102: ( savedCs_) = 84; goto _again;
	tr103: ( savedCs_) = 85; goto _again;
	tr104: ( savedCs_) = 86; goto _again;
	tr105: ( savedCs_) = 87; goto _again;
	tr106: ( savedCs_) = 88; goto _again;
	tr107: ( savedCs_) = 89; goto _again;
	tr4: ( savedCs_) = 90; goto _again;
	tr109: ( savedCs_) = 91; goto _again;
	tr110: ( savedCs_) = 92; goto _again;
	tr111: ( savedCs_) = 93; goto _again;
	tr112: ( savedCs_) = 94; goto _again;
	tr113: ( savedCs_) = 95; goto _again;
	tr114: ( savedCs_) = 96; goto _again;
	tr115: ( savedCs_) = 97; goto _again;
	tr116: ( savedCs_) = 98; goto _again;
	tr117: ( savedCs_) = 99; goto _again;
	tr118: ( savedCs_) = 100; goto _again;
	tr119: ( savedCs_) = 101; goto _again;
	tr120: ( savedCs_) = 102; goto f1;
	tr124: ( savedCs_) = 102; goto f4;
	tr123: ( savedCs_) = 103; goto f1;
	tr127: ( savedCs_) = 104; goto f8;
	tr129: ( savedCs_) = 104; goto f10;
	tr128: ( savedCs_) = 105; goto f9;
	tr130: ( savedCs_) = 106; goto f1;
	tr17: ( savedCs_) = 107; goto f2;
	tr21: ( savedCs_) = 107; goto f5;
	tr23: ( savedCs_) = 107; goto f7;
	tr121: ( savedCs_) = 107; goto f20;
	tr125: ( savedCs_) = 107; goto f22;

f4:
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f7:
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f14:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
	goto _again;
f18:
#line 137 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setFlags(currentUInt_);
}
	goto _again;
f16:
#line 141 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setExptime(static_cast<uint32_t>(currentUInt_));
}
	goto _again;
f11:
#line 187 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // This is unexpected error reply, just put ourself into error state.
  state_ = State::ERROR;
  currentErrorDescription_ = "ERROR reply received from server.";
  {( p_)++; goto _out; }
}
	goto _again;
f23:
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
	goto _again;
f6:
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
	goto _again;
f15:
#line 430 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setNumber(static_cast<uint32_t>(currentUInt_));
}
	goto _again;
f19:
#line 433 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setNumber(static_cast<uint32_t>(-1));
}
	goto _again;
f17:
#line 437 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Max ip address length is INET6_ADDRSTRLEN - 1 chars.
  if (message.valueData_->computeChainDataLength() < INET6_ADDRSTRLEN) {
    char addr[INET6_ADDRSTRLEN] = {0};
    message.valueData_->coalesce();
    memcpy(addr, message.valueData_->data(), message.valueData_->length());
    mcMsgT->ipv = 0;
    if (strchr(addr, ':') == nullptr) {
      if (inet_pton(AF_INET, addr, &mcMsgT->ip_addr) > 0) {
        mcMsgT->ipv = 4;
      }
    } else {
      if (inet_pton(AF_INET6, addr, &mcMsgT->ip_addr) > 0) {
        mcMsgT->ipv = 6;
      }
    }
  }
}
	goto _again;
f12:
#line 455 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_found); }
	goto _again;
f0:
#line 459 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_notfound); }
	goto _again;
f1:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f21:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
	goto _again;
f3:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
	goto _again;
f13:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ currentUInt_ = 0; }
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
	goto _again;
f10:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f9:
#line 171 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setAppSpecificErrorCode(static_cast<uint32_t>(currentUInt_));
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f22:
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f5:
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f20:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f2:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f8:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ currentUInt_ = 0; }
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;

_again:
	if ( ( savedCs_) == 0 )
		goto _out;
	if ( ++( p_) != ( pe_) )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 473 "src/mcrouter/lib/network/McAsciiParser.rl"

}

// McFlushAll reply.

#line 5810 "McAsciiParser-gen.cpp"
static const int mc_ascii_flushall_reply_start = 1;
static const int mc_ascii_flushall_reply_first_final = 43;
static const int mc_ascii_flushall_reply_error = 0;

static const int mc_ascii_flushall_reply_en_flushall_reply = 1;


#line 485 "src/mcrouter/lib/network/McAsciiParser.rl"


template<>
void McClientAsciiParser::consumeMessage<McReply, McOperation<mc_op_flushall>>(
    folly::IOBuf& buffer) {
  McReply& message = currentMessage_.get<McReply>();
  
#line 5826 "McAsciiParser-gen.cpp"
	{
	}

#line 5830 "McAsciiParser-gen.cpp"
	{
	if ( ( p_) == ( pe_) )
		goto _test_eof;
	if ( ( savedCs_) == 0 )
		goto _out;
_resume:
	switch ( ( savedCs_) ) {
case 1:
	switch( (*( p_)) ) {
		case 67: goto tr0;
		case 69: goto tr2;
		case 79: goto tr3;
		case 83: goto tr4;
	}
	goto tr1;
case 0:
	goto _out;
case 2:
	if ( (*( p_)) == 76 )
		goto tr5;
	goto tr1;
case 3:
	if ( (*( p_)) == 73 )
		goto tr6;
	goto tr1;
case 4:
	if ( (*( p_)) == 69 )
		goto tr7;
	goto tr1;
case 5:
	if ( (*( p_)) == 78 )
		goto tr8;
	goto tr1;
case 6:
	if ( (*( p_)) == 84 )
		goto tr9;
	goto tr1;
case 7:
	if ( (*( p_)) == 95 )
		goto tr10;
	goto tr1;
case 8:
	if ( (*( p_)) == 69 )
		goto tr11;
	goto tr1;
case 9:
	if ( (*( p_)) == 82 )
		goto tr12;
	goto tr1;
case 10:
	if ( (*( p_)) == 82 )
		goto tr13;
	goto tr1;
case 11:
	if ( (*( p_)) == 79 )
		goto tr14;
	goto tr1;
case 12:
	if ( (*( p_)) == 82 )
		goto tr15;
	goto tr1;
case 13:
	switch( (*( p_)) ) {
		case 10: goto tr17;
		case 13: goto tr18;
		case 32: goto tr19;
	}
	goto tr16;
case 14:
	switch( (*( p_)) ) {
		case 10: goto tr21;
		case 13: goto tr22;
	}
	goto tr20;
case 43:
	goto tr1;
case 15:
	if ( (*( p_)) == 10 )
		goto tr23;
	goto tr1;
case 16:
	switch( (*( p_)) ) {
		case 10: goto tr17;
		case 13: goto tr18;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr24;
	goto tr16;
case 17:
	switch( (*( p_)) ) {
		case 10: goto tr21;
		case 13: goto tr22;
		case 32: goto tr25;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr26;
	goto tr20;
case 18:
	switch( (*( p_)) ) {
		case 10: goto tr17;
		case 13: goto tr18;
		case 32: goto tr27;
	}
	goto tr16;
case 19:
	switch( (*( p_)) ) {
		case 10: goto tr17;
		case 13: goto tr18;
	}
	goto tr16;
case 20:
	if ( (*( p_)) == 82 )
		goto tr28;
	goto tr1;
case 21:
	if ( (*( p_)) == 82 )
		goto tr29;
	goto tr1;
case 22:
	if ( (*( p_)) == 79 )
		goto tr30;
	goto tr1;
case 23:
	if ( (*( p_)) == 82 )
		goto tr31;
	goto tr1;
case 24:
	switch( (*( p_)) ) {
		case 10: goto tr23;
		case 13: goto tr32;
	}
	goto tr1;
case 25:
	if ( (*( p_)) == 75 )
		goto tr33;
	goto tr1;
case 26:
	if ( (*( p_)) == 69 )
		goto tr34;
	goto tr1;
case 27:
	if ( (*( p_)) == 82 )
		goto tr35;
	goto tr1;
case 28:
	if ( (*( p_)) == 86 )
		goto tr36;
	goto tr1;
case 29:
	if ( (*( p_)) == 69 )
		goto tr37;
	goto tr1;
case 30:
	if ( (*( p_)) == 82 )
		goto tr38;
	goto tr1;
case 31:
	if ( (*( p_)) == 95 )
		goto tr39;
	goto tr1;
case 32:
	if ( (*( p_)) == 69 )
		goto tr40;
	goto tr1;
case 33:
	if ( (*( p_)) == 82 )
		goto tr41;
	goto tr1;
case 34:
	if ( (*( p_)) == 82 )
		goto tr42;
	goto tr1;
case 35:
	if ( (*( p_)) == 79 )
		goto tr43;
	goto tr1;
case 36:
	if ( (*( p_)) == 82 )
		goto tr44;
	goto tr1;
case 37:
	switch( (*( p_)) ) {
		case 10: goto tr46;
		case 13: goto tr47;
		case 32: goto tr48;
	}
	goto tr45;
case 38:
	switch( (*( p_)) ) {
		case 10: goto tr50;
		case 13: goto tr51;
	}
	goto tr49;
case 39:
	switch( (*( p_)) ) {
		case 10: goto tr46;
		case 13: goto tr47;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr52;
	goto tr45;
case 40:
	switch( (*( p_)) ) {
		case 10: goto tr50;
		case 13: goto tr51;
		case 32: goto tr53;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr54;
	goto tr49;
case 41:
	switch( (*( p_)) ) {
		case 10: goto tr46;
		case 13: goto tr47;
		case 32: goto tr55;
	}
	goto tr45;
case 42:
	switch( (*( p_)) ) {
		case 10: goto tr46;
		case 13: goto tr47;
	}
	goto tr45;
	}

	tr1: ( savedCs_) = 0; goto _again;
	tr0: ( savedCs_) = 2; goto _again;
	tr5: ( savedCs_) = 3; goto _again;
	tr6: ( savedCs_) = 4; goto _again;
	tr7: ( savedCs_) = 5; goto _again;
	tr8: ( savedCs_) = 6; goto _again;
	tr9: ( savedCs_) = 7; goto _again;
	tr10: ( savedCs_) = 8; goto _again;
	tr11: ( savedCs_) = 9; goto _again;
	tr12: ( savedCs_) = 10; goto _again;
	tr13: ( savedCs_) = 11; goto _again;
	tr14: ( savedCs_) = 12; goto _again;
	tr15: ( savedCs_) = 13; goto _again;
	tr16: ( savedCs_) = 14; goto f1;
	tr20: ( savedCs_) = 14; goto f4;
	tr32: ( savedCs_) = 15; goto _again;
	tr18: ( savedCs_) = 15; goto f3;
	tr22: ( savedCs_) = 15; goto f6;
	tr47: ( savedCs_) = 15; goto f13;
	tr51: ( savedCs_) = 15; goto f15;
	tr19: ( savedCs_) = 16; goto f1;
	tr24: ( savedCs_) = 17; goto f8;
	tr26: ( savedCs_) = 17; goto f10;
	tr25: ( savedCs_) = 18; goto f9;
	tr27: ( savedCs_) = 19; goto f1;
	tr2: ( savedCs_) = 20; goto _again;
	tr28: ( savedCs_) = 21; goto _again;
	tr29: ( savedCs_) = 22; goto _again;
	tr30: ( savedCs_) = 23; goto _again;
	tr33: ( savedCs_) = 24; goto f0;
	tr31: ( savedCs_) = 24; goto f11;
	tr3: ( savedCs_) = 25; goto f0;
	tr4: ( savedCs_) = 26; goto _again;
	tr34: ( savedCs_) = 27; goto _again;
	tr35: ( savedCs_) = 28; goto _again;
	tr36: ( savedCs_) = 29; goto _again;
	tr37: ( savedCs_) = 30; goto _again;
	tr38: ( savedCs_) = 31; goto _again;
	tr39: ( savedCs_) = 32; goto _again;
	tr40: ( savedCs_) = 33; goto _again;
	tr41: ( savedCs_) = 34; goto _again;
	tr42: ( savedCs_) = 35; goto _again;
	tr43: ( savedCs_) = 36; goto _again;
	tr44: ( savedCs_) = 37; goto _again;
	tr45: ( savedCs_) = 38; goto f1;
	tr49: ( savedCs_) = 38; goto f4;
	tr48: ( savedCs_) = 39; goto f1;
	tr52: ( savedCs_) = 40; goto f8;
	tr54: ( savedCs_) = 40; goto f10;
	tr53: ( savedCs_) = 41; goto f9;
	tr55: ( savedCs_) = 42; goto f1;
	tr17: ( savedCs_) = 43; goto f2;
	tr21: ( savedCs_) = 43; goto f5;
	tr23: ( savedCs_) = 43; goto f7;
	tr46: ( savedCs_) = 43; goto f12;
	tr50: ( savedCs_) = 43; goto f14;

f4:
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f7:
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f11:
#line 187 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // This is unexpected error reply, just put ourself into error state.
  state_ = State::ERROR;
  currentErrorDescription_ = "ERROR reply received from server.";
  {( p_)++; goto _out; }
}
	goto _again;
f15:
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
	goto _again;
f6:
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
	goto _again;
f0:
#line 481 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_ok); }
	goto _again;
f1:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f13:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
	goto _again;
f3:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
	goto _again;
f10:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f9:
#line 171 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setAppSpecificErrorCode(static_cast<uint32_t>(currentUInt_));
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;
f14:
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f5:
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f12:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 198 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
                 if (message.appSpecificErrorCode() == SERVER_ERROR_BUSY) {
                   message.setResult(mc_res_busy);
                 } else {
                   message.setResult(mc_res_remote_error);
                 }
               }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f2:
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 207 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ message.setResult(mc_res_client_error); }
#line 91 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Message is complete, so exit the state machine and return to the caller.
  state_ = State::COMPLETE;
  {( p_)++; goto _out; }
}
	goto _again;
f8:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ currentUInt_ = 0; }
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
#line 72 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.valueData_.clear();
}
#line 59 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (message.valueData_) {
    // Append to the last IOBuf in chain.
    appendCurrentCharTo(buffer, *message.valueData_, p_);
  } else {
    // Emplace IOBuf.
    // TODO: allocate IOBuf and clone it in one operation.
    message.valueData_.emplace();
    initFirstCharIOBuf(buffer, message.valueData_.value(), p_);
  }
}
	goto _again;

_again:
	if ( ( savedCs_) == 0 )
		goto _out;
	if ( ++( p_) != ( pe_) )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 495 "src/mcrouter/lib/network/McAsciiParser.rl"

}

template<>
void McClientAsciiParser::initializeReplyParser<McOperation<mc_op_get>,
                                                McRequest>() {
  initializeCommon();
  savedCs_ = mc_ascii_get_reply_en_get_reply;
  errorCs_ = mc_ascii_get_reply_error;
  consumer_ =
      &McClientAsciiParser::consumeMessage<McReply, McOperation<mc_op_get>>;
}

template<>
void McClientAsciiParser::initializeReplyParser<McOperation<mc_op_gets>,
                                                McRequest>() {
  initializeCommon();
  savedCs_ = mc_ascii_gets_reply_en_gets_reply;
  errorCs_ = mc_ascii_gets_reply_error;
  consumer_ =
      &McClientAsciiParser::consumeMessage<McReply, McOperation<mc_op_gets>>;
}

template<>
void McClientAsciiParser::initializeReplyParser<McOperation<mc_op_lease_get>,
                                                McRequest>() {
  initializeCommon();
  savedCs_ = mc_ascii_lease_get_reply_en_lease_get_reply;
  errorCs_ = mc_ascii_lease_get_reply_error;
  consumer_ =
      &McClientAsciiParser::consumeMessage<McReply,
                                           McOperation<mc_op_lease_get>>;
}

template<>
void McClientAsciiParser::initializeReplyParser<McOperation<mc_op_set>,
                                                McRequest>() {
  initializeStorageReplyCommon();
}

template<>
void McClientAsciiParser::initializeReplyParser<McOperation<mc_op_add>,
                                                McRequest>() {
  initializeStorageReplyCommon();
}

template<>
void McClientAsciiParser::initializeReplyParser<McOperation<mc_op_replace>,
                                                McRequest>() {
  initializeStorageReplyCommon();
}

template<>
void McClientAsciiParser::initializeReplyParser<McOperation<mc_op_lease_set>,
                                                McRequest>() {
  initializeStorageReplyCommon();
}

template<>
void McClientAsciiParser::initializeReplyParser<McOperation<mc_op_cas>,
                                                McRequest>() {
  initializeStorageReplyCommon();
}

template<>
void McClientAsciiParser::initializeReplyParser<McOperation<mc_op_append>,
                                                McRequest>() {
  initializeStorageReplyCommon();
}

template<>
void McClientAsciiParser::initializeReplyParser<McOperation<mc_op_prepend>,
                                                McRequest>() {
  initializeStorageReplyCommon();
}

template<>
void McClientAsciiParser::initializeReplyParser<McOperation<mc_op_incr>,
                                                McRequest>() {
  initializeArithmReplyCommon();
}

template<>
void McClientAsciiParser::initializeReplyParser<McOperation<mc_op_decr>,
                                                McRequest>() {
  initializeArithmReplyCommon();
}

template<>
void McClientAsciiParser::initializeReplyParser<McOperation<mc_op_version>,
                                                McRequest>() {
  initializeCommon();
  savedCs_ = mc_ascii_version_reply_en_version_reply;
  errorCs_ = mc_ascii_version_reply_error;
  consumer_ =
      &McClientAsciiParser::consumeMessage<McReply, McOperation<mc_op_version>>;
}

template<>
void McClientAsciiParser::initializeReplyParser<McOperation<mc_op_delete>,
                                                McRequest>() {
  initializeCommon();
  savedCs_ = mc_ascii_delete_reply_en_delete_reply;
  errorCs_ = mc_ascii_delete_reply_error;
  consumer_ =
      &McClientAsciiParser::consumeMessage<McReply, McOperation<mc_op_delete>>;
}

template<>
void McClientAsciiParser::initializeReplyParser<McOperation<mc_op_metaget>,
                                                McRequest>() {
  initializeCommon();
  // Since mc_op_metaget has A LOT of specific fields, just create McMsgRef for
  // now.
  McReply& reply = currentMessage_.get<McReply>();
  reply.msg_ = createMcMsgRef();
  savedCs_ = mc_ascii_metaget_reply_en_metaget_reply;
  errorCs_ = mc_ascii_metaget_reply_error;
  consumer_ =
      &McClientAsciiParser::consumeMessage<McReply, McOperation<mc_op_metaget>>;
}

template<>
void McClientAsciiParser::initializeReplyParser<McOperation<mc_op_flushall>,
                                                McRequest>() {
  initializeCommon();
  savedCs_ = mc_ascii_flushall_reply_en_flushall_reply;
  errorCs_ = mc_ascii_flushall_reply_error;
  consumer_ = &McClientAsciiParser::consumeMessage<McReply,
                                                   McOperation<mc_op_flushall>>;
}

void McClientAsciiParser::initializeArithmReplyCommon() {
  initializeCommon();
  savedCs_ = mc_ascii_arithm_reply_en_arithm_reply;
  errorCs_ = mc_ascii_arithm_reply_error;
  consumer_ = &McClientAsciiParser::consumeArithmReplyCommon;
}

void McClientAsciiParser::initializeStorageReplyCommon() {
  initializeCommon();
  savedCs_ = mc_ascii_storage_reply_en_storage_reply;
  errorCs_ = mc_ascii_storage_reply_error;
  consumer_ = &McClientAsciiParser::consumeStorageReplyCommon;
}

void McClientAsciiParser::initializeCommon() {
  assert(state_ == State::UNINIT);

  currentUInt_ = 0;
  currentIOBuf_ = nullptr;
  remainingIOBufLength_ = 0;
  state_ = State::PARTIAL;

  currentMessage_.emplace<McReply>();
}

// Server parser.

// Get-like requests (get, gets, lease-get, metaget).


#line 6495 "McAsciiParser-gen.cpp"
static const int mc_ascii_get_like_req_body_start = 1;
static const int mc_ascii_get_like_req_body_first_final = 5;
static const int mc_ascii_get_like_req_body_error = 0;

static const int mc_ascii_get_like_req_body_en_req_body = 1;


#line 668 "src/mcrouter/lib/network/McAsciiParser.rl"


template <class Operation, class Request>
void McServerAsciiParser::consumeGetLike(folly::IOBuf& buffer) {
  Request& message = currentMessage_.get<Request>();
  
#line 6510 "McAsciiParser-gen.cpp"
	{
	}

#line 6514 "McAsciiParser-gen.cpp"
	{
	if ( ( p_) == ( pe_) )
		goto _test_eof;
	if ( ( savedCs_) == 0 )
		goto _out;
_resume:
	switch ( ( savedCs_) ) {
case 1:
	switch( (*( p_)) ) {
		case 32: goto tr1;
		case 127: goto tr2;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr2;
	goto tr0;
case 2:
	switch( (*( p_)) ) {
		case 10: goto tr4;
		case 13: goto tr5;
		case 32: goto tr6;
		case 127: goto tr2;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr2;
	goto tr3;
case 0:
	goto _out;
case 5:
	goto tr2;
case 3:
	if ( (*( p_)) == 10 )
		goto tr7;
	goto tr2;
case 4:
	switch( (*( p_)) ) {
		case 10: goto tr7;
		case 13: goto tr8;
		case 32: goto tr9;
		case 127: goto tr2;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr2;
	goto tr0;
	}

	tr2: ( savedCs_) = 0; goto _again;
	tr1: ( savedCs_) = 1; goto _again;
	tr3: ( savedCs_) = 2; goto _again;
	tr0: ( savedCs_) = 2; goto f0;
	tr8: ( savedCs_) = 3; goto _again;
	tr5: ( savedCs_) = 3; goto f2;
	tr9: ( savedCs_) = 4; goto _again;
	tr6: ( savedCs_) = 4; goto f2;
	tr4: ( savedCs_) = 5; goto f1;
	tr7: ( savedCs_) = 5; goto f3;

f3:
#line 84 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  callback_->multiOpEnd();
  finishReq();
  {( p_)++; goto _out; }
}
	goto _again;
f0:
#line 100 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentKey_.clear();
  keyPieceStart_ = p_;
}
	goto _again;
f2:
#line 105 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  appendKeyPiece(buffer, currentKey_, keyPieceStart_, p_);
  keyPieceStart_ = nullptr;
  currentKey_.coalesce();
}
#line 112 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setKey(std::move(currentKey_));
}
#line 660 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  callback_->onRequest(Operation(),
                       std::move(currentMessage_.get<Request>()));
}
	goto _again;
f1:
#line 105 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  appendKeyPiece(buffer, currentKey_, keyPieceStart_, p_);
  keyPieceStart_ = nullptr;
  currentKey_.coalesce();
}
#line 112 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setKey(std::move(currentKey_));
}
#line 660 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  callback_->onRequest(Operation(),
                       std::move(currentMessage_.get<Request>()));
}
#line 84 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  callback_->multiOpEnd();
  finishReq();
  {( p_)++; goto _out; }
}
	goto _again;

_again:
	if ( ( savedCs_) == 0 )
		goto _out;
	if ( ++( p_) != ( pe_) )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 677 "src/mcrouter/lib/network/McAsciiParser.rl"

}

template <class Operation, class Request>
void McServerAsciiParser::initGetLike() {
  savedCs_ = mc_ascii_get_like_req_body_en_req_body;
  errorCs_ = mc_ascii_get_like_req_body_error;
  state_ = State::PARTIAL;
  currentMessage_.emplace<Request>();
  consumer_ = &McServerAsciiParser::consumeGetLike<Operation, Request>;
}

// Set-like requests (set, add, replace, append, prepend).


#line 6652 "McAsciiParser-gen.cpp"
static const int mc_ascii_set_like_req_body_start = 1;
static const int mc_ascii_set_like_req_body_first_final = 22;
static const int mc_ascii_set_like_req_body_error = 0;

static const int mc_ascii_set_like_req_body_en_req_body = 1;


#line 705 "src/mcrouter/lib/network/McAsciiParser.rl"


template <class Operation, class Request>
void McServerAsciiParser::consumeSetLike(folly::IOBuf& buffer) {
  Request& message = currentMessage_.get<Request>();
  
#line 6667 "McAsciiParser-gen.cpp"
	{
	}

#line 6671 "McAsciiParser-gen.cpp"
	{
	if ( ( p_) == ( pe_) )
		goto _test_eof;
	if ( ( savedCs_) == 0 )
		goto _out;
_resume:
	switch ( ( savedCs_) ) {
case 1:
	switch( (*( p_)) ) {
		case 32: goto tr1;
		case 127: goto tr2;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr2;
	goto tr0;
case 2:
	switch( (*( p_)) ) {
		case 32: goto tr4;
		case 127: goto tr2;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr2;
	goto tr3;
case 0:
	goto _out;
case 3:
	if ( (*( p_)) == 32 )
		goto tr5;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr6;
	goto tr2;
case 4:
	if ( (*( p_)) == 32 )
		goto tr7;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr8;
	goto tr2;
case 5:
	switch( (*( p_)) ) {
		case 32: goto tr9;
		case 45: goto tr10;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr11;
	goto tr2;
case 6:
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr11;
	goto tr2;
case 7:
	if ( (*( p_)) == 32 )
		goto tr12;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr13;
	goto tr2;
case 8:
	if ( (*( p_)) == 32 )
		goto tr14;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr15;
	goto tr2;
case 9:
	switch( (*( p_)) ) {
		case 10: goto tr16;
		case 13: goto tr17;
		case 32: goto tr18;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr19;
	goto tr2;
case 10:
	switch( (*( p_)) ) {
		case 10: goto tr20;
		case 13: goto tr21;
	}
	goto tr2;
case 22:
	goto tr2;
case 11:
	if ( (*( p_)) == 10 )
		goto tr20;
	goto tr2;
case 12:
	if ( (*( p_)) == 10 )
		goto tr22;
	goto tr2;
case 13:
	switch( (*( p_)) ) {
		case 10: goto tr22;
		case 13: goto tr23;
		case 32: goto tr24;
		case 110: goto tr25;
	}
	goto tr2;
case 14:
	if ( (*( p_)) == 111 )
		goto tr26;
	goto tr2;
case 15:
	if ( (*( p_)) == 114 )
		goto tr27;
	goto tr2;
case 16:
	if ( (*( p_)) == 101 )
		goto tr28;
	goto tr2;
case 17:
	if ( (*( p_)) == 112 )
		goto tr29;
	goto tr2;
case 18:
	if ( (*( p_)) == 108 )
		goto tr30;
	goto tr2;
case 19:
	if ( (*( p_)) == 121 )
		goto tr31;
	goto tr2;
case 20:
	switch( (*( p_)) ) {
		case 10: goto tr32;
		case 13: goto tr33;
		case 32: goto tr34;
	}
	goto tr2;
case 21:
	switch( (*( p_)) ) {
		case 10: goto tr22;
		case 13: goto tr23;
		case 32: goto tr35;
	}
	goto tr2;
	}

	tr2: ( savedCs_) = 0; goto _again;
	tr1: ( savedCs_) = 1; goto _again;
	tr3: ( savedCs_) = 2; goto _again;
	tr0: ( savedCs_) = 2; goto f0;
	tr5: ( savedCs_) = 3; goto _again;
	tr4: ( savedCs_) = 3; goto f1;
	tr6: ( savedCs_) = 4; goto f2;
	tr8: ( savedCs_) = 4; goto f4;
	tr9: ( savedCs_) = 5; goto _again;
	tr7: ( savedCs_) = 5; goto f3;
	tr10: ( savedCs_) = 6; goto f5;
	tr11: ( savedCs_) = 7; goto f2;
	tr13: ( savedCs_) = 7; goto f4;
	tr14: ( savedCs_) = 8; goto _again;
	tr12: ( savedCs_) = 8; goto f6;
	tr15: ( savedCs_) = 9; goto f2;
	tr19: ( savedCs_) = 9; goto f4;
	tr16: ( savedCs_) = 10; goto f7;
	tr22: ( savedCs_) = 10; goto f10;
	tr32: ( savedCs_) = 10; goto f11;
	tr21: ( savedCs_) = 11; goto _again;
	tr23: ( savedCs_) = 12; goto _again;
	tr17: ( savedCs_) = 12; goto f8;
	tr33: ( savedCs_) = 12; goto f12;
	tr24: ( savedCs_) = 13; goto _again;
	tr18: ( savedCs_) = 13; goto f8;
	tr25: ( savedCs_) = 14; goto _again;
	tr26: ( savedCs_) = 15; goto _again;
	tr27: ( savedCs_) = 16; goto _again;
	tr28: ( savedCs_) = 17; goto _again;
	tr29: ( savedCs_) = 18; goto _again;
	tr30: ( savedCs_) = 19; goto _again;
	tr31: ( savedCs_) = 20; goto _again;
	tr35: ( savedCs_) = 21; goto _again;
	tr34: ( savedCs_) = 21; goto f12;
	tr20: ( savedCs_) = 22; goto f9;

f10:
#line 51 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (!readValue(buffer, message.valueData_)) {
    {( p_)++; goto _out; }
  }
}
	goto _again;
f12:
#line 77 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  noreply_ = true;
}
	goto _again;
f0:
#line 100 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentKey_.clear();
  keyPieceStart_ = p_;
}
	goto _again;
f4:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
	goto _again;
f5:
#line 132 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  negative_ = true;
}
	goto _again;
f3:
#line 137 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setFlags(currentUInt_);
}
	goto _again;
f6:
#line 145 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  auto value = static_cast<int32_t>(currentUInt_);
  message.setExptime(negative_ ? -value : value);
}
	goto _again;
f8:
#line 154 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  remainingIOBufLength_ = static_cast<size_t>(currentUInt_);
}
	goto _again;
f9:
#line 696 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
              callback_->onRequest(Operation(),
                                   std::move(currentMessage_.get<Request>()),
                                   noreply_);
              finishReq();
              {( p_)++; goto _out; }
            }
	goto _again;
f11:
#line 77 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  noreply_ = true;
}
#line 51 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (!readValue(buffer, message.valueData_)) {
    {( p_)++; goto _out; }
  }
}
	goto _again;
f1:
#line 105 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  appendKeyPiece(buffer, currentKey_, keyPieceStart_, p_);
  keyPieceStart_ = nullptr;
  currentKey_.coalesce();
}
#line 112 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setKey(std::move(currentKey_));
}
	goto _again;
f2:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ currentUInt_ = 0; }
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
	goto _again;
f7:
#line 154 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  remainingIOBufLength_ = static_cast<size_t>(currentUInt_);
}
#line 51 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (!readValue(buffer, message.valueData_)) {
    {( p_)++; goto _out; }
  }
}
	goto _again;

_again:
	if ( ( savedCs_) == 0 )
		goto _out;
	if ( ++( p_) != ( pe_) )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 714 "src/mcrouter/lib/network/McAsciiParser.rl"

}

template <class Operation, class Request>
void McServerAsciiParser::initSetLike() {
  savedCs_ = mc_ascii_set_like_req_body_en_req_body;
  errorCs_ = mc_ascii_set_like_req_body_error;
  state_ = State::PARTIAL;
  currentMessage_.emplace<Request>();
  consumer_ = &McServerAsciiParser::consumeSetLike<Operation, Request>;
}

// Cas request.


#line 6975 "McAsciiParser-gen.cpp"
static const int mc_ascii_cas_req_body_start = 1;
static const int mc_ascii_cas_req_body_first_final = 24;
static const int mc_ascii_cas_req_body_error = 0;

static const int mc_ascii_cas_req_body_en_req_body = 1;


#line 742 "src/mcrouter/lib/network/McAsciiParser.rl"


void McServerAsciiParser::consumeCas(folly::IOBuf& buffer) {
  McRequest& message = currentMessage_.get<McRequest>();
  
#line 6989 "McAsciiParser-gen.cpp"
	{
	}

#line 6993 "McAsciiParser-gen.cpp"
	{
	if ( ( p_) == ( pe_) )
		goto _test_eof;
	if ( ( savedCs_) == 0 )
		goto _out;
_resume:
	switch ( ( savedCs_) ) {
case 1:
	switch( (*( p_)) ) {
		case 32: goto tr1;
		case 127: goto tr2;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr2;
	goto tr0;
case 2:
	switch( (*( p_)) ) {
		case 32: goto tr4;
		case 127: goto tr2;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr2;
	goto tr3;
case 0:
	goto _out;
case 3:
	if ( (*( p_)) == 32 )
		goto tr5;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr6;
	goto tr2;
case 4:
	if ( (*( p_)) == 32 )
		goto tr7;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr8;
	goto tr2;
case 5:
	switch( (*( p_)) ) {
		case 32: goto tr9;
		case 45: goto tr10;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr11;
	goto tr2;
case 6:
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr11;
	goto tr2;
case 7:
	if ( (*( p_)) == 32 )
		goto tr12;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr13;
	goto tr2;
case 8:
	if ( (*( p_)) == 32 )
		goto tr14;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr15;
	goto tr2;
case 9:
	if ( (*( p_)) == 32 )
		goto tr16;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr17;
	goto tr2;
case 10:
	if ( (*( p_)) == 32 )
		goto tr18;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr19;
	goto tr2;
case 11:
	switch( (*( p_)) ) {
		case 10: goto tr20;
		case 13: goto tr21;
		case 32: goto tr22;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr23;
	goto tr2;
case 12:
	switch( (*( p_)) ) {
		case 10: goto tr24;
		case 13: goto tr25;
	}
	goto tr2;
case 24:
	goto tr2;
case 13:
	if ( (*( p_)) == 10 )
		goto tr24;
	goto tr2;
case 14:
	if ( (*( p_)) == 10 )
		goto tr26;
	goto tr2;
case 15:
	switch( (*( p_)) ) {
		case 10: goto tr26;
		case 13: goto tr27;
		case 32: goto tr28;
		case 110: goto tr29;
	}
	goto tr2;
case 16:
	if ( (*( p_)) == 111 )
		goto tr30;
	goto tr2;
case 17:
	if ( (*( p_)) == 114 )
		goto tr31;
	goto tr2;
case 18:
	if ( (*( p_)) == 101 )
		goto tr32;
	goto tr2;
case 19:
	if ( (*( p_)) == 112 )
		goto tr33;
	goto tr2;
case 20:
	if ( (*( p_)) == 108 )
		goto tr34;
	goto tr2;
case 21:
	if ( (*( p_)) == 121 )
		goto tr35;
	goto tr2;
case 22:
	switch( (*( p_)) ) {
		case 10: goto tr36;
		case 13: goto tr37;
		case 32: goto tr38;
	}
	goto tr2;
case 23:
	switch( (*( p_)) ) {
		case 10: goto tr26;
		case 13: goto tr27;
		case 32: goto tr39;
	}
	goto tr2;
	}

	tr2: ( savedCs_) = 0; goto _again;
	tr1: ( savedCs_) = 1; goto _again;
	tr3: ( savedCs_) = 2; goto _again;
	tr0: ( savedCs_) = 2; goto f0;
	tr5: ( savedCs_) = 3; goto _again;
	tr4: ( savedCs_) = 3; goto f1;
	tr6: ( savedCs_) = 4; goto f2;
	tr8: ( savedCs_) = 4; goto f4;
	tr9: ( savedCs_) = 5; goto _again;
	tr7: ( savedCs_) = 5; goto f3;
	tr10: ( savedCs_) = 6; goto f5;
	tr11: ( savedCs_) = 7; goto f2;
	tr13: ( savedCs_) = 7; goto f4;
	tr14: ( savedCs_) = 8; goto _again;
	tr12: ( savedCs_) = 8; goto f6;
	tr15: ( savedCs_) = 9; goto f2;
	tr17: ( savedCs_) = 9; goto f4;
	tr18: ( savedCs_) = 10; goto _again;
	tr16: ( savedCs_) = 10; goto f7;
	tr19: ( savedCs_) = 11; goto f2;
	tr23: ( savedCs_) = 11; goto f4;
	tr20: ( savedCs_) = 12; goto f8;
	tr26: ( savedCs_) = 12; goto f11;
	tr36: ( savedCs_) = 12; goto f12;
	tr25: ( savedCs_) = 13; goto _again;
	tr27: ( savedCs_) = 14; goto _again;
	tr21: ( savedCs_) = 14; goto f9;
	tr37: ( savedCs_) = 14; goto f13;
	tr28: ( savedCs_) = 15; goto _again;
	tr22: ( savedCs_) = 15; goto f9;
	tr29: ( savedCs_) = 16; goto _again;
	tr30: ( savedCs_) = 17; goto _again;
	tr31: ( savedCs_) = 18; goto _again;
	tr32: ( savedCs_) = 19; goto _again;
	tr33: ( savedCs_) = 20; goto _again;
	tr34: ( savedCs_) = 21; goto _again;
	tr35: ( savedCs_) = 22; goto _again;
	tr39: ( savedCs_) = 23; goto _again;
	tr38: ( savedCs_) = 23; goto f13;
	tr24: ( savedCs_) = 24; goto f10;

f11:
#line 51 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (!readValue(buffer, message.valueData_)) {
    {( p_)++; goto _out; }
  }
}
	goto _again;
f13:
#line 77 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  noreply_ = true;
}
	goto _again;
f0:
#line 100 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentKey_.clear();
  keyPieceStart_ = p_;
}
	goto _again;
f4:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
	goto _again;
f5:
#line 132 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  negative_ = true;
}
	goto _again;
f3:
#line 137 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setFlags(currentUInt_);
}
	goto _again;
f6:
#line 145 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  auto value = static_cast<int32_t>(currentUInt_);
  message.setExptime(negative_ ? -value : value);
}
	goto _again;
f7:
#line 154 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  remainingIOBufLength_ = static_cast<size_t>(currentUInt_);
}
	goto _again;
f9:
#line 158 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setCas(currentUInt_);
}
	goto _again;
f10:
#line 733 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
              callback_->onRequest(McOperation<mc_op_cas>(),
                                   std::move(currentMessage_.get<McRequest>()),
                                   noreply_);
              finishReq();
              {( p_)++; goto _out; }
            }
	goto _again;
f12:
#line 77 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  noreply_ = true;
}
#line 51 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (!readValue(buffer, message.valueData_)) {
    {( p_)++; goto _out; }
  }
}
	goto _again;
f1:
#line 105 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  appendKeyPiece(buffer, currentKey_, keyPieceStart_, p_);
  keyPieceStart_ = nullptr;
  currentKey_.coalesce();
}
#line 112 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setKey(std::move(currentKey_));
}
	goto _again;
f2:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ currentUInt_ = 0; }
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
	goto _again;
f8:
#line 158 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setCas(currentUInt_);
}
#line 51 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (!readValue(buffer, message.valueData_)) {
    {( p_)++; goto _out; }
  }
}
	goto _again;

_again:
	if ( ( savedCs_) == 0 )
		goto _out;
	if ( ++( p_) != ( pe_) )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 750 "src/mcrouter/lib/network/McAsciiParser.rl"

}

// Lease-set request.


#line 7310 "McAsciiParser-gen.cpp"
static const int mc_ascii_lease_set_req_body_start = 1;
static const int mc_ascii_lease_set_req_body_first_final = 24;
static const int mc_ascii_lease_set_req_body_error = 0;

static const int mc_ascii_lease_set_req_body_en_req_body = 1;


#line 770 "src/mcrouter/lib/network/McAsciiParser.rl"


void McServerAsciiParser::consumeLeaseSet(folly::IOBuf& buffer) {
  McRequest& message = currentMessage_.get<McRequest>();
  
#line 7324 "McAsciiParser-gen.cpp"
	{
	}

#line 7328 "McAsciiParser-gen.cpp"
	{
	if ( ( p_) == ( pe_) )
		goto _test_eof;
	if ( ( savedCs_) == 0 )
		goto _out;
_resume:
	switch ( ( savedCs_) ) {
case 1:
	switch( (*( p_)) ) {
		case 32: goto tr1;
		case 127: goto tr2;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr2;
	goto tr0;
case 2:
	switch( (*( p_)) ) {
		case 32: goto tr4;
		case 127: goto tr2;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr2;
	goto tr3;
case 0:
	goto _out;
case 3:
	if ( (*( p_)) == 32 )
		goto tr5;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr6;
	goto tr2;
case 4:
	if ( (*( p_)) == 32 )
		goto tr7;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr8;
	goto tr2;
case 5:
	if ( (*( p_)) == 32 )
		goto tr9;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr10;
	goto tr2;
case 6:
	if ( (*( p_)) == 32 )
		goto tr11;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr12;
	goto tr2;
case 7:
	switch( (*( p_)) ) {
		case 32: goto tr13;
		case 45: goto tr14;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr15;
	goto tr2;
case 8:
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr15;
	goto tr2;
case 9:
	if ( (*( p_)) == 32 )
		goto tr16;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr17;
	goto tr2;
case 10:
	if ( (*( p_)) == 32 )
		goto tr18;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr19;
	goto tr2;
case 11:
	switch( (*( p_)) ) {
		case 10: goto tr20;
		case 13: goto tr21;
		case 32: goto tr22;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr23;
	goto tr2;
case 12:
	switch( (*( p_)) ) {
		case 10: goto tr24;
		case 13: goto tr25;
	}
	goto tr2;
case 24:
	goto tr2;
case 13:
	if ( (*( p_)) == 10 )
		goto tr24;
	goto tr2;
case 14:
	if ( (*( p_)) == 10 )
		goto tr26;
	goto tr2;
case 15:
	switch( (*( p_)) ) {
		case 10: goto tr26;
		case 13: goto tr27;
		case 32: goto tr28;
		case 110: goto tr29;
	}
	goto tr2;
case 16:
	if ( (*( p_)) == 111 )
		goto tr30;
	goto tr2;
case 17:
	if ( (*( p_)) == 114 )
		goto tr31;
	goto tr2;
case 18:
	if ( (*( p_)) == 101 )
		goto tr32;
	goto tr2;
case 19:
	if ( (*( p_)) == 112 )
		goto tr33;
	goto tr2;
case 20:
	if ( (*( p_)) == 108 )
		goto tr34;
	goto tr2;
case 21:
	if ( (*( p_)) == 121 )
		goto tr35;
	goto tr2;
case 22:
	switch( (*( p_)) ) {
		case 10: goto tr36;
		case 13: goto tr37;
		case 32: goto tr38;
	}
	goto tr2;
case 23:
	switch( (*( p_)) ) {
		case 10: goto tr26;
		case 13: goto tr27;
		case 32: goto tr39;
	}
	goto tr2;
	}

	tr2: ( savedCs_) = 0; goto _again;
	tr1: ( savedCs_) = 1; goto _again;
	tr3: ( savedCs_) = 2; goto _again;
	tr0: ( savedCs_) = 2; goto f0;
	tr5: ( savedCs_) = 3; goto _again;
	tr4: ( savedCs_) = 3; goto f1;
	tr6: ( savedCs_) = 4; goto f2;
	tr8: ( savedCs_) = 4; goto f4;
	tr9: ( savedCs_) = 5; goto _again;
	tr7: ( savedCs_) = 5; goto f3;
	tr10: ( savedCs_) = 6; goto f2;
	tr12: ( savedCs_) = 6; goto f4;
	tr13: ( savedCs_) = 7; goto _again;
	tr11: ( savedCs_) = 7; goto f5;
	tr14: ( savedCs_) = 8; goto f6;
	tr15: ( savedCs_) = 9; goto f2;
	tr17: ( savedCs_) = 9; goto f4;
	tr18: ( savedCs_) = 10; goto _again;
	tr16: ( savedCs_) = 10; goto f7;
	tr19: ( savedCs_) = 11; goto f2;
	tr23: ( savedCs_) = 11; goto f4;
	tr20: ( savedCs_) = 12; goto f8;
	tr26: ( savedCs_) = 12; goto f11;
	tr36: ( savedCs_) = 12; goto f12;
	tr25: ( savedCs_) = 13; goto _again;
	tr27: ( savedCs_) = 14; goto _again;
	tr21: ( savedCs_) = 14; goto f9;
	tr37: ( savedCs_) = 14; goto f13;
	tr28: ( savedCs_) = 15; goto _again;
	tr22: ( savedCs_) = 15; goto f9;
	tr29: ( savedCs_) = 16; goto _again;
	tr30: ( savedCs_) = 17; goto _again;
	tr31: ( savedCs_) = 18; goto _again;
	tr32: ( savedCs_) = 19; goto _again;
	tr33: ( savedCs_) = 20; goto _again;
	tr34: ( savedCs_) = 21; goto _again;
	tr35: ( savedCs_) = 22; goto _again;
	tr39: ( savedCs_) = 23; goto _again;
	tr38: ( savedCs_) = 23; goto f13;
	tr24: ( savedCs_) = 24; goto f10;

f11:
#line 51 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (!readValue(buffer, message.valueData_)) {
    {( p_)++; goto _out; }
  }
}
	goto _again;
f13:
#line 77 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  noreply_ = true;
}
	goto _again;
f0:
#line 100 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentKey_.clear();
  keyPieceStart_ = p_;
}
	goto _again;
f4:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
	goto _again;
f6:
#line 132 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  negative_ = true;
}
	goto _again;
f5:
#line 137 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setFlags(currentUInt_);
}
	goto _again;
f7:
#line 145 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  auto value = static_cast<int32_t>(currentUInt_);
  message.setExptime(negative_ ? -value : value);
}
	goto _again;
f9:
#line 154 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  remainingIOBufLength_ = static_cast<size_t>(currentUInt_);
}
	goto _again;
f3:
#line 166 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // NOTE: we don't support -1 lease token.
  message.setLeaseToken(currentUInt_);
}
	goto _again;
f10:
#line 761 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
              callback_->onRequest(McOperation<mc_op_lease_set>(),
                                   std::move(currentMessage_.get<McRequest>()),
                                   noreply_);
              finishReq();
              {( p_)++; goto _out; }
            }
	goto _again;
f12:
#line 77 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  noreply_ = true;
}
#line 51 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (!readValue(buffer, message.valueData_)) {
    {( p_)++; goto _out; }
  }
}
	goto _again;
f1:
#line 105 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  appendKeyPiece(buffer, currentKey_, keyPieceStart_, p_);
  keyPieceStart_ = nullptr;
  currentKey_.coalesce();
}
#line 112 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setKey(std::move(currentKey_));
}
	goto _again;
f2:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ currentUInt_ = 0; }
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
	goto _again;
f8:
#line 154 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  remainingIOBufLength_ = static_cast<size_t>(currentUInt_);
}
#line 51 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  if (!readValue(buffer, message.valueData_)) {
    {( p_)++; goto _out; }
  }
}
	goto _again;

_again:
	if ( ( savedCs_) == 0 )
		goto _out;
	if ( ++( p_) != ( pe_) )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 778 "src/mcrouter/lib/network/McAsciiParser.rl"

}

// Delete request.


#line 7646 "McAsciiParser-gen.cpp"
static const int mc_ascii_delete_req_body_start = 1;
static const int mc_ascii_delete_req_body_first_final = 16;
static const int mc_ascii_delete_req_body_error = 0;

static const int mc_ascii_delete_req_body_en_req_body = 1;


#line 796 "src/mcrouter/lib/network/McAsciiParser.rl"


void McServerAsciiParser::consumeDelete(folly::IOBuf& buffer) {
  McRequest& message = currentMessage_.get<McRequest>();
  
#line 7660 "McAsciiParser-gen.cpp"
	{
	}

#line 7664 "McAsciiParser-gen.cpp"
	{
	if ( ( p_) == ( pe_) )
		goto _test_eof;
	if ( ( savedCs_) == 0 )
		goto _out;
_resume:
	switch ( ( savedCs_) ) {
case 1:
	switch( (*( p_)) ) {
		case 32: goto tr1;
		case 127: goto tr2;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr2;
	goto tr0;
case 2:
	switch( (*( p_)) ) {
		case 10: goto tr4;
		case 13: goto tr5;
		case 32: goto tr6;
		case 127: goto tr2;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr2;
	goto tr3;
case 0:
	goto _out;
case 16:
	goto tr2;
case 3:
	if ( (*( p_)) == 10 )
		goto tr7;
	goto tr2;
case 4:
	switch( (*( p_)) ) {
		case 10: goto tr7;
		case 13: goto tr8;
		case 32: goto tr9;
		case 45: goto tr10;
		case 110: goto tr12;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr11;
	goto tr2;
case 5:
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr11;
	goto tr2;
case 6:
	switch( (*( p_)) ) {
		case 10: goto tr13;
		case 13: goto tr14;
		case 32: goto tr15;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr16;
	goto tr2;
case 7:
	switch( (*( p_)) ) {
		case 10: goto tr7;
		case 13: goto tr8;
		case 32: goto tr17;
		case 110: goto tr12;
	}
	goto tr2;
case 8:
	if ( (*( p_)) == 111 )
		goto tr18;
	goto tr2;
case 9:
	if ( (*( p_)) == 114 )
		goto tr19;
	goto tr2;
case 10:
	if ( (*( p_)) == 101 )
		goto tr20;
	goto tr2;
case 11:
	if ( (*( p_)) == 112 )
		goto tr21;
	goto tr2;
case 12:
	if ( (*( p_)) == 108 )
		goto tr22;
	goto tr2;
case 13:
	if ( (*( p_)) == 121 )
		goto tr23;
	goto tr2;
case 14:
	switch( (*( p_)) ) {
		case 10: goto tr24;
		case 13: goto tr25;
		case 32: goto tr26;
	}
	goto tr2;
case 15:
	switch( (*( p_)) ) {
		case 10: goto tr7;
		case 13: goto tr8;
		case 32: goto tr27;
	}
	goto tr2;
	}

	tr2: ( savedCs_) = 0; goto _again;
	tr1: ( savedCs_) = 1; goto _again;
	tr3: ( savedCs_) = 2; goto _again;
	tr0: ( savedCs_) = 2; goto f0;
	tr8: ( savedCs_) = 3; goto _again;
	tr5: ( savedCs_) = 3; goto f2;
	tr14: ( savedCs_) = 3; goto f7;
	tr25: ( savedCs_) = 3; goto f10;
	tr9: ( savedCs_) = 4; goto _again;
	tr6: ( savedCs_) = 4; goto f2;
	tr10: ( savedCs_) = 5; goto f4;
	tr11: ( savedCs_) = 6; goto f5;
	tr16: ( savedCs_) = 6; goto f8;
	tr17: ( savedCs_) = 7; goto _again;
	tr15: ( savedCs_) = 7; goto f7;
	tr12: ( savedCs_) = 8; goto _again;
	tr18: ( savedCs_) = 9; goto _again;
	tr19: ( savedCs_) = 10; goto _again;
	tr20: ( savedCs_) = 11; goto _again;
	tr21: ( savedCs_) = 12; goto _again;
	tr22: ( savedCs_) = 13; goto _again;
	tr23: ( savedCs_) = 14; goto _again;
	tr27: ( savedCs_) = 15; goto _again;
	tr26: ( savedCs_) = 15; goto f10;
	tr4: ( savedCs_) = 16; goto f1;
	tr7: ( savedCs_) = 16; goto f3;
	tr13: ( savedCs_) = 16; goto f6;
	tr24: ( savedCs_) = 16; goto f9;

f10:
#line 77 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  noreply_ = true;
}
	goto _again;
f0:
#line 100 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentKey_.clear();
  keyPieceStart_ = p_;
}
	goto _again;
f8:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
	goto _again;
f4:
#line 132 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  negative_ = true;
}
	goto _again;
f7:
#line 145 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  auto value = static_cast<int32_t>(currentUInt_);
  message.setExptime(negative_ ? -value : value);
}
	goto _again;
f3:
#line 787 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
              callback_->onRequest(McOperation<mc_op_delete>(),
                                   std::move(currentMessage_.get<McRequest>()),
                                   noreply_);
              finishReq();
              {( p_)++; goto _out; }
            }
	goto _again;
f9:
#line 77 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  noreply_ = true;
}
#line 787 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
              callback_->onRequest(McOperation<mc_op_delete>(),
                                   std::move(currentMessage_.get<McRequest>()),
                                   noreply_);
              finishReq();
              {( p_)++; goto _out; }
            }
	goto _again;
f2:
#line 105 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  appendKeyPiece(buffer, currentKey_, keyPieceStart_, p_);
  keyPieceStart_ = nullptr;
  currentKey_.coalesce();
}
#line 112 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setKey(std::move(currentKey_));
}
	goto _again;
f5:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ currentUInt_ = 0; }
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
	goto _again;
f6:
#line 145 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  auto value = static_cast<int32_t>(currentUInt_);
  message.setExptime(negative_ ? -value : value);
}
#line 787 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
              callback_->onRequest(McOperation<mc_op_delete>(),
                                   std::move(currentMessage_.get<McRequest>()),
                                   noreply_);
              finishReq();
              {( p_)++; goto _out; }
            }
	goto _again;
f1:
#line 105 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  appendKeyPiece(buffer, currentKey_, keyPieceStart_, p_);
  keyPieceStart_ = nullptr;
  currentKey_.coalesce();
}
#line 112 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setKey(std::move(currentKey_));
}
#line 787 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
              callback_->onRequest(McOperation<mc_op_delete>(),
                                   std::move(currentMessage_.get<McRequest>()),
                                   noreply_);
              finishReq();
              {( p_)++; goto _out; }
            }
	goto _again;

_again:
	if ( ( savedCs_) == 0 )
		goto _out;
	if ( ++( p_) != ( pe_) )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 804 "src/mcrouter/lib/network/McAsciiParser.rl"

}

// Shutdown request.


#line 7927 "McAsciiParser-gen.cpp"
static const int mc_ascii_shutdown_req_body_start = 1;
static const int mc_ascii_shutdown_req_body_first_final = 6;
static const int mc_ascii_shutdown_req_body_error = 0;

static const int mc_ascii_shutdown_req_body_en_req_body = 1;


#line 823 "src/mcrouter/lib/network/McAsciiParser.rl"


void McServerAsciiParser::consumeShutdown(folly::IOBuf& buffer) {
  McRequest& message = currentMessage_.get<McRequest>();
  
#line 7941 "McAsciiParser-gen.cpp"
	{
	}

#line 7945 "McAsciiParser-gen.cpp"
	{
	if ( ( p_) == ( pe_) )
		goto _test_eof;
	if ( ( savedCs_) == 0 )
		goto _out;
_resume:
	switch ( ( savedCs_) ) {
case 1:
	switch( (*( p_)) ) {
		case 10: goto tr0;
		case 13: goto tr2;
		case 32: goto tr3;
	}
	goto tr1;
case 0:
	goto _out;
case 6:
	goto tr1;
case 2:
	if ( (*( p_)) == 10 )
		goto tr0;
	goto tr1;
case 3:
	switch( (*( p_)) ) {
		case 10: goto tr0;
		case 13: goto tr2;
		case 32: goto tr3;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr4;
	goto tr1;
case 4:
	switch( (*( p_)) ) {
		case 10: goto tr5;
		case 13: goto tr6;
		case 32: goto tr7;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr8;
	goto tr1;
case 5:
	switch( (*( p_)) ) {
		case 10: goto tr0;
		case 13: goto tr2;
		case 32: goto tr9;
	}
	goto tr1;
	}

	tr1: ( savedCs_) = 0; goto _again;
	tr2: ( savedCs_) = 2; goto _again;
	tr6: ( savedCs_) = 2; goto f3;
	tr3: ( savedCs_) = 3; goto _again;
	tr4: ( savedCs_) = 4; goto f1;
	tr8: ( savedCs_) = 4; goto f4;
	tr9: ( savedCs_) = 5; goto _again;
	tr7: ( savedCs_) = 5; goto f3;
	tr0: ( savedCs_) = 6; goto f0;
	tr5: ( savedCs_) = 6; goto f2;

f4:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
	goto _again;
f3:
#line 150 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setNumber(static_cast<uint32_t>(currentUInt_));
}
	goto _again;
f0:
#line 814 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
              callback_->onRequest(McOperation<mc_op_shutdown>(),
                                   std::move(currentMessage_.get<McRequest>()),
                                   noreply_);
              finishReq();
              {( p_)++; goto _out; }
            }
	goto _again;
f1:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ currentUInt_ = 0; }
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
	goto _again;
f2:
#line 150 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setNumber(static_cast<uint32_t>(currentUInt_));
}
#line 814 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
              callback_->onRequest(McOperation<mc_op_shutdown>(),
                                   std::move(currentMessage_.get<McRequest>()),
                                   noreply_);
              finishReq();
              {( p_)++; goto _out; }
            }
	goto _again;

_again:
	if ( ( savedCs_) == 0 )
		goto _out;
	if ( ++( p_) != ( pe_) )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 831 "src/mcrouter/lib/network/McAsciiParser.rl"

}

// Arithmetic request.


#line 8067 "McAsciiParser-gen.cpp"
static const int mc_ascii_arithmetic_req_body_start = 1;
static const int mc_ascii_arithmetic_req_body_first_final = 15;
static const int mc_ascii_arithmetic_req_body_error = 0;

static const int mc_ascii_arithmetic_req_body_en_req_body = 1;


#line 849 "src/mcrouter/lib/network/McAsciiParser.rl"


template <class Operation, class Request>
void McServerAsciiParser::consumeArithmetic(folly::IOBuf& buffer) {
  Request& message = currentMessage_.get<Request>();
  
#line 8082 "McAsciiParser-gen.cpp"
	{
	}

#line 8086 "McAsciiParser-gen.cpp"
	{
	if ( ( p_) == ( pe_) )
		goto _test_eof;
	if ( ( savedCs_) == 0 )
		goto _out;
_resume:
	switch ( ( savedCs_) ) {
case 1:
	switch( (*( p_)) ) {
		case 32: goto tr1;
		case 127: goto tr2;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr2;
	goto tr0;
case 2:
	switch( (*( p_)) ) {
		case 32: goto tr4;
		case 127: goto tr2;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr2;
	goto tr3;
case 0:
	goto _out;
case 3:
	if ( (*( p_)) == 32 )
		goto tr5;
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr6;
	goto tr2;
case 4:
	switch( (*( p_)) ) {
		case 10: goto tr7;
		case 13: goto tr8;
		case 32: goto tr9;
		case 110: goto tr11;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr10;
	goto tr2;
case 15:
	goto tr2;
case 5:
	if ( (*( p_)) == 10 )
		goto tr12;
	goto tr2;
case 6:
	switch( (*( p_)) ) {
		case 10: goto tr12;
		case 13: goto tr13;
		case 32: goto tr14;
		case 110: goto tr15;
	}
	goto tr2;
case 7:
	if ( (*( p_)) == 111 )
		goto tr16;
	goto tr2;
case 8:
	if ( (*( p_)) == 114 )
		goto tr17;
	goto tr2;
case 9:
	if ( (*( p_)) == 101 )
		goto tr18;
	goto tr2;
case 10:
	if ( (*( p_)) == 112 )
		goto tr19;
	goto tr2;
case 11:
	if ( (*( p_)) == 108 )
		goto tr20;
	goto tr2;
case 12:
	if ( (*( p_)) == 121 )
		goto tr21;
	goto tr2;
case 13:
	switch( (*( p_)) ) {
		case 10: goto tr22;
		case 13: goto tr23;
		case 32: goto tr24;
	}
	goto tr2;
case 14:
	switch( (*( p_)) ) {
		case 10: goto tr12;
		case 13: goto tr13;
		case 32: goto tr25;
	}
	goto tr2;
	}

	tr2: ( savedCs_) = 0; goto _again;
	tr1: ( savedCs_) = 1; goto _again;
	tr3: ( savedCs_) = 2; goto _again;
	tr0: ( savedCs_) = 2; goto f0;
	tr5: ( savedCs_) = 3; goto _again;
	tr4: ( savedCs_) = 3; goto f1;
	tr6: ( savedCs_) = 4; goto f2;
	tr10: ( savedCs_) = 4; goto f5;
	tr13: ( savedCs_) = 5; goto _again;
	tr8: ( savedCs_) = 5; goto f4;
	tr23: ( savedCs_) = 5; goto f8;
	tr14: ( savedCs_) = 6; goto _again;
	tr9: ( savedCs_) = 6; goto f4;
	tr15: ( savedCs_) = 7; goto _again;
	tr11: ( savedCs_) = 7; goto f4;
	tr16: ( savedCs_) = 8; goto _again;
	tr17: ( savedCs_) = 9; goto _again;
	tr18: ( savedCs_) = 10; goto _again;
	tr19: ( savedCs_) = 11; goto _again;
	tr20: ( savedCs_) = 12; goto _again;
	tr21: ( savedCs_) = 13; goto _again;
	tr25: ( savedCs_) = 14; goto _again;
	tr24: ( savedCs_) = 14; goto f8;
	tr7: ( savedCs_) = 15; goto f3;
	tr12: ( savedCs_) = 15; goto f6;
	tr22: ( savedCs_) = 15; goto f7;

f8:
#line 77 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  noreply_ = true;
}
	goto _again;
f0:
#line 100 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentKey_.clear();
  keyPieceStart_ = p_;
}
	goto _again;
f5:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
	goto _again;
f4:
#line 162 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setDelta(currentUInt_);
}
	goto _again;
f6:
#line 840 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
              callback_->onRequest(Operation(),
                                   std::move(currentMessage_.get<Request>()),
                                   noreply_);
              finishReq();
              {( p_)++; goto _out; }
            }
	goto _again;
f7:
#line 77 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  noreply_ = true;
}
#line 840 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
              callback_->onRequest(Operation(),
                                   std::move(currentMessage_.get<Request>()),
                                   noreply_);
              finishReq();
              {( p_)++; goto _out; }
            }
	goto _again;
f1:
#line 105 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  appendKeyPiece(buffer, currentKey_, keyPieceStart_, p_);
  keyPieceStart_ = nullptr;
  currentKey_.coalesce();
}
#line 112 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setKey(std::move(currentKey_));
}
	goto _again;
f2:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ currentUInt_ = 0; }
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
	goto _again;
f3:
#line 162 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setDelta(currentUInt_);
}
#line 840 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
              callback_->onRequest(Operation(),
                                   std::move(currentMessage_.get<Request>()),
                                   noreply_);
              finishReq();
              {( p_)++; goto _out; }
            }
	goto _again;

_again:
	if ( ( savedCs_) == 0 )
		goto _out;
	if ( ++( p_) != ( pe_) )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 858 "src/mcrouter/lib/network/McAsciiParser.rl"

}

template <class Operation, class Request>
void McServerAsciiParser::initArithmetic() {
  savedCs_ = mc_ascii_arithmetic_req_body_en_req_body;
  errorCs_ = mc_ascii_arithmetic_req_body_error;
  state_ = State::PARTIAL;
  currentMessage_.emplace<Request>();
  consumer_ = &McServerAsciiParser::consumeArithmetic<Operation, Request>;
}

// Stats request.


#line 8318 "McAsciiParser-gen.cpp"
static const int mc_ascii_stats_req_body_start = 1;
static const int mc_ascii_stats_req_body_first_final = 5;
static const int mc_ascii_stats_req_body_error = 0;

static const int mc_ascii_stats_req_body_en_req_body = 1;


#line 885 "src/mcrouter/lib/network/McAsciiParser.rl"


void McServerAsciiParser::consumeStats(folly::IOBuf& buffer) {
  McRequest& message = currentMessage_.get<McRequest>();
  
#line 8332 "McAsciiParser-gen.cpp"
	{
	}

#line 8336 "McAsciiParser-gen.cpp"
	{
	if ( ( p_) == ( pe_) )
		goto _test_eof;
	if ( ( savedCs_) == 0 )
		goto _out;
_resume:
	switch ( ( savedCs_) ) {
case 1:
	switch( (*( p_)) ) {
		case 10: goto tr0;
		case 13: goto tr2;
		case 32: goto tr3;
	}
	goto tr1;
case 0:
	goto _out;
case 5:
	goto tr1;
case 2:
	if ( (*( p_)) == 10 )
		goto tr0;
	goto tr1;
case 3:
	if ( 32 <= (*( p_)) && (*( p_)) <= 126 )
		goto tr4;
	goto tr1;
case 4:
	switch( (*( p_)) ) {
		case 10: goto tr5;
		case 13: goto tr6;
	}
	if ( 32 <= (*( p_)) && (*( p_)) <= 126 )
		goto tr7;
	goto tr1;
	}

	tr1: ( savedCs_) = 0; goto _again;
	tr2: ( savedCs_) = 2; goto _again;
	tr6: ( savedCs_) = 2; goto f3;
	tr3: ( savedCs_) = 3; goto _again;
	tr7: ( savedCs_) = 4; goto _again;
	tr4: ( savedCs_) = 4; goto f1;
	tr0: ( savedCs_) = 5; goto f0;
	tr5: ( savedCs_) = 5; goto f2;

f1:
#line 100 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentKey_.clear();
  keyPieceStart_ = p_;
}
	goto _again;
f0:
#line 876 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
              callback_->onRequest(McOperation<mc_op_stats>(),
                                   std::move(currentMessage_.get<McRequest>()),
                                   noreply_);
              finishReq();
              {( p_)++; goto _out; }
            }
	goto _again;
f3:
#line 105 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  appendKeyPiece(buffer, currentKey_, keyPieceStart_, p_);
  keyPieceStart_ = nullptr;
  currentKey_.coalesce();
}
#line 116 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Trim string.
  while (currentKey_.length() > 0 && isspace(*currentKey_.data())) {
    currentKey_.trimStart(1);
  }
  while (currentKey_.length() > 0 && isspace(*(currentKey_.tail() - 1))) {
    currentKey_.trimEnd(1);
  }
  message.setKey(std::move(currentKey_));
}
	goto _again;
f2:
#line 105 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  appendKeyPiece(buffer, currentKey_, keyPieceStart_, p_);
  keyPieceStart_ = nullptr;
  currentKey_.coalesce();
}
#line 116 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Trim string.
  while (currentKey_.length() > 0 && isspace(*currentKey_.data())) {
    currentKey_.trimStart(1);
  }
  while (currentKey_.length() > 0 && isspace(*(currentKey_.tail() - 1))) {
    currentKey_.trimEnd(1);
  }
  message.setKey(std::move(currentKey_));
}
#line 876 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
              callback_->onRequest(McOperation<mc_op_stats>(),
                                   std::move(currentMessage_.get<McRequest>()),
                                   noreply_);
              finishReq();
              {( p_)++; goto _out; }
            }
	goto _again;

_again:
	if ( ( savedCs_) == 0 )
		goto _out;
	if ( ++( p_) != ( pe_) )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 893 "src/mcrouter/lib/network/McAsciiParser.rl"

}

// Exec request.


#line 8462 "McAsciiParser-gen.cpp"
static const int mc_ascii_exec_req_body_start = 1;
static const int mc_ascii_exec_req_body_first_final = 4;
static const int mc_ascii_exec_req_body_error = 0;

static const int mc_ascii_exec_req_body_en_req_body = 1;


#line 911 "src/mcrouter/lib/network/McAsciiParser.rl"


void McServerAsciiParser::consumeExec(folly::IOBuf& buffer) {
  McRequest& message = currentMessage_.get<McRequest>();
  
#line 8476 "McAsciiParser-gen.cpp"
	{
	}

#line 8480 "McAsciiParser-gen.cpp"
	{
	if ( ( p_) == ( pe_) )
		goto _test_eof;
	if ( ( savedCs_) == 0 )
		goto _out;
_resume:
	switch ( ( savedCs_) ) {
case 1:
	if ( 32 <= (*( p_)) && (*( p_)) <= 126 )
		goto tr0;
	goto tr1;
case 0:
	goto _out;
case 2:
	switch( (*( p_)) ) {
		case 10: goto tr2;
		case 13: goto tr3;
	}
	if ( 32 <= (*( p_)) && (*( p_)) <= 126 )
		goto tr4;
	goto tr1;
case 4:
	goto tr1;
case 3:
	if ( (*( p_)) == 10 )
		goto tr5;
	goto tr1;
	}

	tr1: ( savedCs_) = 0; goto _again;
	tr4: ( savedCs_) = 2; goto _again;
	tr0: ( savedCs_) = 2; goto f0;
	tr3: ( savedCs_) = 3; goto f2;
	tr2: ( savedCs_) = 4; goto f1;
	tr5: ( savedCs_) = 4; goto f3;

f0:
#line 100 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentKey_.clear();
  keyPieceStart_ = p_;
}
	goto _again;
f3:
#line 902 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
              callback_->onRequest(McOperation<mc_op_exec>(),
                                   std::move(currentMessage_.get<McRequest>()),
                                   noreply_);
              finishReq();
              {( p_)++; goto _out; }
            }
	goto _again;
f2:
#line 105 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  appendKeyPiece(buffer, currentKey_, keyPieceStart_, p_);
  keyPieceStart_ = nullptr;
  currentKey_.coalesce();
}
#line 116 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Trim string.
  while (currentKey_.length() > 0 && isspace(*currentKey_.data())) {
    currentKey_.trimStart(1);
  }
  while (currentKey_.length() > 0 && isspace(*(currentKey_.tail() - 1))) {
    currentKey_.trimEnd(1);
  }
  message.setKey(std::move(currentKey_));
}
	goto _again;
f1:
#line 105 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  appendKeyPiece(buffer, currentKey_, keyPieceStart_, p_);
  keyPieceStart_ = nullptr;
  currentKey_.coalesce();
}
#line 116 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  // Trim string.
  while (currentKey_.length() > 0 && isspace(*currentKey_.data())) {
    currentKey_.trimStart(1);
  }
  while (currentKey_.length() > 0 && isspace(*(currentKey_.tail() - 1))) {
    currentKey_.trimEnd(1);
  }
  message.setKey(std::move(currentKey_));
}
#line 902 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
              callback_->onRequest(McOperation<mc_op_exec>(),
                                   std::move(currentMessage_.get<McRequest>()),
                                   noreply_);
              finishReq();
              {( p_)++; goto _out; }
            }
	goto _again;

_again:
	if ( ( savedCs_) == 0 )
		goto _out;
	if ( ++( p_) != ( pe_) )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 919 "src/mcrouter/lib/network/McAsciiParser.rl"

}

// Flush_regex request.


#line 8597 "McAsciiParser-gen.cpp"
static const int mc_ascii_flush_re_req_body_start = 1;
static const int mc_ascii_flush_re_req_body_first_final = 5;
static const int mc_ascii_flush_re_req_body_error = 0;

static const int mc_ascii_flush_re_req_body_en_req_body = 1;


#line 937 "src/mcrouter/lib/network/McAsciiParser.rl"


void McServerAsciiParser::consumeFlushRe(folly::IOBuf& buffer) {
  McRequest& message = currentMessage_.get<McRequest>();
  
#line 8611 "McAsciiParser-gen.cpp"
	{
	}

#line 8615 "McAsciiParser-gen.cpp"
	{
	if ( ( p_) == ( pe_) )
		goto _test_eof;
	if ( ( savedCs_) == 0 )
		goto _out;
_resume:
	switch ( ( savedCs_) ) {
case 1:
	switch( (*( p_)) ) {
		case 32: goto tr1;
		case 127: goto tr2;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr2;
	goto tr0;
case 2:
	switch( (*( p_)) ) {
		case 10: goto tr4;
		case 13: goto tr5;
		case 32: goto tr6;
		case 127: goto tr2;
	}
	if ( 0 <= (*( p_)) && (*( p_)) <= 31 )
		goto tr2;
	goto tr3;
case 0:
	goto _out;
case 5:
	goto tr2;
case 3:
	if ( (*( p_)) == 10 )
		goto tr7;
	goto tr2;
case 4:
	switch( (*( p_)) ) {
		case 10: goto tr7;
		case 13: goto tr8;
		case 32: goto tr9;
	}
	goto tr2;
	}

	tr2: ( savedCs_) = 0; goto _again;
	tr1: ( savedCs_) = 1; goto _again;
	tr3: ( savedCs_) = 2; goto _again;
	tr0: ( savedCs_) = 2; goto f0;
	tr8: ( savedCs_) = 3; goto _again;
	tr5: ( savedCs_) = 3; goto f2;
	tr9: ( savedCs_) = 4; goto _again;
	tr6: ( savedCs_) = 4; goto f2;
	tr4: ( savedCs_) = 5; goto f1;
	tr7: ( savedCs_) = 5; goto f3;

f0:
#line 100 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentKey_.clear();
  keyPieceStart_ = p_;
}
	goto _again;
f3:
#line 928 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
              callback_->onRequest(McOperation<mc_op_flushre>(),
                                   std::move(currentMessage_.get<McRequest>()),
                                   noreply_);
              finishReq();
              {( p_)++; goto _out; }
            }
	goto _again;
f2:
#line 105 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  appendKeyPiece(buffer, currentKey_, keyPieceStart_, p_);
  keyPieceStart_ = nullptr;
  currentKey_.coalesce();
}
#line 112 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setKey(std::move(currentKey_));
}
	goto _again;
f1:
#line 105 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  appendKeyPiece(buffer, currentKey_, keyPieceStart_, p_);
  keyPieceStart_ = nullptr;
  currentKey_.coalesce();
}
#line 112 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setKey(std::move(currentKey_));
}
#line 928 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
              callback_->onRequest(McOperation<mc_op_flushre>(),
                                   std::move(currentMessage_.get<McRequest>()),
                                   noreply_);
              finishReq();
              {( p_)++; goto _out; }
            }
	goto _again;

_again:
	if ( ( savedCs_) == 0 )
		goto _out;
	if ( ++( p_) != ( pe_) )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 945 "src/mcrouter/lib/network/McAsciiParser.rl"

}

// Flush_all request.


#line 8735 "McAsciiParser-gen.cpp"
static const int mc_ascii_flush_all_req_body_start = 1;
static const int mc_ascii_flush_all_req_body_first_final = 5;
static const int mc_ascii_flush_all_req_body_error = 0;

static const int mc_ascii_flush_all_req_body_en_req_body = 1;


#line 963 "src/mcrouter/lib/network/McAsciiParser.rl"


void McServerAsciiParser::consumeFlushAll(folly::IOBuf& buffer) {
  McRequest& message = currentMessage_.get<McRequest>();
  
#line 8749 "McAsciiParser-gen.cpp"
	{
	}

#line 8753 "McAsciiParser-gen.cpp"
	{
	if ( ( p_) == ( pe_) )
		goto _test_eof;
	if ( ( savedCs_) == 0 )
		goto _out;
_resume:
	switch ( ( savedCs_) ) {
case 1:
	switch( (*( p_)) ) {
		case 10: goto tr0;
		case 13: goto tr2;
		case 32: goto tr3;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr4;
	goto tr1;
case 0:
	goto _out;
case 5:
	goto tr1;
case 2:
	if ( (*( p_)) == 10 )
		goto tr0;
	goto tr1;
case 3:
	switch( (*( p_)) ) {
		case 10: goto tr5;
		case 13: goto tr6;
		case 32: goto tr7;
	}
	if ( 48 <= (*( p_)) && (*( p_)) <= 57 )
		goto tr8;
	goto tr1;
case 4:
	switch( (*( p_)) ) {
		case 10: goto tr0;
		case 13: goto tr2;
		case 32: goto tr9;
	}
	goto tr1;
	}

	tr1: ( savedCs_) = 0; goto _again;
	tr3: ( savedCs_) = 1; goto _again;
	tr2: ( savedCs_) = 2; goto _again;
	tr6: ( savedCs_) = 2; goto f3;
	tr4: ( savedCs_) = 3; goto f1;
	tr8: ( savedCs_) = 3; goto f4;
	tr9: ( savedCs_) = 4; goto _again;
	tr7: ( savedCs_) = 4; goto f3;
	tr0: ( savedCs_) = 5; goto f0;
	tr5: ( savedCs_) = 5; goto f2;

f4:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
	goto _again;
f3:
#line 150 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setNumber(static_cast<uint32_t>(currentUInt_));
}
	goto _again;
f0:
#line 954 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
              callback_->onRequest(McOperation<mc_op_flushall>(),
                                   std::move(currentMessage_.get<McRequest>()),
                                   noreply_);
              finishReq();
              {( p_)++; goto _out; }
            }
	goto _again;
f1:
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{ currentUInt_ = 0; }
#line 128 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  currentUInt_ = currentUInt_ * 10 + ((*( p_)) - '0');
}
	goto _again;
f2:
#line 150 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  message.setNumber(static_cast<uint32_t>(currentUInt_));
}
#line 954 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
              callback_->onRequest(McOperation<mc_op_flushall>(),
                                   std::move(currentMessage_.get<McRequest>()),
                                   noreply_);
              finishReq();
              {( p_)++; goto _out; }
            }
	goto _again;

_again:
	if ( ( savedCs_) == 0 )
		goto _out;
	if ( ++( p_) != ( pe_) )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 971 "src/mcrouter/lib/network/McAsciiParser.rl"

}

// Operation keyword parser.


#line 8868 "McAsciiParser-gen.cpp"
static const int mc_ascii_req_op_type_start = 1;
static const int mc_ascii_req_op_type_first_final = 106;
static const int mc_ascii_req_op_type_error = 0;

static const int mc_ascii_req_op_type_en_command = 1;


#line 1131 "src/mcrouter/lib/network/McAsciiParser.rl"


void McServerAsciiParser::opTypeConsumer(folly::IOBuf& buffer) {
  
#line 8881 "McAsciiParser-gen.cpp"
	{
	}

#line 8885 "McAsciiParser-gen.cpp"
	{
	if ( ( p_) == ( pe_) )
		goto _test_eof;
	if ( ( savedCs_) == 0 )
		goto _out;
_resume:
	switch ( ( savedCs_) ) {
case 1:
	switch( (*( p_)) ) {
		case 97: goto tr0;
		case 99: goto tr2;
		case 100: goto tr3;
		case 101: goto tr4;
		case 102: goto tr5;
		case 103: goto tr6;
		case 105: goto tr7;
		case 108: goto tr8;
		case 109: goto tr9;
		case 112: goto tr10;
		case 113: goto tr11;
		case 114: goto tr12;
		case 115: goto tr13;
		case 118: goto tr14;
	}
	goto tr1;
case 0:
	goto _out;
case 2:
	switch( (*( p_)) ) {
		case 100: goto tr15;
		case 112: goto tr16;
	}
	goto tr1;
case 3:
	switch( (*( p_)) ) {
		case 100: goto tr17;
		case 109: goto tr18;
	}
	goto tr1;
case 4:
	if ( (*( p_)) == 32 )
		goto tr19;
	goto tr1;
case 106:
	goto tr1;
case 5:
	if ( (*( p_)) == 105 )
		goto tr20;
	goto tr1;
case 6:
	if ( (*( p_)) == 110 )
		goto tr21;
	goto tr1;
case 7:
	if ( (*( p_)) == 32 )
		goto tr22;
	goto tr1;
case 8:
	if ( (*( p_)) == 112 )
		goto tr23;
	goto tr1;
case 9:
	if ( (*( p_)) == 101 )
		goto tr24;
	goto tr1;
case 10:
	if ( (*( p_)) == 110 )
		goto tr25;
	goto tr1;
case 11:
	if ( (*( p_)) == 100 )
		goto tr26;
	goto tr1;
case 12:
	if ( (*( p_)) == 32 )
		goto tr27;
	goto tr1;
case 13:
	if ( (*( p_)) == 97 )
		goto tr28;
	goto tr1;
case 14:
	if ( (*( p_)) == 115 )
		goto tr29;
	goto tr1;
case 15:
	if ( (*( p_)) == 32 )
		goto tr30;
	goto tr1;
case 16:
	if ( (*( p_)) == 101 )
		goto tr31;
	goto tr1;
case 17:
	switch( (*( p_)) ) {
		case 99: goto tr32;
		case 108: goto tr33;
	}
	goto tr1;
case 18:
	if ( (*( p_)) == 114 )
		goto tr34;
	goto tr1;
case 19:
	if ( (*( p_)) == 32 )
		goto tr35;
	goto tr1;
case 20:
	if ( (*( p_)) == 101 )
		goto tr36;
	goto tr1;
case 21:
	if ( (*( p_)) == 116 )
		goto tr37;
	goto tr1;
case 22:
	if ( (*( p_)) == 101 )
		goto tr38;
	goto tr1;
case 23:
	if ( (*( p_)) == 32 )
		goto tr39;
	goto tr1;
case 24:
	if ( (*( p_)) == 120 )
		goto tr40;
	goto tr1;
case 25:
	if ( (*( p_)) == 101 )
		goto tr41;
	goto tr1;
case 26:
	if ( (*( p_)) == 99 )
		goto tr21;
	goto tr1;
case 27:
	if ( (*( p_)) == 108 )
		goto tr42;
	goto tr1;
case 28:
	if ( (*( p_)) == 117 )
		goto tr43;
	goto tr1;
case 29:
	if ( (*( p_)) == 115 )
		goto tr44;
	goto tr1;
case 30:
	if ( (*( p_)) == 104 )
		goto tr45;
	goto tr1;
case 31:
	if ( (*( p_)) == 95 )
		goto tr46;
	goto tr1;
case 32:
	switch( (*( p_)) ) {
		case 97: goto tr47;
		case 114: goto tr48;
	}
	goto tr1;
case 33:
	if ( (*( p_)) == 108 )
		goto tr49;
	goto tr1;
case 34:
	if ( (*( p_)) == 108 )
		goto tr50;
	goto tr1;
case 35:
	if ( (*( p_)) == 101 )
		goto tr51;
	goto tr1;
case 36:
	if ( (*( p_)) == 103 )
		goto tr52;
	goto tr1;
case 37:
	if ( (*( p_)) == 101 )
		goto tr53;
	goto tr1;
case 38:
	if ( (*( p_)) == 120 )
		goto tr54;
	goto tr1;
case 39:
	if ( (*( p_)) == 32 )
		goto tr55;
	goto tr1;
case 40:
	if ( (*( p_)) == 101 )
		goto tr56;
	goto tr1;
case 41:
	if ( (*( p_)) == 116 )
		goto tr57;
	goto tr1;
case 42:
	switch( (*( p_)) ) {
		case 32: goto tr58;
		case 115: goto tr59;
	}
	goto tr1;
case 43:
	if ( (*( p_)) == 32 )
		goto tr60;
	goto tr1;
case 44:
	if ( (*( p_)) == 110 )
		goto tr61;
	goto tr1;
case 45:
	if ( (*( p_)) == 99 )
		goto tr62;
	goto tr1;
case 46:
	if ( (*( p_)) == 114 )
		goto tr63;
	goto tr1;
case 47:
	if ( (*( p_)) == 32 )
		goto tr64;
	goto tr1;
case 48:
	if ( (*( p_)) == 101 )
		goto tr65;
	goto tr1;
case 49:
	if ( (*( p_)) == 97 )
		goto tr66;
	goto tr1;
case 50:
	if ( (*( p_)) == 115 )
		goto tr67;
	goto tr1;
case 51:
	if ( (*( p_)) == 101 )
		goto tr68;
	goto tr1;
case 52:
	if ( (*( p_)) == 45 )
		goto tr69;
	goto tr1;
case 53:
	switch( (*( p_)) ) {
		case 103: goto tr70;
		case 115: goto tr71;
	}
	goto tr1;
case 54:
	if ( (*( p_)) == 101 )
		goto tr72;
	goto tr1;
case 55:
	if ( (*( p_)) == 116 )
		goto tr73;
	goto tr1;
case 56:
	if ( (*( p_)) == 32 )
		goto tr74;
	goto tr1;
case 57:
	if ( (*( p_)) == 101 )
		goto tr75;
	goto tr1;
case 58:
	if ( (*( p_)) == 116 )
		goto tr76;
	goto tr1;
case 59:
	if ( (*( p_)) == 32 )
		goto tr77;
	goto tr1;
case 60:
	if ( (*( p_)) == 101 )
		goto tr78;
	goto tr1;
case 61:
	if ( (*( p_)) == 116 )
		goto tr79;
	goto tr1;
case 62:
	if ( (*( p_)) == 97 )
		goto tr80;
	goto tr1;
case 63:
	if ( (*( p_)) == 103 )
		goto tr81;
	goto tr1;
case 64:
	if ( (*( p_)) == 101 )
		goto tr82;
	goto tr1;
case 65:
	if ( (*( p_)) == 116 )
		goto tr83;
	goto tr1;
case 66:
	if ( (*( p_)) == 32 )
		goto tr84;
	goto tr1;
case 67:
	if ( (*( p_)) == 114 )
		goto tr85;
	goto tr1;
case 68:
	if ( (*( p_)) == 101 )
		goto tr86;
	goto tr1;
case 69:
	if ( (*( p_)) == 112 )
		goto tr87;
	goto tr1;
case 70:
	if ( (*( p_)) == 101 )
		goto tr88;
	goto tr1;
case 71:
	if ( (*( p_)) == 110 )
		goto tr89;
	goto tr1;
case 72:
	if ( (*( p_)) == 100 )
		goto tr90;
	goto tr1;
case 73:
	if ( (*( p_)) == 32 )
		goto tr91;
	goto tr1;
case 74:
	if ( (*( p_)) == 117 )
		goto tr92;
	goto tr1;
case 75:
	if ( (*( p_)) == 105 )
		goto tr93;
	goto tr1;
case 76:
	if ( (*( p_)) == 116 )
		goto tr94;
	goto tr1;
case 77:
	switch( (*( p_)) ) {
		case 10: goto tr95;
		case 13: goto tr96;
		case 32: goto tr94;
	}
	goto tr1;
case 78:
	if ( (*( p_)) == 10 )
		goto tr95;
	goto tr1;
case 79:
	if ( (*( p_)) == 101 )
		goto tr97;
	goto tr1;
case 80:
	if ( (*( p_)) == 112 )
		goto tr98;
	goto tr1;
case 81:
	if ( (*( p_)) == 108 )
		goto tr99;
	goto tr1;
case 82:
	if ( (*( p_)) == 97 )
		goto tr100;
	goto tr1;
case 83:
	if ( (*( p_)) == 99 )
		goto tr101;
	goto tr1;
case 84:
	if ( (*( p_)) == 101 )
		goto tr102;
	goto tr1;
case 85:
	if ( (*( p_)) == 32 )
		goto tr103;
	goto tr1;
case 86:
	switch( (*( p_)) ) {
		case 101: goto tr104;
		case 104: goto tr105;
		case 116: goto tr106;
	}
	goto tr1;
case 87:
	if ( (*( p_)) == 116 )
		goto tr107;
	goto tr1;
case 88:
	if ( (*( p_)) == 32 )
		goto tr108;
	goto tr1;
case 89:
	if ( (*( p_)) == 117 )
		goto tr109;
	goto tr1;
case 90:
	if ( (*( p_)) == 116 )
		goto tr110;
	goto tr1;
case 91:
	if ( (*( p_)) == 100 )
		goto tr111;
	goto tr1;
case 92:
	if ( (*( p_)) == 111 )
		goto tr112;
	goto tr1;
case 93:
	if ( (*( p_)) == 119 )
		goto tr113;
	goto tr1;
case 94:
	if ( (*( p_)) == 110 )
		goto tr114;
	goto tr1;
case 95:
	if ( (*( p_)) == 97 )
		goto tr115;
	goto tr1;
case 96:
	if ( (*( p_)) == 116 )
		goto tr116;
	goto tr1;
case 97:
	if ( (*( p_)) == 115 )
		goto tr117;
	goto tr1;
case 98:
	if ( (*( p_)) == 101 )
		goto tr118;
	goto tr1;
case 99:
	if ( (*( p_)) == 114 )
		goto tr119;
	goto tr1;
case 100:
	if ( (*( p_)) == 115 )
		goto tr120;
	goto tr1;
case 101:
	if ( (*( p_)) == 105 )
		goto tr121;
	goto tr1;
case 102:
	if ( (*( p_)) == 111 )
		goto tr122;
	goto tr1;
case 103:
	if ( (*( p_)) == 110 )
		goto tr123;
	goto tr1;
case 104:
	switch( (*( p_)) ) {
		case 10: goto tr124;
		case 13: goto tr125;
		case 32: goto tr123;
	}
	goto tr1;
case 105:
	if ( (*( p_)) == 10 )
		goto tr124;
	goto tr1;
	}

	tr1: ( savedCs_) = 0; goto _again;
	tr0: ( savedCs_) = 2; goto _again;
	tr15: ( savedCs_) = 3; goto _again;
	tr17: ( savedCs_) = 4; goto _again;
	tr18: ( savedCs_) = 5; goto _again;
	tr20: ( savedCs_) = 6; goto _again;
	tr21: ( savedCs_) = 7; goto _again;
	tr16: ( savedCs_) = 8; goto _again;
	tr23: ( savedCs_) = 9; goto _again;
	tr24: ( savedCs_) = 10; goto _again;
	tr25: ( savedCs_) = 11; goto _again;
	tr26: ( savedCs_) = 12; goto _again;
	tr2: ( savedCs_) = 13; goto _again;
	tr28: ( savedCs_) = 14; goto _again;
	tr29: ( savedCs_) = 15; goto _again;
	tr3: ( savedCs_) = 16; goto _again;
	tr31: ( savedCs_) = 17; goto _again;
	tr32: ( savedCs_) = 18; goto _again;
	tr34: ( savedCs_) = 19; goto _again;
	tr33: ( savedCs_) = 20; goto _again;
	tr36: ( savedCs_) = 21; goto _again;
	tr37: ( savedCs_) = 22; goto _again;
	tr38: ( savedCs_) = 23; goto _again;
	tr4: ( savedCs_) = 24; goto _again;
	tr40: ( savedCs_) = 25; goto _again;
	tr41: ( savedCs_) = 26; goto _again;
	tr5: ( savedCs_) = 27; goto _again;
	tr42: ( savedCs_) = 28; goto _again;
	tr43: ( savedCs_) = 29; goto _again;
	tr44: ( savedCs_) = 30; goto _again;
	tr45: ( savedCs_) = 31; goto _again;
	tr46: ( savedCs_) = 32; goto _again;
	tr47: ( savedCs_) = 33; goto _again;
	tr49: ( savedCs_) = 34; goto _again;
	tr48: ( savedCs_) = 35; goto _again;
	tr51: ( savedCs_) = 36; goto _again;
	tr52: ( savedCs_) = 37; goto _again;
	tr53: ( savedCs_) = 38; goto _again;
	tr54: ( savedCs_) = 39; goto _again;
	tr6: ( savedCs_) = 40; goto _again;
	tr56: ( savedCs_) = 41; goto _again;
	tr57: ( savedCs_) = 42; goto _again;
	tr59: ( savedCs_) = 43; goto _again;
	tr7: ( savedCs_) = 44; goto _again;
	tr61: ( savedCs_) = 45; goto _again;
	tr62: ( savedCs_) = 46; goto _again;
	tr63: ( savedCs_) = 47; goto _again;
	tr8: ( savedCs_) = 48; goto _again;
	tr65: ( savedCs_) = 49; goto _again;
	tr66: ( savedCs_) = 50; goto _again;
	tr67: ( savedCs_) = 51; goto _again;
	tr68: ( savedCs_) = 52; goto _again;
	tr69: ( savedCs_) = 53; goto _again;
	tr70: ( savedCs_) = 54; goto _again;
	tr72: ( savedCs_) = 55; goto _again;
	tr73: ( savedCs_) = 56; goto _again;
	tr71: ( savedCs_) = 57; goto _again;
	tr75: ( savedCs_) = 58; goto _again;
	tr76: ( savedCs_) = 59; goto _again;
	tr9: ( savedCs_) = 60; goto _again;
	tr78: ( savedCs_) = 61; goto _again;
	tr79: ( savedCs_) = 62; goto _again;
	tr80: ( savedCs_) = 63; goto _again;
	tr81: ( savedCs_) = 64; goto _again;
	tr82: ( savedCs_) = 65; goto _again;
	tr83: ( savedCs_) = 66; goto _again;
	tr10: ( savedCs_) = 67; goto _again;
	tr85: ( savedCs_) = 68; goto _again;
	tr86: ( savedCs_) = 69; goto _again;
	tr87: ( savedCs_) = 70; goto _again;
	tr88: ( savedCs_) = 71; goto _again;
	tr89: ( savedCs_) = 72; goto _again;
	tr90: ( savedCs_) = 73; goto _again;
	tr11: ( savedCs_) = 74; goto _again;
	tr92: ( savedCs_) = 75; goto _again;
	tr93: ( savedCs_) = 76; goto _again;
	tr94: ( savedCs_) = 77; goto _again;
	tr96: ( savedCs_) = 78; goto _again;
	tr12: ( savedCs_) = 79; goto _again;
	tr97: ( savedCs_) = 80; goto _again;
	tr98: ( savedCs_) = 81; goto _again;
	tr99: ( savedCs_) = 82; goto _again;
	tr100: ( savedCs_) = 83; goto _again;
	tr101: ( savedCs_) = 84; goto _again;
	tr102: ( savedCs_) = 85; goto _again;
	tr13: ( savedCs_) = 86; goto _again;
	tr104: ( savedCs_) = 87; goto _again;
	tr107: ( savedCs_) = 88; goto _again;
	tr105: ( savedCs_) = 89; goto _again;
	tr109: ( savedCs_) = 90; goto _again;
	tr110: ( savedCs_) = 91; goto _again;
	tr111: ( savedCs_) = 92; goto _again;
	tr112: ( savedCs_) = 93; goto _again;
	tr113: ( savedCs_) = 94; goto _again;
	tr106: ( savedCs_) = 95; goto _again;
	tr115: ( savedCs_) = 96; goto _again;
	tr116: ( savedCs_) = 97; goto _again;
	tr14: ( savedCs_) = 98; goto _again;
	tr118: ( savedCs_) = 99; goto _again;
	tr119: ( savedCs_) = 100; goto _again;
	tr120: ( savedCs_) = 101; goto _again;
	tr121: ( savedCs_) = 102; goto _again;
	tr122: ( savedCs_) = 103; goto _again;
	tr123: ( savedCs_) = 104; goto _again;
	tr125: ( savedCs_) = 105; goto _again;
	tr19: ( savedCs_) = 106; goto f0;
	tr22: ( savedCs_) = 106; goto f1;
	tr27: ( savedCs_) = 106; goto f2;
	tr30: ( savedCs_) = 106; goto f3;
	tr35: ( savedCs_) = 106; goto f4;
	tr39: ( savedCs_) = 106; goto f5;
	tr50: ( savedCs_) = 106; goto f6;
	tr55: ( savedCs_) = 106; goto f7;
	tr58: ( savedCs_) = 106; goto f8;
	tr60: ( savedCs_) = 106; goto f9;
	tr64: ( savedCs_) = 106; goto f10;
	tr74: ( savedCs_) = 106; goto f11;
	tr77: ( savedCs_) = 106; goto f12;
	tr84: ( savedCs_) = 106; goto f13;
	tr91: ( savedCs_) = 106; goto f14;
	tr95: ( savedCs_) = 106; goto f15;
	tr103: ( savedCs_) = 106; goto f16;
	tr108: ( savedCs_) = 106; goto f17;
	tr114: ( savedCs_) = 106; goto f18;
	tr117: ( savedCs_) = 106; goto f19;
	tr124: ( savedCs_) = 106; goto f20;

f8:
#line 986 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  initGetLike<McOperation<mc_op_get>, McRequest>();
  {( p_)++; goto _out; }
}
	goto _again;
f9:
#line 991 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  initGetLike<McOperation<mc_op_gets>, McRequest>();
  {( p_)++; goto _out; }
}
	goto _again;
f11:
#line 996 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  initGetLike<McOperation<mc_op_lease_get>, McRequest>();
  {( p_)++; goto _out; }
}
	goto _again;
f13:
#line 1001 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  initGetLike<McOperation<mc_op_metaget>, McRequest>();
  {( p_)++; goto _out; }
}
	goto _again;
f17:
#line 1006 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  initSetLike<McOperation<mc_op_set>, McRequest>();
  {( p_)++; goto _out; }
}
	goto _again;
f0:
#line 1011 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  initSetLike<McOperation<mc_op_add>, McRequest>();
  {( p_)++; goto _out; }
}
	goto _again;
f16:
#line 1016 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  initSetLike<McOperation<mc_op_replace>, McRequest>();
  {( p_)++; goto _out; }
}
	goto _again;
f2:
#line 1021 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  initSetLike<McOperation<mc_op_append>, McRequest>();
  {( p_)++; goto _out; }
}
	goto _again;
f14:
#line 1026 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  initSetLike<McOperation<mc_op_prepend>, McRequest>();
  {( p_)++; goto _out; }
}
	goto _again;
f3:
#line 1031 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  savedCs_ = mc_ascii_cas_req_body_en_req_body;
  errorCs_ = mc_ascii_cas_req_body_error;
  state_ = State::PARTIAL;
  currentMessage_.emplace<McRequest>();
  consumer_ = &McServerAsciiParser::consumeCas;
  {( p_)++; goto _out; }
}
	goto _again;
f12:
#line 1040 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  savedCs_ = mc_ascii_lease_set_req_body_en_req_body;
  errorCs_ = mc_ascii_lease_set_req_body_error;
  state_ = State::PARTIAL;
  currentMessage_.emplace<McRequest>();
  consumer_ = &McServerAsciiParser::consumeLeaseSet;
  {( p_)++; goto _out; }
}
	goto _again;
f5:
#line 1049 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  savedCs_ = mc_ascii_delete_req_body_en_req_body;
  errorCs_ = mc_ascii_delete_req_body_error;
  state_ = State::PARTIAL;
  currentMessage_.emplace<McRequest>();
  consumer_ = &McServerAsciiParser::consumeDelete;
  {( p_)++; goto _out; }
}
	goto _again;
f18:
#line 1058 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  savedCs_ = mc_ascii_shutdown_req_body_en_req_body;
  errorCs_ = mc_ascii_shutdown_req_body_error;
  state_ = State::PARTIAL;
  currentMessage_.emplace<McRequest>();
  consumer_ = &McServerAsciiParser::consumeShutdown;
  {( p_)++; goto _out; }
}
	goto _again;
f10:
#line 1067 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  initArithmetic<McOperation<mc_op_incr>, McRequest>();
  {( p_)++; goto _out; }
}
	goto _again;
f4:
#line 1072 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  initArithmetic<McOperation<mc_op_decr>, McRequest>();
  {( p_)++; goto _out; }
}
	goto _again;
f20:
#line 1077 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  callback_->onRequest(McOperation<mc_op_version>(), McRequest());
  finishReq();
  {( p_)++; goto _out; }
}
	goto _again;
f15:
#line 1083 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  callback_->onRequest(McOperation<mc_op_quit>(), McRequest(),
                       true /* noReply */);
  finishReq();
  {( p_)++; goto _out; }
}
	goto _again;
f19:
#line 1090 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  savedCs_ = mc_ascii_stats_req_body_en_req_body;
  errorCs_ = mc_ascii_stats_req_body_error;
  state_ = State::PARTIAL;
  currentMessage_.emplace<McRequest>();
  consumer_ = &McServerAsciiParser::consumeStats;
  {( p_)++; goto _out; }
}
	goto _again;
f1:
#line 1099 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  savedCs_ = mc_ascii_exec_req_body_en_req_body;
  errorCs_ = mc_ascii_exec_req_body_error;
  state_ = State::PARTIAL;
  currentMessage_.emplace<McRequest>();
  consumer_ = &McServerAsciiParser::consumeExec;
  {( p_)++; goto _out; }
}
	goto _again;
f7:
#line 1108 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  savedCs_ = mc_ascii_flush_re_req_body_en_req_body;
  errorCs_ = mc_ascii_flush_re_req_body_error;
  state_ = State::PARTIAL;
  currentMessage_.emplace<McRequest>();
  consumer_ = &McServerAsciiParser::consumeFlushRe;
  {( p_)++; goto _out; }
}
	goto _again;
f6:
#line 1117 "src/mcrouter/lib/network/McAsciiParser.rl"
	{
  savedCs_ = mc_ascii_flush_all_req_body_en_req_body;
  errorCs_ = mc_ascii_flush_all_req_body_error;
  state_ = State::PARTIAL;
  currentMessage_.emplace<McRequest>();
  consumer_ = &McServerAsciiParser::consumeFlushAll;
  {( p_)++; goto _out; }
}
	goto _again;

_again:
	if ( ( savedCs_) == 0 )
		goto _out;
	if ( ++( p_) != ( pe_) )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 1138 "src/mcrouter/lib/network/McAsciiParser.rl"

}

void McServerAsciiParser::finishReq() {
  state_ = State::UNINIT;
}

McAsciiParserBase::State McServerAsciiParser::consume(folly::IOBuf& buffer) {
  assert(state_ != State::ERROR && state_ != State::COMPLETE &&
         !hasReadBuffer());
  p_ = reinterpret_cast<const char*>(buffer.data());
  pe_ = p_ + buffer.length();

  while (p_ != pe_) {
    // Initialize operation parser.
    if (state_ == State::UNINIT) {
      savedCs_ = mc_ascii_req_op_type_en_command;
      errorCs_ = mc_ascii_req_op_type_error;

      // Reset all fields.
      currentUInt_ = 0;
      currentIOBuf_ = nullptr;
      remainingIOBufLength_ = 0;
      currentKey_.clear();
      noreply_ = false;
      negative_ = false;

      state_ = State::PARTIAL;

      consumer_ = &McServerAsciiParser::opTypeConsumer;
    } else {
      // In case we're currently parsing a key, set keyPieceStart_ to the
      // beginning of the current buffer.
      if (keyPieceStart_ != nullptr) {
        keyPieceStart_ = p_;
      }
    }

    (this->*consumer_)(buffer);

    // If we're parsing a key, append current piece of buffer to it.
    if (keyPieceStart_ != nullptr) {
      appendKeyPiece(buffer, currentKey_, keyPieceStart_, p_);
    }

    if (savedCs_ == errorCs_) {
      handleError(buffer);
      break;
    }

    buffer.trimStart(p_ - reinterpret_cast<const char*>(buffer.data()));
  }

  return state_;
}

}}  // facebook::memcache
