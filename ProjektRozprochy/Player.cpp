#include "Player.h"
#include "Team.h"

Player::Player()
{
	this->image = NULL;
	this->x = 0;
	this->y = 0;
}

Player::Player(double x, double y, Squad t)
{
	team = t;
	if (team == red) {
		this->image = al_load_bitmap("redPlayer.png");
	} else if (team == blue) {
		this->image = al_load_bitmap("bluePlayer.png");
	}
	al_convert_mask_to_alpha(this->image, al_map_rgb(255, 255, 0));

	this->x = x;
	this->y = y;
}

Player::~Player()
{
	al_destroy_bitmap(image);
}

void Player::Draw()
{
	double xStart = x - PLAYER_SIZE / 2.0;
	double yStart = y - PLAYER_SIZE / 2.0;
	al_draw_bitmap(image, xStart, yStart, 0);
}

double Player::GetX()
{
	return x;
}

void Player::SetX(double x)
{
	if (x > X_RIGHT_BOUNDRY) {
		this->x = X_RIGHT_BOUNDRY;
	} else if (x < X_LEFT_BOUNDRY) {
		this->x = X_LEFT_BOUNDRY;
	} else {
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
	} else if (y < Y_UP_BOUNDRY) {
		this->y = Y_UP_BOUNDRY;
	} else {
		this->y = y;
	}
}

void Player::AddX(double a, Team* redTeam, Team* blueTeam)
{
	Player* temp = NULL;
	double distance = NULL;
	double shift = NULL;
	double temp_y = NULL;
	double new_v = NULL;
	bool collision = false;

	if (x + a > X_RIGHT_BOUNDRY) {
		x = X_RIGHT_BOUNDRY;
	} else if (x + a < X_LEFT_BOUNDRY) {
		x = X_LEFT_BOUNDRY;
	} else {
		x += a;
	}
	for (int t = 0; t < SQUAD_NR_ITEMS; t++) {
		for (int i = 0; i < PLAYERS_IN_TEAM; i++) {
			if (t == red) {
				temp = redTeam->GetPlayers()[i];
			} else if (t == blue) {
				temp = blueTeam->GetPlayers()[i];
			}

			distance = sqrt(pow(y - temp->GetY(), 2.0) + pow(x - temp->GetX(), 2.0));
			if (temp != this && distance < PLAYER_SIZE) {
				shift = sqrt(pow(PLAYER_SIZE, 2.0) - pow(x - temp->GetX(), 2.0));
				temp_y = temp->GetY() - shift*fsign(temp->GetY() - y);

				if (collision == false && temp_y >= Y_UP_BOUNDRY && temp_y <= Y_DOWN_BOUNDRY) {
					y = temp_y;
				}

				shift = sqrt(pow(PLAYER_SIZE, 2.0) - pow(y - temp->GetY(), 2.0));
				x = temp->GetX() - shift*fsign(temp->GetX() - x);
				collision = true;
			}
		}
	}
}

void Player::AddY(double a, Team* redTeam, Team* blueTeam)
{
	Player* temp = NULL;
	double distance = NULL;
	double shift = NULL;
	double temp_x = NULL;
	bool collision = false;

	if (y + a > Y_DOWN_BOUNDRY) {
		y = Y_DOWN_BOUNDRY;
	} else if (y + a < Y_UP_BOUNDRY) {
		y = Y_UP_BOUNDRY;

	} else {
		y += a;
	}

	for (int t = 0; t < SQUAD_NR_ITEMS; t++) {
		for (int i = 0; i < PLAYERS_IN_TEAM; i++) {
			if (t == red) {
				temp = redTeam->GetPlayers()[i];
			} else if (t == blue) {
				temp = blueTeam->GetPlayers()[i];
			}

			distance = sqrt(pow(y - temp->GetY(), 2.0) + pow(x - temp->GetX(), 2.0));
			if (temp != this && distance < PLAYER_SIZE) {
				shift = sqrt(pow(PLAYER_SIZE, 2.0) - pow(y - temp->GetY(), 2.0));
				temp_x = temp->GetX() - shift*fsign(temp->GetX() - x);

				if (collision == false && temp_x >= X_LEFT_BOUNDRY && temp_x <= X_RIGHT_BOUNDRY) {
					x = temp_x;
				}

				shift = sqrt(pow(PLAYER_SIZE, 2.0) - pow(x - temp->GetX(), 2.0));
				y = temp->GetY() - shift*fsign(temp->GetY() - y);
				collision = true;
			}
		}
	}
}