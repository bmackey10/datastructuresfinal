#ifndef PLAYER_H
#define PLAYER_H

#include "deck.h"

const std::vector<std::vector<float>> probs_postflop = { 	{0, 58.6, 8.3, 1.4, 0, 0, 0, 0, 0}, // high card
																													{0, 0, 40.2, 16.0, 0, 0, 1.7, 0.1, 0}, // pair
																													{0, 0, 0, 0, 0, 0, 16.5, 0.2, 0}, 	// two pair
																													{0, 0, 0, 0, 0, 0, 29.8, 43, 0},		// three of a Kind
																													{0},																// straight
																													{0},																// flush
																													{0, 0, 0, 0, 0, 0, 0, 4.3, 0},			// full house
																													{0, 0, 0, 0, 0, 0, 0, 0, 0}, 				// four of a Kind
																									 				{0} };															// straight flush

const std::vector<std::vector<float>> probs_postturn = { 	{0, 39.1, 0, 0, 0, 0, 0, 0, 0}, // high card
																													{0, 0, 26.1, 4.3, 0, 0, 0, 0.1, 0}, // pair
																													{0, 0, 0, 0, 0, 0, 8.7, 0, 0}, 	// two pair
																													{0, 0, 0, 0, 0, 0, 19.6, 2.2, 0},		// three of a Kind
																													{0},																// straight
																													{0},																// flush
																													{0, 0, 0, 0, 0, 0, 0, 2.2, 0},			// full house
																													{0, 0, 0, 0, 0, 0, 0, 0, 0}, 				// four of a Kind
																													{0} };															// straight flush



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

    Player ( int i );

    int bet ( int bet_amt );
		
    std::vector<Card> get_player_cards () const;

		std::string enum_to_string_rank(rank type) const;

		std::string enum_to_string_card(int type) const;

		std::string enum_to_string_suit(int type) const;

    bool card_sorter( Card const& lhs, Card const& rhs );

    Hand find_hand( std::vector<Card> table_cards ) const;

		friend std::ostream& operator<<( std::ostream& out, const Player& X );

		std::vector<float> calc_postflop( std::vector<Card> table_cards );

		std::vector<float> calc_postturn( std::vector<Card> table_cards );

} ;

#endif
