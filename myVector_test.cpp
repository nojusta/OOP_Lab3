#include <gtest/gtest.h>
#include <type_traits>
#include "myVector.h"

TEST(MyVectorTest, MemberTypes) { // Vienas testas, kuris testuoja visus member types
    MyVector<int> vec;
    // value_type
    static_assert(std::is_same<decltype(vec)::value_type, int>::value, "value_type should be int");
    // allocator_type
    static_assert(std::is_same<decltype(vec)::allocator_type, std::allocator<int>>::value, "allocator_type should be std::allocator<int>");
    // size_type
    static_assert(std::is_same<decltype(vec)::size_type, std::size_t>::value, "size_type should be std::size_t");
    // difference_type
    static_assert(std::is_same<decltype(vec)::difference_type, std::ptrdiff_t>::value, "difference_type should be std::ptrdiff_t");
    // reference
    static_assert(std::is_same<decltype(vec)::reference, int&>::value, "reference should be int&");
    // const_reference
    static_assert(std::is_same<decltype(vec)::const_reference, const int&>::value, "const_reference should be const int&");
    // pointer
    static_assert(std::is_same<decltype(vec)::pointer, int*>::value, "pointer should be int*");
    // const_pointer
    static_assert(std::is_same<decltype(vec)::const_pointer, const int*>::value, "const_pointer should be const int*");
    // iterator
    static_assert(std::is_same<decltype(vec)::iterator, MyVector<int>::iterator>::value, "iterator should be MyVector<int>::iterator");
    // const_iterator
    static_assert(std::is_same<decltype(vec)::const_iterator, MyVector<int>::const_iterator>::value, "const_iterator should be MyVector<int>::const_iterator");
    // reverse_iterator
    static_assert(std::is_same<decltype(vec)::reverse_iterator, std::reverse_iterator<MyVector<int>::iterator>>::value, "reverse_iterator should be std::reverse_iterator<MyVector<int>::iterator>");
    // const_reverse_iterator
    static_assert(std::is_same<decltype(vec)::const_reverse_iterator, std::reverse_iterator<MyVector<int>::const_iterator>>::value, "const_reverse_iterator should be std::reverse_iterator<MyVector<int>::const_iterator>");
}

TEST(MyVectorTest, Constructor) {
    MyVector<int> vec;
    EXPECT_EQ(vec.size(), 0);
}

TEST(MyVectorTest, Destructor) {
    MyVector<int>* vec = new MyVector<int>();
    vec->push_back(1);
    delete vec;
}

TEST(MyVectorTest, OperatorAssign) {
    MyVector<int> vec1;
    vec1.push_back(1);
    MyVector<int> vec2;
    vec2 = vec1;
    EXPECT_EQ(vec2.size(), 1);
    EXPECT_EQ(vec2[0], 1);
}

TEST(MyVectorTest, Assign) {
    MyVector<int> vec;
    std::vector<int> values(5, 10);
    vec.assign(values.begin(), values.end());
    EXPECT_EQ(vec.size(), 5);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(vec[i], 10);
    }
}

TEST(MyVectorTest, AssignRange) {
    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    MyVector<int> vec;
    vec.assign(arr.begin(), arr.end());
    EXPECT_EQ(vec.size(), 5);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(vec[i], arr[i]);
    }
}

TEST(MyVectorTest, GetAllocator) {
    MyVector<int> vec;
    std::allocator<int> alloc = vec.get_allocator();
    int* p = alloc.allocate(1);  // allocate an int
    alloc.deallocate(p, 1);  // deallocate it
}

TEST(MyVectorTest, At) {
    MyVector<int> vec;
    vec.push_back(10);
    EXPECT_EQ(vec.at(0), 10);
    EXPECT_THROW(vec.at(1), std::out_of_range);
}

TEST(MyVectorTest, OperatorSquareBrackets) {
    MyVector<int> vec;
    vec.push_back(10);
    EXPECT_EQ(vec[0], 10);
}

TEST(MyVectorTest, Front) {
    MyVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    EXPECT_EQ(vec.front(), 10);
}

TEST(MyVectorTest, Back) {
    MyVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    EXPECT_EQ(vec.back(), 20);
}

TEST(MyVectorTest, Data) {
    MyVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    int* data = vec.data();
    EXPECT_EQ(data[0], 10);
    EXPECT_EQ(data[1], 20);
}

TEST(MyVectorTest, Begin) {
    MyVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    MyVector<int>::iterator it = vec.begin();
    EXPECT_EQ(*it, 10);
}

TEST(MyVectorTest, CBegin) {
    MyVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    MyVector<int>::const_iterator it = vec.cbegin();
    EXPECT_EQ(*it, 10);
}

TEST(MyVectorTest, End) {
    MyVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    MyVector<int>::iterator it = vec.end();
    EXPECT_EQ(*(--it), 20);
}

TEST(MyVectorTest, CEnd) {
    MyVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    MyVector<int>::const_iterator it = vec.cend();
    EXPECT_EQ(*(--it), 20);
}

TEST(MyVectorTest, RBegin) {
    MyVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    MyVector<int>::reverse_iterator it = vec.rbegin();
    EXPECT_EQ(*it, 20);
}

TEST(MyVectorTest, CRBegin) {
    MyVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    MyVector<int>::const_reverse_iterator it = vec.crbegin();
    EXPECT_EQ(*it, 20);
}

TEST(MyVectorTest, REnd) {
    MyVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    MyVector<int>::reverse_iterator it = vec.rend();
    EXPECT_EQ(*(--it), 10);
}

TEST(MyVectorTest, CREnd) {
    MyVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    MyVector<int>::const_reverse_iterator it = vec.crend();
    EXPECT_EQ(*(--it), 10);
}

TEST(MyVectorTest, Empty) {
    MyVector<int> vec;
    EXPECT_TRUE(vec.empty());
    vec.push_back(10);
    EXPECT_FALSE(vec.empty());
}

TEST(MyVectorTest, Size) {
    MyVector<int> vec;
    EXPECT_EQ(vec.size(), 0);
    vec.push_back(10);
    EXPECT_EQ(vec.size(), 1);
}

TEST(MyVectorTest, MaxSize) {
    MyVector<int> vec;
    // Patikrina ar nekyla exceptionas
    EXPECT_NO_THROW(vec.max_size());
}

TEST(MyVectorTest, Reserve) {
    MyVector<int> vec;
    EXPECT_EQ(vec.getCapacity(), 0);
    vec.reserve(100);
    EXPECT_GE(vec.getCapacity(), 100);
}

TEST(MyVectorTest, Capacity) {
    MyVector<int> vec;
    vec.reserve(100);
    EXPECT_EQ(vec.getCapacity(), 100);
}

TEST(MyVectorTest, ShrinkToFit) {
    MyVector<int> vec;
    vec.reserve(100);
    vec.push_back(10);
    vec.shrink_to_fit();
    EXPECT_EQ(vec.getCapacity(), vec.size());
}

TEST(MyVectorTest, Clear) {
    MyVector<int> vec;
    vec.push_back(10);
    vec.clear();
    EXPECT_EQ(vec.size(), 0);
}

TEST(MyVectorTest, Insert) {
    MyVector<int> vec;
    vec.insert(vec.begin(), 10);
    EXPECT_EQ(vec[0], 10);
}

TEST(MyVectorTest, InsertRange) {
    MyVector<int> vec;
    std::vector<int> range = {10, 20, 30};
    vec.insert(vec.begin(), range.begin(), range.end());
    EXPECT_EQ(vec[0], 10);
    EXPECT_EQ(vec[1], 20);
    EXPECT_EQ(vec[2], 30);
}

TEST(MyVectorTest, Emplace) {
    MyVector<int> vec;
    vec.emplace(vec.begin(), 10);
    EXPECT_EQ(vec[0], 10);
}

TEST(MyVectorTest, Erase) {
    MyVector<int> vec;
    vec.push_back(10);
    vec.erase(vec.begin());
    EXPECT_EQ(vec.size(), 0);
}

TEST(MyVectorTest, PushBack) {
    MyVector<int> vec;
    vec.push_back(10);
    EXPECT_EQ(vec[0], 10);
}

TEST(MyVectorTest, EmplaceBack) {
    MyVector<int> vec;
    vec.emplace_back(10);
    EXPECT_EQ(vec[0], 10);
}

TEST(MyVectorTest, AppendRange) {
    MyVector<int> vec;
    std::vector<int> range = {10, 20, 30};
    vec.append_range(range.begin(), range.end());
    EXPECT_EQ(vec[0], 10);
    EXPECT_EQ(vec[1], 20);
    EXPECT_EQ(vec[2], 30);
}

TEST(MyVectorTest, PopBack) {
    MyVector<int> vec;
    vec.push_back(10);
    vec.pop_back();
    EXPECT_EQ(vec.size(), 0);
}

TEST(MyVectorTest, Resize) {
    MyVector<int> vec;
    vec.resize(10);
    EXPECT_EQ(vec.size(), 10);
}

TEST(MyVectorTest, Swap) {
    MyVector<int> vec1;
    vec1.push_back(10);
    MyVector<int> vec2;
    vec2.push_back(20);
    vec1.swap(vec2);
    EXPECT_EQ(vec1[0], 20);
    EXPECT_EQ(vec2[0], 10);
}

TEST(MyVectorTest, OperatorEqual) {
    MyVector<int> vec1;
    vec1.push_back(10);
    MyVector<int> vec2;
    vec2.push_back(10);
    EXPECT_TRUE(vec1 == vec2);
}

TEST(MyVectorTest, OperatorNotEqual) {
    MyVector<int> vec1;
    vec1.push_back(10);
    MyVector<int> vec2;
    vec2.push_back(20);
    EXPECT_TRUE(vec1 != vec2);
}

TEST(MyVectorTest, OperatorLessThan) {
    MyVector<int> vec1;
    vec1.push_back(10);
    MyVector<int> vec2;
    vec2.push_back(20);
    EXPECT_TRUE(vec1 < vec2);
}

TEST(MyVectorTest, OperatorLessThanOrEqual) {
    MyVector<int> vec1;
    vec1.push_back(10);
    MyVector<int> vec2;
    vec2.push_back(10);
    EXPECT_TRUE(vec1 <= vec2);
}

TEST(MyVectorTest, OperatorGreaterThan) {
    MyVector<int> vec1;
    vec1.push_back(20);
    MyVector<int> vec2;
    vec2.push_back(10);
    EXPECT_TRUE(vec1 > vec2);
}

TEST(MyVectorTest, OperatorGreaterThanOrEqual) {
    MyVector<int> vec1;
    vec1.push_back(20);
    MyVector<int> vec2;
    vec2.push_back(20);
    EXPECT_TRUE(vec1 >= vec2);
}

TEST(MyVectorTest, StdSwap) {
    MyVector<int> vec1;
    vec1.push_back(10);
    MyVector<int> vec2;
    vec2.push_back(20);
    std::swap(vec1, vec2);
    EXPECT_EQ(vec1[0], 20);
    EXPECT_EQ(vec2[0], 10);
}

TEST(MyVectorTest, NonMemberErase) {
    MyVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    auto it = std::find(vec.begin(), vec.end(), 10);
    if (it != vec.end()) {
        vec.erase(it);
    }
    EXPECT_EQ(vec[0], 20);
}

TEST(MyVectorTest, EraseIf) {
    MyVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    auto it = std::find_if(vec.begin(), vec.end(), [](int x){return x == 10;});
    if (it != vec.end()) {
        vec.erase(it);
    }
    EXPECT_EQ(vec[0], 20);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}