
#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>
#include <sstream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_player_output) {
    Player * alice = Player_factory("Alice", "Simple");

    ostringstream os;
    os << *alice;
    ASSERT_EQUAL("Alice", os.str());

    delete alice;
}

TEST(test_make_trump_round1_yes) {
    Player *alice = Player_factory("Alice", "Simple");

    alice->add_card(Card(ACE, HEARTS));
    alice->add_card(Card(KING, HEARTS));
    alice->add_card(Card(NINE, CLUBS));
    alice->add_card(Card(TEN, SPADES));
    alice->add_card(Card(QUEEN, CLUBS));

    Suit order_up_suit = SPADES;

    bool result = alice->make_trump(
        Card(JACK, HEARTS), false, 1, order_up_suit);

    ASSERT_TRUE(result);
    ASSERT_EQUAL(HEARTS, order_up_suit);

    delete alice;
}

TEST(test_make_trump_round1_no) {
    Player *alice = Player_factory("Alice", "Simple");

    alice->add_card(Card(ACE, HEARTS));
    alice->add_card(Card(NINE, HEARTS));
    alice->add_card(Card(TEN, HEARTS));
    alice->add_card(Card(KING, CLUBS));
    alice->add_card(Card(QUEEN, SPADES));

    Suit order_up_suit = CLUBS;

    bool result = alice->make_trump(
        Card(JACK, HEARTS), false, 1, order_up_suit);

    ASSERT_FALSE(result);
    ASSERT_EQUAL(CLUBS, order_up_suit);

    delete alice;
}

TEST(test_make_trump_round1_dealer_no) {
    Player *alice = Player_factory("Alice", "Simple");

    alice->add_card(Card(ACE, HEARTS));
    alice->add_card(Card(NINE, HEARTS));
    alice->add_card(Card(TEN, HEARTS));
    alice->add_card(Card(KING, CLUBS));
    alice->add_card(Card(QUEEN, SPADES));

    Suit order_up_suit = CLUBS;

    bool result = alice->make_trump(
        Card(JACK, HEARTS), true, 1, order_up_suit);

    ASSERT_FALSE(result);
    ASSERT_EQUAL(CLUBS, order_up_suit);

    delete alice;
}

TEST(test_make_trump_round1_left_bower) {
    Player *alice = Player_factory("Alice", "Simple");

    alice->add_card(Card(JACK, HEARTS));
    alice->add_card(Card(QUEEN, DIAMONDS));
    alice->add_card(Card(NINE, SPADES));
    alice->add_card(Card(TEN, CLUBS));
    alice->add_card(Card(NINE, CLUBS));

    Suit order_up_suit = SPADES;

    bool result = alice->make_trump(
        Card(ACE, DIAMONDS), false, 1, order_up_suit);

    ASSERT_TRUE(result);
    ASSERT_EQUAL(DIAMONDS, order_up_suit);

    delete alice;
}

TEST(test_make_trump_round2_yes) {
    Player *alice = Player_factory("Alice", "Simple");

    alice->add_card(Card(QUEEN, DIAMONDS));
    alice->add_card(Card(NINE, SPADES));
    alice->add_card(Card(TEN, SPADES));
    alice->add_card(Card(NINE, CLUBS));
    alice->add_card(Card(TEN, CLUBS));

    Suit order_up_suit = SPADES;

    bool result = alice->make_trump(
        Card(ACE, HEARTS), false, 2, order_up_suit);

    ASSERT_TRUE(result);
    ASSERT_EQUAL(DIAMONDS, order_up_suit);

    delete alice;
}

TEST(test_make_trump_round2_no) {
    Player *alice = Player_factory("Alice", "Simple");

    alice->add_card(Card(NINE, DIAMONDS));
    alice->add_card(Card(TEN, DIAMONDS));
    alice->add_card(Card(NINE, CLUBS));
    alice->add_card(Card(TEN, CLUBS));
    alice->add_card(Card(ACE, SPADES));

    Suit order_up_suit = SPADES;

    bool result = alice->make_trump(
        Card(ACE, HEARTS), false, 2, order_up_suit);

    ASSERT_FALSE(result);
    ASSERT_EQUAL(SPADES, order_up_suit);

    delete alice;
}

TEST(test_make_trump_round2_dealer) {
    Player *alice = Player_factory("Alice", "Simple");

    alice->add_card(Card(NINE, DIAMONDS));
    alice->add_card(Card(TEN, DIAMONDS));
    alice->add_card(Card(NINE, CLUBS));
    alice->add_card(Card(TEN, CLUBS));
    alice->add_card(Card(NINE, SPADES));

    Suit order_up_suit = SPADES;

    bool result = alice->make_trump(
        Card(ACE, HEARTS), true, 2, order_up_suit);

    ASSERT_TRUE(result);
    ASSERT_EQUAL(DIAMONDS, order_up_suit);

    delete alice;
}

TEST(test_add_and_discard) {
    Player *alice = Player_factory("Alice", "Simple");

    alice->add_card(Card(NINE, SPADES));
    alice->add_card(Card(ACE, CLUBS));
    alice->add_card(Card(KING, CLUBS));
    alice->add_card(Card(QUEEN, CLUBS));
    alice->add_card(Card(TEN, CLUBS));

    alice->add_and_discard(Card(JACK, HEARTS));

    // Verify all five cards, not just the first two.
    ASSERT_EQUAL(Card(ACE, CLUBS), alice->lead_card(HEARTS));
    ASSERT_EQUAL(Card(KING, CLUBS), alice->lead_card(HEARTS));
    ASSERT_EQUAL(Card(QUEEN, CLUBS), alice->lead_card(HEARTS));
    ASSERT_EQUAL(Card(TEN, CLUBS), alice->lead_card(HEARTS));
    ASSERT_EQUAL(Card(JACK, HEARTS), alice->lead_card(HEARTS));

    delete alice;
}

TEST(test_discard_upcard) {
    Player *alice = Player_factory("Alice", "Simple");

    alice->add_card(Card(TEN, HEARTS));
    alice->add_card(Card(JACK, HEARTS));
    alice->add_card(Card(QUEEN, HEARTS));
    alice->add_card(Card(KING, HEARTS));
    alice->add_card(Card(ACE, HEARTS));

    alice->add_and_discard(Card(NINE, HEARTS));

    // The Nine upcard should be discarded, not the Ten in hand.
    ASSERT_EQUAL(Card(JACK, HEARTS), alice->lead_card(HEARTS));
    ASSERT_EQUAL(Card(ACE, HEARTS), alice->lead_card(HEARTS));
    ASSERT_EQUAL(Card(KING, HEARTS), alice->lead_card(HEARTS));
    ASSERT_EQUAL(Card(QUEEN, HEARTS), alice->lead_card(HEARTS));
    ASSERT_EQUAL(Card(TEN, HEARTS), alice->lead_card(HEARTS));

    delete alice;
}

TEST(test_lead_highest_non_trump) {
    Player *alice = Player_factory("Alice", "Simple");

    alice->add_card(Card(ACE, HEARTS));
    alice->add_card(Card(KING, CLUBS));
    alice->add_card(Card(QUEEN, SPADES));
    alice->add_card(Card(TEN, DIAMONDS));
    alice->add_card(Card(NINE, CLUBS));

    Card lead = alice->lead_card(HEARTS);

    ASSERT_EQUAL(Card(KING, CLUBS), lead);

    delete alice;
}

TEST(test_lead_all_trump) {
    Player *alice = Player_factory("Alice", "Simple");

    alice->add_card(Card(NINE, HEARTS));
    alice->add_card(Card(TEN, HEARTS));
    alice->add_card(Card(QUEEN, HEARTS));
    alice->add_card(Card(ACE, HEARTS));
    alice->add_card(Card(JACK, HEARTS));

    Card lead = alice->lead_card(HEARTS);

    ASSERT_EQUAL(Card(JACK, HEARTS), lead);

    delete alice;
}

TEST(test_play_follow_suit) {
    Player *alice = Player_factory("Alice", "Simple");

    alice->add_card(Card(NINE, CLUBS));
    alice->add_card(Card(ACE, CLUBS));
    alice->add_card(Card(KING, SPADES));
    alice->add_card(Card(TEN, HEARTS));
    alice->add_card(Card(QUEEN, DIAMONDS));

    Card played = alice->play_card(
        Card(TEN, CLUBS), HEARTS);

    ASSERT_EQUAL(Card(ACE, CLUBS), played);

    delete alice;
}

TEST(test_play_cannot_follow) {
    Player *alice = Player_factory("Alice", "Simple");

    alice->add_card(Card(NINE, HEARTS));
    alice->add_card(Card(KING, SPADES));
    alice->add_card(Card(ACE, DIAMONDS));
    alice->add_card(Card(QUEEN, SPADES));
    alice->add_card(Card(TEN, DIAMONDS));

    Card played = alice->play_card(
        Card(ACE, CLUBS), HEARTS);

    ASSERT_EQUAL(Card(TEN, DIAMONDS), played);

    delete alice;
}

TEST(test_play_left_bower) {
    Player *alice = Player_factory("Alice", "Simple");

    alice->add_card(Card(NINE, DIAMONDS));
    alice->add_card(Card(ACE, CLUBS));
    alice->add_card(Card(TEN, HEARTS));

    Card played = alice->play_card(
        Card(JACK, HEARTS), DIAMONDS);

    ASSERT_EQUAL(Card(NINE, DIAMONDS), played);

    delete alice;
}

TEST(test_add_discard_keep_upcard_all_trump) {
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(TEN, HEARTS));
    p->add_card(Card(QUEEN, HEARTS));
    p->add_card(Card(ACE, HEARTS));
    p->add_card(Card(JACK, DIAMONDS));
    p->add_and_discard(Card(KING, HEARTS));

    ASSERT_EQUAL(Card(JACK, DIAMONDS), p->lead_card(HEARTS));
    ASSERT_EQUAL(Card(ACE, HEARTS), p->lead_card(HEARTS));
    ASSERT_EQUAL(Card(KING, HEARTS), p->lead_card(HEARTS));
    ASSERT_EQUAL(Card(QUEEN, HEARTS), p->lead_card(HEARTS));
    ASSERT_EQUAL(Card(TEN, HEARTS), p->lead_card(HEARTS));
    delete p;
}

TEST(test_add_discard_nine_trump_beats_ten_nontrump) {
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(JACK, DIAMONDS));
    p->add_card(Card(ACE, SPADES));
    p->add_card(Card(QUEEN, CLUBS));
    p->add_card(Card(TEN, DIAMONDS));
    p->add_and_discard(Card(JACK, HEARTS));

    ASSERT_EQUAL(Card(ACE, SPADES), p->lead_card(HEARTS));
    ASSERT_EQUAL(Card(QUEEN, CLUBS), p->lead_card(HEARTS));
    ASSERT_EQUAL(Card(JACK, HEARTS), p->lead_card(HEARTS));
    ASSERT_EQUAL(Card(JACK, DIAMONDS), p->lead_card(HEARTS));
    ASSERT_EQUAL(Card(NINE, HEARTS), p->lead_card(HEARTS));
    delete p;
}

TEST(test_add_discard_left_bower_preserved) {
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(JACK, DIAMONDS));
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(ACE, SPADES));
    p->add_card(Card(KING, CLUBS));
    p->add_card(Card(TEN, SPADES));
    p->add_and_discard(Card(QUEEN, HEARTS));

    ASSERT_EQUAL(Card(ACE, SPADES), p->lead_card(HEARTS));
    ASSERT_EQUAL(Card(KING, CLUBS), p->lead_card(HEARTS));
    ASSERT_EQUAL(Card(JACK, DIAMONDS), p->lead_card(HEARTS));
    ASSERT_EQUAL(Card(QUEEN, HEARTS), p->lead_card(HEARTS));
    ASSERT_EQUAL(Card(NINE, HEARTS), p->lead_card(HEARTS));
    delete p;
}

TEST(test_add_discard_equal_rank_nontrumps) {
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(NINE, SPADES));
    p->add_card(Card(NINE, DIAMONDS));
    p->add_card(Card(TEN, SPADES));
    p->add_card(Card(TEN, DIAMONDS));
    p->add_card(Card(NINE, CLUBS));
    p->add_and_discard(Card(ACE, HEARTS));

    ASSERT_EQUAL(Card(TEN, DIAMONDS), p->lead_card(HEARTS));
    ASSERT_EQUAL(Card(TEN, SPADES), p->lead_card(HEARTS));
    ASSERT_EQUAL(Card(NINE, DIAMONDS), p->lead_card(HEARTS));
    ASSERT_EQUAL(Card(NINE, CLUBS), p->lead_card(HEARTS));
    ASSERT_EQUAL(Card(ACE, HEARTS), p->lead_card(HEARTS));
    delete p;
}

TEST(test_add_discard_lowest_at_middle) {
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(ACE, CLUBS));
    p->add_card(Card(KING, SPADES));
    p->add_card(Card(NINE, DIAMONDS));
    p->add_card(Card(QUEEN, CLUBS));
    p->add_card(Card(TEN, SPADES));
    p->add_and_discard(Card(NINE, HEARTS));

    ASSERT_EQUAL(Card(ACE, CLUBS), p->lead_card(HEARTS));
    ASSERT_EQUAL(Card(KING, SPADES), p->lead_card(HEARTS));
    ASSERT_EQUAL(Card(QUEEN, CLUBS), p->lead_card(HEARTS));
    ASSERT_EQUAL(Card(TEN, SPADES), p->lead_card(HEARTS));
    ASSERT_EQUAL(Card(NINE, HEARTS), p->lead_card(HEARTS));
    delete p;
}

TEST(test_make_trump_round1_low_trump_not_enough) {
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(TEN, HEARTS));
    p->add_card(Card(ACE, SPADES));
    p->add_card(Card(KING, CLUBS));
    p->add_card(Card(QUEEN, DIAMONDS));
    Suit selected = CLUBS;
    ASSERT_FALSE(p->make_trump(Card(JACK, HEARTS), false, 1, selected));
    ASSERT_EQUAL(CLUBS, selected);
    delete p;
}

TEST(test_make_trump_round2_left_bower_yes) {
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(JACK, HEARTS));
    p->add_card(Card(NINE, SPADES));
    p->add_card(Card(TEN, SPADES));
    p->add_card(Card(NINE, CLUBS));
    p->add_card(Card(TEN, CLUBS));
    Suit selected = SPADES;
    ASSERT_TRUE(p->make_trump(Card(ACE, HEARTS), false, 2, selected));
    ASSERT_EQUAL(DIAMONDS, selected);
    delete p;
}

TEST(test_lead_excludes_left_bower_from_nontrumps) {
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(JACK, DIAMONDS));
    p->add_card(Card(NINE, SPADES));
    p->add_card(Card(TEN, SPADES));
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(QUEEN, HEARTS));
    ASSERT_EQUAL(Card(TEN, SPADES), p->lead_card(HEARTS));
    delete p;
}

TEST(test_play_follow_trump_with_left_bower) {
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(JACK, HEARTS));
    p->add_card(Card(ACE, CLUBS));
    p->add_card(Card(NINE, CLUBS));
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(KING, SPADES));
    ASSERT_EQUAL(Card(JACK, HEARTS),
                 p->play_card(Card(NINE, DIAMONDS), DIAMONDS));
    delete p;
}

TEST(test_play_left_bower_does_not_follow_printed_suit) {
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(JACK, HEARTS));
    p->add_card(Card(NINE, SPADES));
    p->add_card(Card(TEN, SPADES));
    p->add_card(Card(ACE, CLUBS));
    p->add_card(Card(NINE, DIAMONDS));
    ASSERT_EQUAL(Card(NINE, SPADES),
                 p->play_card(Card(QUEEN, HEARTS), DIAMONDS));
    delete p;
}

TEST(test_play_cannot_follow_discard_low_nontrump) {
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(TEN, HEARTS));
    p->add_card(Card(ACE, SPADES));
    p->add_card(Card(NINE, CLUBS));
    p->add_card(Card(TEN, CLUBS));
    ASSERT_EQUAL(Card(NINE, CLUBS),
                 p->play_card(Card(QUEEN, DIAMONDS), HEARTS));
    delete p;
}

TEST(test_play_cannot_follow_all_trump) {
    Player *p = Player_factory("Alice", "Simple");
    p->add_card(Card(NINE, HEARTS));
    p->add_card(Card(TEN, HEARTS));
    p->add_card(Card(JACK, DIAMONDS));
    p->add_card(Card(QUEEN, HEARTS));
    p->add_card(Card(KING, HEARTS));
    ASSERT_EQUAL(Card(NINE, HEARTS),
                 p->play_card(Card(ACE, CLUBS), HEARTS));
    delete p;
}

TEST_MAIN()
