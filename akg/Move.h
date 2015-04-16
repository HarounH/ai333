#ifndef MOVE_H
#define MOVE_H

#include <utility>

using namespace std;

typedef pair<int, int> Pos;

struct PosHasher{
	size_t operator()(const Pos& k) const{
		return (hash<int>()(k.first) ^ (hash<int>()(k.second) << 1));
	}
};

struct Move {
	int choice;
	Pos pos;
	
	Move()
	{
		choice  = pos.first = pos.second = 0;
	}
	
	Move(int a, int b, int c)
	{
		choice = a;
		pos.first = b;
		pos.second = c;
	}
	
	Move(int a, Pos b)
	{
		choice = a;
		pos = b;
	}
	
	Move(const Move& other)
	{
		choice = other.choice;
		pos = other.pos;
	}
	
	Move& operator =(const Move& other)
	{
		choice = other.choice;
		pos = other.pos;
		return *this;
	}
};

#endif