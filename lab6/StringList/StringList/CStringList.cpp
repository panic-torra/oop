#include "stdafx.h"
#include "CStringList.h"

CStringList::CNode::CNode(const std::string & data, CNode * prev, std::unique_ptr<CNode> && next)
	:data(data)
	, prev(prev)
	, next(std::move(next))
{
}