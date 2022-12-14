#include "pch.h"

#include "HeightMapGenerator.h"
#include "AABBEstimation.h"

using namespace core;

CHeightMapGenerator::CHeightMapGenerator()
{ }

bool CHeightMapGenerator::setCloud(const PC_t::Ptr& vCloud)
{
	_ASSERTE(vCloud != nullptr);
	_ASSERTE(vCloud->size());
	m_pCloud = vCloud;
	return true;
}

bool CHeightMapGenerator::setAABB(const SAABB& vBox)
{
	_ASSERTE(vBox.isValid());
	m_Box = vBox;
	return true;
}

bool CHeightMapGenerator::generate(int vWidth, int vHeight)
{
	_ASSERTE(vWidth > 0 && vHeight > 0);
	m_Map.setSize(vWidth, vHeight);

	// By default, it is projected along the Z-axis

	if (!m_Box.isValid())
	{
		CAABBEstimation AABBEstimation(m_pCloud);
		m_Box = AABBEstimation.compute();
		_ASSERTE(m_Box.isValid());
	}

	for (auto& e : *m_pCloud) 
	{
		Eigen::Vector2i Offset = __computeOffset(e);
		if (e.z > m_Map.getValueAt(Offset[0], Offset[1]))
			m_Map.setValueAt(e.z, Offset[0], Offset[1]);
	}

	return true;
}

Eigen::Vector2i CHeightMapGenerator::__computeOffset(const Point_t& vPoint)
{
	int OffsetX = (vPoint.getVector3fMap()[0] - m_Box._Min[0]) / (m_Box._Max[0] - m_Box._Min[0]) * m_Map.getWidth();
	int OffsetY = (vPoint.getVector3fMap()[1] - m_Box._Min[1]) / (m_Box._Max[1] - m_Box._Min[1]) * m_Map.getHeight();

	if (m_Box._Max[0] == m_Box._Min[0]) OffsetX = 0;
	if (m_Box._Max[1] == m_Box._Min[1]) OffsetY = 0;

	if (OffsetX == m_Map.getWidth()) OffsetX--;
	if (OffsetY == m_Map.getHeight()) OffsetY--;

	return Eigen::Vector2i(OffsetX, OffsetY);
}




