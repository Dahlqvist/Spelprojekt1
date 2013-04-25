#ifndef		INC_XMLLOADER
#define		INC_XMLLOADER
#include	<rapidxml.hpp>
#include	<string>

using namespace rapidxml;

//Class is Done
class	XmlLoader
{
public:
	//Uninitalized constructor
	XmlLoader();
	//Initalized constructor
	XmlLoader(std::string FileName);
	//Loads a XML-File and returns if it worked
	bool	loadFile(std::string	FileName);
protected:
	//Returns a string of the value from a child node
	std::string	getValue(xml_node<>* Node);
	//Memebervariables
	xml_document<>	mDocument;
	//Bool for checking if the file is open
	bool	mFileOpen;
};

#endif