/************************************************************
**
** file:	btreeioblock.h
** author:	Andreas Steffens
** license:	LGPL v3
**
** description:
**
** This file contains code for the b-tree framework's
** block IO data layer class.
**
************************************************************/

#ifndef	BTREEIOBLOCK_H
#define	BTREEIOBLOCK_H

#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

#include <stdint.h>
#include <memory.h>
#include <stddef.h>

#if defined (_MSC_VER)

 #include <io.h>

#elif defined(__GNUC__) || defined(__GNUG__)

 #include <string.h>
 #include <stdlib.h>
 #include <sys/time.h>
 #include <sys/vfs.h>

#endif

#include "io/data_layer/base/btreeio.h"

template<class _t_datalayerproperties>
class CBTreeBlockIO : public CBTreeIO<_t_datalayerproperties>
{
	typedef struct btree_block_io_descriptor_s
	{
		uint8_t		*pBlockData;
		uint32_t	nAccessCtr;
		bool		bMarkedForUnmap;
	} btree_block_io_descriptor_t;

public:

	typedef typename _t_datalayerproperties::size_type				size_type;
	typedef typename _t_datalayerproperties::node_iter_type			node_iter_type;
	typedef typename _t_datalayerproperties::sub_node_iter_type		sub_node_iter_type;
	typedef typename _t_datalayerproperties::address_type			address_type;
	typedef typename _t_datalayerproperties::offset_type			offset_type;

	// construction
							CBTreeBlockIO<_t_datalayerproperties>
														(
															const sub_node_iter_type nNodeSize, 
															const uint32_t nNumDataPools, 
															const CBTreeIOperBlockPoolDesc_t *psDataPools
														);

							~CBTreeBlockIO<_t_datalayerproperties>
														();

	// resource management
	virtual void			set_root_node				(const node_iter_type nRootNode);

protected:

	// address generation
	inline address_type		get_blockAddr				(const node_iter_type nNode) const;
	virtual offset_type		get_poolOffset				() const;
	inline address_type		get_node_offset				(const node_iter_type nNode) const;
	inline address_type		get_nodeAddr				(const node_iter_type nNode) const;
	
	inline offset_type		get_per_node_pool_offset	(const uint32_t nPool) const;
	inline address_type		get_pool_address			(const uint32_t nPool, const node_iter_type nNode) const;

	offset_type				generate_pool_offsets		();

	void					realloc_descriptor_vector	(const node_iter_type nMaxNodes);

	uint32_t				convert_node_to_descriptor	(const node_iter_type nNode, const bool bRoundUp = false) const;

	// initialisation
	void					setup						(const address_type nBlockSize);

	void					increment_access_counter	(const uint32_t nDescriptor) const;

	address_type										m_nBlockSize;				// optimal block size
	uint32_t											m_nNodesPerBlock;			// number of nodes that fit into one block
	uint32_t											m_nNodesPerBlockVectorSize;	// number of nodes that fit into one block (vector size)

	offset_type											m_nAlignedNodeSize;			// size of one node in a block plus alignment
	
	offset_type											*m_pnPerNodePoolOffset;

	btree_block_io_descriptor_t							*m_psDescriptorVector;
	uint32_t											m_nDescriptorVectorSize;

	node_iter_type										m_nPrevRootNode;

	uint32_t											m_nMaxAccessCtr;			// number of accesses before degrading statistics
};

#endif // BTREEIOBLOCK_H

#include "btreeioblock.cpp"
