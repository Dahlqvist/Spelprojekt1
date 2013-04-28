#include"Editor.h"
#include<iostream>
#include<string>

int main(int numArgs, char* Args[])
{
	for(int i=0;i<numArgs;i++)
	{
		std::string temp;
		temp=Args[i];
		std::cout<<temp<<std::endl;
	}
	std::cout<<"Done";
	Editor*	edit;
	if(numArgs>1)
	{
		std::string temp(Args[1],std::char_traits<char>::length(Args[1]));
		cout<<"\n"<<temp<<"\nstopid\n"<<strlen(Args[1])<<temp.size();
		edit=new Editor(temp);
	}
	else
	{
		edit=new Editor();
	}
	edit->run();
	delete edit;
	return 0;
}