// Copyright (c) 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/third_party/quic/core/qpack/qpack_decoder_stream_receiver.h"

#include "net/third_party/quic/core/qpack/qpack_constants.h"
#include "net/third_party/quiche/src/http2/decoder/decode_buffer.h"
#include "net/third_party/quiche/src/http2/decoder/decode_status.h"

namespace quic {

QpackDecoderStreamReceiver::QpackDecoderStreamReceiver(Delegate* delegate)
    : instruction_decoder_(QpackDecoderStreamLanguage(), this),
      delegate_(delegate),
      error_detected_(false) {
  DCHECK(delegate_);
}

void QpackDecoderStreamReceiver::Decode(QuicStringPiece data) {
  if (data.empty() || error_detected_) {
    return;
  }

  instruction_decoder_.Decode(data);
}

bool QpackDecoderStreamReceiver::OnInstructionDecoded(
    const QpackInstruction* instruction) {
  if (instruction == TableStateSynchronizeInstruction()) {
    delegate_->OnTableStateSynchronize(instruction_decoder_.varint());
    return true;
  }

  if (instruction == HeaderAcknowledgementInstruction()) {
    delegate_->OnHeaderAcknowledgement(instruction_decoder_.varint());
    return true;
  }

  DCHECK_EQ(instruction, StreamCancellationInstruction());
  delegate_->OnStreamCancellation(instruction_decoder_.varint());
  return true;
}

void QpackDecoderStreamReceiver::OnError(QuicStringPiece error_message) {
  DCHECK(!error_detected_);

  error_detected_ = true;
  delegate_->OnErrorDetected(error_message);
}

}  // namespace quic
