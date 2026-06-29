/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadeluge <nadeluge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 16:43:16 by nadeluge          #+#    #+#             */
/*   Updated: 2026/04/04 17:49:29 by nadeluge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <set>
#include <string>

class Channel
{
	private:
		// Channels name = strings (beginning with '&', '#', '+' or '!') with len of 50 char
		// Shall not contain any space / "^G" / ',' -> see 2.3.1
		std::string		_name;
		std::string 	_topic;
		std::set<int>	_operators; //liste des operateurs
		std::set<int>	_members; //list de tous les clients
		std::set<int>	_invitations;

		// Modes
		int				_limit; // Limite du nombre de membres (-1 = pas de limite)
		bool			_topicRestriction;
		bool			_inviteNeeded;
		std::string		_password;
	public:
		Channel(const std::string &name);
		~Channel();

		/**
		 * @brief Permet de savoir si un client fait partie du channel
		 *
		 * @param clientId L'id du client à chercher
		 * @return true si le client fait partie des membres, sinon false
		 */
		bool				isMember(int clientId) const;

		/**
		 * @brief Permet d'ajouter un client aux membres du channel
		 *
		 * @param clientFd L'id du client a ajouter au channel
		 */
		void				addMember(int clientFd);

		/**
		 * @brief Permet de retirer un client des membres du channel
		 *
		 * @param clientFd L'id du client a retirer du channel
		 */
		void				removeMember(int clientFd);

		/**
		 * @brief Permet de savoir si un client est operateur sur le channel
		 *
		 * @param clientId L'id du client à chercher
		 * @return true si le client est operateur, sinon false
		 */
		bool				isOp(int clientId) const;
		void				addOp(int clientFd);
		void				removeOp(int clientFd);

		const std::set<int> &getMembers() const;
		const std::string	&getName() const;

		const std::string 	&getTopic() const;
		void 				setTopic(const std::string& new_topic);

		int 				getLimit() const;
		void 				setLimit(int new_limit);
		void				removeLimit();
		bool				isFull() const;
		bool				isEmpty() const;

		/**
		 * @brief Permet de savoir si jamais le channel restreint l'utilisation de TOPIC seulement aux operateurs
		 *
		 * @return true Si la commande TOPIC n'est executable que par les op, sinon false
		 */
		bool				hasTopicRestriction() const;
		void				setTopicRestriction(bool hasRestriction);

		bool				hasInvitationMode() const;
		void				setInvitationMode(bool hasInvitationMode);

		bool				isInvited(int clientFd) const;
		void				addInvitation(int clientFd);
		void				removeInvitation(int clientFd);

		bool				hasPassword() const;
		void				setPassword(const std::string &password);
		void				removePassword();
		bool				checkPassword(const std::string &password) const;
};

#endif
