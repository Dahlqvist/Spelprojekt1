#include <fstream>
#include <sstream>
#include <assert.h>
#include <stdlib.h>

#include "XmlLoader.h"

using namespace	std;


XmlLoader::XmlLoader()
	:mDocument(),mFileOpen(false)
{
}

XmlLoader::XmlLoader(string	FileName)
	:mDocument()
{
	loadFile(FileName);
}

bool	XmlLoader::loadFile(std::string	FileName)
{
	ifstream	xmlFil;
	string		xmlText;
	//Clears the document
	mDocument.clear();
	//Opens the xml file
	xmlFil.open(FileName);
	//Checks if the file is open
	mFileOpen=xmlFil.is_open();
	//Starts the load session if the file is open
	if(mFileOpen)
	{
		while(!xmlFil.eof())
		{
			string temp;
			//The line gets transfered to the temp  string
			getline(xmlFil,temp);
			//The temp string gets added to the xmlText string
			xmlText+=temp;
		}
		char	*temp=new char[xmlText.length()+1];
		//Copies the xmlText string to the temp c-string
		strcpy(temp, xmlText.c_str());
		//The xml document parses the c-string
		//Bascily constructing the XmlTree
		mDocument.parse<0>(temp);
	}
	return	mFileOpen;
}



string	XmlLoader::getValue(xml_node<>* Node)
{
	string temp;
	int i=0,max=Node->value_size();
	for(i;i<max;i++)
	{
		temp+=Node->value()[i];
	}
	if(temp.find('"')!=string::npos)
	{
		temp=	temp.substr(temp.find_first_of('"')+1,temp.find_last_of('"')-temp.find_first_of('"')-1);
	}
	return temp;
}
