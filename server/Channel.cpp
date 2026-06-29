/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadeluge <nadeluge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 16:49:18 by nadeluge          #+#    #+#             */
/*   Updated: 2026/04/05 15:15:58 by nadeluge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Irc.hpp"
#include "Channel.hpp"

Channel::Channel(const std::string &name) : _name(name), _topic(""), _topicRestriction(false), _inviteNeeded(false)
{
}

Channel::~Channel()
{
}

bool Channel::isMember(int clientId) const
{
	if (this->_members.find(clientId) != this->_members.end())
		return (true);
	return (false);
}

void Channel::addMember(int clientFd)
{
	this->_members.insert(clientFd);
}

void Channel::removeMember(int clientFd)
{
	this->_members.erase(clientFd);
}

bool Channel::isOp(int clientId) const
{
	if (this->_operators.find(clientId) != this->_operators.end())
		return (true);
	return (false);
}

void Channel::addOp(int clientFd)
{
	if (isOp(clientFd))
		return;
	this->_operators.insert(clientFd);
}

void Channel::removeOp(int clientFd)
{
	this->_operators.erase(clientFd);
}

const std::set<int> &Channel::getMembers() const
{
	return (this->_members);
}

const std::string &Channel::getName() const
{
	return (this->_name);
}

const std::string &Channel::getTopic() const
{
	return (this->_topic);
}

void Channel::setTopic(const std::string &new_topic)
{
	this->_topic = new_topic;
}

int Channel::getLimit() const
{
	return (this->_limit);
}

void Channel::setLimit(int new_limit)
{
	this->_limit = new_limit;
}

void Channel::removeLimit()
{
	this->_limit = -1;
}

bool Channel::isFull() const
{
	if (this->_limit == -1)
		return (false);
	return (this->_members.size() >= static_cast<size_t>(this->_limit));
}

bool Channel::isEmpty() const
{
	if (this->_members.size() == 0)
		return (true);
	return (false);
}

void Channel::setTopicRestriction(bool hasRestriction)
{
	this->_topicRestriction = hasRestriction;
}

bool Channel::hasTopicRestriction() const
{
	return (this->_topicRestriction);
}

bool Channel::hasInvitationMode() const
{
	return (this->_inviteNeeded);
}

void Channel::setInvitationMode(bool hasInvitationMode)
{
	this->_inviteNeeded = hasInvitationMode;
}

bool Channel::isInvited(int clientFd) const
{
	return (this->_invitations.find(clientFd) != this->_invitations.end());
}

void Channel::addInvitation(int clientFd)
{
	if (isInvited(clientFd))
		return;
	this->_invitations.insert(clientFd);
}

void Channel::removeInvitation(int clientFd)
{
	this->_invitations.erase(clientFd);
}

bool Channel::hasPassword() const
{
	return (!this->_password.empty());
}

void Channel::setPassword(const std::string &password)
{
	this->_password = password;
}

void Channel::removePassword()
{
	this->_password = "";
}


bool Channel::checkPassword(const std::string &password) const
{
	if (!this->hasPassword())
		return (true);
	return (this->_password == password);
}

