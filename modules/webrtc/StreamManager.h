/*
 * Copyright (c) 2022 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <WebRtcStream.h>

#include <functional>
#include <string>
#include <thread>
#include <vector>

namespace AittWebRTCNamespace {

class StreamManager {
  public:
    using IceCandidateAddedCallback = std::function<void(void)>;
    using StreamStartCallback = std::function<void(void)>;
    using StreamStopCallback = std::function<void(void)>;
    explicit StreamManager(const std::string &topic, const std::string &watching_topic,
          const std::string &aitt_id, const std::string &thread_id);
    virtual ~StreamManager() = default;
    virtual std::vector<uint8_t> GetDiscoveryMessage(void) = 0;

    void Start(void);
    void Stop(void);
    void HandleRemovedClient(const std::string &discovery_id);
    void HandleMsg(const std::string &discovery_id, const std::vector<uint8_t> &message);
    void SetIceCandidateAddedCallback(IceCandidateAddedCallback cb);
    void SetStreamStartCallback(StreamStartCallback cb);
    void SetStreamStopCallback(StreamStopCallback cb);
    std::string GetTopic(void) const;
    std::string GetWatchingTopic(void) const;

  protected:
    std::string topic_;
    std::string watching_topic_;
    // TODO: why dont' we remove below
    std::string aitt_id_;
    std::string thread_id_;
    // TODO: What if user copies the module?
    // Think about that case with destructor
    std::map<std::string /* Peer Aitt Discovery ID */, WebRtcStream *> streams_;
    StreamStartCallback stream_start_cb_;
    StreamStopCallback stream_stop_cb_;
    IceCandidateAddedCallback ice_candidate_added_cb_;

  private:
    virtual void SetWebRtcStreamCallbacks(WebRtcStream &stream) = 0;
    virtual void HandleStreamState(const std::string &discovery_id,
          const std::vector<uint8_t> &message) = 0;
    virtual void HandleStreamInfo(const std::string &discovery_id,
          const std::vector<uint8_t> &message) = 0;
};
}  // namespace AittWebRTCNamespace
