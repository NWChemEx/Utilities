/*
 * Copyright 2025 NWChemEx-Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include <utilities/any_float/float_traits.hpp>

namespace utilities::any_float {

template<typename ToType, typename FromType>
class Converter {
private:
    using to_traits   = FloatTraits<ToType>;
    using from_traits = FloatTraits<FromType>;

public:
    using to_value_type = typename to_traits::value_type;

    using from_value_type = typename from_traits::value_type;

    to_value_type convert_value(from_value_type from) { return from; }
};

} // namespace utilities::any_float
