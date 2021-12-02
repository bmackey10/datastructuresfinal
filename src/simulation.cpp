#include "../inc/player.h"

int main()
{
	Deck deck;
	deck.shuffle();

	Player p1;

	p1.player_cards.push_back( deck.deal_to_player() );

	std::vector<Card> test_cards = p1.get_player_cards(); 

	std::cout << test_cards.at(0).number << " " << test_cards.at(0).suit << std::endl;

	return 0;
}
