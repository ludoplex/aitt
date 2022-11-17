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

#include <memory>

#include "MainLoopIface.h"

namespace aitt {

class MainLoopHandler : public MainLoopIface {
  public:
    MainLoopHandler();
    virtual ~MainLoopHandler() = default;

    static void AddIdle(MainLoopHandler *handle, const mainLoopCB &cb,
          MainLoopData *user_data = nullptr);

    void Run() override;
    bool Quit() override;
    void AddIdle(const mainLoopCB &cb, MainLoopData *user_data = nullptr) override;
    void AddWatch(int fd, const mainLoopCB &cb, MainLoopData *user_data = nullptr) override;
    MainLoopData *RemoveWatch(int fd) override;
    unsigned int AddTimeout(int interval, const mainLoopCB &cb,
          MainLoopData *user_data = nullptr) override;
    void RemoveTimeout(unsigned int id) override;

  private:
    std::unique_ptr<MainLoopIface> loop;
};

}  // namespace aitt
