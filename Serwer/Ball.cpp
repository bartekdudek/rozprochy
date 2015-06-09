#pragma once
#include "Ball.h"
#include "Team.h"
#include "Player.h"

Ball::Ball(double x, double y)
{
	this->x = x;
	this->y = y;
	this->vy = 0;
	this->vx = 0;
	this->v = 0;
}

double Ball::GetX()
{
	return x;
}

double Ball::GetY()
{
	return y;
}

void Ball::MoveBall(Team* redTeam, Team* blueTeam)
{
	Player* temp;
	bool collision = false;
	double distance = NULL;
	double shift = NULL;
	double temp_x = NULL;
	double temp_y = NULL;
	double coeff_a = NULL;
	double coeff_b = NULL;
	double dist_simple_to_point = NULL;
		if (y + vy > Y_DOWN_BOUNDRY) {
			this->y = Y_DOWN_BOUNDRY - MOVE_CHANGE;
			vy *= -1.0;
		}
		else if (y + vy < Y_UP_BOUNDRY) {
			this->y = Y_UP_BOUNDRY + MOVE_CHANGE;
			vy *= -1.0;
		}
		else {
			this->y += vy;
		}

		if (x + vx > X_RIGHT_BOUNDRY) {
			this->x = X_RIGHT_BOUNDRY - MOVE_CHANGE;
			vx *= -1.0;
		}
		else if (x + vx < X_LEFT_BOUNDRY) {
			this->x = X_LEFT_BOUNDRY + MOVE_CHANGE;
			vx *= -1.0;
		}
		else {
			this->x += vx;
		}

	v /= 1.004;

	if (v < 0) {
		v = 0;
		vy = 0;
		vx = 0;
	}

	for (int t = 0; t < SQUAD_NR_ITEMS; t++) {
		for (int i = 0; i < PLAYERS_IN_TEAM; i++) {
			if (t == red) {
				temp = redTeam->GetPlayers()[i];
			}
			else if (t == blue) {
				temp = blueTeam->GetPlayers()[i];
			}

			distance = sqrt(pow(y - temp->GetY(), 2.0) + pow(x - temp->GetX(), 2.0));
			if (distance < PLAYER_SIZE / 2 + BALL_SIZE / 2) {
				if (fabs(vy) > fabs(vx))
				{
					shift = sqrt(pow(PLAYER_SIZE, 2.0) - pow(y - temp->GetY(), 2.0));
					temp_x = temp->GetX() - shift*fsign(temp->GetX() - x);


					shift = sqrt(pow(PLAYER_SIZE, 2.0) - pow(x - temp->GetX(), 2.0));
					y = temp->GetY() - shift*fsign(temp->GetY() - y);
				}
				else {
					shift = sqrt(pow(PLAYER_SIZE, 2.0) - pow(y - temp->GetY(), 2.0));
					temp_x = temp->GetX() - shift*fsign(temp->GetX() - x);
					if (collision == false && temp_x >= X_LEFT_BOUNDRY && temp_x <= X_RIGHT_BOUNDRY) {
						x = temp_x;
					}

					shift = sqrt(pow(PLAYER_SIZE, 2.0) - pow(x - temp->GetX(), 2.0));
					temp_y = temp->GetY() - shift*fsign(temp->GetY() - y);
					if (collision == false && temp_y >= Y_UP_BOUNDRY && temp_y <= Y_DOWN_BOUNDRY) {
						y = temp_y;
					}
					collision = true;
				}
				if (v > MOVE_CHANGE)
				{
					temp_y = y + vy;
					temp_x = x + vx;
					coeff_a = (y - temp_y) / (x - temp_x);
					coeff_b = temp_y - coeff_a * temp_x;
					dist_simple_to_point = fabs(coeff_a*temp->GetX() - 1.0*temp->GetY() + coeff_b) /
						sqrt(pow(coeff_a, 2.0) + 1);

					if (dist_simple_to_point > PLAYER_SIZE / 2.0 && direction == vertical){
						vy *= 3.0;
					}
					else if (dist_simple_to_point > PLAYER_SIZE / 2.0 && direction == horizontal) {
						vx *= 3.0;
					}
					else {
						vx *= -1.0;
						vy *= -1.0;
					}
					if (direction == horizontal) {
						angle = atan(tan(vx / vy));
					}
					else {
						angle = atan(tan(vy / vx));
					}
					if (angle < 0)
						angle *= -1.0;
					v *= 0.5;
				}
				collision = true;
			}
		}
	}

	if (direction == vertical && v > 0){
		vy = fsign(vy)*sin(angle) * v;
		vx = fsign(vx)*cos(angle) * v;
	}
	else if (v > 0) {
		vy = fsign(vy)*cos(angle) * v;
		vx = fsign(vx)*sin(angle) * v;
	}
}

void Ball::SetSpeed(double vy, double vx, int direction, bool kicked)
{
	this->direction = direction;
	this->vy = fsign(vy);
	this->vx = fsign(vx);
	if (direction == horizontal) {
		angle = atan(tan(vx / vy));
	}
	else {
		angle = atan(tan(vy / vx));
	}
	if (angle < 0)
		angle *= -1.0;
	v = MOVE_CHANGE;

	if (kicked == true){
		v = MOVE_CHANGE*6.0;
	}
}

