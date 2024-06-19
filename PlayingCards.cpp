/*
    PlayingCards.cpp
    Copyright Angelos Tsangarides (c)

    Year Of Creation: 2022
*/

#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <random>
#include <ctime>

#include "PlayingCards.hpp"

namespace PlayingCards {
    
    std::string suit_to_str(Suit s) {
        switch (s) {
            case Suit::Hearts:
                return "Hearts"; break;
            case Suit::Diamonds:
                return "Diamonds"; break;
            case Suit::Spades:
                return "Spades"; break;
            case Suit::Clubs:
                return "Clubs"; break;
            default:
                return ""; break;
        }
    }
    
    // --- Begin definitions for Rank ---
    Rank::Rank(unsigned int v) {
        value(v);
    }

    void Rank::value(unsigned int v) {
        if (v < 0 || v > 13) {
            throw std::out_of_range {"PlayingCards::Rank::value(int v)"};
        } else {
            mValue = v;
        }

        switch (v) {
            case 0:
                mStr = "Joker"; break;
            case 1:
                mStr = "Ace"; break;
            case 2:
                mStr = "Two"; break;
            case 3:
                mStr = "Three"; break;
            case 4:
                mStr = "Four"; break;
            case 5:
                mStr = "Five"; break;
            case 6:
                mStr = "Six"; break;
            case 7:
                mStr = "Seven"; break;
            case 8:
                mStr = "Eight"; break;
            case 9:
                mStr = "Nine"; break;
            case 10:
                mStr = "Ten"; break;
            case 11:
                mStr = "Jack"; break;
            case 12:
                mStr = "Queen"; break;
            case 13:
                mStr = "King"; break;
        }
    }

    void Rank::operator++() {
        if (mValue == 13) {
            throw std::out_of_range{"PlayingCards::Rank::operator++()"};
        } else {
            value( mValue + 1 );
        }
    }

    void Rank::operator--() {
        if (mValue == 0) {
            throw std::out_of_range{"PlayingCards::Rank::operator++()"};
        } else {
            value( mValue - 1 );
        }
    }
    // --- End definitions for Rank ---


    // --- Begin definitions for Card ---
    Card::Card() {
        card(Rank(), Suit::Hearts);
    }

    Card::Card(Rank r, Suit s) {
        mStr = "";
        card(r, s);
    }

    void Card::card(Rank r, Suit s) {
        mRank = r;
        mSuit = s;

        if (r.value() == 0 && mSuit == Suit::Joker) {
            mStr = "Joker";
        } else {
            mStr = mRank.to_str() + " of " + suit_to_str(mSuit);
        }
    }

    void Card::rank(Rank r) {
        card(r, mSuit);
    }

    void Card::suit(Suit s) {
        card(mRank, s);
    }
    // --- End definitions for Card ---
    
    // --- Begin definitions for CardCollection ---
    CardCollection::~CardCollection() {}

    Card& CardCollection::operator[](int i) {
        if (i < 0 || i >= mSize) {
            throw std::out_of_range{"PlayingCards::CardCollection::operator[](int i)"};
        } else {
            return mCards[i];
        }
    }

    std::string CardCollection::to_str() {
        std::string temp = "";

        for (Card c : mCards) {
            temp += c.to_str() + "\n";
        }

        return temp;
    }

    void CardCollection::shuffle() {
        std::default_random_engine engine;
        engine.seed( unsigned( std::time(0) ) );
        std::shuffle( mCards.begin(), mCards.end(), engine );
    }

    void CardCollection::sort() {
        // Sort by card suit
        bool sorted = false;
        while(!sorted) {
            bool swapped = false;
            for (int i=0; i < mSize-1; ++i) {
                if (mCards[i].rank().value() > mCards[i+1].rank().value()) {
                    Card temp = mCards[i];
                    mCards[i] = mCards[i+1];
                    mCards[i+1] = temp;

                    swapped = true;
                }
            }

            if(!swapped) {
                sorted = true;
            }
        }

        // Sort by card rank
        sorted = false;
        while(!sorted) {
            bool swapped = false;
            for (int i=0; i < mSize-1; ++i) {
                if (mCards[i].suit() > mCards[i+1].suit()) {
                    Card temp = mCards[i];
                    mCards[i] = mCards[i+1];
                    mCards[i+1] = temp;

                    swapped = true;
                }
            }

            if(!swapped) {
                sorted = true;
            }
        }
    }

    void CardCollection::add(Card c) {
        mCards.push_back(c);
        ++mSize;
    }

    void CardCollection::del(int i) {
        mCards.erase( mCards.begin() + i );
        --mSize;
    }

    Card CardCollection::get_card(int i) {
        if(i < 0 || i >= mSize) {
            throw std::out_of_range{"PlayingCards::CardCollection::get_card(int i)"};
        } else {
            return mCards[i];
        }
    }

    // --- End definitions for CardCollection ---    

    // --- Begin definitions for Deck ---
    Deck::Deck(bool hasJokers) {
        if(hasJokers) {
            mCards.push_back(Card(Rank(0), Suit::Joker));
            mCards.push_back(Card(Rank(0), Suit::Joker));
            mSize = 2;
        }

        for (int suit=1; suit<5; ++suit){
            for (int rank=1; rank<=13; ++rank) {
                mCards.push_back( Card( Rank(rank), (Suit)suit ) );
                ++mSize;
            }
        }

    }

    Deck::~Deck() {}
    // --- End definitions for Deck ---

}