#include "../inc/player.h"

std::string Player::enum_to_string_rank(rank type) const {

	switch (type) {
		case HIGH_CARD:
			return "High Card";
		case PAIR:
			return "Pair";
		case TWO_PAIR:
			return "Two Pair";
		case THREE_OF_A_KIND:
			return "Three of a Kind";
		case STRAIGHT:
			return "Straight";
		case FLUSH:
			return "Flush";
		case FULL_HOUSE:
			return "Full House";
		case FOUR_OF_A_KIND:
			return "Four of a Kind";
		case STRAIGHT_FLUSH:
			return "Straight Flush";
	}
}

std::string Player::enum_to_string_card(int type) const {

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

std::string Player::enum_to_string_suit(int type) const {

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

Player::Player( ) : player_num( ), player_money( 100 ), player_cards( ), cur_hand( ) {}

void Player::fold ( std::vector<Card> player_cards, int player_num ) {

  std::cout << "Player " << player_num << " has folded." << std::endl;

  player_cards.clear();

}

int Player::bet ( int bet_amt, bool bet_type, int highest_bet ) { // need to take highest bid input

  if ( bet_type == 0 ) { // check

    player_money = player_money - highest_bet;

  } else if ( bet_type == 1 ) { // bet

    player_money = player_money - bet_amt;

  }

  return bet_amt;

}


std::vector<Card> Player::get_player_cards () const {

  return player_cards;

}

/*
// Function to compare cards by number
bool Player::card_sorter( Card const& lhs, Card const& rhs ) {
  if (lhs.number != rhs.number)
    return lhs.number > rhs.number; // Trying to sort highest to lowest
  else
    return lhs.number == rhs.number;

}
*/

Hand Player::find_hand( std::vector<Card> table_cards ) const
{
  std::vector<Card> cards = get_player_cards();

  cards.insert(cards.end(), table_cards.begin(), table_cards.end());


	std::sort(cards.begin(), cards.end(), [](Card a, Card b) { return a.number > b.number; } );
  //std::sort(cards.begin(), cards.end(), &Player::card_sorter);


	/* for (int i = 0; i < cards.size(); i++) {
		std::cout << cards.at(i).number << " " << cards.at(i).suit << std::endl;
	} */



  Hand best_hand; // best_hand is always returned

  best_hand.the_rank = HIGH_CARD;
  best_hand.first = cards[0].number;
  best_hand.second = cards[1].number;

  std::vector<int> suitCount (5, 0);
  int consecutive = 1;
  int start = 0;
  //bool flush;
  //int index;

// Should I return each time a hand is found?
  if (cards.size() == 2) {
    if(cards[0].number == cards[1].number) {
      best_hand.the_rank = PAIR;
     }
	return best_hand;
  }

// Not considering the case where cards would be a size it shouldn't be
  else if (cards.size() == 5) {
    // Need to calculate straight flush here
    if(cards[0].number == cards[3].number || cards[1].number == cards[4].number) {
      best_hand.the_rank = FOUR_OF_A_KIND;
      best_hand.first = cards[1].number; // Will always correspond to one with four of a kind
      if (cards[0].number == cards[1].number)
        best_hand.second = cards[4].number;
      else
        best_hand.second = cards[0].number;
	  return best_hand;
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
            best_hand.first = cards[iter].number; // Check for second card
            iter++; // Skip over the next iteration since it was accounted for
            continue;
          }
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
        else {
          best_hand.the_rank = PAIR;
          best_hand.first = cards[iter].number;
        }
      }
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
      if (cards[iter].number != cards[iter + 1].number + 1)
        break;

      if (iter == cards.size() - 2) {
        best_hand.the_rank = STRAIGHT;
        return best_hand;
      }
    }

    return best_hand;
  }

  else if (cards.size() == 6) {
    if(cards[0].number == cards[3].number || cards[1].number == cards[4].number || cards[2].number == cards[5].number) {
      best_hand.the_rank = FOUR_OF_A_KIND;
      best_hand.first = cards[2].number; // Will always correspond to one with four of a kind
      if (cards[0].number == cards[1].number)
        best_hand.second = cards[4].number;
      else
        best_hand.second = cards[0].number;

      return best_hand; // Returns right when a four of a kind is found.
    }

// Copied from size == 5; I don't think we can make it so we only use it once
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
        else {
          best_hand.the_rank = PAIR;
          best_hand.first = cards[iter].number;
        }
      }
	}

      for (long unsigned int iter = 0; iter < cards.size(); iter++) {
        int cur_suit = cards[iter].suit;
        suitCount[cur_suit]++;
        if (suitCount[cur_suit] >= 5) {
          best_hand.the_rank = FLUSH;
          if (cards[0].suit != cur_suit) { // In this case, the top card for the flush is the second highest ranked card.
            best_hand.first = cards[1].number;
            best_hand.second = cards[2].number;
          }
          else if (cards[1].suit != cur_suit) {
            best_hand.second = cards[2].number;
          }
          return best_hand;
        }
      }

      for (long unsigned int iter = 0; iter < cards.size() - 1; iter++) {
        if (cards[iter].number == cards[iter + 1].number) continue;
        else if (cards[iter].number != cards[iter + 1].number + 1) {
          consecutive = 1;
          start = iter + 1; // Starts straight at iter + 1
          continue; // Moves to the next iteration of the loop
        }

        consecutive++;

        if (consecutive >= 5) {
          best_hand.the_rank = STRAIGHT;
          best_hand.first = cards[start].number;
          best_hand.second = cards[start + 1].number; // Will create a situation with 7 as first and second if cards are 7, 7, 6, 5, 4, 3
          return best_hand;
        }
      }

      return best_hand;
    }

  else if (cards.size() == 7) {
    if(cards[0].number == cards[3].number || cards[1].number == cards[4].number || cards[2].number == cards[5].number || cards[3].number == cards[6].number) {
      best_hand.the_rank = FOUR_OF_A_KIND;
      best_hand.first = cards[3].number; // Will always correspond to one with four of a kind
      if (cards[0].number == cards[1].number)
        best_hand.second = cards[4].number;
      else
        best_hand.second = cards[0].number;

      return best_hand; // Returns right when a four of a kind is found.
    }

// Copied from size == 5; I don't think we can make it so we only use it once
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
        else {
          best_hand.the_rank = PAIR;
          best_hand.first = cards[iter].number;
        }
      }
    }

// Could alternatively use a bitset or a hash for flush determination
    for (long unsigned int iter = 0; iter < cards.size(); iter++) {
      int cur_suit = cards[iter].suit;
      suitCount[cur_suit]++; // Shouldn't be an issue but might need to reset suitCount at beginning of for loop.
      if (suitCount[cur_suit] >= 5) {
        best_hand.the_rank = FLUSH;
        if (cards[0].suit != cur_suit) { // In this case, the top card for the flush is the second highest ranked card.
          if (cards[1].suit != cur_suit) {
            best_hand.first = cards[2].number;
            best_hand.second = cards[3].number;
          }
          else {
            best_hand.first = cards[1].number;
            if (cards[2].suit != cur_suit)
              best_hand.second = cards[3].number;
            else
              best_hand.second = cards[2].number;
          }
        }
        else if (cards[1].suit != cur_suit) {
          if (cards[2].suit != cur_suit)
            best_hand.second = cards[3].number;
          else
            best_hand.second = cards[2].number;
        }

        return best_hand;
      }
    }

    for (long unsigned int iter = 0; iter < cards.size() - 1; iter++) {
      if (cards[iter].number == cards[iter + 1].number) continue;
      else if (cards[iter].number != cards[iter + 1].number + 1) {
        consecutive = 1;
        start = iter + 1; // Starts straight at iter + 1
        continue;
      }

      consecutive++;

      if (consecutive >= 5) {
        best_hand.the_rank = STRAIGHT;
        best_hand.first = cards[start].number;
        best_hand.second = cards[start + 1].number; // Will create a situation with 7 as first and second if cards are 10, 7, 7, 6, 5, 4, 3
        return best_hand;
      }
    }

    return best_hand;

  }

}

/*
void Player::update_hand() {
  cur_hand = find_hand(); // Does this work?
}
*/

//Hand Player::get_hand() const {}

std::ostream& operator<<( std::ostream& out, const Player& X ){

  std::vector<Card> table_cards; // figure out how to access table cards within this method

  out << "Player " << X.player_num << ": \n\tChips: " << X.player_money << "\n\tCards: ";

  for (long unsigned int iter = 0; iter < 2; iter++ ) {
    if (X.player_cards.at(iter).number > 10) {
      out << X.enum_to_string_card(X.player_cards.at(iter).number) << " of " << X.enum_to_string_suit(X.player_cards.at(iter).suit);
    } else {
      out << X.player_cards.at(iter).number << " of " << X.enum_to_string_suit(X.player_cards.at(iter).suit);
    }

    if (iter == 0) {
      out << "\n\t       ";
    }
  }

  out << "\n\tHand: " << X.enum_to_string_rank(X.find_hand(table_cards).the_rank) << "\n\tHighest Cards: ";

  if (X.find_hand(table_cards).first > 10) {
    out << X.enum_to_string_card(X.find_hand(table_cards).first) << ", ";
  } else {
    out << X.find_hand(table_cards).first << ", ";
  }

  if (X.find_hand(table_cards).second > 10) {
    out << X.enum_to_string_card(X.find_hand(table_cards).second);
  } else {
    out << X.find_hand(table_cards).second;
  }

	return out;
}
