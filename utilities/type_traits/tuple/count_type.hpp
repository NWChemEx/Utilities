#pragma once
#include <tuple>
#include <type_traits>
#include "utilities/type_traits/parameter_pack_traits.hpp"

namespace utilities::type_traits::tuple {
namespace detail_ {

/** @brief Primary template for counting the number of times a type appears in a
 *         tuple
 *
 *  This struct can be used to count the number of times @p Type2Look4 appears in the tuple
 *  @p Tuple. The primary template is selected when @p Tuple is not an
 *  std::tuple; the primary template is not defined and thus a compilation error
 *  will arise if @p Tuple is not a tuple.
 *
 *  @tparam Type2Look4 The type we are attempting to find in @p Tuple
 *  @tparam Tuple If this version of has_type is selected @p Tuple will be a
 *                type other than std::tuple.
 */
template<typename Type2Look4, typename Tuple>
struct count_type;


/// Implementation of `count_type` for tuple types
template<typename Type2Look4, typename... TupleTypes>
struct count_type<Type2Look4, std::tuple<TupleTypes...>>
  : public utilities::type_traits::parameter_pack_count_type< Type2Look4,
                                                              TupleTypes...> {};

} // namespace detail_

/** @brief Global variable indicating the numberof times @p Type2Look4 appears in 
 *         the tuple @p Tuple.
 *
 *  This is the public API for determining the number of times  a type appears in 
 *  a tuple. 
 *
 *  @tparam Type2Look4 The type we are looking for.
 *  @tparam Tuple The tuple we are searching.
 */
template<typename Type2Look4, typename Tuple>
static constexpr std::size_t count_type_v = detail_::count_type<Type2Look4, Tuple>::value;

} // namespace utilities::type_traits::tuple
