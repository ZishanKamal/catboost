#pragma once

#include "output.h"

#include <util/memory/tempbuf.h>

class TTempBufOutput: public IOutputStream, public TTempBuf {
public:
    TTempBufOutput() = default;

    explicit TTempBufOutput(size_t size)
        : TTempBuf(size)
    {
    }

    void DoWrite(const void* data, size_t len) override;
};

class TTempBufCuttingWrapperOutput: public IOutputStream {
public:
    TTempBufCuttingWrapperOutput(TTempBuf& tempbuf)
        : TempBuf_(tempbuf)
    {
    }

    void DoWrite(const void* data, size_t len) override {
        TempBuf_.Append(data, Min(len, TempBuf_.Left()));
    }

private:
    TTempBuf& TempBuf_;
};

class TGrowingTempBufOutput: public IOutputStream, public TTempBuf {
public:
    inline TGrowingTempBufOutput() = default;

    explicit TGrowingTempBufOutput(size_t size)
        : TTempBuf(size)
    {
    }

    TGrowingTempBufOutput(TGrowingTempBufOutput&&) noexcept = default;
    TGrowingTempBufOutput& operator=(TGrowingTempBufOutput&&) noexcept = default;

protected:
    void DoWrite(const void* data, size_t len) override;
};
