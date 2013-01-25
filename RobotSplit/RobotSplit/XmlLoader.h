#ifndef		INC_XMLLOADER
#define		INC_XMLLOADER
#include	<rapidxml.hpp>
#include	<string>

using namespace rapidxml;

//Class is Done
class	XmlLoader
{
public:
	//Uninitalized constructor							(Done)
	XmlLoader();
	//Initalized constructor							(Done)
	XmlLoader(std::string FileName);
	//Loads a XML-File									(Done)
	void	loadFile(std::string	FileName);
protected:
	//Returns a string of the value from a child node	(Done)
	std::string	getValue(xml_node<>* Node);
	//Memebervariables									(Done)
	xml_document<>	mDocument;
};

#endif