#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdio.h>

#include <iostream>

#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <fstream>

using namespace std;

class coord {
    public: int x;
    int y;
    int verifcoord() {
    if ((this -> x >= 0) && (this -> x < 8) && (this -> y >= 0) && (this -> y < 8))
        return 1;
    else
        return 0;
    }
    void lirecoord() {
    char ch[2];
    cin >> ch;
    switch (ch[0]) {
    case 'H':
        this -> y = 7;
        break;
    case 'G':
        this -> y = 6;
        break;
    case 'F':
        this -> y = 5;
        break;
    case 'E':
        this -> y = 4;
        break;
    case 'D':
        this -> y = 3;
        break;
    case 'C':
        this -> y = 2;
        break;
    case 'B':
        this -> y = 1;
        break;
    case 'A':
        this -> y = 0;
        break;
    default:
        cout << "erreur" << endl;
    }
    switch (ch[1]) {
    case '1':
        this -> x = 7;
        break;
    case '2':
        this -> x = 6;
        break;
    case '3':
        this -> x = 5;
        break;
    case '4':
        this -> x = 4;
        break;
    case '5':
        this -> x = 3;
        break;
    case '6':
        this -> x = 2;
        break;
    case '7':
        this -> x = 1;
        break;
    case '8':
        this -> x = 0;
        break;
    default:
        cout << "erreur" << endl;
    }
    }
    bool operator == (coord
        const & b) {
        if ((this -> x == b.x) && (this -> y == b.y)) return true;
        else return false;
    }

   friend ostream & operator << (ostream & flux, coord pos) {
    flux << pos.x << "  " << pos.y << endl;
    return flux;
} 

};

template < class T >
    struct cCell {
        cCell(T data): elt(data), succ(NULL) {}
        T elt;
        cCell < T > * succ;
    };

template < class T >
    class liste {
        public: cCell < T > * head;
        liste(): head(NULL) {};
        ~liste();
        void ajoutliste(const T data);
        void affichechaine();
        int cherchechaine(const T data) const;
        int emptylist() const {
            if (head == NULL) return 1;
            return 0;
        }
    };

template < class T >
    liste < T > ::~liste() {
        while (head != NULL) {
            cCell < T > * tmp = head;
            head = head -> succ;
            delete tmp;
        }
        delete head;
        head = NULL;
    }

template < class T >
    void liste < T > ::affichechaine() {
        for (cCell < T > * tmp = head; tmp != NULL; tmp = tmp -> succ)
            cout << "  " << tmp -> elt;
    }

template < class T >
    void liste < T > ::ajoutliste(const T data) {
        if (head == NULL) {
            head = new cCell < T > (data);
        } else {
            cCell < T > * cour;
            cour = new cCell < T > (data);
            cour -> succ = head;
            head = cour;

        }
    }

template < class T >
    int liste < T > ::cherchechaine(const T data) const {
        if (this -> head != NULL)
            if (this -> head -> elt == data) return 1;
        for (cCell < T > * tmp = this -> head; tmp != NULL; tmp = tmp -> succ)
            if (tmp -> elt == data)
                return 1;
        return 0;
    }

#endif // UTILS_H_INCLUDED