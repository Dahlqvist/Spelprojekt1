#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
//#include <dirent.h>
#include <iostream>
#include <string>
using namespace sf;
int main(int argc, char *argv[])
{
	RenderWindow window(sf::VideoMode(1280, 768), "Robot split Editor");
	while(window.isOpen())
	{
		Event CurrentEvent;
		while(window.pollEvent(CurrentEvent))
		{

			if(CurrentEvent.type==Event::EventType::Closed)
			{
				window.close();
			} 
		}
	}
}
/*Exemple på dirent
void main(int argc, char *argv[]) 
{
	string	temp;
	temp=argv[0];
	temp.erase(temp.find_last_of("\\"));
	DIR	*direct;
	dirent *directNext;
	direct=opendir(temp.c_str());
	directNext =readdir(direct);
	while(directNext!=0)
	{
		cout<<directNext->d_name<<endl;
		directNext =readdir(direct);
	}
	system("PAUSE");
}

*/