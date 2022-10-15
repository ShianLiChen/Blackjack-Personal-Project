#include <iostream>
#include <string>
#include <random>

using namespace std;

int generateRandomNumber()
{
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distrib(1, 13);
    return distrib(gen);
}

string isSpecialCard(int randnumber)
{
    if(randnumber == 1)
    {
        return "Ace";
    }
    else if(randnumber == 11)
    {
        return "Jack";
    }
    else if(randnumber == 12)
    {
        return "Queen";
    }
    else if(randnumber == 13)
    {
        return "King";
    }
    else
    {
        return to_string(randnumber);
    }
}

int specialCardFix(int generatedNumber, string aceChoice)
{
    if(generatedNumber > 10)
    {
        generatedNumber = 10;
    }
    else if(generatedNumber == 1)
    {
        cout << "Would you like your Ace to be a 1 or 11? ";
        cin >> aceChoice;
        if(aceChoice == "1")
        {
            generatedNumber = 1;
        }
        else
        {
            generatedNumber = 11;
        }
    }

    return generatedNumber;
}

int specialDealerCardFix(int generatedNumber)
{
    if(generatedNumber > 10)
    {
        generatedNumber = 10;
    }
    else if(generatedNumber == 1)
    {
        generatedNumber = 11;
    }

    return generatedNumber;
}

int specialDealerAddedCardFix(int generatedNumber, int dealerTotal)
{
    if(generatedNumber > 10)
    {
        generatedNumber = 10;
    }
    else if(generatedNumber == 1)
    {
        if((dealerTotal + 11) > 21)
        {
            generatedNumber = 1;
        }
        else
        {
            generatedNumber = 11;
        }
    }

    return generatedNumber;
}

int main()
{
    int dealerFirstCard, dealerSecondCard, playerFirstCard, playerSecondCard;
    string dealerCardOne, dealerCardTwo, playerCardOne, playerCardTwo, newDealerCard, newPlayerCard;
    string response, playerDecision, aceChoice;
    int dealerAddCard, playerAddCard;
    string dealerCardAdded, playerCardAdded;
    bool continuePlaying = true;

    while(true)
    {
        dealerFirstCard = generateRandomNumber();
        dealerCardOne = isSpecialCard(dealerFirstCard);
        dealerFirstCard = specialDealerCardFix(dealerFirstCard);
        cout << "\nDealer's First Card is: " << dealerCardOne << endl; //remove

        dealerSecondCard = generateRandomNumber();
        dealerCardTwo = isSpecialCard(dealerSecondCard);
        dealerSecondCard = specialDealerCardFix(dealerSecondCard);
        cout << "Dealer's Second Card is: " << dealerCardTwo << endl; //remove or not 

        playerFirstCard = generateRandomNumber();
        playerCardOne = isSpecialCard(playerFirstCard);
        cout << "\nYour First Card is: " << playerCardOne << endl;
        

        playerSecondCard = generateRandomNumber();
        playerCardTwo = isSpecialCard(playerSecondCard);
        cout << "Your Second Card is: " << playerCardTwo << endl;
        playerFirstCard = specialCardFix(playerFirstCard, aceChoice);
        playerSecondCard = specialCardFix(playerSecondCard, aceChoice);
        
        int playerTotal, dealerTotal;
        playerTotal = playerFirstCard + playerSecondCard;
        cout << "\nYour Total is: " << playerTotal << endl;

        dealerTotal = dealerFirstCard + dealerSecondCard;
        cout << "Dealer Total is: " << dealerTotal << endl << endl; // remove
        // End of initial dealing of cards 

        // NEED TO ACCOUNT FOR IF BOTH GET A BLACKJACK 

        // player turn
        if(dealerTotal == 21 && playerTotal == 21)
        {
            cout << "You tied with the dealer." << endl;
        }
        else if(dealerTotal == 21)
        {
            cout << "Sorry. You lost. The dealer got blackjack!" << endl;
        }
        else if(playerTotal == 21)
        {
            cout << "Congratulations! You win with a blackjack!" << endl;
        }
        else
        {
            while(true)
            {
                if(playerTotal > 21)
                {
                    cout << "Sorry. You busted." << endl;
                    break;
                }
                else if(playerTotal == 21)
                {
                    cout << "Congratulations! You Won!" << endl;
                    break;
                }
                else
                {
                    cout << "Would you like to \"Hit\" or \"Stand\"? ";
                    cin >> playerDecision;

                    if(playerDecision == "Hit")
                    {
                        playerAddCard = generateRandomNumber();
                        playerCardAdded = isSpecialCard(playerAddCard);
                        cout << "Your added card is: " << playerCardAdded << endl;
                        playerAddCard = specialCardFix(playerAddCard, aceChoice);
                        playerTotal += playerAddCard;
                      
                        cout << "Your new total is: " << playerTotal << endl << endl;
                    }
                    else if(playerDecision == "Stand")
                    {
                        break;
                    }
                }
            }
        }
        

        //Dealer turn
        if(dealerTotal != 21 && playerTotal < 21)
        {
            cout << "\nDealer's total is: " << dealerTotal << endl;
        }
        while(dealerTotal <= playerTotal && playerTotal < 21)
        {
            cout << "The dealer will add another card." << endl;
            dealerAddCard = generateRandomNumber();
            dealerCardAdded = isSpecialCard(dealerAddCard);
            cout << "The dealer's added card is " << dealerCardAdded << endl;
            dealerAddCard = specialDealerAddedCardFix(dealerAddCard, dealerTotal);
            dealerTotal += dealerAddCard;

            cout << "Dealer's new total is: " << dealerTotal << endl;
            if(dealerTotal > playerTotal && dealerTotal < 21)
            {
                break;
            }
            else if(dealerTotal == 21)
            {
                cout << "I'm sorry. You lost." << endl;
                break;
            }
            else if(dealerTotal > 21)
            {
                cout << "Congratulations! You won, since the dealer busted." << endl;
                break;
            }
        }

        if(playerTotal < dealerTotal && dealerTotal < 21)
        {
            cout << "I'm sorry. You lost." << endl;
        }
        // End of the Game 
        cout << "\nWould you like to play again? ";
        while(true)
        {
            cin >> response;
            if(response == "No" || response == "no")
            {
                continuePlaying = false;
                break;
            }
            else if(response == "Yes" || response == "yes")
            {
                break;
            }
            else
            {
                cout << "Please provide a valid response. Would you like to play again? ";
            }
        }
        if(continuePlaying == false)
        {
            break;
        }
    }

    return 0;
}