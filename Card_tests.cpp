#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

// Add more test cases here

TEST_MAIN()

TEST(test_ctor2){
    Card c;
    ASSERT_EQUAL(TWO, c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_suit());

    
}

TEST(test_get_suit){
    Card c2(JACK, DIAMONDS);
    ASSERT_EQUAL(JACK, c2.get_rank());
    ASSERT_EQUAL(DIAMONDS, c2.get_suit());
    ASSERT_EQUAL(HEARTS, c2.get_suit(HEARTS));
    Card c3(KING, DIAMONDS);
    ASSERT_EQUAL(KING, c3.get_rank());
    ASSERT_EQUAL(DIAMONDS, c3.get_suit());
    ASSERT_EQUAL(DIAMONDS, c3.get_suit(HEARTS));

    Card c4(JACK, HEARTS);
    ASSERT_EQUAL(JACK, c4.get_rank());
    ASSERT_EQUAL(HEARTS, c4.get_suit());
    ASSERT_EQUAL(DIAMONDS, c4.get_suit(DIAMONDS));
    Card c5(TWO, HEARTS);
    ASSERT_EQUAL(TWO, c5.get_rank());
    ASSERT_EQUAL(HEARTS, c5.get_suit());
    ASSERT_EQUAL(HEARTS, c5.get_suit(HEARTS));

    Card c6(JACK, SPADES);
    ASSERT_EQUAL(JACK, c6.get_rank());
    ASSERT_EQUAL(SPADES, c6.get_suit());
    ASSERT_EQUAL(CLUBS, c6.get_suit(CLUBS));
    Card c7(FIVE, SPADES);
    ASSERT_EQUAL(FIVE, c7.get_rank());
    ASSERT_EQUAL(SPADES, c7.get_suit());
    ASSERT_EQUAL(SPADES, c7.get_suit(CLUBS));

    Card c8(JACK, CLUBS);
    ASSERT_EQUAL(JACK, c8.get_rank());
    ASSERT_EQUAL(CLUBS, c8.get_suit());
    ASSERT_EQUAL(SPADES, c8.get_suit(SPADES));
    Card c9(ACE, CLUBS);
    ASSERT_EQUAL(ACE, c9.get_rank());
    ASSERT_EQUAL(CLUBS, c9.get_suit());
    ASSERT_EQUAL(CLUBS, c9.get_suit(SPADES));
    ASSERT_EQUAL(CLUBS, c9.get_suit(CLUBS));

    Card c10(JACK, HEARTS);
    ASSERT_EQUAL(HEARTS, c10.get_suit(HEARTS));
    ASSERT_EQUAL(HEARTS, c10.get_suit(SPADES));


}

TEST(test_is_right_bower){
    Card c(JACK, DIAMONDS);
    ASSERT_TRUE(c.is_right_bower(DIAMONDS));
    ASSERT_FALSE(c.is_right_bower(SPADES));
    ASSERT_FALSE(c.is_right_bower(HEARTS));
    ASSERT_FALSE(c.is_right_bower(CLUBS));

    Card c1(ACE, SPADES);
    ASSERT_FALSE(c1.is_right_bower(DIAMONDS));
    ASSERT_FALSE(c1.is_right_bower(SPADES));
    ASSERT_FALSE(c1.is_right_bower(HEARTS));
    ASSERT_FALSE(c1.is_right_bower(HEARTS));

    Card c2(JACK, SPADES);
    ASSERT_FALSE(c2.is_right_bower(CLUBS));
    ASSERT_TRUE(c2.is_right_bower(SPADES));
    ASSERT_FALSE(c2.is_right_bower(HEARTS));
    ASSERT_FALSE(c2.is_right_bower(DIAMONDS));

    Card c3(JACK, HEARTS);
    ASSERT_FALSE(c3.is_right_bower(CLUBS));
    ASSERT_FALSE(c3.is_right_bower(SPADES));
    ASSERT_FALSE(c3.is_right_bower(DIAMONDS));
    ASSERT_TRUE(c3.is_right_bower(HEARTS));

    Card c4(JACK, CLUBS);
    ASSERT_TRUE(c4.is_right_bower(CLUBS));
    ASSERT_FALSE(c4.is_right_bower(SPADES));
    ASSERT_FALSE(c4.is_right_bower(DIAMONDS));
    ASSERT_FALSE(c4.is_right_bower(HEARTS));
}

TEST(test_is_left_bower){
    Card c(JACK, DIAMONDS);
    ASSERT_FALSE(c.is_left_bower(DIAMONDS));
    ASSERT_FALSE(c.is_left_bower(SPADES));
    ASSERT_TRUE(c.is_left_bower(HEARTS));
    ASSERT_FALSE(c.is_left_bower(CLUBS));

    Card c1(ACE, SPADES);
    ASSERT_FALSE(c1.is_left_bower(DIAMONDS));
    ASSERT_FALSE(c1.is_left_bower(SPADES));
    ASSERT_FALSE(c1.is_left_bower(HEARTS));
    ASSERT_FALSE(c.is_left_bower(CLUBS));

    Card c2(JACK, SPADES);
    ASSERT_TRUE(c2.is_left_bower(CLUBS));
    ASSERT_FALSE(c2.is_left_bower(SPADES));
    ASSERT_FALSE(c2.is_left_bower(HEARTS));
    ASSERT_FALSE(c.is_left_bower(DIAMONDS));

    Card c3(JACK, HEARTS);
    ASSERT_FALSE(c3.is_left_bower(CLUBS));
    ASSERT_FALSE(c3.is_left_bower(SPADES));
    ASSERT_FALSE(c3.is_left_bower(HEARTS));
    ASSERT_TRUE(c3.is_left_bower(DIAMONDS));

    Card c4(JACK, CLUBS);
    ASSERT_TRUE(c4.is_left_bower(SPADES));
    ASSERT_FALSE(c4.is_left_bower(CLUBS));
    ASSERT_FALSE(c4.is_left_bower(HEARTS));
    ASSERT_FALSE(c4.is_left_bower(DIAMONDS));
}

TEST(test_is_trump){
    Card c(JACK, CLUBS);
    ASSERT_TRUE(c.is_trump(SPADES));
    ASSERT_TRUE(c.is_trump(CLUBS));
    ASSERT_FALSE(c.is_trump(DIAMONDS));
    ASSERT_FALSE(c.is_trump(HEARTS));

    Card c1(FIVE, CLUBS);
    ASSERT_FALSE(c1.is_trump(SPADES));
    ASSERT_TRUE(c1.is_trump(CLUBS));
    ASSERT_FALSE(c1.is_trump(DIAMONDS));
    ASSERT_FALSE(c1.is_trump(HEARTS));

    Card c2(JACK, SPADES);
    ASSERT_TRUE(c2.is_trump(SPADES));
    ASSERT_TRUE(c2.is_trump(CLUBS));
    ASSERT_FALSE(c2.is_trump(DIAMONDS));
    ASSERT_FALSE(c2.is_trump(HEARTS));

    Card c3(JACK, DIAMONDS);
    ASSERT_TRUE(c3.is_trump(HEARTS));
    ASSERT_TRUE(c3.is_trump(DIAMONDS));
    ASSERT_FALSE(c3.is_trump(CLUBS));
    ASSERT_FALSE(c3.is_trump(SPADES));

    Card c4(JACK, HEARTS);
    ASSERT_TRUE(c4.is_trump(HEARTS));
    ASSERT_TRUE(c4.is_trump(DIAMONDS));
    ASSERT_FALSE(c4.is_trump(CLUBS));
    ASSERT_FALSE(c4.is_trump(SPADES));
}

TEST(test_is_face_or_ace){
    Card c(ACE, HEARTS);
    ASSERT_TRUE(c.is_face_or_ace());
    Card c2(KING, DIAMONDS);
    ASSERT_TRUE(c2.is_face_or_ace());
    Card c3(QUEEN, SPADES);
    ASSERT_TRUE(c3.is_face_or_ace());
    Card c4(JACK, HEARTS);
    ASSERT_TRUE(c4.is_face_or_ace());
    Card c5(NINE, HEARTS);
    ASSERT_FALSE(c5.is_face_or_ace());
    Card c6(FIVE, HEARTS);
    ASSERT_FALSE(c6.is_face_or_ace());
}