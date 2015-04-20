#ifndef POSITION_CPP
#define POSITION_CPP

#include "form.h"
/* All the functions of cell. essentially, connvectivity.cpp */


/* Generating adjacent positions. */
Position Position::up() { Position p(r-1,c); return p; }
Position Position::down() { Position p(r+1,c); return p; }
Position Position::right() { Position p(r,c+1); return p; }
Position Position::left() { Position p(r,c-1); return p; }

Position Position::d_up() { Position p(r-2,c); return p; }
Position Position::d_down() { Position p(r+2,c); return p; }
Position Position::d_right() { Position p(r,c+2); return p; }
Position Position::d_left() { Position p(r,c-2); return p; }

Position Position::up_right() { Position p(r-1,c+1); return p; }
Position Position::up_left() { Position p(r-1,c-1); return p; }
Position Position::down_right() { Position p(r+1,c+1); return p; }
Position Position::down_left() { Position p(r+1,c-1); return p; }

/* Checking if this position is relative to input position. */
bool Position::is_up(Position& p) {  return (((*this).r==(p.r-1))&&((*this).c==(p.c))); }
bool Position::is_down(Position& p) {  return (((*this).r==(p.r+1))&&((*this).c==(p.c))); }
bool Position::is_right(Position& p) {  return (((*this).r==(p.r))&&((*this).c==(p.c+1))); }
bool Position::is_left(Position& p) {  return (((*this).r==(p.r))&&((*this).c==(p.c-1))); }

bool Position::is_d_up(Position& p) { return (((*this).r==(p.r-2))&&((*this).c==(p.c))); }
bool Position::is_d_down(Position& p) { return (((*this).r==(p.r+2))&&((*this).c==(p.c))); }
bool Position::is_d_right(Position& p) { return (((*this).r==(p.r))&&((*this).c==(p.c+2))); }
bool Position::is_d_left(Position& p) { return (((*this).r==(p.r))&&((*this).c==(p.c-2))); }

bool Position::is_up_right(Position& p) {  return (((*this).r==(p.r-1))&&((*this).c==(p.c+1))); }
bool Position::is_up_left(Position& p) {  return (((*this).r==(p.r-1))&&((*this).c==(p.c-1)))  ;}
bool Position::is_down_right(Position& p) { return (((*this).r==(p.r+1))&&((*this).c==(p.c+1))) ; }
bool Position::is_down_left(Position& p) { return (((*this).r==(p.r+1))&&((*this).c==(p.c-1)))  ;}

int Position::l1_norm(Position& p) { return ( abs(r-p.r) + abs(c-p.c) ); }
double Position::l2_norm(Position& p) { return ( pow(r-p.r,2) + pow(c-p.c,2) ) ;}

/* The end. */
#endif