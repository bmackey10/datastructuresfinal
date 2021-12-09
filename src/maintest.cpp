// Names: Connor Ding, Brooke Mackey, Tara Flannery, Thomas Mercurio
// Emails: cding2@nd.edu, bmackey@nd.edu, tflanne2@nd.edu, tmercuri@nd.edu
// File Name: maintest.cpp
// File Contents: Contains the Poker simulation that will run from terminal.

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>

#include "../inc/player.h"

#define COUT std::cout
#define CIN std::cin
#define smallblind 5
#define bigblind 10
#define ENDL std::endl

bool same_bet( std::vector<int> player_bets )
{
for ( int i = 0; i < player_bets.size() - 1; ++i )
{
 if ( player_bets[i] != player_bets[i+1])
   return false;
}
return true;
}

int highest_bet( std::vector<int> player_bets )
{
  int max = player_bets.at(0);
  for ( int i = 1; i < player_bets.size(); ++i )
    if ( player_bets.at(i) > max )
      max = player_bets.at(i);

  return max;
}


std::vector<Player> compare_hand( std::vector<Player> players ) {

  std::vector<Player> leaderboard;

	for (long unsigned int iter = 0; iter < players.size(); iter++ ) {

		leaderboard.push_back( players.at(iter) );

	}

  Player temp(0);

  for (long unsigned int iter = 0; iter < leaderboard.size(); iter++ ) {

    for (long unsigned int jter = 0; jter < (leaderboard.size() - iter - 1); jter++ ) {

      if ( leaderboard.at(jter).cur_hand.the_rank < leaderboard.at(jter + 1).cur_hand.the_rank) {

        temp = leaderboard.at(jter);

        leaderboard.at(jter) = leaderboard.at(jter + 1);

        leaderboard.at(jter + 1) = temp;

      } else if ( leaderboard.at(jter).cur_hand.the_rank == leaderboard.at(jter + 1).cur_hand.the_rank ) {

        if ( leaderboard.at(jter).cur_hand.first < leaderboard.at(jter + 1).cur_hand.first ) {

          temp = leaderboard.at(jter);

          leaderboard.at(jter) = leaderboard.at(jter + 1);

          leaderboard.at(jter + 1) = temp;

        } else if ( leaderboard.at(jter).cur_hand.first == leaderboard.at(jter + 1).cur_hand.first) {

          if (leaderboard.at(jter).cur_hand.second < leaderboard.at(jter + 1).cur_hand.second) {

            temp = leaderboard.at(jter);

            leaderboard.at(jter) = leaderboard.at(jter + 1);

            leaderboard.at(jter + 1) = temp;

          }

        }

      }

    }

  }

  return leaderboard;

}


int main() {

   int users= 0, betamt= 0, num_bet = 0, curr_bet = 0;

//asks the user how many players
   COUT << "Enter the number of players that will be playing (there must be at least 3): ";
   CIN >> users; //equal to "player_num" in player class
   COUT << ENDL;
//instantiate that many players by creating a vector and pushing back as many users as entered
   std::vector<Player> gameplayers;
   int i = 1;
   while (i <= users)
   {
      Player p(i);
      gameplayers.push_back(p);
      i++;
   }

//initialize the deck
   Deck deck;

//then shuffle it
   deck.shuffle();

//assign two cards to each player
  i = 0;
   while(i < users){
      gameplayers.at(i).player_cards.push_back(deck.deal_to_player());
      gameplayers.at(i).player_cards.push_back(deck.deal_to_player());
      i++;
   }
//print out cards
   COUT<<"Now we will enter the first round of betting. To fold, type -1. To check, type -2." << ENDL << ENDL;

//first round of betting
   i = 0;
   COUT << "Player " << i + 1 << ", you are the small blind. You will bet 5 chips to start the game." << ENDL;
   gameplayers.at(i).bet(smallblind);
   i++;

   COUT << "Player " << i + 1 << ", you are the big blind. You will bet 10 chips to double the small blind. " << ENDL << ENDL;

   COUT << "\t\t Cards \t Money \t Hand \t Highest Cards" << ENDL;
   i = 0;
   while(i < 10){
      COUT << "----------";
      ++i;
   }
   COUT << ENDL;

   i = 1;

   gameplayers.at(i).bet(bigblind);
   i++;

   for (long unsigned int iter = 0; iter < gameplayers.size(); iter ++ ) {
     gameplayers.at(iter).cur_hand = gameplayers.at(iter).find_hand( deck.table_cards );
   }

   for (long unsigned int iter = 0; iter < gameplayers.size(); iter ++ ) {
     COUT << gameplayers.at(iter) << ENDL;
  }

  i = 0;
  while(i < 10){
     COUT << "----------";
     ++i;
  }
  i = 0;

  COUT << ENDL << "Pot: 15" << ENDL << ENDL;

std::vector<int> player_bets (users, 0);
int small_blind_print = 5;

bool small_blind = true, big_blind = true;
int index = 0;
do {
  if ( index == users )
    index = 0;

  if ( small_blind )
  {
    // player bets small_blind
    player_bets.at(index) += 5;
    small_blind = false;
    deck.pot += 5;
    ++index;
    continue;
  }

  if ( big_blind )
  {
    // player bets big_blind
    player_bets.at(index) += 10;
    big_blind = false;
    deck.pot += 10;
    ++index;
    continue;
  }

  COUT << "Player " << gameplayers.at(index).player_num <<  ", please enter how much you would like to bet: ";
  CIN >> betamt;

  if ( betamt == -1 )
  {
    COUT << ENDL << "\tPlayer " << gameplayers.at(index).player_num << " has folded." << ENDL << ENDL;
    gameplayers.erase(std::next(gameplayers.begin() + index - 1));
    player_bets.erase(std::next(player_bets.begin() + index - 1));
    users = users - 1;

    continue;
  }

  if ( betamt == -2 && player_bets.at(index) == highest_bet(player_bets) )
  {
    COUT << ENDL << "\tPlayer " << gameplayers.at(index).player_num << " has checked." << ENDL;
    betamt = 0;
  }

  // only for ones w/ blinds
  if ( index == 0 )
    betamt += 5;
  if ( index == 1 )
    betamt += 10;

  if ( betamt + player_bets.at(index) < highest_bet(player_bets) )
  {
    while ( betamt + player_bets.at(index) <  highest_bet(player_bets) ) {
      COUT << "Invalid bet. Try again: ";
      CIN >> betamt;
    }
  }

  // only for ones w/ blinds
  if ( index == 0 )
    betamt -= 5;
  if ( index == 1 )
    betamt -= 10;

  if ( index == 0 ) {
    small_blind_print += betamt;
  }

  curr_bet = gameplayers.at(index).bet(betamt);

  deck.pot += curr_bet;
  player_bets.at(index) += curr_bet;

  COUT << ENDL << "\tTotal Player Bets | ";

  COUT << "Player " << gameplayers.at(0).player_num << ": " << small_blind_print << ", ";

  for (long unsigned int iter = 1; iter < gameplayers.size(); iter ++ ) {
    COUT << "Player " << gameplayers.at(iter).player_num << ": " << player_bets.at(iter);
    if (iter != (gameplayers.size() - 1) ) {
      COUT << ", ";
    }
  }

  COUT << ENDL << ENDL;

  ++index;
} while ( !same_bet( player_bets ) );


//after the first round of betting, three cards are laid out on the table
   deck.deal_to_table();
   deck.deal_to_table();
   deck.deal_to_table();

  COUT << ENDL << "Now we will enter the second round of betting. To fold, type -1. To check, type -2." << ENDL << ENDL;

//print out status
   COUT << ENDL << "\t\t Cards \t Money \t Hand \t Highest Cards" << ENDL;
   i = 0;
   while(i < 10){
      COUT << "----------";
      ++i;
   }
   COUT << ENDL;

   for (long unsigned int iter = 0; iter < gameplayers.size(); iter ++ ) {
     gameplayers.at(iter).cur_hand = gameplayers.at(iter).find_hand( deck.table_cards );
   }

   i = 0;
   while ( i < users) {
      COUT << gameplayers.at(i) << ENDL; //uses friend operator
      std::vector<float> probs = gameplayers.at(i).calc_postflop( deck.table_cards );
      COUT << "         | ";
      for ( int i = 0; i < probs.size(); ++i )
      {
        if ( i == HIGH_CARD )
        {
          if ( probs.at(i) != 0 )
          {
            COUT << "High Card Probability: " << probs.at(i) << "%  ";
          }
        }
        if ( i == PAIR )
        {
          if ( probs.at(i) != 0 )
          {
            COUT << "Pair Probability: " << probs.at(i) << "%  ";
          }
        }
        if ( i == TWO_PAIR )
        {
          if ( probs.at(i) != 0 )
          {
            COUT << "Two Pair Probability: " << probs.at(i) << "%  ";
          }
        }
        if ( i == THREE_OF_A_KIND )
        {
          if ( probs.at(i) != 0 )
          {
            COUT << "Three of a Kind Probability: " << probs.at(i) << "%  ";
          }
        }
        if ( i == STRAIGHT )
        {
          if ( probs.at(i) != 0 )
          {
            COUT << "Straight Probability: " << probs.at(i) << "%  ";
          }
        }
        if ( i == FLUSH )
        {
          if ( probs.at(i) != 0 )
          {
            COUT << "Flush Probability: " << probs.at(i) << "%  ";
          }
        }
        if ( i == FULL_HOUSE )
        {
          if ( probs.at(i) != 0 )
          {
            COUT << "Full House Probability: " << probs.at(i) << "%  ";
          }
        }
        if ( i == FOUR_OF_A_KIND )
        {
          if ( probs.at(i) != 0 )
          {
            COUT << "Four of a Kind Probability: " << probs.at(i) << "%  ";
          }
        }
        if ( i == STRAIGHT_FLUSH )
        {
          if ( probs.at(i) != 0 )
          {
            COUT << "Straight Flush Probability: " << probs.at(i) << "%  ";
          }
        }
      }
      COUT << ENDL;
      ++i;
   }
   COUT << deck << ENDL << ENDL;

for (int i = 0; i < player_bets.size(); ++i )
{
  player_bets.at(i) = 0;
}

index = 0;
int counter = 0;
do {
  if ( index == users )
    index = 0;

  COUT << "Player " << gameplayers.at(index).player_num <<  ", please enter how much you would like to bet: ";
  CIN >> betamt;


  if ( betamt == -1 )
  {
    COUT << ENDL << "\tPlayer " << gameplayers.at(index).player_num << " has folded." << ENDL << ENDL;
    gameplayers.erase(std::next(gameplayers.begin() + index - 1));
    player_bets.erase(std::next(player_bets.begin() + index - 1));
    users = users - 1;

    continue;
  }

  if ( betamt == -2 && player_bets.at(index) == highest_bet(player_bets) )
  {
    COUT << ENDL << "\tPlayer " << gameplayers.at(index).player_num << " has checked." << ENDL;
    betamt = 0;
  }


  if ( betamt + player_bets.at(index) < highest_bet(player_bets) )
  {
    while ( betamt + player_bets.at(index) <  highest_bet(player_bets) ) {
      COUT << "Invalid bet. Try again: ";
      CIN >> betamt;
    }
  }


    curr_bet = gameplayers.at(index).bet(betamt);

    deck.pot += curr_bet;
    player_bets.at(index) += curr_bet;

  COUT << ENDL << "\tTotal Player Bets | ";

  for (long unsigned int iter = 0; iter < gameplayers.size(); iter ++ ) {
    COUT << "Player " << gameplayers.at(iter).player_num << ": " << player_bets.at(iter);
    if (iter != (gameplayers.size() - 1) ) {
      COUT << ", ";
    }
  }

  COUT << ENDL << ENDL;

  ++counter;
  ++index;
} while ( !same_bet( player_bets ) || counter < users);

//deal another card to the table
   deck.deal_to_table(); // Turn

   COUT << ENDL <<"Now we will enter the third round of betting. To fold, type -1. To check, type -2." << ENDL << ENDL;
//print out status
   COUT << ENDL << "\t\t Cards \t Money \t Hand \t Highest Cards" << ENDL;
   i = 0;
   while(i < 10){
      COUT << "----------";
      ++i;
   }
   COUT << ENDL;

   for (long unsigned int iter = 0; iter < gameplayers.size(); iter ++ ) {
     gameplayers.at(iter).cur_hand = gameplayers.at(iter).find_hand( deck.table_cards );
   }

   i = 0;
   while ( i < users) {
      COUT << gameplayers.at(i) << ENDL; //uses friend operator
      std::vector<float> probs = gameplayers.at(i).calc_postturn( deck.table_cards );
      COUT << "         | ";
      for ( int i = 0; i < probs.size(); ++i )
      {
        if ( i == HIGH_CARD )
        {
          if ( probs.at(i) != 0 )
          {
            COUT << "High Card Probability: " << probs.at(i) << "%  ";
          }
        }
        if ( i == PAIR )
        {
          if ( probs.at(i) != 0 )
          {
            COUT << "Pair Probability: " << probs.at(i) << "%  ";
          }
        }
        if ( i == TWO_PAIR )
        {
          if ( probs.at(i) != 0 )
          {
            COUT << "Two Pair Probability: " << probs.at(i) << "%  ";
          }
        }
        if ( i == THREE_OF_A_KIND )
        {
          if ( probs.at(i) != 0 )
          {
            COUT << "Three of a Kind Probability: " << probs.at(i) << "%  ";
          }
        }
        if ( i == STRAIGHT )
        {
          if ( probs.at(i) != 0 )
          {
            COUT << "Straight Probability: " << probs.at(i) << "%  ";
          }
        }
        if ( i == FLUSH )
        {
          if ( probs.at(i) != 0 )
          {
            COUT << "Flush Probability: " << probs.at(i) << "%  ";
          }
        }
        if ( i == FULL_HOUSE )
        {
          if ( probs.at(i) != 0 )
          {
            COUT << "Full House Probability: " << probs.at(i) << "%  ";
          }
        }
        if ( i == FOUR_OF_A_KIND )
        {
          if ( probs.at(i) != 0 )
          {
            COUT << "Four of a Kind Probability: " << probs.at(i) << "%  ";
          }
        }
        if ( i == STRAIGHT_FLUSH )
        {
          if ( probs.at(i) != 0 )
          {
            COUT << "Straight Flush Probability: " << probs.at(i) << "%  ";
          }
        }
      }
      COUT << ENDL;
      ++i;
   }
   COUT << deck << ENDL << ENDL;

   for (int i = 0; i < player_bets.size(); ++i )
   {
     player_bets.at(i) = 0;
   }

   index = 0;
   counter = 0;
   do {
     if ( index == users )
       index = 0;

     COUT << "Player " << gameplayers.at(index).player_num <<  ", please enter how much you would like to bet: ";
     CIN >> betamt;

     if ( betamt == -1 )
     {
       COUT << ENDL << "\tPlayer " << gameplayers.at(index).player_num << " has folded." << ENDL << ENDL;
       gameplayers.erase(std::next(gameplayers.begin() + index - 1));
       player_bets.erase(std::next(player_bets.begin() + index - 1));
       users = users - 1;

       continue;
     }

     if ( betamt == -2 && player_bets.at(index) == highest_bet(player_bets) )
     {
       COUT << ENDL << "\tPlayer " << gameplayers.at(index).player_num << " has checked." << ENDL;
       betamt = 0;
     }

     if ( betamt + player_bets.at(index) < highest_bet(player_bets) )
     {
       while ( betamt + player_bets.at(index) <  highest_bet(player_bets) ) {
         COUT << "Invalid bet. Try again: ";
         CIN >> betamt;
       }
     }

       curr_bet = gameplayers.at(index).bet(betamt);

       deck.pot += curr_bet;
       player_bets.at(index) += curr_bet;

     COUT << ENDL << "\tTotal Player Bets | ";

     for (long unsigned int iter = 0; iter < gameplayers.size(); iter ++ ) {
       COUT << "Player " << gameplayers.at(iter).player_num << ": " << player_bets.at(iter);
       if (iter != (gameplayers.size() - 1) ) {
         COUT << ", ";
       }
     }

     COUT << ENDL << ENDL;

     ++counter;
     ++index;
   } while ( !same_bet( player_bets ) || counter < users);

   COUT << ENDL <<"Now we will enter the fourth and final round of betting. To fold, type -1. To check, type -2." << ENDL << ENDL;

//print out status
   COUT << ENDL << "\t\t Cards \t Money \t Hand \t Highest Cards \t Probability" << ENDL;
   i = 0;
   while(i < 10){
      COUT << "----------";
      ++i;
   }
   COUT << ENDL;

   for (long unsigned int iter = 0; iter < gameplayers.size(); iter ++ ) {
     gameplayers.at(iter).cur_hand = gameplayers.at(iter).find_hand( deck.table_cards );
   }

   i = 0;
   while ( i < users) {
      COUT << gameplayers.at(i) << ENDL; //uses friend operator
      ++i;
   }

  deck.deal_to_table();

  COUT << deck << ENDL << ENDL; // River

  for (int i = 0; i < player_bets.size(); ++i )
  {
    player_bets.at(i) = 0;
  }

  for (long unsigned int iter = 0; iter < gameplayers.size(); iter ++ ) {
    gameplayers.at(iter).cur_hand = gameplayers.at(iter).find_hand( deck.table_cards );
  }

  index = 0;
  counter = 0;
  do {
    if ( index == users )
      index = 0;

    COUT << "Player " << gameplayers.at(index).player_num <<  ", please enter how much you would like to bet: ";
    CIN >> betamt;

    if ( betamt == -1 )
    {
      COUT << ENDL << "\tPlayer " << gameplayers.at(index).player_num << " has folded." << ENDL << ENDL;
      gameplayers.erase(std::next(gameplayers.begin() + index - 1));
      player_bets.erase(std::next(player_bets.begin() + index - 1));
      users = users - 1;

      continue;
    }

    if ( betamt == -2 && player_bets.at(index) == highest_bet(player_bets) )
    {
      COUT << ENDL << "\tPlayer " << gameplayers.at(index).player_num << " has checked." << ENDL;
      betamt = 0;
    }


    if ( betamt + player_bets.at(index) < highest_bet(player_bets) )
    {
      while ( betamt + player_bets.at(index) <  highest_bet(player_bets) ) {
        COUT << "Invalid bet. Try again: ";
        CIN >> betamt;
      }
    }

    curr_bet = gameplayers.at(index).bet(betamt);

    deck.pot += curr_bet;
    player_bets.at(index) += curr_bet;

    COUT << ENDL << "\tTotal Player Bets | ";

    for (long unsigned int iter = 0; iter < gameplayers.size(); iter ++ ) {
      COUT << "Player " << gameplayers.at(iter).player_num << ": " << player_bets.at(iter);
      if (iter != (gameplayers.size() - 1) ) {
        COUT << ", ";
      }
    }

    COUT << ENDL << ENDL;

    ++counter;
    ++index;
  } while ( !same_bet( player_bets ) || counter < users);

   std::vector<Player> leaderboard;

   leaderboard = compare_hand( gameplayers );
   Player temp(0);

   COUT << ENDL;

   int index_1 = 0;
   int index_2 = 0;

   if ( leaderboard.at(0).cur_hand.the_rank  == leaderboard.at(1).cur_hand.the_rank &&
      leaderboard.at(0).cur_hand.first == leaderboard.at(1).cur_hand.first &&
      leaderboard.at(0).cur_hand.second == leaderboard.at(1).cur_hand.second) {

      gameplayers.at(leaderboard.at(0).player_num - 1).player_money += deck.get_pot() / 2;
      gameplayers.at(leaderboard.at(1).player_num - 1).player_money += deck.get_pot() / 2;

      COUT << "Player " << gameplayers.at(leaderboard.at(0).player_num - 1).player_num << " and Player " <<
        gameplayers.at(leaderboard.at(1).player_num - 1).player_num << " are tied as winners." << ENDL << "Player " <<
        gameplayers.at(leaderboard.at(0).player_num - 1).player_num << "'s total money is now " <<
        gameplayers.at(leaderboard.at(0).player_num - 1).player_money << " and Player " <<
        gameplayers.at(leaderboard.at(1).player_num - 1).player_num << "'s total money is now " <<
        gameplayers.at(leaderboard.at(1).player_num - 1).player_money << "." << ENDL << ENDL;

    } else {

      gameplayers.at(leaderboard.at(0).player_num - 1).player_money += deck.get_pot();

      COUT << "Player " << gameplayers.at(leaderboard.at(0).player_num - 1).player_num << " won. Their best hand is " << "\e[1m" <<
        temp.enum_to_string_rank(gameplayers.at(leaderboard.at(0).player_num - 1).cur_hand.the_rank) << "\e[0m" <<
        ". " << ENDL << "Player " << gameplayers.at(leaderboard.at(0).player_num - 1).player_num << "'s total money is now " <<
        gameplayers.at(leaderboard.at(0).player_num - 1).player_money << "." << ENDL << ENDL;

      }

//end of game
   COUT << "This is the end of the game. Great game everyone!!!" << ENDL;

   deck.reset_pot();

   return 0;

}
