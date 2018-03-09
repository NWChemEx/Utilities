#pragma once
#include "Utilities/TypeTraits/IteratorTypes.hpp"
#include "Utilities/TypeTraits/TupleUtilities.hpp" //Includes tuple always
#include <algorithm>                                 //For std::min
#include <type_traits>

namespace Utilities {
namespace detail_ {

/// Forward declaration of TupleContainerImpl for meta-programming
template<typename IncrementFunctor, typename... ContainerTypes>
class TupleContainerImpl;

/// Struct which contains value==false if T is not a TupleContainerImpl instance
template<typename T>
struct IsTupleContainerImpl : std::false_type {};

/// Specialization of IsTupleContainerImpl to trigger value == true
template<typename IncrementFunctor, typename... Args>
struct IsTupleContainerImpl<TupleContainerImpl<IncrementFunctor, Args...>>
  : std::true_type {};

/// This will allow us to use iterators which are actually raw pointers
template<typename T>
struct GetValueType {
    using type = typename T::value_type;
};

/// Partial specialization to catch raw pointers
template<typename T>
struct GetValueType<T*> {
    using type = T;
};

template<typename T>
using IteratorType =
  std::conditional_t<std::is_same<T, std::remove_cv_t<T>>::value,
                     typename T::iterator, typename T::const_iterator>;

/** @brief Simulates a container filled with some set of tuples formed from a
 *         series of containers.
 *
 *  This class is primarily code factorization for iterating over a series
 *  of containers.
 *
 *  @note This class is the implementation of the innards of the TupleContainer
 function,
 * but for all intents and purposes it is TupleContainer.  The TupleContainer
 function only exists so
 *  the usage syntax is not:
 *  @code
 *  for(auto& x :
 TupleContainer<iterator_t1,iterator_t2,...>(iterator1,iterator2,...))
 *  {
 *      ...
 *  }
 *  @endcode
 *
 *
 *  @note At the moment the values returned in the tuples are copies and not the
 *        actual ones in the zipped containers.  Everything is by reference
 *        until apply_functor_to_tuple is called to modify the buffer of the
 *        iterator.
 * @tparam IncrementFunctor The type of a functor that can be used to compute
 *         the next tuple in the sequence.  Must contain a member function with
 *         the signature:
 *         @code
 *         template<typename IteratorType, std::size_t...I>
 *         void run(const IteratorType& start, const IteratorType& end,
                    IteratorType& value,  std::index_sequence<I...>);
 *         @endcode
 *         where start and end are tuples containing iterators to the original
 *         containers as generated by calling begin and end respectively, value
 *         is a tuple containing the current value of the iterators (and should
 *         be updated).
 *
 * @tparam ContainerTypes The types of the containers that will be zipped
 *                       together.
 *
 */
template<typename IncrementFunctor, typename... ContainerTypes>
class TupleContainerImpl {
private:
    /// Forward declaration of the actual iterator type
    class TupleContainerIterator;

    /// The type of a tuple holding iterators to the containers
    using iterator_tuple = std::tuple<detail_::IteratorType<ContainerTypes>...>;

public:
    /// The type of an element in this container.
    using value_type = std::tuple<std::remove_cv_t<
      typename GetValueType<detail_::IteratorType<ContainerTypes>>::type>...>;
    /// The type of a reference to an element of this container
    using reference = value_type&;
    /// The type of a read-only element of this container
    using const_reference = const value_type&;
    /// The type of an iterator to this container (can't actually modify)
    using iterator = TupleContainerIterator;
    /// The type of a read-only iterator to this container
    using const_iterator = TupleContainerIterator;
    /// The type of the difference between two pointers
    using difference_type = long int;
    /// The type of an index or offset into this container
    using size_type = std::size_t;

    /** @brief Constructs a container filled with no tuples taken from no
     *         containers.
     *
     *  @throw None. No throw guarantee.
     */
    TupleContainerImpl() noexcept = default;

    /** @brief Constructs a new TupleContainerImpl by grabbing the begin and
     *         end iterators of a container
     * @tparam SizeFunctor The type of a functor that will be used to compute
     *         the number of elements in this container.  Must have a static
     *         member variable named @p initial_value containing the initial
     *         value for the accumulate and must have a function named run with
     *         the following interface:
               @code
               template<std::size_t,typename T>
               auto run(std::size_t curr_size, T&& container) const;
               @endcode
               where @p curr_size is the current value of the accumulate and
               @p container is the next container whose size is to be included.
               The function should return the updated value of the current size.
     * @tparam InputTypes The types of the containers.
     * @param containers The actual container instances to zip.  Note that the
     *        iterators stored in this class are tied to the original containers
     *        still and thus their validity is also tied to those containers.
     *
     * @throw ??? This constructor will call the size(), begin() and end()
     *            members of each container if any of those member functions
     *            throw, then this constructor will also throw.  Strong throw
     *            guarantee.
     */
    template<typename SizeFunctor, typename... InputTypes>
    TupleContainerImpl(SizeFunctor f, InputTypes&&... containers) :
      size_(
        sizeof...(InputTypes) ?
          tuple_accumulate(std::tie(std::forward<InputTypes>(containers)...), f,
                           SizeFunctor::initial_value) :
          0L),
      begin_(!size_, std::forward<InputTypes>(containers)...),
      end_(true, std::forward<InputTypes>(containers)...) {}

    /** @brief Makes a copy of the current container.
     *
     *  It should be noted that this is a deep copy of the TupleContainerImpl
     * container, which means that all internal state will be deep copied.  The
     * internal state will not be copied recursively though (which in turn
     * means that the tuple copies will still be filled with shallow copies of
     * the input containers).
     *
     *  @param rhs The container to copy.
     *  @throw None. No throw guarantee. Can't be noexcept b/c tuple copy
     *  constructor is not noexcept; however,
     *
     */
    TupleContainerImpl(const TupleContainerImpl& /*rhs*/) = default;

    /** @brief Takes ownership of another container.
     *
     *  @param rhs The container to take over.  After this call @p rhs is in a
     *  valid, but otherwise undefined state.
     *  @throw None. No throw guarantee.
     *
     */
    TupleContainerImpl(TupleContainerImpl&& /*rhs*/) = default;

    /** @brief Deletes the current instance.
     *
     *  This doesn't delete the containers that were zipped together.
     *
     *  @throw None. No throw guarantee.
     */
    ~TupleContainerImpl() = default;

    /** @brief Assigns a deep copy of another TupleContainerImpl to this one.
     *
     *  The same comments as the copy constructor apply here, namely that the
     *  result still contains shallow copies of the actual containers.
     *
     *  @param rhs The TupleContainerImpl to copy the state of.
     *
     *  @throw None. No throw guarantee. Can't be marked as noexcept because
     *  tuple copy constructor is not noexcept
     */
    TupleContainerImpl& operator=(const TupleContainerImpl& /*rhs*/) = default;

    /** @brief Assigns another TupleContainerImpl's state to this one.
     *
     *  @param rhs The TupleContainerImpl to take the state of.  After this call
     * @p rhs is in a valid, but otherwise undefined state.
     *  @return The current instance containing @p rhs 's state.
     *  @throw None. No throw guarantee.
     */
    TupleContainerImpl& operator=(TupleContainerImpl&& /*rhs*/) = default;

    /** @brief Returns the number of tuples in this container.
     *
     *  Given a list of containers such that the @f$i@f$-th container contains
     *  @f$N_i@f$ elements.  This function returns the smallest @f$N_i@f$ as
     *  that is the maximum number of iterations possible.
     *
     *  @return The number of tuples in this container.
     *  @throw None. No throw guarantee.
     */
    size_type size() const noexcept { return size_; }

    /** @brief Returns the maximum number of elements this container can
     *  possibly hold ignoring hardware considerations.
     *
     *  At the moment this function simply returns the maximum of @p size_type.
     *
     *  @return The maximum number of elements this container can possibly hold
     *  ignoring hardware considerations.
     *
     *  @throw None. No throw guarantee.
     */
    constexpr static size_type max_size() noexcept {
        return std::numeric_limits<size_type>::max();
    }

    /**
     * @brief Returns true if the current instance contains no elements
     *
     * @return True if the current instance holds no elements and false if it
     *         holds even one element.
     * @throw None. No throw guarantee.
     */
    bool empty() const noexcept { return !size_; }

    /**
     * @brief Creates an iterator that points to the first tuple of elements in
     *        the zipped containers.
     *
     * @return An iterator pointing to first tuple of elements inside the
     * zipped container.
     */
    iterator begin() { return begin_; }

    ///@copydoc begin()
    const_iterator cbegin() const { return begin_; }

    /**
     * @brief Creates an iterator that points to just past the last tuple of
     *        elements in the zipped containers.
     *
     * @return An iterator pointing to just past the last tuple of elements
     * inside the zipped container.
     */
    iterator end() { return end_; }

    ///@copydoc end()
    const_iterator cend() const { return end_; }

    /**
     * @brief Determines if two TupleContainerImpl instances are holding the
     * same elements.
     *
     * Two TupleContainerImpl instances are assumed equal if they have the same
     * first and last elements (size is checked for good measure).  Given that
     * incrementing is implemented via functor, which is part of the type, this
     * should be sufficient to ensure the same sequence will be generated.
     *
     * @tparam OtherContainers The types of the other containers.  Must satisfy
     *         the same concepts as ContainerTypes.
     * @param rhs The actual TupleContainerImpl instance to compare to.
     * @return True if the the two instances hold the same elements.
     * @throw None. No throw guarantee.
     */
    template<typename... OtherContainers>
    bool operator==(const TupleContainerImpl<OtherContainers...>& rhs) const
      noexcept {
        return std::tie(begin_, end_, size_) ==
               std::tie(rhs.begin_, rhs.end_, rhs.size_);
    }

    /**
     * @brief Determines if two TupleContainerImpl instances are different
     * containers.
     *
     * This function uses the same definition of equality as operator==
     *
     * @tparam OtherContainers The types of the other containers.  Must satisfy
     *         the same concepts as ContainerTypes.
     * @param rhs The actual TupleContainerImpl instance to compare to.
     * @return True if the the two instances are different containers
     *         false if the container instances are the same.
     * @throw None. No throw guarantee.
     */
    template<typename... OtherContainers>
    bool operator!=(const TupleContainerImpl<OtherContainers...>& rhs) const
      noexcept {
        return !((*this) == rhs);
    }

private:
    /// The number of containers we are zipping together
    constexpr static std::size_t ncontainers_ = sizeof...(ContainerTypes);

    /// The number of iterations in this container
    std::size_t size_ = 0;

    /// Points to start of each container
    TupleContainerIterator begin_;

    /// Points to end of each container
    TupleContainerIterator end_;

    /** @brief The class responsible for iterating over the containers stored in
     *  a TupleContainerImpl instance.
     *
     *  TupleContainerIterator instances store iterators to the zipped
     * containers and are only valid so long as said containers are in scope.
     * Since the actual iterators are stored within the TupleContainerIterator
     * instance, TupleContainerIterators remain valid even if the creating
     * TupleContainerImpl goes out of scope.
     *
     */
    class TupleContainerIterator
      : public detail_::InputIteratorBase<TupleContainerIterator, value_type> {
    private:
        /// Allows TupleContainerImpl to create an iterator
        friend class TupleContainerImpl<IncrementFunctor, ContainerTypes...>;
        /// Allows the base class to call the implementation functions
        friend class detail_::InputIteratorBase<TupleContainerIterator,
                                                value_type>;

        /** @brief Creates a TupleContainerIterator instance.
         *
         *  The TupleContainerIterator keeps a copy of the iterators internally
         * and thus is valid even if the TupleContainerImpl goes out of scope.
         * If any of the containers being iterated over go out of scope the
         * TupleContainerIterator is invalidated.
         *
         * @param containers The tuple of containers to iterate over.
         * @param at_end If true the resulting iterator will represent an
         * iterator just past the last element, otherwise it's pointing to
         * the first element.
         */
        template<typename... InputTypes>
        TupleContainerIterator(bool at_end, InputTypes&&... containers) :
          start_(tuple_transform(
            std::tie(std::forward<InputTypes>(containers)...), CallBegin())),
          end_(tuple_transform(
            std::tie(std::forward<InputTypes>(containers)...), CallEnd())),
          value_(!at_end ? start_ : end_),
          buffer_(!at_end ? tuple_transform(value_, Derefer()) : value_type()) {
        }

        /// Implements the means by which this class can be dereferenced
        reference dereference() { return buffer_; }

        /// Implements the mechanism for dereferencing a read-only iterator
        const_reference dereference() const { return buffer_; }

        /// Implements the mechansim for incrementing this iterator
        TupleContainerIterator& increment() noexcept {
            IncrementFunctor f;
            f.run(start_, end_, value_,
                  std::make_index_sequence<ncontainers_>());
            if(value_ != end_) buffer_ = tuple_transform(value_, Derefer());
            return *this;
        }

        /// Implements the mechanism for checking if this iterator equals
        /// another
        bool are_equal(const TupleContainerIterator& rhs) const noexcept {
            return value_ == rhs.value_;
        }

        /// A tuple containing the starting iterators to the containers
        iterator_tuple start_;

        /// A tuple containing the ending iterators of the containers
        iterator_tuple end_;

        /// The tuple containing our current iterators
        iterator_tuple value_;

        /// The actual element
        value_type buffer_;

        /// Functor for calling begin() on all containers
        struct CallBegin {
            template<std::size_t, typename T>
            auto run(T&& container) {
                return container.begin();
            }
        };

        /// Functor for calling end() on all containers
        struct CallEnd {
            template<std::size_t, typename T>
            auto run(T&& container) const {
                return container.end();
            }
        };

        /// Functor for derefrencing an argument
        struct Derefer {
            template<std::size_t, typename T>
            auto& run(T&& itr) const {
                return *itr;
            }
        };

    public:
        TupleContainerIterator() noexcept = default;
    };
};
} // End namespace detail_

} // namespace Utilities
