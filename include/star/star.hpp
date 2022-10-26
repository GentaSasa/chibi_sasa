#ifndef STAR_H
#define STAR_H

#include<ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PointStamped.h>
#include <vector>

struct grid{
  double x;
  double y;
  double g;
  double f;
};

class Astar{
  public:
    Astar();
    void process();

  private:
    void star_callback(const nav_msgs::OccupancyGrid::ConstPtr & msg);
    void set_point();
    void cost4s2g();
    void remap();

    int hz_;
    int row_;
    int col_;
    double resolution_;
    double origin_x_;
    double origin_y_;
    
    grid origin_;
    grid starr_grid = {0,0,0,0};
    std::vector<grid> open_list_;
    std::vector<grid> close_list_;

    std::vector<std::vector<int>> map_array_;
    nav_msgs::OccupancyGrid raw_map_;
    nav_msgs::Path global_path_;
   
    std::vector<std::vector<int>> waypoint_;
    std::vector<std::vector<int>> costmap_;

    ros::NodeHandle nh_;
    ros::NodeHandle private_nh_;

    ros::Subscriber no_change_map_;
    ros::Publisher changed_map_;
    ros::Publisher pub_path_;
    ros::Publisher pub_wp_path_;
};
#endif
