#ifndef PLAYER_H
#define PLAYER_H

#include “deck.h”

typedef struct chips {

  int white;
  int red;
  int blue;
  int green;

  int total = (white * 1) + (red * 5) + (blue * 10) + (green * 25);

} chips ;

class Player {

  private:

    int player_num;

    chips player_chips;

    std::vector<Card> player_cards;

  public:

    Player ();

    void get_chips ();

    void fold ( std::vector<Card> player_cards, int player_num );

    int bet ( chips player_chips );

    std::vector<Card> get_player_cards () const;


} ;

#endif
