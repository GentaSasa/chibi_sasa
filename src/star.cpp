#include<ros/ros.h>
#include<nav_msgs/OccupancyGrid.h>
#include<nav_msgs/Path.h>
#include<geometry_msgs/PoseStamped.h>
#include<geometry_msgs/PointStamped.h>
#include<vector>

//マップを配列へ
//スタート、ゴールノードと経由点の設定
//スタートからゴールまでのコスト計算
//ゴールからスタートまでの最短コストを算出
//スタートからゴールまでのパスを引く

int row=0; 
int col=0;
double resolution;
std::vector<std::vector<int>> map_array;
nav_msgs::OccupancyGrid raw_map;
std::vector<std::vector<int>> waypoint;



//各マス目の座標とコスト
struct grid{
  double x;
  double y;
  double g;
  double f;
};

grid origin;
grid start_grid={0,0,0,0};

int origin_x;
int origin_y;

//マップを配列へ
void map_receive(const nav_msgs::OccupancyGrid::ConstPtr &msg)
{
  raw_map = *msg;
	if(raw_map.data.size() == 0)
	{
	  printf("ERROR map size is 0");
	}
  else
	{
	  row = raw_map.info.height;
		col = raw_map.info.width;
		resolution = raw_map.info.resolution;
    map_array = std::vector<std::vector<int>>(row, std::vector<int>(col,0));//ここの仕組みがわかってない  
		for(int i=0;i<row;i++)
		{
      for(int j=0;j<col;j++)
      {
        map_array[i][j] = raw_map.data[i+j*col];//1次元から2次元の配列へ格納
      }
    }

    origin.x = raw_map.info.origin.position.x;//原点の設定
    origin.y = raw_map.info.origin.position.y;

    std::cout << "complete map set" << std::endl;
	}
}


//スタート、ゴールノードと経由点の設定
void set_point()
{
  origin_x = origin.x / resolution;
  origin_y = origin.y / resolution;

  int x0,y0,x1,y1,x2,y2;
  x0 = 0;
  y0 = 0;
  x1 = 100;
  y1 = 100;
  x2 = -100;
  y2 = -100;
  
  waypoint = {
    {x0,y0},
    {x1,y0},
    {x1,y1},
    {x0,y1},
    {x2,y1},
    {x2,y0},
    {x0,y0},
  };
}

//スタートからゴールまでのコスト計算



//ゴールからスタートまでの最短コストを算出


//スタートからゴールまでのパスを引く


int main(int argc, char **argv)
{
  int N = 4000;
	int M = 4000;

  ros::init(argc, argv,"global_path_planner");





  return 0;
}

