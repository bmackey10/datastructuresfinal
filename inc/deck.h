#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stdlib.h>
#include <string>

struct Card {

  int number;
  int suit;

};

class Deck {

  public:

    std::vector<Card> the_deck;
    std::unordered_map<int, bool> deck_hash;
    std::vector<Card> table_cards;

    int pot;

    Deck();

    void shuffle();

    int get_pot();

    void reset_pot();

    Card deal_to_player();

    Card deal_to_table();

    std::string enum_to_string_card(int type) const;

    std::string enum_to_string_suit(int type) const;

    std::vector<Card> get_table_cards();

    friend std::ostream& operator<<( std::ostream& out, const Deck& X );
};


#endif
