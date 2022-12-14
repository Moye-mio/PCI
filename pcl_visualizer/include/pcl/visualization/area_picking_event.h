/*
 * Software License Agreement (BSD License)
 *
 *  Point Cloud Library (PCL) - www.pointclouds.org
 *  Copyright (c) 2010-2011, Willow Garage, Inc.
 *  Copyright (c) 2012-, Open Perception, Inc.
 *
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the copyright holder(s) nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 */

#pragma once

#include <pcl/pcl_macros.h>

#include <vector>

namespace pcl
{
  namespace visualization
  {
    /** /brief Class representing 3D area picking events. */
    class PCL_EXPORTS AreaPickingEvent
    {
      public:
        AreaPickingEvent (int nb_points, const std::vector<int>& indices, float last_x, float last_y, float x, float y)
          : nb_points_ (nb_points)
          , indices_ (indices)
          , last_x_ (last_x)
          , last_y_ (last_y)
          , x_(x)
          , y_(y)
        {}

        /** \brief For situations where a whole are is selected, return the points indices.
          * \param[out] indices indices of the points under the area selected by user.
          * \return true, if the area selected by the user contains points, false otherwise
          */
        inline bool
        getPointsIndices (std::vector<int>& indices) const
        {
          if (nb_points_ <= 0)
            return (false);
          indices = indices_;
          return (true);
        }

        inline void
        getArea(float& min_x, float& min_y, float& max_x, float& max_y) const
        {
            min_x = std::min(last_x_, x_);
            min_y = std::min(last_y_, y_);
            max_x = std::max(last_x_, x_);
            max_y = std::max(last_y_, y_);
        }

      private:
        int nb_points_;
        std::vector<int> indices_;

        float last_x_, last_y_;
        float x_, y_;
    };
  } //namespace visualization
} //namespace pcl
