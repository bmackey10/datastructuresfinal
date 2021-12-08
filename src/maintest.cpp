#include <iostream>
#include <cstdlib> 
#include <time.h> 
#include <vector>

#include "deck.h"
#include "player.h"
//#include "probability.h"

#define COUT std::cout
#define CIN std::cin
#define smallblind 5
#define bigblind 10
#define ENDL std::endl

/* void reiter(int &highest_bet, int i){  //loops back through players including small blind
   int j = 0; 
   while(j < i){
      COUT << "Player %d" << (j+1) <<", please re-enter how much you would like to bet since player %d" << (i+1) << "raised the bet amount to %d: " << highest_bet; 
      CIN >> betamt; 
      p.at(j).bet(betamt, 1, NULL);          
      j++; 
   }

} */

int main() {

   int stillPlaying = 1; 

   while(stillPlaying == 1){


   int users= 0, betamt= 0, pot = 0, highest_bet= 0; 

//asks the user how many players
   COUT << "Enter the number of players that will be playing (there must be at least 3): "; 
   CIN >> users; //equal to "player_num" in player class

//instantiate that many players by creating a vector and pushing back as many users as entered 
   Player p; 
   std::vector<Player> gameplayers; 
   int i = 1;
   while (i <= users)
   {
      Player p;
      gameplayers.push_back(p(i));
      i++; 
   }

//initialize the deck
   Deck deck;
   deck(); //default constructor 
//then shuffle it 
   deck.shuffle();

//assign two cards to each player 
   int i = 0; 
   while(i < users){ 
      gameplayers.p.at(i).player_cards.push_back(deck.deal_to_player()); 
      gameplayers.p.at(i).player_cards.push_back(deck.deal_to_player()); 
      i++;   
   }
//print out cards                                                                                
   COUT<<"Now we will enter the first round of betting. To fold, type -1. To call, type 0.\n" ;

//first round of betting
   i = 0; 
   COUT << "Player %d, you are the small blind. You will bet 5 chips to start the game." << (i+1);
   //CIN >> betamt; 
   /* if(betamt == -1){
      gameplayers.p.at(i).fold( gameplayers.p.at(i).player_cards, gameplayers.p.at(i).player_num ); //erases players from that index
      gameplayers.erase(std::next(gameplayers.begin() + i));
   } */
   p.at(i).bet(smallblind, 1, NULL); 
   highest_bet = smallblind; 
   i++;

   COUT << "Player %d, you are the big blind. You will bet 10 chips to double the small blind. " << (i+1); //assume user will bet twice as much
   //CIN >> betamt; 
   /* if(betamt == -1){
      gameplayers.p.at(i).fold( gameplayers.p.at(i).player_cards, gameplayers.p.at(i).player_num ); //erases players from that index
      gameplayers.erase(std::next(gameplayers.begin() + i));
   } */
   p.at(i).bet(bigblind, 1, NULL); 
   highest_bet = bigblind; 
   i++; //i now starts at player 3, where i = 2 


   while( i < users){
      COUT << "Player %d, please enter how much you would like to bet: " << (i+1);
      CIN >> betamt; 
//if fold
      if(betamt == -1){
         gameplayers.p.at(i).fold( gameplayers.p.at(i).player_cards, gameplayers.p.at(i).player_num ); //erases players from that index
         gameplayers.erase(std::next(gameplayers.begin() + i));
      }
//if bet amount is less than the big blind
      if(betamt < highest_bet && betamt != 0){
         COUT << "Invalid bet amount. Try again: ";   
         CIN >> betamt;
      }
//if bet amount is higher than the highest bet 
      if(betamt > highest_bet){
         highest_bet = betamt;
         p.at(i).bet(betamt, 1, NULL); 
         int j = 0; 
         while(j < i){
            COUT << "Player %d" << (j+1) <<", please re-enter how much you would like to bet since player %d" << (i+1) << "raised the bet amount to %d: " << highest_bet; 
            CIN >> betamt;
            if (betamt == -1) {
               gameplayers.p.at(i).fold( gameplayers.p.at(i).player_cards, gameplayers.p.at(i).player_num ); //erases players from that index
               gameplayers.erase(std::next(gameplayers.begin() + i));
            } else if(betamt < highest_bet && betamt != 0){
               COUT << "Invalid bet amount. Try again: ";   
               CIN >> betamt;
            } else if (bet_amt == 0 || bet_amt == highest_bet) {
                p.at(i).bet(NULL, 0, highest_bet); 
            } else {
               p.at(j).bet(betamt, 1, NULL);
            }          
            j++; 
        }
      }
      if (bet_amt == 0 || bet_amt == highest_bet) {
          p.at(i).bet(NULL, 0, highest_bet); 
      }
      i++; 
   }


//gets the pot amount
   int numPlayers = gameplayers.size(); 
   pot = highest_bet * numPlayers; 
   


//after the first round of betting, three cards are laid out on the table 
   deck.table_cards.push_back(deck.at(0).deal_to_table()); 
   deck.table_cards.push_back(deck.at(1).deal_to_table()); 
   deck.table_cards.push_back(deck.at(2).deal_to_table()); 



//print out status
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


COUT<<"Now we will enter the second round of betting. To fold, type -1. To call, type 0.\n" ;
//then second round of betting; add check function (skips player and goes next by using continue in the if statement ) 
   i =0; 
   while( i < users){
      COUT << "Player %d, please enter how much you would like to bet: " << (i+1);
      CIN >> betamt; 
//if fold
      if(betamt == -1){
         gameplayers.p.at(i).fold( gameplayers.p.at(i).player_cards, gameplayers.p.at(i).player_num ); //erases players from that index
         gameplayers.erase(std::next(gameplayers.begin() + i));
      }
//if bet amount is less than the big blind
      if(betamt < highest_bet && betamt != 0){
         COUT << "Invalid bet amount. Try again: ";   
         CIN >> betamt;
      }
//if bet amount is higher than the highest bet 
      if(betamt > highest_bet){
         highest_bet = betamt;
         p.at(i).bet(betamt, 1, NULL); 
         int j = 0; 
         while(j < i){
            COUT << "Player %d" << (j+1) <<", please re-enter how much you would like to bet since player %d" << (i+1) << "raised the bet amount to %d: " << highest_bet; 
            CIN >> betamt;
            if (betamt == -1) {
               gameplayers.p.at(i).fold( gameplayers.p.at(i).player_cards, gameplayers.p.at(i).player_num ); //erases players from that index
               gameplayers.erase(std::next(gameplayers.begin() + i));
            } else if(betamt < highest_bet && betamt != 0){
               COUT << "Invalid bet amount. Try again: ";   
               CIN >> betamt;
            } else if (bet_amt == 0 || bet_amt == highest_bet) {
                p.at(i).bet(NULL, 0, highest_bet); 
            } else {
               p.at(j).bet(betamt, 1, NULL);
            }          
            j++; 
        }
      }
      if (bet_amt == 0 || bet_amt == highest_bet) {
          p.at(i).bet(NULL, 0, highest_bet); 
      }
      i++; 
   }
   pot = pot + (highest_bet * numPlayers); 







//then deal another card to the table
   deck.table_cards.push_back(deck.at(3).deal_to_table());  
//then print out status
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
COUT<<"Now we will enter the third round of betting. To fold, type -1. To call, type 0.\n" ;
//then second round of betting; add check function (skips player and goes next by using continue in the if statement ) 
   i =0; 
   while( i < users){
      COUT << "Player %d, please enter how much you would like to bet: " << (i+1);
      CIN >> betamt; 
//if fold
      if(betamt == -1){
         gameplayers.p.at(i).fold( gameplayers.p.at(i).player_cards, gameplayers.p.at(i).player_num ); //erases players from that index
         gameplayers.erase(std::next(gameplayers.begin() + i));
      }
//if bet amount is less than the big blind
      if(betamt < highest_bet && betamt != 0){
         COUT << "Invalid bet amount. Try again: ";   
         CIN >> betamt;
      }
//if bet amount is higher than the highest bet 
      if(betamt > highest_bet){
         highest_bet = betamt;
         p.at(i).bet(betamt, 1, NULL); 
         int j = 0; 
         while(j < i){
            COUT << "Player %d" << (j+1) <<", please re-enter how much you would like to bet since player %d" << (i+1) << "raised the bet amount to %d: " << highest_bet; 
            CIN >> betamt;
            if (betamt == -1) {
               gameplayers.p.at(i).fold( gameplayers.p.at(i).player_cards, gameplayers.p.at(i).player_num ); //erases players from that index
               gameplayers.erase(std::next(gameplayers.begin() + i));
            } else if(betamt < highest_bet && betamt != 0){
               COUT << "Invalid bet amount. Try again: ";   
               CIN >> betamt;
            } else if (bet_amt == 0 || bet_amt == highest_bet) {
                p.at(i).bet(NULL, 0, highest_bet); 
            } else {
               p.at(j).bet(betamt, 1, NULL);
            }          
            j++; 
        }
      }
      if (bet_amt == 0 || bet_amt == highest_bet) {
          p.at(i).bet(NULL, 0, highest_bet); 
      }
      i++; 
   }
   pot = pot + (highest_bet * numPlayers); 

//deal another card to the table
   deck.table_cards.push_back(deck.at(4).deal_to_table()); 
//print out status
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




//final round of betting 
COUT<<"Now we will enter the last round of betting. To fold, type -1. To call, type 0.\n" ;
//then second round of betting; add check function (skips player and goes next by using continue in the if statement ) 
   i =0; 
   while( i < users){
      COUT << "Player %d, please enter how much you would like to bet: " << (i+1);
      CIN >> betamt; 
//if fold
      if(betamt == -1){
         gameplayers.p.at(i).fold( gameplayers.p.at(i).player_cards, gameplayers.p.at(i).player_num ); //erases players from that index
         gameplayers.erase(std::next(gameplayers.begin() + i));
      }
//if bet amount is less than the big blind
      if(betamt < highest_bet && betamt != 0){
         COUT << "Invalid bet amount. Try again: ";   
         CIN >> betamt;
      }
//if bet amount is higher than the highest bet 
      if(betamt > highest_bet){
         highest_bet = betamt;
         p.at(i).bet(betamt, 1, NULL); 
         int j = 0; 
         while(j < i){
            COUT << "Player %d" << (j+1) <<", please re-enter how much you would like to bet since player %d" << (i+1) << "raised the bet amount to %d: " << highest_bet; 
            CIN >> betamt;
            if (betamt == -1) {
               gameplayers.p.at(i).fold( gameplayers.p.at(i).player_cards, gameplayers.p.at(i).player_num ); //erases players from that index
               gameplayers.erase(std::next(gameplayers.begin() + i));
            } else if(betamt < highest_bet && betamt != 0){
               COUT << "Invalid bet amount. Try again: ";   
               CIN >> betamt;
            } else if (bet_amt == 0 || bet_amt == highest_bet) {
                p.at(i).bet(NULL, 0, highest_bet); 
            } else {
               p.at(j).bet(betamt, 1, NULL);
            }          
            j++; 
        }
      }
      if (bet_amt == 0 || bet_amt == highest_bet) {
          p.at(i).bet(NULL, 0, highest_bet); 
      }
      i++; 
   }
   pot = pot + (highest_bet * numPlayers); 

//print out status
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









//end of game
   COUT << "This is the end of the game. Great game everyone!!!"; 

   //ask user if they want to play another game
   char another;
   COUT<< "Would you like to play another game? Type y or n: "; //need to reset varubales and rotate the small blind/big blind vector
   CIN >> another;

   if(another == 'n'){
      stillPlaying = 0; 
   }
   else(){
      //rotate the vector for the blinds
      i = 0; 
      Player temp = p.at(0); 
      while(i < users -1){
         p.at(i) = p.at(i+1); 
         i++; 
      }
      p.at(users) = temp; 
   }//end of else loop

   }//end of while loop

   return 0; 

}//end of main


