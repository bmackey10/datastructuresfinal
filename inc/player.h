#ifndef PLAYER_H
#define PLAYER_H

#include "deck.h"

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

    int player_money;

    std::vector<Card> player_cards;

    Hand cur_hand;

  public:

    Player ();

    void fold ( std::vector<Card> player_cards, int player_num );

    int bet ( int bet_amt, bool bet_type, int highest_bet, int pot );

    std::vector<Card> get_player_cards () const;

    bool card_sorter( Card const& lhs, Card const& rhs );

    Hand find_hand( std::vector<Card> table_cards );

    //void update_hand();

    //Hand get_hand() const;

} ;

#endif
