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
#include <utility>

namespace utilities::any_float {
namespace detail_ {
class FloatPIMPL;
}

class Float {
public:
    using pimpl_base    = FloatPIMPL;
    using pimpl_pointer = std::unique_ptr<pimpl_base>;

    explicit Float(pimpl_pointer pimpl) : m_pimpl_(std::move(pimpl)) {}

private:
    pimpl_pointer m_pimpl_;
};

template<typename FloatType>
Float make_float(FloatType&& float_in) {
    using clean_type = std::decay_t<FloatType>;
    using impl_type  = detail_::FloatPIMPLImpl<clean_type>;
    auto ptr = std::make_unique<impl_type>(std::forward<FloatType>(float_in));
    return Float(std::move(ptr));
}

template<typename FloatType>
FloatType unwrap_float(Float& float_in) {
    bool float_
}

} // namespace utilities::any_float
