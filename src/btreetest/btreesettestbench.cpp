/************************************************************
**
** file:	btreesettestbench.cpp
** author:	Andreas Steffens
** license:	GPL v2
**
** description:
**
** This file contains code for the b-tree framework's test bench
** exercising functional, code coverage and regression tests
** for the set application class.
**
************************************************************/

#include "btreesettestbench.h"

template <class _t_set>
void TestBTreeSetSTLifAssignmentOperator (_t_set *pClSet, uint32_t nNumEntries)
{
	typedef typename _t_set::const_iterator		citer_t;

	_t_set										sClSet (*pClSet, false);
	uint32_t									nLastKey = 0;
	citer_t										sIter;
	citer_t										sIterRslt;
	
	cout << "exercises assignment operator compatible to STL interface CBTreeSet<>:: operator= (CBTreeSet<> &)" << endl;

	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sClSet = *pClSet;

	if (sClSet != (*pClSet))
	{
		cerr << endl;
		cerr << "TestBTreeSetSTLifAssignmentOperator<>: ERROR: mismatch after assignment operation" << endl;

		exit (-1);
	}
}

template <class _t_set>
void TestBTreeSetSTLifInsert (_t_set *pClSet, uint32_t nNumEntries)
{
	uint32_t	nLastSeed = 0;

	cout << "CBTreeSet::insert (const valuetype &) is exercised" << endl;

	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastSeed, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
}

template <class _t_set>
void TestBTreeSetSTLifInsertViaIterator (_t_set *pClSet, uint32_t nNumEntries, typename _t_set::datalayerproperties_t &rDataLayerProperties, bayerTreeCacheDescription_t *psCacheDescription, uint32_t nNodeSize)
{
	typedef typename _t_set::value_t											value_t;

	typedef typename _t_set::iterator											iter_t;
	typedef typename _t_set::const_iterator										citer_t;
	typedef typename _t_set::reverse_iterator									riter_t;
	typedef typename _t_set::const_reverse_iterator								criter_t;

	typedef typename ::std::list<value_t>::iterator								itlist_t;
	typedef typename ::std::list<value_t>::const_iterator						citlist_t;
	typedef typename ::std::list<value_t>::reverse_iterator						ritlist_t;
	typedef typename ::std::list<value_t>::const_reverse_iterator				critlist_t;

	typedef typename ::std::vector<value_t>::iterator							itvec_t;
	typedef typename ::std::vector<value_t>::const_iterator						citvec_t;
	typedef typename ::std::vector<value_t>::reverse_iterator					ritvec_t;
	typedef typename ::std::vector<value_t>::const_reverse_iterator				critvec_t;

	typedef CBTreeSet<uint32_t, size_t>											CBTreeSet_VectorFeed_t;

	typedef CBTreeTestSet<typename _t_set::sizetype_t, typename _t_set::nodeiter_t, typename _t_set::subnodeiter_t, typename _t_set::datalayerproperties_t, typename _t_set::datalayer_t>
																				CBTreeSetTest_Pair_t;

	typedef typename CBTreeSetTest_Pair_t::iterator								iter_pair_t;
	typedef typename CBTreeSetTest_Pair_t::const_iterator						citer_pair_t;
	typedef typename CBTreeSetTest_Pair_t::reverse_iterator						riter_pair_t;
	typedef typename CBTreeSetTest_Pair_t::const_reverse_iterator				criter_pair_t;

	typedef typename ::std::set<uint32_t>::iterator								itset_t;
	typedef typename ::std::set<uint32_t>::const_iterator						citset_t;
	typedef typename ::std::set<uint32_t>::reverse_iterator						ritset_t;
	typedef typename ::std::set<uint32_t>::const_reverse_iterator				critset_t;

	typedef typename ::std::multiset<uint32_t>::iterator						itmset_t;
	typedef typename ::std::multiset<uint32_t>::const_iterator				citmset_t;
	typedef typename ::std::multiset<uint32_t>::reverse_iterator				ritmset_t;
	typedef typename ::std::multiset<uint32_t>::const_reverse_iterator		critmset_t;
	
	_t_set										sClSetTarget (*pClSet, false);
	uint32_t									nLastKey = 0;
	citer_t										sCIterA, sCIterB;
	criter_t									sCRIterA, sCRIterB;
	::std::list<value_t>						sList;
	::std::vector<value_t>						sVector;
	itlist_t									sItListA, sItListB;
	citlist_t									sCItListA, sCItListB;
	ritlist_t									sRItListA, sRItListB;
	critlist_t									sCRItListA, sCRItListB;
	itvec_t										sItVecA, sItVecB;
	citvec_t									sCItVecA, sCItVecB;
	ritvec_t									sRItVecA, sRItVecB;
	critvec_t									sCRItVecA, sCRItVecB;
	CBTreeIOpropertiesRAM						sRAMproperties;
	CBTreeSet_VectorFeed_t						sSetVectorFeed (sRAMproperties, psCacheDescription, nNodeSize);
	CBTreeSetTest_Pair_t						sSetPair (rDataLayerProperties, psCacheDescription, nNodeSize);
	CBTreeSetTest_Pair_t						sSetTargetPair (sSetPair);
//	value_t										sSetPairData;
	citer_pair_t								sCIterPairA, sCIterPairB;
	criter_pair_t								sCRIterPairA, sCRIterPairB;
	::std::set<uint32_t>						sSet;
	itset_t										sItSetA, sItSetB;
	citset_t									sCItSetA, sCItSetB;
	ritset_t									sRItSetA, sRItSetB;
	critset_t									sCRItSetA, sCRItSetB;
	::std::multiset<uint32_t>				sMSet;
	itmset_t									sItMSetA, sItMSetB;
	citmset_t									sCItMSetA, sCItMSetB;
	ritmset_t									sRItMSetA, sRItMSetB;
	critmset_t									sCRItMSetA, sCRItMSetB;
	
	cout << "exercises method compatible to STL interface CBTreeSet<>:: insert<_t_iterator> (_t_iterator, _t_iterator)" << endl;

#if 0 // for this code to compile, the b-tree framework under test must support const methods
// this is to be implemented

	cout << "target::insert<_t_obj::iter_t> (iter_t, iter_t)" << endl;

	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sClSetTarget.template insert <iter_t> (pClSet->begin (), pClSet->end ());

	pClSet->clear ();
	sClSetTarget.clear ();

#endif

	cout << "target::insert<_t_obj::citer_t> (citer_t, citer_t)" << endl;

	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sClSetTarget.template insert <citer_t> (pClSet->cbegin (), pClSet->cend ());

	pClSet->clear ();
	sClSetTarget.clear ();

#if 0 // for this code to compile, the b-tree framework under test must support const methods
// this is to be implemented

	cout << "target::insert<_t_obj::riter_t> (riter_t, riter_t)" << endl;

	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sClSetTarget.template insert <riter_t> (pClSet->rbegin (), pClSet->rend ());

	pClSet->clear ();
	sClSetTarget.clear ();

#endif

	cout << "target::insert<_t_obj::criter_t> (criter_t, criter_t)" << endl;

	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sClSetTarget.template insert <criter_t> (pClSet->crbegin (), pClSet->crend ());

	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<_t_obj::citer_t> (citer_t == citer_t)" << endl;

	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sCIterA = pClSet->cbegin ();
	sCIterB = pClSet->cbegin ();

	while (sCIterA != pClSet->cend ())
	{
		sClSetTarget.template insert <citer_t> (sCIterA, sCIterB);

		sCIterA++;
		sCIterB++;
	}

	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<_t_obj::criter_t> (criter_t == criter_t)" << endl;

	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sCRIterA = pClSet->crbegin ();
	sCRIterB = pClSet->crbegin ();

	while (sCRIterA != pClSet->crend ())
	{
		sClSetTarget.template insert <criter_t> (sCRIterA, sCRIterB);

		sCRIterA++;
		sCRIterB++;
	}

	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<_t_obj::citer_t> (>citer_t, citer_t<)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sCIterA = pClSet->cbegin ();
	sCIterB = pClSet->cend ();

	sCIterA += (int) (nNumEntries / 4);
	sCIterB -= (int) (nNumEntries / 4);

	sClSetTarget.template insert <citer_t> (sCIterA, sCIterB);

	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<_t_obj::criter_t> (>criter_t, criter_t<)" << endl;

	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sCRIterA = pClSet->crbegin ();
	sCRIterB = pClSet->crend ();

	sCRIterA += (int) (nNumEntries / 4);
	sCRIterB -= (int) (nNumEntries / 4);

	sClSetTarget.template insert <criter_t> (sCRIterA, sCRIterB);

	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<_t_obj::citer_t> (target::citer_t, target::citer_t)" << endl;

	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	pClSet->template insert <citer_t> (pClSet->cbegin (), pClSet->cend ());

	pClSet->clear ();

	cout << "target::insert<_t_obj::criter_t> (target::criter_t, target::criter_t)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	pClSet->template insert <criter_t> (pClSet->crbegin (), pClSet->crend ());

	pClSet->clear ();

	cout << "target::insert<_t_obj::citer_t> (target::citer_t == target::citer_t)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sCIterA = pClSet->cbegin ();
	sCIterB = pClSet->cbegin ();

	while (sCIterA != pClSet->cend ())
	{
		pClSet->template insert <citer_t> (sCIterA, sCIterB);

		sCIterA++;
		sCIterB++;
	}

	pClSet->clear ();

	cout << "target::insert<_t_obj::criter_t> (target::criter_t == target::criter_t)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sCRIterA = pClSet->crbegin ();
	sCRIterB = pClSet->crbegin ();

	while (sCRIterA != pClSet->crend ())
	{
		pClSet->template insert <criter_t> (sCRIterA, sCRIterB);

		sCRIterA++;
		sCRIterB++;
	}

	pClSet->clear ();

	cout << "target::insert<_t_obj::citer_t> (>target::citer_t, target::citer_t<)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	pClSet->template insert <citer_t> (pClSet->cbegin (), pClSet->cend ());
	pClSet->template insert <citer_t> (pClSet->cbegin (), pClSet->cend ());
	pClSet->template insert <citer_t> (pClSet->cbegin (), pClSet->cend ());
	pClSet->template insert <citer_t> (pClSet->cbegin (), pClSet->cend ());

	sCIterA = pClSet->cbegin ();
	sCIterB = pClSet->cend ();

	sCIterA += (int) (nNumEntries / 4);
	sCIterB -= (int) (nNumEntries / 4);

	pClSet->template insert <citer_t> (sCIterA, sCIterB);

	pClSet->clear ();

	cout << "target::insert<_t_obj::criter_t> (>target::criter_t, target::criter_t<)" << endl;

	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	pClSet->template insert <criter_t> (pClSet->crbegin (), pClSet->crend ());
	pClSet->template insert <criter_t> (pClSet->crbegin (), pClSet->crend ());
	pClSet->template insert <criter_t> (pClSet->crbegin (), pClSet->crend ());
	pClSet->template insert <criter_t> (pClSet->crbegin (), pClSet->crend ());

	sCRIterA = pClSet->crbegin ();
	sCRIterB = pClSet->crend ();

	sCRIterA += (int) (nNumEntries / 4);
	sCRIterB -= (int) (nNumEntries / 4);

	pClSet->template insert <criter_t> (sCRIterA, sCRIterB);

	pClSet->clear ();

	cout << "target::insert<list::iter_t> (iter_t, iter_t)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sList.template insert <citer_t> (sList.begin (), pClSet->cbegin (), pClSet->cend ());

	sClSetTarget.template insert <itlist_t> (sList.begin (), sList.end ());

	sList.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<list::citer_t> (citer_t, citer_t)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sList.template insert <citer_t> (sList.begin (), pClSet->cbegin (), pClSet->cend ());

	sClSetTarget.template insert <citlist_t> (sList.cbegin (), sList.cend ());

	sList.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<list::riter_t> (riter_t, riter_t)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sList.template insert <citer_t> (sList.begin (), pClSet->cbegin (), pClSet->cend ());

	sClSetTarget.template insert <ritlist_t> (sList.rbegin (), sList.rend ());

	sList.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<list::criter_t> (criter_t, criter_t)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sList.template insert <citer_t> (sList.begin (), pClSet->cbegin (), pClSet->cend ());

	sClSetTarget.template insert <critlist_t> (sList.crbegin (), sList.crend ());

	sList.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<list::iter_t> (iter_t == iter_t)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sList.template insert <citer_t> (sList.begin (), pClSet->cbegin (), pClSet->cend ());

	sItListA = sList.begin ();
	sItListB = sList.begin ();

	while (sItListA != sList.end ())
	{
		sClSetTarget.template insert <itlist_t> (sItListA, sItListB);

		sItListA++;
		sItListB++;
	}

	sList.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<list::citer_t> (citer_t == citer_t)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sList.template insert <citer_t> (sList.begin (), pClSet->cbegin (), pClSet->cend ());

	sCItListA = sList.cbegin ();
	sCItListB = sList.cbegin ();

	while (sCItListA != sList.cend ())
	{
		sClSetTarget.template insert <citlist_t> (sCItListA, sCItListB);

		sCItListA++;
		sCItListB++;
	}

	sList.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<list::riter_t> (riter_t == riter_t)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sList.template insert <citer_t> (sList.begin (), pClSet->cbegin (), pClSet->cend ());

	sRItListA = sList.rbegin ();
	sRItListB = sList.rbegin ();

	while (sRItListA != sList.rend ())
	{
		sClSetTarget.template insert <ritlist_t> (sRItListA, sRItListB);

		sRItListA++;
		sRItListB++;
	}

	sList.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<list::criter_t> (criter_t == criter_t)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sList.template insert <citer_t> (sList.begin (), pClSet->cbegin (), pClSet->cend ());

	sCRItListA = sList.crbegin ();
	sCRItListB = sList.crbegin ();

	while (sCRItListA != sList.crend ())
	{
		sClSetTarget.template insert <critlist_t> (sCRItListA, sCRItListB);

		sCRItListA++;
		sCRItListB++;
	}

	sList.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<list::iter_t> (>iter_t, iter_t<)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sList.template insert <citer_t> (sList.begin (), pClSet->cbegin (), pClSet->cend ());

	sItListA = sList.begin ();
	sItListB = sList.end ();

	::std::advance<itlist_t, int> (sItListA, nNumEntries / 4);
	::std::advance<itlist_t, int> (sItListB, 0 - (nNumEntries / 4));

	sClSetTarget.template insert <itlist_t> (sItListA, sItListB);

	sList.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<list::citer_t> (>citer_t, citer_t<)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sList.template insert <citer_t> (sList.begin (), pClSet->cbegin (), pClSet->cend ());

	sCItListA = sList.cbegin ();
	sCItListB = sList.cend ();

	::std::advance<citlist_t, int> (sCItListA, nNumEntries / 4);
	::std::advance<citlist_t, int> (sCItListB, 0 - (nNumEntries / 4));

	sClSetTarget.template insert <citlist_t> (sCItListA, sCItListB);

	sList.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<list::riter_t> (>riter_t, riter_t<)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sList.template insert <citer_t> (sList.begin (), pClSet->cbegin (), pClSet->cend ());

	sRItListA = sList.rbegin ();
	sRItListB = sList.rend ();

	::std::advance<ritlist_t, int> (sRItListA, nNumEntries / 4);
	::std::advance<ritlist_t, int> (sRItListB, 0 - (nNumEntries / 4));

	sClSetTarget.template insert <ritlist_t> (sRItListA, sRItListB);

	sList.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<list::criter_t> (>criter_t, criter_t<)" << endl;

	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sList.template insert <citer_t> (sList.begin (), pClSet->cbegin (), pClSet->cend ());

	sCRItListA = sList.crbegin ();
	sCRItListB = sList.crend ();

	::std::advance<critlist_t, int> (sCRItListA, nNumEntries / 4);
	::std::advance<critlist_t, int> (sCRItListB, 0 - (nNumEntries / 4));

	sClSetTarget.template insert <critlist_t> (sCRItListA, sCRItListB);

	sList.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<vector::iter_t> (iter_t, iter_t)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sSetVectorFeed.template insert <citer_t> (pClSet->cbegin (), pClSet->cend ());

	sVector.template insert <typename CBTreeSet_VectorFeed_t::const_iterator> (sVector.begin (), sSetVectorFeed.cbegin (), sSetVectorFeed.cend ());

	sClSetTarget.template insert <itvec_t> (sVector.begin (), sVector.end ());

	sVector.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<vector::citer_t> (citer_t, citer_t)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sSetVectorFeed.template insert <citer_t> (pClSet->cbegin (), pClSet->cend ());

	sVector.template insert <typename CBTreeSet_VectorFeed_t::const_iterator> (sVector.begin (), sSetVectorFeed.cbegin (), sSetVectorFeed.cend ());

	sClSetTarget.template insert <citvec_t> (sVector.cbegin (), sVector.cend ());

	sVector.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<vector::riter_t> (riter_t, riter_t)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sSetVectorFeed.template insert <citer_t> (pClSet->cbegin (), pClSet->cend ());

	sVector.template insert <typename CBTreeSet_VectorFeed_t::const_iterator> (sVector.begin (), sSetVectorFeed.cbegin (), sSetVectorFeed.cend ());

	sClSetTarget.template insert <ritvec_t> (sVector.rbegin (), sVector.rend ());

	sVector.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<vector::criter_t> (criter_t, criter_t)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sSetVectorFeed.template insert <citer_t> (pClSet->cbegin (), pClSet->cend ());

	sVector.template insert <typename CBTreeSet_VectorFeed_t::const_iterator> (sVector.begin (), sSetVectorFeed.cbegin (), sSetVectorFeed.cend ());

	sClSetTarget.template insert <critvec_t> (sVector.crbegin (), sVector.crend ());

	sVector.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<vector::iter_t> (iter_t == iter_t)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sSetVectorFeed.template insert <citer_t> (pClSet->cbegin (), pClSet->cend ());

	sVector.template insert <typename CBTreeSet_VectorFeed_t::const_iterator> (sVector.begin (), sSetVectorFeed.cbegin (), sSetVectorFeed.cend ());

	sItVecA = sVector.begin ();
	sItVecB = sVector.begin ();

	while (sItVecA != sVector.end ())
	{
		sClSetTarget.template insert <itvec_t> (sItVecA, sItVecB);

		sItVecA++;
		sItVecB++;
	}

	sVector.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<vector::citer_t> (citer_t == citer_t)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sSetVectorFeed.template insert <citer_t> (pClSet->cbegin (), pClSet->cend ());

	sVector.template insert <typename CBTreeSet_VectorFeed_t::const_iterator> (sVector.begin (), sSetVectorFeed.cbegin (), sSetVectorFeed.cend ());

	sCItVecA = sVector.cbegin ();
	sCItVecB = sVector.cbegin ();

	while (sCItVecA != sVector.cend ())
	{
		sClSetTarget.template insert <citvec_t> (sCItVecA, sCItVecB);

		sCItVecA++;
		sCItVecB++;
	}

	sVector.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<vector::riter_t> (riter_t == riter_t)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sSetVectorFeed.template insert <citer_t> (pClSet->cbegin (), pClSet->cend ());

	sVector.template insert <typename CBTreeSet_VectorFeed_t::const_iterator> (sVector.begin (), sSetVectorFeed.cbegin (), sSetVectorFeed.cend ());

	sRItVecA = sVector.rbegin ();
	sRItVecB = sVector.rbegin ();

	while (sRItVecA != sVector.rend ())
	{
		sClSetTarget.template insert <ritvec_t> (sRItVecA, sRItVecB);

		sRItVecA++;
		sRItVecB++;
	}

	sVector.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<vector::criter_t> (criter_t == criter_t)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sSetVectorFeed.template insert <citer_t> (pClSet->cbegin (), pClSet->cend ());

	sVector.template insert <typename CBTreeSet_VectorFeed_t::const_iterator> (sVector.begin (), sSetVectorFeed.cbegin (), sSetVectorFeed.cend ());

	sCRItVecA = sVector.crbegin ();
	sCRItVecB = sVector.crbegin ();

	while (sCRItVecA != sVector.crend ())
	{
		sClSetTarget.template insert <critvec_t> (sCRItVecA, sCRItVecB);

		sCRItVecA++;
		sCRItVecB++;
	}

	sVector.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<vector::iter_t> (>iter_t, iter_t<)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sSetVectorFeed.template insert <citer_t> (pClSet->cbegin (), pClSet->cend ());

	sVector.template insert <typename CBTreeSet_VectorFeed_t::const_iterator> (sVector.begin (), sSetVectorFeed.cbegin (), sSetVectorFeed.cend ());

	sItVecA = sVector.begin ();
	sItVecB = sVector.end ();

	::std::advance<itvec_t, int> (sItVecA, nNumEntries / 4);
	::std::advance<itvec_t, int> (sItVecB, 0 - (nNumEntries / 4));

	sClSetTarget.template insert <itvec_t> (sItVecA, sItVecB);

	sList.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<vector::citer_t> (>citer_t, citer_t<)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sSetVectorFeed.template insert <citer_t> (pClSet->cbegin (), pClSet->cend ());

	sVector.template insert <typename CBTreeSet_VectorFeed_t::const_iterator> (sVector.begin (), sSetVectorFeed.cbegin (), sSetVectorFeed.cend ());

	sCItVecA = sVector.cbegin ();
	sCItVecB = sVector.cend ();

	::std::advance<citvec_t, int> (sCItVecA, nNumEntries / 4);
	::std::advance<citvec_t, int> (sCItVecB, 0 - (nNumEntries / 4));

	sClSetTarget.template insert <citvec_t> (sCItVecA, sCItVecB);

	sList.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<vector::riter_t> (>riter_t, riter_t<)" << endl;
	
	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sSetVectorFeed.template insert <citer_t> (pClSet->cbegin (), pClSet->cend ());

	sVector.template insert <typename CBTreeSet_VectorFeed_t::const_iterator> (sVector.begin (), sSetVectorFeed.cbegin (), sSetVectorFeed.cend ());

	sRItVecA = sVector.rbegin ();
	sRItVecB = sVector.rend ();

	::std::advance<ritvec_t, int> (sRItVecA, nNumEntries / 4);
	::std::advance<ritvec_t, int> (sRItVecB, 0 - (nNumEntries / 4));

	sClSetTarget.template insert <ritvec_t> (sRItVecA, sRItVecB);

	sList.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<vector::criter_t> (>criter_t, criter_t<)" << endl;

	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sSetVectorFeed.template insert <citer_t> (pClSet->cbegin (), pClSet->cend ());

	sVector.template insert <typename CBTreeSet_VectorFeed_t::const_iterator> (sVector.begin (), sSetVectorFeed.cbegin (), sSetVectorFeed.cend ());

	sCRItVecA = sVector.crbegin ();
	sCRItVecB = sVector.crend ();

	::std::advance<critvec_t, int> (sCRItVecA, nNumEntries / 4);
	::std::advance<critvec_t, int> (sCRItVecB, 0 - (nNumEntries / 4));

	sClSetTarget.template insert <critvec_t> (sCRItVecA, sCRItVecB);

	sList.clear ();
	pClSet->clear ();
	sClSetTarget.clear ();

	cout << "target::insert<map::iter_t> (iter_t, iter_t)" << endl;

	multiSetPrim_add<::std::set<uint32_t>, ::std::set<uint32_t>::value_type> (&sSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sSetPair.template insert<itset_t> (sSet.begin (), sSet.end ());

	sSetPair.clear ();

	cout << "target::insert<map::citer_t> (citer_t, citer_t)" << endl;
	
	multiSetPrim_add<::std::set<uint32_t>, ::std::set<uint32_t>::value_type> (&sSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	
	sSetPair.template insert<citset_t> (sSet.cbegin (), sSet.cend ());

	sSetPair.clear ();

	cout << "target::insert<map::riter_t> (riter_t, riter_t)" << endl;
	
	multiSetPrim_add<::std::set<uint32_t>, ::std::set<uint32_t>::value_type> (&sSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	
	sSetPair.template insert<ritset_t> (sSet.rbegin (), sSet.rend ());

	sSetPair.clear ();

	cout << "target::insert<map::criter_t> (criter_t, criter_t)" << endl;
	
	multiSetPrim_add<::std::set<uint32_t>, ::std::set<uint32_t>::value_type> (&sSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	
	sSetPair.template insert<critset_t> (sSet.crbegin (), sSet.crend ());

	sSetPair.clear ();

	cout << "target::insert<map::iter_t> (iter_t == iter_t)" << endl;

	multiSetPrim_add<::std::set<uint32_t>, ::std::set<uint32_t>::value_type> (&sSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	
	sItSetA = sSet.begin ();
	sItSetB = sSet.begin ();

	while (sItSetA != sSet.end ())
	{
		sSetPair.template insert <itset_t> (sItSetA, sItSetB);

		sItSetA++;
		sItSetB++;
	}

	sSetPair.clear ();
	
	cout << "target::insert<map::citer_t> (citer_t == citer_t)" << endl;
	
	multiSetPrim_add<::std::set<uint32_t>, ::std::set<uint32_t>::value_type> (&sSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	
	sCItSetA = sSet.cbegin ();
	sCItSetB = sSet.cbegin ();

	while (sCItSetA != sSet.cend ())
	{
		sSetPair.template insert <citset_t> (sCItSetA, sCItSetB);

		sCItSetA++;
		sCItSetB++;
	}

	sSetPair.clear ();
	
	cout << "target::insert<map::riter_t> (riter_t == riter_t)" << endl;
	
	multiSetPrim_add<::std::set<uint32_t>, ::std::set<uint32_t>::value_type> (&sSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	
	sRItSetA = sSet.rbegin ();
	sRItSetB = sSet.rbegin ();

	while (sRItSetA != sSet.rend ())
	{
		sSetPair.template insert <ritset_t> (sRItSetA, sRItSetB);

		sRItSetA++;
		sRItSetB++;
	}

	sSetPair.clear ();
	
	cout << "target::insert<map::criter_t> (criter_t == criter_t)" << endl;
	
	multiSetPrim_add<::std::set<uint32_t>, ::std::set<uint32_t>::value_type> (&sSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	
	sCRItSetA = sSet.crbegin ();
	sCRItSetB = sSet.crbegin ();

	while (sCRItSetA != sSet.crend ())
	{
		sSetPair.template insert <critset_t> (sCRItSetA, sCRItSetB);

		sCRItSetA++;
		sCRItSetB++;
	}

	sSetPair.clear ();
	
	cout << "target::insert<map::iter_t> (>iter_t, iter_t<)" << endl;
	
	multiSetPrim_add<::std::set<uint32_t>, ::std::set<uint32_t>::value_type> (&sSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	
	sItSetA = sSet.begin ();
	sItSetB = sSet.end ();

	::std::advance<itset_t, int> (sItSetA, (int) (nNumEntries / 4));
	::std::advance<itset_t, int> (sItSetB, (int) (0 - (nNumEntries / 4)));

	sSetPair.template insert <itset_t> (sItSetA, sItSetB);

	sSetPair.clear ();

	cout << "target::insert<map::citer_t> (>citer_t, citer_t<)" << endl;
	
	multiSetPrim_add<::std::set<uint32_t>, ::std::set<uint32_t>::value_type> (&sSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	
	sCItSetA = sSet.cbegin ();
	sCItSetB = sSet.cend ();

	::std::advance<citset_t, int> (sCItSetA, (int) (nNumEntries / 4));
	::std::advance<citset_t, int> (sCItSetB, (int) (0 - (nNumEntries / 4)));

	sSetPair.template insert <citset_t> (sCItSetA, sCItSetB);

	sSetPair.clear ();

	cout << "target::insert<map::riter_t> (>riter_t, riter_t<)" << endl;
	
	multiSetPrim_add<::std::set<uint32_t>, ::std::set<uint32_t>::value_type> (&sSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	
	sRItSetA = sSet.rbegin ();
	sRItSetB = sSet.rend ();

	::std::advance<ritset_t, int> (sRItSetA, (int) (nNumEntries / 4));
	::std::advance<ritset_t, int> (sRItSetB, (int) (0 - (nNumEntries / 4)));

	sSetPair.template insert <ritset_t> (sRItSetA, sRItSetB);

	sSetPair.clear ();

	cout << "target::insert<map::criter_t> (>criter_t, criter_t<)" << endl;

	multiSetPrim_add<::std::set<uint32_t>, ::std::set<uint32_t>::value_type> (&sSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	
	sCRItSetA = sSet.crbegin ();
	sCRItSetB = sSet.crend ();

	::std::advance<critset_t, int> (sCRItSetA, (int) (nNumEntries / 4));
	::std::advance<critset_t, int> (sCRItSetB, (int) (0 - (nNumEntries / 4)));

	sSetPair.template insert <critset_t> (sCRItSetA, sCRItSetB);

	sSetPair.clear ();

	cout << "target::insert<multimap::iter_t> (iter_t, iter_t)" << endl;
	
	multiSetPrim_add<::std::multiset<uint32_t>, ::std::multiset<uint32_t>::value_type> (&sMSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	
	sSetPair.template insert<itmset_t> (sMSet.begin (), sMSet.end ());

	sSetPair.clear ();

	cout << "target::insert<multimap::citer_t> (citer_t, citer_t)" << endl;
	
	multiSetPrim_add<::std::multiset<uint32_t>, ::std::multiset<uint32_t>::value_type> (&sMSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	
	sSetPair.template insert<citmset_t> (sMSet.cbegin (), sMSet.cend ());

	sSetPair.clear ();

	cout << "target::insert<multimap::riter_t> (riter_t, riter_t)" << endl;
	
	multiSetPrim_add<::std::multiset<uint32_t>, ::std::multiset<uint32_t>::value_type> (&sMSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	
	sSetPair.template insert<ritmset_t> (sMSet.rbegin (), sMSet.rend ());

	sSetPair.clear ();

	cout << "target::insert<multimap::criter_t> (criter_t, criter_t)" << endl;
	
	multiSetPrim_add<::std::multiset<uint32_t>, ::std::multiset<uint32_t>::value_type> (&sMSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	
	sSetPair.template insert<critmset_t> (sMSet.crbegin (), sMSet.crend ());

	sSetPair.clear ();

	cout << "target::insert<multimap::iter_t> (iter_t == iter_t)" << endl;
	
	multiSetPrim_add<::std::multiset<uint32_t>, ::std::multiset<uint32_t>::value_type> (&sMSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	
	sItMSetA = sMSet.begin ();
	sItMSetB = sMSet.begin ();

	while (sItMSetA != sMSet.end ())
	{
		sSetPair.template insert <itmset_t> (sItMSetA, sItMSetB);

		sItMSetA++;
		sItMSetB++;
	}

	sSetPair.clear ();
	
	cout << "target::insert<multimap::citer_t> (citer_t == citer_t)" << endl;
	
	multiSetPrim_add<::std::multiset<uint32_t>, ::std::multiset<uint32_t>::value_type> (&sMSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	
	sCItMSetA = sMSet.cbegin ();
	sCItMSetB = sMSet.cbegin ();

	while (sCItMSetA != sMSet.cend ())
	{
		sSetPair.template insert <citmset_t> (sCItMSetA, sCItMSetB);

		sCItMSetA++;
		sCItMSetB++;
	}

	sSetPair.clear ();
	
	cout << "target::insert<multimap::riter_t> (riter_t == riter_t)" << endl;
	
	multiSetPrim_add<::std::multiset<uint32_t>, ::std::multiset<uint32_t>::value_type> (&sMSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	
	sRItMSetA = sMSet.rbegin ();
	sRItMSetB = sMSet.rbegin ();

	while (sRItMSetA != sMSet.rend ())
	{
		sSetPair.template insert <ritmset_t> (sRItMSetA, sRItMSetB);

		sRItMSetA++;
		sRItMSetB++;
	}

	sSetPair.clear ();
	
	cout << "target::insert<multimap::criter_t> (criter_t == criter_t)" << endl;
	
	multiSetPrim_add<::std::multiset<uint32_t>, ::std::multiset<uint32_t>::value_type> (&sMSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	
	sCRItMSetA = sMSet.crbegin ();
	sCRItMSetB = sMSet.crbegin ();

	while (sCRItMSetA != sMSet.crend ())
	{
		sSetPair.template insert <critmset_t> (sCRItMSetA, sCRItMSetB);

		sCRItMSetA++;
		sCRItMSetB++;
	}

	sSetPair.clear ();
	
	cout << "target::insert<multimap::iter_t> (>iter_t, iter_t<)" << endl;
	
	multiSetPrim_add<::std::multiset<uint32_t>, ::std::multiset<uint32_t>::value_type> (&sMSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	
	sItMSetA = sMSet.begin ();
	sItMSetB = sMSet.end ();

	::std::advance<itmset_t, int> (sItMSetA, (int) (nNumEntries / 4));
	::std::advance<itmset_t, int> (sItMSetB, (int) (0 - (nNumEntries / 4)));

	sSetPair.template insert <itmset_t> (sItMSetA, sItMSetB);

	sSetPair.clear ();

	cout << "target::insert<multimap::citer_t> (>citer_t, citer_t<)" << endl;
	
	multiSetPrim_add<::std::multiset<uint32_t>, ::std::multiset<uint32_t>::value_type> (&sMSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	
	sCItMSetA = sMSet.cbegin ();
	sCItMSetB = sMSet.cend ();

	::std::advance<citmset_t, int> (sCItMSetA, (int) (nNumEntries / 4));
	::std::advance<citmset_t, int> (sCItMSetB, (int) (0 - (nNumEntries / 4)));

	sSetPair.template insert <citmset_t> (sCItMSetA, sCItMSetB);

	sSetPair.clear ();

	cout << "target::insert<multimap::riter_t> (>riter_t, riter_t<)" << endl;
	
	multiSetPrim_add<::std::multiset<uint32_t>, ::std::multiset<uint32_t>::value_type> (&sMSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	
	sRItMSetA = sMSet.rbegin ();
	sRItMSetB = sMSet.rend ();

	::std::advance<ritmset_t, int> (sRItMSetA, (int) (nNumEntries / 4));
	::std::advance<ritmset_t, int> (sRItMSetB, (int) (0 - (nNumEntries / 4)));

	sSetPair.template insert <ritmset_t> (sRItMSetA, sRItMSetB);

	sSetPair.clear ();

	cout << "target::insert<multimap::criter_t> (>criter_t, criter_t<)" << endl;

	multiSetPrim_add<::std::multiset<uint32_t>, ::std::multiset<uint32_t>::value_type> (&sMSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	
	sCRItMSetA = sMSet.crbegin ();
	sCRItMSetB = sMSet.crend ();

	::std::advance<critmset_t, int> (sCRItMSetA, (int) (nNumEntries / 4));
	::std::advance<critmset_t, int> (sCRItMSetB, (int) (0 - (nNumEntries / 4)));

	sSetPair.template insert <critmset_t> (sCRItMSetA, sCRItMSetB);

	sSetPair.clear ();
}

template <class _t_set>
void TestBTreeSetSTLifEraseViaIterator (_t_set *pClSet, uint32_t nNumEntries)
{
	typedef typename _t_set::const_iterator						citer_t;

	uint32_t									nLastKey = 0;
	citer_t										sIter;
	citer_t										sIterRslt;
	uint32_t									nDebug = 0;
	
	cout << "exercises method compatible to STL interface CBTreeSet<>:: erase (const_iterator)" << endl;

	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	while (pClSet->size () > 0)
	{
		sIter = pClSet->cbegin ();

		sIter += (int) (generate_rand32 () % pClSet->size ());

		sIterRslt = pClSet->erase (sIter);

		if (sIter != sIterRslt)
		{
			cerr << endl;
			cerr << "TestBTreeSetSTLifEraseViaIterator: returned iterator mismatches!" << endl;

			exit (-1);
		}

		nDebug++;
	}
}

template <class _t_set>
void TestBTreeSetSTLifEraseViaKey (_t_set *pClSet, uint32_t nNumEntries, uint32_t nInstances)
{
	typedef typename _t_set::const_iterator		citer_t;
	
	typename _t_set::value_t					nLastKey;
	citer_t										sIter;
	uint32_t									i;
	typename _t_set::sizetype_t					nRslt;
	
	cout << "exercises method compatible to STL interface CBTreeSet<>:: erase (const keytype &)" << endl;

	for (i = 0; i < nInstances; i++)
	{
		nLastKey = 0;

		multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	}

	while (pClSet->size () > 0)
	{
		sIter = pClSet->cbegin ();

		sIter += (int) (generate_rand32 () % pClSet->size ());

		nRslt = pClSet->erase ((typename _t_set::value_t)(*sIter));

		if (nRslt != 1)
		{
			cerr << endl;
			cerr << "TestBTreeSetSTLifEraseViaKey: unexpected number of items deleted!" << endl;

			exit (-1);
		}
	}
}

template <class _t_set>
void TestBTreeSetSTLifEraseViaIteratorMultiple (_t_set *pClSet, uint32_t nNumEntries, uint32_t nInstances)
{
	typedef typename _t_set::const_iterator										citer_t;

	uint32_t									nLastKey;
	citer_t										sIterBegin;
	citer_t										sIterEnd;
	citer_t										sIterRslt;
	uint32_t									i;
	
	cout << "exercises method compatible to STL interface CBTreeSet<>:: erase (const_iterator, const_iterator)" << endl;

	for (i = 0; i < nInstances; i++)
	{
		nLastKey = 0;

		multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);
	}

	while (pClSet->size () > 0)
	{
		sIterBegin = pClSet->cbegin ();
		sIterEnd = pClSet->cend ();

		if (pClSet->size () > 1)
		{
			sIterBegin += (int) (generate_rand32 () % (pClSet->size () / 2));
			sIterEnd -= (int) (generate_rand32 () % (pClSet->size () / 2));
		}

		sIterRslt = pClSet->erase (sIterBegin, sIterEnd);

		if (sIterRslt != sIterBegin)
		{
			cerr << endl;
			cerr << "TestBTreeSetSTLifEraseViaIteratorMultiple: returned iterator mismatches!" << endl;

			exit (-1);
		}
	}
}

template<class _t_set>
void TestBTreeSetSTLifKeyComp (_t_set *pClSet, uint32_t nNumEntries)
{
	typedef typename _t_set::iterator		iter_t;

	uint32_t									nLastKey = 0;
	iter_t										sIterBegin;
	iter_t										sIterEnd;
	iter_t										sIter;
	iter_t										sIterUpper;
	uint32_t									nKey;
	uint32_t									nNextKey;
	typename _t_set::key_compare			sMMComp = pClSet->key_comp ();
	
	cout << "exercises method compatible to STL interface CBTreeSet<>:: key_comp ()" << endl;

	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sIterBegin = pClSet->begin ();
	sIterEnd = pClSet->end ();

	for (sIter = sIterBegin; sIter != sIterEnd; sIter++)
	{
		nKey = ((typename _t_set::value_t)(*sIter));

		sIterUpper = pClSet->upper_bound (nKey);

		if (sIterUpper != sIterEnd)
		{
			nNextKey = ((typename _t_set::value_t)(*sIterUpper));

			if (!sMMComp (nKey, nNextKey))
			{
				cerr << endl;
				cerr << "TestBTreeSetSTLifKeyComp: ERROR: CBTreeSet::key_compare (const keytype &, const keytype &) delivered unexpected result!" << endl;

				exit (-1);
			}
		}
	}
}

template<class _t_set>
void TestBTreeSetSTLifValueComp (_t_set *pClSet, uint32_t nNumEntries)
{
	typedef typename _t_set::iterator		iter_t;

	uint32_t									nLastKey = 0;
	iter_t										sIterBegin;
	iter_t										sIterEnd;
	iter_t										sIter;
	iter_t										sIterUpper;
	uint32_t									nKey;
	typename _t_set::value_compare			sMMComp = pClSet->value_comp ();
	
	cout << "exercises method compatible to STL interface CBTreeSet<>:: value_comp ()" << endl;

	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sIterBegin = pClSet->begin ();
	sIterEnd = pClSet->end ();

	for (sIter = sIterBegin; sIter != sIterEnd; sIter++)
	{
		nKey = ((typename _t_set::value_t)(*sIter));

		sIterUpper = pClSet->upper_bound (nKey);

		if (sIterUpper != sIterEnd)
		{
			if (!sMMComp (((typename _t_set::value_t)(*sIter)), ((typename _t_set::value_t)(*sIterUpper))))
			{
				cerr << endl;
				cerr << "TestBTreeSetSTLifValueComp: ERROR: CBTreeSet::value_compare (const valuetype &, const valuetype &) delivered unexpected result!" << endl;

				exit (-1);
			}
		}
	}
}

template <class _t_set>
void TestBTreeSetSTLifSwap (_t_set *pClSet, uint32_t nNumEntries)
{
	typedef typename _t_set::const_iterator			citer_t;

	uint32_t						nLastKey = 0;
	_t_set						sClSetTarget (*pClSet, false);
	_t_set						sClSetRef (*pClSet, false);
	_t_set						sClSetTargetRef (*pClSet, false);

	cout << "exercises method compatible to STL interface CBTreeSet<>:: swap (CBTreeSet &)" << endl;

	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sClSetRef.template insert<citer_t> (pClSet->cbegin (), pClSet->cend ());

	if ((*pClSet) != sClSetRef)
	{
		cerr << "ERROR: Unexpected multimap mismatch!" << endl;

		exit (-1);
	}

	multiSetPrim_add<_t_set, typename _t_set::value_t> (&sClSetTarget, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_RANDOM_KEY);

	sClSetTargetRef.template insert<citer_t> (sClSetTarget.cbegin (), sClSetTarget.cend ());

	if (sClSetTarget != sClSetTargetRef)
	{
		cerr << "ERROR: Unexpected target mismatch!" << endl;

		exit (-1);
	}

	pClSet->swap (sClSetTarget);

	if ((*pClSet) != sClSetTargetRef)
	{
		cerr << "ERROR: swapped multimap mismatches target reference!" << endl;

		exit (-1);
	}

	if (sClSetTarget != sClSetRef)
	{
		cerr << "ERROR: target mismatches multimap reference!" << endl;

		exit (-1);
	}

	sClSetTarget.swap (*pClSet);

	if ((*pClSet) != sClSetRef)
	{
		cerr << "ERROR: multimap mismatches multimap reference!" << endl;

		exit (-1);
	}

	if (sClSetTarget != sClSetTargetRef)
	{
		cerr << "ERROR: target mismatches target reference!" << endl;

		exit (-1);
	}
}

template <class _t_set>
void TestBTreeSetSTLifFind (_t_set *pClSet, uint32_t nNumEntries)
{
	typedef typename _t_set::const_iterator			citer_t;

	typename _t_set::value_t		nLastKey = 1;
	citer_t							sCIter;
	citer_t							sCIterRslt;
	
	cout << "exercises method compatible to STL interface CBTreeSet<>:: find (const _t_keytype &)" << endl;

	multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_ASCEND_KEY);

	for (sCIter = pClSet->cbegin (); sCIter != pClSet->cend (); sCIter++)
	{
		sCIterRslt = pClSet->find ((typename _t_set::value_t)(*sCIter));

		if (sCIter != sCIterRslt)
		{
			cerr << endl;
			cerr << "TestBTreeSetSTLifFind: ERROR: iterator mismatch!" << endl;

			exit (-1);
		}
	}

	sCIterRslt = pClSet->find (0);

	if (sCIterRslt != pClSet->cend ())
	{
		cerr << endl;
		cerr << "TestBTreeSetSTLifFind: ERROR: find () didn't return cend () on lower bound check!" << endl;

		exit (-1);
	}

	sCIterRslt = pClSet->find (nNumEntries + 1);

	if (sCIterRslt != pClSet->cend ())
	{
		cerr << endl;
		cerr << "TestBTreeSetSTLifFind: ERROR: find () didn't return cend () on upper bound check!" << endl;

		exit (-1);
	}
}

template <class _t_set>
void TestBTreeSetSTLifLowerBoundUpperBound (_t_set *pClSet, uint32_t nNumEntries, uint32_t nInstance)
{
	typedef typename _t_set::const_iterator			citer_t;

	uint32_t						nLastKey;
	uint32_t						i;
	citer_t							sCIterLower;
	citer_t							sCIterUpper;
	
	cout << "exercises method compatible to STL interface CBTreeSet<>:: lower_bound () upper_bound () count ()" << endl;
	
	for (i = 0; i < nInstance; i++)
	{
		nLastKey = 1;

		multiSetPrim_add<_t_set, typename _t_set::value_t> (pClSet, nNumEntries, nLastKey, BTREETEST_MULTISET_PRIMITIVE_ASCEND_KEY);
	}

	for (i = 0; i < nNumEntries; i++)
	{
		sCIterLower = pClSet->lower_bound (i + 1);
		sCIterUpper = pClSet->upper_bound (i + 1);

		sCIterLower += (int) 1;

		if (sCIterLower != sCIterUpper)
		{
			cerr << endl;
			cerr << "TestBTreeSetSTLifLowerBoundUpperBound: ERROR: boundary mismatch!" << endl;

			exit (-1);
		}

		if (pClSet->count (i + 1) != 1)
		{
			cerr << endl;
			cerr << "TestBTreeSetSTLifLowerBoundUpperBound: ERROR: count () returned with unexpected value!" << endl;

			exit (-1);
		}
	}

	sCIterLower = pClSet->lower_bound (0);

	if (sCIterLower != pClSet->cbegin ())
	{
		cerr << endl;
		cerr << "TestBTreeSetSTLifLowerBoundUpperBound: ERROR: lower_bound () didn't return cbegin () when testing for lowest key!" << endl;

		exit (-1);
	}

	sCIterUpper = pClSet->upper_bound (nNumEntries + 1);

	if (sCIterUpper != pClSet->cend ())
	{
		cerr << endl;
		cerr << "TestBTreeSetSTLifLowerBoundUpperBound: ERROR: upper_bound () didn't return cend () when testing for lowest key!" << endl;

		exit (-1);
	}
}

template <class _t_sizetype, class _t_nodeiter, class _t_subnodeiter, class _t_datalayerproperties, class _t_datalayer>
void TestBTreeSTLset (uint32_t nTestNum, _t_subnodeiter nNodeSize, _t_datalayerproperties sDataProperties, bayerTreeCacheDescription_t &sCacheDesc, int argc, char **argv)
{
	typedef CBTreeTestSet<_t_sizetype, _t_nodeiter, _t_subnodeiter, _t_datalayerproperties, _t_datalayer>		CBTreeTestSet_t;

	CBTreeTestSet_t		*pClSet = new CBTreeTestSet_t (sDataProperties, &sCacheDesc, nNodeSize);

	if (pClSet == NULL)
	{
		cerr << "TestBTreeSTLmultiMap: ERROR: insufficient memory!" << endl;

		exit (-1);
	}

	cout << "b-tree multi-map test bench selected" << endl;

	switch (nTestNum)
	{
	case BTREETEST_SET_ASSIGNMENT_OPERATOR	:
		{
			TestBTreeSetSTLifAssignmentOperator<CBTreeTestSet_t> (pClSet, 64);

			break;
		}
	
	case BTREETEST_SET_STL_IF_INSERT	:
		{
			TestBTreeSetSTLifInsert<CBTreeTestSet_t> (pClSet, 64);

			break;
		}
	
	case BTREETEST_SET_STL_IF_INSERT_VIA_ITERATOR	:
		{
			TestBTreeSetSTLifInsertViaIterator<CBTreeTestSet_t> (pClSet, 64, sDataProperties, &sCacheDesc, nNodeSize);

			break;
		}
	
	case BTREETEST_SET_STL_IF_ERASE_VIA_ITERATOR	:
		{
			TestBTreeSetSTLifEraseViaIterator<CBTreeTestSet_t> (pClSet, 64);

			break;
		}
	
	case BTREETEST_SET_STL_IF_ERASE_VIA_KEY	:
		{
			TestBTreeSetSTLifEraseViaKey<CBTreeTestSet_t> (pClSet, 64, 5);

			break;
		}
	
	case BTREETEST_SET_STL_IF_ERASE_VIA_ITERATOR_MULTIPLE	:
		{
			TestBTreeSetSTLifEraseViaIteratorMultiple<CBTreeTestSet_t> (pClSet, 64, 5);

			break;
		}
	
	case BTREETEST_SET_STL_IF_KEY_COMP	:
		{
			TestBTreeSetSTLifKeyComp<CBTreeTestSet_t> (pClSet, 64);

			break;
		}
	
	case BTREETEST_SET_STL_IF_VALUE_COMP	:
		{
			TestBTreeSetSTLifValueComp<CBTreeTestSet_t> (pClSet, 64);

			break;
		}
	
	case BTREETEST_SET_STL_IF_SWAP	:
		{
			TestBTreeSetSTLifSwap<CBTreeTestSet_t> (pClSet, 128);

			break;
		}
	
	case BTREETEST_SET_STL_IF_FIND	:
		{
			TestBTreeSetSTLifFind<CBTreeTestSet_t> (pClSet, 64);

			break;
		}
	
	case BTREETEST_SET_STL_IF_LOWER_BOUND_UPPER_BOUND	:
		{
			TestBTreeSetSTLifLowerBoundUpperBound<CBTreeTestSet_t> (pClSet, 64, 5);

			break;
		}
	
	default:
		{
			cerr << "ERROR: TestBTreeSTLmultiMap: Unknown test or test not specified!" << endl;

			break;
		}
	}

	delete pClSet;
}