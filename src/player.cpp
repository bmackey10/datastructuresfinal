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

Player::Player( int i ) : player_num( i ), player_money( 100 ), player_cards( ), cur_hand( ) {}

void Player::fold ( std::vector<Card> player_cards, int player_num ) {

  std::cout << "Player " << player_num << " has folded." << std::endl;

  player_cards.clear();

}

int Player::bet ( int bet_amt, bool bet_type, int highest_bet ) { // need to take highest bid input

  if ( bet_type == 0 ) { // call

    player_money = player_money - highest_bet;

		bet_amt = highest_bet;

  } else if ( bet_type == 1 ) { // bet / raise

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


	/* for (int i = 0; i < cards.size(); i++) {
		std::cout << cards.at(i).number << " " << cards.at(i).suit << std::endl;
	} */



  Hand best_hand; // best_hand is always returned

  best_hand.the_rank = HIGH_CARD;
	if (player_cards[0].number > player_cards[1].number) {
  	best_hand.first = player_cards[0].number;
  	best_hand.second = player_cards[1].number;
	}
	else {
		best_hand.first = player_cards[1].number;
		best_hand.second = player_cards[0].number;
	}

  std::vector<int> suitCount (5, 0);
  int consecutive = 1;
  int start = 0;
	int begin = 0;

  if (cards.size() == 2) {
    if(cards[0].number == cards[1].number) {
      best_hand.the_rank = PAIR;
     }
	return best_hand;
  }

// Not considering the case where cards would be a size it shouldn't be
  else if (cards.size() == 5) {

		for (long unsigned int iter = 0; iter < cards.size() - 1; iter++) {
			if (cards[iter].number != cards[iter + 1].number + 1 || cards[iter].suit != cards[iter + 1].suit)
        break;
      if (iter == cards.size() - 2) {
        best_hand.the_rank = STRAIGHT_FLUSH;
        return best_hand;
      }
    }

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
						if (best_hand.first != cards[iter].number) {
							best_hand.second = best_hand.first;
            	best_hand.first = cards[iter].number;
						}
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
        else if (best_hand.the_rank == HIGH_CARD) {
          best_hand.the_rank = PAIR;
					if (cards[iter].number != best_hand.first) {
						best_hand.second = best_hand.first;
						best_hand.first = cards[iter].number;
					}
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
			if (cards[iter].number != cards[iter + 1].number + 1) {
				if (cards[iter].number == 14 && cards[iter + 1].number == 5) continue;
				else break;
			}


      if (iter == cards.size() - 2) {
        best_hand.the_rank = STRAIGHT;
				best_hand.first = cards[0].number;
				best_hand.second = cards[1].number;
        return best_hand;
      }
    }

    return best_hand;
  }

// -----------------------------------------------------------------------------

  else if (cards.size() == 6) {

		consecutive = 1;
		for (long unsigned int iter = 0; iter < cards.size() - 1; iter++) {
			if (cards[iter].number != cards[iter + 1].number + 1 || cards[iter].suit != cards[iter + 1].suit) {
				consecutive = 1;
				begin = iter + 1; // Starts straight at iter + 1
				continue; // Moves to the next iteration of the loop
			}

			consecutive++;

			if (consecutive >= 5) {
				best_hand.the_rank = STRAIGHT_FLUSH;
				best_hand.first = cards[begin].number;
				best_hand.second = cards[begin].number;
				return best_hand;
			}
    }

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
						if (best_hand.first != cards[iter].number) {
							best_hand.second = best_hand.first;
            	best_hand.first = cards[iter].number;
						}
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
        else if (best_hand.the_rank == HIGH_CARD) {
          best_hand.the_rank = PAIR;
					if (cards[iter].number != best_hand.first) {
						best_hand.second = best_hand.first;
						best_hand.first = cards[iter].number;
					}
        }
      }
	}

      for (long unsigned int iter = 0; iter < cards.size(); iter++) {
        int cur_suit = cards[iter].suit;
        suitCount[cur_suit]++;
        if (suitCount[cur_suit] >= 5) {
          best_hand.the_rank = FLUSH;
					int greater = player_cards[0].number < player_cards[1].number;
					int lesser = player_cards[0].number > player_cards[1].number;
					if (player_cards[greater].suit != cur_suit && player_cards[lesser].suit == cur_suit) {
            best_hand.first = player_cards[lesser].number;
            best_hand.second = cards[0].number;
					}
					else if (player_cards[greater].suit != cur_suit && player_cards[lesser].suit == cur_suit) {
						best_hand.second = cards[0].number;
					}
					else {
						best_hand.first = cards[0].number;
						best_hand.second = cards[1].number;
          }
          return best_hand;
        }
      }

			consecutive = 1;
      for (long unsigned int iter = 0; iter < cards.size() - 1; iter++) {
				if (cards[iter].number == cards[iter + 1].number) continue;
				else if (cards[iter].number == 14) {
					if (cards[iter + 1].number == 5)
						start = iter + 1;
					else if (cards[iter + 2].number == 5) {
						start = iter + 2;
						iter++;
					}
				}

        else if (cards[iter].number != cards[iter + 1].number + 1) {
          consecutive = 1;
          start = iter + 1; // Starts straight at iter + 1
          continue; // Moves to the next iteration of the loop
        }

        consecutive++;

        if (consecutive >= 5) {
          best_hand.the_rank = STRAIGHT;
          best_hand.first = cards[start].number;
          best_hand.second = cards[start + 1].number;
          return best_hand;
        }
      }

      return best_hand;
    }

// -----------------------------------------------------------------------------

  else if (cards.size() == 7) {

		consecutive = 1;
		for (long unsigned int iter = 0; iter < cards.size() - 1; iter++) {
			if (cards[iter].number != cards[iter + 1].number + 1 || cards[iter].suit != cards[iter + 1].suit) {
				consecutive = 1;
				begin = iter + 1; // Starts straight at iter + 1
				continue; // Moves to the next iteration of the loop
			}

			consecutive++;

			if (consecutive >= 5) {
				best_hand.the_rank = STRAIGHT_FLUSH;
				best_hand.first = cards[begin].number;
				best_hand.second = cards[begin + 1].number;
				return best_hand;
			}
    }

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
						if (best_hand.first != cards[iter].number) {
							best_hand.second = best_hand.first;
            	best_hand.first = cards[iter].number;
						}
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
      else if (best_hand.the_rank == HIGH_CARD) {
          best_hand.the_rank = PAIR;
					if (cards[iter].number != best_hand.first) {
						best_hand.second = best_hand.first;
						best_hand.first = cards[iter].number;
					}
        }
      }
    }

// Could alternatively use a bitset or a hash for flush determination
    for (long unsigned int iter = 0; iter < cards.size(); iter++) {
      int cur_suit = cards[iter].suit;
      suitCount[cur_suit]++; // Shouldn't be an issue but might need to reset suitCount at beginning of for loop.
      if (suitCount[cur_suit] >= 5) {
        best_hand.the_rank = FLUSH;
				int greater = player_cards[0].number < player_cards[1].number;
				int lesser = player_cards[0].number > player_cards[1].number;
				if (player_cards[greater].suit != cur_suit && player_cards[lesser].suit == cur_suit) {
					best_hand.first = player_cards[lesser].number;
					best_hand.second = cards[0].number;
				}
				else if (player_cards[greater].suit != cur_suit && player_cards[lesser].suit == cur_suit) {
					best_hand.second = cards[0].number;
				}
				else if (player_cards[greater].suit != cur_suit && player_cards[lesser].suit != cur_suit) {
					if (best_hand.first != cards[0].number) {
						best_hand.first = cards[0].number;
						if (best_hand.second != cards[1].number)
							best_hand.second = cards[1].number;
					}
				}
        return best_hand;
      }
    }


		consecutive = 1;

    for (long unsigned int iter = 0; iter < cards.size() - 1; iter++) {
			if (cards[iter].number == cards[iter + 1].number) continue;
			else if (cards[iter].number == 14) {
				if (cards[iter + 1].number == 5)
					start = iter + 1;
				else if (cards[iter + 2].number == 5) {
					start = iter + 2;
					iter++;
				}
			else if (cards[iter + 3].number == 5) {
				start = iter + 3;
				iter += 2;
			}
		}

      else if (cards[iter].number != cards[iter + 1].number + 1) {
        consecutive = 1;
        start = iter + 1; // Starts straight at iter + 1
        continue;
      }

      consecutive++;

      if (consecutive >= 5) {
        best_hand.the_rank = STRAIGHT;
        best_hand.first = cards[start].number;
        best_hand.second = cards[start + 1].number;
        return best_hand;
      }
    }

    return best_hand;

  }

}

std::ostream& operator<<( std::ostream& out, const Player& X ){

	out << "\n";

  std::vector<Card> table_cards;

  out << "Player " << X.player_num << " | ";

  for (long unsigned int iter = 0; iter < 2; iter++ ) {
    if (X.player_cards.at(iter).number > 10) {
      out << X.enum_to_string_card(X.player_cards.at(iter).number) << " of " << X.enum_to_string_suit(X.player_cards.at(iter).suit);
    } else {
      out << X.player_cards.at(iter).number << " of " << X.enum_to_string_suit(X.player_cards.at(iter).suit);
    }

    if (iter == 0) {
      out << ", ";
    } else {
			out << "\t\t";
		}
  }

	out << X.player_money << "\t";

  out << X.enum_to_string_rank(X.cur_hand.the_rank) << "\t\t";

  if (X.cur_hand.first > 10) {
    out << X.enum_to_string_card(X.cur_hand.first) << ", ";
  } else {
    out << X.cur_hand.first << ", ";
  }

  if (X.cur_hand.second > 10) {
    out << X.enum_to_string_card(X.cur_hand.second);
  } else {
    out << X.cur_hand.second;
  }

	return out;
}

std::vector<float> Player::calc_postflop( std::vector<Card> table_cards )
{
	std::vector<Card> cards = get_player_cards();

  cards.insert(cards.end(), table_cards.begin(), table_cards.end());

	std::sort(cards.begin(), cards.end(), [](Card a, Card b) { return a.number > b.number; } );

	std::vector<float> return_probs (9, 0);

	int rank = cur_hand.the_rank;

	return_probs.at(HIGH_CARD) = probs_postflop[rank][HIGH_CARD];
	return_probs.at(PAIR) = probs_postflop[rank][PAIR];
	return_probs.at(TWO_PAIR) = probs_postflop[rank][TWO_PAIR];
	return_probs.at(THREE_OF_A_KIND) = probs_postflop[rank][THREE_OF_A_KIND];
	// skip straight and flush
	return_probs.at(FULL_HOUSE) = probs_postflop[rank][FULL_HOUSE];
	return_probs.at(FOUR_OF_A_KIND) = probs_postflop[rank][FOUR_OF_A_KIND];

	// calc flush
	int hearts = 0, diamonds = 0, clubs = 0, spades = 0;
	for ( int i = 0; i < cards.size(); ++i )
	{
		if ( cards.at(i).suit == 1 )
			++hearts;
		if ( cards.at(i).suit == 2 )
			++diamonds;
		if ( cards.at(i).suit == 3 )
			++clubs;
		if ( cards.at(i).suit == 4 )
			++spades;
	}
	int max = hearts > diamonds ? hearts : diamonds;
	max = max > clubs ? max : clubs;
	max = max > spades ? max : spades;

	if ( max == 3 )
		return_probs.at(FLUSH) = 4.2;
	if ( max == 4 )
		return_probs.at(FLUSH) = 35.0;

	// calc straight
	bool added_ace = false;
	for ( int i = 0; i < cards.size(); ++i )	// add ace low
	{
		if ( cards.at(i).number == 14 )
		{
			Card low_ace = {1, cards.at(i).suit};
			cards.push_back( low_ace );
			added_ace = true;
			break;
		}
	}

	int needed1 = 4, distance1 = 0, index = 0;
	while ( index < 4 )
	{
		if ( cards.at(index).number == cards.at(index+1).number )
		{
			++index;
			continue;
		}

		distance1 += cards.at(index).number - cards.at(index+1).number;
		if ( distance1 >= 5 )
		{
				distance1 -= cards.at(index).number - cards.at(index+1).number;
				break;
		}
		--needed1;
		++index;
	}

	int needed2 = 4, distance2 = 0;
	index = 1;
	while ( index < 4 )
	{
		if ( cards.at(index).number == cards.at(index+1).number )
		{
			++index;
			continue;
		}

		distance2 += cards.at(index).number - cards.at(index+1).number;
		if ( distance2 >= 5 )
		{
				distance2 -= cards.at(index).number - cards.at(index+1).number;
				break;
		}
		--needed2;
		++index;
	}

	int needed3 = 4, distance3 = 0;
	index = 2;
	while ( index < 4 )
	{
		if ( cards.at(index).number == cards.at(index+1).number )
		{
			++index;
			continue;
		}

		distance3 += cards.at(index).number - cards.at(index+1).number;
		if ( distance3 >= 5 )
		{
			distance3 -= cards.at(index).number - cards.at(index+1).number;
			break;
		}
		--needed3;
		++index;
	}

	if ( added_ace )
	{
		int needed4 = 4, distance4 = 0;
		index = 3;

		while ( index < 5 )
		{
			if ( cards.at(index).number == cards.at(index+1).number )
			{
				++index;
				continue;
			}

			distance4 -= cards.at(index).number - cards.at(index+1).number;
			if ( distance4 >= 5 )
			{
				distance4 -= cards.at(index).number - cards.at(index+1).number;
				break;
			}
			--needed4;
			++index;
		}

		if ( needed3 > needed4 )
		{
			needed3 = needed4;
			distance3 = distance4;
		}
	}

	if ( needed2 > needed3 )
	{
		needed2 = needed3;
		distance2 = distance3;
	}
	if ( needed1 > needed2 )
	{
		needed1 = needed2;
		distance1 = distance2;
	}

	std::cout << needed1 << " " << distance1 << std::endl;

	if ( needed1 == 2 && distance1 == 4 )
		return_probs.at(STRAIGHT) = 1.5;
	if ( needed1 == 2 && distance1 == 3 )
		return_probs.at(STRAIGHT) = 3.0;
	if ( needed1 == 2 && distance1 == 2 )
			return_probs.at(STRAIGHT) = 4.4;

	else if ( needed1 == 1 && distance1 == 4 )
		return_probs.at(STRAIGHT) = 16.5;
	else if ( needed1 == 1 && distance1 == 3)
		return_probs.at(STRAIGHT) = 31.5;

	return return_probs;
}

std::vector<float> Player::calc_postturn( std::vector<Card> table_cards )
{
	std::vector<Card> cards = get_player_cards();

  cards.insert(cards.end(), table_cards.begin(), table_cards.end());

	std::sort(cards.begin(), cards.end(), [](Card a, Card b) { return a.number > b.number; } );

	std::vector<float> return_probs (9, 0);

	int rank = cur_hand.the_rank;

	return_probs.at(HIGH_CARD) = probs_postturn[rank][HIGH_CARD];
	return_probs.at(PAIR) = probs_postturn[rank][PAIR];
	return_probs.at(TWO_PAIR) = probs_postturn[rank][TWO_PAIR];
	return_probs.at(THREE_OF_A_KIND) = probs_postturn[rank][THREE_OF_A_KIND];
	// skip straight and flush
	return_probs.at(FULL_HOUSE) = probs_postturn[rank][FULL_HOUSE];
	return_probs.at(FOUR_OF_A_KIND) = probs_postturn[rank][FOUR_OF_A_KIND];

	// calc flush
	int hearts = 0, diamonds = 0, clubs = 0, spades = 0;
	for ( int i = 0; i < cards.size(); ++i )
	{
		if ( cards.at(i).suit == 1 )
			++hearts;
		if ( cards.at(i).suit == 2 )
			++diamonds;
		if ( cards.at(i).suit == 3 )
			++clubs;
		if ( cards.at(i).suit == 4 )
			++spades;
	}
	int max = hearts > diamonds ? hearts : diamonds;
	max = max > clubs ? max : clubs;
	max = max > spades ? max : spades;

	if ( max == 4 )
		return_probs.at(FLUSH) = 19.6;

	// calc straight
	bool added_ace = false;
	for ( int i = 0; i < cards.size(); ++i )	// add ace low
	{
		if ( cards.at(i).number == 14 )
		{
			Card low_ace = {1, cards.at(i).suit};
			cards.push_back( low_ace );
			added_ace = true;
			break;
		}
	}

	int needed1 = 4, distance1 = 0, index = 0;
	while ( index < 5 )
	{
		if ( cards.at(index).number == cards.at(index+1).number )
		{
			++index;
			continue;
		}

		distance1 += cards.at(index).number - cards.at(index+1).number;
		if ( distance1 >= 5 )
		{
				distance1 -= cards.at(index).number - cards.at(index+1).number;
				break;
		}
		--needed1;
		++index;
	}

	int needed2 = 5, distance2 = 0;
	index = 1;
	while ( index < 4 )
	{
		if ( cards.at(index).number == cards.at(index+1).number )
		{
			++index;
			continue;
		}

		distance2 += cards.at(index).number - cards.at(index+1).number;
		if ( distance2 >= 5 )
		{
				distance2 -= cards.at(index).number - cards.at(index+1).number;
				break;
		}
		--needed2;
		++index;
	}

	int needed3 = 4, distance3 = 0;
	index = 2;
	while ( index < 5 )
	{
		if ( cards.at(index).number == cards.at(index+1).number )
		{
			++index;
			continue;
		}

		distance3 += cards.at(index).number - cards.at(index+1).number;
		if ( distance3 >= 5 )
		{
				distance3 -= cards.at(index).number - cards.at(index+1).number;
				break;
		}
		--needed3;
		++index;
	}

	int needed4 = 4, distance4 = 0;
	index = 3;
	while ( index < 5 )
	{
		if ( cards.at(index).number == cards.at(index+1).number )
		{
			++index;
			continue;
		}

		distance4 += cards.at(index).number - cards.at(index+1).number;
		if ( distance4 >= 5 )
		{
				distance4 -= cards.at(index).number - cards.at(index+1).number;
				break;
		}
		--needed4;
		++index;
	}

	if ( added_ace )
	{
		int needed5 = 4, distance5 = 0;
		index = 4;

		while ( index < 6 )
		{
			if ( cards.at(index).number == cards.at(index+1).number )
			{
				++index;
				continue;
			}

			distance5 += cards.at(index).number - cards.at(index+1).number;
			if ( distance5 >= 5 )
			{
					distance5 -= cards.at(index).number - cards.at(index+1).number;
					break;
			}
			--needed5;
			++index;
		}

		if ( needed4 > needed5 )
		{
			needed4 = needed5;
			distance4 = distance5;
		}
	}
	if ( needed3 > needed4 )
	{
		needed3 = needed4;
		distance3 = distance4;
	}
	if ( needed2 > needed3 )
	{
		needed2 = needed3;
		distance2 = distance3;
	}
	if ( needed1 > needed2 )
	{
		needed1 = needed2;
		distance1 = distance2;
	}

	if ( needed1 == 1 && distance1 == 4 )
		return_probs.at(STRAIGHT) = 8.7;
	if ( needed1 == 1 && distance1 == 3)
		return_probs.at(STRAIGHT) = 17.4;

	return return_probs;
}
