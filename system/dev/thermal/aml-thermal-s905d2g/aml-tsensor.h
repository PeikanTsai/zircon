// Copyright 2018 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <ddk/io-buffer.h>
#include <ddk/protocol/platform-device.h>
#include <ddktl/device.h>
#include <fbl/unique_ptr.h>
#include <hwreg/mmio.h>
#include <lib/zx/interrupt.h>

namespace thermal {

// This class represents a temperature sensor
// which is on the S905D2 core.
class AmlTSensor {

public:
    DISALLOW_COPY_AND_ASSIGN_ALLOW_MOVE(AmlTSensor);
    AmlTSensor(){};
    uint32_t ReadTemperature();
    zx_status_t InitSensor(zx_device_t* parent);
    ~AmlTSensor();

private:
    zx_status_t InitPdev(zx_device_t* parent);
    uint32_t TempToCode(uint32_t temp, bool trend);
    uint32_t CodeToTemp(uint32_t temp_code);
    void SetRebootTemperature(uint32_t temp);
    uint32_t trim_info_;
    platform_device_protocol_t pdev_;
    io_buffer_t pll_mmio_;
    io_buffer_t ao_mmio_;
    io_buffer_t hiu_mmio_;
    zx::interrupt tsensor_irq_;
    fbl::unique_ptr<hwreg::RegisterIo> pll_regs_;
    fbl::unique_ptr<hwreg::RegisterIo> ao_regs_;
    fbl::unique_ptr<hwreg::RegisterIo> hiu_regs_;
};
} // namespace thermal
