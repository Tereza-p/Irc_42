/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nardis <nardis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:08:55 by elaudrez          #+#    #+#             */
/*   Updated: 2026/04/03 12:26:35 by nardis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>

#include "src/server/Server.hpp"

// Color definitions
std::string red("\033[0;31m");
std::string green("\033[0;32m");
std::string yellow("\033[0;33m");
std::string blue("\033[0;34m");
std::string purple("\033[0;35m");
std::string reset("\033[0m");

int main(int argc, char **argv)
{
	long		port;
	std::string	password;

	if (argc != 3)
	{
		std::cerr << "Usage: ./ft_irc <port> <password>" << std::endl;
		return -1;
	}
	port = std::atol(argv[1]);
	password.assign(argv[2]);
	Server server;

	try
	{

		server.createSocket();
		server.bindSocket(port);
		server.getServerData().setServerPassword(password);

		server.run();

		server.shutdown();
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error : " << e.what() << std::endl;
		return (-1);
	}
	return (0);
}
