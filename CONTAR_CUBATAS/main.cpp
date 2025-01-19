#include <iostream>
#include <fstream>

//#include <map>

#include "Cubata.h"

//idea: pasar nombres personas por argumentos
// programa *.txt nombre1 {nombres...}
int main(int argc, char *argv[]) {

	/*******************************************************************/
	//ERROR and arguments
	if (argc != 2) {
		std::cerr << "Error: Too few arguments!" << std::endl;
		return EXIT_FAILURE;
	}

	// std::string nombresvalidos[argc-2];
	// for (int i = 0; i < argc-2; i++) {
	// 	nombresvalidos[i] = argv[i+2];
	// }

	std::ifstream in_text;
	in_text.open(argv[1]);

	if (!in_text.is_open()) {
		std::cerr << "Error opening file" << std::endl;
	}
	/*******************************************************************/

	// std::string personas[argc - 2];
	// std::map<std::string, int> map_cubata;
	//
	// for (std::string line; std::getline(in_text, line);) {
	// 	map_cubata[line]++;
	// }
	//
	// for (auto it:map_cubata) {
	// 	std::cout << it.first << " " << it.second << std::endl;
	// }

	//IMPLEMENTACION CON CLASE CUBATAS

	Cubatas cubatas;
	cubatas.leer_personas(in_text);
	in_text.close();

	 std::ofstream out_text;
	 out_text.open("output.txt");
	 out_text << cubatas;
	 out_text.close();

	std::cout << cubatas << std::endl;



	return 0;
}
