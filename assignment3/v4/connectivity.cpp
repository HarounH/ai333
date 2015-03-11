#ifndef CONNECTIVITY_CPP
#define CONNECTIVITY_CPP
bool State::connected_up(Position& p) { 
	Position to= p.up();
	if ( !in_bounds(to) ) { return false; }
	return (
		(!((pos_other==to)))
		&&  (!wall_up(p))
		);
}
bool State::connected_down(Position& p) { 
	Position to=p.down();
	if ( !in_bounds(to) ) { return false; }
	return (
		(!((pos_other==to)))
		&&  (!wall_down(p))
		); 
}
bool State::connected_right(Position& p) { 
	Position to=p.right();
	if ( !in_bounds(to) ) { return false; }
	return (
		(!((pos_other==to)))
		&&  (!wall_right(p))
		);
}
bool State::connected_left(Position& p) { 
	Position to=p.left();
	if ( !in_bounds(to) ) { return false; }
	return (
		(!((pos_other==to)))
		&&  (!wall_left(p))
		); 
}

//Part 1 Done!.

bool State::connected_d_up(Position& p) { 
	Position to=p.d_up();
	Position bl=p.up();
	if ( !in_bounds(to) ) { return false; }
	return (
		((pos_other==bl))
		&& (!wall_up(p))
		&& (!((pos_other==to)))
		&&  (!wall_d_up(p))
		);
}
bool State::connected_d_down(Position& p) { 
	Position to=p.d_down();
	Position bl=p.down();
	if ( !in_bounds(to) ) { return false; }
	return (
		((pos_other==bl))
		&& (!wall_down(p))
		&& (!((pos_other==to)))
		&&  (!wall_d_down(p))
		);
}
bool State::connected_d_right(Position& p) { 
	Position to=p.d_right();
	Position bl=p.right();
	if ( !in_bounds(to) ) { return false; }
	return (
		((pos_other==bl))
		&& (!wall_right(p))
		&& (!((pos_other==to)))
		&&  (!wall_d_right(p))
		);
}
bool State::connected_d_left(Position& p) { 
	Position to=p.d_left();
	Position bl=p.left();
	if ( !in_bounds(to) ) { return false; }
	return (
		((pos_other==bl))
		&& (!wall_left(p))
		&& (!((pos_other==to)))
		&&  (!wall_d_left(p))
		);
}

//part2 : Done!

bool State::connected_up_right(Position& p) { 
	Position to = p.up_right();
	if ( !in_bounds(to) ) { return false; }
	if (!((pos_other==to))) { //Player doesnt block my destination
		//Destination isn't blocked.
		
		Position up = p.up();
		Position right = p.right();
		if ( pos_other==up ) { //Case1 : Blocked above.
			return (
				(!wall_up(p))
				&& (!wall_right(up) )
				);
		}
		
		else if ( pos_other==right ) { //Case2 : Blocked to the right.
			return (
				(!wall_right(p))
				&& (!wall_up(right) )
				);
		} else {
			return false;
		}
	}
	return false;
}

bool State::connected_up_left(Position& p) { 
	Position to = p.up_left();
	if ( !in_bounds(to) ) { return false; }
	if (!((pos_other==to))) { //Player doesnt block my destination
		//Destination isn't blocked.
		
		Position up = p.up();
		Position left = p.left();
		if ( pos_other==up ) { //Case1 : Blocked above.
			return (
				(!wall_up(p))
				&& (!wall_left(up) )
				);
		}
		
		else if ( pos_other==left ) { //Case2 : Blocked to the right.
			return (
				(!wall_left(p))
				&& (!wall_up(left) )
				);
		} else {
			return false;
		}
	}
	return false;
}

bool State::connected_down_right(Position& p) { 
	Position to = p.down_right();
	if ( !in_bounds(to) ) { return false; }
	if (!((pos_other==to))) { //Player doesnt block my destination
		//Destination isn't blocked.
		
		Position down = p.down();
		Position right = p.right();
		if ( pos_other==down ) { //Case1 : Blocked above.
			return (
				(!wall_down(p))
				&& (!wall_right(down) )
				);
		}
		
		else if ( pos_other==right ) { //Case2 : Blocked to the right.
			return (
				(!wall_right(p))
				&& (!wall_down(right) )
				);
		} else {
			return false;
		}
	}
	return false;
}

bool State::connected_down_left(Position& p) { 
	Position to = p.down_left();
	if ( !in_bounds(to) ) { return false; }
	if (!((pos_other==to))) { //Player doesnt block my destination
		//Destination isn't blocked.
		
		Position down = p.down();
		Position left = p.left();
		if ( pos_other==down ) { //Case1 : Blocked above.
			return (
				(!wall_down(p))
				&& (!wall_left(down) )
				);
		}
		
		else if ( pos_other==left ) { //Case2 : Blocked to the right.
			return (
				(!wall_left(p))
				&& (!wall_down(left) )
				);
		} else {
			return false;
		}
	}
	return false;
}

#endif