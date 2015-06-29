#include "Player.h"
#include "Team.h"

Player::Player()
{
	this->x = 0;
	this->y = 0;
}

Player::Player(double x, double y, Squad t)
{
	team = t;

	this->kicking = false;
	this->x = x;
	this->y = y;
}


double Player::GetX()
{
	return x;
}

void Player::SetX(double x)
{
	if (x > X_RIGHT_BOUNDRY) {
		this->x = X_RIGHT_BOUNDRY;
	}
	else if (x < X_LEFT_BOUNDRY) {
		this->x = X_LEFT_BOUNDRY;
	}
	else {
		this->x = x;
	}
}

double Player::GetY()
{
	return y;
}

void Player::SetY(double y)
{
	if (y > Y_DOWN_BOUNDRY) {
		this->y = Y_DOWN_BOUNDRY;
	}
	else if (y < Y_UP_BOUNDRY) {
		this->y = Y_UP_BOUNDRY;
	}
	else {
		this->y = y;
	}
}

void Player::AddX(double a, Team* redTeam, Team* blueTeam, Ball* ball)
{
	Player* temp = NULL;

	double distance = NULL;
	double shift = NULL;
	double temp_y = NULL;
	double coeff_a = NULL;
	double coeff_b = NULL;
	double new_y = NULL;
	double reduced_x = NULL; // its needed to fix the bug couses teleporting the ball
	double delta_y = NULL;
	double delta_x = NULL;
	bool collision = false;
	bool near_the_boundry = false;


	if (x + a > X_RIGHT_BOUNDRY) {
		x = X_RIGHT_BOUNDRY;
	}
	else if (x + a < X_LEFT_BOUNDRY) {
		x = X_LEFT_BOUNDRY;
	}
	else {
		x += a;
	}
	for (int t = 0; t < SQUAD_NR_ITEMS; t++) {
		for (int i = 0; i < PLAYERS_IN_TEAM; i++) {
			if (t == red) {
				temp = redTeam->GetPlayers()[i];
			}
			else if (t == blue) {
				temp = blueTeam->GetPlayers()[i];
			}
			delta_y = pow(fabs(temp->GetY() - y), 1.0/3.0);
			distance = sqrt(pow(y - temp->GetY(), 2.0) + pow(x - temp->GetX(), 2.0));
			reduced_x = x - (a / delta_y);
			if (temp != this && distance < PLAYER_SIZE) {
				shift = sqrt(pow(PLAYER_SIZE, 2.0) - pow(reduced_x - temp->GetX(), 2.0));
				temp_y = temp->GetY() - shift*fsign(temp->GetY() - y);

				if (collision == false && temp_y >= Y_UP_BOUNDRY && temp_y <= Y_DOWN_BOUNDRY) {
					y = temp_y;
				}

				shift = sqrt(pow(PLAYER_SIZE, 2.0) - pow(y - temp->GetY(), 2.0));
				x = temp->GetX() - shift*fsign(temp->GetX() - reduced_x);
				collision = true;
			}
		}
	}
	delta_y = ball->GetY() - y;
	delta_x = ball->GetX() - x;
	distance = sqrt(pow(y - ball->GetY(), 2.0) + pow(x - ball->GetX(), 2.0));
	if (distance < PLAYER_SIZE / 2.0 + BALL_SIZE / 2.0)
	{
		//part responsible for collision of the player with the ball
		shift = sqrt(pow(PLAYER_SIZE / 2.0 + BALL_SIZE / 2.0, 2.0) - pow(y - ball->GetY(), 2.0));
		x = ball->GetX() - shift*fsign(ball->GetX() - x);
		collision = true;

		//part responsible for movement of the ball
		near_the_boundry = this->GetX() == X_LEFT_BOUNDRY || this->GetX() == X_RIGHT_BOUNDRY ||
			this->GetY() == Y_DOWN_BOUNDRY || this->GetY() == Y_UP_BOUNDRY;

		if (horizontally == true && fabs(delta_y) > fabs(delta_x) && near_the_boundry == false) {
			if (fsign(delta_y) == ysign) {
				ball->SetSpeed((delta_y)*DIRECTING_COEFF, delta_x, horizontal, false);
			}
			else if (fsign(delta_y) != ysign && fabs(delta_y) <= BALL_SIZE / 2.0 + PLAYER_SIZE / 2.0) {
				ball->SetSpeed(0, delta_x, horizontal, false);
			}
			else {
				ball->SetSpeed(delta_y, delta_x, horizontal, false);
			}
		}
		else if (horizontally == true && fabs(delta_y) < fabs(delta_x) && near_the_boundry == false) {
			if (fsign(delta_x) == fsign(a)) {
				ball->SetSpeed(delta_y, delta_x*DIRECTING_COEFF, vertical, false);
			}
			else if (fsign(delta_x) != fsign(a) && fabs(delta_x) <= BALL_SIZE / 2.0 + PLAYER_SIZE / 2.0) {
				ball->SetSpeed(delta_y, 0, vertical, false);
			}
			else {
				ball->SetSpeed(delta_y, delta_x, vertical, false);
			}
		}
		else {
			ball->SetSpeed(delta_y, delta_x, vertical, false);
		}
	}
}

void Player::AddY(double a, Team* redTeam, Team* blueTeam, Ball* ball)
{
	Player* temp = NULL;
	double distance = NULL;
	double shift = NULL;
	double temp_x = NULL;
	double coeff_a = NULL;
	double coeff_b = NULL;
	double delta_x = NULL;
	double reduced_y = fabs(a);
	bool collision = false;

	if (y + a > Y_DOWN_BOUNDRY) {
		y = Y_DOWN_BOUNDRY;
	}
	else if (y + a < Y_UP_BOUNDRY) {
		y = Y_UP_BOUNDRY;

	}
	else {
		y += a;
	}

	for (int t = 0; t < SQUAD_NR_ITEMS; t++) {
		for (int i = 0; i < PLAYERS_IN_TEAM; i++) {
			if (t == red) {
				temp = redTeam->GetPlayers()[i];
			}
			else if (t == blue) {
				temp = blueTeam->GetPlayers()[i];
			}

			delta_x = pow(fabs(temp->GetX() - x), 1.0/3.0);
			distance = sqrt(pow(y - temp->GetY(), 2.0) + pow(x - temp->GetX(), 2.0));
			reduced_y = y - (a / delta_x);
			if (temp != this && distance < PLAYER_SIZE) {
				shift = sqrt(pow(PLAYER_SIZE, 2.0) - pow(reduced_y - temp->GetY(), 2.0));
				temp_x = temp->GetX() - shift*fsign(temp->GetX() - x);

				if (collision == false && temp_x >= X_LEFT_BOUNDRY && temp_x <= X_RIGHT_BOUNDRY) {
					x = temp_x;
				}

				shift = sqrt(pow(PLAYER_SIZE, 2.0) - pow(x - temp->GetX(), 2.0));
				y = temp->GetY() - shift*fsign(temp->GetY() - reduced_y);
				collision = true;
			}
		}
	}
	distance = sqrt(pow(y - ball->GetY(), 2.0) + pow(x - ball->GetX(), 2.0));
	if (distance < PLAYER_SIZE / 2.0 + BALL_SIZE / 2.0)
	{
		//part responsible for collision of the player with the ball
		shift = sqrt(pow(PLAYER_SIZE / 2.0 + BALL_SIZE / 2.0, 2.0) - pow(x - ball->GetX(), 2.0));
		y = ball->GetY() - shift*fsign(ball->GetY() - y);
		collision = true;

		//part responsible for movement of the ball
		if (x - ball->GetX() == 0) {
			ball->SetSpeed(ball->GetY() - y, 0, horizontal, false);
		}
		else {
			ball->SetSpeed(ball->GetY() - y, ball->GetX() - x, horizontal, false);
		}
	}
}

void Player::SetHorizontally(bool horizontally, double ysign)
{
	this->horizontally = horizontally;
	this->ysign = ysign;
}

void Player::Kicked(Ball* ball)
{
	double distance = NULL;
	double new_x = NULL;
	double new_y = NULL;

	distance = sqrt(pow(y - ball->GetY(), 2.0) + pow(x - ball->GetX(), 2.0));
	if (distance < PLAYER_SIZE / 2.0 + BALL_SIZE / 2.0 + KICK_DISTANCE)
	{
		if (fabs(y - ball->GetY()) > fabs(x - ball->GetX())){
			if (x - ball->GetX() == 0) {
				ball->SetSpeed(ball->GetY() - y, 0, horizontal, true);
			}
			else {
				ball->SetSpeed(ball->GetY() - y, ball->GetX() - x, horizontal, true);
			}
		}
		else {
			ball->SetSpeed(ball->GetY() - y, ball->GetX() - x, vertical, true);
		}

	}
}