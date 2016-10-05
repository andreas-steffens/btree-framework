/************************************************************
**
** file:	btreeassociativebase.h
** author:	Andreas Steffens
** license:	GPL v2
**
** description:
**
** This file contains code for the b-tree framework's
** STL base class, containing a common sub-set of methods
** shared between all STL interchangeable container classes.
**
************************************************************/

#ifndef BTREEASSOCAITIVEBASE_H
#define	BTREEASSOCAITIVEBASE_H

#include <utility>

#include "abstract_data_classes/btreeassociative.h"
#include "iterators/btreeiter.h"

template<class _t_data, class _t_key = _t_data, class _t_datalayerproperties = CBTreeIOpropertiesRAM <> >
class CBTreeAssociativeBase
	:	public CBTreeAssociative<_t_data, _t_key, _t_datalayerproperties>
{
public:

	typedef _t_data												value_type;
	typedef _t_key												key_type;
	typedef typename _t_datalayerproperties::size_type			size_type;
	typedef typename _t_datalayerproperties::node_iter_type		node_iter_type;
	typedef typename _t_datalayerproperties::sub_node_iter_type	sub_node_iter_type;
	typedef _t_datalayerproperties								data_layer_properties_type;
	typedef typename _t_datalayerproperties::data_layer_type	data_layer_type;

	typedef value_type&											reference;
	typedef const value_type&									const_reference;
	typedef value_type*											pointer;
	typedef const value_type*									const_pointer;
	typedef	typename ::std::make_signed<size_type>::type		difference_type;

	typedef CBTreeAssociativeBase								CBTreeAssociativeBase_t;

	typedef CBTreeAssociative<_t_data, _t_key, _t_datalayerproperties>
																CBTreeAssociative_t;

	typedef typename CBTreeAssociative_t::CBTreeBaseDefaults_t	CBTreeBaseDefaults_t;

	typedef CBTreeIf<value_type, size_type>						CBTreeIf_t;

	typedef typename CBTreeIf_t::iterator						iterator;
	typedef	typename CBTreeIf_t::const_iterator					const_iterator;
	typedef typename CBTreeIf_t::reverse_iterator				reverse_iterator;
	typedef	typename CBTreeIf_t::const_reverse_iterator			const_reverse_iterator;

	typedef	typename CBTreeBaseDefaults_t::node_t				node_t;

	// construction
							CBTreeAssociativeBase<_t_data, _t_key, _t_datalayerproperties>
													(_t_datalayerproperties &rDataLayerProperties, const bayerTreeCacheDescription_t *psCacheDescription, sub_node_iter_type nNodeSize);

							CBTreeAssociativeBase<_t_data, _t_key, _t_datalayerproperties>
													(const CBTreeAssociativeBase_t &rBT, bool bAssign = true);

	// destruction
	virtual					~CBTreeAssociativeBase<_t_data, _t_key, _t_datalayerproperties>
													();

	CBTreeAssociativeBase_t &		operator=				(const CBTreeAssociativeBase_t &rBT);

	size_type				max_size				() const;

	iterator				lower_bound				(const key_type &rKey);
	const_iterator			lower_bound				(const key_type &rKey) const;

	iterator				upper_bound				(const key_type &rKey);
	const_iterator			upper_bound				(const key_type &rKey) const;

protected:

	int						comp					(const key_type &rKey0, const key_type &rKey1) const;

	static int				comp					(const key_type &rKey0, const key_type &rKey1, ::std::true_type);
	static int				comp					(const key_type &rKey0, const key_type &rKey1, ::std::false_type);

	void					_swap					(CBTreeAssociativeBase_t &rContainer);

public:

	friend class CBTreeIterator<CBTreeIf_t>;
	friend class CBTreeConstIterator<CBTreeIf_t>;
	friend class CBTreeReverseIterator<iterator>;
	friend class CBTreeConstReverseIterator<const_iterator>;
};

#endif // BTREEASSOCAITIVEBASE_H

#include "btreeassociativebase.cpp"
