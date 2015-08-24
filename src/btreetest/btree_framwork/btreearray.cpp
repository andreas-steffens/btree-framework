/************************************************************
**
** file:	btreearray.cpp
** author:	Andreas Steffens
** license:	GPL v2
**
** description:
**
** This file contains code for the b-tree framework's array data class.
**
************************************************************/

#ifndef	BTREEARRAY_CPP
#define	BTREEARRAY_CPP

#include "btreearray.h"

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::CBTreeArray
	(
		_t_datalayerproperties &rDataLayerProperties, 
		bayerTreeCacheDescription_t *psCacheDescription, 
		_t_subnodeiter nNodeSize
	)
	:	CBTreeBaseIteratorWriteAccess <CBTreeArrayPos<_t_sizetype>, _t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>
	(
		rDataLayerProperties, 
		psCacheDescription, 
		nNodeSize
	)
	,	CBTreeArrayDataIf <_t_data, _t_sizetype> ()
	,	m_pClAccessWrapper (NULL)
{
	CBTreeArrayDataIf<_t_data, _t_sizetype>	&rBtrArray = dynamic_cast <CBTreeArrayDataIf<_t_data, _t_sizetype> &> (*this);

	m_pClAccessWrapper = new CBTreeArrayAccessWrapper<_t_data, _t_sizetype> (rBtrArray);

	BTREE_ASSERT (m_pClAccessWrapper != NULL, "CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::CBTreeArray (bool, char *, bayerTreeCacheDescription_t *, _t_subnodeiter): insufficient memory!");
}
						
template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::CBTreeArray (CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer> &rBT, bool bAssign)
	:	CBTreeBaseIteratorWriteAccess <CBTreeArrayPos<_t_sizetype>, _t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>
	(
		dynamic_cast <CBTreeBaseIteratorWriteAccess <CBTreeArrayPos<_t_sizetype>, _t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer> &> (rBT)
	)
	,	CBTreeArrayDataIf <_t_data, _t_sizetype> ()
	,	m_pClAccessWrapper (NULL)
{
	CBTreeArrayDataIf<_t_data, _t_sizetype>	&rBtrArray = dynamic_cast <CBTreeArrayDataIf<_t_data, _t_sizetype> &> (*this);

	m_pClAccessWrapper = new CBTreeArrayAccessWrapper<_t_data, _t_sizetype> (rBtrArray);

	BTREE_ASSERT (m_pClAccessWrapper != NULL, "CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::CBTreeArray (bool, char *, bayerTreeCacheDescription_t *, _t_subnodeiter): insufficient memory!");

	if (bAssign)
	{
		assign (rBT);
	}
}

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::~CBTreeArray ()
{
	if (m_pClAccessWrapper != NULL)
	{
		delete m_pClAccessWrapper;
	}
}

/*

at

nPos		- specifies position of data item to retrieved or modified

This method returns the refernce of one data item associated with the linear position of nPos.

If the method was successful, then a reference to a data item is returned, otherwise
this method throws an exception of type ::std::out_of_range.

*/

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
CBTreeArrayAccessWrapper<_t_data, _t_sizetype>
CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::at (const _t_sizetype nPos)
{
	BTREE_ASSERT_EXCEPT (nPos < this->size (), ::std::out_of_range, "CBTreeArray<>::at (const _t_sizetype): nPos exceeds range!");

	m_pClAccessWrapper->set (nPos);

	return (*(m_pClAccessWrapper));
}

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
CBTreeArrayAccessWrapper<_t_data, _t_sizetype>
CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::front ()
{
	BTREE_ASSERT_EXCEPT (!this->empty (), ::std::out_of_range, "CBTreeArray<>::front (): array is empty!");

	m_pClAccessWrapper->set (0);

	return (*(m_pClAccessWrapper));
}

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
CBTreeArrayAccessWrapper<_t_data, _t_sizetype>
CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::back ()
{
	BTREE_ASSERT_EXCEPT (!this->empty (), ::std::out_of_range, "CBTreeArray<>::back (): array is empty!");

	m_pClAccessWrapper->set (this->size () - 1);

	return (*(m_pClAccessWrapper));
}

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
template <class _t_iterator>
void CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::assign (_t_iterator sItFirst, _t_iterator sItLast)
{
	this->create_root ();

	_t_sizetype	nDiff;
	_t_sizetype	nAppendix;
	bool		bSelfReverse;
	bool		bSelfReference = test_self_reference_of_iterator_to_this<_t_iterator> (sItFirst, sItLast, nDiff, nAppendix, bSelfReverse);

	if (bSelfReference)
	{
		_t_sizetype		i;
		_t_sizetype		nPos = this->size () - nAppendix;

		while (this->size () > nPos)
		{
			CBTreeArray_t::remove_at (nPos);
		}
		
		nPos = nDiff;

		while (this->size () > nPos)
		{
			CBTreeArray_t::remove_at (0);
		}

		if (bSelfReverse)
		{
			iterator			sIter = this->begin ();
			reverse_iterator	sRIter = this->rbegin ();

			_t_data				sEntry;

			for (i = 0; i < (nDiff / 2); i++)
			{
				sEntry = *sIter;

				*sIter = (_t_data)(*sRIter);

				*sRIter = sEntry;

				sIter++;
				sRIter++;
			}
		}

		return;
	}

	// remove all data in this list
	CBTreeArray_t::clear ();

	CBTreeArray_t::insert<_t_iterator> (this->cbegin (), sItFirst, sItLast);
}

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
void CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::assign (_t_sizetype nNewSize, const _t_data& rVal)
{
	// remove all data in this list
	CBTreeArray_t::clear ();

	this->create_root ();

	/*
	**	Although a b-tree guarantees that data is stored balanced; this happens under the assumption that 
	**	data entries are stored and removed in random order. In case data is stored or removed in order, the
	**	tree will become partially unblanced. To prevent this the data is not copied in order, but in a
	**	skewed fashion. The skew width is determined by the target tree's maximum node size (t * 2) and target
	**	tree's future depth (based on the source tree's size) combined, since that ensures an equal distribution
	**	of all data throughout the entire target tree.
	*/
	
	// determine initial part of skew width
	_t_sizetype			nSkewWidth = this->get_node_max_sub_nodes ();
	_t_sizetype			nEntries = 1;
	_t_sizetype			i;
	_t_sizetype			j;
	_t_sizetype			nOffset;
	_t_subnodeiter		nAverageNodeSize = this->get_node_max_sub_nodes ();

	nAverageNodeSize *= 3;
	nAverageNodeSize /= 4;

	// combine skew width with eventual target tree depth (log t of n, while t is node size and n is tree size)
	for (nSkewWidth--; nEntries <= nNewSize; nSkewWidth++)
	{
		// on average every new layer allows for t times current tree size more entries
		nEntries *= (_t_sizetype) nAverageNodeSize;
	}

	// copy data using skew width
	for (i = 0; i < nSkewWidth; i++)
	{
		for (j = i, nOffset = 0; j < nNewSize; j += nSkewWidth, nOffset++)
		{
			CBTreeArray_t::insert_at (i + (nOffset * (i + 1)), rVal);
		}
	}
}


template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
void CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::push_back (const _t_data &rData)
{
	const _t_sizetype		nPos = this->size ();
	_t_sizetype				nNewPos;

	nNewPos = CBTreeArray_t::insert_at (nPos, rData);

	BTREE_ASSERT (nNewPos == 1, "CBTreeArray<>::push_back (const _t_data &): insert_at failed to add new entry!");
}

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
void CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::pop_back ()
{
	BTREE_ASSERT ((!this->empty ()) , "CBTreeArray<>::pop_back (): method tried to remove one entry on an empty container!");

	const _t_sizetype		nPos = this->size () - 1;
	_t_sizetype				nNewPos;

	nNewPos = CBTreeArray_t::remove_at (nPos);

	BTREE_ASSERT (nNewPos == 1, "CBTreeArray<>::pop_back (): remove_at failed to remove entry on container not being empty!");
}

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
typename CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::iterator
	CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::insert
	(
		typename CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::const_iterator sCIterPos, 
		const _t_data& rData
	)
{
	this->create_root ();

	this->insert_via_reference (sCIterPos, rData, false);

	iterator		sRetval (this, false);

	sRetval = this->begin ();

	sRetval += sCIterPos.get_pos ();

	return (sRetval);
}

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
typename CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::iterator
	CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::insert
	(
		typename CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::const_iterator sCIterPos, 
		const _t_sizetype nLen, 
		const _t_data& rData
	)
{
	this->create_root ();

	_t_sizetype		i;
	iterator		sRetval (this, false);

	sRetval = this->begin ();

	sRetval += sCIterPos.get_pos ();

	for (i = 0; i < nLen; i++)
	{
		this->insert_via_reference (sCIterPos, rData);
	}

	return (sRetval);
}

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
template <class _t_iterator>
typename CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::iterator
	CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::insert
	(
		typename CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::const_iterator sCIterPos, 
		_t_iterator sItFirst, 
		_t_iterator sItLast
	)
{
	typedef typename CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::const_iterator	citer_t;
	typedef typename CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::iterator			iter_t;

	this->create_root ();

	if (sItFirst == sItLast)
	{
		iter_t		sRetval (this, false);

		sRetval = this->begin ();

		sRetval += sCIterPos.get_pos ();

		return (sRetval);
	}

	_t_sizetype	nDiff;
	_t_sizetype	nAppendix;
	bool		bSelfReverse;
	bool		bSelfReference = test_self_reference_of_iterator_to_this<_t_iterator> (sItFirst, sItLast, nDiff, nAppendix, bSelfReverse);

	if (bSelfReference)
	{
		_t_sizetype		nBlockSize = ::std::min<_t_sizetype> (8192, nDiff);
		_t_sizetype		nAllocSize = nBlockSize;
		_t_data			*pBlock;
		_t_sizetype		i;
		_t_sizetype		j;
		_t_sizetype		nStart;
		_t_sizetype		nEnd;
		_t_sizetype		nPos = sCIterPos.get_pos ();
		_t_sizetype		nLenPriorToInsert;
		_t_sizetype		nLenPastInsert;
		_t_sizetype		nChunkSize;
		citer_t			sCIterTarget = sCIterPos;

		nStart = this->size () - nDiff - nAppendix;
		nEnd = this->size () - nAppendix;

		if (bSelfReverse)
		{
			nStart = this->size () - nStart;
			nEnd = this->size () - nEnd;

			nStart = nEnd ^ nStart;
			nEnd = nEnd ^ nStart;
			nStart = nEnd ^ nStart;
		}
		
		if ((nStart < nPos) && (nEnd < nPos))
		{
			nLenPriorToInsert = nDiff;
			nLenPastInsert = 0;
		}
		else if ((nStart >= nPos) && (nEnd > nPos))
		{
			nLenPriorToInsert = 0;
			nLenPastInsert = nDiff;
		}
		else
		{
			nLenPriorToInsert = nPos - nStart;
			nLenPastInsert = nEnd - nPos;
		}

		do
		{
			nBlockSize = nAllocSize;

			pBlock = (_t_data *) calloc ((size_t) nAllocSize, sizeof (_t_data));

			nAllocSize /= 2;

			BTREE_ASSERT (nAllocSize > 0, "CBTreeArray<>::insert (const_iterator, _t_iterator, _t_iterator): insufficient memory!");
		} while (pBlock == NULL);

		if (!bSelfReverse)
		{
			for (i = 0; i < nLenPriorToInsert; i += nChunkSize)
			{
				nChunkSize = ::std::min<_t_sizetype> (nBlockSize, nLenPriorToInsert - i);

				this->serialize (nStart + i, nChunkSize, pBlock);

				for (j = nChunkSize; j > 0;)
				{
					j--;

					this->insert_via_reference (sCIterTarget, pBlock[j]);
				}

				sCIterTarget += nChunkSize;
			}

			nLenPriorToInsert *= 2;

			for (i = 0; i < nLenPastInsert; i += nChunkSize)
			{
				nChunkSize = ::std::min<_t_sizetype> (nBlockSize, nLenPastInsert - i);

				this->serialize (nLenPriorToInsert + nStart + i, nChunkSize, pBlock);

				for (j = nChunkSize; j > 0;)
				{
					j--;

					this->insert_via_reference (sCIterTarget, pBlock[j]);
				}

				nLenPriorToInsert += nChunkSize;
				sCIterTarget += nChunkSize;
			}
		}
		else
		{
			for (i = 0; i < nLenPriorToInsert; i += nChunkSize)
			{
				nChunkSize = ::std::min<_t_sizetype> (nBlockSize, nLenPriorToInsert - i);

				this->serialize (nStart + i, nChunkSize, pBlock);

				for (j = 0; j < nChunkSize; j++)
				{
					this->insert_via_reference (sCIterTarget, pBlock[j]);
				}
			}

			nLenPriorToInsert *= 2;

			for (i = 0; i < nLenPastInsert; i += nChunkSize)
			{
				nChunkSize = ::std::min<_t_sizetype> (nBlockSize, nLenPastInsert - i);

				this->serialize (nLenPriorToInsert + nStart + i, nChunkSize, pBlock);

				for (j = 0; j < nChunkSize; j++)
				{
					this->insert_via_reference (sCIterTarget, pBlock[j]);
				}

				nLenPriorToInsert += nChunkSize;
			}
		}

		free ((void *) pBlock);

		iter_t		sRetval (this, false);

		sRetval = this->begin ();

		sRetval += sCIterPos.get_pos ();

		return (sRetval);
	}
	else
	{
		typename::std::iterator_traits<_t_iterator>::iterator_category	sIterCategory;

		return (this->insert_via_iterator_tag (sCIterPos, sItFirst, sItLast, sIterCategory));
	}
}

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
typename CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::iterator
	CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::erase
	(
		typename CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::const_iterator sCIterPos
	)
{
	typedef typename CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::iterator			iter_t;

	this->erase_via_reference (sCIterPos, false);

	iter_t		sRetval (this, false);

	sRetval = this->begin ();

	sRetval += sCIterPos.get_pos ();

	return (sRetval);
}

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
typename CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::iterator
	CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::erase
	(
		typename CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::const_iterator sCIterFirst,
		typename CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::const_iterator sCIterLast
	)
{
	typedef typename CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::iterator			iter_t;

	iter_t		sRetval (this, false);

	sRetval = this->begin ();

	sRetval += sCIterFirst.get_pos ();

	if (sCIterFirst == sCIterLast)
	{
		return (sRetval);
	}

	_t_sizetype		nDiff = sCIterLast - sCIterFirst;
	_t_sizetype		i;

	for (i = 0; i < nDiff; i++)
	{
		this->erase_via_reference (sCIterFirst);
	}

	return (sRetval);
}

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
void CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::swap (CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer> &rArray)
{
	if (this != &rArray)
	{
		fast_swap<uint32_t> (this->m_nPoolIDserialVector, rArray.m_nPoolIDserialVector);
//		fast_swap<CBTreeArrayAccessWrapper<_t_data, _t_sizetype> *> (this->m_pClAccessWrapper, rArray.m_pClAccessWrapper);

		CBTreeBase_t	&rThisBase = dynamic_cast <CBTreeBase_t &> (*this);
		CBTreeBase_t	&rArrayBase = dynamic_cast <CBTreeBase_t &> (rArray);

		rThisBase.swap (rArrayBase);
	}
}

/*

insert_at - insert data at position

nPos		- 
rData		- data set to be added

This method adds one entry at position nPos.

If the method was successful, then the return value is the position of the newly added
entry, otherwise the return value has all bits set ((_t_sizetype) ~0).

*/

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
_t_sizetype CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::insert_at (const _t_sizetype nPos, const _t_data &rData)
{
	uint64_t						retval = nPos;
	CBTreeArrayPos<_t_sizetype>		sPos;
	
	this->create_root ();

	sPos.nIndex = retval;

	retval = this->add_to_node (sPos, rData, this->m_nRootNode, 0);

	return (retval);
}

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
_t_sizetype CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::replace_at (const _t_sizetype nStart, const _t_sizetype nLen, _t_data *pSrcData)
{
	CBTreeArrayPos <_t_sizetype>	sPos;
	_t_sizetype						nRetval;

	/*
	**	The actual serialize process is done by CBTreeBase::serialize.
	**	All this method does is to convert nFrom and nTo into the template parameter _ti_pos (CBTreeArrayPos <_t_sizetype>)
	**	and nLen. This has to be done, since CBTreeBase::serialize has no concept of what an _t_sizetype in terms of a position is.
	*/

	sPos.nIndex = nStart;

	nRetval = CBTreeBase<CBTreeArrayPos <_t_sizetype>, _t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::serialize (sPos, nLen, pSrcData, false);

	return (nRetval);
}

/*

remove_at - remove entry at position

nPos		- specifies position where entry is to be removed

This method removes the entry at the specified position.

If the method was successful, then the return value is the position of the removed
entry, otherwise the return value has all bits set ((_t_sizetype) ~0).

*/

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
_t_sizetype CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::remove_at (const _t_sizetype nPos)
{
	_t_sizetype						nRetval = nPos;
	CBTreeArrayPos<_t_sizetype>		sPos;

#if defined (_DEBUG)
	BTREE_ASSERT (this->empty () == false, "CBTreeBase<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::remove_at: cannot remove entry from empty list");
	BTREE_ASSERT (nPos < this->size (), "CBTreeBase<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::remove_at: position exceeds maximum entries");
#endif

	if (this->m_pData == NULL)
	{
		nRetval = (_t_sizetype) ~0x0;
	}
	else
	{
		sPos.nIndex = nPos;

		nRetval = this->remove_from_node (sPos, this->m_nRootNode, 0);
	}

	return (nRetval);
}

/*

clear - remove all

This method removes all data by dstroying the data layer.

If successfully this method returns true, otherwise false.

*/
template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
void CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::clear ()
{
	CBTreeBase<CBTreeArrayPos <_t_sizetype>, _t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::clear ();
}

/*

serialize - serialize

The serialize method reads out data items from position nFrom to position nTo - 1 and writes the
return data into an array pData is poiting at. It is assumed by this method that the array is large enough
to contain all data that will potentially be written into it, otherwise memory regions not associated with
pData get overwritten.

nStart		- specifies position of initial entry to be serialized
nLen		- specifies number of entries to be serialized
pData		- pointer to array where the serialized data will be copied to

This method returns the number of items that have been written to the array pData is pointing at.

*/

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
_t_sizetype CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::serialize (const _t_sizetype nStart, const _t_sizetype nLen, _t_data *pData)
{
	CBTreeArrayPos <_t_sizetype>	sPos;

	/*
	**	The actual serialize process is done by CBTreeBase::serialize.
	**	All this method does is to convert nFrom and nTo into the template parameter _ti_pos (CBTreeArrayPos <_t_sizetype>)
	**	and nLen. This has to be done, since CBTreeBase::serialize has no concept of what an _t_sizetype in terms of a position is.
	*/

	sPos.nIndex = nStart;

	return (CBTreeBase<CBTreeArrayPos <_t_sizetype>, _t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::serialize (sPos, nLen, pData));
}

/*

operator= - assignment operator overload

rBT		- is a reference to a b-tree that will have its content be assigned to this instance

The result is a reference to this instance.

*/

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer> &CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::operator=
	(CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer> &rBT)
{
	// if this is not the same instance as the referenced b-tree (rBT) ...
	if (this != &rBT)
	{
		// ... then destroy this data layer
		this->clear ();

		// and copy all data from rBT to this instance
		assign (rBT);
	}

	return (*this);
}

/*

operator[] - subscription operator overload (write)

nPos	- specifies the linear position of the entry to be written to

The result is an instance to CBTreeArrayAccessWrapper, which will manage the write.

Note:	The class CBTreeArrayAccessWrapper has a cast operator, which cast CBTreeArrayAccessWrapper
		to _t_data. This way the compiler can distinguish between read and write
		accesses, when subscriptions are employed.

*/

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
CBTreeArrayAccessWrapper<_t_data, _t_sizetype>
	CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::operator[] (const _t_sizetype nPos)
{
	m_pClAccessWrapper->set (nPos);

	return (*m_pClAccessWrapper);
}

/*

set_at - set data at specified position

nPos		- specifies the position of the entry to be set with new data
rData		- contains the data to replace the entry data at the specified position

The entry at the specified position gets replaced with the data of the parameter obj.

If successful true is returned, otherwise false.

*/

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
bool CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::set_at (const _t_sizetype nPos, const _t_data &rData)
{
	bool				retval = false;
	_t_nodeiter			nNode;
	_t_subnodeiter		nSubPos;
	
	this->create_root ();

	if (nPos < this->size ())
	{
		this->convert_pos_to_container_pos (this->m_nRootNode, nPos, nNode, nSubPos);

		this->set_data (nNode, nSubPos, rData);

		retval = true;
	}
	
	return (retval);
}

/*

get_at - retrieves data from specified position

nPos			- specifies the position of the entry to be retrieved

The entry at the specified position is returned.

If successful true is returned, otherwise false.

*/

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
bool CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::get_at (const _t_sizetype nPos, _t_data &rData)
{
	bool			retval = false;
	_t_nodeiter		nNode;
	_t_subnodeiter	nSubPos;

	if (this->m_pData != NULL)
	{
		if (nPos < this->size ())
		{
			this->convert_pos_to_container_pos (this->m_nRootNode, nPos, nNode, nSubPos);

			rData = this->get_data (nNode, nSubPos);

			retval = true;
		}
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

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
CBTreeArrayPos<_t_sizetype> CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::determine_position (CBTreeArrayPos<_t_sizetype> sPos, _t_nodeiter nNode, _t_subnodeiter &nSubPos, _t_subnodeiter &nSubData, bool &bFound)
{
	_t_sizetype			nMaxIdx;
	node_t				sNodeDesc;

	if (this->is_leaf (nNode))
	{
		nSubData = (_t_subnodeiter) sPos.nIndex;

		bFound = true;
	}
	else
	{
		bFound = false;

		this->get_node (nNode, sNodeDesc);

		// determine which subnode (nSubPos) is to enter
		// sPos will return as the number of data items before the selected sub node, including data from this node
		nSubData = nSubPos = this->find_next_sub_pos (nNode, sPos); // <- note: sPos is an input/output parameter

		// determine size of sub node
		nMaxIdx = this->get_max_index (this->get_sub_node (nNode, nSubPos));

#if defined (_DEBUG)
		BTREE_ASSERT (sPos.nIndex <= nMaxIdx, "CBTreeArray::determine_position: position exceeds sub node size");
#endif

		// if the offset inside the next sub node exceeds the next sub node's size by one ...
		if (sPos.nIndex == nMaxIdx)
		{
			// ... then the data to be deleted exists in the current node
			bFound = true;
		}

		// if select sub-node is outside of the current node ...
		if (nSubPos >= this->get_data_count (sNodeDesc))
		{
			// ... then correct to most right sub-node
			nSubData--;
		}
	}

	return (sPos);
}

/*

rebuild_node - update maximum index

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

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
void CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::rebuild_node (const _t_nodeiter nNode, const int32_t triMod, _t_subnodeiter nSubStart)
{
#if defined (_DEBUG)
	BTREE_ASSERT (nNode < this->m_nTreeSize, "CBTreeBase<_ti_pos, _t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayer>::rebuild_node: requested node exceeds tree size");
#endif

	_t_nodeiter									nSubNode;
	node_t										sNodeDesc;
	_t_sizetype									nIdx = (_t_sizetype) 0;
	_t_subnodeiter								ui32;
	_t_subnodeiter								nSubPosOffset;

	this->get_node (nNode, sNodeDesc);

	if (this->is_leaf (nNode))
	{
		nIdx = ((_t_subnodeiter) (0 - sNodeDesc.nNumData));
	}
	else
	{
		this->get_serVector (nNode, this->m_pSerVector);

		if (nSubStart == 0)
		{
			nSubPosOffset = 0;
			nIdx = 0;
		}
		else
		{
			nSubPosOffset = nSubStart - 1;
			nIdx = this->m_pSerVector[nSubPosOffset] - nSubPosOffset;
		}

		this->m_pData->set_cacheFreeze (true);
		{
			for (ui32 = nSubStart; ui32 < this->get_sub_node_count (sNodeDesc); ui32++)
			{
				nSubNode = this->get_sub_node (nNode, ui32);
				nIdx += this->get_max_index (nSubNode);
			
				if (ui32 < this->get_data_count (nNode))
				{
					this->m_pSerVector[ui32] = nIdx + ui32;
				}
			}
		}
		this->m_pData->set_cacheFreeze (false);

		nIdx += this->get_data_count (sNodeDesc);

		this->set_serVector (nNode, this->m_pSerVector);
	}

	sNodeDesc.nMaxIdx = nIdx;

	this->set_node (nNode, sNodeDesc);
}

/*

generate_prev_position - generate previous position

This method returns the previous position (CBTreeBase::_ti_pos = CBTreeArrayPos<_t_sizetype>)
based on the parameter sPos and the node / sub-node tuple associated with sPos.

nNode		- specifies the node of the node / sub-position tuple of which the previous position will be generated from
nSub		- specifies the sub_position of the node / sub-position tuple of which the previous position will be generated from
sPos		- class specific position associated with node / sub-node tuple

The return value is the previous linear position of sPos (nNode, nSub) in terms of how data is
presented to the application. Given that the b-tree classes are supposed to act like a linear
list to calling the application, this pseudo code displays what generate_prev_position does:

return_value = (*this)[sPos (this, nNode, nSub) - 1];

*/

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
CBTreeArrayPos<_t_sizetype> CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::generate_prev_position (const _t_nodeiter nNode, const _t_subnodeiter nSub, CBTreeArrayPos<_t_sizetype> sPos)
{
#if defined (_DEBUG)
	BTREE_ASSERT (!this->is_leaf (nNode), "CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::generate_prev_position: This method cannot be used on leaf nodes!");
	BTREE_ASSERT (sPos.nIndex > 0, "CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::generate_prev_position: Cannot generate previous position from position 0!");
#endif

	sPos.nIndex--;

	return (sPos);
}

/*

generate_next_position - generate next position

This method returns the next position (CBTreeBase::_ti_pos = CBTreeArrayPos<_t_sizetype>)
based on the parameter sPos and the node / sub-node tuple associated with sPos.

nNode		- specifies the node of the node / sub-position tuple of which the next position will be generated from
nSub		- specifies the sub_position of the node / sub-position tuple of which the next position will be generated from
sPos		- class specific position associated with node / sub-node tuple

The return value is the next linear position of sPos (nNode, nSub) in terms of how data is
presented to the application. Given that the b-tree classes are supposed to act like a linear
list to calling the application, this pseudo code displays what generate_prev_position does:

return_value = (*this)[sPos (this, nNode, nSub) + 1];

*/

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
CBTreeArrayPos<_t_sizetype> CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::generate_next_position (_t_nodeiter nNode, _t_subnodeiter nSub, CBTreeArrayPos<_t_sizetype> sPos)
{
#if defined (_DEBUG)
	BTREE_ASSERT (!this->is_leaf (nNode), "CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::generate_next_position: This method cannot be used on leaf nodes!");
#endif

	sPos.nIndex++;

	return (sPos);
}

/*

convert_pos_to_container_pos - linearly access data

This method steps into a b-tree and finds the node and sub-position where the data associated
with the linear address nPos is stored. Dependent on the parameter bReadOpr the data from that
location is either copied from the b-tree into sData or from sData into the b-tree.

nNode			- specifies the next node to go into
nPos			- specifies the linear address of the data entry within the next node
sData			- read / write data of access
bReadOpr		- if true the access is a read operation, otherwise it is a write operation

*/

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
void CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::convert_pos_to_container_pos (_t_nodeiter nNode, _t_sizetype nPos, _t_nodeiter &rRsltNode, _t_subnodeiter &rRsltSubPos)
{
	_t_subnodeiter							ui32;
	_t_subnodeiter							nNumSubNodes;
	_t_subnodeiter							nNumData;
	bool									isLeaf = this->is_leaf (nNode);
	CBTreeArrayPos<_t_sizetype>				sPos;

	// node is not a leaf node ...
	if (!isLeaf)
	{
		// ... then continue searching in this node as well as the sub-nodes
		nNumData = this->get_data_count (nNode);
		nNumSubNodes = this->get_sub_node_count (nNode);

		sPos.nIndex = nPos;

		// identify next sub-node to search in
		ui32 = this->find_next_sub_pos (nNode, sPos);

		// if data is in this node ...
		if ((ui32 < nNumData) && (nPos == this->m_pSerVector[ui32]))
		{
			// ... then return immediately with result
			rRsltNode = nNode;
			rRsltSubPos = ui32;
		}
		else
		{
			// otherwise step into next sub-node

			// if initial sub-node needs to be accessed ...
			if (ui32 == 0)
			{
				// ... then the serial vector is not involved to calculate the next linear offset
				this->convert_pos_to_container_pos (this->get_sub_node (nNode, ui32), nPos, rRsltNode, rRsltSubPos);
			}
			else
			{
				this->convert_pos_to_container_pos (this->get_sub_node (nNode, ui32), nPos - (this->m_pSerVector[ui32 - 1] + 1), rRsltNode, rRsltSubPos);
			}
		}
	}
	else
	{
		// linear access to leaf nodes are handled in CBTreeBase to avoid redundant code
		CBTreeBase<CBTreeArrayPos <_t_sizetype>, _t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::convert_pos_to_container_pos (nNode, nPos, rRsltNode, rRsltSubPos);
	}
}

/*

find_next_sub_pos - find next sub-position

To find the sub-position of the nearest greater offset of what sPos is displaying
within a node, this method ought to be used.

nNode		- specifies the node in which the nearest greater offset is to be sought in
sPos		- specifes the offset

The value returned is the sub-position, which has the nearest greater offset displayed by sPos.

*/

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
_t_subnodeiter CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::find_next_sub_pos (const _t_nodeiter nNode, CBTreeArrayPos<_t_sizetype> &sPos)
{
	// sPos is an input output parameter
	// input	- absolute index within this node
	// output	- if sub node was found then index of sub node, otherwise zero

	node_t					sNodeDesc;
	_t_subnodeiter			nRetval;
	_t_sizetype				nDiff;
#if defined (WIN32)
	uint32_t				*pDiff = (uint32_t *) &nDiff;
#endif

	// node is a leave node ...
	if (this->is_leaf (nNode))
	{
		// ... then return immediately with input index
		nRetval = (_t_subnodeiter) sPos.nIndex;

		sPos.nIndex = (_t_sizetype) 0;
	}
	else
	{
		this->get_node (nNode, sNodeDesc);

		// load node's serial vector
		this->get_serVector (nNode, this->m_pSerVector);

		uint32_t	ui32, nMinPos, nMaxPos;

		// set range up
		nMinPos = 0UL;

		nMaxPos = this->get_data_count (sNodeDesc);

		// until nearest sub postion has been found ...
		while (nMinPos != nMaxPos)
		{
			// sub divide range and determine average middle position
			ui32 = (nMinPos + nMaxPos) / 2;

			// determine difference between current middle position's index and input index
			nDiff = this->m_pSerVector[ui32] - sPos.nIndex;

			// if current middle position's index is beyond input index ...
#if defined (WIN32)
			if (pDiff[1] & 0x80000000)
#elif defined (LINUX)
			if (nDiff & 0x8000000000000000ULL)
#endif
			{
				// ... then range minimum assumes next position after middle position
				nMinPos = ui32 + 1;
			}
			else
			{
				// ... otherwise range maximum assumes middle position
				nMaxPos = ui32;
			}
		}

		nRetval = nMinPos;

		// if returned sub position is not the initial position ...
		if (nMinPos > 0)
		{
			// ... then subtract sub position's serial vector entry from input index
			sPos.nIndex -= this->m_pSerVector[nMinPos - 1] + 1;

			// Note: The initial sub node's position in the serial vector list would always be zero and is therefore not part of the serial vector.
		}
	}

	return (nRetval);
}

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
bool CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::showdata (std::ofstream &ofs, const _t_nodeiter nNode, const _t_subnodeiter nSubPos)
{
	return (true);
}

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
void CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::assign
	(CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer> &rBT)
{
	// if the source contains no data ...
	if (rBT.size () == 0)
	{
		// ... then remove all data in this list
		this->clear ();

		return;
	}

	/*
	**	Although a b-tree guarantees that data is stored balanced; this happens under the assumption that 
	**	data entries are stored and removed in random order. In case data is stored or removed in order, the
	**	tree will become partially unblanced. To prevent this the data is not copied in order, but in a
	**	skewed fashion. The skew width is determined by the target tree's maximum node size (t * 2) and target
	**	tree's future depth (based on the source tree's size) combined, since that ensures an equal distribution
	**	of all data throughout the entire target tree.
	*/
	
	// determine initial part of skew width
	_t_sizetype			nSkewWidth = this->get_node_max_sub_nodes ();
	_t_sizetype			nEntries = 1;
	_t_sizetype			i;
	_t_sizetype			j;
	_t_sizetype			nOffset;
	_t_data				sData;
	_t_subnodeiter		nAverageNodeSize = this->get_node_max_sub_nodes ();

	nAverageNodeSize *= 3;
	nAverageNodeSize /= 4;

	// combine skew width with eventual target tree depth (log t of n, while t is node size and n is tree size)
	for (nSkewWidth--; nEntries <= rBT.size (); nSkewWidth++)
	{
		// on average every new layer allows for t times current tree size more entries
		nEntries *= (_t_sizetype) nAverageNodeSize;
	}

	// copy data using skew width
	for (i = 0; i < nSkewWidth; i++)
	{
		for (j = i, nOffset = 0; j < rBT.size (); j += nSkewWidth, nOffset++)
		{
			rBT.get_at (j, sData);

			insert_at (i + (nOffset * (i + 1)), sData);
		}
	}
}

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
template <class _t_iterator>
typename CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::iterator
	CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::insert_via_iterator_tag
	(
		typename CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::const_iterator sCIterPos, 
		_t_iterator sItFirst, 
		_t_iterator sItLast, 
		::std::forward_iterator_tag
	)
{
	typedef typename CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::const_iterator	citer_t;
	typedef typename CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::iterator			iter_t;

	iter_t				sRetval (this, false);
	citer_t				sCIterTarget (this, false);
	_t_data				sData;
	
	_t_iterator			sIt;

	sCIterTarget = sCIterPos;

	for (sIt = sItFirst; sIt != sItLast; sIt++)
	{
		sData = *sIt;

		insert (sCIterTarget, sData);

		sCIterTarget++;
	}
	
	sRetval = this->begin ();

	sRetval += sCIterPos.get_pos ();

	return (sRetval);
}

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
template <class _t_iterator>
typename CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::iterator
	CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::insert_via_iterator_tag
	(
		typename CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::const_iterator sCIterPos, 
		_t_iterator sItFirst, 
		_t_iterator sItLast, 
		::std::random_access_iterator_tag
	)
{
	typedef typename CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::const_iterator	citer_t;
	typedef typename CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::iterator			iter_t;

	/*
	**	Although a b-tree guarantees that data is stored balanced; this happens under the assumption that 
	**	data entries are stored and removed in random order. In case data is stored or removed in order, the
	**	tree will become partially unblanced. To prevent this the data is not copied in order, but in a
	**	skewed fashion. The skew width is determined by the target tree's maximum node size (t * 2) and target
	**	tree's future depth (based on the source tree's size) combined, since that ensures an equal distribution
	**	of all data throughout the entire target tree.
	*/

	// determine initial part of skew width
	iter_t				sRetval (this, false);
	_t_iterator			sIt;
	citer_t				sCIterTarget (this, false);
	_t_sizetype			nNewSize = ::std::distance <_t_iterator> (sItFirst, sItLast);
	_t_sizetype			nSkewWidth = this->get_node_max_sub_nodes ();
	_t_sizetype			nEntries = 1;
	_t_sizetype			i;
	_t_sizetype			j;
	_t_sizetype			nOffset;
	_t_data				sData;
	_t_subnodeiter		nAverageNodeSize = this->get_node_max_sub_nodes ();

	nAverageNodeSize *= 3;
	nAverageNodeSize /= 4;

	// combine skew width with eventual target tree depth (log t of n, while t is node size and n is tree size)
	for (nSkewWidth--; nEntries <= nNewSize; nSkewWidth++)
	{
		// on average every new layer allows for t times current tree size more entries
		nEntries *= (_t_sizetype) nAverageNodeSize;
	}

	// copy data using skew width
	for (i = 0; i < nSkewWidth; i++)
	{
		sIt = sItFirst;

		::std::advance<_t_iterator> (sIt, (typename ::std::iterator_traits<_t_iterator>::difference_type) i);

		for (j = i, nOffset = 0; j < nNewSize; nOffset++)
		{
			sData = *sIt;

			sCIterTarget = sCIterPos;

			sCIterTarget += i + (nOffset * (i + 1));

			insert (sCIterTarget, sData);

			j += nSkewWidth;

			if (j < nNewSize)
			{
				// some containers (like ::std::vector) cannot operate outside their range
				::std::advance<_t_iterator> (sIt, (typename ::std::iterator_traits<_t_iterator>::difference_type) nSkewWidth);
			}
		}
	}

	sRetval = this->begin ();

	sRetval += sCIterPos.get_pos ();

	return (sRetval);
}

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
void CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::insert_via_reference (const_iterator &rCIterPos, const _t_data& rData, bool bReEvaluate)
{
	bool			bFallBack = true;

	// if the iterator is associated with this btree ...
	if (this == rCIterPos.get_container ())
	{
		// ... and the iterator is ready for use ...
		if (rCIterPos.is_evaluated ())
		{
			// ... and if btree is not empty ...
			if (!this->empty ())
			{
				// ... and if the node to be modified is a leaf node ...
				if (this->is_leaf (rCIterPos.get_node ()))
				{
					// ... and if the node to be modified has enough space to take another entry ...
					if (this->get_data_count (rCIterPos.get_node ()) < this->get_node_max_data_size ())
					{
						// ... then an additional entry can be added fast
						_t_nodeiter			nNode;
						_t_subnodeiter		nSubPos;

						bFallBack = false;

#if defined (_DEBUG)

						BTREE_ASSERT (rCIterPos.get_sub_pos () <= this->get_data_count (rCIterPos.get_node ()), "CBTreeArray<>::insert_via_reference (const_iterator &, const _t_data&): ERROR: iterator not up-to-date!");

#endif

						// insert entry into leaf node
						nSubPos = this->insert_data_into_node (rCIterPos.get_node (), rCIterPos.get_sub_pos (), rData, (_t_nodeiter) ~0x0, -1);

						// rebuild node integrity of all parent nodes by back-tracing to the root node
						nNode = rCIterPos.get_node ();

						while (nNode != this->m_nRootNode)
						{
							nNode = this->get_parent (nNode);

							this->rebuild_node (nNode, 1);
						}

						// update time stamp
						this->update_time_stamp ();

						// overwrite iterator time stamp directly, without having the iterator to evaluate again
						rCIterPos.set_time_stamp (this);
					}
				}
			}
		}
	}

	// if fast insert was not possible ...
	if (bFallBack)
	{
		// ... then perform regular insert
		CBTreeArray::insert_at (rCIterPos.get_pos (), rData);

		// iterator reference is used for more than one access ...
		if (bReEvaluate)
		{
			// ... then prepare iterator for next access
			rCIterPos.sync ();
		}
	}
}

template <class _t_data, class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
void CBTreeArray<_t_data, _t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>::erase_via_reference (const_iterator &rCIterPos, bool bReEvaluate)
{
	bool			bFallBack = true;
	
	// if the iterator is associated with this btree ...
	if (this == rCIterPos.get_container ())
	{
		// ... and the iterator is ready for use ...
		if (rCIterPos.is_evaluated ())
		{
			// ... and if the node to be modified is a leaf node ...
			if (this->is_leaf (rCIterPos.get_node ()))
			{
				// ... and if the node to be modified has enough entries left ...
				if (this->get_data_count (rCIterPos.get_node ()) > (this->get_node_max_data_size () / 2))
				{
					// ... then an additional entry can be added fast
					_t_nodeiter			nNode;

					bFallBack = false;

					// insert entry into leaf node
					this->remove_data_from_leaf (rCIterPos.get_node (), rCIterPos.get_sub_pos ());

					// rebuild all parent node's integrity by back-tracing to the root node
					nNode = rCIterPos.get_node ();

					while (nNode != this->m_nRootNode)
					{
						nNode = this->get_parent (nNode);

						this->rebuild_node (nNode, -1);
					}

					// update time stamp
					this->update_time_stamp ();

					// overwrite iterator time stamp directly, without having the iterator to evaluate again
					rCIterPos.set_time_stamp (this);
				}
			}
		}
	}

	// if fast erase was not possible ...
	if (bFallBack)
	{
		// ... then perform regular erase
		CBTreeArray_t::remove_at (rCIterPos.get_pos ());

		// iterator reference is used for more than one access ...
		if (bReEvaluate)
		{
			// ... then prepare iterator for next access
			rCIterPos.sync ();
		}
	}
}

/**********************************************************************************************/

/*

The class' CBTreeArrayAccessWrapper purpose is to help the compiler to distinguish between
CBTreeArray::operator[] reads and writes, since the afore mentioned operator is
helping that. 
It is required to have that distingtion, because dependent on what datalayer type is
in use the returned reference might be a reference to a cache line, which needs
to be managed in terms of unloading unwanted data residing in that cache line and
reloading the actual data in question. On a higher level this is managed by get_at
and set_at, thus the two different routes.

To clearify, this is how reads work:
(const _t_data &) = ((*this)[(const _t_sizetype) nOffset]) (_t_data sData; get_at (nOffset, sData); return (sData))

This is how writes work:
1) (CBTreeArrayAccessWrapper) = CBTreeArray::operator[const _t_sizetype nOffset] creates an instance of CBTreeArrayAccessWrapper
	The constructor of CBTreeArrayAccessWrapper takes *this as a reference (m_rInstance)
	and the parameter nOffset becoming (m_nPos).
2) CBTreeArrayAccessWrapper::operator= (const _t_data &rData) takes the reference to the data to be written
	and uses the instance of CBTreeArray and the copy of nOffset, which have been taken by the
	constructor before, to call set_at (m_rInstance.set_at (m_nPos, rData))

*/

template <class _t_data, class _t_sizetype>
CBTreeArrayConstAccessWrapper<_t_data, _t_sizetype>::CBTreeArrayConstAccessWrapper
	(
		CBTreeArrayDataIf<_t_data, _t_sizetype>	&rInstance
	)
	:	m_rInstance (rInstance)
	,	m_nPos (0)
{
}

template <class _t_data, class _t_sizetype>
CBTreeArrayConstAccessWrapper<_t_data, _t_sizetype>::~CBTreeArrayConstAccessWrapper ()
{
}

template <class _t_data, class _t_sizetype>
void CBTreeArrayConstAccessWrapper<_t_data, _t_sizetype>::set (const _t_sizetype nPos)
{
	this->m_nPos = nPos;
}

template <class _t_data, class _t_sizetype>
_t_data & CBTreeArrayConstAccessWrapper<_t_data, _t_sizetype>::operator* ()
{
	bool		bRslt;

	bRslt = m_rInstance.get_at (this->m_nPos, this->m_sData);

	BTREE_ASSERT (bRslt, "CBTreeArrayAccessWrapper<>::operator* (): get_at was not successful!");

	return (this->m_sData);
}

template <class _t_data, class _t_sizetype>
_t_data & CBTreeArrayConstAccessWrapper<_t_data, _t_sizetype>::operator-> ()
{
	return (*this);
}

template <class _t_data, class _t_sizetype>
CBTreeArrayConstAccessWrapper<_t_data, _t_sizetype>::operator const _t_data& ()
{
	bool		bRslt;

	bRslt = m_rInstance.get_at (this->m_nPos, this->m_sData);

	BTREE_ASSERT (bRslt, "CBTreeArrayConstAccessWrapper<>::operator const _t_data& (): get_at was not successful!");

	return (this->m_sData);
}

/************************************************************/

template <class _t_data, class _t_sizetype>
CBTreeArrayAccessWrapper<_t_data, _t_sizetype>::CBTreeArrayAccessWrapper
	(
		CBTreeArrayDataIf<_t_data, _t_sizetype>	&rInstance
	)
	:	CBTreeArrayConstAccessWrapper<_t_data, _t_sizetype> (rInstance)
{
}

template <class _t_data, class _t_sizetype>
CBTreeArrayAccessWrapper<_t_data, _t_sizetype>::~CBTreeArrayAccessWrapper ()
{
}

template <class _t_data, class _t_sizetype>
CBTreeArrayAccessWrapper<_t_data, _t_sizetype> &CBTreeArrayAccessWrapper<_t_data, _t_sizetype>::operator=
	(const _t_data &rData)
{
	bool		bRslt;

	bRslt = this->m_rInstance.set_at (this->m_nPos, rData);

	BTREE_ASSERT (bRslt, "CBTreeArrayAccessWrapper<>::operator= (const _t_data &): set_at was not successful!");

	return (*this);
}

template <class _t_data, class _t_sizetype>
CBTreeArrayAccessWrapper<_t_data, _t_sizetype> &CBTreeArrayAccessWrapper<_t_data, _t_sizetype>::operator=
	(const CBTreeArrayAccessWrapper<_t_data, _t_sizetype> &rData)
{
	if (this != &rData)
	{
		_t_data		sDataTmp;
		bool		bRslt;

		bRslt = rData.m_rInstance.get_at (rData.m_nPos, sDataTmp);

		BTREE_ASSERT (bRslt, "CBTreeArrayAccessWrapper<>::operator= (const CBTreeArrayAccessWrapper<> &): get_at was not successful!");

		*this = sDataTmp;
	}

	return (*this);
}

#endif // BTREEARRAY_CPP