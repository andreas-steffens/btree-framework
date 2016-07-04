/************************************************************
**
** file:	btreemultimap.cpp
** author:	Andreas Steffens
** license:	GPL v2
**
** description:
**
** This file contains code for the b-tree framework's
** multi map data class, which has an interface interchangeable
** with ::std::multimap.
**
************************************************************/

#ifndef BTREEMULTIMAP_CPP
#define	BTREEMULTIMAP_CPP

#include "./associative/btreemultimap.h"

template<class _t_keytype, class _t_maptype, class _t_datalayerproperties>
CBTreeMultiMap<_t_keytype, _t_maptype, _t_datalayerproperties>::CBTreeMultiMap
	(_t_datalayerproperties &rDataLayerProperties, const bayerTreeCacheDescription_t *psCacheDescription, typename _t_datalayerproperties::sub_node_iter_type nNodeSize)
	:	CBTreeAssociativeBase<typename CBTreeMultiMap<_t_keytype, _t_maptype, _t_datalayerproperties>::value_type, _t_keytype, _t_datalayerproperties>
		(
			rDataLayerProperties, 
			psCacheDescription, 
			nNodeSize
		)
{
}

template<class _t_keytype, class _t_maptype, class _t_datalayerproperties>
CBTreeMultiMap<_t_keytype, _t_maptype, _t_datalayerproperties>::CBTreeMultiMap
	(const CBTreeMultiMap_t &rBT, bool bAssign)
	:	CBTreeAssociativeBase<typename CBTreeMultiMap<_t_keytype, _t_maptype, _t_datalayerproperties>::value_type, _t_keytype, _t_datalayerproperties>
	(
		dynamic_cast<const CBTreeAssociativeBase<typename CBTreeMultiMap<_t_keytype, _t_maptype, _t_datalayerproperties>::value_type, _t_keytype, _t_datalayerproperties> &> (rBT), 
		bAssign
	)
{
}

template<class _t_keytype, class _t_maptype, class _t_datalayerproperties>
CBTreeMultiMap<_t_keytype, _t_maptype, _t_datalayerproperties>::~CBTreeMultiMap ()
{
}

template<class _t_keytype, class _t_maptype, class _t_datalayerproperties>
void CBTreeMultiMap<_t_keytype, _t_maptype, _t_datalayerproperties>::swap (typename CBTreeMultiMap<_t_keytype, _t_maptype, _t_datalayerproperties>::CBTreeAssociativeIf_t &rContainerIf)
{
	CBTreeMultiMap_t		&rContainer = dynamic_cast<CBTreeMultiMap_t &> (rContainerIf);

	this->swap (rContainer);
}

template<class _t_keytype, class _t_maptype, class _t_datalayerproperties>
void CBTreeMultiMap<_t_keytype, _t_maptype, _t_datalayerproperties>::swap (typename CBTreeMultiMap<_t_keytype, _t_maptype, _t_datalayerproperties>::CBTreeMultiMap_t &rContainer)
{
	if (this != &rContainer)
	{
		this->_swap (rContainer);
	}
}

template<class _t_keytype, class _t_maptype, class _t_datalayerproperties>
typename CBTreeMultiMap<_t_keytype, _t_maptype, _t_datalayerproperties>::key_compare
	CBTreeMultiMap<_t_keytype, _t_maptype, _t_datalayerproperties>::key_comp () const
{
	key_compare		sRslt;

	sRslt.pThis = (CBTreeAssociativeIf_t *) (this);

	return (sRslt);
}

template<class _t_keytype, class _t_maptype, class _t_datalayerproperties>
typename CBTreeMultiMap<_t_keytype, _t_maptype, _t_datalayerproperties>::value_compare
	CBTreeMultiMap<_t_keytype, _t_maptype, _t_datalayerproperties>::value_comp () const
{
	value_compare		sRslt;

	sRslt.pThis = (CBTreeAssociativeIf_t *) (this);

	return (sRslt);
}

template<class _t_keytype, class _t_maptype, class _t_datalayerproperties>
typename CBTreeMultiMap<_t_keytype, _t_maptype, _t_datalayerproperties>::key_type *CBTreeMultiMap<_t_keytype, _t_maptype, _t_datalayerproperties>::extract_key (typename CBTreeMultiMap<_t_keytype, _t_maptype, _t_datalayerproperties>::key_type *pKey, const typename CBTreeMultiMap<_t_keytype, _t_maptype, _t_datalayerproperties>::value_type &rData) const
{
	*pKey = rData.first;

	return (pKey);
}

template<class _t_keytype, class _t_maptype, class _t_datalayerproperties>
void CBTreeMultiMap<_t_keytype, _t_maptype, _t_datalayerproperties>::_swap (typename CBTreeMultiMap<_t_keytype, _t_maptype, _t_datalayerproperties>::CBTreeMultiMap_t &rContainer)
{
	CBTreeAssociativeBase_t		&rSTLbaseContainerContainer = dynamic_cast <CBTreeAssociativeBase_t &> (rContainer);
	
	CBTreeAssociativeBase_t::_swap (rSTLbaseContainerContainer);
}

#endif // BTREEMULTIMAP_CPP
