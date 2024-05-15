#include <cstddef> // size_t ir ptrdiff_t tipams
#include <iterator> // reverse_iterator tipui
#include <memory> // allocator_traits tipams

template <typename T, typename Allocator = std::allocator<T>>
class MyVector {
public:
    // Member types
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
    pointer arr;
    size_type capacity;
    size_type current;

public:
    // Constructor
    MyVector() : arr(allocator_type().allocate(1)), capacity(1), current(0) {}

    // Destructor
    ~MyVector() {
        allocator_type().deallocate(arr, capacity);
    }
};