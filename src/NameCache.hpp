/*
 * Copyright (C) 2010 kilabit.org
 * Author:
 *	- m.shulhan (ms@kilabit.org)
 */

#ifndef _RESCACHED_NAME_CACHE_HPP
#define	_RESCACHED_NAME_CACHE_HPP	1

#include "Reader.hpp"
#include "Writer.hpp"
#include "NCR_Tree.hpp"
#include "NCR_List.hpp"

using vos::Record;
using vos::RecordMD;
using vos::Reader;
using vos::Writer;

#define	CACHET_IDX_SIZE		43	/* size of bucket tree, 0-Z + others */
#define	CACHET_IDX_FIRST	'0'

namespace rescached {

struct NCR_Bucket {
	NCR_Tree* _v;
};

class NameCache {
public:
	NameCache();
	~NameCache();

	void lock();
	void unlock();

	int raw_to_ncrecord(Record* raw, NCR** ncr);
	int load(const char* fdata, const long int max);

	int ncrecord_to_record(const NCR* ncr, Record* row);
	int save(const char* fdata);

	int get_answer_from_cache(NCR_Tree** node, Buffer* name);
	int get_answer_from_cache_r(NCR_Tree** node, Buffer* name);

	void clean_by_threshold(const long int thr);

	int insert(NCR* record);
	int insert_raw(const int type, const Buffer* name
			, const Buffer* question, const Buffer* answer);
	int insert_raw_r(const int type, const Buffer* name
			, const Buffer* question, const Buffer* answer);

	void increase_stat_and_rebuild_r(NCR_List *list);

	void prune();
	void dump();
	void dump_r();

	long int	_n_cache;
	pthread_mutex_t	_lock;
	NCR_Bucket*	_buckets;
	NCR_List*	_cachel;
private:
	NameCache(const NameCache&);
	void operator=(const NameCache&);
};

} /* namespace::rescached */

#endif
