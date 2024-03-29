#include "game.h"

#include <SFML/Graphics.hpp>
#include <cstdio>

#include "utils.h"

using namespace sf;
using namespace std;
Vector2f offset(28, 28);
int load = 0, load2 = 0;
int difsim = 0;
int board[8][8];

std::string position = "";
Vector2i pos;

std::string toChessNote(Vector2f p) {
  std::string s = "";
  s += char(p.x / 56 + 97);
  s += char(7 - p.y / 56 + 49);
  return s;
}

Vector2f toCoord(char a, char b) {
  int x = int(a) - 97;
  int y = 7 - int(b) + 49;
  return Vector2f(x * 56, y * 56);
}

void display(Chessboard& E, int board[8][8]) {
  int signe = 0, p;
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++) {
      coord loc;
      loc.x = i;
      loc.y = j;
      if (E.getPiece(loc) != NULL) {
        if (E.getPiece(loc)->player == 2)
          signe = -1;
        else
          signe = 1;
        switch (E.getPiece(loc)->value) {
          case 999:
            p = 5;
            break;
          case 1:
            p = 6;
            break;
          case 4:
            p = 2;
            break;
          case 3:
            p = 3;
            break;
          case 5:
            p = 1;
            break;
          case 10:
            p = 4;
            break;
        }
      } else
        p = 0;
      board[i][j] = p * signe;
    }
}

void move(std::string str, Sprite f[]) {
  Vector2f oldPos = toCoord(str[0], str[1]);
  Vector2f newPos = toCoord(str[2], str[3]);

  for (int i = 0; i < 32; i++)
    if (f[i].getPosition() == newPos) f[i].setPosition(-100, -100);

  for (int i = 0; i < 32; i++)
    if (f[i].getPosition() == oldPos) f[i].setPosition(newPos);
}

void loadPosition(int board[8][8], Sprite f[]) {
  int k = 0;
  for (int k = 0; k < 32; k++) f[k].setPosition(-1000, -1000);
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++) {
      int n = board[i][j];
      if (!n) continue;
      int x = abs(n) - 1;
      int y = n > 0 ? 1 : 0;
      f[k].setTextureRect(IntRect(56 * x, 56 * y, 56, 56));
      f[k].setPosition(56 * j, 56 * i);
      k++;
    }

  for (int i = 0; i < position.length(); i += 5) move(position.substr(i, 4));
}

void selectMenu(int& mode) {
  RenderWindow window(VideoMode(504, 604), "ENITCHESS");
  Texture t1, t2, t3, t4, t5, t6;
  Sprite f[5];
  t1.loadFromFile("img/Main-Menu.png");
  t2.loadFromFile("img/1VS1-Button.png");
  t3.loadFromFile("img/1VScpu1-Button.png");
  t4.loadFromFile("img/1VScpu2-Button.png");
  t5.loadFromFile("img/1VScpu3-Button.png");
  t6.loadFromFile("img/1VScpu4-Button.png");

  f[0].setTexture(t2);
  f[1].setTexture(t3);
  f[2].setTexture(t4);
  f[3].setTexture(t5);
  f[4].setTexture(t6);

  Sprite sBoard(t1);
  f[0].setPosition(56 * 2, 56 * 3);
  f[1].setPosition(56 * 2, 56 * 4);
  f[2].setPosition(56 * 2, 56 * 5);
  f[3].setPosition(56 * 2, 56 * 6);
  f[4].setPosition(56 * 2, 56 * 7);

  window.draw(sBoard);
  for (int i = 0; i < 5; i++) f[i].move(offset);
  for (int i = 0; i < 5; i++) {
    window.draw(f[i]);
  }
  for (int i = 0; i < 5; i++) f[i].move(-offset);
  window.display();
  while (window.isOpen()) {
    pos = Mouse::getPosition(window) - Vector2i(offset);
    Event e;
    while (window.pollEvent(e)) {
      if (f[0].getGlobalBounds().contains(pos.x, pos.y))
        if (e.type == Event::MouseButtonPressed)
          if (e.key.code == Mouse::Left) {
            window.close();
            mode = 1;
          }
      if (f[1].getGlobalBounds().contains(pos.x, pos.y))
        if (e.type == Event::MouseButtonPressed)
          if (e.key.code == Mouse::Left) {
            window.close();
            mode = 2;
          }
      if (f[2].getGlobalBounds().contains(pos.x, pos.y))
        if (e.type == Event::MouseButtonPressed)
          if (e.key.code == Mouse::Left) {
            window.close();
            mode = 3;
          }
      if (f[3].getGlobalBounds().contains(pos.x, pos.y))
        if (e.type == Event::MouseButtonPressed)
          if (e.key.code == Mouse::Left) {
            window.close();
            mode = 4;
          }
      if (f[4].getGlobalBounds().contains(pos.x, pos.y))
        if (e.type == Event::MouseButtonPressed)
          if (e.key.code == Mouse::Left) {
            window.close();
            mode = 5;
          }
    }
  }
}

void aide() {
  RenderWindow window(VideoMode(504, 604), "ENITCHESS");
  Texture t1;
  t1.loadFromFile("img/Help-Menu.png");

  Sprite sBoard(t1);

  window.draw(sBoard);
  window.display();
  while (window.isOpen()) {
    pos = Mouse::getPosition(window) - Vector2i(offset);
    Event e;
    while (window.pollEvent(e)) {
      if (e.type == Event::MouseButtonPressed) {
        window.close();
      }
    }
  }
}

void startMenu(Chessboard& E, int& nbtour, int& mode, Game* p) {
  RenderWindow window(VideoMode(504, 604), "ENITCHESS");
  Texture t1, t2, t3, t4, t5;
  Sprite f[4];
  t1.loadFromFile("img/Main-Menu.png");
  t2.loadFromFile("img/Start-Button.png");
  t3.loadFromFile("img/Load-Button.png");
  t4.loadFromFile("img/Help-Button.png");
  t5.loadFromFile("img/Exit-Button.png");

  f[0].setTexture(t2);
  f[1].setTexture(t3);
  f[2].setTexture(t4);
  f[3].setTexture(t5);
  Sprite sBoard(t1);
  f[0].setPosition(56 * 2, 56 * 3);
  f[1].setPosition(56 * 2, 56 * 4);
  f[2].setPosition(56 * 2, 56 * 5);
  f[3].setPosition(56 * 2, 56 * 6);

  window.draw(sBoard);
  for (int i = 0; i < 4; i++) f[i].move(offset);
  for (int i = 0; i < 4; i++) {
    window.draw(f[i]);
  }
  for (int i = 0; i < 4; i++) f[i].move(-offset);
  window.display();
  while (window.isOpen()) {
    pos = Mouse::getPosition(window) - Vector2i(offset);
    Event e;
    while (window.pollEvent(e)) {
      if (f[0].getGlobalBounds().contains(pos.x, pos.y))
        if (e.type == Event::MouseButtonPressed)
          if (e.key.code == Mouse::Left) {
            window.close();
            selectMenu(mode);
            nbtour = 1;
            break;
            break;
          }
      if (f[1].getGlobalBounds().contains(pos.x, pos.y))
        if (e.type == Event::MouseButtonPressed)
          if (e.key.code == Mouse::Left) {
            window.close();
            p->resumeGame();
            load = 1;
          }
      if (f[2].getGlobalBounds().contains(pos.x, pos.y))
        if (e.type == Event::MouseButtonPressed)
          if (e.key.code == Mouse::Left) {
            aide();
          }
      if (f[3].getGlobalBounds().contains(pos.x, pos.y))
        if (e.type == Event::MouseButtonPressed)
          if (e.key.code == Mouse::Left) {
            exit(0);
          }
    }
  }
}

Piece* Human::choosePiece() {
  RenderWindow window(VideoMode(504, 380), "Choose-Piece-Menu");
  Texture t1, t2;
  Sprite g[32];
  Chessboard q;
  int size = 56;
  int s = 0;
  t1.loadFromFile("img/Pieces.png");
  t2.loadFromFile("img/Choose-Piece-Menu.png");
  for (int i = 0; i < 32; i++) g[i].setTexture(t1);
  Sprite sBoard(t2);
  int k = 0;
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++) {
      int n = board[i][j];
      if (!n) continue;
      int x = abs(n) - 1;
      int y = n > 0 ? 1 : 0;
      g[k].setTextureRect(IntRect(56 * x, 56 * y, 56, 56));
      g[k].setPosition(-100, -100);
      k++;
    }
  if (this->color % 2 == 0) {
    g[0].setPosition(56 * 1, 56 * 4);
    g[1].setPosition(149.3, 56 * 4);
    g[2].setPosition(242.6, 56 * 4);
    g[3].setPosition(56 * 6, 56 * 4);
  } else {
    g[24].setPosition(56 * 1, 56 * 4);
    g[25].setPosition(149.3, 56 * 4);
    g[26].setPosition(242.6, 56 * 4);
    g[27].setPosition(56 * 6, 56 * 4);
  }

  window.draw(sBoard);
  for (int i = 0; i < 32; i++) g[i].move(offset);
  for (int i = 0; i < 32; i++) {
    window.draw(g[i]);
  }
  for (int i = 0; i < 32; i++) g[i].move(-offset);
  window.display();
  while (window.isOpen()) {
    pos = Mouse::getPosition(window) - Vector2i(offset);
    Event e;
    while (window.pollEvent(e)) {
      if (g[0].getGlobalBounds().contains(pos.x, pos.y))
        if (e.type == Event::MouseButtonPressed)
          if (e.key.code == Mouse::Left) {
            window.close();
            Piece* p = new Rook(2);
            return p;
          }
      if (g[1].getGlobalBounds().contains(pos.x, pos.y))
        if (e.type == Event::MouseButtonPressed)
          if (e.key.code == Mouse::Left) {
            window.close();
            Piece* p = new Knight(2);
            return p;
          }
      if (g[2].getGlobalBounds().contains(pos.x, pos.y))
        if (e.type == Event::MouseButtonPressed)
          if (e.key.code == Mouse::Left) {
            window.close();
            Piece* p = new Bishop(2);
            return p;
          }
      if (g[3].getGlobalBounds().contains(pos.x, pos.y))
        if (e.type == Event::MouseButtonPressed)
          if (e.key.code == Mouse::Left) {
            window.close();
            Piece* p = new Queen(2);
            return p;
          }
      if (g[24].getGlobalBounds().contains(pos.x, pos.y))
        if (e.type == Event::MouseButtonPressed)
          if (e.key.code == Mouse::Left) {
            window.close();
            Piece* p = new Rook(1);
            return p;
          }
      if (g[25].getGlobalBounds().contains(pos.x, pos.y))
        if (e.type == Event::MouseButtonPressed)
          if (e.key.code == Mouse::Left) {
            window.close();
            Piece* p = new Knight(1);
            return p;
          }
      if (g[26].getGlobalBounds().contains(pos.x, pos.y))
        if (e.type == Event::MouseButtonPressed)
          if (e.key.code == Mouse::Left) {
            window.close();
            Piece* p = new Bishop(1);
            return p;
          }
      if (g[27].getGlobalBounds().contains(pos.x, pos.y))
        if (e.type == Event::MouseButtonPressed)
          if (e.key.code == Mouse::Left) {
            window.close();
            Piece* p = new Queen(1);
            return p;
          }
    }
  }
}

void endMenu(Chessboard& E, int nbtour, int mode) {
  RenderWindow window(VideoMode(504, 604), "ENITCHESS");
  Texture t1, t2, t3, t4, t5, t6, t7, t8;
  Sprite f[2];
  t1.loadFromFile("img/End-Menu.png");
  t2.loadFromFile("img/Player-1.png");
  t3.loadFromFile("img/Player-2.png");
  t4.loadFromFile("img/CPU1.png");
  t5.loadFromFile("img/CPU2.png");
  t6.loadFromFile("img/CPU3.png");
  t7.loadFromFile("img/CPU4.png");
  t8.loadFromFile("img/Restart-Button.png");

  if (nbtour % 2)
    f[1].setTexture(t2);
  else
    switch (mode) {
      case 1:
        f[1].setTexture(t3);
        break;
      case 2:
        f[1].setTexture(t4);
        break;
      case 3:
        f[1].setTexture(t5);
        break;
      case 4:
        f[1].setTexture(t6);
        break;
      case 5:
        f[1].setTexture(t7);
        break;
    }
  f[0].setTexture(t8);
  Sprite sBoard(t1);
  f[1].setPosition(56 * 2, 56 * 2);
  f[0].setPosition(56 * 4 - 10, 56 * 8);

  window.draw(sBoard);
  for (int i = 0; i < 2; i++) f[i].move(offset);
  for (int i = 0; i < 2; i++) {
    window.draw(f[i]);
  }
  for (int i = 0; i < 2; i++) f[i].move(-offset);
  window.display();
  while (window.isOpen()) {
    pos = Mouse::getPosition(window) - Vector2i(offset);
    Event e;
    while (window.pollEvent(e)) {
      if (f[0].getGlobalBounds().contains(pos.x, pos.y))
        if (e.type == Event::MouseButtonPressed)
          if (e.key.code == Mouse::Left) {
            window.close();
            usleep(200);
            Game x;
            x.startgame();
          }
    }
  }
}

Game::Game() {
  int nb, mode;
  startMenu(this->chessboard, nb, mode, this);
  this->nbtour = nb;
  this->white = new Human;
  if (mode == 1)
    this->black = new Human;
  else
    this->black = new Ai(mode);
  black->color = 2;
  white->color = 1;
}

void tryMove(Sprite& f, int x, int y) { f.setPosition(56 * x, 56 * y); }

void Game::startgame() {
  Sprite f[35];  // Pieces
  RenderWindow window(VideoMode(504, 560), "ENITCHESS");
  Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;
  if (load == 0) this->chessboard.initializeChessboard();
  this->chessboard.naiveMove(1);
  this->chessboard.naiveMove(2);
  display(this->chessboard, board);
  int size = 56, s = 0;
  t1.loadFromFile("img/Pieces.png");
  t2.loadFromFile("img/Chessboard.png");
  t3.loadFromFile("img/Player-1.png");
  t4.loadFromFile("img/Player-2.png");
  t5.loadFromFile("img/CPU1.png");
  t6.loadFromFile("img/CPU2.png");
  t7.loadFromFile("img/CPU3.png");
  t8.loadFromFile("img/CPU4.png");
  t9.loadFromFile("img/Save-Button.png");

  int indice;
  coord ini, dest, loc;
  loc.x = 0;
  loc.y = 0;
  dest.x = 0;
  dest.y = 0;
  ini.x = 0;
  ini.y = 0;
  bool test = false;
  for (int i = 0; i < 32; i++) f[i].setTexture(t1);
  Sprite sBoard(t2);
  loadPosition(board, f);
  f[33].setTexture(t9);
  int mode = 1;
  f[34].setTexture(t3);
  if (dynamic_cast<Ai*>(this->white)) {
    s = 1;
    mode = 1;
  } else if (dynamic_cast<Ai*>(this->black)) {
    Ai* test = dynamic_cast<Ai*>(this->black);
    mode = (test->difficulty);
  }
  if ((s == 0) && (load == 1)) mode = difsim + 1;
  load = 0;
  switch (mode) {
    case 1:
      f[32].setTexture(t4);
      break;
    case 2:
      f[32].setTexture(t5);
      break;
    case 3:
      f[32].setTexture(t6);
      break;
    case 4:
      f[32].setTexture(t7);
      break;
    case 5:
      f[32].setTexture(t8);
      break;
  }

  f[34].setPosition(56 * 0, 56 * 9);
  f[32].setPosition(56 * 0, 56 * 9);
  f[33].setPosition(56 * 5, 56 * 9);

  bool isMove = false, old = false;
  float dx = 0, dy = 0;
  Vector2f oldPos, newPos, var;
  std::string str;
  int n = 0;
  this->chessboard.naiveMove(nbtour + 1);
  this->chessboard.naiveMove(nbtour);
  this->chessboard.legalMove(nbtour);
  while (window.isOpen()) {
    Vector2i pos = Mouse::getPosition(window) - Vector2i(offset);
    Event e;

    while ((s == 0) && (window.pollEvent(e)) && ((mode == 1) || (nbtour % 2))) {
      if (e.type == Event::Closed) window.close();
      /////drag and drop///////

      if (f[33].getGlobalBounds().contains(pos.x, pos.y))
        if ((e.type == Event::MouseButtonPressed) &&
            (e.key.code == Mouse::Left)) {
          this->saveGame();
          window.close();
          system("clear");
          this->chessboard.initializeChessboard();
          this->nbtour = 1;
          Game x;
          x.startgame();
        }

      if (e.type == Event::MouseButtonPressed)
        if (e.key.code == Mouse::Left) {
          old = false;
          for (int i = 0; i < 32; i++)
            if (f[i].getGlobalBounds().contains(pos.x, pos.y)) {
              isMove = true;
              n = i;
              dx = pos.x - f[i].getPosition().x;
              dy = pos.y - f[i].getPosition().y;
              oldPos = f[i].getPosition();
              indice = i;
              if (old == false) {
                var = f[i].getPosition();
                old = true;
              }
            }
        }

      if (e.type == Event::MouseButtonReleased)
        if (e.key.code == Mouse::Left) {
          pos = Mouse::getPosition(window) - Vector2i(offset);
          isMove = false;
          Vector2f p = f[n].getPosition() + Vector2f(size / 2, size / 2);
          newPos = Vector2f(size * int(p.x / size), size* int(p.y / size));
          ini.x = (int)oldPos.y / 56;
          ini.y = (int)oldPos.x / 56;
          dest.x = (int)newPos.y / 56;
          dest.y = (int)newPos.x / 56;
          if (nbtour % 2) {
            bool Pawn = false;
            test = this->white->decideMove(this->chessboard, ini, dest);
            if (test) {
              for (int i = 0; i < 32; i++)
                if (f[i].getPosition() == newPos) f[i].setPosition(-100, -100);
              for (int i = 0; i < 32; i++)
                if (f[i].getPosition() == oldPos) f[i].setPosition(newPos);
              int x = this->chessboard.getPiece(ini)->value;
              this->chessboard.move(ini, dest, white);
              if (x != this->chessboard.getPiece(dest)->value) {
                window.close();
                load = 1;
                this->startgame();
                break;
                break;
              }

              this->chessboard.naiveMove(nbtour + 1);
              this->chessboard.legalMove(nbtour);
            }
          } else {
            test = this->black->decideMove(this->chessboard, ini, dest);
            if (test) {
              for (int i = 0; i < 32; i++)
                if (f[i].getPosition() == newPos) f[i].setPosition(-100, -100);
              for (int i = 0; i < 32; i++)
                if (f[i].getPosition() == oldPos) f[i].setPosition(newPos);
              int x = this->chessboard.getPiece(ini)->value;
              this->chessboard.move(ini, dest, black);
              if (x != this->chessboard.getPiece(dest)->value) {
                window.close();
                load = 1;
                this->startgame();
                break;
                break;
              }
              this->chessboard.naiveMove(nbtour + 1);
              this->chessboard.legalMove(nbtour);
            }
          }
          if (test) {
            str = toChessNote(oldPos) + toChessNote(newPos);
            if (oldPos != newPos) position += str + " ";
            f[n].setPosition(newPos);
            if (this->chessboard.endGame(nbtour + 1)) {
              window.close();
              endMenu(this->chessboard, nbtour, mode);
              break;
              break;
            }
            this->nbtour++;

          } else if (old == true) {
            old = false;
            f[indice].setPosition(var);
          }
        }
    }
    window.clear();
    window.draw(sBoard);
    for (int i = 0; i < 32; i++) f[i].move(offset);
    for (int i = 0; i < 32; i++) window.draw(f[i]);
    window.draw(f[n]);
    window.draw(f[33]);
    if ((this->nbtour) % 2)
      window.draw(f[34]);
    else
      window.draw(f[32]);
    for (int i = 0; i < 32; i++) f[i].move(-offset);
    window.display();
    if ((s == 1) || ((mode != 1) && (nbtour % 2 == 0))) {
      this->chessboard.naiveMove(nbtour + 1);
      this->chessboard.legalMove(nbtour);
      if (nbtour % 2)
        test = this->white->decideMove(this->chessboard, ini, dest);
      else
        test = this->black->decideMove(this->chessboard, ini, dest);

      if (test) {
        oldPos.x = ini.y * 56;
        oldPos.y = ini.x * 56;
        newPos.x = dest.y * 56;
        newPos.y = dest.x * 56;
        for (int i = 0; i < 32; i++)
          if (f[i].getPosition() == newPos) f[i].setPosition(-100, -100);

        for (int i = 0; i < 32; i++)
          if (f[i].getPosition() == oldPos) f[i].setPosition(newPos);

        if (nbtour % 2) {
          int x = this->chessboard.getPiece(ini)->value;
          this->chessboard.move(ini, dest, white);
          if (x != this->chessboard.getPiece(dest)->value) {
            window.close();
            load = 1;
            this->startgame();
            break;
            break;
          }
        } else {
          int x = this->chessboard.getPiece(ini)->value;
          this->chessboard.move(ini, dest, black);
          if (x != this->chessboard.getPiece(dest)->value) {
            window.close();
            load = 1;
            this->startgame();
            break;
            break;
          }
        }
        this->chessboard.naiveMove(nbtour + 1);
        this->chessboard.legalMove(nbtour);

        if (this->chessboard.endGame(nbtour)) {
          window.close();
          endMenu(this->chessboard, nbtour, mode);
        }
        usleep(500);
        this->nbtour++;
      }
    }
    if (isMove) f[n].setPosition(pos.x - dx, pos.y - dy);

    window.clear();
    window.draw(sBoard);
    for (int i = 0; i < 32; i++) f[i].move(offset);
    for (int i = 0; i < 32; i++) window.draw(f[i]);
    window.draw(f[n]);
    window.draw(f[33]);
    if ((this->nbtour) % 2)
      window.draw(f[34]);
    else
      window.draw(f[32]);
    for (int i = 0; i < 32; i++) f[i].move(-offset);
    window.display();
  }
}

void Game::resumeGame() {
  int lign, column, value, player;
  coord x;
  int difficulty;
  std::string myPath;
  cout << "Enter the path:" << endl;
  cin >> myPath;
  ifstream myFile(myPath.c_str());
  if (myFile.is_open()) {
    int n;
    myFile >> this->nbtour;
    myFile >> difficulty;
    if (difficulty == 0)
      this->white = new Human;
    else
      this->white = new Ai(difficulty);
    myFile >> difficulty;
    if (difficulty == 0)
      this->black = new Human;
    else
      this->black = new Ai(difficulty);
    difsim = difficulty;
    this->black->color = 2;
    this->white->color = 1;
    while (myFile >> lign >> column >> value >> player) {
      x.x = lign;
      x.y = column;
      Piece* input = NULL;
      switch (value) {
        case 999:
          input = new King(player);
          break;
        case 1:
          input = new Pawn(player);
          break;
        case 4:
          input = new Knight(player);
          break;
        case 3:
          input = new Bishop(player);
          break;
        case 5:
          input = new Rook(player);
          break;
        case 10:
          input = new Queen(player);
          break;
      }
      this->chessboard.setPiece(input, x);
    }
    myFile.close();
    this->chessboard.naiveMove(this->nbtour + 1);
    this->chessboard.legalMove(this->nbtour);
    load = 1;
    this->startgame();
  } else
    cout << "Error: File not found" << endl;
}

void Game::saveGame() {
  std::string myPath;
  cout << "Enter the path:" << endl;
  cin >> myPath;
  ofstream myFile(myPath.c_str(), ios::trunc);
  coord x;
  myFile << this->nbtour << endl;
  myFile << this->white->requestSave() << endl;
  myFile << this->black->requestSave() << endl;
  for (int lign = 0; lign < 8; lign++) {
    for (int column = 0; column < 8; column++) {
      x.x = lign;
      x.y = column;
      if (this->chessboard.pieceCheck(x))
        myFile << lign << " " << column << " "
               << this->chessboard.getPiece(x)->value << " "
               << this->chessboard.getPiece(x)->player << endl;
    }
  }
}