#include	<rapidxml_print.hpp>
#include	<fstream>
//#include	<iostream>
#include	<stdlib.h>
#include	<sstream>

#include	"XmlSaver.h"

using namespace rapidxml;

XmlSaver::XmlSaver(void)
	:mDocument()
{
}

XmlSaver::XmlSaver(string Filename)
	:mDocument()
{
	setFilename(Filename);
}

XmlSaver::~XmlSaver(void)
{
}

char*	XmlSaver::modifyString(const string &Source)
{
	string temp;
	temp="\""+Source+"\"";
	char *ret = new char[temp.size()+1];
	strcpy(ret,temp.c_str());
	return ret;
}

char*	XmlSaver::modifyInt(const int &Source)
{
	char	*tempValue=	new char[256];
	itoa(Source,tempValue,10);
	return	tempValue;
}

void	XmlSaver::setFilename(const string& NewName)
{
	if(mFilename.find(".xml")!=std::string::npos)
	{
		mFilename=NewName+".xml";
	}
	else
	{
		mFilename=NewName;	
	}
}

void	XmlSaver::createFile()
{
	//Creates the file to write to
	std::ofstream	file;
	file.open(mFilename);
	assert(file.is_open());
	//Sets the standard of xml on the file
	file<<"<?xml version=\"1.0\"?>"<<endl;
	//Writes the document to the file
	file<<mDocument;
	file.close();
}