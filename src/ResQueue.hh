//
// Copyright 2009-2016 M. Shulhan (ms@kilabit.info). All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#ifndef _RESCACHED_QUEUE_HH
#define _RESCACHED_QUEUE_HH 1

#include "Socket.hh"
#include "DNSQuery.hh"

using vos::Socket;
using vos::DNSQuery;

namespace rescached {

class ResQueue {
public:
	ResQueue();
	~ResQueue();

	time_t			_timeout;
	struct sockaddr_in*	_udp_client;
	Socket*			_tcp_client;
	DNSQuery*		_qstn;
	ResQueue*		_next;
	ResQueue*		_prev;
	ResQueue*		_last;

	static void PUSH(ResQueue** head, ResQueue* node);
	static void REMOVE(ResQueue** head, ResQueue* node);
private:
	ResQueue(const ResQueue&);
	void operator=(const ResQueue&);
};

} /* namespace::rescached */

#endif
// vi: ts=8 sw=8 tw=78:
