#pragma once

namespace core
{
	using SPoint = Eigen::Vector3f;

	class CBSplineCurve
	{
	public:
		CBSplineCurve(int vDegree, bool vIsClamped = true);
		~CBSplineCurve() {}

		bool setControlPoints(const std::vector<SPoint>& vPoints);
		SPoint sample(float vU);

	private:
		std::vector<SPoint> m_ControlPoints;

		int m_Degree;
		int m_IsClamped;

	};

}