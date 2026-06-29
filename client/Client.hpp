/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadeluge <nadeluge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:07:06 by elaudrez          #+#    #+#             */
/*   Updated: 2026/04/05 15:15:41 by nadeluge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <string>

# include <netinet/in.h>

#include "UserModes.hpp"

class Client
{
	private:
		struct AuthenticationData
		{
			std::string password;
			bool passReceived;
			bool passValid;
			bool nickSet;
			bool userSet;

			AuthenticationData(bool pr = false, bool pv = false, bool ns = false, bool us = false) : passReceived(pr), passValid(pv), nickSet(ns), userSet(us) {}
		};
		std::string			_username;
		std::string			_nickname;
		std::string			_realname;
		std::string			_hostname; // =IP -> a resolve cote serveur
		AuthenticationData	_authData;
		UserModes			_modes;

		int 		_client_fd;
		sockaddr_in	_client_addr;
		socklen_t	_client_addr_len; //unsigned int, represente taille des structures d'adresses
		char		_client_ip[INET_ADDRSTRLEN]; // Tableau pour stocker address IP en texte

		std::string _inputBuffer;
	public:
		Client(int clientFd, const sockaddr_in &address, socklen_t &addressLen);

		void		initClient();

		int			getClientFd() const;

		/* ************************************************************************** */
		/*                                  GET&&SET                                  */
		/* ************************************************************************** */
		const std::string	&getUsername() const;
		void				setUsername(const std::string &username);

		const std::string	&getNickname() const;
		void				setNickname(const std::string &nick);

		const std::string	&getRealname() const;
		void				setRealname(const std::string &realname);

		const std::string	&getHostname() const;
		void				setHostname(const std::string &hostname);

		bool				isRegistered() const;


		/**
		 * Envoie un message IRC au client par sa socket.
		 * Le message ne DOIT pas être proprement terminé avec "\r\n" comme demandé par la RFC 2812.
		 *
		 * @param message Le message IRC complet à envoyer (dont le CRLF : \\r\\n).
		 */
		void		sendMessage(const std::string &message) const;

		std::string getIp() const;
		int			getPort() const;

		// Fonctions relatives à l'inputBuffer (le buffer de lecture pour pouvoir recevoir les commandes en plusieur fois

		void		appendBuffer(const std::string &);
		std::string &getInputBuffer();

		std::string	buildPrefix() const;

		bool		isPasswordValid() const;
		bool		isNickSet() const;
		bool		isUserSet() const;
		void		passValid();
		void		passReceived();
		void		nickSet();
		void		userSet();

		UserModes &getModes();
};

#endif
