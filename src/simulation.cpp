#include "../inc/player.h"

int main()
{
	Deck deck;
	deck.shuffle();

	Player p1;

	p1.player_cards.push_back( deck.deal_to_player() );
	p1.player_cards.push_back( deck.deal_to_player() );

	std::vector<Card> test_cards = p1.get_player_cards();

	deck.table_cards.push_back(deck.deal_to_player());
	deck.table_cards.push_back(deck.deal_to_player());
	deck.table_cards.push_back(deck.deal_to_player());

	std::cout << test_cards.at(0).number << " " << test_cards.at(0).suit << std::endl;
	std::cout << test_cards.at(1).number << " " << test_cards.at(1).suit << std::endl;

	std::cout << p1 << std::endl;
	std::cout << std::endl << deck << std::endl;

	return 0;
}
