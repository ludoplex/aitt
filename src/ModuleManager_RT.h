/*
 * Copyright 2023 Samsung Electronics Co., Ltd. All Rights Reserved
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

#ifdef TIZEN_RT
#include <memory>
#include <string>
#include <vector>

#include "AittDiscovery.h"
#include "AittTransport.h"
#include "NullTransport.h"

namespace aitt {

class ModuleManager {
  public:
    explicit ModuleManager(const std::string &my_ip, AittDiscovery &d);
    virtual ~ModuleManager() = default;

    AittTransport &Get(AittProtocol type);
    std::unique_ptr<MQ> NewCustomMQ(const std::string &id, const AittOption &option);

  private:
    // It should be ("the number of shifts" - 1) of AittProtocol
    enum TransportType {
        TYPE_TCP,         //(0x1 << 1)
        TYPE_TCP_SECURE,  //(0x1 << 2)
        TYPE_TRANSPORT_MAX,
    };

    TransportType Convert(AittProtocol type);

    std::string ip;
    AittDiscovery &discovery;
    std::unique_ptr<AittTransport> transports[TYPE_TRANSPORT_MAX];
    NullTransport null_transport;
};

}  // namespace aitt

#endif
