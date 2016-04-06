/************************************************************
**
** file:	btreeassociative.cpp
** author:	Andreas Steffens
** license:	GPL v2
**
** description:
**
** This file contains code for the b-tree framework's
** key sort interface class.
**
************************************************************/

#ifndef	BTREEASSOCIATIVE_CPP
#define	BTREEASSOCIATIVE_CPP

#include "btreeassociative.h"

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::CBTreeAssociative
	(
		_t_datalayerproperties &rDataLayerProperties, 
		const bayerTreeCacheDescription_t *psCacheDescription, 
		_t_subnodeiter nNodeSize
	)
	:	CBTreeBaseDefaults <CBTreeKeySortPos<_t_sizetype, _t_key>, _t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>
	(
		rDataLayerProperties, 
		psCacheDescription, 
		nNodeSize
	)
{
#if defined (_DEBUG)
	m_pbShortLiveKeyInUse = new bool (false);

	BTREE_ASSERT (m_pbShortLiveKeyInUse != NULL, "CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::CBTreeAssociative (_t_datalayerproperties &, bayerTreeCacheDescription_t *, _t_subnodeiter): insufficient memory!");
#endif

	m_pRemoveKey = NULL;
	m_pTempRemoveKey = NULL;
	m_pInstancesNewKey = NULL;
	m_pTempFindFirstKeyNewKey = NULL;
	m_pAddToNodeKey = NULL;
	m_pGetNewKey = NULL;

	m_ppShortLiveKey = new _t_key *;

	BTREE_ASSERT (m_ppShortLiveKey != NULL, "CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::CBTreeAssociative (_t_datalayerproperties &, bayerTreeCacheDescription_t *, _t_subnodeiter) (m_ppShortLiveKey): insufficient memory!");

	*m_ppShortLiveKey = NULL;

	m_ppTempFindFirstKeyKey = new _t_key *;

	BTREE_ASSERT (m_ppTempFindFirstKeyKey != NULL, "CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::CBTreeAssociative (_t_datalayerproperties &, bayerTreeCacheDescription_t *, _t_subnodeiter) (m_ppTempFindFirstKeyKey): insufficient memory!");

	*m_ppTempFindFirstKeyKey = NULL;
	
	// allocate all variable size temporary buffers
	vbufferAllocate (m_ppShortLiveKey);
	vbufferAllocate (m_ppTempFindFirstKeyKey);

	vbufferAllocate (&m_pRemoveKey);
	vbufferAllocate (&m_pTempRemoveKey);
	vbufferAllocate (&m_pInstancesNewKey);
	vbufferAllocate (&m_pTempFindFirstKeyNewKey);
	vbufferAllocate (&m_pAddToNodeKey);
	vbufferAllocate (&m_pGetNewKey);
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::CBTreeAssociative (const CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer> &rBT, bool bAssign)
	:	CBTreeBaseDefaults <CBTreeKeySortPos<_t_sizetype, _t_key>, _t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>
	(
		dynamic_cast <const CBTreeBaseDefaults <CBTreeKeySortPos<_t_sizetype, _t_key>, _t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer> &> (rBT)
	)
{
#if defined (_DEBUG)
	m_pbShortLiveKeyInUse = new bool (false);

	BTREE_ASSERT (m_pbShortLiveKeyInUse != NULL, "CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::CBTreeAssociative (CBTreeAssociative<> &): insufficient memory!");
#endif

	m_pRemoveKey = NULL;
	m_pTempRemoveKey = NULL;
	m_pInstancesNewKey = NULL;
	m_pTempFindFirstKeyNewKey = NULL;
	m_pAddToNodeKey = NULL;
	m_pGetNewKey = NULL;
	
	m_ppShortLiveKey = new _t_key *;

	BTREE_ASSERT (m_ppShortLiveKey != NULL, "CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::CBTreeAssociative (CBTreeAssociative<> &) (m_ppShortLiveKey): insufficient memory!");

	*m_ppShortLiveKey = NULL;
	
	m_ppTempFindFirstKeyKey = new _t_key *;

	BTREE_ASSERT (m_ppTempFindFirstKeyKey != NULL, "CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::CBTreeAssociative (CBTreeAssociative<> &) (m_ppTempFindFirstKeyKey): insufficient memory!");

	*m_ppTempFindFirstKeyKey = NULL;
	
	// allocate all variable size temporary buffers
	vbufferAllocate (m_ppShortLiveKey);
	vbufferAllocate (m_ppTempFindFirstKeyKey);
	
	vbufferAllocate (&m_pRemoveKey);
	vbufferAllocate (&m_pTempRemoveKey);
	vbufferAllocate (&m_pInstancesNewKey);
	vbufferAllocate (&m_pTempFindFirstKeyNewKey);
	vbufferAllocate (&m_pAddToNodeKey);
	vbufferAllocate (&m_pGetNewKey);

	if (bAssign)
	{
		this->_assign (rBT);
	}
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::~CBTreeAssociative ()
{
	vbufferDeallocate (m_ppShortLiveKey);
	vbufferDeallocate (m_ppTempFindFirstKeyKey);
	vbufferDeallocate (&m_pRemoveKey);
	vbufferDeallocate (&m_pTempRemoveKey);
	vbufferDeallocate (&m_pInstancesNewKey);
	vbufferDeallocate (&m_pTempFindFirstKeyNewKey);
	vbufferDeallocate (&m_pAddToNodeKey);
	vbufferDeallocate (&m_pGetNewKey);

	delete m_ppShortLiveKey;
	delete m_ppTempFindFirstKeyKey;

#if defined (_DEBUG)
	delete m_pbShortLiveKeyInUse;
#endif
}

/*

insert - insert data

rData		- data set to be added

This method inserts one entry.

If the method was successful, then the return value is an iterator reflecting the position of
the newly added entry, otherwise the method asserts and throws an ::std::run_time_error expection.

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
typename CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::iterator
	CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::insert
	(
		const _t_data &rData
	)
{
	_t_sizetype								nRetval;
	iterator_state_t						sIterState;
	CBTreeKeySortPos<_t_sizetype, _t_key>	sPos;
	
	this->create_root ();

	// convert object to a position structure for internal use
	//
	// nInstance is left to any (~0), since it will be ignored but 
	// has to be set to not turn up on any valgrind report and this
	// object will be appended to any set of entries that share
	// the same key
	sPos.nInstance = ~0;
	sPos.pKey = extract_key (m_pAddToNodeKey, rData);

	sIterState.nAssociatedPos = 0;

	nRetval = this->add_to_node (sPos, rData, this->m_nRootNode, 0, sIterState.nNode, sIterState.nSubPos, &sIterState.nAssociatedPos);

	BTREE_ASSERT (nRetval == 1, "CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::insert (const _t_data &): Failed to create new entry!");

	iterator		sRetval (this, sIterState.nAssociatedPos, &sIterState, this->get_time_stamp (), false);

	return (sRetval);
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
template <class _t_iterator>
void CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::insert (_t_iterator sItFirst, _t_iterator sItLast)
{
	bool			bSelfReverse;
	_t_iterator		sIt;
	const_iterator	*psItFirst;
	const_iterator	*psItLast;

	if (sItFirst == sItLast)
	{
		return;
	}

	if (this->test_self_reference_of_iterator_to_this (sItFirst, sItLast, bSelfReverse, &psItFirst, &psItLast))
	{
		const_iterator						sIt = (const_iterator) (*psItLast);
		const_iterator						sItLower;
		const_iterator						sItUpper;
		_t_data								sData;
		_t_key								sKey;
		_t_key								sPrevKey;
		bool								bBounce;
		_t_key								sFirstKey;
		_t_key								sLastKey;
		typename ::std::list<_t_data>		sList;

		sData = *((const_iterator) (*psItFirst));

		this->extract_key (&sFirstKey, sData);

		(*psItLast)--;

		sData = *((const_iterator) (*psItLast));

		this->extract_key (&sLastKey, sData);

		(*psItLast)++;

		while (sIt != ((const_iterator) (*psItFirst)))
		{
			sIt--;

			sData = *sIt;

			this->extract_key (&sKey, sData);

			sItLower = this->lower_bound (sKey);
			sItUpper = this->upper_bound (sKey);

			if (this->comp (sKey, sFirstKey) == 0)
			{
				sItLower = ((const_iterator) (*psItFirst));
			}

			if (this->comp (sKey, sLastKey) == 0)
			{
				sItUpper = ((const_iterator) (*psItLast));
			}

			sList.clear ();

			sList.template insert <const_iterator> (sList.begin (), sItLower, sItUpper);

			CBTreeAssociative_t::insert<typename ::std::list<_t_data>::const_iterator> (sList.cbegin (), sList.cend ());

			this->get_prev_key (sKey, sPrevKey, bBounce);

			if (bBounce)
			{
				break;
			}

			sKey = sPrevKey;

			sIt = sItLower;
		}

		delete (psItFirst);
		delete (psItLast);
	}
	else
	{
#if defined (_DEBUG)

		uint32_t	nDebug = 0;

#endif

		for (sIt = sItFirst; sIt != sItLast; sIt++)
		{
#if defined (_DEBUG)

			_t_sizetype		nSize = this->size ();

#endif

			CBTreeAssociative_t::insert ((const _t_data &) *sIt);

#if defined (_DEBUG)

			nDebug++;

			BTREE_ASSERT ((nSize + 1) == this->size (), "CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::insert<_t_iterator>: unexpected container size!");

#endif
		}
	}
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
typename CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::iterator
	CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::erase
	(
		typename CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::const_iterator sCIterPos
	)
{
	typedef typename CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::iterator		iter_t;

	this->erase_via_reference (sCIterPos, false);

	return (iter_t (this, sCIterPos.get_pos (), false));
}

/*

erase - removes all entries using the same key

key		- specifies the key which is extracted from the parameter

Every entry using the same as the key extracted from the parameter is removed.

The method returns number of removed entries.

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
_t_sizetype CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::erase (const _t_key &rKey)
{
		CBTreeKeySortPos<_t_sizetype, _t_key>	sPos;
	_t_sizetype								nRetval = (_t_sizetype) 0;

	if (this->m_pData != NULL)
	{
		// convert object to a position structure for internal use
		sPos.pKey = m_pRemoveKey;
		*m_pRemoveKey = rKey;

		// nInstance is left to any (~0), since any entry using the same
		// key will be removed
		sPos.nInstance = ~0;

		// for as long as any instnce using the same key is left ...
		while (count (rKey) > (_t_sizetype) 0)
		{
			// ... continue removing those entries
			nRetval += this->remove_from_node (sPos, this->m_nRootNode, 0);
		}
	}

	return (nRetval);
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
typename CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::iterator
	CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::erase
	(
		typename CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::const_iterator sCIterFirst, 
		typename CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::const_iterator sCIterLast
	)
{
	_t_sizetype		nDiff = ::std::distance<const_iterator> (sCIterFirst, sCIterLast);
	_t_sizetype		i;

	for (i = 0; i < nDiff; i++)
	{
		this->erase_via_reference (sCIterFirst);
	}

	return (iterator (this, sCIterFirst.get_pos (), false));
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
typename CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::iterator
CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::find
	(
		const _t_key &rKey
	)
{
	iterator_state_t		sIterState;
	
	if (CBTreeAssociative::_find (rKey, sIterState.nNode, sIterState.nSubPos, sIterState.nAssociatedPos))
	{
		return (iterator (this, sIterState.nAssociatedPos, (void *) &sIterState, this->get_time_stamp (), false));
	}
	else
	{
		return (this->end ());
	}
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
typename CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::const_iterator
	CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::find
	(
		const _t_key &rKey
	) const
{
	iterator_state_t		sIterState;
	
	if (CBTreeAssociative::_find (rKey, sIterState.nNode, sIterState.nSubPos, sIterState.nAssociatedPos))
	{
		return (const_iterator (this, sIterState.nAssociatedPos, (void *) &sIterState, this->get_time_stamp (), false));
	}
	else
	{
		return (this->cend ());
	}
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
typename CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::iterator
	CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::lower_bound
	(
		const _t_key &rKey
	)
{
	iterator_state_t		sIterState;
	
	CBTreeAssociative_t::_lower_bound (rKey, sIterState.nNode, sIterState.nSubPos, sIterState.nAssociatedPos);
	
	return (iterator (this, sIterState.nAssociatedPos, (void *) &sIterState, this->get_time_stamp (), false));
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
typename CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::const_iterator
	CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::lower_bound
	(
		const _t_key &rKey
	) const
{
	iterator_state_t		sIterState;
	
	CBTreeAssociative_t::_lower_bound (rKey, sIterState.nNode, sIterState.nSubPos, sIterState.nAssociatedPos);
	
	return (const_iterator (this, sIterState.nAssociatedPos, (void *) &sIterState, this->get_time_stamp (), false));
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
typename CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::iterator
	CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::upper_bound
	(
		const _t_key &rKey
	)
{
	iterator_state_t		sIterState;
	
	if (CBTreeAssociative_t::_upper_bound (rKey, sIterState.nNode, sIterState.nSubPos, sIterState.nAssociatedPos))
	{
		return (iterator (this, sIterState.nAssociatedPos, false));
	}
	else
	{
		return (iterator (this, sIterState.nAssociatedPos, (void *) &sIterState, this->get_time_stamp (), false));
	}
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
typename CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::const_iterator
	CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::upper_bound
	(
		const _t_key &rKey
	) const
{
	iterator_state_t		sIterState;
	
	if (CBTreeAssociative_t::_upper_bound (rKey, sIterState.nNode, sIterState.nSubPos, sIterState.nAssociatedPos))
	{
		return (const_iterator (this, sIterState.nAssociatedPos, false));
	}
	else
	{
		return (const_iterator (this, sIterState.nAssociatedPos, (void *) &sIterState, this->get_time_stamp (), false));
	}
}

/*

get_next_key - get next key

rKey		- specifies key prior to key to be returned
rNextKey	- specifies reference to return key
bBounce		- specifies reference to bounce return value

This method searches for the next key value relative to the key value rKey. If the method was
successful then bBounce is false and rNextKey contains the next key value relative to rKey, otherwise
bBounce is true and rNextKey contains an undefined value.

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
void CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::get_next_key (const _t_key &rKey, _t_key &rNextKey, bool &bBounce) const
{
	_t_nodeiter					nNode, nNextNode;
	_t_subnodeiter				nSub, nNextSub;
	
	bBounce = false;
	
	// if data not present ...
	if (this->empty ())
	{
		// ... then flag bounce since search for not successful and return
		bBounce = true;
		
		return;
	}
	
	nNode = this->m_nRootNode;
	
	while (1)
	{
		nSub = this->get_firstSubPos (nNode, rKey, true);
		
		if (nSub < this->get_data_count (nNode))
		{
			this->extract_key (&rNextKey, nNode, nSub);

			if (this->is_leaf (nNode))
			{
				while (this->comp (rKey, rNextKey) == 0)
				{
					this->move_next (nNode, nSub, nNextNode, nNextSub, bBounce);

					if (bBounce)
					{
						return;
					}

					this->extract_key (&rNextKey, nNextNode, nNextSub);

					nNode = nNextNode;
					nSub = nNextSub;
				}

				break;
			}
			else
			{
				if (this->comp (rKey, rNextKey) == 0)
				{
					this->move_next (nNode, nSub, nNextNode, nNextSub, bBounce);

					if (bBounce)
					{
						return;
					}

					nNode = nNextNode;
					nSub = nNextSub;
				}
				else
				{
					nNode = *(this->get_sub_node (nNode, nSub));
				}
			}
		}
		else
		{
			nSub--;

			this->move_next (nNode, nSub , nNextNode, nNextSub, bBounce);

			if (bBounce)
			{
				return;
			}

			this->extract_key (&rNextKey, nNode, nSub);

			nNode = nNextNode;
			nSub = nNextSub;

			if (this->comp (rKey, rNextKey) > 0)
			{
				this->extract_key (&rNextKey, nNextNode, nNextSub);

				if (this->comp (rKey, rNextKey) < 0)
				{
					return;
				}
			}
		}
	}
}

/*

get_prev_key - get previous key

rKey		- specifies key next to key to be returned
rNextKey	- specifies reference to return key
bBounce		- specifies reference to bounce return value

This method searches for the previous key value relative to the key value rKey. If the method was
successful then bBounce is false and rNextKey contains the previous key value relative to rKey, otherwise
bBounce is true and rNextKey contains an undefined value.

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
void CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::get_prev_key (const _t_key &rKey, _t_key &rPrevKey, bool &bBounce) const
{
	_t_nodeiter					nNode, nPrevNode;
	_t_subnodeiter				nSub, nPrevSub;
	
	bBounce = false;
	
	// if data not present ...
	if (this->empty ())
	{
		// ... then flag bounce since search for not successful and return
		bBounce = true;
		
		return;
	}

	if (this->find_oneKey (rKey, nNode, nSub))
	{
		this->find_firstKey (nNode, nSub, nPrevNode, nPrevSub);

		nNode = nPrevNode;
		nSub = nPrevSub;
	}

	this->move_prev (nNode, nSub, nPrevNode, nPrevSub, bBounce);
				
	if (bBounce)
	{
		return;
	}
	
	this->extract_key (&rPrevKey, nPrevNode, nPrevSub);
}

/*

count - get number of instances of one key

key			- contains on object specifying the key which is to be extracted from this parameter

This method determines the number entries containing the same key as the object of parameter key.

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
_t_sizetype CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::count (const _t_key &rKey) const
{
	_t_sizetype				nRetval = (_t_sizetype) 0;
	_t_nodeiter				nNode = this->m_nRootNode, nNodeSeen;
	_t_subnodeiter			nSubPos, nSubPosSeen;
	bool					bBounce;

	// if no data is present ...
	if (this->empty ())
	{
		// ... then return
		return (nRetval);
	}

	// if not a single entry can be found using the same key as pkey is pointing at ...
	if (!find_oneKey (rKey, nNode, nSubPos))
	{
		// ... then return
		return (nRetval);
	}

	// find first node / sub-node position where the key in question has been 'seen'
	find_firstKey (nNode, nSubPos, nNodeSeen, nSubPosSeen);

	while (1)
	{
		// increment return value on any entry with a matching key
		nRetval++;

		// determine next position in b-tree
		this->move_next (nNodeSeen, nSubPosSeen, nNode, nSubPos, bBounce);

		// if the last seen position also was the final entry ...
		if (bBounce)
		{
			// ... then abort
			break;
		}

		// extract key of next entry
		extract_key (m_pInstancesNewKey, nNode, nSubPos);

		// if key is no longer matching ...
		if (this->comp (*m_pInstancesNewKey, rKey) != 0)
		{
			// ... then abort
			break;
		}

		// make next position the last seen position
		nNodeSeen = nNode;
		nSubPosSeen = nSubPos;
	}

	return (nRetval);
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
typename CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::key_compare CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::key_comp () const
{
	key_compare		sRetval;

	sRetval.pThis = dynamic_cast <CBTreeAssociativeIf_t *> ((CBTreeAssociative_t *) this);

	return (sRetval);
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
typename CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::value_compare CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::value_comp () const
{
	value_compare		sRetval;

	sRetval.pThis = dynamic_cast <CBTreeAssociativeIf_t *> ((CBTreeAssociative_t *) this);

	return (sRetval);
}
	
/*

serialize - serialize

The serialize method reads out data items from position nFrom to position nTo - 1 and writes the
return data into an array pData is poiting at. It is assumed by this method that the array is large enough
to contain all data that will potentially be written into it, otherwise memory regions not associated with
pData get overwritten.

nStart		- specifies the initial position to be serialized
nLen		- specifies number of entries to be serialized
pData		- pointer to array where result will be copied to

This method returns the number of items that have been written to the array pData is pointing at.

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
_t_sizetype CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::serialize (const _t_sizetype nStart, const _t_sizetype nLen, _t_data *pData) const
{
	CBTreeKeySortPos <_t_sizetype, _t_key>	sPos;
	_t_key									sKey;
	_t_data									sData;

	/*
	**	The actual serialize process is done by CBTreeBaseDefaults::serialize.
	**	All this method does is to convert nFrom and nTo into the template parameter _ti_pos (CBTreeKeySortPos <_t_sizetype, _t_key>)
	**	and nLen. This has to be done, since CBTreeBaseDefaults::serialize has no concept of what an _t_sizetype in terms of a position is.
	*/

	get_at (nStart, sData);

	extract_key (&sKey, sData);

	// if initial position is requested or the key is unique ...
	if ((nStart == 0) || (count (sKey) == 1))
	{
		// ... then initial instance of key is implied
		sPos.nInstance = 0;
	}
	else
	{
		// ... otherwise determine instance
		_t_sizetype		nInit = get_init_pos_of_key (sKey);

		sPos.nInstance = nStart - nInit;
	}

	sPos.pKey = &sKey;

	return (CBTreeBaseDefaults<CBTreeKeySortPos <_t_sizetype, _t_key>, _t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::serialize (sPos, nLen, pData));
}

/*

operator= - assignment operator overload

rBT		- is a reference to a b-tree that will have its content be assigned to this instance

The result is a reference to this instance.

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer> &CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::operator=
	(const CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer> &rBT)
{
	// if this is not the same instance as the referenced b-tree (rBT) ...
	if (this != &rBT)
	{
		CBTreeBase_t		&rBaseThis = dynamic_cast<CBTreeBase_t &> (*this);
		const CBTreeBase_t	&rBaseBT = dynamic_cast<const CBTreeBase_t &> (rBT);
		
		rBaseThis = rBaseBT;
	}

	return (*this);
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
bool CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::operator== (const CBTreeAssociativeIf<_t_data, _t_key, _t_sizetype> &rRhs) const
{
	if (this == &rRhs)
	{
		true;
	}

	if (this->size () != rRhs.size ())
	{
		return (false);
	}

	const uint32_t		nLocalVectorSize = 32;		// used as number of bits in the local vector
	const uint32_t		nLoaclVectorShift = 5;
	const uint32_t		nLoaclVectorMask = 0x1F;
	uint32_t			uLocalVector;
	uint32_t			*pLocalVector;
	_t_data				sData;
	_t_key				sKey;

	const_iterator		sCIterThis = this->cbegin ();
	const_iterator		sCIterThisEnd = this->cend ();

	const_iterator		sCIterRhs = rRhs.cbegin ();

	while (sCIterThis < sCIterThisEnd)
	{
		sData = *sCIterThis;

		this->extract_key (&sKey, sData);

		const_iterator		sCIterThisKeyLower = this->lower_bound (sKey);
		const_iterator		sCIterThisKeyUpper = this->upper_bound (sKey);
		const_iterator		sCIter;
		const_iterator		sCIterRhsKeyLower = rRhs.lower_bound (sKey);
		const_iterator		sCIterRhsKeyUpper = rRhs.upper_bound (sKey);
		const_iterator		sCIterRhs;
		_t_sizetype			nCountThis;
		_t_sizetype			nCountRhs;
		_t_sizetype			i;
		_t_data				sDataRhs;
		_t_key				sKeyRhs;

		nCountThis = this->count (sKey);

		nCountRhs = rRhs.count (sKey);

		if (nCountThis != nCountRhs)
		{
			return (false);
		}

		if (nCountRhs < nLocalVectorSize)
		{
			uLocalVector = 0;

			pLocalVector = &uLocalVector;
		}
		else
		{
			pLocalVector = (uint32_t *) calloc ((size_t) ((nCountRhs + 1) / nLocalVectorSize), sizeof (*pLocalVector));
		}

		for (sCIter = sCIterThisKeyLower, i = 0; sCIter < sCIterThisKeyUpper; sCIter++, i++)
		{
			sData = *sCIter;

			for (sCIterRhs = sCIterRhsKeyLower; sCIterRhs < sCIterRhsKeyUpper; sCIterRhs++)
			{
				sDataRhs = *sCIterRhs;

				this->extract_key (&sKeyRhs, sDataRhs);

				if (this->comp (sKey, sKeyRhs) == 0)
				{
					if ((pLocalVector[i >> nLoaclVectorShift] &= 1 << (i & nLoaclVectorMask)) == 0)
					{
						pLocalVector[i >> nLoaclVectorShift] |= 1 << (i & nLoaclVectorMask);

						if (sCIterRhs == sCIterRhsKeyLower)
						{
							sCIterRhsKeyLower++;

							break;
						}
					}
				}
			}

			if (sCIterRhs >= sCIterRhsKeyUpper)
			{
				break;
			}
		}

		if (nCountRhs >= nLocalVectorSize)
		{
			free ((void *) pLocalVector);
		}

		if (sCIter < sCIterThisKeyUpper)
		{
			return (false);
		}

		sCIterThis = sCIterThisKeyUpper;
	}

	return (true);
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
bool CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::operator!= (const CBTreeAssociativeIf<_t_data, _t_key, _t_sizetype> &rRhs) const
{
	return (!(*this == rRhs));
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
void CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::_assign
	(const CBTreeIf<_t_data, _t_sizetype> &rContainer)
{
	// remove all data from target container
	this->clear ();

	/*
	**	Although a b-tree guarantees that data is stored balanced; this happens under the assumption that 
	**	data entries are stored and removed in random order. In case data is stored or removed in order, the
	**	tree will become partially unblanced. To prevent this the data is not copied in order, but in a
	**	skewed fashion. The skew width is determined by the target tree's maximum node size (t * 2) and target
	**	tree's future depth (based on the source tree's size) combined, since that ensures an equal distribution
	**	of all data throughout the entire target tree.
	*/
	
	// determine initial part of skew width
	const CBTreeAssociative_t&		rAssociative = dynamic_cast<const CBTreeAssociative_t &> (rContainer);
	_t_sizetype						nSkewWidth = this->m_nNodeSize * 2;
	_t_sizetype						nEntries = 1;
	_t_sizetype						i;
	_t_sizetype						j;
	_t_data							sData;

	// combine skew width with eventual target tree depth (log t of n, while t is node size and n is tree size)
	for (nSkewWidth--; nEntries <= rAssociative.size (); nSkewWidth++)
	{
		// on average every new layer allows for t times current tree size more entries
		nEntries *= this->m_nNodeSize;
	}

	// copy data using skew width
	for (i = 0; i < nSkewWidth; i++)
	{
		for (j = i; j < rAssociative.size (); j += nSkewWidth)
		{
			rAssociative.get_at (j, sData);

			this->insert (sData);
		}
	}
}

/*

get_at - get at

nPos		- specifies the the linear position
rData		- reference to where the returned entry is put


This method returns true is the access was successful, otherwise false.

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
bool CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::get_at (const _t_sizetype nPos, _t_data &rData) const
{
	bool			retval = false;
	_t_nodeiter		nNode;
	_t_subnodeiter	nSubPos;

	// if data layer is present ...
	if (this->m_pData != NULL)
	{
		// ... and the linear position does not exceed the size of this tree ...
		if (nPos < this->size ())
		{
			// ... then obtain of the data entry at the linear position in question
			this->convert_pos_to_container_pos (this->m_nRootNode, nPos, nNode, nSubPos);

			rData = *(this->get_data (nNode, nSubPos));

			retval = true;
		}
	}

	return (retval);
}

/*

get - get one specific instance using key

key			- contains an object specifying the key which is to be extracted from this parameter
nInstance	- specifies the instance of the entry sharing the same key as parameter "key"
pObj		- specifies a pointer where the entry will be copied to

This method extracts the key from the object of the first parameter (key) and copies
the instance of entry sharing the same key to the location pObj is pointing at.
The method count may be used to determine how many instances of the key in question exist.

The method returns true if it was successful, otherwise false.

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
bool CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::get (const _t_key &rKey, _t_sizetype nInstance, _t_data *pObj) const
{
	bool					retval = false;
	_t_nodeiter				nNode = this->m_nRootNode, nodeSeen;
	_t_subnodeiter			subPos, subPosSeen;
	bool					bBounce;
	_t_sizetype				u64;

	// if data layer not present ...
	if (this->m_pData == NULL)
	{
		// ... then return failure
		return (retval);
	}

	// if no entry with that is preset ...
	if (!find_oneKey (rKey, nNode, subPos))
	{
		// ... then return failure
		return (retval);
	}

	// find the first entry of sharing the same key and make it the "seen" position
	find_firstKey (nNode, subPos, nodeSeen, subPosSeen);

	// walk through key streak until the instance in question has been found
	for (u64 = 0ULL; u64 < nInstance; u64++)
	{
		// determine next position
		this->move_next (nodeSeen, subPosSeen, nNode, subPos, bBounce);

		// if next position doesn't exist ...
		if (bBounce)
		{
			// ... then abort procedure
			break;
		}

		// extract key of next position
		extract_key (m_pGetNewKey, nNode, subPos);

		// if key of next postion is not equal with current key ...
		if (this->comp (*m_pGetNewKey, rKey) != 0)
		{
			// ... then abort procedure
			break;
		}

		// assume next position as current position
		nodeSeen = nNode;
		subPosSeen = subPos;
	}

	// if procedure had been aborted ...
	if (u64 < nInstance)
	{
		// ... then return failure
		return (retval);
	}

	retval = true;

	// obtain data instance
	*pObj = *(this->get_data (nodeSeen, subPosSeen));

#if defined (_DEBUG)
	BTREE_ASSERT (nInstance == get_instancePos (nodeSeen, subPosSeen), "CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::get (_t_data, uint64_t, _t_data *): comparison of external and internal instance position mismatch!");
#endif

	// return success
	return (retval);
}

/*

get_init_pos_of_key - obtain first linear position of one key

key			- contains on object specifying the key which is to be extracted

If a number of entries is sharing the same key, this method is to be used to obtain the initial
position of those entries. However, the key must exists, otherwise the result is undefined.

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
_t_sizetype CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::get_init_pos_of_key (const _t_key &rKey) const
{
	_t_sizetype					retval = (_t_sizetype) ~0;
	_t_nodeiter					nNode, fstNode;
	_t_nodeiter					*pnNode;
	_t_subnodeiter				sub, fstSub;
	uint32_t					comp = 0;
	bool						bContinue;
	node_t						*psNodeDesc;

	// if data layer not present ...
	if (this->m_pData == NULL)
	{
		// ... then return failure
		return (retval);
	}

	// if any entry using that key exists ...
	if (find_oneKey (rKey, nNode, sub))
	{
		// ... then find first entry sharing the same key and find its linear position within the tree
		find_firstKey (nNode, sub, fstNode, fstSub);

		nNode = fstNode;
		sub = fstSub;

		retval = (_t_sizetype) 0;

		// move from parent node to parent node until the root node has been found and therewith the linear position
		do
		{
			// get description of current node
			psNodeDesc = this->get_node (nNode);

			bContinue = (nNode != this->m_nRootNode);

			// combine the number of entries in the current node with the result so far
			retval += (_t_subnodeiter) (sub + comp);

			// if this is an inner node ...
			if (!this->is_leaf (nNode))
			{
				// ... then add the number of all entries of previous or left sub nodes
				for (; sub != ((_t_subnodeiter) ~0); sub--)
				{
					pnNode = this->get_sub_node (nNode, sub);

					retval += this->get_max_index (*pnNode);
				}
			}

			// if the current node is not the root node ...
			if (bContinue)
			{
				// ... move to the parent node, which during the next iteration will be the current node
				sub = this->find_sub_node_offset (psNodeDesc->nParent, nNode) - 1;
				nNode = psNodeDesc->nParent;

				comp = 1;
			}
		} while (bContinue);
	}

	return (retval);
}

/*

determine_position - determine position

This method tries to determine whether or not a data item at position sPos is in the
node nNode or in one of its sub-nodes. If the return value bFound is true, then nSubData
points at the data item the caller is interested in, otherwise nSubPos must be used to
determine next sub-node and this method's return value ought to be used as parameter sPos
for the next call to determine_position.

This method is used to step into a tree to determine the position of a specific data item
to then further process it.

sPos		- specifies the absolute linear position of the data entry
nNode		- specifies the node to step into
nSubPos		- returns the sub-position in this node to determine the next node to step into, if bFound is false
nSubData	- returns the sub-position of the data item in this node
bFound		- return true if the sought data item is in node nNode, otherwise false

If bFound is false, then this method returns the parameter sPos for the next call to
determine_position, otherwise it return sPos again.

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
CBTreeKeySortPos<_t_sizetype, _t_key> CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::determine_position (CBTreeKeySortPos<_t_sizetype, _t_key> sPos, _t_nodeiter nNode, _t_subnodeiter &nSubPos, _t_subnodeiter &nSubData, bool &bFound) const
{
	_t_sizetype		nInstancePos;
	int				triCmpRslt;
	node_t			*psNodeDesc;

	psNodeDesc = this->get_node (nNode);

	// if node is a leaf node ...
	if (this->is_leaf (nNode))
	{
		// ... then convert sPos to a linear within this node
		_t_subnodeiter		uBase, ui32;

		nSubData = 0UL;

		// since this is a leaf node and stepping into another sub-node is not possible, it is simply assumed that the data is to be found in this node
		bFound = true;

		// binary sub-divide the data in this node until the correct sub-data position (nSubData) has been idenfied
		for (uBase = 0UL, ui32 = this->get_data_count (*psNodeDesc) / 2; ui32 > 0; ui32 >>= 1)
		{
			allocateShortLiveKey ();
			{
				// test for correct position in sub-division
				for (nSubData = uBase; nSubData < this->get_data_count (*psNodeDesc); nSubData += ui32)
				{
					// if the key of the current sub-position is smaller than the sought key ...
					if (this->comp (*(extract_key (*m_ppShortLiveKey, nNode, nSubData)), *(sPos.pKey)) < 0)
					{
						// ... then advance to next sub-division
						uBase = nSubData;
					}
					// if current key is equal to sought key ...
					else if (this->comp (*(extract_key (*m_ppShortLiveKey, nNode, nSubData)), *(sPos.pKey)) == 0)
					{
						// ... and it is key's instance of interest ...
						if ((sPos.nInstance == ~0ULL) || (sPos.nInstance == get_instancePos (nNode, nSubData)))
						{
							// ... then abort search
							ui32 = 0UL;

							break;
						}
					}
					else
					{
						// if the current key is bigger than the sought key, then abort and sub-divide further
						break;
					}
				}
			}
			freeShortLiveKey ();
		}
	}
	else
	{
		// if this is an inner node, then try to find data item within this node or identify the next sub-node
		bFound = false;

		// find nearest sub-position of key of interest in this node
		nSubData = nSubPos = get_firstSubPos (nNode, *(sPos.pKey));

		// if the nearest sub-position is not the last position ...
		if (nSubPos < this->get_data_count (*psNodeDesc))
		{
			allocateShortLiveKey ();
			{
				triCmpRslt = this->comp (*(sPos.pKey), *(extract_key (*m_ppShortLiveKey, nNode, nSubData)));

				// if key of interest matches key at data sub-position ...
				if (triCmpRslt == 0)
				{
					// ... and it is key's instance of interest ...
					if ((get_instancePos (nNode, nSubPos) == sPos.nInstance) || (sPos.nInstance == ~0ULL))
					{
						// ... then flag the find
						bFound = true;
					}
				}
			}
			freeShortLiveKey ();
		}

		// if data has not been found yet ...
		if (!bFound)
		{
			// ... and if a specific key instance is being sought ...
			if (sPos.nInstance != ~0ULL)
			{
				// ... then test for other instances that share the same key and if any of those has the correct instance
				allocateShortLiveKey ();
				{
					// walk through node until the end of the node has been reached or a different key has been found
					for (; ((nSubPos < this->get_data_count (*psNodeDesc)) && (this->comp (*(sPos.pKey), *(extract_key (*m_ppShortLiveKey, nNode, nSubPos))) == 0)); nSubPos++, nSubData++)
					{
						nInstancePos = get_instancePos (nNode, nSubPos);

						// if the found instance is bigger than the one of interest ...
						if (nInstancePos > sPos.nInstance)
						{
							// ... then the correct instance must be in the previous sub-node and the search in this node is aborted
							break;
						}
						// if the correct instance has been found ...
						else if (nInstancePos == sPos.nInstance)
						{
							// ... then flag the find and abort search
							bFound = true;

							break;
						}
					}
				}
				freeShortLiveKey ();
			}

			// if data sub-position exceeds node data size as a result of the previous loop ...
			if (nSubData >= this->get_data_count (*psNodeDesc))
			{
				// ... then limit data sub-position to node's data size
				nSubData -= 1;
			}
		}
	}

	return (sPos);
}

/*

rebuild_node - rebuild node after modification

This method is called to re-instate the integrity of this node within the b-tree. If a
node is split, merged or an entry is inserted or removed, then not only the size of a node
needs updating. Also the maximum index (nMaxIdx), which displays the size of this node
as well as any sub-nodes of this node combined, has to be re-calculated.

nNode		- specifies the node to be updated
triMod		- specifies a tri-state fast update modifier
				+ if set to zero, then fully re-calculate nMaxIdx
				+ if not set to zero, then add triMod to this node's nMaxIdx

Note:	The parameter triMod is usually set 1 or -1 if one entry is inserted or removed
		respectively. This avoids the requirement to look at any sub-node's nMaxIdx, which
		as a result avoids to have the sub-node descriptor cache modified to a dis-advantage.

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
void CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::rebuild_node (const _t_nodeiter nNode, const int32_t triMod, _t_subnodeiter nSubStart)
{
#if defined (_DEBUG)
	BTREE_ASSERT (nNode < this->m_nTreeSize, "CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::rebuild_node: requested node exceeds tree size");
#endif

	_t_nodeiter									*pnSubNode;
	node_t										*psNodeDesc;
	_t_sizetype									nIdx = (_t_sizetype) 0;
	_t_subnodeiter								ui32;
	_t_subnodeiter								nSubPosOffset;
	_t_sizetype									*pnSerVector;
	int											nLocalTriMod = triMod;

	psNodeDesc = this->get_node (nNode);

	// if nNode is a leaf node ...
	if (this->is_leaf (nNode))
	{
		// ... then use the arithmetic negative size value of this node to determine nMaxIdx
		nIdx = ((_t_subnodeiter) (0 - psNodeDesc->nNumData));

		// Note:	If a node is a leaf node, then the size is displayed as a negative
		//			value, which appears as a 2's complement value, since the size actually is unsigned.
	}
	else
	{
		const _t_subnodeiter						nNumData = this->get_data_count (*psNodeDesc);

		pnSerVector = this->get_serVector (nNode);

		// if nMaxIdx has been determined (already set up node) and the fast modifier is set ...
		if ((psNodeDesc->nMaxIdx != 0) && (triMod != 0))
		{
			// ... then use fast modifier to update nMaxIdx and serial vector
			
			// initialise index variable being employed to populate serial vector
			if (nSubStart == 0)
			{
				nIdx = 0;
			}
			else
			{
				nSubPosOffset = nSubStart - 1;
				nIdx = pnSerVector[nSubPosOffset] - nSubPosOffset;
			}

			// seek point where serial vector mismatches expected sequence based on sub-node indexes
			for (ui32 = nSubStart; ui32 < (nNumData - 1); ui32++)
			{
				pnSubNode = this->get_sub_node (nNode, ui32);

				nIdx += this->get_max_index (*pnSubNode);

				if (pnSerVector[ui32] != (nIdx + ui32))
				{
					break;
				}
			}

			// update remaining serial vector part by using fast modifier
			for (; ui32 < (nNumData - 1); ui32++)
			{
				pnSerVector[ui32] += triMod;
			}

			nIdx = psNodeDesc->nMaxIdx + triMod;

			if (ui32 == 0)
			{
				pnSubNode = this->get_sub_node (nNode, 0);

				pnSerVector[0] = this->get_max_index (*pnSubNode);
			}
			else if (ui32 < nNumData)
			{
				pnSubNode = this->get_sub_node (nNode, nNumData);

				const _t_sizetype	nLastIdx = this->get_max_index (*pnSubNode);

				pnSubNode = this->get_sub_node (nNode, nNumData - 1);

				const _t_sizetype	nSecondLastIdx = this->get_max_index (*pnSubNode);
				_t_sizetype			nTrialingIdx = nLastIdx;

				nTrialingIdx += nSecondLastIdx;

				nTrialingIdx += 2;

				if (nIdx != (pnSerVector[ui32 - 1] + nTrialingIdx))
				{
					nLocalTriMod = 0;
				}
				else
				{
					// code cannot be sure if the last entry had valid data in the first place
					// re-build last entry from all other values
					pnSerVector[ui32] = nIdx - nLastIdx - 1;

					// the above code doesn't account for new entries
					// if new entry has been created, which is not in the last place ...
					if (pnSerVector[ui32] < pnSerVector[ui32 - 1])
					{
						// ..then fall back to slow full re-build mode
						nLocalTriMod = 0;
					}
				}
			}
		}
		
		// if nMaxIdx has not been determined yet (newly created node) or the fast modifier is not set ...
		if ((psNodeDesc->nMaxIdx == 0) || (nLocalTriMod == 0))
		{
			this->m_pData->set_cacheFreeze (true);
			{
				// ... then fully re-calculate nMaxIdx and serial vector
				for (ui32 = 0UL, nIdx = 0; ui32 < this->get_sub_node_count (*psNodeDesc); ui32++)
				{
					pnSubNode = this->get_sub_node (nNode, ui32);

					nIdx += this->get_max_index (*pnSubNode);

					if (ui32 < this->get_data_count (nNode))
					{
						pnSerVector[ui32] = nIdx + ui32;
					}
				}
			}
			this->m_pData->set_cacheFreeze (false);

			nIdx += this->get_data_count (*psNodeDesc);
		}
	}

	// write result back
	psNodeDesc->nMaxIdx = nIdx;
}

/*

generate_prev_position - generate previous position

This method returns the previous position (CBTreeBaseDefaults::_ti_pos = CBTreeKeySortPos<_t_sizetype, _t_key>)
based on the parameter sPos and the node / sub-node tuple associated with sPos.

nNode		- specifies the node of the node / sub-position tuple of which the previous position will be generated from
nSub		- specifies the sub_position of the node / sub-position tuple of which the previous position will be generated from
sPos		- class specific position associated with node / sub-node tuple

The return value is the previous linear position of sPos (nNode, nSub) in terms of how data is
presented to the application. Given that the b-tree classes are supposed to act like a linear
list to calling the application, this pseudo code displays what generate_prev_position does:

return_value = (*this)[sPos (this, nNode, nSub) - 1];

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
CBTreeKeySortPos<_t_sizetype, _t_key> CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::generate_prev_position (const _t_nodeiter nNode, const _t_subnodeiter nSub, CBTreeKeySortPos<_t_sizetype, _t_key> sPos)
{
	_t_nodeiter		nPrevNode;
	_t_subnodeiter	nPrevSubPos;
	bool			bBounce;
	_t_data			*psData;

	// get previous position within tree
	this->move_prev (nNode, nSub, nPrevNode, nPrevSubPos, bBounce);

#if defined (_DEBUG)
	BTREE_ASSERT (!this->is_leaf (nNode), "CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::generate_prev_position: This method cannot be used on leaf nodes!");
	BTREE_ASSERT (!bBounce, "CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::generate_prev_position: unexpected bounce!");
#endif

	psData = this->get_data (nPrevNode, nPrevSubPos);

	// get key of previous position
	m_pTempRemoveKey = extract_key (m_pTempRemoveKey, *psData);

	sPos.pKey = m_pTempRemoveKey;
	sPos.nInstance = get_instancePos (nPrevNode, nPrevSubPos);

	return (sPos);
}

/*

generate_next_position - generate next position

This method returns the next position (CBTreeBaseDefaults::_ti_pos = CBTreeKeySortPos<_t_sizetype, _t_key>)
based on the parameter sPos and the node / sub-node tuple associated with sPos.

nNode		- specifies the node of the node / sub-position tuple of which the next position will be generated from
nSub		- specifies the sub_position of the node / sub-position tuple of which the next position will be generated from
sPos		- class specific position associated with node / sub-node tuple

The return value is the next linear position of sPos (nNode, nSub) in terms of how data is
presented to the application. Given that the b-tree classes are supposed to act like a linear
list to calling the application, this pseudo code displays what generate_prev_position does:

return_value = (*this)[sPos (this, nNode, nSub) + 1];

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
CBTreeKeySortPos<_t_sizetype, _t_key> CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::generate_next_position (_t_nodeiter nNode, _t_subnodeiter nSub, CBTreeKeySortPos<_t_sizetype, _t_key> sPos)
{
	_t_nodeiter		nNextNode;
	_t_subnodeiter	nNextSubPos;
	bool			bBounce;
	_t_data			*psData;

	// get previous position within tree
	this->move_next (nNode, nSub, nNextNode, nNextSubPos, bBounce);

#if defined (_DEBUG)
	BTREE_ASSERT (!this->is_leaf (nNode), "CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::generate_next_position: This method cannot be used on leaf nodes!");
	BTREE_ASSERT (!bBounce, "CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::generate_next_position: unexpected bounce!");
#endif

	psData = this->get_data (nNextNode, nNextSubPos);

	// get key of previous position
	m_pTempRemoveKey = extract_key (m_pTempRemoveKey, *psData);

	sPos.pKey = m_pTempRemoveKey;
	sPos.nInstance = get_instancePos (nNextNode, nNextSubPos);

	return (sPos);
}

/*

comp - compare keys

This is the default method to compare two keys.

pkey0		- first key to compare
pkey1		- second key to compare

The return value is zero if both keys are matching, negative if the first key is smaller than
the second key and positive if the first key is bigger than the second key.

Note:	This method is application specific. By default the entire data set is deemed to be its key.
		If the key needs to be interpreted from the data set or not the entire data set is the, than
		a class inheriting from CBTreeKeySort needs to be created, replacing this method.

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
int CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::comp (const _t_key &rKey0, const _t_key &rKey1) const
{
	return (memcmp ((void *) &rKey0, (void *) &rKey1, sizeof (_t_key)));
}

/*

extract_key - extract key

This is the default method to convert the dataset associated with node / sub-node into a key.

nNode		- node parameter of node / sub-node tuple
nEntry		- sub-node parameter of node / sub-node tuple
obj			- dataset to be converted

The return value is pKey again. This enables extract_key to act as a parameter for other methods.

Note:	This method is application specific. By default the entire data set is deemed to be its key.
		If the key needs to be interpreted from the data set or not the entire data set is the, than
		a class inheriting from CBTreeKeySort needs to be created, replacing this method.

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
_t_key *CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::extract_key (_t_key *pKey, const _t_nodeiter nNode, const _t_subnodeiter nEntry) const
{
	_t_data				*psData;

#if defined (_DEBUG)
	BTREE_ASSERT (nEntry < this->get_data_count (nNode), "CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::extract_key (_t_key *, const _t_nodeiter, const _t_subnodeiter): requested entry exceeds nodes data size");
#endif

	// obtain dataset
	psData = this->get_data (nNode, nEntry);

	// convert dataset to key
	return (extract_key (pKey, *psData));
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
_t_key *CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::extract_key (_t_key *pKey, const _t_data &rData) const
{
	typename ::std::is_convertible<_t_data, _t_key>::type	sExtractSelect;

	return (CBTreeAssociative_t::extract_key (pKey, rData, sExtractSelect));
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
_t_key *CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::extract_dataset_as_key (_t_key *pKey, const _t_data &rData, typename ::std::true_type) const
{
	pKey;

	return (&rData);
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
_t_key *CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::extract_dataset_as_key (_t_key *pKey, const _t_data &rData, typename ::std::false_type) const
{
	typename ::std::is_convertible<_t_data, _t_key *>::type	sExtractSelect;	// extract by reference or conversion
	
	return (CBTreeAssociative_t::extract_key_directly (pKey, rData, sExtractSelect));
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
_t_key *CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::extract_key_directly (_t_key *pKey, const _t_data &rData, typename ::std::true_type) const
{
	pKey;

	return ((_t_key *) rData);
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
_t_key *CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::extract_key_directly (_t_key *pKey, const _t_data &rData, typename ::std::false_type) const
{
	typename ::std::is_convertible<_t_data, _t_key>::type	sExtractSelect;

	return (CBTreeAssociative_t::extract_key (pKey, rData, sExtractSelect));
}

/*

extract_key - extract key

This is the default method to convert a dataset into a key.

pKey		- pointer to location where the extracted key will be written to
obj			- dataset to be converted

The return value is pKey again. This enables extract_key to act as a parameter for other methods.

Note:	This method is application specific. By default the entire data set is deemed to be its key.
		If the key needs to be interpreted from the data set or not the entire data set is the, than
		a class inheriting from CBTreeKeySort needs to be created, replacing this method.

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
_t_key *CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::extract_key (_t_key *pKey, const _t_data &rData, typename ::std::true_type) const
{
	_t_data		sData = rData;

	*pKey = (_t_key) sData;

	return (pKey);
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
_t_key *CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::extract_key (_t_key *pKey, const _t_data &rData, typename ::std::false_type) const
{
#if defined (_DEBUG)

	static int	nCallDepth = 0;

	// if this assertion is hit, then _t_data cannot be cast to _t_key and this or the deriving class has not provided its version of extract_key ()
	BTREE_ASSERT (nCallDepth == 0, "CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::extract_key (_t_key *, const _t_data &, typename ::std::false_type): Call depth not zero");

	nCallDepth++;

#endif

	_t_key		*pRslt;

	pRslt = this->extract_key (pKey, rData);

#if defined (_DEBUG)

	nCallDepth--;

#endif

	return (pRslt);
}

/*

get_instancePos - get instance position

The method get_instancePos extracts the key of sub-position (nSub) in node (nNode) and returns
the number of linear entries before the given entry, which share the same key.

nNode		- node parameter of node / sub-node tuple
nSub		- sub-node parameter of node / sub-node tuple

The return value is zero if no other entry shares the same key or it is the initial instance of
an entry streak sharing the same key, otherwise the number of entries before the given instance
sharing the same key is returned.

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
_t_sizetype CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::get_instancePos (_t_nodeiter nNode, _t_subnodeiter nSub) const
{
	_t_sizetype				nRetval = (_t_sizetype) 0;
	bool					bBounce;
	_t_nodeiter				nFromNode = nNode;
	_t_subnodeiter			nFromSub = nSub;
	_t_nodeiter				*pnNode;

	// determine one key of the key raw in question
	*m_ppTempFindFirstKeyKey = extract_key (*m_ppTempFindFirstKeyKey, nFromNode, nFromSub);

	// continue searching for the initial position of key raw until either the beginning of the list or a different key has been found
	while (true)
	{
		// update output position
		nNode = nFromNode;
		nSub = nFromSub;

		if (	this->is_leaf (nNode) || 
				(nSub == 0) || 
				(this->comp (**m_ppTempFindFirstKeyKey, *(extract_key (m_pTempFindFirstKeyNewKey, nNode, nSub - 1))) != 0)
			)
		{
			// move to previous position
			this->move_prev (nNode, nSub, nFromNode, nFromSub, bBounce);
		}
		else
		{
			bBounce = false;

			nFromSub = nSub - 1;

			pnNode = this->get_sub_node (nNode, nSub);

			nRetval += this->get_max_index (*pnNode);
		}

		// if beginning the of the list has been reached ...
		if (bBounce)
		{
			// ... then abort searching
			break;
		}

		extract_key (m_pTempFindFirstKeyNewKey, nFromNode, nFromSub);

		// if a different key has been found ...
		if (this->comp (*m_pTempFindFirstKeyNewKey, **m_ppTempFindFirstKeyKey) != 0)
		{
			// ... then abort searching
			break;
		}

		nRetval++;
	}

	return (nRetval);
}

/*

get_firstSubPos - get first sub-position

To find the sub-position of the nearest greater or equal key of what pKey is pointing at
within a node, this method ought to be used.

nNode		- specifies the node in which the nearest greater or equal key is to be sought in
pKey		- points at key to be sought

The value returned is the sub-position, which has the nearest greater or equal key compared to *pKey.

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
_t_subnodeiter CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::get_firstSubPos (_t_nodeiter nNode, _t_key const &rKey, bool bReverse) const
{
	node_t					*psNodeDesc;
	_t_subnodeiter			ui32;
	_t_subnodeiter			nMinPos, nMaxPos;
	int						triCmpRslt = ~0x0;

	// load node descriptor
	psNodeDesc = this->get_node (nNode);

	// set range up
	nMinPos = 0UL;

	nMaxPos = this->get_data_count (*psNodeDesc);

	// until first sub postion has been found ...
	while (nMinPos != nMaxPos)
	{
		// sub divide range and determine average middle position
		ui32 = (nMinPos + nMaxPos) / 2;

		allocateShortLiveKey ();
		{
			// get key of current middle position
			*m_ppShortLiveKey = extract_key (*m_ppShortLiveKey, nNode, ui32);

			triCmpRslt = this->comp (rKey, **m_ppShortLiveKey);

			// if search key is smaller than or equal to middle key ...
			if (triCmpRslt <= 0)
			{
				// ... then range maximum assumes middle position
				nMaxPos = ui32;
			}
			else
			{
				// ... otherwise, range minimum assumes next position after middle position
				nMinPos = ui32 + 1;
			}
		}
		freeShortLiveKey ();
	}

	if (bReverse)
	{
		if (triCmpRslt == 0)
		{
			// set range up
			nMaxPos = this->get_data_count (*psNodeDesc);

			// until last equal sub postion has been found ...
			while ((nMinPos + 1) != nMaxPos)
			{
				// sub divide range and determine average middle position
				ui32 = (nMinPos + nMaxPos) / 2;

				allocateShortLiveKey ();

				// get key of current middle position
				*m_ppShortLiveKey = extract_key (*m_ppShortLiveKey, nNode, ui32);

				triCmpRslt = this->comp (rKey, **m_ppShortLiveKey);

				// if search key is smaller than or equal to middle key ...
				if (triCmpRslt < 0)
				{
					// ... then range maximum assumes middle position
					nMaxPos = ui32;
				}
				else
				{
					// ... otherwise, range minimum assumes next position after middle position
					nMinPos = ui32;
				}

				freeShortLiveKey ();
			}
		}
	}

	return (nMinPos);
}

/*

find_next_sub_pos - find next sub-position

To find the sub-position of the nearest greater key of what pKey is pointing at
within a node, this method ought to be used.

nNode		- specifies the node in which the nearest greater key is to be sought in
pKey		- points at key to be sought

The value returned is the sub-position, which has the nearest greater key compared to *pKey.

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
_t_subnodeiter CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::find_next_sub_pos (const _t_nodeiter nNode, CBTreeKeySortPos<_t_sizetype, _t_key> &sPos) const
{
	node_t					*psNodeDesc;
	_t_subnodeiter			ui32;
	_t_subnodeiter			nMinPos, nMaxPos;

	// load node descriptor
	psNodeDesc = this->get_node (nNode);

	// set range up
	nMinPos = 0UL;

	nMaxPos = this->get_data_count (*psNodeDesc);

	// until nearest sub postion has been found ...
	while (nMinPos != nMaxPos)
	{
		// sub divide range and determine average middle position
		ui32 = (nMinPos + nMaxPos) / 2;

		allocateShortLiveKey ();

		// get key of current middle position
		*m_ppShortLiveKey = extract_key (*m_ppShortLiveKey, nNode, ui32);

		// if search key is smaller than middle key ...
		if (this->comp (*(sPos.pKey), **m_ppShortLiveKey) < 0)
		{
			// ... then range maximum assumes middle position
			nMaxPos = ui32;
		}
		else
		{
			// ... otherwise, range minimum assumes next position after middle position
			nMinPos = ui32 + 1;
		}

		freeShortLiveKey ();
	}

	return (nMinPos);
}

/*

find_oneKey - find one key

To track down into the tree to find any location, which has the same key as pKey is
pointing at, this method is to be used.

pkey		- specifies the pointer to the key in question
nNode		- returns the node in which an equal key has been found
nSub		- returns the sub-position within the node in which an equal key has been found

If it was possible to find any matching key, then true is returned, otherwise false.

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
bool CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::find_oneKey (const _t_key &rKey, _t_nodeiter &nNode, _t_subnodeiter &nSub, _t_sizetype *pnPos) const
{
	uint32_t	bFound;

	nNode = this->m_nRootNode;

	if (pnPos != NULL)
	{
		(*pnPos) = 0;
	}

	// continue until one node has been found that contains *pkey
	while (1)
	{
		bFound = 0;

		// determine current node's sub position that has the nearest smaller or equal key
		nSub = get_firstSubPos (nNode, rKey);

		// load node descriptor
		node_t	*psNodeDesc;
			
		psNodeDesc = this->get_node (nNode);

		// if key can be found in current node ...
		if (nSub < this->get_data_count (*psNodeDesc))
		{
			// ... then test if key is part of the current node

			allocateShortLiveKey ();

			// extract key from node's sub postition
			*m_ppShortLiveKey = extract_key (*m_ppShortLiveKey, nNode, nSub);

			// if extracted key is equal to searched key ...
			if (this->comp (**m_ppShortLiveKey, rKey) == 0)
			{
				// ... then abort searching
				bFound = 1;
			}

			freeShortLiveKey ();
		}

		if (pnPos != NULL)
		{
			_t_subnodeiter	i;

			if (!this->is_leaf (nNode))
			{
				for (i = 0; i < (nSub + bFound); i++)
				{
					_t_nodeiter		*pnSubNode = this->get_sub_node (nNode, i);

					(*pnPos) += this->get_max_index (*pnSubNode);
				}
			}

			(*pnPos) += nSub;
		}

		if (bFound != 0)
		{
			break;
		}

		// if the current node is a leaf node ...
		if (this->is_leaf (nNode))
		{
			// ... then abort searching and return failure
			return (false);
		}

		// determine sub node for next iteration
		nNode = *(this->get_sub_node (nNode, nSub));
	}

	return (true);
}

/*

find_firstKey - find first key

This method extracts the key from the sub-position nFromSub within node nFromNode and then rewinds
until the first location, that has the same key as the one extracted, has been found. 

nFromNode	- specifies node from where to rewind from
nFromSub	- specifies the sub-position within nFromNode
nNode		- returns the node where the first key has been found
nSub		- returns the sub-position within nNode where the first key has been found

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
_t_sizetype CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::find_firstKey (_t_nodeiter nFromNode, _t_subnodeiter nFromSub, _t_nodeiter &nNode, _t_subnodeiter &nSub) const
{
	_t_sizetype		nRetval = 0;
	_t_sizetype		nStepSize = 0;
	_t_nodeiter		*pnSubNode;
	bool			bBounce;
	
	// determine one key of the key raw in question
	*m_ppTempFindFirstKeyKey = extract_key (*m_ppTempFindFirstKeyKey, nFromNode, nFromSub);

	// continue searching for the initial position of key raw until either the beginning of the list or a different key has been found
	while (1)
	{
		// update output position
		nNode = nFromNode;
		nSub = nFromSub;

		nRetval += nStepSize;

		if (	this->is_leaf (nNode) || 
				(nSub == 0) || 
				(this->comp (**m_ppTempFindFirstKeyKey, *(extract_key (m_pTempFindFirstKeyNewKey, nNode, nSub - 1))) != 0)
			)
		{
			// move to previous position
			this->move_prev (nNode, nSub, nFromNode, nFromSub, bBounce);

			nStepSize = 1;
		}
		else
		{
			bBounce = false;

			pnSubNode = this->get_sub_node (nFromNode, nFromSub);

			nFromSub = nSub - 1;

			nStepSize = this->get_max_index (*pnSubNode);
			nStepSize += 1;
		}

		// if beginning the of the list has been reached or a different key has been found ...
		if (bBounce)
		{
			// ... then abort searching
			break;
		}

		extract_key (m_pTempFindFirstKeyNewKey, nFromNode, nFromSub);

		if (this->comp (*m_pTempFindFirstKeyNewKey, **m_ppTempFindFirstKeyKey) != 0)
		{
			break;
		}
	}

	return (nRetval);
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
void CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::erase_via_reference
	(
		typename CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::const_iterator &rCIterPos, 
		bool bReEvaluate
	)
{
	bool			bFallBack = true;
	
	// if the iterator is associated with this btree ...
	if (this == rCIterPos.get_container ())
	{
		// ... and if iterator ready for use ...
		if (rCIterPos.is_evaluated ())
		{
			iterator_state_t	*psIterState = (iterator_state_t *) rCIterPos.get_iterator_state ();

			// ... and if the node to be modified is a leaf node ...
			if (this->is_leaf (psIterState->nNode))
			{
				// ... and if the node to be modified has enough entries left ...
				if (this->get_data_count (psIterState->nNode) > (this->get_node_max_data_size () / 2))
				{
					// ... then an additional entry can be added fast
					_t_nodeiter			nNode;

					bFallBack = false;

					// insert entry into leaf node
					this->remove_data_from_leaf (psIterState->nNode, psIterState->nSubPos);

					// rebuild all parent node's integrity by back-tracing to the root node
					nNode = psIterState->nNode;

					while (nNode != this->m_nRootNode)
					{
						nNode = this->get_parent (nNode);

						this->rebuild_node (nNode, -1);
					}

					// update time stamp
					this->update_time_stamp ();

					if (psIterState->nSubPos < this->get_data_count (psIterState->nNode))
					{
						// overwrite iterator time stamp directly, without having the iterator to evaluate again
						rCIterPos.set_time_stamp (this);

						bReEvaluate = false;
					}
				}
			}
		}
	}

	// if fast erase was not possible ...
	if (bFallBack)
	{
		CBTreeKeySortPos<_t_sizetype, _t_key>	sPos;
		_t_sizetype								nPos = rCIterPos.get_pos ();
		_t_nodeiter								nNode;
		_t_subnodeiter							nSubPos;

		this->convert_pos_to_container_pos (this->m_nRootNode, nPos, nNode, nSubPos);

		this->extract_key (m_pRemoveKey, nNode, nSubPos);

		sPos.pKey = m_pRemoveKey;
		sPos.nInstance = this->get_instancePos (nNode, nSubPos);

		this->remove_from_node (sPos, this->m_nRootNode, 0);
	}

	// iterator reference is used for more than one access ...
	if (bReEvaluate)
	{
		// ... then prepare iterator for next access
		rCIterPos.sync ();
	}
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
bool CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::_find (const _t_key &rKey, _t_nodeiter &rnNode, _t_subnodeiter &rnSub, _t_sizetype &rnPos) const
{
	return (this->find_oneKey (rKey, rnNode, rnSub, &rnPos));
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
void CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::_lower_bound (const _t_key &rKey, _t_nodeiter &rnNode, _t_subnodeiter &rnSub, _t_sizetype &rnPos) const
{
	_t_nodeiter			nRsltNode;
	_t_subnodeiter		nRsltSub;

	if (this->find_oneKey (rKey, rnNode, rnSub, &rnPos))
	{
		rnPos -= this->find_firstKey (rnNode, rnSub, nRsltNode, nRsltSub);

		rnNode = nRsltNode;
		rnSub = nRsltSub;
	}
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
bool CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::_upper_bound (const _t_key &rKey, _t_nodeiter &rnNode, _t_subnodeiter &rnSub, _t_sizetype &rnPos) const
{
	_t_key				sKey;
	bool				bBounce;

	this->get_next_key (rKey, sKey, bBounce);

	if (bBounce)
	{
		rnPos = this->size ();
	}
	else
	{
		CBTreeAssociative_t::_lower_bound (sKey, rnNode, rnSub, rnPos);
	}

	return (bBounce);
}

/*

vbufferAllocate - allocate variable size buffer

This method de-allocates the buffer *pp if that is required and allocates a new buffer
of size of _t_key.

Note:	The intention is to be able to allocate and de-allocate temporary key buffers as soon as
		unload is called and to have them reinstated when needed. This has not been implemented
		yet and therefore vbufferAllocate and vbufferDeallocate seem like overkill.

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
void CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::vbufferAllocate (_t_key **pp)
{
	if (*pp != NULL)
	{
		vbufferDeallocate (pp);
	}

	*pp = new _t_key;

	BTREE_ASSERT (*pp != NULL, "CBTreeAssociative<_t_data, _t_key, _t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayer>::vbufferAllocate: insufficient memory");
}

/*

vbufferDeallocate - de-allocate variable size buffer

This method de-allocates the buffer *pp if that is required.

Note:	The intention is to be able to allocate and de-allocate temporary key buffers as soon as
		unload is called and to have them reinstated when needed. This has not been implemented
		yet and therefore vbufferAllocate and vbufferDeallocate seem like overkill.

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
void CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::vbufferDeallocate (_t_key **pp)
{
	if (*pp != NULL)
	{
		delete *pp;
	}

	*pp = NULL;
}

/*

allocateShortLiveKey - allocate short live key

This method tests if the member variable m_bShortLiveKeyInUse is de-asserted, if it is not
then the program terminates, otherwise it asserts m_bShortLiveKeyInUse.

Note:	The intention is to make sure that m_pShortLiveKey is not used in one method and then
		used again in another method which is called by the method before. So, code
		sections were m_pShortLiveKey gets employed are surrounded by allocateShortLiveKey
		and freeShortLiveKey. It has debug purposes only and is not part of the final binary.

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
void CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::allocateShortLiveKey () const
{
#if defined (_DEBUG)
	BTREE_ASSERT (!(*m_pbShortLiveKeyInUse), "CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayer>::allocateShortLiveKey: DEBUG: short live key in use!");

	*m_pbShortLiveKeyInUse = true;
#endif
}

/*

freeShortLiveKey - free short live key

This method tests if the member variable m_bShortLiveKeyInUse is asserted, if it is not
then the program terminates, otherwise it de-asserts m_bShortLiveKeyInUse.

Note:	The intention is to make sure that m_pShortLiveKey is not used in one method and then
		used again in another method which is called by the method before. So, code
		sections were m_pShortLiveKey gets employed are surrounded by allocateShortLiveKey
		and freeShortLiveKey. It has debug purposes only and is not part of the final binary.

*/

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
void CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::freeShortLiveKey () const
{
#if defined (_DEBUG)
	BTREE_ASSERT (*(m_pbShortLiveKeyInUse), "CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayer>::freeShortLiveKey: DEBUG: short live key was already de-allocated!");

	*m_pbShortLiveKeyInUse = false;
#endif
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
bool CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::show_data (std::ofstream &ofs, std::stringstream &rstrData, std::stringstream &rszMsg, const _t_nodeiter nNode, const _t_subnodeiter nSubPos) const
{
	return (true);
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
bool CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::show_node (std::ofstream &ofs, const _t_nodeiter nNode, const _t_subnodeiter nSubPos) const
{
	std::stringstream		buf;
	_t_data					*psData;
	_t_nodeiter				nNeightbourNode;
	_t_subnodeiter			nNeightbourSub;
	int						nErrCnt = 0;
	std::stringstream		aszMsg;
	char					*pColorInit = (char *) "";
	char					*pColorExit = (char *) "";
	_t_nodeiter				nPrevNode;
	_t_subnodeiter			nPrevSub;
	_t_nodeiter				nNextNode;
	_t_subnodeiter			nNextSub;
	bool					bBounce;
	_t_key					sKey;

	psData = this->get_data (nNode, nSubPos);

	if (this->is_leaf (nNode))
	{
		if (!this->show_data (ofs, buf, aszMsg, nNode, nSubPos))
		{
			if (!ofs.is_open ())
			{
				return (false);
			}

			nErrCnt++;
		}

		try
		{
			this->move_prev (nNode, nSubPos, nPrevNode, nPrevSub, bBounce);

			if (bBounce == false)
			{
				_t_data	*psPrevData = this->get_data (nPrevNode, nPrevSub);
				_t_key	sPrevKey;
				_t_key	sKey;

				this->extract_key (&sPrevKey, *psPrevData);
				this->extract_key (&sKey, *psData);

				if (this->comp (sPrevKey, sKey) > 0)
				{
					if (!ofs.is_open ())
					{
						return (false);
					}

					nErrCnt++;

					aszMsg << "<br>prev: integrity error";
				}

				this->move_next (nPrevNode, nPrevSub, nNextNode, nNextSub, bBounce);

				if (bBounce)
				{
					if (!ofs.is_open ())
					{
						return (false);
					}

					nErrCnt++;

					aszMsg << "<br>prev: unexpected bBounce";
				}
				else
				{
					if ((nNextNode != nNode) || (nNextSub != nSubPos))
					{
						if (!ofs.is_open ())
						{
							return (false);
						}

						nErrCnt++;

						aszMsg << "<br>prev: broken link";
					}
				}
			}

			this->allocateShortLiveKey ();
			{
				this->move_prev (nNode, nSubPos, nNeightbourNode, nNeightbourSub, bBounce);

				if (bBounce == false)
				{
					this->extract_key (*(this->m_ppShortLiveKey), nNeightbourNode, nNeightbourSub);

					this->extract_key (&sKey, *psData);

					if (this->comp (**(this->m_ppShortLiveKey), sKey) == 0)
					{
						if (this->get_instancePos (nNode, nSubPos) != (this->get_instancePos (nNeightbourNode, nNeightbourSub) + 1))
						{
							if (!ofs.is_open ())
							{
								this->freeShortLiveKey ();
								
								return (false);
							}

							nErrCnt++;

							aszMsg << "<br>instance position error!";
						}
					}
				}

				this->move_next (nNode, nSubPos, nNeightbourNode, nNeightbourSub, bBounce);

				if (bBounce == false)
				{
					this->extract_key (*(this->m_ppShortLiveKey), nNeightbourNode, nNeightbourSub);

					this->extract_key (&sKey, *psData);

					if (this->comp (**(this->m_ppShortLiveKey), sKey) == 0)
					{
						if (this->get_instancePos (nNode, nSubPos) != (this->get_instancePos (nNeightbourNode, nNeightbourSub) - 1))
						{
							if (!ofs.is_open ())
							{
								this->freeShortLiveKey ();
								
								return (false);
							}

							nErrCnt++;

							aszMsg << "<br>instance position error!";
						}
					}
				}
			}
			this->freeShortLiveKey ();
		}
		catch (exception *pE)
		{
			if (!ofs.is_open ())
			{
				return (false);
			}

			nErrCnt++;

			aszMsg << "<br>prev: link walk crashed (" << pE->what () << ")";
		}

		try
		{
			this->move_next (nNode, nSubPos, nNextNode, nNextSub, bBounce);

			if (bBounce == false)
			{
				_t_data	*psNextData = this->get_data (nNextNode, nNextSub);
				_t_key	sNextKey;
				_t_key	sKey;

				this->extract_key (&sNextKey, *psNextData);
				this->extract_key (&sKey, *psData);

				if (this->comp (sNextKey, sKey) < 0)
				{
					if (!ofs.is_open ())
					{
						return (false);
					}

					nErrCnt++;

					aszMsg << "<br>next: integrity error";
				}

				this->move_prev (nNextNode, nNextSub, nPrevNode, nPrevSub, bBounce);

				if (bBounce)
				{
					if (!ofs.is_open ())
					{
						return (false);
					}

					nErrCnt++;

					aszMsg << "<br>next: unexpected bBounce";
				}
				else
				{
					if ((nPrevNode != nNode) || (nPrevSub != nSubPos))
					{
						if (!ofs.is_open ())
						{
							return (false);
						}

						nErrCnt++;

						aszMsg << "<br>next: broken link";
					}
				}
			}
		}
		catch (exception *pE)
		{
			if (!ofs.is_open ())
			{
				return (false);
			}

			nErrCnt++;

			aszMsg << "<br>next: link walk crashed (" << pE->what () << ")";
		}

		if (nErrCnt == 0)
		{
			pColorInit = (char *) "";
			pColorExit = (char *) "";
		}
		else
		{
			pColorInit = (char *) "<font color=\"#FF0000\">";
			pColorExit = (char *) "</font>";
		}
		
		if (ofs.is_open ())
		{
			ofs << pColorInit << buf.str ().c_str () << pColorExit << aszMsg.str ().c_str ();
		}
	}
	else
	{
		if (!this->show_data (ofs, buf, aszMsg, nNode, nSubPos))
		{
			if (!ofs.is_open ())
			{
				return (false);
			}

			nErrCnt++;
		}

		if (ofs.is_open ())
		{
			ofs << buf.str ().c_str () << endl;
		}
	}

	return (true);
}

template <class _t_data, class _t_key, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
void CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::_swap
	(
		CBTreeAssociative<_t_data, _t_key, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer> &rContainer
	)
{
	fast_swap <_t_key **> (m_ppShortLiveKey, rContainer.m_ppShortLiveKey);
	fast_swap <_t_key **> (m_ppTempFindFirstKeyKey, rContainer.m_ppTempFindFirstKeyKey);
	fast_swap <_t_key *> (m_pRemoveKey, rContainer.m_pRemoveKey);
	fast_swap <_t_key *> (m_pTempRemoveKey, rContainer.m_pTempRemoveKey);
	fast_swap <_t_key *> (m_pInstancesNewKey, rContainer.m_pInstancesNewKey);
	fast_swap <_t_key *> (m_pTempFindFirstKeyNewKey, rContainer.m_pTempFindFirstKeyNewKey);
	fast_swap <_t_key *> (m_pAddToNodeKey, rContainer.m_pAddToNodeKey);
	fast_swap <_t_key *> (m_pGetNewKey, rContainer.m_pGetNewKey);

#if defined (_DEBUG)

	fast_swap <bool *> (m_pbShortLiveKeyInUse, rContainer.m_pbShortLiveKeyInUse);

#endif

	CBTreeBase_t	&rKeySortBase = dynamic_cast <CBTreeBase_t &> (rContainer);

	CBTreeBase_t::_swap (rKeySortBase);
}

#endif // BTREEASSOCIATIVE_CPP