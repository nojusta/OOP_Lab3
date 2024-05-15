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
    // at
    reference at(size_type pos) {
        if (pos >= current) {
            throw std::out_of_range("MyVector::at");
        }
        return arr[pos];
    }

    const_reference at(size_type pos) const {
        if (pos >= current) {
            throw std::out_of_range("MyVector::at");
        }
        return arr[pos];
    }

    // operator[]
    reference operator[](size_type pos) {
        return arr[pos];
    }

    const_reference operator[](size_type pos) const {
        return arr[pos];
    }
    // Copy assignment operator
    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            allocator_type().deallocate(arr, capacity);
            arr = allocator_type().allocate(other.capacity);
            capacity = other.capacity;
            current = other.current;
            std::copy(other.arr, other.arr + other.current, arr);
        }
        return *this;
    }

    // assign
    void assign(size_type count, const T& value) {
        if (count > capacity) {
            allocator_type().deallocate(arr, capacity);
            arr = allocator_type().allocate(count);
            capacity = count;
        }
        current = count;
        std::fill(arr, arr + count, value);
    }

    // assign_range
    template <typename InputIt>
    void assign(InputIt first, InputIt last) {
        size_type count = std::distance(first, last);
        if (count > capacity) {
            allocator_type().deallocate(arr, capacity);
            arr = allocator_type().allocate(count);
            capacity = count;
        }
        current = count;
        std::copy(first, last, arr);
    }

    // get_allocator
    allocator_type get_allocator() const noexcept {
        return allocator_type();
    }

    // front
    reference front() {
        return arr[0];
    }

    const_reference front() const {
        return arr[0];
    }

    // back
    reference back() {
        return arr[current - 1];
    }

    const_reference back() const {
        return arr[current - 1];
    }

    // data
    T* data() noexcept {
        return arr;
    }

    const T* data() const noexcept {
        return arr;
    }

    // begin
    iterator begin() noexcept {
        return arr;
    }

    const_iterator begin() const noexcept {
        return arr;
    }

    const_iterator cbegin() const noexcept {
        return arr;
    }

    // end
    iterator end() noexcept {
        return arr + current;
    }

    const_iterator end() const noexcept {
        return arr + current;
    }

    const_iterator cend() const noexcept {
        return arr + current;
    }

    // rbegin
    reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    // rend
    reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(begin());
    }

    const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(begin());
    }

    // empty
    bool empty() const noexcept {
        return current == 0;
    }

    // size
    size_type size() const noexcept {
        return current;
    }

    // max_size
    size_type max_size() const noexcept {
        return allocator_type().max_size();
    }

    // reserve
    void reserve(size_type new_cap) {
        if (new_cap > capacity) {
            T* new_arr = allocator_type().allocate(new_cap);
            std::copy(arr, arr + current, new_arr);
            allocator_type().deallocate(arr, capacity);
            arr = new_arr;
            capacity = new_cap;
        }
    }

    // capacity
    size_type capacity() const noexcept {
        return capacity;
    }

    // shrink_to_fit
    void shrink_to_fit() {
        if (capacity > current) {
            T* new_arr = allocator_type().allocate(current);
            std::copy(arr, arr + current, new_arr);
            allocator_type().deallocate(arr, capacity);
            arr = new_arr;
            capacity = current;
        }
    }
    
};