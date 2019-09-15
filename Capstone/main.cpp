/*
	
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "SQMData.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Utilities.h"
#include "GraphWindow.h"
#include "SQMGraph.h"
#include "TestSFML.h"

using namespace std;
using namespace sf;

char pause;

int main(int argc, char *argv[])
{
	/*
	Instructions to change input and output file:

	create an ifstream object with the file path and name
	ex:
		//file inside Capstone folder with source
		ifstream data("filename.txt")
		//file on machine. make sure to use \\ to escape the \(backslash). *NOTE* Drive letter not always C
		ifstream data("C:\\my\\file\\path\\filename.txt")
	add file to the dataCollection vector
	ex:
		//reference it as a pointer using &
		dataCollection.push_back(&data)
	*/

    //2 different test data files
    //ifstream inData1("2018_3_17.txt");
    ifstream inData2("SQMReadings.txt");
    //vector of file streams
    vector<ifstream*> dataCollection;
	
    //load the files into the vector
   // dataCollection.push_back(&inData1);
    dataCollection.push_back(&inData2);

    //output the data
    SQMData SQM(dataCollection);

	SQM.OutputData("C:\\Users\\Zack\\Desktop\\SQMData.csv");

	std::cout << "data has been outputed: press any button to continue." << std::endl;
	std::cin >> pause;

	SQMGraph graph(&SQM);

	while (graph.isOpen()) {
		Event event;
		while (graph.pollEvent(&event))
		{
			if (event.type == Event::Closed) {
				graph.close();
			}
		}
		graph.update(event);
	}
	
    return 0;
}
