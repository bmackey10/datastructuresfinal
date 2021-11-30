​​#include "player.h"

Player::Player( int num, chips player_chips, std::vector<Card> player_cards) :
  player_num( num ), player_chips( player_chips ), player_cards( player_cards ) {}

void Player::get_chips () {

  chips init_chips;

  player_chips.white = 10;
  player_chips.red = 9;
  player_chips.blue = 2;
  player_chips.green = 1;
  player_chips.total = 100;

  player_chips = init_chips;

}

void Player::fold ( std::vector<Card> player_cards, int player_num ) {

  std::cout << "Player " << player_num << " has folded." << std::endl;

  player_cards.clear();

}

<<<<<<< HEAD
int bet ( chips player_chips ) { // work on this logic // number bet amount, 0 / 1
=======
int Player::bet ( chips player_chips ) { // work on this logic
>>>>>>> d4f16bf57dc4b484267e8a4d6d2aa8b6584fb27c

  int bet_amt;

  std::cout << "How much money would you like to bet? " << std::endl;

  std::cin >> bet_amt;

  while ( bet_amt > player_chips.total ) {

    std::cout << "Do not have enough money to cover the bet. Please enter a new bet." << std::endl;

    std:: cin >> bet_amt;

  }

  if ( bet_amt >= 25 ) {

    player_chips.green = player_chips.green - (int) bet_amt / 25;

    bet_amt = bet_amt - ( player_chips.green * 25 );

  }

  if ( bet_amt >= 10 && bet_amt < 25 ) {

    player_chips.blue = player_chips.blue - (int) bet_amt / 10;

    bet_amt = bet_amt - ( player_chips.blue * 10 );

  }

  if ( bet_amt >= 5 && bet_amt < 10 ) {

    player_chips.red = player_chips.red - (int) bet_amt / 5;

    bet_amt = bet_amt - ( player_chips.red * 5 );

  }

  if ( bet_amt >= 1 && bet_amt < 5 ) {

    player_chips.white = player_chips.white - (int) bet_amt / 1;

    bet_amt = bet_amt - ( player_chips.white * 1 );

  }

  return bet_amt;

}

std::vector<Card> Player::get_player_cards () const {

  return player_cards;

}

// Function to compare cards by number
bool Player::card_sorter( Card const& lhs, Card const& rhs ) {
  if (lhs.number != rhs.number)
    return lhs.number > rhs.number; // Trying to sort highest to lowest
  else
    return lhs.number == rhs.number;
}

Hand Player::find_hand()
{
  std::vector<Card> cards = get_player_cards();

  cards.insert(cards.end(), get_table_cards.begin(), get_table_cards.end());

  std::sort(cards.begin(), cards.end(), &card_sorter);

  Hand best_hand; // best_hand is always returned

  best_hand.the_rank = HIGH_CARD;
  best_hand.first = cards[0].number;
  best_hand.second = cards[1].number;

  std::vector<int> suitCount;
  bool flush;
  int index;

// Should I return each time a hand is found?
  if (cards.size() == 2) {
    if(cards[0].number == cards[1].number) {
      best_hand.the_rank = PAIR;
      return best_hand;
    }
  }

// Not considering the case where cards would be a size it shouldn't be
  else if (cards.size() == 5) {
    // Need to calculate straight flush here
    if(cards[0].number == cards[3].number || cards[1].number == cards[4].number) {
      best_hand.the_rank = FOUR_OF_A_KIND;
      best_hand.first = cards[1].number; // Will always correspond to one with four of a kind
      if (cards[0] == cards[1])
        best_hand.second = cards[4].number;
      else
        best_hand.second = cards[0].number;

      return best_hand; // Returns right when a four of a kind is found.
    }

// Check for pairs, three of a kind, and full houses
    for (long unsigned int iter = 0; iter < cards.size() - 1; iter++) {
      if (iter + 2 < cards.size()) {
        if (cards[iter].number == cards[iter + 2].number) {
          if (best_hand.the_rank == PAIR) {
            best_hand.the_rank = FULL_HOUSE;
            best_hand.second = best_hand.first;
            best_hand.first = cards[iter].number;
            return best_hand;
          }
          else {
            best_hand.the_rank = THREE_OF_A_KIND;
            best_hand.first = cards[iter].number;
            iter++; // Skip over the next iteration since it was accounted for
            continue;
          }
        }
      if(cards[iter].number == cards[iter + 1].number) {
        if (best_hand.the_rank == THREE_OF_A_KIND) {
          best_hand.the_rank = FULL_HOUSE;
          best_hand.second = cards[iter].number;
          return best_hand;
        }
        else if (best_hand.the_rank == PAIR) {
          best_hand.the_rank = TWO_PAIR;
          best_hand.second = cards[iter].number;
        }
      else if(cards[iter] == cards[iter + 1]) {
        best_hand.the_rank = PAIR;
        best_hand.first = cards[iter];
    }

// Could move this out of the if if we could figure out how to not overwrite best hand.
    for (long unsigned int iter = 0; iter < cards.size(); iter++) {
      int cur_suit = cards[iter].suit;
      suitCount[cur_suit]++;
      if (suitCount[cur_suit] >= 5) {
        best_hand.the_rank = FLUSH;
        return best_hand;
      }
    }

    for (long unsigned int iter = 0; iter < cards.size() - 1; iter++) {
      if (cards[iter].number != cards.[iter + 1].number + 1)
        break;

      if (iter == cards.size() - 2) {
        best_hand.the_rank = STRAIGHT;
        return best_hand;
      }
    }

    return best_hand;
  }

}

void Player::update_hand() {
  cur_hand = find_hand(); // Does this work?
}

//Hand Player::get_hand() const {}
