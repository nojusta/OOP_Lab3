#include <cstddef>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <utility>

/**
 * @brief MyVector klasė, kurios funkcionalumas yra panašus į std::vector.
 *
 * @tparam T Elementų tipas
 * @tparam Allocator Skiriamosios atminties valdiklio tipas
 */
template <typename T, typename Allocator = std::allocator<T>>
class MyVector
{
public:
    // Member types
    /**
     * @brief Elementų tipas.
     */
    using value_type = T;

    /**
     * @brief Skiriamosios atminties valdiklio tipas.
     */
    using allocator_type = Allocator;

    /**
     * @brief Dydis, naudojamas vektoriuje.
     */
    using size_type = std::size_t;

    /**
     * @brief Skirtumas tarp dviejų iteratorių.
     */
    using difference_type = std::ptrdiff_t;

    /**
     * @brief Nuoroda į elementą.
     */
    using reference = value_type &;

    /**
     * @brief Nuoroda į konstantų elementą.
     */
    using const_reference = const value_type &;

    /**
     * @brief Nuoroda į elementą atmintyje.
     */
    using pointer = typename std::allocator_traits<Allocator>::pointer;

    /**
     * @brief Nuoroda į konstantų elementą atmintyje.
     */
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;

    /**
     * @brief Iteratorius per elementus.
     */
    using iterator = pointer;

    /**
     * @brief Iteratorius per konstantus elementus.
     */
    using const_iterator = const_pointer;

    /**
     * @brief Atvirkštinis iteratorius per elementus.
     */
    using reverse_iterator = std::reverse_iterator<iterator>;

    /**
     * @brief Atvirkštinis iteratorius per konstantus elementus.
     */
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
    allocator_type allocator;
    pointer arr;
    size_type capacity;
    size_type current;

    /**
     * @brief Naikina visus elementus masyve.
     *
     * Metodas naikina visus elementus masyve, naudojant std::allocator_traits<Allocator>::destroy.
     * Po naikinimo, nustato current reikšmę į 0.
     */
    void destroy_elements()
    {
        for (size_type i = 0; i < current; ++i)
        {
            std::allocator_traits<Allocator>::destroy(allocator, arr + i);
        }
        current = 0;
    }

public:
    /**
     * @brief Konstruktorius be parametrų, sukuriantis tuščią vektorių.
     */
    MyVector() : arr(nullptr), capacity(0), current(0) {}

    /**
     * @brief Destruktorius, atlaisvinantis vektoriaus resursus.
     */
    ~MyVector()
    {
        destroy_elements();
        if (arr)
        {
            allocator.deallocate(arr, capacity);
        }
    }

    /**
     * @brief Kopijavimo konstruktorius.
     *
     * @param other Kitas vektorius, iš kurio bus kopijuojami duomenys.
     */
    MyVector(const MyVector &other) : allocator(other.allocator), arr(nullptr), capacity(0), current(0)
    {
        if (other.current > 0)
        {
            arr = allocator.allocate(other.capacity);
            try
            {
                for (current = 0; current < other.current; ++current)
                {
                    std::allocator_traits<Allocator>::construct(allocator, arr + current, other.arr[current]);
                }
                capacity = other.capacity;
            }
            catch (...)
            {
                destroy_elements();
                allocator.deallocate(arr, other.capacity);
                throw;
            }
        }
    }

    /**
     * @brief Priskyrimo operatorius kopijavimui.
     *
     * @param other Kitas vektorius, iš kurio bus kopijuojami duomenys.
     * @return Grąžinamas pats objektas po priskyrimo.
     */
    MyVector &operator=(const MyVector &other)
    {
        if (this != &other)
        {
            MyVector temp(other);
            swap(temp);
        }
        return *this;
    }

    /**
     * @brief Perkėlimo konstruktorius.
     *
     * @param other Kitas vektorius, kurio duomenys bus perkelti.
     */
    MyVector(MyVector &&other) noexcept : allocator(std::move(other.allocator)), arr(other.arr), capacity(other.capacity), current(other.current)
    {
        other.arr = nullptr;
        other.capacity = 0;
        other.current = 0;
    }

    /**
     * @brief Priskyrimo operatorius perkėlimui.
     *
     * @param other Kitas vektorius, kurio duomenys bus perkelti.
     * @return Grąžinamas pats objektas po priskyrimo.
     */
    MyVector &operator=(MyVector &&other) noexcept
    {
        if (this != &other)
        {
            destroy_elements();
            if (arr)
            {
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

    /**
     * @brief Grąžina elementą nurodytoje pozicijoje su ribų tikrinimu.
     *
     * @param pos Elemento pozicija.
     * @return Nuoroda į elementą.
     * @throw std::out_of_range Jei pozicija yra už vektoriaus ribų.
     */
    reference at(size_type pos)
    {
        if (pos >= current)
        {
            throw std::out_of_range("MyVector::at");
        }
        return arr[pos];
    }

    /**
     * @brief Grąžina elementą nurodytoje pozicijoje su ribų tikrinimu (konstanta versija).
     *
     * @param pos Elemento pozicija.
     * @return Nuoroda į elementą.
     * @throw std::out_of_range Jei pozicija yra už vektoriaus ribų.
     */
    const_reference at(size_type pos) const
    {
        if (pos >= current)
        {
            throw std::out_of_range("MyVector::at");
        }
        return arr[pos];
    }

    /**
     * @brief Grąžina elementą nurodytoje pozicijoje.
     *
     * @param pos Elemento pozicija.
     * @return Nuoroda į elementą.
     */
    reference operator[](size_type pos)
    {
        return arr[pos];
    }

    /**
     * @brief Grąžina elementą nurodytoje pozicijoje (konstanta versija).
     *
     * @param pos Elemento pozicija.
     * @return Nuoroda į elementą.
     */
    const_reference operator[](size_type pos) const
    {
        return arr[pos];
    }

    /**
     * @brief Grąžina vektoriaus paskirstytoją.
     *
     * @return Paskirstytojo objektas.
     */
    allocator_type get_allocator() const noexcept
    {
        return allocator_type();
    }

    /**
     * @brief Grąžina pirmąjį vektoriaus elementą.
     *
     * @return Nuoroda į pirmąjį elementą.
     */
    reference front()
    {
        return arr[0];
    }

    /**
     * @brief Grąžina pirmąjį vektoriaus elementą (konstanta versija).
     *
     * @return Nuoroda į pirmąjį elementą.
     */
    const_reference front() const
    {
        return arr[0];
    }

    /**
     * @brief Grąžina paskutinį vektoriaus elementą.
     *
     * @return Nuoroda į paskutinį elementą.
     */
    reference back()
    {
        return arr[current - 1];
    }

    /**
     * @brief Grąžina paskutinį vektoriaus elementą (konstanta versija).
     *
     * @return Nuoroda į paskutinį elementą.
     */
    const_reference back() const
    {
        return arr[current - 1];
    }

    /**
     * @brief Grąžina žaliąjį vektoriaus masyvą.
     *
     * @return Rodyklė į masyvą.
     */
    T *data() noexcept
    {
        return arr;
    }

    /**
     * @brief Grąžina žaliąjį vektoriaus masyvą (konstanta versija).
     *
     * @return Rodyklė į masyvą.
     */
    const T *data() const noexcept
    {
        return arr;
    }

    /**
     * @brief Grąžina iteratorių į pirmąjį vektoriaus elementą.
     *
     * @return Iteratorius į pirmąjį elementą.
     */
    iterator begin() noexcept
    {
        return arr;
    }

    /**
     * @brief Grąžina iteratorių į pirmąjį vektoriaus elementą (konstanta versija).
     *
     * @return Iteratorius į pirmąjį elementą.
     */
    const_iterator begin() const noexcept
    {
        return arr;
    }

    /**
     * @brief Grąžina konstanta iteratorių į pirmąjį vektoriaus elementą.
     *
     * @return Konstanta iteratorius į pirmąjį elementą.
     */
    const_iterator cbegin() const noexcept
    {
        return arr;
    }

    /**
     * @brief Grąžina iteratorių į paskutinį vektoriaus elementą.
     *
     * @return Iteratorius į paskutinį elementą.
     */
    iterator end() noexcept
    {
        return arr + current;
    }

    /**
     * @brief Grąžina iteratorių į paskutinį vektoriaus elementą (konstanta versija).
     *
     * @return Iteratorius į paskutinį elementą.
     */
    const_iterator end() const noexcept
    {
        return arr + current;
    }

    /**
     * @brief Grąžina konstanta iteratorių į paskutinį vektoriaus elementą.
     *
     * @return Konstanta iteratorius į paskutinį elementą.
     */
    const_iterator cend() const noexcept
    {
        return arr + current;
    }

    /**
     * @brief Grąžina atvirkštinį iteratorių į pirmąjį vektoriaus elementą.
     *
     * @return Atvirkštinis iteratorius į pirmąjį elementą.
     */
    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(end());
    }

    /**
     * @brief Grąžina atvirkštinį iteratorių į pirmąjį vektoriaus elementą (konstanta versija).
     *
     * @return Atvirkštinis iteratorius į pirmąjį elementą.
     */
    const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }

    /**
     * @brief Grąžina konstanta atvirkštinį iteratorių į pirmąjį vektoriaus elementą.
     *
     * @return Konstanta atvirkštinis iteratorius į pirmąjį elementą.
     */
    const_reverse_iterator crbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }

    /**
     * @brief Grąžina atvirkštinį iteratorių į paskutinį vektoriaus elementą.
     *
     * @return Atvirkštinis iteratorius į paskutinį elementą.
     */
    reverse_iterator rend() noexcept
    {
        return reverse_iterator(begin());
    }

    /**
     * @brief Grąžina atvirkštinį iteratorių į paskutinį vektoriaus elementą (konstanta versija).
     *
     * @return Atvirkštinis iteratorius į paskutinį elementą.
     */
    const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

    /**
     * @brief Grąžina konstanta atvirkštinį iteratorių į paskutinį vektoriaus elementą.
     *
     * @return Konstanta atvirkštinis iteratorius į paskutinį elementą.
     */
    const_reverse_iterator crend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

    /**
     * @brief Patikrina, ar vektorius yra tuščias.
     *
     * @return True, jei vektorius yra tuščias, priešingu atveju False.
     */
    bool empty() const noexcept
    {
        return current == 0;
    }

    /**
     * @brief Grąžina elementų skaičių vektoriuje.
     *
     * @return Elementų skaičius.
     */
    size_type size() const noexcept
    {
        return current;
    }

    /**
     * @brief Grąžina maksimalų galimą vektoriaus dydį.
     *
     * @return Maksimalus elementų skaičius.
     */
    size_type max_size() const noexcept
    {
        return std::numeric_limits<size_t>::max() / sizeof(T);
    }

    /**
     * @brief Rezervuoja nurodytą vietos kiekį vektoriui.
     *
     * @param new_cap Nauja talpa.
     */
    void reserve(size_type new_cap)
    {
        if (new_cap > capacity)
        {
            pointer new_arr = allocator.allocate(new_cap);
            try
            {
                for (size_type i = 0; i < current; ++i)
                {
                    std::allocator_traits<Allocator>::construct(allocator, new_arr + i, std::move_if_noexcept(arr[i]));
                }
            }
            catch (...)
            {
                for (size_type i = 0; i < current; ++i)
                {
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

    /**
     * @brief Grąžina vektoriaus talpą.
     *
     * @return Talpa.
     */
    size_type getCapacity() const noexcept
    {
        return capacity;
    }

    /**
     * @brief Sumažina vektoriaus talpą iki dabartinio elemento skaičiaus.
     */
    void shrink_to_fit()
    {
        if (capacity > current)
        {
            pointer new_arr = allocator.allocate(current);
            try
            {
                for (size_type i = 0; i < current; ++i)
                {
                    std::allocator_traits<Allocator>::construct(allocator, new_arr + i, std::move_if_noexcept(arr[i]));
                }
            }
            catch (...)
            {
                for (size_type i = 0; i < current; ++i)
                {
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

    /**
     * @brief Išvalo vektoriaus turinį.
     */
    void clear() noexcept
    {
        destroy_elements();
    }

    /**
     * @brief Prideda elementą į vektoriaus pabaigą.
     *
     * @param value Elemento reikšmė.
     */
    void push_back(const T &value)
    {
        if (current == capacity)
        {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        std::allocator_traits<Allocator>::construct(allocator, arr + current, value);
        ++current;
    }

    /**
     * @brief Pašalina paskutinį vektoriaus elementą.
     *
     * @throw std::out_of_range Jei vektorius yra tuščias.
     */
    void pop_back()
    {
        if (current > 0)
        {
            --current;
            std::allocator_traits<Allocator>::destroy(allocator, arr + current);
        }
        else
        {
            throw std::out_of_range("Cannot pop_back from an empty MyVector");
        }
    }

    /**
     * @brief Pakeičia vektoriaus dydį.
     *
     * @param count Naujas dydis.
     * @param value Nauji elementai bus užpildyti šia reikšme.
     */
    void resize(size_type count, T value = T())
    {
        if (count > current)
        {
            if (count > capacity)
            {
                reserve(count);
            }
            for (size_type i = current; i < count; ++i)
            {
                std::allocator_traits<Allocator>::construct(allocator, arr + i, value);
            }
        }
        else
        {
            for (size_type i = count; i < current; ++i)
            {
                std::allocator_traits<Allocator>::destroy(allocator, arr + i);
            }
        }
        current = count;
    }

    /**
     * @brief Pakeičia šio vektoriaus turinį su kitu vektoriumi.
     *
     * @param other Kitas vektorius.
     */
    void swap(MyVector &other) noexcept
    {
        std::swap(arr, other.arr);
        std::swap(capacity, other.capacity);
        std::swap(current, other.current);
        std::swap(allocator, other.allocator);
    }

    /**
     * @brief Įterpia elementą nurodytoje pozicijoje.
     *
     * @param pos Pozicija, kurioje bus įterptas elementas.
     * @param value Įterpiamas elementas.
     * @return Iteratorius į įterptą elementą.
     */
    iterator insert(const_iterator pos, const T &value)
    {
        size_type index = std::distance(cbegin(), pos);
        if (current == capacity)
        {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        if (index < current)
        {
            std::move_backward(arr + index, arr + current, arr + current + 1);
        }
        std::allocator_traits<Allocator>::construct(allocator, arr + index, value);
        ++current;
        return arr + index;
    }

    /**
     * @brief Įterpia elementą nurodytoje pozicijoje su argumentais.
     *
     * @param pos Pozicija, kurioje bus įterptas elementas.
     * @param args Argumentai, naudojami elemento konstravimui.
     * @return Iteratorius į įterptą elementą.
     */
    template <typename... Args>
    iterator emplace(const_iterator pos, Args &&...args)
    {
        size_type index = std::distance(cbegin(), pos);
        if (current == capacity)
        {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        std::move_backward(arr + index, arr + current, arr + current + 1);
        arr[index] = T(std::forward<Args>(args)...);
        ++current;
        return arr + index;
    }

    /**
     * @brief Pašalina elementą nurodytoje pozicijoje.
     *
     * @param pos Pozicija, iš kurios bus pašalintas elementas.
     * @return Iteratorius į poziciją po pašalinto elemento.
     */
    iterator erase(const_iterator pos)
    {
        size_type index = std::distance(cbegin(), pos);
        std::allocator_traits<Allocator>::destroy(allocator, arr + index);
        std::move(arr + index + 1, arr + current, arr + index);
        --current;
        return arr + index;
    }

    /**
     * @brief Pakeičia vektoriaus turinį intervalu.
     *
     * @param first Pradžios iteratorius.
     * @param last Pabaigos iteratorius.
     */
    template <typename InputIt>
    void assign(InputIt first, InputIt last)
    {
        size_type count = std::distance(first, last);
        if (count > capacity)
        {
            clear();
            allocator.deallocate(arr, capacity);
            arr = allocator.allocate(count);
            capacity = count;
        }
        for (current = 0; current < count; ++current, ++first)
        {
            std::allocator_traits<Allocator>::construct(allocator, arr + current, *first);
        }
    }

    /**
     * @brief Pakeičia vektoriaus turinį nurodytu elementų skaičiumi.
     *
     * @param count Elementų skaičius.
     * @param value Elementų reikšmė.
     */
    void assign(size_type count, const T &value)
    {
        if (count > capacity)
        {
            clear();
            allocator.deallocate(arr, capacity);
            arr = allocator.allocate(count);
            capacity = count;
        }
        for (current = 0; current < count; ++current)
        {
            std::allocator_traits<Allocator>::construct(allocator, arr + current, value);
        }
    }

    /**
     * @brief Prideda elementą į vektoriaus pabaigą su argumentais.
     *
     * @param args Argumentai, naudojami elemento konstravimui.
     */
    template <typename... Args>
    void emplace_back(Args &&...args)
    {
        if (current == capacity)
        {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        std::allocator_traits<Allocator>::construct(allocator, arr + current, std::forward<Args>(args)...);
        ++current;
    }

    /**
     * @brief Prideda elementų intervalą į vektoriaus pabaigą.
     *
     * @param first Pradžios iteratorius.
     * @param last Pabaigos iteratorius.
     */
    template <typename InputIt>
    void append_range(InputIt first, InputIt last)
    {
        size_type count = std::distance(first, last);
        if (current + count > capacity)
        {
            reserve(current + count);
        }
        for (; first != last; ++first, ++current)
        {
            std::allocator_traits<Allocator>::construct(allocator, arr + current, *first);
        }
    }
};

/**
 * @brief Palygina du vektorius lygybės atžvilgiu.
 * 
 * @tparam T Elementų tipas.
 * @tparam Allocator Alokatoriaus tipas.
 * @param lhs Kairysis operandas.
 * @param rhs Dešinysis operandas.
 * @return true, jei vektoriai yra lygūs.
 * @return false, jei vektoriai nėra lygūs.
 */
template <typename T, typename Allocator>
bool operator==(const MyVector<T, Allocator> &lhs, const MyVector<T, Allocator> &rhs)
{
    return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

/**
 * @brief Palygina du vektorius nelygybės atžvilgiu.
 * 
 * @tparam T Elementų tipas.
 * @tparam Allocator Alokatoriaus tipas.
 * @param lhs Kairysis operandas.
 * @param rhs Dešinysis operandas.
 * @return true, jei vektoriai nėra lygūs.
 * @return false, jei vektoriai yra lygūs.
 */
template <typename T, typename Allocator>
bool operator!=(const MyVector<T, Allocator> &lhs, const MyVector<T, Allocator> &rhs)
{
    return !(lhs == rhs);
}

/**
 * @brief Palygina du vektorius mažiau operatoriaus atžvilgiu.
 * 
 * @tparam T Elementų tipas.
 * @tparam Allocator Alokatoriaus tipas.
 * @param lhs Kairysis operandas.
 * @param rhs Dešinysis operandas.
 * @return true, jei kairysis vektorius yra mažesnis už dešinįjį.
 * @return false, jei kairysis vektorius nėra mažesnis už dešinįjį.
 */
template <typename T, typename Allocator>
bool operator<(const MyVector<T, Allocator> &lhs, const MyVector<T, Allocator> &rhs)
{
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

/**
 * @brief Palygina du vektorius mažiau arba lygu operatoriaus atžvilgiu.
 * 
 * @tparam T Elementų tipas.
 * @tparam Allocator Alokatoriaus tipas.
 * @param lhs Kairysis operandas.
 * @param rhs Dešinysis operandas.
 * @return true, jei kairysis vektorius yra mažesnis arba lygus dešiniajam.
 * @return false, jei kairysis vektorius nėra mažesnis arba lygus dešiniajam.
 */
template <typename T, typename Allocator>
bool operator<=(const MyVector<T, Allocator> &lhs, const MyVector<T, Allocator> &rhs)
{
    return !(rhs < lhs);
}

/**
 * @brief Palygina du vektorius daugiau operatoriaus atžvilgiu.
 * 
 * @tparam T Elementų tipas.
 * @tparam Allocator Alokatoriaus tipas.
 * @param lhs Kairysis operandas.
 * @param rhs Dešinysis operandas.
 * @return true, jei kairysis vektorius yra didesnis už dešinįjį.
 * @return false, jei kairysis vektorius nėra didesnis už dešinįjį.
 */
template <typename T, typename Allocator>
bool operator>(const MyVector<T, Allocator> &lhs, const MyVector<T, Allocator> &rhs)
{
    return rhs < lhs;
}

/**
 * @brief Palygina du vektorius daugiau arba lygu operatoriaus atžvilgiu.
 * 
 * @tparam T Elementų tipas.
 * @tparam Allocator Alokatoriaus tipas.
 * @param lhs Kairysis operandas.
 * @param rhs Dešinysis operandas.
 * @return true, jei kairysis vektorius yra didesnis arba lygus dešiniajam.
 * @return false, jei kairysis vektorius nėra didesnis arba lygus dešiniajam.
 */
template <typename T, typename Allocator>
bool operator>=(const MyVector<T, Allocator> &lhs, const MyVector<T, Allocator> &rhs)
{
    return !(lhs < rhs);
}

/**
 * @brief Apkeitimo funkcija vektoriams.
 * 
 * @tparam T Elementų tipas.
 * @tparam Allocator Alokatoriaus tipas.
 * @param lhs Kairysis vektorius.
 * @param rhs Dešinysis vektorius.
 */
namespace std
{
    template <typename T, typename Allocator>
    void swap(MyVector<T, Allocator> &lhs, MyVector<T, Allocator> &rhs) noexcept
    {
        lhs.swap(rhs);
    }
}

/**
 * @brief Pašalina elementus, kurie atitinka predikato sąlygą.
 * 
 * @tparam T Elementų tipas.
 * @tparam Allocator Alokatoriaus tipas.
 * @tparam Pred Predikato tipas.
 * @param vec Vektorius.
 * @param pred Predikatas.
 */
template <typename T, typename Allocator, typename Pred>
void erase(MyVector<T, Allocator> &vec, Pred pred)
{
    vec.erase(std::remove_if(vec.begin(), vec.end(), pred), vec.end());
}

/**
 * @brief Pašalina elementus, kurie atitinka predikato sąlygą.
 * 
 * @tparam T Elementų tipas.
 * @tparam Allocator Alokatoriaus tipas.
 * @tparam Pred Predikato tipas.
 * @param vec Vektorius.
 * @param pred Predikatas.
 */
template <typename T, typename Allocator, typename Pred>
void erase_if(MyVector<T, Allocator> &vec, Pred pred)
{
    vec.erase(std::remove_if(vec.begin(), vec.end(), pred), vec.end());
}
