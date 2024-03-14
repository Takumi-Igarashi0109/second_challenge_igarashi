#include "second_challenge_igarashi/second_challenge_igarashi.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  std::shared_ptr<SecondChallengeIgarashi> schallenge = std::make_shared<SecondChallengeIgarashi>();
  rclcpp::spin(schallenge);
  rclcpp::shutdown();

  return 0;
}
