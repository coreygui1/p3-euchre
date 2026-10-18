#include <iostream>
#include <fstream>
#include "Player.hpp"
#include "Pack.hpp"
#include <vector>
using namespace std;

class Game{
    public:
        //constructor
        Game(Pack pack_in, std::vector<Player*> players_in, bool shuffle_in, 
            int win_points_in): pack(pack_in), players(players_in), shuffle(shuffle_in),
            win_points(win_points_in){};
        // Playing the game
        void play(){
            int team1_score = 0;
            int team2_score = 0; 
            int hand_num = 0;
            int dealer_num = 0;
            while (team1_score < win_points && team2_score < win_points){
                if (shuffle){
                    pack.shuffle();
                }
                else{
                    pack.reset();
                }
                hand(hand_num, dealer_num, team1_score, team2_score);
                hand_num++;
                dealer_num = (dealer_num + 1) % 4;
                cout << players[0]->get_name() << " and " << players[2]->get_name() <<
                " have "<< team1_score<< " points" << endl; 
                cout << players[1]->get_name() << " and " << players[3]->get_name() <<
                " have "<< team2_score<< " points" << endl; 
                cout << endl;
            }
            if(team1_score > team2_score){
                cout << players[0]->get_name() << " and " << players[2]->get_name() << " win!" << endl;
            }
            else{
                cout << players[1]->get_name() << " and " << players[3]->get_name() << " win!" << endl;
            }


        }

    private:
        Pack pack; //The pack used for the game
        std::vector<Player*> players; // Vector of each of the players for the game
        bool shuffle; // Is the pack going to be shuffled
        int win_points; // how many points are needed to win

        // function to deal the cards
        // dealer_num is the index of the dealer, which is the same as hand%4
        void deal(const int &dealer_num){ 
            //round 1
            for (int i =1; i<5; ++i){
                if(i%2 == 1){
                    for (int j = 0; j<3;++j){
                        const Card deal = pack.deal_one();
                        players[(i+dealer_num)%4]->add_card(deal);
                    } 
                }
                else{
                    for (int j = 0; j<2;++j){
                        const Card deal = pack.deal_one();
                        players[(i+dealer_num)%4]->add_card(deal);
                    } 
                }
            }
            //round 2
            for (int i =1; i<5; ++i){
                if(i%2 == 1){
                    for (int j = 0; j<2;++j){
                        const Card deal = pack.deal_one();
                        players[(i+dealer_num)%4]->add_card(deal);
                    } 
                }
                else{
                    for (int j = 0; j<3;++j){
                        const Card deal = pack.deal_one();
                        players[(i+dealer_num)%4]->add_card(deal);
                    } 
                }
            }
        }
        
        Card make_upcard(){
            Card upcard = pack.deal_one();
            cout << upcard << " turned up"<<endl;
            return upcard;
        }

        // function to create the trump suit. We return the trump suit and the index of the player 
        //     who made trump. 
        Suit create_trump(const Card &upcard, const int &dealer_num, int &made_trump){
            Suit order_up = SPADES;
            //round 1
            for (int r = 1; r<3; ++r){
                for (int i = 1; i < 5; ++i){
                    if (i==4){
                        if (players[dealer_num]->make_trump(upcard, true, r, order_up)){
                            made_trump = (i+dealer_num)%4;
                            cout << players[dealer_num]->get_name() << " orders up " << order_up << endl;
                            
                            if (r == 1){
                                players[dealer_num]->add_and_discard(upcard);
                            }
                            cout << endl;
                            return order_up;
                        }
                        else{
                            cout << players[dealer_num]->get_name() << " passes" << endl;
                        }
                    }
                    else{
                        if(players[(i+dealer_num)%4]->make_trump(upcard, false, r, order_up)){
                            made_trump = (i+dealer_num)%4;
                            cout << players[(i+dealer_num)%4]->get_name() << " orders up " <<
                                     order_up << endl;
                            if (r == 1){
                                players[dealer_num]->add_and_discard(upcard);
                            }
                            
                            cout << endl;
                            return order_up;
                        }
                        else{
                            cout << players[(i+dealer_num)%4]->get_name() << " passes" << endl;
                        }
                    }
                }
            } 
            return order_up;
        }
        
        //Next, we determine how to score
        void score(int player_tricks[], const int &make_trump, int &team1_score, int &team2_score){
            int team1_tricks = player_tricks[0] + player_tricks[2];
            int team2_tricks = player_tricks[1] + player_tricks[3];

            if(team1_tricks > team2_tricks){
                if(make_trump != 0 && make_trump !=2){  // add 2 points if team 1 didn't choose trump
                    team1_score +=2;
                    cout << "euchred!" << endl;
                }
                else if(team1_tricks == 5){ // add 2 if team 1 chose trump but won all tricks
                    team1_score +=2;
                    cout << "march!" << endl;
                }
                else{
                    team1_score +=1; // add 1 if team 1 did choose trump but didn't win all tricks
                }
            }
            if(team2_tricks > team1_tricks){
                if(make_trump != 1 && make_trump !=3){  // add 2 points if team 2 didn't choose trump
                    team2_score +=2;
                    cout << "euchred!" << endl;
                }
                else if(team2_tricks == 5){ // add 2 if team 2 chose trump but won all tricks
                    team2_score +=2;
                    cout << "march!" << endl;
                }
                else{
                    team2_score +=1; // add 1 if team 2 did choose trump but didn't win all tricks
                }
            }
        }
        

        // Function to play a trick
        // returns the index of the player who just won
        // Input the index of the player who is is leading
        int trick(const int led_num, const Suit &trump){
            int win = led_num; //index of the player who won the trick
            Card led_Card = players[led_num]->lead_card(trump);
            cout << led_Card << " led by "<< players[led_num]->get_name() << endl;
            Card Card_max = led_Card;
            for (int i = 1; i<4; ++i){ //start from the lead, then go around the table
                int index = (led_num+i)%4;
                Card Card_current = players[index]->play_card(led_Card, trump);
                cout << Card_current << " played by " << players[index]->get_name() << endl;
                if (Card_less(Card_max, Card_current, led_Card, trump)){
                    win = index;
                    Card_max = Card_current;
                }
            }
            cout << players[win]->get_name() << " takes the trick"<< endl;
            cout << endl;
            return win;
        }
        // how the hand is played
        void hand(const int &hand_num, const int &dealer_num, int &team1_score, 
            int &team2_score){
            cout << "Hand " << hand_num << endl;
            cout << players[dealer_num]->get_name() << " deals" << endl;
            deal(dealer_num);
            Card upcard = make_upcard();
            int made_trump = 0;   // The index of the player who made trump
            Suit trump = create_trump(upcard, dealer_num, made_trump);

            int player_tricks[4] = {0,0,0,0};
            int led_num = (dealer_num + 1)%4;   // the index of the player who is leading
            for (int i = 0; i < 5; ++i){
                int win = trick(led_num, trump);
                player_tricks[win]+=1;
                led_num = win;
            }
            if (player_tricks[0]+ player_tricks[2] > player_tricks[1]+ player_tricks[3]){
                cout << players[0]->get_name() << " and " << players[2]->get_name() <<
                " win the hand" << endl; 
            }
            else{
                cout << players[1]->get_name() << " and " << players[3]->get_name() <<
                " win the hand" << endl; 
            }
            score(player_tricks, made_trump, team1_score, team2_score);

        }
};

int main(int argc, char *argv[]) {

  // Getting the inputs
  if (argc !=12 || stoi(argv[3]) < 1 || stoi(argv[3]) > 100 
        || (string(argv[2]) != "shuffle" && string(argv[2]) != "noshuffle")){
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     return 1;
  }
  
  bool shuffle;
  if (string(argv[2]) == "shuffle"){
    shuffle = true;
  }
  else if(string(argv[2]) == "noshuffle"){
    shuffle = false;
  }

  int win_points = stoi(argv[3]); //points needed to win the game

  // Initialize player names
  string player_names[4] = {argv[4], argv[6], argv[8], argv[10]};

  // Initialize player types
  string player_types[4] = {argv[5], argv[7], argv[9], argv[11]};

  for (string *ptr = player_types; ptr < player_types + 4; ++ ptr){
    if (*ptr != "Simple" && *ptr != "Human"){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     return 1;
    }
  }

  ifstream pack_in(argv[1]);
  if(!pack_in.is_open()){
    cout << "Error opening " << argv[1] << endl;   //pack file input
    return 1;
  }
  for (int i = 0; i<argc; ++i){
    cout << argv[i] << " ";
  }
  cout << endl;

  std::vector<Player*> players;
  for (int i = 0; i<4; ++i){
    players.push_back(Player_factory(player_names[i], player_types[i]));
  }

  Pack pack(pack_in);
  Game game(pack, players, shuffle, win_points);

  game.play();

  for (size_t i = 0; i < players.size(); ++i) {
    delete players[i];
  }



}
