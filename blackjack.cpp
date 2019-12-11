#include <iostream>
#include <string>
#include <cstdlib>
#include "Card.cpp" // Include Card class
#include <ctime>


/**Global variable**/
int score = 0; // User's card score
int cardsGiven = 0; // Number of cards that have been given to a User
std::pair<std::string, int> cardsWithScores[13] = { std::make_pair("Ace", 11), std::make_pair("King", 10), std::make_pair("Queen",10), std::make_pair("Jack", 10), std::make_pair("Ten", 10), std::make_pair("Nine", 9), std::make_pair("Eight", 8), std::make_pair("Seven", 7), std::make_pair("Six", 6), std::make_pair("Five", 5), std::make_pair("Four", 4), std::make_pair("Three", 3), std::make_pair("Two", 2) }; // Card names
std::string suit[4] = {"Diamonds", "Clubs", "Hearts", "Spades"}; // Card suits
Card myCards[10]; // Array for storing user's cards, so same card doesn't get generated

/**Functions**/
// function to check if a card already exists
bool doesUserHaveThisCard(Card aCard){
    for(int i = 0; i < cardsGiven; i++){
        if(aCard.cardName == myCards[i].cardName && aCard.cardSuit == myCards[i].cardSuit){
            return true;
        }
    }
    return false;
}

// funciton to generate a random card
Card generateCard(){

    Card newCard; // Initialize new card
        
    while(true){
    srand(time(0));
    int randomNum = std::rand() % 12; // in order to get a random card out of array of possible ones
    std::string randomCardName = cardsWithScores[randomNum].first; // The name of the random card
    int randomCardScore = cardsWithScores[randomNum].second; // The score of the random card


    newCard.cardName = randomCardName;
    newCard.cardScore = randomCardScore;
    srand(time(0));
    newCard.cardSuit = suit[std::rand() % 3]; // the suit of the random card

    if(!doesUserHaveThisCard(newCard)){
        break;
    }

    }

    // Add card to an array of User's cards
    cardsGiven++;

    // Add a new card to the array of User's cards
    myCards[cardsGiven-1] = newCard;

    return newCard;
}


int main()
{
    std::string ans = "yes";
    int ace_ans;
    
    // ask a user: "would you like to get one more card? Answer 'yes' or 'no'."
    // if "yes" keep generate card
    // if not, calculate result
    while(ans != "no" || ans != "n"){
        Card aCard = generateCard();
        std::cout<<"Your card is: " << aCard.cardName << " of " << aCard.cardSuit << "\n";

        // if a card is Ace, give the user an option of either 1 or 11
        if(aCard.cardName == "Ace"){
            std::cout<<"Your current score is: " << score << "\n";

            std::cout<<"Would you like the Ace to count as 1 or 11? (Type in either number '1' or '11')\n";
            // get Integer input 1 or 11
            std::cin>>ace_ans;
            // Increase the score
            score += ace_ans;
            //print out user's score
            std::cout<<"Great! Your score is: " << score << "\n";
        } else {
    
            // Calculate user's current score
            score += aCard.cardScore;
            // Print out user's score
            std::cout<<"Your score is: " << score << "\n";
        }

        // If score is greater than 21 -> get busted
        if (score > 21){
            std::cout<<"You got busted! :(\n";
            return 0;
        }

        std::cout <<"Would you like to get one more card? Answer 'yes' or 'no'\n";
        std::cin >> ans;

        // If no, open up cards
        if(ans == "no" || ans == "n"){
            std::cout<<"Sounds good! Let's open up - your final score is: " << score << "\n";

            std::cout<<"You were playing only with the dealer, Kevin. \n";
            // Lazy dealer's score generation. Make it better later
            srand(time(0));
            int randomDealerScore = rand() % (26 - 15) + 15;
            if(randomDealerScore > 21){
                std::cout<<"Kevin's score is " << randomDealerScore << "\nYou've won!!!\n";
                return 0;
            } else {
            std::cout<<"Kevin's score is " << randomDealerScore << "\n";
            }
            
            if(score > randomDealerScore){
                std::cout<<"YAS! You have won!\n";
                return 0;
            } else if(score == randomDealerScore){
                std::cout<<"That's a draw!\n";
                return 0;
            } else if(score < randomDealerScore){
                std::cout<<"Sorry, you've lost!\n";
                return 0;
            }

        }

    }


    return 0;
}

