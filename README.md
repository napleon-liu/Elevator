# 写在前面
写这个课程作业的时候我还啥都不懂，不了解设计模式，不会用qt库，只知道C++基本的一些库。当时真的是一抹黑，网上也没有可以参考的设计，后来自己摸索着写出了一个类似于有限状态机的结构。回头看这些代码除了能跑没别的优点了，好在是能跑，应付过了课程要求。

# 编译问题

机房电脑缺少动态链接库，在自己电脑上编译好再去验收。

---实验一----
在main文件夹下打开控制台(不知道怎么打开请自行百度)
输入
g++ -std=c++11 -o a.out Elevator.cpp ElevatorService.cpp Building.cpp EvtCtrl.cpp Passenger.cpp
执行
a.out


---实验二、三、四、五---

g++ -o a.out Simulation.cpp Timer.cpp Passenger.cpp Elevator.cpp Building.cpp
a.out