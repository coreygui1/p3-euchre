
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

    Card first = alice->lead_card(HEARTS);
    Card second = alice->lead_card(HEARTS);

    ASSERT_EQUAL(Card(ACE, CLUBS), first);
    ASSERT_EQUAL(Card(KING, CLUBS), second);

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

    Card first = alice->lead_card(HEARTS);
    ASSERT_EQUAL(Card(JACK, HEARTS), first);

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

TEST_MAIN()
