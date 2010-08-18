/*
 * Copyright (C) 2010 kilabit.org
 * Author:
 *	- m.shulhan (ms@kilabit.org)
 */

#include "ResQueue.hpp"

namespace rescached {

ResQueue::ResQueue() :
	_timeout(0)
,	_udp_client(NULL)
,	_tcp_client(NULL)
,	_qstn(NULL)
,	_next(NULL)
,	_prev(NULL)
,	_last(this)
{}

ResQueue::~ResQueue()
{
	if (_udp_client) {
		free(_udp_client);
		_udp_client = NULL;
	}
	if (_tcp_client) {
		_tcp_client = NULL;
	}
	if (_qstn) {
		delete _qstn;
		_qstn = NULL;
	}
	if (_next) {
		delete _next;
		_next = NULL;
	}
	_prev = NULL;
}

/**
 * @desc	: push a new node to queue.
 * @param	:
 *	> head	: head of queue.
 *	> node	: pointer to new node.
 */
void ResQueue::PUSH(ResQueue** head, ResQueue* node)
{
	if (!(*head)) {
		(*head) = node;
	} else {
		(*head)->_last->_next	= node;
		node->_prev		= (*head)->_last;
		(*head)->_last		= node;
	}
	node->_timeout = time(NULL);
}

/**
 * @method	: ResQueue::REMOVE
 * @param	:
 *	> head	: pointer to head of the list.
 *	> node	: pointer to member of the list.
 * @desc	: remove member 'node' from the 'list'.
 */
void ResQueue::REMOVE(ResQueue** head, ResQueue* node)
{
	if (!(*head)) {
		return;
	}
	if (node == (*head)) {
		(*head) = (*head)->_next;
		if ((*head)) {
			(*head)->_last = node->_last;
			(*head)->_prev = NULL;
		}
	} else if ((*head)->_last == node) {
		(*head)->_last		= node->_prev;
		(*head)->_last->_next	= NULL;
	} else {
		node->_prev->_next	= node->_next;
		node->_next->_prev	= node->_prev;
	}

	node->_next = NULL;
	node->_prev = NULL;
	delete node;
}

} /* namespace::rescached */
