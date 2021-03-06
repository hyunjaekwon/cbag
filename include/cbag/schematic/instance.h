// SPDX-License-Identifier: BSD-3-Clause AND Apache-2.0
/*
Copyright (c) 2018, Regents of the University of California
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


Copyright 2019 Blue Cheetah Analog Design Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef CBAG_SCHEMATIC_INSTANCE_H
#define CBAG_SCHEMATIC_INSTANCE_H

#include <memory>
#include <unordered_set>

#include <cbag/common/box_t.h>
#include <cbag/common/param_map.h>
#include <cbag/common/transformation.h>

#include <cbag/util/sorted_map.h>

namespace cbag {
namespace sch {

/** An instance object
 */
struct instance {
  public:
    std::string lib_name;
    std::string cell_name;
    std::string view_name;
    transformation xform;
    box_t bbox;
    bool is_primitive = false;
    cbag::util::sorted_map<std::string, std::string> connections;
    param_map params;

    instance();

    instance(std::string lib, std::string cell, std::string view, transformation xform, coord_t xl,
             coord_t yl, coord_t xh, coord_t yh);

    offset_t width() const;

    offset_t height() const;

    std::unique_ptr<instance> get_copy() const;

    void clear_params();

    void set_param(const std::string &name, const param_t &val);

    void update_connection(const std::string &inst_name, cnt_t inst_size, std::string term_str,
                           std::string net_str);

    void update_connection(const std::string &inst_name, std::string term, std::string net);

    void check_connections(const std::unordered_set<std::string> &terminals);

    void update_master(std::string lib, std::string cell, bool prim, bool keep_connections);

    void resize_nets(cnt_t old_size, cnt_t new_size);

    instance get_move_by(offset_t dx, offset_t dy) const;
};

} // namespace sch
} // namespace cbag

#endif
