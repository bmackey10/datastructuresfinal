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

  public:

		int player_num;

    int player_money;

    std::vector<Card> player_cards;

    Hand cur_hand;

    Player ();

    void fold ( std::vector<Card> player_cards, int player_num );

    int bet ( int bet_amt, bool bet_type, int highest_bet );

    std::vector<Card> get_player_cards () const;

		std::string enum_to_string_rank(rank type) const;

		std::string enum_to_string_card(int type) const;

		std::string enum_to_string_suit(int type) const;

    bool card_sorter( Card const& lhs, Card const& rhs );

    Hand find_hand( std::vector<Card> table_cards ) const;

		friend std::ostream& operator<<( std::ostream& out, const Player& X );

    //void update_hand();

    //Hand get_hand() const;

} ;

#endif
