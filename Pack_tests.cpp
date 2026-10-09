#include "Pack.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();

    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}

TEST(test_pack_deal_order) {
    Pack pack;

    Card c1 = pack.deal_one();
    Card c2 = pack.deal_one();
    Card c3 = pack.deal_one();

    ASSERT_EQUAL(NINE, c1.get_rank());
    ASSERT_EQUAL(SPADES, c1.get_suit());

    ASSERT_EQUAL(TEN, c2.get_rank());
    ASSERT_EQUAL(SPADES, c2.get_suit());

    ASSERT_EQUAL(JACK, c3.get_rank());
    ASSERT_EQUAL(SPADES, c3.get_suit());
}

TEST(test_pack_empty) {
    Pack pack;

    for (int i = 0; i < 24; ++i) {
        ASSERT_FALSE(pack.empty());
        pack.deal_one();
    }

    ASSERT_TRUE(pack.empty());
}

TEST(test_pack_reset) {
    Pack pack;

    pack.deal_one();
    pack.deal_one();

    pack.reset();

    Card first = pack.deal_one();

    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}

TEST(test_pack_suit_change) {
    Pack pack;

    for (int i = 0; i < 6; ++i) {
        pack.deal_one();
    }

    Card next = pack.deal_one();

    ASSERT_EQUAL(NINE, next.get_rank());
    ASSERT_EQUAL(HEARTS, next.get_suit());
}

TEST(test_pack_shuffle) {
    Pack pack;

    pack.shuffle();

    Card first = pack.deal_one();
    Card second = pack.deal_one();

    ASSERT_EQUAL(KING, first.get_rank());
    ASSERT_EQUAL(CLUBS, first.get_suit());

    ASSERT_EQUAL(JACK, second.get_rank());
    ASSERT_EQUAL(HEARTS, second.get_suit());
}

TEST_MAIN()