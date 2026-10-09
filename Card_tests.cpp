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

TEST(test_operator1){ // check operator <<
    std::ostringstream output1;
    Card c1(JACK, DIAMONDS);
    output1 << c1;
    std::string output1_correct = "Jack of Diamonds";
    ASSERT_EQUAL(output1.str(), output1_correct);

    std::ostringstream output2;
    Card c2(FIVE, CLUBS);
    output2 << c2;
    std::string output2_correct = "Five of Clubs";
    ASSERT_EQUAL(output2.str(), output2_correct);

    std::ostringstream output3;
    Card c3(ACE, DIAMONDS);
    output3 << c3;
    std::string output3_correct = "Ace of Diamonds";
    ASSERT_EQUAL(output3.str(), output3_correct);
}

TEST(test_operator2){ //test operator >>
    std::string input1 = "Jack of Diamonds";
    std::istringstream ss_input1(input1);
    Card c1(JACK, DIAMONDS);
    Card c_test;
    ss_input1 >> c_test;
    ASSERT_EQUAL(c1, c_test);

    std::string input2 = "Five of Spades";
    std::istringstream ss_input2(input2);
    ss_input2 >> c_test;
    Card c2(FIVE, SPADES);
    ASSERT_EQUAL(c_test, c2);
}

TEST(test_operator3){ // test < and > and >= and <= and !=
    Card c1(JACK, DIAMONDS);
    Card c2(JACK, CLUBS);
    Card c3(JACK, HEARTS);
    Card c4(JACK, SPADES);

    Card c5(ACE, DIAMONDS);
    Card c6(ACE, CLUBS);
    Card c7(ACE, HEARTS);
    Card c8(ACE, SPADES);
    
    Card c9(FIVE, SPADES);
    Card c10(KING, HEARTS);
    Card c11(NINE, CLUBS);
    Card c12(SIX, DIAMONDS);

    ASSERT_TRUE(c1 > c2);
    ASSERT_FALSE(c1 < c2);
    ASSERT_TRUE(c1 >= c2);
    ASSERT_FALSE(c1 <= c2);
    ASSERT_FALSE(c2 > c1);
    ASSERT_TRUE(c2 < c1);
    ASSERT_FALSE(c2 >= c1);
    ASSERT_TRUE(c2 <= c1);
    ASSERT_TRUE(c2 != c1);

    ASSERT_TRUE(c3 > c4);
    ASSERT_FALSE(c3 < c4);
    ASSERT_TRUE(c3 >= c4);
    ASSERT_FALSE(c3 <= c4);
    ASSERT_FALSE(c4 > c3);
    ASSERT_TRUE(c4 < c3);
    ASSERT_FALSE(c4 >= c3);
    ASSERT_TRUE(c4 <= c3);
    ASSERT_TRUE(c4 != c3);

    ASSERT_TRUE(c2 > c4);
    ASSERT_FALSE(c2 < c4);
    ASSERT_TRUE(c2 >= c4);
    ASSERT_FALSE(c2 <= c4);
    ASSERT_FALSE(c4 > c2);
    ASSERT_TRUE(c4 < c2);
    ASSERT_FALSE(c4 >= c2);
    ASSERT_TRUE(c4 <= c2);
    ASSERT_TRUE(c4 != c2);

    ASSERT_TRUE(c6 > c8);
    ASSERT_FALSE(c6 < c8);
    ASSERT_TRUE(c6 >= c8);
    ASSERT_FALSE(c6 <= c8);
    ASSERT_FALSE(c8 > c6);
    ASSERT_TRUE(c8 < c6);
    ASSERT_FALSE(c8 >= c6);
    ASSERT_TRUE(c8 <= c6);
    ASSERT_TRUE(c8 != c6);

    ASSERT_FALSE(c3 > c7);
    ASSERT_TRUE(c3 < c7);
    ASSERT_FALSE(c3 >= c7);
    ASSERT_TRUE(c3 <= c7);
    ASSERT_TRUE(c7 > c3);
    ASSERT_FALSE(c7 < c3);
    ASSERT_TRUE(c7 >= c3);
    ASSERT_FALSE(c7 <= c3);
    ASSERT_TRUE(c7 != c3);

    ASSERT_FALSE(c9 > c11);
    ASSERT_TRUE(c9 < c11);
    ASSERT_FALSE(c9 >= c11);
    ASSERT_TRUE(c9 <= c11);
    ASSERT_TRUE(c11 > c9);
    ASSERT_FALSE(c11 < c9);
    ASSERT_TRUE(c11 >= c9);
    ASSERT_FALSE(c11 <= c9);
    ASSERT_TRUE(c11 != c9);
}

TEST(test_operator4){ // check==
    Card c1(JACK, DIAMONDS);
    Card c2(JACK, DIAMONDS);
    Card c3(ACE, HEARTS);
    Card c4(ACE, HEARTS);
    Card c5(JACK, HEARTS);
    ASSERT_TRUE(c1==c2);
    ASSERT_TRUE(c3==c4);
    ASSERT_FALSE(c1==c3);
    ASSERT_FALSE(c2==c5);
    ASSERT_FALSE(c1==c5);
}

TEST(test_suit_next){
    ASSERT_EQUAL(Suit_next(CLUBS), SPADES);
    ASSERT_EQUAL(Suit_next(HEARTS), DIAMONDS);
    ASSERT_EQUAL(Suit_next(DIAMONDS), HEARTS);
    ASSERT_EQUAL(Suit_next(SPADES), CLUBS);
}

TEST(card_less1){
    Card c1(JACK, DIAMONDS);
    Card c2(JACK, CLUBS);
    Card c3(JACK, HEARTS);
    Card c4(JACK, SPADES);

    Card c5(ACE, DIAMONDS);
    Card c6(ACE, CLUBS);
    Card c7(ACE, HEARTS);
    Card c8(ACE, SPADES);
    
    Card c9(FIVE, SPADES);
    Card c10(KING, HEARTS);
    Card c11(NINE, CLUBS);
    Card c12(SIX, DIAMONDS);

    // Power of right Bower
    ASSERT_TRUE(Card_less(c2, c1, DIAMONDS));
    ASSERT_FALSE(Card_less(c1, c2, DIAMONDS));

    ASSERT_TRUE(Card_less(c2, c4, SPADES));
    ASSERT_FALSE(Card_less(c4, c2, SPADES));

    ASSERT_TRUE(Card_less(c5, c4, SPADES));
    ASSERT_FALSE(Card_less(c4, c5, SPADES));

    ASSERT_TRUE(Card_less(c3, c1, DIAMONDS));
    ASSERT_FALSE(Card_less(c1, c3, DIAMONDS));

    ASSERT_TRUE(Card_less(c4, c1, DIAMONDS));
    ASSERT_FALSE(Card_less(c1, c4, DIAMONDS));

    ASSERT_TRUE(Card_less(c5, c1, DIAMONDS));
    ASSERT_FALSE(Card_less(c1, c5, DIAMONDS));

    ASSERT_TRUE(Card_less(c6, c1, DIAMONDS));
    ASSERT_FALSE(Card_less(c1, c6, DIAMONDS));

    ASSERT_TRUE(Card_less(c10, c1, DIAMONDS));
    ASSERT_FALSE(Card_less(c1, c10, DIAMONDS));

    //Power of left bower
    ASSERT_TRUE(Card_less(c2, c3, DIAMONDS));
    ASSERT_FALSE(Card_less(c3, c2, DIAMONDS));

    ASSERT_TRUE(Card_less(c5, c2, SPADES));
    ASSERT_FALSE(Card_less(c2, c5, SPADES));

    ASSERT_TRUE(Card_less(c4, c3, DIAMONDS));
    ASSERT_FALSE(Card_less(c3, c4, DIAMONDS));

    ASSERT_TRUE(Card_less(c7, c3, DIAMONDS));
    ASSERT_FALSE(Card_less(c3, c7, DIAMONDS));

    ASSERT_TRUE(Card_less(c8, c3, DIAMONDS));
    ASSERT_FALSE(Card_less(c3, c8, DIAMONDS));

    ASSERT_TRUE(Card_less(c11, c3, DIAMONDS));
    ASSERT_FALSE(Card_less(c3, c11, DIAMONDS));

    ASSERT_FALSE(Card_less(c1, c1, DIAMONDS));
    ASSERT_FALSE(Card_less(c3, c3, DIAMONDS));
    ASSERT_FALSE(Card_less(c7, c7, DIAMONDS));

    // show that any card in trump is higher than any other card
    ASSERT_TRUE(Card_less(c7, c11, CLUBS));
    ASSERT_FALSE(Card_less(c11, c7, CLUBS));

    // For cards in trump, ranking still matters
    ASSERT_TRUE(Card_less(c11, c6, CLUBS));
    ASSERT_FALSE(Card_less(c6, c11, CLUBS));

    // OUTSIDE OF TRUMP, THE NORMAL RANKINGS STILL HOLD
    ASSERT_TRUE(Card_less(c1, c7, CLUBS));
    ASSERT_FALSE(Card_less(c7, c1, CLUBS));

    ASSERT_TRUE(Card_less(c6, c5, HEARTS));
    ASSERT_FALSE(Card_less(c5, c6, HEARTS));
}

TEST(card_less2){
    Card c1(JACK, DIAMONDS);
    Card c2(JACK, CLUBS);
    Card c3(JACK, HEARTS);
    Card c4(JACK, SPADES);

    Card c5(ACE, DIAMONDS);
    Card c6(ACE, CLUBS);
    Card c7(ACE, HEARTS);
    Card c8(ACE, SPADES);
    
    Card c9(FIVE, SPADES);
    Card c10(KING, HEARTS);
    Card c11(NINE, CLUBS);
    Card c12(SIX, DIAMONDS);

    // Power of right bower
    ASSERT_TRUE(Card_less(c2, c4, c10, SPADES)); // led: hearts trump: spades
    ASSERT_FALSE(Card_less(c4, c2, c10, SPADES));

    ASSERT_TRUE(Card_less(c8, c4, c10, SPADES));
    ASSERT_FALSE(Card_less(c4, c8, c10, SPADES));

    ASSERT_TRUE(Card_less(c9, c4, c10, SPADES));
    ASSERT_FALSE(Card_less(c4, c9, c10, SPADES));

    ASSERT_TRUE(Card_less(c7, c4, c10, SPADES));
    ASSERT_FALSE(Card_less(c4, c7, c10, SPADES));

    ASSERT_TRUE(Card_less(c10, c4, c10, SPADES));
    ASSERT_FALSE(Card_less(c4, c10, c10, SPADES));

    ASSERT_TRUE(Card_less(c12, c4, c10, SPADES));
    ASSERT_FALSE(Card_less(c4, c12, c10, SPADES));

    ASSERT_TRUE(Card_less(c1, c3, c11, HEARTS)); // led: clubs trump: hearts
    ASSERT_FALSE(Card_less(c3, c1, c11, HEARTS));
    ASSERT_TRUE(Card_less(c6, c3, c11, HEARTS)); 
    ASSERT_FALSE(Card_less(c3, c6, c11, HEARTS));


    //Power of left bower
    ASSERT_TRUE(Card_less(c8, c2, c10, SPADES));  // led: hearts trump: spades
    ASSERT_FALSE(Card_less(c2, c8, c10, SPADES));

    ASSERT_TRUE(Card_less(c9, c2, c10, SPADES));
    ASSERT_FALSE(Card_less(c2, c9, c10, SPADES));

    ASSERT_TRUE(Card_less(c7, c2, c10, SPADES));
    ASSERT_FALSE(Card_less(c2, c7, c10, SPADES));

    ASSERT_TRUE(Card_less(c10, c2, c10, SPADES));
    ASSERT_FALSE(Card_less(c2, c10, c10, SPADES));

    ASSERT_TRUE(Card_less(c12, c2, c10, SPADES));
    ASSERT_FALSE(Card_less(c2, c12, c10, SPADES));

    ASSERT_FALSE(Card_less(c1, c1, c10, DIAMONDS));
    ASSERT_FALSE(Card_less(c3, c3, c10, DIAMONDS));
    ASSERT_FALSE(Card_less(c7, c7, c10, DIAMONDS));

    ASSERT_TRUE(Card_less(c6, c1, c11, HEARTS)); // led: clubs trump: hearts
    ASSERT_FALSE(Card_less(c1, c6, c11, HEARTS));

    Card AS(ACE, SPADES);
    Card KS(KING, SPADES);
    Card QS(QUEEN, SPADES);
    Card JS(JACK, SPADES);
    Card NINES(NINE, SPADES);
    
    Card AH(ACE, HEARTS);
    Card KH(KING, HEARTS);
    Card QH(QUEEN, HEARTS);
    Card NINEH(NINE, HEARTS);

    Card AC(ACE, CLUBS);
    Card KC(KING, CLUBS);
    Card QC(QUEEN, CLUBS);
    Card NINEC(NINE, CLUBS);

    Card AD(ACE, DIAMONDS);
    Card KD(KING, DIAMONDS);
    Card QD(QUEEN, DIAMONDS);
    Card NINED(NINE, DIAMONDS);

    // Trump suit more powerful than led suit
    ASSERT_TRUE(Card_less(AH, QS, c10, SPADES)); // led: hearts trump: spades
    ASSERT_FALSE(Card_less(QS, AH, c10, SPADES));

    ASSERT_TRUE(Card_less(QH, KS, c10, SPADES));
    ASSERT_FALSE(Card_less(KS, QH, c10, SPADES));

    // Trump suit more powerful than ordinary cards
    ASSERT_TRUE(Card_less(AC, NINEH, AD, HEARTS)); // led: diamonds trump: hearts
    ASSERT_FALSE(Card_less(NINEH, AC, AD, HEARTS));

    // WITHIN TRUMP, ORDINARY STRUCTURE IS FOLLOWED
    ASSERT_TRUE(Card_less(NINED, KD, KS, DIAMONDS)); // led: SPADES trump: dIAMONDS
    ASSERT_FALSE(Card_less(KD, NINED, KS, DIAMONDS));

    // IF TRUMP AND LED ARE THE SAME
    ASSERT_TRUE(Card_less(NINEH, KH, KH, HEARTS)); // led: HEARTS trump: HEARTS
    ASSERT_FALSE(Card_less(KH, NINEH, KH, HEARTS));

    ASSERT_TRUE(Card_less(KS, JS, KS, SPADES)); // led: SPADES trump: sPADES
    ASSERT_FALSE(Card_less(JS, KS, KS, SPADES));

    //LED ARE MORE POWERFUL THAN ORDINARY CARDS
    ASSERT_TRUE(Card_less(AD, NINEH, NINEH, CLUBS)); // led: hearts trump: CLUBS
    ASSERT_FALSE(Card_less(NINEH, AD, NINEH, CLUBS));
    ASSERT_TRUE(Card_less(KS, AH, NINEH, CLUBS)); // led: hearts trump: CLUBS
    ASSERT_FALSE(Card_less(AH, KS, NINEH, CLUBS));

    //WITHIN LED, ORDINARY STRUCTURE FOLLOWED
    ASSERT_TRUE(Card_less(NINED, KD, KD, SPADES)); // led: DIAMONDS trump: SPADES
    ASSERT_FALSE(Card_less(KD, NINED, KD, SPADES));

    //OUTSIDE OF LED AND TRUMP, WE FOLLOW NORMAL STRUCTURE
    ASSERT_TRUE(Card_less(NINEC, KC, KS, DIAMONDS)); // led: DIAMONDS trump: SPADES
    ASSERT_FALSE(Card_less(KC, NINEC, KS, DIAMONDS));
    ASSERT_FALSE(Card_less(KH, NINEH, KS, DIAMONDS));
}