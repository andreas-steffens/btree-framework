/************************************************************
**
** file:	btreemultimaptestwrapper.cpp
** author:	Andreas Steffens
** license:	GPL v2
**
** description:
**
** This file contains the definition of a multi map test class 
** wrapping accesses to a multi map application class instance and
** a reference container instance, while making sure the
** multi map instance acts the same way as the reference.
**
************************************************************/

#ifndef	BTREEMULTIMAPTESTWRAPPER_CPP
#define	BTREEMULTIMAPTESTWRAPPER_CPP

#include "btreemultimaptestwrapper.h"

template <class _t_data, class _t_value, class _t_ref_container>
CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::CBTreeMultiMapTestWrapper (const uint32_t nNodeSize, const uint32_t nPageSize)
	:	CBTreeAssociativeTestWrapper<_t_data, _t_value, _t_ref_container> (nNodeSize, nPageSize)
{
	this->m_nNumContainers = CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::m_nNumContainersMM;

	this->instantiate_reference_container ();

	this->init_containers (this->m_nNodeSize, this->m_nPageSize);

	this->transfer_containers ();
}

template <class _t_data, class _t_value, class _t_ref_container>
CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::CBTreeMultiMapTestWrapper (const CBTreeMultiMapTestWrapper &rContainer)
	:	CBTreeAssociativeTestWrapper<_t_data, _t_value, _t_ref_container> (rContainer)
{
	this->m_nNumContainers = CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::m_nNumContainersMM;

	this->instantiate_reference_container ();

	this->init_containers (rContainer);

	this->transfer_containers ();

	this->test ();
}

template <class _t_data, class _t_value, class _t_ref_container>
CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::~CBTreeMultiMapTestWrapper ()
{
}

template <class _t_data, class _t_value, class _t_ref_container>
template<class _t_iterator>
void CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::insert (_t_iterator sIterFirst, _t_iterator sIterLast)
{
	uint32_t		i = 0;

	this->m_pReference->insert (sIterFirst, sIterLast);

	m_pContainerRAM6565_n->insert (sIterFirst, sIterLast); i++;
	m_pContainerRAM6555_n->insert (sIterFirst, sIterLast); i++;
	m_pContainerRAM5555_n->insert (sIterFirst, sIterLast); i++;
	m_pContainerRAM5554_n->insert (sIterFirst, sIterLast); i++;
	m_pContainerRAM5454_n->insert (sIterFirst, sIterLast); i++;
	m_pContainerRAM5444_n->insert (sIterFirst, sIterLast); i++;
	m_pContainerRAM4444_n->insert (sIterFirst, sIterLast); i++;
	m_pContainerRAM6565_2n->insert (sIterFirst, sIterLast); i++;
	m_pContainerRAM6555_2n->insert (sIterFirst, sIterLast); i++;
	m_pContainerRAM5555_2n->insert (sIterFirst, sIterLast); i++;
	m_pContainerRAM5554_2n->insert (sIterFirst, sIterLast); i++;
	m_pContainerRAM5454_2n->insert (sIterFirst, sIterLast); i++;
	m_pContainerRAM5444_2n->insert (sIterFirst, sIterLast); i++;
	m_pContainerRAM4444_2n->insert (sIterFirst, sIterLast); i++;
	m_pContainerRAM6565_4n->insert (sIterFirst, sIterLast); i++;
	m_pContainerRAM6555_4n->insert (sIterFirst, sIterLast); i++;
	m_pContainerRAM5555_4n->insert (sIterFirst, sIterLast); i++;
	m_pContainerRAM5554_4n->insert (sIterFirst, sIterLast); i++;
	m_pContainerRAM5454_4n->insert (sIterFirst, sIterLast); i++;
	m_pContainerRAM5444_4n->insert (sIterFirst, sIterLast); i++;
	m_pContainerRAM4444_4n->insert (sIterFirst, sIterLast); i++;
	m_pContainerFile6565min->insert (sIterFirst, sIterLast); i++;
	m_pContainerFile6555min->insert (sIterFirst, sIterLast); i++;
	m_pContainerFile5555min->insert (sIterFirst, sIterLast); i++;
	m_pContainerFile5554min->insert (sIterFirst, sIterLast); i++;
	m_pContainerFile5454min->insert (sIterFirst, sIterLast); i++;

	m_pContainerFile6565default->insert (sIterFirst, sIterLast); i++;
	m_pContainerFile6555default->insert (sIterFirst, sIterLast); i++;
	m_pContainerFile5555default->insert (sIterFirst, sIterLast); i++;
	m_pContainerFile5554default->insert (sIterFirst, sIterLast); i++;
	m_pContainerFile5454default->insert (sIterFirst, sIterLast); i++;

	m_pContainerFile6565large->insert (sIterFirst, sIterLast); i++;
	m_pContainerFile6555large->insert (sIterFirst, sIterLast); i++;
	m_pContainerFile5555large->insert (sIterFirst, sIterLast); i++;
	m_pContainerFile5554large->insert (sIterFirst, sIterLast); i++;
	m_pContainerFile5454large->insert (sIterFirst, sIterLast); i++;

	BTREE_ASSERT (i == this->get_num_containers (), "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::insert<_t_iterator>: ERROR: Unexpected number of test containers!");

	this->test ();
}

template <class _t_data, class _t_value, class _t_ref_container>
template<class _t_iterator, class _t_dummy_iterator>
void CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::insert (_t_dummy_iterator &rIterDummy, _t_iterator sIterFirst, _t_iterator sIterLast)
{
	rIterDummy;

	this->insert (sIterFirst, sIterLast);
}

template <class _t_data, class _t_value, class _t_ref_container>
typename CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::iterator CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::insert (const typename CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::value_type &rData)
{
	return (CBTreeAssociativeTestWrapper_t::insert (rData));
}

template <class _t_data, class _t_value, class _t_ref_container>
template<class _t_iterator, class _t_test_iterator>
void CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::insert_self_reference (_t_iterator sIterFirst, _t_iterator sIterLast, _t_test_iterator &rIterTest)
{
	typedef typename reference_t::const_iterator		citer_ref_t;

	uint32_t			i = 0;
	_t_iterator			sIterBegin;
	sizetype_test_t		nFirst;
	sizetype_test_t		nLast;
	reference_t			sTempContainer;
	_t_test_iterator	sIterTestFirst;
	_t_test_iterator	sIterTestLast;
	citer_ref_t			sCIterRefBegin;
	citer_ref_t			sCIterRefEnd;

	get_begin (this->m_pReference, sIterBegin);
	nFirst = (sizetype_test_t) ::std::distance (sIterBegin, sIterFirst);
	nLast = (sizetype_test_t) ::std::distance (sIterBegin, sIterLast);
	
	sTempContainer.insert (sIterFirst, sIterLast);

	sCIterRefBegin = sTempContainer.cbegin ();
	sCIterRefEnd = sTempContainer.cend ();

	this->m_pReference->insert (sCIterRefBegin, sCIterRefEnd);

	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerRAM6565_n->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerRAM6555_n->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerRAM5555_n->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerRAM5554_n->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerRAM5454_n->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerRAM5444_n->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerRAM4444_n->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerRAM6565_2n->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerRAM6555_2n->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerRAM5555_2n->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerRAM5554_2n->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerRAM5454_2n->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerRAM5444_2n->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerRAM4444_2n->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerRAM6565_4n->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerRAM6555_4n->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerRAM5555_4n->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerRAM5554_4n->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerRAM5454_4n->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerRAM5444_4n->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerRAM4444_4n->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerFile6565min->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerFile6555min->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerFile5555min->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerFile5554min->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerFile5454min->insert (sIterTestFirst, sIterTestLast); i++;

	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerFile6565default->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerFile6555default->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerFile5555default->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerFile5554default->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerFile5454default->insert (sIterTestFirst, sIterTestLast); i++;

	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerFile6565large->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerFile6555large->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerFile5555large->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerFile5554large->insert (sIterTestFirst, sIterTestLast); i++;
	get_begin (this->m_ppContainers[i], sIterTestFirst); sIterTestLast = sIterTestFirst; ::std::advance (sIterTestFirst, nFirst); ::std::advance (sIterTestLast, nLast); m_pContainerFile5454large->insert (sIterTestFirst, sIterTestLast); i++;

	BTREE_ASSERT (i == this->get_num_containers (), "CBTreeAssociativeTestWrapper<_t_data, _t_value, _t_ref_container>::insert_self_reference<_t_iterator>: ERROR: Unexpected number of test containers!");

//	this->test ();
}

template <class _t_data, class _t_value, class _t_ref_container>
template<class _t_ext_container, class _t_ext_iterator, class _t_ref_iterator>
void CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::test_all_containers_insert (_t_ext_container *pExtContainer, _t_ext_iterator &rExtPos, _t_ref_iterator &rIterBegin, _t_ref_iterator &rIterFirst, _t_ref_iterator &rIterLast) const
{
	_t_ext_container		sExtOriginal (*pExtContainer);
	uint32_t				i = 0;
	sizetype_test_t			nFirst = (sizetype_test_t) ::std::distance (rIterBegin, rIterFirst);
	sizetype_test_t			nLast = (sizetype_test_t) ::std::distance (rIterBegin, rIterLast);
	_t_ext_iterator			sExtIterBegin;
	bool					bRefIterConst = is_const_iterator (this->m_pReference, rIterFirst);
	bool					bRefIterReverse = is_reverse_iterator (this->m_pReference, rIterFirst);

	get_begin (pExtContainer, sExtIterBegin);

	typename _t_ext_container::size_type		nDist = ::std::distance (sExtIterBegin, rExtPos);
	
	container_insert (pExtContainer, sExtIterBegin, rIterFirst, rIterLast);
	
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerRAM6565_n); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerRAM6555_n); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerRAM5555_n); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerRAM5554_n); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerRAM5454_n); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerRAM5444_n); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerRAM4444_n); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerRAM6565_2n); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerRAM6555_2n); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerRAM5555_2n); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerRAM5554_2n); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerRAM5454_2n); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerRAM5444_2n); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerRAM4444_2n); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerRAM6565_4n); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerRAM6555_4n); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerRAM5555_4n); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerRAM5554_4n); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerRAM5454_4n); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerRAM5444_4n); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerRAM4444_4n); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerFile6565min); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerFile6555min); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerFile5555min); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerFile5554min); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerFile5454min); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerFile6565default); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerFile6555default); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerFile5555default); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerFile5554default); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerFile5454default); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerFile6565large); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerFile6555large); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerFile5555large); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerFile5554large); i++;
	test_one_container_insert (&sExtOriginal, pExtContainer, nDist, nFirst, nLast, rExtPos, bRefIterConst, bRefIterReverse, m_pContainerFile5454large); i++;

	BTREE_ASSERT (i == this->get_num_containers (), "CBTreeMapTestWrapper<_t_data, _t_value, _t_ref_container>::test_all_containers_insert: ERROR: Unexpected number of containers has been exercised!");
}

template <class _t_data, class _t_value, class _t_ref_container>
typename CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::key_compare CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::key_comp () const
{
	key_compare		sRetval;

	sRetval.m_pThis = (CBTreeMultiMapTestWrapper_t *) this;

	return (sRetval);
}

template <class _t_data, class _t_value, class _t_ref_container>
typename CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::value_compare CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::value_comp () const
{
	value_compare	sRetval;

	sRetval.m_pThis = (CBTreeMultiMapTestWrapper_t *) this;

	return (sRetval);
}

template <class _t_data, class _t_value, class _t_ref_container>
bool CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::run_key_compare (const typename CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::key_t &rKey0, const typename CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::key_t &rKey1) const
{
	typename reference_t::key_compare	sRefComp = this->m_pReference->key_comp ();
	bool								bRefValue = sRefComp (rKey0, rKey1);
	uint32_t							i;

	for (i = 0; i < this->get_num_containers (); i++)
	{
		typename CBTreeAssociativeIf_t::key_compare		sTestComp = this->m_ppContainers[i]->key_comp ();
		bool											bTestValue = sTestComp (rKey0, rKey1);

		if (bRefValue != bTestValue)
		{
			::std::cerr << "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::run_key_compare: ERROR: comparison result mismatch!" << ::std::endl;

			exit (-1);
		}
	}

	return (bRefValue);
}

template <class _t_data, class _t_value, class _t_ref_container>
bool CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::run_value_compare (const typename CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::data_t &rVal0, const typename CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::data_t &rVal1) const
{
	typename reference_t::value_compare	sRefComp = this->m_pReference->value_comp ();
	bool								bRefValue = sRefComp (rVal0, rVal1);
	uint32_t							i;

	for (i = 0; i < this->get_num_containers (); i++)
	{
		typename CBTreeAssociativeIf_t::value_compare	sTestComp = this->m_ppContainers[i]->value_comp ();
		bool											bTestValue = sTestComp (rVal0, rVal1);

		if (bRefValue != bTestValue)
		{
			::std::cerr << "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::run_value_compare: ERROR: comparison result mismatch!" << ::std::endl;

			exit (-1);
		}
	}

	return (bRefValue);
}

template <class _t_data, class _t_value, class _t_ref_container>
void CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers (const uint32_t nNodeSize, const uint32_t nPageSize)
{
	CBTreeIOpropertiesRAM			sRAMproperties;
	CBTreeIOpropertiesFile			sFilePropertiesMin ("./", 1);
	CBTreeIOpropertiesFile			sFilePropertiesDefault ("./");
	CBTreeIOpropertiesFile			sFilePropertiesLarge ("./", 16777216);
	bayerTreeCacheDescription_t		sCacheDescPageSize = {nPageSize};
	bayerTreeCacheDescription_t		sCacheDescMin = {1};
	bayerTreeCacheDescription_t		sCacheDescNearestBigger = {nPageSize * 2 / 3};
	bayerTreeCacheDescription_t		sCacheDescLarge = {nPageSize * 16};
	uint32_t						i = 0;

	m_pContainerRAM6565_n = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint64_t, uint32_t, uint64_t, uint32_t> > (sRAMproperties, &sCacheDescPageSize, nNodeSize, this->m_pReference);
	m_pContainerRAM6555_n = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint64_t, uint32_t, uint32_t, uint32_t> > (sRAMproperties, &sCacheDescPageSize, nNodeSize, this->m_pReference);
	m_pContainerRAM5555_n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint32_t, uint32_t, uint32_t> > (sRAMproperties, &sCacheDescPageSize, nNodeSize, this->m_pReference);
	m_pContainerRAM5554_n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint32_t, uint32_t, uint16_t> > (sRAMproperties, &sCacheDescPageSize, nNodeSize, this->m_pReference);
	m_pContainerRAM5454_n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint16_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint16_t, uint32_t, uint16_t> > (sRAMproperties, &sCacheDescPageSize, nNodeSize, this->m_pReference);
	m_pContainerRAM5444_n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint16_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint16_t, uint16_t, uint16_t> > (sRAMproperties, &sCacheDescPageSize, nNodeSize, this->m_pReference);
	m_pContainerRAM4444_n = new CBTreeTestMultiMap<sizetype_test_t, uint16_t, uint16_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint16_t, uint16_t, uint16_t, uint16_t> > (sRAMproperties, &sCacheDescPageSize, nNodeSize, this->m_pReference);
	m_pContainerRAM6565_2n = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint64_t, uint32_t, uint64_t, uint32_t> > (sRAMproperties, &sCacheDescPageSize, nNodeSize * 2, this->m_pReference);
	m_pContainerRAM6555_2n = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint64_t, uint32_t, uint32_t, uint32_t> > (sRAMproperties, &sCacheDescPageSize, nNodeSize * 2, this->m_pReference);
	m_pContainerRAM5555_2n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint32_t, uint32_t, uint32_t> > (sRAMproperties, &sCacheDescPageSize, nNodeSize * 2, this->m_pReference);
	m_pContainerRAM5554_2n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint32_t, uint32_t, uint16_t> > (sRAMproperties, &sCacheDescPageSize, nNodeSize * 2, this->m_pReference);
	m_pContainerRAM5454_2n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint16_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint16_t, uint32_t, uint16_t> > (sRAMproperties, &sCacheDescPageSize, nNodeSize * 2, this->m_pReference);
	m_pContainerRAM5444_2n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint16_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint16_t, uint16_t, uint16_t> > (sRAMproperties, &sCacheDescPageSize, nNodeSize * 2, this->m_pReference);
	m_pContainerRAM4444_2n = new CBTreeTestMultiMap<sizetype_test_t, uint16_t, uint16_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint16_t, uint16_t, uint16_t, uint16_t> > (sRAMproperties, &sCacheDescPageSize, nNodeSize * 2, this->m_pReference);
	m_pContainerRAM6565_4n = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint64_t, uint32_t, uint64_t, uint32_t> > (sRAMproperties, &sCacheDescPageSize, nNodeSize * 4, this->m_pReference);
	m_pContainerRAM6555_4n = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint64_t, uint32_t, uint32_t, uint32_t> > (sRAMproperties, &sCacheDescPageSize, nNodeSize * 4, this->m_pReference);
	m_pContainerRAM5555_4n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint32_t, uint32_t, uint32_t> > (sRAMproperties, &sCacheDescPageSize, nNodeSize * 4, this->m_pReference);
	m_pContainerRAM5554_4n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint32_t, uint32_t, uint16_t> > (sRAMproperties, &sCacheDescPageSize, nNodeSize * 4, this->m_pReference);
	m_pContainerRAM5454_4n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint16_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint16_t, uint32_t, uint16_t> > (sRAMproperties, &sCacheDescPageSize, nNodeSize * 4, this->m_pReference);
	m_pContainerRAM5444_4n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint16_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint16_t, uint16_t, uint16_t> > (sRAMproperties, &sCacheDescPageSize, nNodeSize * 4, this->m_pReference);
	m_pContainerRAM4444_4n = new CBTreeTestMultiMap<sizetype_test_t, uint16_t, uint16_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint16_t, uint16_t, uint16_t, uint16_t> > (sRAMproperties, &sCacheDescPageSize, nNodeSize * 4, this->m_pReference);
	m_pContainerFile6565min = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint64_t, uint32_t, uint64_t, uint32_t> > (sFilePropertiesMin, &sCacheDescPageSize, nNodeSize * 4, this->m_pReference);
	m_pContainerFile6555min = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint64_t, uint32_t, uint32_t, uint32_t> > (sFilePropertiesMin, &sCacheDescPageSize, nNodeSize * 8, this->m_pReference);
	m_pContainerFile5555min = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint32_t, uint32_t, uint32_t, uint32_t> > (sFilePropertiesMin, &sCacheDescMin, nNodeSize * 7, this->m_pReference);
	m_pContainerFile5554min = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint32_t, uint32_t, uint32_t, uint16_t> > (sFilePropertiesMin, &sCacheDescNearestBigger, nNodeSize * 6, this->m_pReference);
	m_pContainerFile5454min = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint16_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint32_t, uint16_t, uint32_t, uint16_t> > (sFilePropertiesMin, &sCacheDescLarge, nNodeSize * 5, this->m_pReference);

	m_pContainerFile6565default = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint64_t, uint32_t, uint64_t, uint32_t> > (sFilePropertiesDefault, &sCacheDescNearestBigger, nNodeSize * 3, this->m_pReference);
	m_pContainerFile6555default = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint64_t, uint32_t, uint32_t, uint32_t> > (sFilePropertiesDefault, &sCacheDescNearestBigger, nNodeSize * 2, this->m_pReference);
	m_pContainerFile5555default = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint32_t, uint32_t, uint32_t, uint32_t> > (sFilePropertiesDefault, &sCacheDescLarge, nNodeSize, this->m_pReference);
	m_pContainerFile5554default = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint32_t, uint32_t, uint32_t, uint16_t> > (sFilePropertiesDefault, &sCacheDescPageSize, nNodeSize * 8, this->m_pReference);
	m_pContainerFile5454default = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint16_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint32_t, uint16_t, uint32_t, uint16_t> > (sFilePropertiesDefault, &sCacheDescMin, nNodeSize * 7, this->m_pReference);

	m_pContainerFile6565large = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint64_t, uint32_t, uint64_t, uint32_t> > (sFilePropertiesLarge, &sCacheDescPageSize, nNodeSize * 5, this->m_pReference);
	m_pContainerFile6555large = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint64_t, uint32_t, uint32_t, uint32_t> > (sFilePropertiesLarge, &sCacheDescPageSize, nNodeSize * 4, this->m_pReference);
	m_pContainerFile5555large = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint32_t, uint32_t, uint32_t, uint32_t> > (sFilePropertiesDefault, &sCacheDescMin, nNodeSize * 3, this->m_pReference);
	m_pContainerFile5554large = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint32_t, uint32_t, uint32_t, uint16_t> > (sFilePropertiesDefault, &sCacheDescNearestBigger, nNodeSize * 2, this->m_pReference);
	m_pContainerFile5454large = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint16_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint32_t, uint16_t, uint32_t, uint16_t> > (sFilePropertiesDefault, &sCacheDescLarge, nNodeSize, this->m_pReference);

	BTREE_ASSERT (NULL != m_pContainerRAM6565_n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM6565_n)");
	BTREE_ASSERT (NULL != m_pContainerRAM6555_n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM6555_n)");
	BTREE_ASSERT (NULL != m_pContainerRAM5555_n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5555_n)");
	BTREE_ASSERT (NULL != m_pContainerRAM5554_n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5554_n)");
	BTREE_ASSERT (NULL != m_pContainerRAM5454_n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5454_n)");
	BTREE_ASSERT (NULL != m_pContainerRAM5444_n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5444_n)");
	BTREE_ASSERT (NULL != m_pContainerRAM4444_n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM4444_n)");
	BTREE_ASSERT (NULL != m_pContainerRAM6565_2n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM6565_2n)");
	BTREE_ASSERT (NULL != m_pContainerRAM6555_2n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM6555_2n)");
	BTREE_ASSERT (NULL != m_pContainerRAM5555_2n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5555_2n)");
	BTREE_ASSERT (NULL != m_pContainerRAM5554_2n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5554_2n)");
	BTREE_ASSERT (NULL != m_pContainerRAM5454_2n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5454_2n)");
	BTREE_ASSERT (NULL != m_pContainerRAM5444_2n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5444_2n)");
	BTREE_ASSERT (NULL != m_pContainerRAM4444_2n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM4444_2n)");
	BTREE_ASSERT (NULL != m_pContainerRAM6565_4n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM6565_4n)");
	BTREE_ASSERT (NULL != m_pContainerRAM6555_4n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM6555_4n)");
	BTREE_ASSERT (NULL != m_pContainerRAM5555_4n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5555_4n)");
	BTREE_ASSERT (NULL != m_pContainerRAM5554_4n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5554_4n)");
	BTREE_ASSERT (NULL != m_pContainerRAM5454_4n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5454_4n)");
	BTREE_ASSERT (NULL != m_pContainerRAM5444_4n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5444_4n)");
	BTREE_ASSERT (NULL != m_pContainerRAM4444_4n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM4444_4n)");
	BTREE_ASSERT (NULL != m_pContainerFile6565min, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile6565min)");
	BTREE_ASSERT (NULL != m_pContainerFile6555min, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile6555min)");
	BTREE_ASSERT (NULL != m_pContainerFile5555min, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile5555min)");
	BTREE_ASSERT (NULL != m_pContainerFile5554min, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile5554min)");
	BTREE_ASSERT (NULL != m_pContainerFile5454min, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile5454min)");

	BTREE_ASSERT (NULL != m_pContainerFile6565default, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile6565default)");
	BTREE_ASSERT (NULL != m_pContainerFile6555default, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile6555default)");
	BTREE_ASSERT (NULL != m_pContainerFile5555default, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile5555default)");
	BTREE_ASSERT (NULL != m_pContainerFile5554default, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile5554default)");
	BTREE_ASSERT (NULL != m_pContainerFile5454default, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile5454default)");

	BTREE_ASSERT (NULL != m_pContainerFile6565large, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile6565large)");
	BTREE_ASSERT (NULL != m_pContainerFile6555large, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile6555large)");
	BTREE_ASSERT (NULL != m_pContainerFile5555large, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile5555large)");
	BTREE_ASSERT (NULL != m_pContainerFile5554large, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile5554large)");
	BTREE_ASSERT (NULL != m_pContainerFile5454large, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile5454large)");
}

template <class _t_data, class _t_value, class _t_ref_container>
void CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers (const CBTreeAssociativeTestWrapper<_t_data, _t_value, _t_ref_container> &rWrapper)
{
	uint32_t	i = 0;

	const CBTreeMultiMapTestWrapper_t		&rThisWrapper = dynamic_cast<const CBTreeMultiMapTestWrapper_t &> (rWrapper);

	m_pContainerRAM6565_n = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint64_t, uint32_t, uint64_t, uint32_t> > (*rThisWrapper.m_pContainerRAM6565_n); i++;
	m_pContainerRAM6555_n = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint64_t, uint32_t, uint32_t, uint32_t> > (*rThisWrapper.m_pContainerRAM6555_n); i++;
	m_pContainerRAM5555_n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint32_t, uint32_t, uint32_t> > (*rThisWrapper.m_pContainerRAM5555_n); i++;
	m_pContainerRAM5554_n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint32_t, uint32_t, uint16_t> > (*rThisWrapper.m_pContainerRAM5554_n); i++;
	m_pContainerRAM5454_n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint16_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint16_t, uint32_t, uint16_t> > (*rThisWrapper.m_pContainerRAM5454_n); i++;
	m_pContainerRAM5444_n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint16_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint16_t, uint16_t, uint16_t> > (*rThisWrapper.m_pContainerRAM5444_n); i++;
	m_pContainerRAM4444_n = new CBTreeTestMultiMap<sizetype_test_t, uint16_t, uint16_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint16_t, uint16_t, uint16_t, uint16_t> > (*rThisWrapper.m_pContainerRAM4444_n); i++;
	m_pContainerRAM6565_2n = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint64_t, uint32_t, uint64_t, uint32_t> > (*rThisWrapper.m_pContainerRAM6565_2n); i++;
	m_pContainerRAM6555_2n = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint64_t, uint32_t, uint32_t, uint32_t> > (*rThisWrapper.m_pContainerRAM6555_2n); i++;
	m_pContainerRAM5555_2n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint32_t, uint32_t, uint32_t> > (*rThisWrapper.m_pContainerRAM5555_2n); i++;
	m_pContainerRAM5554_2n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint32_t, uint32_t, uint16_t> > (*rThisWrapper.m_pContainerRAM5554_2n); i++;
	m_pContainerRAM5454_2n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint16_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint16_t, uint32_t, uint16_t> > (*rThisWrapper.m_pContainerRAM5454_2n); i++;
	m_pContainerRAM5444_2n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint16_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint16_t, uint16_t, uint16_t> > (*rThisWrapper.m_pContainerRAM5444_2n); i++;
	m_pContainerRAM4444_2n = new CBTreeTestMultiMap<sizetype_test_t, uint16_t, uint16_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint16_t, uint16_t, uint16_t, uint16_t> > (*rThisWrapper.m_pContainerRAM4444_2n); i++;
	m_pContainerRAM6565_4n = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint64_t, uint32_t, uint64_t, uint32_t> > (*rThisWrapper.m_pContainerRAM6565_4n); i++;
	m_pContainerRAM6555_4n = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint64_t, uint32_t, uint32_t, uint32_t> > (*rThisWrapper.m_pContainerRAM6555_4n); i++;
	m_pContainerRAM5555_4n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint32_t, uint32_t, uint32_t> > (*rThisWrapper.m_pContainerRAM5555_4n); i++;
	m_pContainerRAM5554_4n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint32_t, uint32_t, uint16_t> > (*rThisWrapper.m_pContainerRAM5554_4n); i++;
	m_pContainerRAM5454_4n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint16_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint16_t, uint32_t, uint16_t> > (*rThisWrapper.m_pContainerRAM5454_4n); i++;
	m_pContainerRAM5444_4n = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint16_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint32_t, uint16_t, uint16_t, uint16_t> > (*rThisWrapper.m_pContainerRAM5444_4n); i++;
	m_pContainerRAM4444_4n = new CBTreeTestMultiMap<sizetype_test_t, uint16_t, uint16_t, CBTreeIOpropertiesRAM, CBTreeRAMIO <uint16_t, uint16_t, uint16_t, uint16_t> > (*rThisWrapper.m_pContainerRAM4444_4n); i++;
	m_pContainerFile6565min = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint64_t, uint32_t, uint64_t, uint32_t> > (*rThisWrapper.m_pContainerFile6565min); i++;
	m_pContainerFile6555min = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint64_t, uint32_t, uint32_t, uint32_t> > (*rThisWrapper.m_pContainerFile6555min); i++;
	m_pContainerFile5555min = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint32_t, uint32_t, uint32_t, uint32_t> > (*rThisWrapper.m_pContainerFile5555min); i++;
	m_pContainerFile5554min = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint32_t, uint32_t, uint32_t, uint16_t> > (*rThisWrapper.m_pContainerFile5554min); i++;
	m_pContainerFile5454min = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint16_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint32_t, uint16_t, uint32_t, uint16_t> > (*rThisWrapper.m_pContainerFile5454min); i++;

	m_pContainerFile6565default = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint64_t, uint32_t, uint64_t, uint32_t> > (*rThisWrapper.m_pContainerFile6565default); i++;
	m_pContainerFile6555default = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint64_t, uint32_t, uint32_t, uint32_t> > (*rThisWrapper.m_pContainerFile6555default); i++;
	m_pContainerFile5555default = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint32_t, uint32_t, uint32_t, uint32_t> > (*rThisWrapper.m_pContainerFile5555default); i++;
	m_pContainerFile5554default = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint32_t, uint32_t, uint32_t, uint16_t> > (*rThisWrapper.m_pContainerFile5554default); i++;
	m_pContainerFile5454default = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint16_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint32_t, uint16_t, uint32_t, uint16_t> > (*rThisWrapper.m_pContainerFile5454default); i++;

	m_pContainerFile6565large = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint64_t, uint32_t, uint64_t, uint32_t> > (*rThisWrapper.m_pContainerFile6565large); i++;
	m_pContainerFile6555large = new CBTreeTestMultiMap<sizetype_test_t, uint64_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint64_t, uint32_t, uint32_t, uint32_t> > (*rThisWrapper.m_pContainerFile6555large); i++;
	m_pContainerFile5555large = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint32_t, uint32_t, uint32_t, uint32_t> > (*rThisWrapper.m_pContainerFile5555large); i++;
	m_pContainerFile5554large = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint32_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint32_t, uint32_t, uint32_t, uint16_t> > (*rThisWrapper.m_pContainerFile5554large); i++;
	m_pContainerFile5454large = new CBTreeTestMultiMap<sizetype_test_t, uint32_t, uint16_t, CBTreeIOpropertiesFile, CBTreeFileIO <uint32_t, uint16_t, uint32_t, uint16_t> > (*rThisWrapper.m_pContainerFile5454large); i++;

	BTREE_ASSERT (i == this->get_num_containers (), "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers (const CBTreeAssociativeTestWrapper &): ERROR: Unexpected number of test containers instantiated!");

	i = 0;

	BTREE_ASSERT (NULL != m_pContainerRAM6565_n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM6565_n)"); i++;
	BTREE_ASSERT (NULL != m_pContainerRAM6555_n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM6555_n)"); i++;
	BTREE_ASSERT (NULL != m_pContainerRAM5555_n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5555_n)"); i++;
	BTREE_ASSERT (NULL != m_pContainerRAM5554_n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5554_n)"); i++;
	BTREE_ASSERT (NULL != m_pContainerRAM5454_n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5454_n)"); i++;
	BTREE_ASSERT (NULL != m_pContainerRAM5444_n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5444_n)"); i++;
	BTREE_ASSERT (NULL != m_pContainerRAM4444_n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM4444_n)"); i++;
	BTREE_ASSERT (NULL != m_pContainerRAM6565_2n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM6565_2n)"); i++;
	BTREE_ASSERT (NULL != m_pContainerRAM6555_2n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM6555_2n)"); i++;
	BTREE_ASSERT (NULL != m_pContainerRAM5555_2n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5555_2n)"); i++;
	BTREE_ASSERT (NULL != m_pContainerRAM5554_2n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5554_2n)"); i++;
	BTREE_ASSERT (NULL != m_pContainerRAM5454_2n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5454_2n)"); i++;
	BTREE_ASSERT (NULL != m_pContainerRAM5444_2n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5444_2n)"); i++;
	BTREE_ASSERT (NULL != m_pContainerRAM4444_2n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM4444_2n)"); i++;
	BTREE_ASSERT (NULL != m_pContainerRAM6565_4n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM6565_4n)"); i++;
	BTREE_ASSERT (NULL != m_pContainerRAM6555_4n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM6555_4n)"); i++;
	BTREE_ASSERT (NULL != m_pContainerRAM5555_4n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5555_4n)"); i++;
	BTREE_ASSERT (NULL != m_pContainerRAM5554_4n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5554_4n)"); i++;
	BTREE_ASSERT (NULL != m_pContainerRAM5454_4n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5454_4n)"); i++;
	BTREE_ASSERT (NULL != m_pContainerRAM5444_4n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM5444_4n)"); i++;
	BTREE_ASSERT (NULL != m_pContainerRAM4444_4n, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerRAM4444_4n)"); i++;
	BTREE_ASSERT (NULL != m_pContainerFile6565min, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile6565min)"); i++;
	BTREE_ASSERT (NULL != m_pContainerFile6555min, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile6555min)"); i++;
	BTREE_ASSERT (NULL != m_pContainerFile5555min, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile5555min)"); i++;
	BTREE_ASSERT (NULL != m_pContainerFile5554min, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile5554min)"); i++;
	BTREE_ASSERT (NULL != m_pContainerFile5454min, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile5454min)"); i++;

	BTREE_ASSERT (NULL != m_pContainerFile6565default, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile6565default)"); i++;
	BTREE_ASSERT (NULL != m_pContainerFile6555default, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile6555default)"); i++;
	BTREE_ASSERT (NULL != m_pContainerFile5555default, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile5555default)"); i++;
	BTREE_ASSERT (NULL != m_pContainerFile5554default, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile5554default)"); i++;
	BTREE_ASSERT (NULL != m_pContainerFile5454default, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile5454default)"); i++;

	BTREE_ASSERT (NULL != m_pContainerFile6565large, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile6565large)"); i++;
	BTREE_ASSERT (NULL != m_pContainerFile6555large, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile6555large)"); i++;
	BTREE_ASSERT (NULL != m_pContainerFile5555large, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile5555large)"); i++;
	BTREE_ASSERT (NULL != m_pContainerFile5554large, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile5554large)"); i++;
	BTREE_ASSERT (NULL != m_pContainerFile5454large, "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers: ERROR: insufficient memory! (m_pContainerFile5454large)"); i++;

	BTREE_ASSERT (i == this->get_num_containers (), "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers (const CBTreeAssociativeTestWrapper &): ERROR: Unexpected number of test containers checked to be instantiated successfully!");

	i = 0;

	m_pContainerRAM6565_n->set_reference (this->m_pReference); i++;
	m_pContainerRAM6555_n->set_reference (this->m_pReference); i++;
	m_pContainerRAM5555_n->set_reference (this->m_pReference); i++;
	m_pContainerRAM5554_n->set_reference (this->m_pReference); i++;
	m_pContainerRAM5454_n->set_reference (this->m_pReference); i++;
	m_pContainerRAM5444_n->set_reference (this->m_pReference); i++;
	m_pContainerRAM4444_n->set_reference (this->m_pReference); i++;
	m_pContainerRAM6565_2n->set_reference (this->m_pReference); i++;
	m_pContainerRAM6555_2n->set_reference (this->m_pReference); i++;
	m_pContainerRAM5555_2n->set_reference (this->m_pReference); i++;
	m_pContainerRAM5554_2n->set_reference (this->m_pReference); i++;
	m_pContainerRAM5454_2n->set_reference (this->m_pReference); i++;
	m_pContainerRAM5444_2n->set_reference (this->m_pReference); i++;
	m_pContainerRAM4444_2n->set_reference (this->m_pReference); i++;
	m_pContainerRAM6565_4n->set_reference (this->m_pReference); i++;
	m_pContainerRAM6555_4n->set_reference (this->m_pReference); i++;
	m_pContainerRAM5555_4n->set_reference (this->m_pReference); i++;
	m_pContainerRAM5554_4n->set_reference (this->m_pReference); i++;
	m_pContainerRAM5454_4n->set_reference (this->m_pReference); i++;
	m_pContainerRAM5444_4n->set_reference (this->m_pReference); i++;
	m_pContainerRAM4444_4n->set_reference (this->m_pReference); i++;
	m_pContainerFile6565min->set_reference (this->m_pReference); i++;
	m_pContainerFile6555min->set_reference (this->m_pReference); i++;
	m_pContainerFile5555min->set_reference (this->m_pReference); i++;
	m_pContainerFile5554min->set_reference (this->m_pReference); i++;
	m_pContainerFile5454min->set_reference (this->m_pReference); i++;

	m_pContainerFile6565default->set_reference (this->m_pReference); i++;
	m_pContainerFile6555default->set_reference (this->m_pReference); i++;
	m_pContainerFile5555default->set_reference (this->m_pReference); i++;
	m_pContainerFile5554default->set_reference (this->m_pReference); i++;
	m_pContainerFile5454default->set_reference (this->m_pReference); i++;

	m_pContainerFile6565large->set_reference (this->m_pReference); i++;
	m_pContainerFile6555large->set_reference (this->m_pReference); i++;
	m_pContainerFile5555large->set_reference (this->m_pReference); i++;
	m_pContainerFile5554large->set_reference (this->m_pReference); i++;
	m_pContainerFile5454large->set_reference (this->m_pReference); i++;

	BTREE_ASSERT (i == this->get_num_containers (), "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::init_containers (const CBTreeAssociativeTestWrapper &): ERROR: Unexpected number of test containers after setting reference container!");
}

template <class _t_data, class _t_value, class _t_ref_container>
void CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::transfer_containers ()
{
	uint32_t		i = 0;

	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerRAM6565_n); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerRAM6555_n); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerRAM5555_n); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerRAM5554_n); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerRAM5454_n); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerRAM5444_n); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerRAM4444_n); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerRAM6565_2n); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerRAM6555_2n); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerRAM5555_2n); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerRAM5554_2n); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerRAM5454_2n); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerRAM5444_2n); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerRAM4444_2n); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerRAM6565_4n); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerRAM6555_4n); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerRAM5555_4n); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerRAM5554_4n); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerRAM5454_4n); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerRAM5444_4n); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerRAM4444_4n); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerFile6565min); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerFile6555min); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerFile5555min); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerFile5554min); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerFile5454min); i++;

	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerFile6565default); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerFile6555default); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerFile5555default); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerFile5554default); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerFile5454default); i++;

	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerFile6565large); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerFile6555large); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerFile5555large); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerFile5554large); i++;
	this->m_ppContainers[i] = dynamic_cast<CBTreeAssociativeIf<_t_value, uint32_t, sizetype_test_t> *> (m_pContainerFile5454large); i++;

	BTREE_ASSERT (i == this->get_num_containers (), "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::transfer_containers: ERROR: Unexpected number of test containers!");
}
	
template <class _t_data, class _t_value, class _t_ref_container>
template<class _t_ext_container, class _t_source_container, class _t_ext_sizetype, class _t_ext_iterator>
void CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::test_one_container_insert (_t_ext_container *pExtOriginal, _t_ext_container *pExtReference, _t_ext_sizetype nPos, sizetype_test_t nFirst, sizetype_test_t nLast, _t_ext_iterator &rExtIter, bool bRefIterConst, bool bRefIterReverse, _t_source_container *pSrc) const
{
//#if defined (WIN32)

	bRefIterConst;

//#else

//	if (bRefIterConst)
//	{
//#endif
		if (bRefIterReverse)
		{
			typename _t_source_container::const_reverse_iterator	sCRIter;

			test_one_container_insert (pExtOriginal, pExtReference, nPos, nFirst, nLast, rExtIter, sCRIter, pSrc);
		}
		else
		{
			typename _t_source_container::const_iterator			sCIter;

			test_one_container_insert (pExtOriginal, pExtReference, nPos, nFirst, nLast, rExtIter, sCIter, pSrc);
		}
/*
#if !defined (WIN32)
	}
	else
	{
		if (bRefIterReverse)
		{
			typename _t_source_container::reverse_iterator			sRIter;

			test_one_container_insert (pExtOriginal, pExtReference, nPos, nFirst, nLast, rExtIter, sRIter, pSrc);
		}
		else
		{
			typename _t_source_container::iterator					sIter;

			test_one_container_insert (pExtOriginal, pExtReference, nPos, nFirst, nLast, rExtIter, sIter, pSrc);
		}
	}
#endif
*/
}
	
template <class _t_data, class _t_value, class _t_ref_container>
template<class _t_ext_container, class _t_source_container, class _t_ext_sizetype, class _t_ext_iterator, class _t_iterator>
void CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::test_one_container_insert	(_t_ext_container *pExtOriginal, _t_ext_container *pExtReference, _t_ext_sizetype nPos, sizetype_test_t nFirst, sizetype_test_t nLast, _t_ext_iterator &rExtIter, _t_iterator &rIter, _t_source_container *pSrc) const
{
	_t_ext_container	sExtTest (*pExtOriginal);
	_t_iterator			sIterBegin;
	_t_iterator			sIterFirst;
	_t_iterator			sIterLast;
	_t_ext_iterator		sExtIter;
	_t_ext_iterator		sExtIterBegin;
	_t_ext_iterator		sExtIterRefBegin;
	_t_ext_iterator		sExtIterRefEnd;

	get_begin (pSrc, sIterBegin);
	get_begin (pSrc, sIterFirst);
	get_begin (pSrc, sIterLast);
	get_begin (&sExtTest, sExtIter);
	
	::std::advance (sIterFirst, nFirst);
	::std::advance (sIterLast, nLast);

	::std::advance (sExtIter, nPos);

	container_insert (&sExtTest, sExtIter, sIterFirst, sIterLast);

	if (sExtTest.size () != pExtReference->size ())
	{
		::std::cerr << "CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::test_one_container_insert: ERROR: size mismatch!" << ::std::endl << ::std::flush;

		exit (-1);
	}

	get_begin (&sExtTest, sExtIterBegin);
	get_begin (pExtReference, sExtIterRefBegin);
	get_end (pExtReference, sExtIterRefEnd);

	while (sExtIterRefBegin != sExtIterRefEnd)
	{
		_t_data		sDataTest;
		_t_data		sDataRef;

		entry_conversion (sDataTest, *sExtIterBegin);
		entry_conversion (sDataRef, *sExtIterRefBegin);

		if ((get_entry_data (sDataTest) != get_entry_data (sDataRef)) ||
			(get_entry_key (sDataTest) != get_entry_key (sDataRef)))
		{
			::std::cerr << "CBTreeMapTestWrapper<_t_data, _t_value, _t_ref_container>::test_one_container_insert: ERROR: data mismatch!" << ::std::endl << ::std::flush;

			exit (-1);
		}

		::std::advance (sExtIterBegin, 1);
		::std::advance (sExtIterRefBegin, 1);
	}

	pSrc->test ();
}
	
template <class _t_data, class _t_value, class _t_ref_container>
const uint32_t CBTreeMultiMapTestWrapper<_t_data, _t_value, _t_ref_container>::m_nNumContainersMM = 36;

#endif // BTREEMAPTESTWRAPPER_CPP
