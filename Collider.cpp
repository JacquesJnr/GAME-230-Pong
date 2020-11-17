#include "Collider.h"

Collider::Collider(sf::RectangleShape& body) : body(body)
{

}

bool Collider::CheckCollision(Collider& other, float pushAway)
{
	//Get the positions and half-sizes of colliding objects
	sf::Vector2f thisPosition = this->GetPosition();
	sf::Vector2f thisHalfSize = this->GetHalfSize();
	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f otherHalfSize = other.GetHalfSize();

	//Define the delta between the colliding objects
	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	// Define intersection
	int intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	int intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f) // Objects are interecting
	{
		//Clamp collision response
		pushAway = std::min(std::max(pushAway, 0.0f), 1.0f);

		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f) { //Move the colliding objects opposite ways from eachother on the X axis
				Move(intersectX * (1.0f - pushAway), 0.0f);
				other.Move(-intersectX * pushAway, 0.0f);
			}
			else
			{
				Move(-intersectX * (1.0f - pushAway), 0.0f);
				other.Move(intersectX * pushAway, 0.0f);
			}
		}
		else
		{
			if (deltaY > 0.0f) { //Move the colliding objects opposite ways from eachother on the Y axis
				Move(0.0f, intersectY * (1.0f - pushAway));
				other.Move(0.0f, -intersectY * pushAway);
			}
			else
			{
				Move(0.0f, -intersectY * (1.0f - pushAway));
				other.Move(0.0f, intersectY * pushAway);
			}
		}

		return true;
	}

	return false;
}
