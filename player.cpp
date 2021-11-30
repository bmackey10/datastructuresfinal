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

void fold ( std::vector<Card> player_cards, int player_num ) {

  std::cout << "Player " << player_num << " has folded." << std::endl;

  player_cards.clear();

}

int bet ( chips player_chips ) { // work on this logic

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

std::vector<Card> get_player_cards () const {

  return player_cards;

}
