/* Copyright 2017 R. Thomas
 * Copyright 2017 Quarkslab
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
#include "pyPE.hpp"

#include "LIEF/PE/hash.hpp"
#include "LIEF/PE/LoadConfigurations.hpp"

#include <string>
#include <sstream>

template<class T>
using getter_t = T (LoadConfigurationV6::*)(void) const;

template<class T>
using setter_t = void (LoadConfigurationV6::*)(T);

void init_PE_LoadConfigurationV6_class(py::module& m) {
  py::class_<LoadConfigurationV6, LoadConfigurationV5>(m, "LoadConfigurationV6",
    "" RST_CLASS_REF(lief.PE.LoadConfigurationV5) " enhanced with Hotpatch and improved RFG. \n\n"
    "It is associated with the " RST_CLASS_REF(lief.PE.WIN_VERSION) ": "
    ":attr:`~lief.PE.WIN_VERSION.WIN10_0_15002`")

    .def(py::init<>())

    .def_property("guard_rf_verify_stackpointer_function_pointer",
        static_cast<getter_t<uint64_t>>(&LoadConfigurationV6::guard_rf_verify_stackpointer_function_pointer),
        static_cast<setter_t<uint64_t>>(&LoadConfigurationV6::guard_rf_verify_stackpointer_function_pointer),
        "VA of the Function verifying the stack pointer")

    .def_property("hotpatch_table_offset",
        static_cast<getter_t<uint32_t>>(&LoadConfigurationV6::hotpatch_table_offset),
        static_cast<setter_t<uint32_t>>(&LoadConfigurationV6::hotpatch_table_offset),
        "Offset to the *hotpatch* table")


    .def("__eq__", &LoadConfigurationV6::operator==)
    .def("__ne__", &LoadConfigurationV6::operator!=)
    .def("__hash__",
        [] (const LoadConfigurationV6& config) {
          return Hash::hash(config);
        })


    .def("__str__", [] (const LoadConfigurationV6& config)
        {
          std::ostringstream stream;
          stream << config;
          std::string str = stream.str();
          return str;
        });


}
