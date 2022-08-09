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

#include <flatbuffers/flexbuffers.h>

class FlexbufPrinter {
  public:
    FlexbufPrinter();

    void PrettyPrint(const std::string &name, const uint8_t *data, int datalen);

  private:
    std::string PrettyTab(bool ignore);
    void PrettyMap(const flexbuffers::Reference &data, bool inline_value);
    void PrettyVector(const flexbuffers::Reference &data, bool inline_value);
    void PrettyBlob(const flexbuffers::Reference &data, bool inline_value);
    void PrettyParsing(const flexbuffers::Reference &data, bool inline_value);

    int tab;
};
