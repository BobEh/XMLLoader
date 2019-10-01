#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <rapidXML/rapidxml.hpp>
#include <rapidXML/rapidxml_print.hpp>

using namespace rapidxml;

int main()
{
	xml_document<> document;
	xml_node<>* root_node;
	std::string currentLanguage;

	std::ifstream gameData("gameData.xml");

	std::vector<char> buffer((std::istreambuf_iterator<char>(gameData)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	document.parse<parse_no_data_nodes>(&buffer[0]);

	root_node = document.first_node("GameData");
	xml_node<>* currentLanguageNode = root_node->first_node("CurrentLanguage");
	currentLanguage = currentLanguageNode->value();

	if (currentLanguage == "English")
	{
		std::cout << "Please choose your preferred language. Current language is: " << currentLanguage << std::endl;
		std::cout << "Choices are as follows: " << std::endl;
	}
	else if (currentLanguage == "French")
	{
		std::cout << "S'il vous plaît choisissez votre langue préférée. La langue actuelle est: " << currentLanguage << std::endl;
		std::cout << "Les choix sont les suivants: " << std::endl;
	}
	else if (currentLanguage == "Spanish")
	{
		std::cout << "Por favor, elija su idioma preferido. El idioma actual es: " << currentLanguage << std::endl;
		std::cout << "Las opciones son las siguientes: " << std::endl;
	}
	else if (currentLanguage == "Irish")
	{
		std::cout << "Roghnaigh do rogha teanga. Is í an teanga reatha: " << currentLanguage << std::endl;
		std::cout << "Seo a leanas na roghanna: " << std::endl;
	}
	char userInput = '0';
	std::cout << "e: English\nf: French\ns: Spanish\ni: Irish\n";
	std::cin >> userInput;
	switch (std::tolower(userInput))
	{
	case 'e':
		currentLanguage = "English";
		break;
	case 'f':
		currentLanguage = "French";
		break;
	case 's':
		currentLanguage = "Spanish";
		break;
	case 'i' :
		currentLanguage = "Irish";
		break;
	default:
		break;
	}
	currentLanguageNode->value(currentLanguage.c_str());
	std::ofstream file;
	file.open("gameData.xml");
	file << "<?xml version='1.0' encoding='utf-8'?>";
	file << document;
	file.close();

	for (xml_node<>* languageNode = root_node->first_node("Language"); languageNode; languageNode = languageNode->next_sibling())
	{
		if (languageNode->first_attribute("name")->value() == currentLanguage)
		{
			for (xml_node<>* characterNode = languageNode->first_node("Character");	characterNode; characterNode = characterNode->next_sibling())
			{
				
				printf("%s: %s\n", characterNode->name() ,characterNode->first_attribute("name")->value());

				// Print for game info
				for (xml_node<>* characterInfo = characterNode->first_node(); characterInfo; characterInfo = characterInfo->next_sibling())
				{
					printf("\t%s: %s\n", characterInfo->name(), characterInfo->value());
					if (*characterInfo->name() == 'I' || *characterInfo->name() == 'A' || *characterInfo->name() == 'Q')
					{
						for (xml_node<>* moreInfo = characterInfo->first_node(); moreInfo; moreInfo = moreInfo->next_sibling())
						{
							printf("\t\t%s: %s\n", moreInfo->name(), moreInfo->value());
							if (*moreInfo->name() == 'S')
							{
								for (xml_node<>* questInfo = moreInfo->first_node(); questInfo; questInfo = questInfo->next_sibling())
								{
									printf("\t\t\t%s: %s\n", questInfo->name(), questInfo->first_attribute("name")->value());
									printf("\t\t\t%s: %s\n", questInfo->first_node()->name(), questInfo->first_node()->value());
								}
							}
						}
					}
					if (*characterInfo->name() == 'S')
					{
						for (xml_node<>* moreInfo = characterInfo->first_node(); moreInfo; moreInfo = moreInfo->next_sibling())
						{
							printf("\t\t\t%s: %s\n", moreInfo->name(), moreInfo->first_attribute("name")->value());
							printf("\t\t\t%s: %s\n", moreInfo->first_node()->name(), moreInfo->first_node()->value());
						}
					}
				}
			}
		}
	}
}