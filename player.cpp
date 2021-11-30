​​#include "player.h"

Player::Player( ) : player_num( ), player_money( 100 ), player_cards( ) {}

void Player::fold ( std::vector<Card> player_cards, int player_num ) {

  std::cout << "Player " << player_num << " has folded." << std::endl;

  player_cards.clear();

}

int Player::bet ( int bet_amt, bool bet_type, int highest_bet  ) { // need to take highest bid input

  if ( bet_type == 0 ) { // check

    player_money = player_money - highest_bet;

  } else if ( bet_type == 1 ) { // bet

    player_money = player_money - bet_amt;

  }

  deck.pot = deck.pot + bet_amt;

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
