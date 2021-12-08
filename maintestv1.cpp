#include <iostream>
#include <cstdlib> 
#include <time.h> 

//#include "deck.h"
//#include "player.h"
//#include "probability.h"

#define COUT std::cout
#define CIN std::cin
#define smallblind 5
#define bigblind 10
//#define ENDL std::endl

int main(/*const int argc, const char* argv[]*/){

   int users= 0, betamt= 0, pot = 0; 

//asks the user how many players
   COUT << "Enter the number of players that will be playing (there must be at least 3): "; 
   CIN >> users; //equal to "player_num" in player class

//instantiate that many players by creating a vector and pushing back as many users as entered 
   Player p; 
   std::vector<Player> gameplayers(user, p); 
   /*int i = 0;
   while (i < users)
   {
      Player p;
      gameplayers.push_back(p.at(i));
      i++; 
   }*/

//initialize the deck
   Deck deck;
   deck(); //default constructor 
//then shuffle it 
   deck.shuffle();

//assign two cards to each player 
   int i = 0; 
   while(i < users){ 
      p.at(i).player_cards.push_back(deck.deal_to_player()); 
      p.at(i).player_cards.push_back(deck.deal_to_player()); 
      i++;   
   }

//to stay in the game, each player must match the highest bet 
//asks the user for their bet
   // deck.pot(); //sets the pot
   /*int smallinc= 0; //the small blind incrementer 
   int biginc = 1; //the big blind incrementer 
   p.at(smallinc).bet(smallblind); //the small blind makes the small blind bet of 5
   p.at(biginc).bet(bigblind); //the big blind makes the big blind bet of 10 
   pot = pot + smallblind + bigblind; 
*/

   COUT << "The small blind has made their bet to be %d\n" << smallblind;
   COUT << "The big blind has made their bet to be %d\n" << bigblind; 
   COUT << "Enter how much you would like to bet. Your bet must at the least match the big blind's bet amount: ";    
   CIN >> betamt; 
   if(betamt < 0 || betamt < bigblind){
      COUT << "Invalid bet amount. Try again: ";   
      CIN >> betamt;
   }
//everybody will match the big blind for the first round, but for the rounds after, we will randomize (within reason) how much is bet by each player 
//after big and small blinds set their bets, user will enter theirs and for simplicity, we will have the other random players bet the same amount as the user
   i = 2; 
   int biggestbet = betamt; //the users amount bet is the current highest bet amount 
   while (i < users){
      srand(time(NULL)); 
      int randbet = rand() % (biggestbet + 5) + biggestbet; //random bet made from (the biggest bet made) to (the biggest bet made plus 5) 
      p.at(i).bet(randbet, );
      pot += betamt;
      i++;
   }
   pot = pot - smallblind; 
   p.at(smallinc).bet(betamt); //finally goes back around to the small blind to set it equal to the lowest amount that was bet
   pot = pot + betamt; 

//rotate the vector for the blinds 
 /*  i = 0; 
      Player temp = p.at(0); 
   while(i < users -1){
      p.at(i) = p.at(i+1); 
      i++; 
   }
      p.at(users) = temp; 
*/



//after the first round of betting, three cards are laid out on the table 
   deck.table_cards.push_back(deck.at(0).deal_to_table()); 
   deck.table_cards.push_back(deck.at(1).deal_to_table()); 
   deck.table_cards.push_back(deck.at(2).deal_to_table()); 



   COUT << "\t Cards \t Money \t Hand \t Highest Cards \t Probability\n"
   i = 0; 
   while(i < 5){
      COUT << "----------"; 
   }  
   COUT << "\n";


   i = 0; 
   while ( i < users) {
      COUT << p.at(i) << ENDL; //uses friend operator 
   }
   COUT << deck << ENDL;

//then another round of betting
//if the player folds, pop them from the vector 

   return 0; 
}


/*

//case statement: fold, bet, check, call
   //call fold function
   //check -> dont do anything, skip over the player and go to the next in the case statement 
   //call-> three inputs: the bet amount, (only used if raising), the highest bet ( an int) and the highest bet thats been made becuase ti has to be natched or higher, a bool called bet type and if this is = 0, the player is calling which is matching the highets bid, for betting, the bool is equal to 1, then raise/bet and the bet amuont will be passed in and then add this to the pot 
      //then add the highest amount to the pot

//each player is dealt to cards (we will use a hash table to keep track of what is dealt) that only they can see
//use dealing function from deck class as many times as the number of players; the user will be player 0 
//the dealer eventually spreads five community cards; initially three are down at once, then one each time during a subsequent round to form the board
//during each round, the players in the game use the cards from the boad as well as their own two cards to make the best possible combination of five out of the seven given cards 


//the player clockwise of the dealer makes the "small blind" which is the first bet
//we will make player(0) the small blind by default and then have the lowest value player number be the small blind in the cases that some have folded
//we can randomize the bet as long as its greatest then the last one
//the person clockwise of the small blind makes the "big blind" which is usually twice as much but depends
//make a vector and rotate for the players and indices 
   int smallblind = 0;//make the small blind player 1 by default 
   playernum.Player(smallblind).bet(betamt);
   pot = betamt; 
   int bigblind = 1; //makes big blind player 2 by default
   betamt = betamt*2; //doubles the smallblind
   playernum.Player(bigblind).bet(betamt);
   pot = pot + betamt; 
   //int maxbet= betamt;  //the max bet amount is the current bet amount set by the big blind
   int i;
   for(i = 2; i < users; i++){
      srand(time(NULL));
      int num = rand() % 100 + betamt; //random bet made from the bet amount set by the big blind and 100 (the players amount of money) 
      playernum.Player(i).bet(num);
      betamt = num; //sets the new bet amount to num so it can only be as low as the highest bet made 
      //if(betamt > maxbet){ //if the bet amount is greater than the current max bet (which isintiially the big blind bet), then set the max bet to that 
         //maxbet = betamt; 
      //}
      pot = pot + betamt; 
   }


//after these two bets are placed, each player receives their two cards from the dealer, and betting action proceeds clockwise around the table with the player immediately clockwise to the big blind
   Card c1, c2; 
   for(i = 0; i < users; i++){
      c1.card(0)=playernum.Player(i).deal_to_player();  playernum.Player(i).deal_to_player(); //how do we use deal to player to assign them two cards? 
      c2.card(1) = playernum.Player(i).deal_to_player(); 
   }
   COUT << "Your current cards are a " << << " and a " << ;

   COUT << "The current bet amount is: " << betamt; 
   playernum.Player(0).bet(betamt);
   int i;
   for(i = 1; i < users; i++){
      srand(time(NULL));
      int num = rand() % 100+  betamt; //random bet made from the bet amount set by the small blind and 100 (the players amount of money) 
      playernum.Player(i).bet(num);
      betamt = num; //sets the new bet amount to num so it can only be as low as the highest bet made 
   }

*/



//   //In poker betting the action options are “fold”, “check”, “call”, or “raise”, and the specific actions available depend on the action taken by previous players.
//      //If no one has made a bet yet in that round, the player may check, which means to decline to bet, or bet.
//         //If a player has bet, the player may fold, call, or raise. Folding means giving up your cards, effectively taking yourself out of the game. Calling is matching the highest previous bet made by a player in the round. Raising is to bet but it must be higher than the previous highest bet.
//            //





//how to compile: g++ -o maintest maintest.cpp
//COUT << "user: " << users;


//Player::Player(int num ) : player_num( ), player_money( 100 ), player_cards( ) {
//    player_num(int num);
// }
