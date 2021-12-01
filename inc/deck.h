#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stdlib.h>

struct Card {

  int number;
  int suit;

};

class Deck {

  private:

    std::vector<Card> the_deck;

    // need to rethink how to implement deck_hash
    // as of now its key is index of card in vector and value is boolean
    // how do we say "is the ace of hearts in the deck" in O(1) time
    std::unordered_map<int, bool> deck_hash;
    std::vector<Card> table_cards;

    int pot;


  public:

    Deck();

    void shuffle();

    int get_pot();

    void reset_pot();

    Card deal_to_player();

    Card deal_to_table();

    std::vector<Card> get_table_cards();
};


#endif
