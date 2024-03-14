#ifndef SECOND_CHALLENGE_IGARASHI_HPP
#define SECOND_CHALLENGE_IGARASHI_HPP

#include <chrono>
#include <rclcpp/rclcpp.hpp>// rclcpp/rclcpp.hpp
#include <functional>// functional
#include <memory>// memory
#include <optional>// optional
#include <sensor_msgs/msg/laser_scan.hpp>//roomba_500driver_meiji/meg/roomba_ctrl.hpp
#include "roomba_500driver_meiji/msg/roomba_ctrl.hpp"

using namespace std::chrono_literals;

class SecondChallengeIgarashi : public rclcpp::Node
{
  public:
    rclcpp::TimerBase::SharedPtr timer_;
    SecondChallengeIgarashi();
    void process();
    void scan_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg);
    void timer_callback();
    // 関数
    
    //bool can_move();                        // センサ情報（今回はodom）を取得できているかの確認用
    bool is_goal();                         // 終了判定
    //double calc_distance();                 // 進んだ距離を計算
    void run(float velocity, float omega);  // roombaの制御入力を決定
    void set_cmd_vel();                     // 並進速度と旋回速度を計算

    // 変数
    double goal_dist_ = 0.0;
    double velocity_ = 0.0;
    double omega_ = 0.0;
    std::optional<sensor_msgs::msg::LaserScan> scan_;  // optional型で定義することによりodomをsubできたかの判定も同時に行う
    roomba_500driver_meiji::msg::RoombaCtrl cmd_vel_;

    // Pub & Sub
    // subscriberはnav_msgs::msg::Odometry型のトピックをsubscribe
    // rclcpp::Subscription<msg型>::SharedPtr subscriber名;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr scan_sub;                  // odom
    // publisherはroomba_500driver_meiji::msg::RoombaCtrl型のトピックをpublish
    // rclcpp::Publisher<roomba_500driver_meiji::msg::RoombaCtrl>::SharedPtr publisher名;
    rclcpp::Publisher<roomba_500driver_meiji::msg::RoombaCtrl>::SharedPtr cmd_vel_pub_; 
};

#endif  // SECOND_CHALLENGE_IGARASHI_HPP
