# go1_ros_joy

 付属のjoystickを押すと、 それに応じたrosのtopicを流すもの。
 
 unitree_legged_sdkでのlowlevel制御を用いている。（はず）
 なのに、動作中にリモコンから動かすことができるし、basic modeにもなっていないように見える。
 つまり実用上は問題ないが、不気味。
 
 ちなみに、highlevelは、なぜかうまくいかない。（要検証）

## 環境設定

　go1_ros_joyをcatkin_ws/srcに置いてください。

## 実行方法
 ```
 $ catkin_make
 $ source ~/catkin_ws/source/setup.bash
 $ rosrun go1_ros_joy topic_publisher
 ```
 別のターミナルを起動して次のようにすれば、確認できる：
 ```
 $ source ~/catkin_ws/source/setup.bash
 $ rosrun go1_ros_joy topic_subscriber
 ```
もしくは次のようにしてもよい：
 ```
 $ source ~/catkin_ws/source/setup.bash
 $ rostopic echo /ros_joy_msg
 ```

