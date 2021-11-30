#ifndef PLAYER_H
#define PLAYER_H

#include “deck.h”
#include <algorithm>

typedef struct Chips {

  int white;
  int red;
  int blue;
  int green;

  int total = (white * 1) + (red * 5) + (blue * 10) + (green * 25);

} Chips ;

enum rank {
	HIGH_CARD,
	PAIR,
	TWO_PAIR,
	THREE_OF_A_KIND,
	STRAIGHT,
	FLUSH,
	FULL_HOUSE,
	FOUR_OF_A_KIND,
	STRAIGHT_FLUSH
};

typedef struct Hand {
	rank the_rank;
	int first;
	int second;
} Hand;

class Player {

  private:

    int player_num;

    chips player_chips;

    std::vector<Card> player_cards;

    Hand cur_hand;

  public:

    Player ();

    void get_chips ();

    void fold ( std::vector<Card> player_cards, int player_num );

    int bet ( chips player_chips );

    std::vector<Card> get_player_cards () const;

    bool card_sorter( Card const& lhs, Card const& rhs );

    Hand find_hand();

    void update_hand();

    //Hand get_hand() const;

} ;

#endif
