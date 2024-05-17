#include <cstddef>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <utility>

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
    allocator_type allocator;
    pointer arr;
    size_type capacity;
    size_type current;

    void destroy_elements() {
        for (size_type i = 0; i < current; ++i) {
            std::allocator_traits<Allocator>::destroy(allocator, arr + i);
        }
        current = 0;
    }

public:
    // Konstruktorius
    MyVector() : arr(nullptr), capacity(0), current(0) {}

    // Destruktorius
    ~MyVector() {
        destroy_elements();
        if (arr) {
            allocator.deallocate(arr, capacity);
        }
    }

    MyVector(const MyVector& other) : allocator(other.allocator), arr(nullptr), capacity(0), current(0) {
        if (other.current > 0) {
            arr = allocator.allocate(other.capacity);
            try {
                for (current = 0; current < other.current; ++current) {
                    std::allocator_traits<Allocator>::construct(allocator, arr + current, other.arr[current]);
                }
                capacity = other.capacity;
            } catch (...) {
                destroy_elements();
                allocator.deallocate(arr, other.capacity);
                throw;
            }
        }
    }

    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            MyVector temp(other);
            swap(temp);
        }
        return *this;
    }

    MyVector(MyVector&& other) noexcept : allocator(std::move(other.allocator)), arr(other.arr), capacity(other.capacity), current(other.current) {
        other.arr = nullptr;
        other.capacity = 0;
        other.current = 0;
    }

    MyVector& operator=(MyVector&& other) noexcept {
        if (this != &other) {
            destroy_elements();
            if (arr) {
                allocator.deallocate(arr, capacity);
            }

            allocator = std::move(other.allocator);
            arr = other.arr;
            capacity = other.capacity;
            current = other.current;

            other.arr = nullptr;
            other.capacity = 0;
            other.current = 0;
        }
        return *this;
    }

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

    reference operator[](size_type pos) {
        return arr[pos];
    }

    const_reference operator[](size_type pos) const {
        return arr[pos];
    }

    allocator_type get_allocator() const noexcept {
        return allocator_type();
    }

    reference front() {
        return arr[0];
    }

    const_reference front() const {
        return arr[0];
    }

    reference back() {
        return arr[current - 1];
    }

    const_reference back() const {
        return arr[current - 1];
    }

    T* data() noexcept {
        return arr;
    }

    const T* data() const noexcept {
        return arr;
    }

    iterator begin() noexcept {
        return arr;
    }

    const_iterator begin() const noexcept {
        return arr;
    }

    const_iterator cbegin() const noexcept {
        return arr;
    }

    iterator end() noexcept {
        return arr + current;
    }

    const_iterator end() const noexcept {
        return arr + current;
    }

    const_iterator cend() const noexcept {
        return arr + current;
    }

    reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(begin());
    }

    const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(begin());
    }

    bool empty() const noexcept {
        return current == 0;
    }

    size_type size() const noexcept {
        return current;
    }

    size_type max_size() const noexcept {
        return std::numeric_limits<size_t>::max() / sizeof(T);
    }

    void reserve(size_type new_cap) {
        if (new_cap > capacity) {
            pointer new_arr = allocator.allocate(new_cap);
            try {
                for (size_type i = 0; i < current; ++i) {
                    std::allocator_traits<Allocator>::construct(allocator, new_arr + i, std::move_if_noexcept(arr[i]));
                }
            } catch (...) {
                for (size_type i = 0; i < current; ++i) {
                    std::allocator_traits<Allocator>::destroy(allocator, new_arr + i);
                }
                allocator.deallocate(new_arr, new_cap);
                throw;
            }
            destroy_elements();
            allocator.deallocate(arr, capacity);
            arr = new_arr;
            capacity = new_cap;
        }
    }

    size_type getCapacity() const noexcept {
        return capacity;
    }

    void shrink_to_fit() {
        if (capacity > current) {
            pointer new_arr = allocator.allocate(current);
            try {
                for (size_type i = 0; i < current; ++i) {
                    std::allocator_traits<Allocator>::construct(allocator, new_arr + i, std::move_if_noexcept(arr[i]));
                }
            } catch (...) {
                for (size_type i = 0; i < current; ++i) {
                    std::allocator_traits<Allocator>::destroy(allocator, new_arr + i);
                }
                allocator.deallocate(new_arr, current);
                throw;
            }
            destroy_elements();
            allocator.deallocate(arr, capacity);
            arr = new_arr;
            capacity = current;
        }
    }

    void clear() noexcept {
        destroy_elements();
    }

    void push_back(const T& value) {
        if (current == capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        std::allocator_traits<Allocator>::construct(allocator, arr + current, value);
        ++current;
    }

    void pop_back() {
        if (current > 0) {
            --current;
            std::allocator_traits<Allocator>::destroy(allocator, arr + current);
        } else {
            throw std::out_of_range("Cannot pop_back from an empty MyVector");
        }
    }

    void resize(size_type count, T value = T()) {
        if (count > current) {
            if (count > capacity) {
                reserve(count);
            }
            for (size_type i = current; i < count; ++i) {
                std::allocator_traits<Allocator>::construct(allocator, arr + i, value);
            }
        } else {
            for (size_type i = count; i < current; ++i) {
                std::allocator_traits<Allocator>::destroy(allocator, arr + i);
            }
        }
        current = count;
    }

    void swap(MyVector& other) noexcept {
        std::swap(arr, other.arr);
        std::swap(capacity, other.capacity);
        std::swap(current, other.current);
        std::swap(allocator, other.allocator);
    }

    iterator insert(const_iterator pos, const T& value) {
        size_type index = std::distance(cbegin(), pos);
        if (current == capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        if (index < current) {
            std::move_backward(arr + index, arr + current, arr + current + 1);
        }
        std::allocator_traits<Allocator>::construct(allocator, arr + index, value);
        ++current;
        return arr + index;
    }

    // emplace
    template <typename... Args>
    iterator emplace(const_iterator pos, Args&&... args) {
        size_type index = std::distance(cbegin(), pos);
        if (current == capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        std::move_backward(arr + index, arr + current, arr + current + 1);
        arr[index] = T(std::forward<Args>(args)...);
        ++current;
        return arr + index;
    }

    iterator erase(const_iterator pos) {
        size_type index = std::distance(cbegin(), pos);
        std::allocator_traits<Allocator>::destroy(allocator, arr + index);
        std::move(arr + index + 1, arr + current, arr + index);
        --current;
        return arr + index;
    }

    template <typename InputIt>
    void assign(InputIt first, InputIt last) {
        size_type count = std::distance(first, last);
        if (count > capacity) {
            clear();
            allocator.deallocate(arr, capacity);
            arr = allocator.allocate(count);
            capacity = count;
        }
        for (current = 0; current < count; ++current, ++first) {
            std::allocator_traits<Allocator>::construct(allocator, arr + current, *first);
        }
    }

    void assign(size_type count, const T& value) {
        if (count > capacity) {
            clear();
            allocator.deallocate(arr, capacity);
            arr = allocator.allocate(count);
            capacity = count;
        }
        for (current = 0; current < count; ++current) {
            std::allocator_traits<Allocator>::construct(allocator, arr + current, value);
        }
    }

    template <typename... Args>
    void emplace_back(Args&&... args) {
        if (current == capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        std::allocator_traits<Allocator>::construct(allocator, arr + current, std::forward<Args>(args)...);
        ++current;
    }

    template <typename InputIt>
    void append_range(InputIt first, InputIt last) {
        size_type count = std::distance(first, last);
        if (current + count > capacity) {
            reserve(current + count);
        }
        for (; first != last; ++first, ++current) {
            std::allocator_traits<Allocator>::construct(allocator, arr + current, *first);
        }
    }
};

// Non-member functions
template <typename T, typename Allocator>
bool operator==(const MyVector<T, Allocator>& lhs, const MyVector<T, Allocator>& rhs) {
    return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T, typename Allocator>
bool operator!=(const MyVector<T, Allocator>& lhs, const MyVector<T, Allocator>& rhs) {
    return !(lhs == rhs);
}

template <typename T, typename Allocator>
bool operator<(const MyVector<T, Allocator>& lhs, const MyVector<T, Allocator>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T, typename Allocator>
bool operator<=(const MyVector<T, Allocator>& lhs, const MyVector<T, Allocator>& rhs) {
    return !(rhs < lhs);
}

template <typename T, typename Allocator>
bool operator>(const MyVector<T, Allocator>& lhs, const MyVector<T, Allocator>& rhs) {
    return rhs < lhs;
}

template <typename T, typename Allocator>
bool operator>=(const MyVector<T, Allocator>& lhs, const MyVector<T, Allocator>& rhs) {
    return !(lhs < rhs);
}

namespace std {
    template <typename T, typename Allocator>
    void swap(MyVector<T, Allocator>& lhs, MyVector<T, Allocator>& rhs) noexcept {
        lhs.swap(rhs);
    }
}

template <typename T, typename Allocator, typename Pred>
void erase(MyVector<T, Allocator>& vec, Pred pred) {
    vec.erase(std::remove_if(vec.begin(), vec.end(), pred), vec.end());
}

template <typename T, typename Allocator, typename Pred>
void erase_if(MyVector<T, Allocator>& vec, Pred pred) {
    vec.erase(std::remove_if(vec.begin(), vec.end(), pred), vec.end());
}
