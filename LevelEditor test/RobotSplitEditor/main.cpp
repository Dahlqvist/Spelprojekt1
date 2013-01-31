#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <dirent.h>
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
			switch(CurrentEvent.type)
			{
			case Event::EventType::Closed:
				window.close();
				break;
			case Event::EventType::TextEntered:
				  if (CurrentEvent.text.unicode < 128)
					   std::cout << "ASCII character typed: " << static_cast<char>(CurrentEvent.text.unicode) << std::endl;
				  break;
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