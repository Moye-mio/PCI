#include "pch.h"
#include "NormalEstimator.h"

#include <pcl/features/normal_3d.h>
#include <pcl/kdtree/kdtree_flann.h>

using namespace core;

CNormalEstimator::CNormalEstimator()
	: m_Normals(new NormalPC_t)
{}

bool CNormalEstimator::setCloud(const PC_t::Ptr& vCloud)
{
	_ASSERTE(vCloud != NULL);
	_ASSERTE(vCloud->size());

	m_Cloud = vCloud;

	return true;
}

void CNormalEstimator::compute(float vRadius)
{
	_ASSERTE(m_Cloud != NULL);
	_ASSERTE(m_Cloud->size());
	_ASSERTE(vRadius);

	pcl::NormalEstimation<Point_t, Normal_t> PCLEstimator;
	PCLEstimator.setInputCloud(m_Cloud);
	pcl::search::KdTree<Point_t>::Ptr KdTree(new pcl::search::KdTree<Point_t>());
	PCLEstimator.setSearchMethod(KdTree);
	PCLEstimator.setRadiusSearch(vRadius);
	PCLEstimator.compute(*m_Normals);

	for (auto& e : *m_Normals)
	{
		if (std::isnan(e.normal_x)) e.normal_x = 0.0f;
		if (std::isnan(e.normal_y)) e.normal_y = 0.0f;
		if (std::isnan(e.normal_z)) e.normal_z = 0.0f;
		if (e.normal_x == 0 && e.normal_y == 0 && e.normal_z == 0) e.normal_x = 1.0f;
	}
}
