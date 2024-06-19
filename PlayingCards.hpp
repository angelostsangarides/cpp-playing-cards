/*
    PlayingCards.hpp
    Copyright Angelos Tsangarides (c)

    Year Of Creation: 2022
*/

#ifndef _PlayingCards_H_
#define _PlayingCards_H_

#include <string>
#include <vector>

namespace PlayingCards {

    enum Suit {Joker, Hearts, Diamonds, Spades, Clubs};

    std::string suit_to_str(Suit s);

    class Rank {
        /*
            Class Name: Rank

            Class Description:
                Represents the rank of a playing card, e.g: ace, 5, jack.
        */

        public:
            Rank() :mValue{1}, mStr{"Ace"} {};
            Rank(unsigned int v);

            unsigned int value() const { return mValue; };
            void value(unsigned int v); // Sets mValue to v. Updates mStr according to v.

            std::string to_str() const { return mStr; }; 

            void operator++(); // Increases rank value ( mValue ).
            void operator--(); // Decreases rank value ( mValue ).

            bool operator>(const Rank& r2) { return (mValue > r2.value()); }
            bool operator<(const Rank& r2) { return (mValue < r2.value()); }

            bool operator>=(const Rank& r2) { return (mValue >= r2.value()); }
            bool operator<=(const Rank& r2) { return (mValue <= r2.value()); }

            bool operator==(const Rank& r2) { return (mValue == r2.value()); }

        private:
            unsigned int mValue; // Numerical representation of the rank, e.g: val 5 = rank 5, val 1 = rank ace, val 11 = rank jack.
            std::string mStr; // Textual representation of the rank, e.g: "Five", "Ace", "Jack".
    };

    class Card {
        /*
            Class Name: Card

            Class Description:
                Represents a playing card.
        */

        public:
            Card();
            Card(Rank r, Suit s);

            Rank rank() const { return mRank; };
            void rank(Rank r); // Sets mRank to r. Updates mStr according to r and mSuit;

            Suit suit() const { return mSuit; };
            void suit(Suit s); // Sets mSuit to s. Updates mStr according to s and mRank;

            void card(Rank r, Suit s); // Performs the actions of both [void rank()] and [void suit()].

            std::string to_str() const { return mStr; };

            bool operator>(Card& c2) { return (mRank > c2.rank()); }
            bool operator<(Card& c2) { return (mRank < c2.rank()); }

            bool operator>=(Card& c2) { return (mRank >= c2.rank()); }
            bool operator<=(Card& c2) { return (mRank <= c2.rank()); }

            bool operator==(Card& c2) { return (mRank == c2.rank()); }

        protected:
            Rank mRank;
            Suit mSuit;
            std::string mStr; // Textual representation/title of the card, e.g: "Five of Hearts", "Ace of Spades", "Jack of Clubs".

    };

    class CardCollection {
        /*
            Class Name: CardCollection

            Class Description:
                A container that represents a group of Cards;
        */

        public:
            CardCollection() :mSize{0} {};
            ~CardCollection();

            Card& operator[](int i);

            void add(Card c);
            void del(int i);
            Card get_card(int i); // Returns a copy of the card at mCards[i]

            int size() { return mSize; };

            void sort(); // Sorts the cards in mCards by rank and suit using 'bubble sort'.
            void shuffle();

            std::string to_str();

        protected:
            std::vector<Card> mCards;
            unsigned int mSize;
            
    };

    class Deck : public CardCollection {
        /*
            Class Name: Deck
            Subclass of: CardCollection

            Class Description:
                Represents a deck of cards.

            Difference(s) from superclass:
                Constructor initializes mCards with the cards found in a traditional deck.
        */

        public:
            Deck(bool hasJokers);
            ~Deck();

    };

}

#endif
