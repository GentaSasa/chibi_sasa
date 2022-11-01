#include"star/star.hpp"

Astar::Astar():private_nh_("~")
{
    private_nh_.param("hz_", hz_, {10});
    sub_mapper_ = nh_.subscribe("/new_map", 10, &Astar::star_callback, this);
    pub_path_ = nh_.advertise<nav_msgs::Path>("/global_path", 1);
    pub_wp_path_ = nh_.advertise<nav_msgs::Path>("/wp_path", 1);
}

//マップを配列へ
void Astar::star_callback(const nav_msgs::OccupancyGrid::ConstPtr &msg)//callback関数
{
  raw_map_ = *msg;
	if(raw_map_.data.size() == 0)
	{
	  printf("ERROR map size is 0");
	}
  else
	{
	  row_ = raw_map_.info.height;
		col_ = raw_map_.info.width;
		resolution_ = raw_map_.info.resolution;
    map_array_ = std::vector<std::vector<int>>(row_, std::vector<int>(col_,0));//ここの仕組みがわかってない  
		for(int i=0;i<row_;i++)
		{
      for(int j=0;j<col_;j++)
      {
        map_array_[i][j] = raw_map_.data[i+j*col_];//1次元から2次元の配列へ格納
      }
    }

    origin_.x = raw_map_.info.origin.position.x;//原点の設定
    origin_.y = raw_map_.info.origin.position.y;
    
    std::cout <<origin_.x<< std::endl;
    std::cout << "complete map set" << std::endl;
	}
}

//スタート、ゴールノードと経由点の設定
void Astar::set_point()
{
  origin_x_ = origin_.x / resolution_;
  origin_y_ = origin_.y / resolution_;

  int x0,y0,x1,y1,x2,y2;
  x0 = 0;
  y0 = 0;
  x1 = 100;
  y1 = 100;
  x2 = -100;
  y2 = -100;
  
  waypoint_ = {
    {x0,y0},
    {x1,y0},
    {x1,y1},
    {x0,y1},
    {x2,y1},
    {x2,y0},
    {x0,y0},
  };
}


//コスト計算
void Astar::cost_calc()
{




}

//オープンリストの中から最もコストの低いノードを選択
void Astar::low_grid_select()
{

}

//選択したノードを親ノードとする
void Astar::parent_chose()
{

}
//親ノードの周りの４つのノードをオープンリストへ追加
void Astar::child_append()
{

}
//オープンリストの中のから最もコストの低いノードを次の親とする



//ゴールからスタートまでの最短コストを算出
void Astar::cost4s2g()
{
  for(int i=0;i<4;i++)
  {
    if( i==3)
    {

    }
  }
}




//スタートからゴールまでのパスを引く
void Astar::line_draw()
{

}

//マップ情報を配列からmapメッセージへ
void Astar::remap()
{
  std::cout<<"remapping"<<std::endl;

  for(int i=0;i<row_;i++)//配列情報からros msgに変換
  {
    for(int j=0;j<col_;j++)
    {
      raw_map_.data.push_back(map_array_[i][j]);
    }
  }
  pub_mapper_.publish(raw_map_);
}

//process関数
void Astar::process()
{
  std::cout<<"a-star start!!\n"<<std::endl;
  ros::Rate loop_rate(hz_);
  while(ros::ok())
  {
    set_point();//ウェイポイントの設定
    for(int i= 0;i<waypoint_.size();i++)//経由するウェイポイント分だけループする
    {
      while(is_reached_!=true)
      {
        if(parent_grid_.x==x_waypoint_ && parent_grid_.y==y_waypoint_)
        {
          is_reached_ = true;
        }
        else
        {
          set_child_node();
          cost_update():
        }

      }

    }
    pub_path_.publish(global_path_);
    ros::spinOnce();
    loop_rate.sleep();
  }
  std::cout <<"a-star is finished\n"<<std::endl;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv,"global_path_planner");
  Astar astar;
  astar.process();
  return 0;
}
