#include "Pack.hpp"
#include <iostream>
#include <array>

Pack::Pack() : next(0){
    //initialize a new pack
    int index = 0;
    for (int s = SPADES; s <= DIAMONDS; ++s) {
        Suit suit = static_cast<Suit>(s);
        for (int i = NINE; i <= ACE; ++i) {
            Rank rank = static_cast<Rank>(i);
            cards[index++] = Card(rank, suit);
        }
    }
}

Pack::Pack(std::istream &pack_input) : next(0) {
  for (int i = 0; i < PACK_SIZE; ++i) {
    pack_input >> cards[i];
  }
}

Card Pack::deal_one() {
    Card dealt = cards[next];
    next++;
    return dealt;
}

void Pack::reset() {
    next = 0;
}

void Pack::shuffle() {
    for (int i = 0; i < 7; ++i) {
        std::array<Card, PACK_SIZE> shuffled_cards;

        int first_half = 0;
        int second_half = PACK_SIZE / 2;

        for (int j = 0; j < PACK_SIZE; j += 2) {
            shuffled_cards[j] = cards[second_half];
            shuffled_cards[j + 1] = cards[first_half];

            first_half++;
            second_half++;
        }
        cards = shuffled_cards;
    }

    reset();
}

bool Pack::empty() const {
    return next == PACK_SIZE;
}