// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <memory>

#include "frc/simulation/CallbackStore.h"

namespace frc {

class Relay;

namespace sim {

/**
 * Class to control a simulated relay.
 */
class RelaySim {
 public:
  /**
   * Constructs from a Relay object.
   *
   * @param relay Relay to simulate
   */
  explicit RelaySim(const Relay& relay);

  /**
   * Constructs from a relay channel number.
   *
   * @param channel Channel number
   */
  explicit RelaySim(int channel);

  std::unique_ptr<CallbackStore> RegisterInitializedForwardCallback(
      NotifyCallback callback, bool initialNotify);

  bool GetInitializedForward() const;

  void SetInitializedForward(bool initializedForward);

  std::unique_ptr<CallbackStore> RegisterInitializedReverseCallback(
      NotifyCallback callback, bool initialNotify);

  bool GetInitializedReverse() const;

  void SetInitializedReverse(bool initializedReverse);

  std::unique_ptr<CallbackStore> RegisterForwardCallback(
      NotifyCallback callback, bool initialNotify);

  bool GetForward() const;

  void SetForward(bool forward);

  std::unique_ptr<CallbackStore> RegisterReverseCallback(
      NotifyCallback callback, bool initialNotify);

  bool GetReverse() const;

  void SetReverse(bool reverse);

  void ResetData();

 private:
  int m_index;
};
}  // namespace sim
}  // namespace frc
