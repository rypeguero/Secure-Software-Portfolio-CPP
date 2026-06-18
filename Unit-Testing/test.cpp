//Ryan A Peguero CS-405 Unit Tests Assignment
#include "pch.h"

// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
//TEST_F(CollectionTest, AlwaysFail)
//{
// *   FAIL();
//}

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // verify empty
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0u);

    // add one entry
    add_entries(1);

    // verify not empty and size == 1
    EXPECT_FALSE(collection->empty());
    EXPECT_EQ(collection->size(), 1u);
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    // add five entries
    add_entries(5);

    // verify size == 5
    EXPECT_EQ(collection->size(), 5u);
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeIsGTEToSizeForVariousEntryCounts)
{
    auto check = [&](int count) {
        collection->clear();
        if (count > 0)
            add_entries(count);
        EXPECT_LE(collection->size(), collection->max_size());
    };

    check(0);
    check(1);
    check(5);
    check(10);
}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityIsGTEToSizeForVariousEntryCounts)
{
    auto check = [&](int count) {
        collection->clear();
        if (count > 0)
            add_entries(count);
        EXPECT_GE(collection->capacity(), collection->size());
    };

    check(0);
    check(1);
    check(5);
    check(10);
}

// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizeIncreasesCollection)
{
    // start with 0
    EXPECT_EQ(collection->size(), 0u);

    // resize up
    collection->resize(10);

    // verify increased size
    EXPECT_EQ(collection->size(), 10u);
}

// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizeDecreasesCollection)
{
    // prepare with entries
    collection->resize(10);
    ASSERT_EQ(collection->size(), 10u);

    // shrink
    collection->resize(5);

    // verify decreased size
    EXPECT_EQ(collection->size(), 5u);
}

// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizeToZeroClearsCollection)
{
    collection->resize(10);
    ASSERT_EQ(collection->size(), 10u);

    collection->resize(0);

    EXPECT_EQ(collection->size(), 0u);
    EXPECT_TRUE(collection->empty());
}

// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, ClearErasesCollection)
{
    add_entries(5);
    ASSERT_EQ(collection->size(), 5u);

    collection->clear();

    EXPECT_TRUE(collection->empty());
    EXPECT_EQ(collection->size(), 0u);
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseBeginEndErasesCollection)
{
    add_entries(7);
    ASSERT_EQ(collection->size(), 7u);

    collection->erase(collection->begin(), collection->end());

    EXPECT_TRUE(collection->empty());
    EXPECT_EQ(collection->size(), 0u);
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreasesCapacityButNotSize)
{
    auto initialCapacity = collection->capacity();

    collection->reserve(initialCapacity + 50);

    EXPECT_GE(collection->capacity(), initialCapacity + 50);
    EXPECT_EQ(collection->size(), 0u);
}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, AtThrowsOutOfRangeWhenIndexInvalid)
{
    // empty vector -> at(0) throws
    EXPECT_THROW(collection->at(0), std::out_of_range);

    // add some entries then use invalid index
    add_entries(3);
    ASSERT_EQ(collection->size(), 3u);
    EXPECT_THROW(collection->at(100), std::out_of_range);
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
// Positive: push_back and back consistency
TEST_F(CollectionTest, PushBackUpdatesBackElement)
{
    collection->push_back(42);
    EXPECT_EQ(collection->back(), 42);
    collection->push_back(7);
    EXPECT_EQ(collection->back(), 7);
}

// Negative: accessing front on empty vector is undefined; use at() to assert throwing, but front() can't be tested for throw.
// We'll test insert with invalid range using at() equivalent negative behavior: erase with invalid iterators should not be used; instead, we simulate by calling at() out of range.
TEST_F(CollectionTest, NegativeAccessUsingAtThrows)
{
    // Ensure empty and verify at() throws
    ASSERT_TRUE(collection->empty());
    EXPECT_THROW(collection->at(1), std::out_of_range);
}