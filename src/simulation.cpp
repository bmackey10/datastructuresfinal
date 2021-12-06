#include "../inc/player.h"

int main()
{
	Deck deck;
	deck.shuffle();

	Player p1(1);

	p1.player_cards.push_back( deck.deal_to_player() );
	p1.player_cards.push_back( deck.deal_to_player() );

	Player p2(2);

	p2.player_cards.push_back( deck.deal_to_player() );
	p2.player_cards.push_back( deck.deal_to_player() );

	Player p3(3);

	p3.player_cards.push_back( deck.deal_to_player() );
	p3.player_cards.push_back( deck.deal_to_player() );

	std::vector<Card> test_cards = p1.get_player_cards();

	deck.table_cards.push_back(deck.deal_to_player());
	deck.table_cards.push_back(deck.deal_to_player());
	deck.table_cards.push_back(deck.deal_to_player());

	/* std::cout << test_cards.at(0).number << " " << test_cards.at(0).suit << std::endl;
	std::cout << test_cards.at(1).number << " " << test_cards.at(1).suit << std::endl;

	std::cout << deck.table_cards.at(0).number << " " << deck.table_cards.at(0).suit << std::endl;
	std::cout << deck.table_cards.at(1).number << " " << deck.table_cards.at(1).suit << std::endl;
	std::cout << deck.table_cards.at(2).number << " " << deck.table_cards.at(2).suit << std::endl; */

	p1.cur_hand = p1.find_hand(deck.table_cards);
	p2.cur_hand = p2.find_hand(deck.table_cards);
	p3.cur_hand = p3.find_hand(deck.table_cards);

	std::cout << p1;
	std::cout << p2;
	std::cout << p3;

	std::cout << deck << std::endl;

	return 0;
}
