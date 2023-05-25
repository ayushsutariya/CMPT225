
// Conversation opened. 1 unread message.

// Skip to content
// Using Gmail with screen readers

// 1 of 8,406
// Fwd: CMPT 225 Wordlist
// Inbox

// Jeet Manishkumar PATEL <patjd2202@learning.fraseric.ca>
// Attachments
// 6:57 PM (23 minutes ago)
// to me


// ---------- Forwarded message ---------
// From: Jeet Manishkumar PATEL <patjd2202@learning.fraseric.ca>
// Date: Wed, May 24, 2023, 18:44
// Subject: CMPT 225 Wordlist
// To: <aryaman08112003@gmail.com>



//  One attachment
//   •  Scanned by Gmail
// Wordlist.h

#pragma once

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <Jeet Manishkumar Patel>
// St.# : <301573108>
// Email: <jmp20@sfu.ca>
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

//
// Do not use any other #includes
//
#include "Wordlist_base.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Wordlist : public Wordlist_base
{
    
    //
    // Use this Node to implement the singly-linked list for the word list. You
    // can *add* extra variables/methods/features to this struct if you like,
    // but you must keep its name the same, and also keep the word, count, and
    // next variables as defined.
    //
        struct Node
        {
            string word;
            int count = 0;
            Node *next;
        };

    //
    // ... your code goes here ...
    //

    //
    // ... you can write helper methods if you need them ...
    //

    //
    // ... write a default constructor that creates an empty Wordlist ...
    //
   


    private:
        Node* head;


    public:
        // Constructors
        Wordlist()
        {
            head = nullptr;
        }

        // Non Default Constructors
        Wordlist(const string& s)
        {
            head = nullptr;
            ifstream fin(s);
            string w;
            while (!fin.eof())
            {
                fin >> w;
                add_word(w);
            }
            fin.close();
            return;
        }



        // Destructor
        ~Wordlist() 
        {
            while (head != nullptr)
            {
                Node* temp = head;
                head = temp->next;
                delete temp;
            }
        }


        //Helping functions


        int get_count(const string &w) const override
        {
            for (Node* i = head ; i != nullptr ; i = i->next)
            {
                if (i->word == w)
                {
                    return i->count;
                }
            }
            return 0; //If the word does not exist, it will return 0.
        }

        bool contains(const string &w) const
        {
            return (get_count(w) > 0);
        }

        int num_different_words()  const override
        {
            int size = 0;
            for (Node* i = head ; i != nullptr ; i = i->next)
            {
                size++;
            }
            return size;
        }


        int total_words()  const override
        {
            int numOfWords = 0;
            for (Node* i = head ; i != nullptr ; i = i->next)
            {
                numOfWords += i->count;
            }
            return numOfWords;
        }


        bool is_sorted()  const override
        {
            for (Node* i = head ; i != nullptr ; i = i->next)
            {
                if ((i->next) != nullptr)
                {
                    if (i->word > (i->next)->word)
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        

        string most_frequent()  const override
        {
            Node* freq_used = head;
            int count = 0;
            for (Node* i = head ; i != nullptr ; i = i->next)
            {
                if (i->count > count)
                {
                    freq_used = i;
                    count = i->count;
                }
            }
            return freq_used->word + " " + to_string(freq_used->count);
        }


        int num_singletons()  const override
        {
            int numOfSingles = 0;
            for (Node* i = head ; i != nullptr ; i = i->next)
            {
                if (i->count == 1)
                {
                    numOfSingles++;
                }
            }
            return numOfSingles;
        }

        void add_word(const string &w)
        {
            Node* current = head;
            Node* previous = nullptr;

            Node* newNode = new Node;
            newNode->word = w;
            newNode->count = 1;
            newNode->next = nullptr;

            if (head == nullptr)
            {
                head = newNode;
                return;
            }
            while (current != nullptr)
            {
                if (current->word == w)
                {
                    current->count += 1;
                    delete newNode;
                    return;
                }
                else if (current->word < w)
                {
                    previous = current;
                    current = current->next;
                }
                else
                {
                    break;
                }
            }

            if (previous == nullptr)
            {
                newNode->next = head;
                head = newNode;
            }
            else
            {
                previous->next = newNode;
                newNode->next = current;
            }

            if (current == nullptr)
            {
                previous->next = newNode;
                newNode->next = nullptr;
            }
        }
        

        void print_stats() const
        {
            cout << "Number of different words: " << num_different_words() << endl;
            cout << "    Total number of words: " << total_words() << endl;
            cout << "       Most frequent word: " << most_frequent() << endl;
            cout << "     Number of singletons: " << num_singletons() << setprecision(0) << fixed << " (" << 100.0 * num_singletons() / num_different_words() << "%)" << endl;
        }



        void print_words() const override
        {
            for (Node* i = head ; i != nullptr ; i = i->next)
            {
                cout << i+1 << '.' << " {'" << i->word << "', " << i->count << "}" << endl;
            }
        }
}; // class Wordlist

//
// ... you can write helpr functions here (or before Wordlist) if you need them
// ...
//
//
// ... write functions to test every method of Wordlist ...
//