#include "Player.hpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class SimplePlayer : public Player {
private:
  string name;
  vector<Card> hand;

public:
  SimplePlayer(const string &name_in)
    : name(name_in) {}

  const string & get_name() const override {
    return name;
  }

  void add_card(const Card &c) override {
    hand.push_back(c);
  }

  bool make_trump(const Card &upcard, bool is_dealer, int round, Suit &order_up_suit) const override {
    if (round == 1) {
      Suit proposed_suit = upcard.get_suit();

      int count = 0;

      for (const Card &card : hand) {
        if (card.is_face_or_ace() && card.is_trump(proposed_suit)) {
          ++count;
        }
      }
      if (count >= 2) {
        order_up_suit = proposed_suit;
        return true;
      }
      
      return false;
    }

    Suit proposed_suit = Suit_next(upcard.get_suit());

    int count = 0;

    for (const Card &card : hand) {
        if (card.is_face_or_ace() && card.is_trump(proposed_suit)) {
          ++count;
        }
    }

    if (count >= 1 || is_dealer) {
        order_up_suit = proposed_suit;
        return true;
    }

    return false;
  }

  void add_and_discard(const Card &upcard) override {
    hand.push_back(upcard);

    Suit trump = upcard.get_suit();

    int lowest = 0;

    for (int i = 0; i < hand.size(); ++i) {
        if (Card_less(hand[i], hand[lowest], trump)) {
            lowest = i;
        }
    }

    hand.erase(hand.begin() + lowest);
  }

  Card lead_card(Suit trump) override {
    int best = -1;

    for (int i = 0; i < hand.size(); ++i) {
      if (!hand[i].is_trump(trump)) {
        if (best == -1 || Card_less(hand[best], hand[i], trump)) {
          best = i;
        }
      }
    }

    if (best == -1) {
      best = 0;
      for (int i = 1; i < hand.size(); ++i) {
        if (Card_less(hand[best], hand[i], trump)) {
          best = i;
        }
      }
    }

    Card lead = hand[best];
    hand.erase(hand.begin() + best);
    return lead;
  }

  Card play_card(const Card &led_card, Suit trump) override {
    Suit led_suit = led_card.get_suit(trump);
    int best = -1;

    for (int i = 0; i < hand.size(); ++i) {
      if (hand[i].get_suit(trump) == led_suit) {
        if (best == -1 || Card_less(hand[best], hand[i], led_card, trump)) {
          best = i;
        }
      }
    }

    if (best == -1) {
      best = 0;
      for (int i = 1; i < hand.size(); ++i) {
        if (Card_less(hand[i], hand[best], trump)) {
          best = i;
        }
      }
    }

    Card play = hand[best];
    hand.erase(hand.begin() + best);
    return play;
  }
};

// Human player: asks the user which card to play.
class HumanPlayer : public Player {
private:
  string name;
  vector<Card> hand;

  void print_hand() const {
    for (int i = 0; i < hand.size(); ++i) {
      cout << "Human player " << name << "'s hand: "
           << "[" << i << "] " << hand[i] << "\n";
    }
  }

public:
  HumanPlayer(const string &name_in) : name(name_in) {}

  const string & get_name() const override {
    return name;
  }

  void add_card(const Card &c) override {
    hand.push_back(c);
    sort(hand.begin(), hand.end());
  }

  bool make_trump(const Card &upcard, bool is_dealer,
                  int round, Suit &order_up_suit) const override {
    print_hand();
    cout << "Human player " << name
         << ", enter a suit, or \"pass\":\n";

    string choice;
    cin >> choice;
    if (choice == "pass") {
      return false;
    }
    order_up_suit = string_to_suit(choice);
    return true;
  }

  void add_and_discard(const Card &upcard) override {
    print_hand();
    cout << "Discard upcard: [-1]\n";
    cout << "Human player " << name
         << ", select a card to discard:\n";

    int choice;
    cin >> choice;
    if (choice != -1) {
      hand[choice] = upcard;
      sort(hand.begin(), hand.end());
    }
  }

  Card lead_card(Suit trump) override {
    print_hand();
    cout << "Human player " << name
         << ", select a card:\n";

    int choice;
    cin >> choice;
    Card chosen = hand[choice];
    hand.erase(hand.begin() + choice);
    return chosen;
  }

  Card play_card(const Card &led_card, Suit trump) override {
    return lead_card(trump);
  }
};

Player * Player_factory(const string &name, const string &strategy) {
  if (strategy == "Simple") {
    return new SimplePlayer(name);
  }
  if (strategy == "Human") {
    return new HumanPlayer(name);
  }
  assert(false);
  return nullptr;
}

ostream & operator<<(ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}
