//
// Created by jazema on 01/04/2026.
//

#ifndef STRINGHELPER_HPP
#define STRINGHELPER_HPP
#include <string>
#include <iostream>
#include <vector>

class StringHelper
{
	public:
		/**
		 * @brief Vérifie si une string commence par un préfixe donné
		 *
		 * @param reference La string complète à inspecter
		 * @param beginning Le préfixe à chercher au début de la référence
		 * @return true si la référence commence par le préfixe, sinon false
		 *
		 * @note La comparaison est sensible aux majuscules
		 * @note Retourne faux si jamais le préfix est plus long que la référence
		 */
		static bool startsWith(const std::string &reference, const std::string &beginning);
		static void	printCentered(std::string str, int width, char c);


		/**
		 * @brief Remplace toutes les occurences de caracteres specifiques dans une string
		 *
		 * Iterates through the given reference string and replaces any character
		 * found in `charsToReplace` with the specified replacement character.
		 *
		 * @param reference La string d'input
		 * @param matchChars Une string contenant tous les caracteres a remplacer.
		 * @param replacement Le caractere de remplacement.
		 */
		static void replaceChars(std::string &reference, const std::string &matchChars, char replacement);

		static std::string join(const std::vector<std::string> &strings, const std::string &delimiter);

		static std::vector<std::string> split(const std::string &string, const std::string &delimiter);
};

#endif
