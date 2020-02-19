/**
  Thy H. Nguyen
  CSC236 L05: Game of War
  Code designed to learn to use stacks, queues, and deques correctly
 */

#include <iostream> 
#include <stack> 
#include <queue>
#include <algorithm>    // has shuffle
#include <vector> 
#include <random>
#include <chrono>

using namespace std;


class Getrandom {
	/** Uses <random> and <chrono> from C++11 to return a random integer in range [1..size] */
public:
	Getrandom(int size) {
		auto seed = chrono::system_clock::now().time_since_epoch().count(); //gets a new seed for the randomness
		default_random_engine generator(seed);			//seeds our randomness
		uniform_int_distribution<int> intdist(1, size); //a distibution to make each in-range integer equally likely
		self_rand_int_ = intdist(generator);			//generates the randme number
	}
	int roll() {
		return self_rand_int_;
	}
private:
	int self_rand_int_;
};


class War {
	//This is a class to play game War
public:
	War()
	{
		//This is a class to play game War

		// This code makes the 5 decks of cards that are in order
		newdecks.reserve(125);
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 10; j++) {
				newdecks.push_back(j);
			}
		}

		// This code gets a time-based seed for randomness
		unsigned seed = std::chrono::system_clock::now()
			.time_since_epoch().count();

		//The following code shuffles
		shuffle(newdecks.begin(), newdecks.end(), std::default_random_engine(seed));

		//cout << "We see our randomized cards" << endl; //FIXME: Remove thisLine
		//for (int i = 0; i < 50; i++) { //FIXME: Remove this loop--it is for testing only
		//	cout << newdecks[i] << endl; //FIXME: remove this line
		//}
		/*The following code should be removed or commented out
		*/

		// Constructor should initialize instance variables 
		//But, it is okay to have empty stacks, queues, and deques.

	}
	void  add_dealingPile()  //optional method
	// adds the shuffled decks of cards to the dealer's pile
	{
		for (int i = 0; i < newdecks.size(); i++) {
			dealingPile.push(newdecks[i]);
		}
		cout << "There are " << dealingPile.size() << " cards in the Dealing Pile." << endl;
	}

	void deal() {
		// deals out 25 cards to each player's playing pile from shuffled dealers pile
		for (int i = 0; i < 25; i++)
		{
			myPlayingPile.push(dealingPile.top());
			dealingPile.pop();
			otherPlayingPile.push(dealingPile.top());
			dealingPile.pop();
		}
		cout << "There are " << myPlayingPile.size() << " cards in my Playing Pile." << endl;
		cout << "There are " << otherPlayingPile.size() << " cards in other Playing Pile." << endl;

	}


	bool make_move() {
		// initiates a round of play and communicates play-by-play during the round
		if (myPlayingPile.size() == 0 && myStoragePile.size() == 0) {
			cout << "There are " << myPlayingPile.size() << " cards in my Playing Pile." << endl;
			cout << "There are " << myStoragePile.size() << " cards in my Storage Pile." << endl;
			cout << "The game is over." << "The computer is the winner!" << endl;
			currentState = false;
		}

		else if (otherPlayingPile.size() == 0 && otherStoragePile.size() == 0)
		{
			cout << "There are " << otherPlayingPile.size() << " cards in other Playing Pile." << endl;
			cout << "There are " << otherStoragePile.size() << " cards in other Storage Pile." << endl;
			cout << "The game is over." << "I am the winner!" << endl;
			currentState = false;
		}
		else {


			if (myPlayingPile.size() == 25 && myStoragePile.size() == 25) {
				cout << "There are " << myPlayingPile.size() << " cards in my Playing Pile and " << myStoragePile.size() << " cards in my Storage Pile." << endl;
				cout << "The game is over." << "I am the winner!" << endl;

				currentState = false;
			}
			else if (otherPlayingPile.size() == 25 && otherStoragePile.size() == 25) {
				cout << "There are " << otherPlayingPile.size() << " cards in other Playing Pile and " << otherStoragePile.size() << " cards in other Storage Pile." << endl;
				cout << "The game is over." << "The computer is the winner!" << endl;
				currentState = false;
			}

			else
			{
				cout << "There are " << myPlayingPile.size() << " cards in my Playing Pile and " << myStoragePile.size() << " cards in my Storage Pile." << endl;
				cout << "There are " << otherPlayingPile.size() << " cards in other Playing Pile and " << otherStoragePile.size() << " cards in other Storage Pile." << endl;
				cout << "The game is still in play." << endl;
				currentState = true;
			}
		}


		return currentState;
		// returns true when the game is still in play
		// returns false when the game is over
		// Communicates an appropriate message about whether the user beat the computer

	}


	int remove_my_card() {
		if (myPlayingPile.size() != 0) {
			myCurrent = myPlayingPile.top();
			myPlayingPile.pop();
		}
		else
		{
			for (int i = 0; i < myStoragePile.size(); i++)
			{
				myPlayingPile.push(myStoragePile.front());
				myStoragePile.pop();
			}
			myCurrent = myPlayingPile.top();
			myPlayingPile.pop();
		}
		return myCurrent;

	}
	// Precondition: myPlayingPile is not empty 
	// If it is not empty, the function removes a card from myPlayingPile, 
	// returning the stored value


	int remove_other_card() {
		if (otherPlayingPile.size() != 0) {
			otherCurrent = otherPlayingPile.top();
			otherPlayingPile.pop();

		}
		else
		{
			for (int i = 0; i < otherStoragePile.size(); i++)
			{
				otherPlayingPile.push(otherStoragePile.front());
				otherStoragePile.pop();
			}
			otherCurrent = otherPlayingPile.top();
			otherPlayingPile.pop();

		}
		return otherCurrent;

		// Precondition: otherPlayingPile is not empty 
		// If it is not empty, the function removes a card from otherPlayingPile,
		// returning the stored value
	}


	int display_card() {
		cout << "My current card is " << myCurrent << endl;
		cout << "Other current card is " << otherCurrent << endl;
		return 0;

	}
	// displays a card on the screen and returns the value




	bool compare_cards() {


		if (myCurrent < otherCurrent) {
			cout << "Since " << myCurrent << " <" << otherCurrent << " the computer takes " << myCurrent << "and " << otherCurrent << " into its Storage Pile." << endl;
			otherStoragePile.push(myCurrent);
			otherStoragePile.push(otherCurrent);
			return true;

		}
		else if (myCurrent > otherCurrent) {
			cout << "Since " << myCurrent << " >" << otherCurrent << " I take " << myCurrent << "and " << otherCurrent << " into my Storage Pile." << endl;
			myStoragePile.push(myCurrent);
			myStoragePile.push(otherCurrent);
	
			return true;
		}

		else
		{
			while (myCurrent == otherCurrent) {
				cout << "Since " << myCurrent << " =" << otherCurrent << " War starts! Placing " << myCurrent << "and " << otherCurrent << " into the Loot Pile." << endl;
				lootPile.push(myCurrent);
				lootPile.push(otherCurrent);
				cout << "Placing my next card in my Playing card and other's next card in other Playing Card into the Loot Pile. " << endl;
				cout << "There are " << lootPile.size() << " cards in Loot Pile." << endl;
				if (myPlayingPile.size() != 0)
				{
					lootPile.push(myPlayingPile.top());
					myPlayingPile.pop();
					cout << "There are " << lootPile.size() << " cards in Loot Pile." << endl;

				}
				else
				{
					if (myStoragePile.size() != 0) {
						for (int i = 0; i < myStoragePile.size(); i++)
						{
							myPlayingPile.push(myStoragePile.front());
							myStoragePile.pop();
						}
						lootPile.push(myPlayingPile.top());
						myPlayingPile.pop();
						cout << "There are " << lootPile.size() << " cards in Loot Pile." << endl;

					}
				}
				if (otherPlayingPile.size() != 0)
				{
					lootPile.push(otherPlayingPile.top());
					otherPlayingPile.pop();
					cout << "There are " << lootPile.size() << " cards in Loot Pile." << endl;
				}
				else
				{
					if (otherStoragePile.size() != 0) {
						for (int i = 0; i < otherStoragePile.size(); i++)
						{
							otherPlayingPile.push(otherStoragePile.front());
							otherStoragePile.pop();
						}
						lootPile.push(otherPlayingPile.top());
						otherPlayingPile.pop();
						cout << "There are " << lootPile.size() << " cards in Loot Pile." << endl;
					}
				}


				if (myPlayingPile.size() != 0) {
					myCurrent = myPlayingPile.top();
					myPlayingPile.pop();
									}
				else
				{
					if (myStoragePile.size() != 0) {
						for (int i = 0; i < myStoragePile.size(); i++)
						{
							myPlayingPile.push(myStoragePile.front());
							myStoragePile.pop();
						}

						myCurrent = myPlayingPile.top();
						myPlayingPile.pop();
							}
				}
				if (otherPlayingPile.size() != 0) {
						otherCurrent = otherPlayingPile.top();
						otherPlayingPile.pop();
			
					}
					else
					{
					if (otherStoragePile.size() != 0) {
						for (int i = 0; i < otherStoragePile.size(); i++)
						{
							otherPlayingPile.push(otherStoragePile.front());
							otherStoragePile.pop();
						}
						otherCurrent = otherPlayingPile.top();
						otherPlayingPile.pop();
					}
					}
		

				display_card();

			}
			return false;
		}

	}

	// compares myCurrent to otherCurrent and behaves appropriately    


	void move_my_loot() {
		// moves everything from lootPile to myStoragePile    
		if (myCurrent > otherCurrent)
		{
			for (int i = 0; i < lootPile.size(); i++) {
				myStoragePile.push(lootPile.front());
				lootPile.pop();

			}
			cout << "Getting " << lootPile.size() << " from loop Pile. So, there are " << myStoragePile.size() << " cards in my Storage Pile." << endl;
		}
	}
	void move_other_loot() {
		// moves everything from lootPile to otherStoragePile
		if (myCurrent < otherCurrent)
		{
			for (int i = 0; i < lootPile.size(); i++) {
				otherStoragePile.push(lootPile.front());
				lootPile.pop();
			}
			cout << "Getting " << lootPile.size() << " from loop Pile. So, there are " << otherStoragePile.size() << " cards in other Storage Pile." << endl;
		}
	}
	void move_my_storage() {
		// moves everything from myStoragePile to myPlayingPile
		for (int i = 0; i < myStoragePile.size(); i++) {
			myPlayingPile.push(myStoragePile.front());
			myStoragePile.pop();

		}
	
	}
	void move_other_storage() {
		// moves everything from otherStoragePile to otherPlayingPile
		for (int i = 0; i < otherStoragePile.size(); i++) {
			otherPlayingPile.push(otherStoragePile.front());
			otherStoragePile.pop();
		}
	
	}



private:
	vector<int> newdecks; //This is the ONLY vector you are allowed to use
	int myCurrent;
	int otherCurrent;
	bool currentState;
	stack <int> dealingPile;
	stack <int> myPlayingPile;
	queue <int>  myStoragePile;
	stack <int>  otherPlayingPile;
	queue <int> otherStoragePile;
	queue <int> lootPile;

}; //a semi colon must end every C++ class declaration.


//---------------------------------------------------------------------
// main begins here

int main() {
	char stopme;

	War game;
	game.add_dealingPile();
	game.deal();

	while (game.make_move() == true) {
		game.remove_my_card();
		game.remove_other_card();
		game.display_card();

		if (game.compare_cards() == false) {

			game.move_my_loot();
			game.move_other_loot();
		}
		
	}




	cin >> stopme; //holds open the window in some cases
	return 0;
}



