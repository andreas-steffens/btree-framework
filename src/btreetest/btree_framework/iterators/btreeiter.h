/************************************************************
**
** file:	btreeiter.h
** author:	Andreas Steffens
** license:	GPL v2
**
** description:
**
** This file contains code for the b-tree framework's
** iterator classes.
**
************************************************************/

#ifndef	BTREEITER_H
#define	BTREEITER_H

#include <iterator>

#include <stdint.h>

#include "btreecommon.h"
#include "btreeaux.h"

template<class _ti_container>
class CBTreeIterator;

template<class _ti_container>
class CBTreeConstIterator : public ::std::iterator < ::std::random_access_iterator_tag, typename _ti_container::value_type, typename _ti_container::difference_type, typename _ti_container::pointer, typename _ti_container::reference>
{
public:

	typedef CBTreeConstIterator									CBTreeBaseConstIterator_t;

	typedef _ti_container										container_t;

	typedef typename container_t::value_type					value_type;
	typedef typename container_t::size_type						size_type;
	typedef typename container_t::difference_type				difference_type;
	typedef typename container_t::reference						reference;
	typedef typename container_t::pointer						pointer;
	
								CBTreeConstIterator<_ti_container> ();
								CBTreeConstIterator<_ti_container> (const _ti_container *pContainer, const size_type nPos, const bool bRegister = true);
								CBTreeConstIterator<_ti_container> (const _ti_container *pContainer, const size_type nPos, const void *pExternState, const btree_time_stamp_t sTimeStamp, const bool bRegister = true);
								CBTreeConstIterator<_ti_container> (const CBTreeConstIterator &rIter, const bool bRegister = true);
								CBTreeConstIterator<_ti_container> (const CBTreeIterator<_ti_container> &rIter, const bool bRegister = true);

								~CBTreeConstIterator<_ti_container> ();

	void						detach ();
	
	void						swap (CBTreeConstIterator &rRight);
	
	CBTreeConstIterator &		operator= (const CBTreeConstIterator &rIter);
	CBTreeConstIterator &		operator= (const CBTreeIterator<_ti_container> &rIter);

	bool						operator== (const CBTreeConstIterator &rIter) const;
	bool						operator!= (const CBTreeConstIterator &rIter) const;
	
	value_type &				operator* ();
	value_type *				operator-> ();

	CBTreeConstIterator&		operator++ ();
	CBTreeConstIterator			operator++ (int);
	CBTreeConstIterator&		operator-- ();
	CBTreeConstIterator			operator-- (int);
	
//	CBTreeConstIterator&		operator+= (const int nOperand);
	CBTreeConstIterator&		operator+= (const size_type nOperand);
	CBTreeConstIterator&		operator+= (const CBTreeConstIterator &rIter);

//	CBTreeConstIterator&		operator-= (const int nOperand);
	CBTreeConstIterator&		operator-= (const size_type nOperand);
	CBTreeConstIterator&		operator-= (const CBTreeConstIterator &rIter);
	
//	const CBTreeConstIterator	operator+ (const int nOperand) const;
	const CBTreeConstIterator	operator+ (const size_type nOperand) const;
	const CBTreeConstIterator	operator+ (const CBTreeConstIterator &rIter) const;

//	const CBTreeConstIterator	operator- (const int nOperand) const;
	const CBTreeConstIterator	operator- (const size_type nOperand) const;
	const size_type				operator- (const CBTreeConstIterator &rIter) const;

	bool						operator<  (const CBTreeConstIterator &rIter) const;
	bool						operator<= (const CBTreeConstIterator &rIter) const;
	bool						operator>  (const CBTreeConstIterator &rIter) const;
	bool						operator>= (const CBTreeConstIterator &rIter) const;

	value_type&					operator[] (const int nPos);
	value_type&					operator[] (const size_type nPos);

	_ti_container				*get_container	();
	bool						is_btree_valid	();

	bool						is_evaluated	();

	void						sync			();

	size_type					get_pos			();
	void						*get_iterator_state ();

	void						set_time_stamp	(_ti_container *pContainer);
	
protected:

	typedef struct btree_iter_last_access_s
	{
		btree_time_stamp_t		sTimeStamp;
		_ti_container			*pContainer;

		bool			operator== (const struct btree_iter_last_access_s &rLA) const
		{
			return ((sTimeStamp == rLA.sTimeStamp) && (pContainer == rLA.pContainer));
		}

		bool			operator!= (const struct btree_iter_last_access_s &rLA) const
		{
			return ((sTimeStamp != rLA.sTimeStamp) && (pContainer != rLA.pContainer));
		}
	} btree_iter_last_access_t;

	void						increment_by	(const size_type nOperand);
	void						decrement_by	(const size_type nOperand);
	
	bool						out_of_range	();
	
	void						evaluate		();
	
	void						evaluate_by_seek ();
	
	size_type					get_pos			() const;

	bool						is_time_stamp_up_to_date	();

	void						invalidate_time_stamp	();

	void						update_time_stamp	();
	
	float						get_average_node_hops (const size_type nHopDistance) const;
	
	void						assign			(const CBTreeConstIterator &rIter);

	void						register_iterator	(_ti_container *pContainer);
	void						unregister_iterator (_ti_container *pContainer);
	
	_ti_container				*m_pContainer;
	size_type					m_nPos;
	void						*m_pExternState;
	value_type					m_sData;
	value_type					m_sSubScriptResult;
	btree_iter_last_access_t	m_sTimeStamp;

public:

	template<class _fti_container>
	friend typename ::CBTreeConstIterator<_fti_container> operator+
	(
		typename _fti_container::size_type nLhs, 
		const typename ::CBTreeConstIterator<_fti_container> &nRhs
	);

	template<class _fti_container>
	friend typename ::CBTreeConstIterator<_fti_container> operator+
	(
		int nLhs, 
		const typename ::CBTreeConstIterator<_fti_container> &nRhs
	);
};

template<class _ti_container>
typename ::CBTreeConstIterator<_ti_container> operator+
(
	typename _ti_container::size_type nLhs, 
	const typename ::CBTreeConstIterator<_ti_container> &nRhs
);

template<class _ti_container>
typename ::CBTreeConstIterator<_ti_container> operator+
(
	int nLhs, 
	const typename ::CBTreeConstIterator<_ti_container> &nRhs
);

template<class _ti_container>
class CBTreeIteratorSubScriptWrapper;

template<class _t_iterator>
class CBTreeReverseIterator;

template<class _ti_container>
class CBTreeIterator : public CBTreeConstIterator<_ti_container>
{
public:

	typedef CBTreeIterator										CBTreeIterator_t;

	typedef _ti_container										container_t;

	typedef typename container_t::value_type					value_type;
	typedef typename container_t::size_type						size_type;
	typedef typename container_t::difference_type				difference_type;
	typedef typename container_t::reference						reference;
	typedef typename container_t::pointer						pointer;

									CBTreeIterator<_ti_container> ();
									CBTreeIterator<_ti_container> (const _ti_container *pContainer, const size_type nPos, const bool bRegister = true);
									CBTreeIterator<_ti_container> (const _ti_container *pContainer, const size_type nPos, const void *pExternState, const btree_time_stamp_t sTimeStamp, const bool bRegister = true);
									CBTreeIterator<_ti_container> (const CBTreeIterator &rIter, const bool bRegister = true);
						explicit	CBTreeIterator<_ti_container> (const CBTreeReverseIterator<CBTreeIterator<_ti_container> > &rRIter, const bool bRegister = true);
						
									CBTreeIterator<_ti_container> (const CBTreeConstIterator<_ti_container> &rIter, const bool bRegister = true);

									~CBTreeIterator<_ti_container> ();

	const value_type &				operator* () const;

	CBTreeIteratorSubScriptWrapper<_ti_container>
									operator* ();
	
	CBTreeIterator&					operator= (const CBTreeIterator &rIter);

	CBTreeIteratorSubScriptWrapper<_ti_container>
									operator[] (const int nPos);

	CBTreeIteratorSubScriptWrapper<_ti_container>
									operator[] (const size_type nPos);

protected:

	void							set			(const value_type &rData);

public:

	friend typename ::CBTreeIteratorSubScriptWrapper<_ti_container>;

	template<class _fti_container>
	friend typename ::CBTreeIterator<_fti_container> operator+
	(
		typename _fti_container::_t_sizetype nLhs, 
		const typename ::CBTreeIterator<_fti_container> &nRhs
	);

	template<class _fti_container>
	friend typename ::CBTreeIterator<_fti_container> operator+
	(
		int nLhs, 
		const typename ::CBTreeIterator<_fti_container> &nRhs
	);
};

template<class _ti_container>
typename ::CBTreeIterator<_ti_container> operator+
(
	typename _ti_container::_t_sizetype nLhs, 
	const typename ::CBTreeIterator<_ti_container> &nRhs
);

template<class _ti_container>
typename ::CBTreeIterator<_ti_container> operator+
(
	int nLhs, 
	const typename ::CBTreeIterator<_ti_container> &nRhs
);

template<class _ti_container>
class CBTreeIteratorSubScriptWrapper
{
public:

	typedef _ti_container										container_t;

	typedef typename container_t::value_type					value_type;
	typedef typename container_t::size_type						size_type;
	typedef typename container_t::difference_type				difference_type;
	typedef typename container_t::reference						reference;
	typedef typename container_t::pointer						pointer;

						CBTreeIteratorSubScriptWrapper<_ti_container>
						(
							const CBTreeIterator<_ti_container>	&rInstance, 
							size_type								nPos
						);

						~CBTreeIteratorSubScriptWrapper<_ti_container> ();

	CBTreeIteratorSubScriptWrapper<_ti_container> &
						operator=					(const value_type &rData);

						operator const value_type &	();

protected:

	CBTreeIterator<_ti_container>	m_nOffset;
	size_type						m_nPos;
	value_type						m_sData;
};

template<class _ti_container>
typename ::CBTreeIterator<_ti_container> operator+
(
	const int nLhs, 
	const typename ::CBTreeIterator<_ti_container> &nRhs
);

template<class _ti_container>
typename ::CBTreeIterator<_ti_container> operator+
(
	const typename _ti_container::_t_sizetype nLhs, 
	const typename ::CBTreeIterator<_ti_container> &nRhs
);

template<class _t_iterator>
class CBTreeConstReverseIterator	:	public ::std::reverse_iterator<_t_iterator>
{
public:

	typedef typename _t_iterator::container_t					container_t;

	typedef typename container_t::value_type					value_type;
	typedef typename container_t::size_type						size_type;
	typedef typename container_t::difference_type				difference_type;
	typedef typename container_t::reference						reference;
	typedef typename container_t::pointer						pointer;
	
											CBTreeConstReverseIterator<_t_iterator>	();
								explicit	CBTreeConstReverseIterator<_t_iterator>	(const _t_iterator &rIter);
											CBTreeConstReverseIterator<_t_iterator>	(const CBTreeConstReverseIterator<_t_iterator> &rIter);
								explicit	CBTreeConstReverseIterator<_t_iterator> (const CBTreeReverseIterator<CBTreeIterator<container_t> > &rIter);

											~CBTreeConstReverseIterator<_t_iterator>	();

	void									swap (CBTreeConstReverseIterator &rRight);
												
	CBTreeConstReverseIterator&				operator= (const ::std::reverse_iterator<_t_iterator> &rIter);
	CBTreeConstReverseIterator&				operator= (const CBTreeReverseIterator<CBTreeIterator <container_t> > &rIter);

	bool									operator== (const CBTreeConstReverseIterator &rIter) const;
	bool									operator!= (const CBTreeConstReverseIterator &rIter) const;

	value_type&								operator* ();
	value_type*								operator-> ();

	value_type&								operator[] (const int nPos);
	value_type&								operator[] (const size_type nPos);

protected:

	value_type								m_sSubScriptResult;
};

template<class _t_iterator>
class CBTreeReverseIterator	:	public CBTreeConstReverseIterator<_t_iterator>
{
public:

	typedef typename _t_iterator::container_t					container_t;

	typedef typename container_t::value_type					value_type;
	typedef typename container_t::size_type						size_type;
	typedef typename container_t::difference_type				difference_type;
	typedef typename container_t::reference						reference;
	typedef typename container_t::pointer						pointer;

											CBTreeReverseIterator<_t_iterator>	();
								explicit	CBTreeReverseIterator<_t_iterator>	(const _t_iterator &rIter);
											CBTreeReverseIterator<_t_iterator>	(const CBTreeReverseIterator<_t_iterator> &rIter);

											~CBTreeReverseIterator<_t_iterator>	();

	const value_type &						operator*	() const;

	CBTreeIteratorSubScriptWrapper<container_t>
											operator*	();
											
	CBTreeReverseIterator&					operator=	(const ::std::reverse_iterator<_t_iterator> &rIter);
	CBTreeReverseIterator&					operator=	(const value_type &rData);

											operator const CBTreeConstReverseIterator<CBTreeConstIterator <container_t> > &	();

	CBTreeIteratorSubScriptWrapper<container_t>
											operator[]	(const int nPos);

	CBTreeIteratorSubScriptWrapper<container_t>
											operator[]	(const size_type nPos);

public:

	friend typename ::CBTreeIterator<container_t>;
	friend typename ::CBTreeIteratorSubScriptWrapper<container_t>;

};

#endif	// BTREEITER_H

#include "btreeiter.cpp"