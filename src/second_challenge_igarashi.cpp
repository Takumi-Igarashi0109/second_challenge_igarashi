#include "second_challenge_igarashi/second_challenge_igarashi.hpp"

SecondChallengeIgarashi::SecondChallengeIgarashi() : Node("second_challenge_igarashi")
{
    // デフォルト値は以下のようにする
    // goal_dist_ : 1.0
    // velocity_  : 0.1
    goal_dist_ = this->declare_parameter<double>("goal_dist",1.0);
    velocity_  = this->declare_parameter<double>("velocity",0.1);
    
   // timer
    timer_ = this->create_wall_timer (0.5s, 
    std::bind(&SecondChallengeIgarashi::timer_callback, this));
    //sensor_msgs::msg::LaserScan

    cmd_vel_pub_ = this->create_publisher<roomba_500driver_meiji::msg::RoombaCtrl>(
    "/roomba/control", rclcpp::QoS(1).reliable());

    scan_sub = this->create_subscription<sensor_msgs::msg::LaserScan>(
    "/scan", rclcpp::QoS(1).reliable(),
    std::bind(&SecondChallengeIgarashi::scan_callback, this, std::placeholders::_1));

}

void SecondChallengeIgarashi::timer_callback()
{
    // 一定周期で行う処理を書く
    set_cmd_vel();
}

void SecondChallengeIgarashi::scan_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
{
    scan_ = *msg;
}

void SecondChallengeIgarashi::run(float velocity, float omega)
{
    // roombaの制御モード
    // 基本的に11（DRIVE_DIRECT）固定で良い
    cmd_vel_.mode = 11;

    // 並進速度を指定
    cmd_vel_.cntl.linear.x  = velocity;
    // 旋回速度を指定
    cmd_vel_.cntl.angular.z = omega;

    // cmd_velをpublish
    // <publisher名>->publish(<変数名>);
    cmd_vel_pub_ -> publish(cmd_vel_);
}

// 並進速度と旋回速度を計算
void SecondChallengeIgarashi::set_cmd_vel()
{
    // 計算した制御入力はrun()に渡すこと
    if(is_goal())
    {
        run(velocity_, omega_);
    } else {
        run(0.0, 0.0);
    }
    
}

bool SecondChallengeIgarashi::is_goal()
{
    // calc_distance()を使用すること

    const int H = (int)((scan_.value().angle_max)-(scan_.value().angle_min))/(2*scan_.value().angle_increment);    
    const float a = scan_.value().ranges[H];
    //printf("%f",a);

    if( a > goal_dist_ ){
        return true; 
    } else {
        return false;
    }
}


