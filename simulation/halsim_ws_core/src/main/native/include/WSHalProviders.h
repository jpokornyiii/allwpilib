// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <functional>
#include <memory>
#include <string>

#include <hal/simulation/NotifyListener.h>
#include <wpi/json.h>
#include <wpi/mutex.h>

#include "WSBaseProvider.h"

namespace wpilibws {

typedef void (*HALCbRegisterIndexedFunc)(int32_t index,
                                         HAL_NotifyCallback callback,
                                         void* param, HAL_Bool initialNotify);
typedef void (*HALCbRegisterSingleFunc)(HAL_NotifyCallback callback,
                                        void* param, HAL_Bool initialNotify);

// provider generates diffs based on values
class HALSimWSHalProvider : public HALSimWSBaseProvider {
 public:
  using HALSimWSBaseProvider::HALSimWSBaseProvider;

  void OnNetworkConnected(
      std::shared_ptr<HALSimBaseWebSocketConnection> ws) override;
  void OnNetworkDisconnected() override;

  void ProcessHalCallback(const wpi::json& payload);

 protected:
  virtual void RegisterCallbacks() = 0;
  virtual void CancelCallbacks() = 0;
};

// provider generates per-channel diffs
class HALSimWSHalChanProvider : public HALSimWSHalProvider {
 public:
  explicit HALSimWSHalChanProvider(int32_t channel, const std::string& key,
                                   const std::string& type);

  int32_t GetChannel() { return m_channel; }

 protected:
  int32_t m_channel;
};

using WSRegisterFunc = std::function<void(
    const std::string&, std::shared_ptr<HALSimWSBaseProvider>)>;

template <typename T>
void CreateProviders(const std::string& prefix, int32_t numChannels,
                     WSRegisterFunc webRegisterFunc);

template <typename T>
void CreateSingleProvider(const std::string& key,
                          WSRegisterFunc webRegisterFunc);

#include "WSHalProviders.inl"

}  // namespace wpilibws
