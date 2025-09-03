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

namespace utilities::any_float::detail_ {

class FloatPIMPL {
public:
    using parent_type   = Float;
    using pimpl_pointer = typename parent_type::pimpl_pointer;

    using size_type = std::size_t;

    virtual Float convert(const FloatPIMPL& other) = 0;

    virtual pimpl_pointer add(const FloatPIMPL& other) = 0;

    virtual size_type digits10() const = 0;

    bool has_lower_precision(const FloatPIMPL& other) {
        return digits10() < other.digits10();
    }

    bool has_same_or_higher_precision(const FloatPIMPL& other) {
        return !has_lower_precision(other);
    }
};

template<typename FloatType>
class FloatPIMPLImpl : public FloatPIMPL {
private:
public:
    Float(FloatType float_in) : m_float_(std::move(float_in)) {}

    virtual Float convert(const FloatPIMPL& other) override {}

    Float add(const FloatPIMPL& other) override {
        if(has_same_or_higher_precision(other))
            return make_float(m_float_ + other.downcast<FloatType>());
        else
        other.convert(m_float_)

          private : FloatType m_float_;
    };

} // namespace utilities::any_float::detail_
