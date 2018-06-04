#include "Input.h"
#include "Camera.h"

//void processKeys()
//{
//	if (keys['W'])
//	{
//		player->changeTranslationY(1.0f);
//		camera->setYCoordinates(player->getCoordinatesY());
//		//std::cout << "JUMP" << std::endl;
//	}
//	if (keys['S'])
//	{
//		player->changeTranslationY(-1.0f);
//		camera->setYCoordinates(player->getCoordinatesY());
//		//std::cout << "down: " << translateY << std::endl;
//	}
//	if (keys['A'])
//	{
//		player->changeTranslationX(-1.0f);
//		camera->setXCoordinates(player->getCoordinatesX());
//		//std::cout << "left: " << translateX << std::endl;
//	}
//	if (keys['D'])
//	{
//		player->changeTranslationX(1.0f);
//		camera->setXCoordinates(player->getCoordinatesX());
//		//std::cout << "right: " << translateX << std::endl;
//	}
//
//	if (keys['K'])
//	{
//		if (jumpActive == false)
//		{
//			jumpActive = true;
//			std::cout << "jumpActive set True" << std::endl;
//		}
//	}
//}