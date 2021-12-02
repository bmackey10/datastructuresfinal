#include "../inc/deck.h"

std::string Deck::enum_to_string_card(int type) const {

  switch (type) {
		case 11:
			return "Jack";
		case 12:
			return "Queen";
		case 13:
			return "King";
		case 14:
      return "Ace";
  }

}

std::string Deck::enum_to_string_suit(int type) const {

  switch (type) {
		case 1:
			return "Hearts";
		case 2:
			return "Diamonds";
		case 3:
			return "Clubs";
		case 4:
      return "Spades";
  }

}

/*
* initialize members of card with default constructors
*/
//Card::Card() : number(), suit() {}

/*
* initialize cards in the deck by setting values 1-13 and suits 1-4
* set all cards in deck_hash to true because all card are in the deck
*/
Deck::Deck() : the_deck(), deck_hash(), table_cards(), pot()
{
  Card cards[52];

  // initialize card numbers in deck
  int i = 0, number = 1;
  while (i < 52)
  {
    if (number > 13)
      number = 1;

    cards[i].number = number;

    ++number;
    ++i;
  }

  // initialize suits in deck
  i = 0;
  int suit = 1;
  while (i < 52)
  {
    if (i % 13 == 0 && i != 0)
      ++suit;

    cards[i].suit = suit;

    the_deck.push_back( cards[i] );
    deck_hash[i] = true;

    ++i;
  }

}

/*
* move all elements in the deck vector
* reset deck_hash because all elements are now in the deck
*/
void Deck::shuffle()
{
  std::random_shuffle(the_deck.begin(), the_deck.end());

  table_cards.clear();

  for (auto i : deck_hash)
    i.second = true;
}

/*
* return amount of chips in the pot
*/
int Deck::get_pot()
{
  return pot;
}

/*
* reset amount of chips in the pot
*/
void Deck::reset_pot()
{
  pot = 0;
}

/*
* selects a random index in the deck, lazy deletes that index, and returns the
* card at that index
*/
Card Deck::deal_to_player()
{
  srand(time(NULL));

  int index;
  do {
    index = rand() % 52;
  }
  while ( deck_hash[index] == false );

  deck_hash[index] = false;

  return the_deck.at(index);
}

/*
* selects a random index in the deck, lazy deletes that index, adds the card
at that index to the table_cards vector, and returns the card at that index
*/
Card Deck::deal_to_table()
{
  srand(time(NULL));

  int index;
  do {
    index = rand() % 52;
  }
  while ( deck_hash[index] == false );

  deck_hash[index] = false;
  table_cards.push_back(the_deck.at(index));

  return the_deck.at(index);
}

/*
* returns a vector of the cards on the table
*/
std::vector<Card> Deck::get_table_cards()
{
  return table_cards;
}

std::ostream& operator<<( std::ostream& out, const Deck& X ) {

  out << "\nTable Cards: ";

  for (long unsigned int iter = 0; iter < X.table_cards.size(); iter++ ) {
    if (X.table_cards.at(iter).number > 10) {
      out << X.enum_to_string_card(X.table_cards.at(iter).number) << " of " << X.enum_to_string_suit(X.table_cards.at(iter).suit);
    } else {
      out << X.table_cards.at(iter).number << " of " << X.enum_to_string_suit(X.table_cards.at(iter).suit);
    }

    if (iter < (X.table_cards.size() - 1)) {
      out << "\n             ";
    }
  }

  out << "\nPot: " << X.pot;

  return out;

}
