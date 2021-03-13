#ifndef CLASSPIECE_H_INCLUDED
#define CLASSPIECE_H_INCLUDED

#include "utils.h"
#include "chessboard.h"



int Piece::verifami (Coord dest,ChessBoard E)
{
    if (E.verifPiece(dest))
    {
        if (this->joueur == (E.getPiece(dest))->joueur) return (1); else return (0);
    }
    else return (0);
}

int Piece::verifennemi(Coord dest,ChessBoard E)
{
    if (E.verifPiece(dest))
    {
        if (this->joueur != E.getPiece(dest)->joueur) return (1); else return (0);
    }
    else return (0);
}

void Queen::deplacementnaif(Coord source,ChessBoard Tab)
{
    int i=source.x,j=source.y;
    int x,y;
    Coord pos;
    x=1,y=1;
    this->possibilites.~LinkedList();
    while (1)
    {
        pos.x=i+x;pos.y=j+y;
        if (pos.verifcoord())
        {
            if(this->verifami(pos,Tab))
                break;

            if(this->verifennemi(pos,Tab))
            {
                this->possibilites.addlist(pos);
                break;
            }
            this->possibilites.addlist(pos);
            x+=1;y+=1;
        }
        else break;
    }
    x=1,y=1;
    while (1)
    {
        pos.x=i-x;pos.y=j-y;
        if (pos.verifcoord())
        {
            if(this->verifami(pos,Tab))
                break;

            if(this->verifennemi(pos,Tab))
            {
                this->possibilites.addlist(pos);
                break;
            }
            this->possibilites.addlist(pos);
            x+=1;y+=1;
        }
        else break;
    }
    x=1,y=1;
    while (1)
    {

        pos.x=i+x;pos.y=j-y;
        if (pos.verifcoord())
        {
            if(this->verifami(pos,Tab))
                break;

            if(this->verifennemi(pos,Tab))
            {
                this->possibilites.addlist(pos);
                break;
            }
            this->possibilites.addlist(pos);
            x+=1;y+=1;
        }
        else break;


    }
    x=1,y=1;
    while (1)
    {
        pos.x=i-x;pos.y=j+y;
        if (pos.verifcoord())
        {
            if(this->verifami(pos,Tab))
                break;

            if(this->verifennemi(pos,Tab))
            {
                this->possibilites.addlist(pos);
                break;
            }
            this->possibilites.addlist(pos);
            x+=1;y+=1;
        }
        else break;
    }
    x=1;
    while (1)
    {

        pos.x=i+x;pos.y=j;
        if (pos.verifcoord())
        {
            if(this->verifami(pos,Tab))
                break;

            if(this->verifennemi(pos,Tab))
            {
                this->possibilites.addlist(pos);
                break;
            }
            this->possibilites.addlist(pos);
            x+=1;y+=1;
        }
        else break;
    }
    x=1;
    while (1)
    {

        pos.x=i-x;pos.y=j;
        if (pos.verifcoord())
        {
            if(this->verifami(pos,Tab))
                break;

            if(this->verifennemi(pos,Tab))
            {
                this->possibilites.addlist(pos);
                break;
            }
            this->possibilites.addlist(pos);
            x+=1;y+=1;
        }
        else break;
    }
    y=1;
    while (1)
    {

        pos.x=i;pos.y=j+y;
        if (pos.verifcoord())
        {
            if(this->verifami(pos,Tab))
                break;

            if(this->verifennemi(pos,Tab))
            {
                this->possibilites.addlist(pos);
                break;
            }
            this->possibilites.addlist(pos);
            x+=1;y+=1;
        }
        else break;
    }
    y=1;
    while (1)
    {
        pos.x=i;pos.y=j-y;
        if (pos.verifcoord())
        {
            if(this->verifami(pos,Tab))
                break;

            if(this->verifennemi(pos,Tab))
            {
                this->possibilites.addlist(pos);
                break;
            }
            this->possibilites.addlist(pos);
            x+=1;y+=1;
        }
        else break;
    }
}

void Bishop::deplacementnaif(Coord source,ChessBoard Tab)
{
    int i=source.x,j=source.y;
    int x,y;
    Coord pos;
    x=1,y=1;
    this->possibilites.~LinkedList();
    while (1)
    {
        pos.x=i+x;pos.y=j+y;
        if (pos.verifcoord())
        {
            if(this->verifami(pos,Tab))
                break;

            if(this->verifennemi(pos,Tab))
            {
                this->possibilites.addlist(pos);
                break;
            }
            this->possibilites.addlist(pos);
            x+=1;y+=1;
        }
        else break;
    }
    x=1,y=1;
    while (1)
    {
        pos.x=i-x;pos.y=j-y;
        if (pos.verifcoord())
        {
            if(this->verifami(pos,Tab))
                break;

            if(this->verifennemi(pos,Tab))
            {
                this->possibilites.addlist(pos);
                break;
            }
            this->possibilites.addlist(pos);
            x+=1;y+=1;
        }
        else break;
    }
    x=1,y=1;
    while (1)
    {

        pos.x=i+x;pos.y=j-y;
        if (pos.verifcoord())
        {
            if(this->verifami(pos,Tab))
                break;

            if(this->verifennemi(pos,Tab))
            {
                this->possibilites.addlist(pos);
                break;
            }
            this->possibilites.addlist(pos);
            x+=1;y+=1;
        }
        else break;


    }
    x=1,y=1;
    while (1)
    {

        pos.x=i-x;pos.y=j+y;
        if (pos.verifcoord())
        {
            if(this->verifami(pos,Tab))
                break;

            if(this->verifennemi(pos,Tab))
            {
                this->possibilites.addlist(pos);
                break;
            }
            this->possibilites.addlist(pos);
            x+=1;y+=1;
        }
        else break;
    }
}

void Rook::deplacementnaif(Coord source,ChessBoard Tab)
{
    int i=source.x,j=source.y;
    int x,y;
    Coord pos;
    x=1,y=1;
    this->possibilites.~LinkedList();
    while (1)
    {

        pos.x=i+x;pos.y=j;
        if (pos.verifcoord())
        {
            if(this->verifami(pos,Tab))
                break;

            if(this->verifennemi(pos,Tab))
            {
                this->possibilites.addlist(pos);
                break;
            }
            this->possibilites.addlist(pos);
            x+=1;y+=1;
        }
        else break;
    }
    x=1;
    while (1)
    {

        pos.x=i-x;pos.y=j;
        if (pos.verifcoord())
        {
            if(this->verifami(pos,Tab))
                break;

            if(this->verifennemi(pos,Tab))
            {
                this->possibilites.addlist(pos);
                break;
            }
            this->possibilites.addlist(pos);
            x+=1;y+=1;
        }
        else break;
    }
    y=1;
    while (1)
    {

        pos.x=i;pos.y=j+y;
        if (pos.verifcoord())
        {
            if(this->verifami(pos,Tab))
                break;

            if(this->verifennemi(pos,Tab))
            {
                this->possibilites.addlist(pos);
                break;
            }
            this->possibilites.addlist(pos);
            x+=1;y+=1;
        }
        else break;
    }
    y=1;
    while (1)
    {
        pos.x=i;pos.y=j-y;
        if (pos.verifcoord())
        {
            if(this->verifami(pos,Tab))
                break;

            if(this->verifennemi(pos,Tab))
            {
                this->possibilites.addlist(pos);
                break;
            }
            this->possibilites.addlist(pos);
            x+=1;y+=1;
        }
        else break;
    }
}

void Pawn::deplacementnaif(Coord source,ChessBoard Tab)
{
    int i=source.x,j=source.y;
    Coord pos;
    this->possibilites.~LinkedList();
    if (this->joueur==1)
    {
        pos.x=i-1;
        pos.y=j;
        if ((!this->verifami(pos,Tab))&&(!this->verifennemi(pos,Tab))&&pos.verifcoord())
            {
                this->possibilites.addlist(pos);
                pos.x=i-2;
                pos.y=j;
                if ((i==6)&&(!this->verifami(pos,Tab))&&(!this->verifennemi(pos,Tab)))
                    this->possibilites.addlist(pos);
            }
        pos.x=i-1;
        pos.y=j+1;
        if ((this->verifennemi(pos,Tab))&&pos.verifcoord())
            this->possibilites.addlist(pos);
        pos.x=i-1;
        pos.y=j-1;
        if ((this->verifennemi(pos,Tab))&&pos.verifcoord())
            this->possibilites.addlist(pos);
    }
    if (this->joueur==2)
    {
        pos.x=i+1;
        pos.y=j;
        if ((!this->verifami(pos,Tab))&&(!this->verifennemi(pos,Tab))&&pos.verifcoord())
            {
                this->possibilites.addlist(pos);
                pos.x=i+2;
                pos.y=j;
                if ((i==1)&&(!this->verifami(pos,Tab))&&(!this->verifennemi(pos,Tab)))
                    this->possibilites.addlist(pos);
            }
        pos.x=i+1;
        pos.y=j+1;
        if ((this->verifennemi(pos,Tab))&&pos.verifcoord())
            this->possibilites.addlist(pos);
        pos.x=i+1;
        pos.y=j-1;
        if ((this->verifennemi(pos,Tab))&&pos.verifcoord())
            this->possibilites.addlist(pos);
    }
}

void Knight::deplacementnaif(Coord source,ChessBoard Tab)
{
    int i=source.x,j=source.y;
    this->possibilites.~LinkedList();
    Coord pos;
    pos.x=i+1;
    pos.y=j+2;
    if ((!this->verifami(pos,Tab))&&pos.verifcoord())
                this->possibilites.addlist(pos);
    pos.x=i-1;
    pos.y=j+2;
    if ((!this->verifami(pos,Tab))&&pos.verifcoord())
                this->possibilites.addlist(pos);
    pos.x=i+1;
    pos.y=j-2;
    if ((!this->verifami(pos,Tab))&&pos.verifcoord())
                this->possibilites.addlist(pos);
    pos.x=i-1;
    pos.y=j-2;
    if ((!this->verifami(pos,Tab))&&pos.verifcoord())
                this->possibilites.addlist(pos);
    pos.x=i+2;
    pos.y=j+1;
    if ((!this->verifami(pos,Tab))&&pos.verifcoord())
                this->possibilites.addlist(pos);
    pos.x=i+2;
    pos.y=j-1;
    if ((!this->verifami(pos,Tab))&&pos.verifcoord())
                this->possibilites.addlist(pos);
    pos.x=i-2;
    pos.y=j+1;
    if ((!this->verifami(pos,Tab))&&pos.verifcoord())
                this->possibilites.addlist(pos);
    pos.x=i-2;
    pos.y=j-1;
    if ((!this->verifami(pos,Tab))&&pos.verifcoord())
                this->possibilites.addlist(pos);
}

void King::deplacementnaif(Coord source,ChessBoard Tab)
{
    int i=source.x,j=source.y;
    this->possibilites.~LinkedList();
    Coord pos;
    pos.x=i+1;
    pos.y=j+1;
    if ((!this->verifami(pos,Tab))&&pos.verifcoord())
                this->possibilites.addlist(pos);
    pos.x=i;
    pos.y=j+1;
    if ((!this->verifami(pos,Tab))&&pos.verifcoord())
                this->possibilites.addlist(pos);
    pos.x=i-1;
    pos.y=j+1;
    if ((!this->verifami(pos,Tab))&&pos.verifcoord())
                this->possibilites.addlist(pos);
    pos.x=i-1;
    pos.y=j;
    if ((!this->verifami(pos,Tab))&&pos.verifcoord())
                this->possibilites.addlist(pos);
    pos.x=i+1;
    pos.y=j;
    if ((!this->verifami(pos,Tab))&&pos.verifcoord())
                this->possibilites.addlist(pos);
    pos.x=i-1;
    pos.y=j-1;
    if ((!this->verifami(pos,Tab))&&pos.verifcoord())
                this->possibilites.addlist(pos);
    pos.x=i;
    pos.y=j-1;
    if ((!this->verifami(pos,Tab))&&pos.verifcoord())
                this->possibilites.addlist(pos);
    pos.x=i+1;
    pos.y=j-1;
    if ((!this->verifami(pos,Tab))&&pos.verifcoord())
                this->possibilites.addlist(pos);

}

#endif // CLASSPIECE_H_INCLUDED
