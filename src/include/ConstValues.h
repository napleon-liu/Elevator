//
// Created by 79893 on 2022-10-30.
//

#ifndef ELEVATOR_CONSTVALUES_H
#define ELEVATOR_CONSTVALUES_H

// 建筑的总楼层
const int floorNums =  40;
// 电梯的数目
const int evtNums =  10;
// 乘客数目
const int maxPsgNums = 100;
// 乘客的最大仿真次数
const int maxSimulationTimes = 10;
// 乘客在某层的最大停留时间
const int maxStayingTime = 10;
// 表示电梯运行方向的枚举类型
typedef enum {
    DirectionUp = 0, // 0 表示向上
    DirectionDown = 1, // 1表示向下
    DirectionStay = 2, // 2表示停留
}Direction;

// 表示乘客状态的枚举类型
typedef enum {
    BeforeSimulation = 0,   //  表示该乘客还未进入大楼，仿真还未开始
    StayForRandomTime = 1,  // 表示乘客在某层随机停留
    WaitForElevatorArrive = 2,  // 表示乘客在等待电梯到达
//    WaitToGetInElevator = 3,    // 表示乘客在等待上电梯
//    GetInElevator = 4,  //表示正在上电梯
//    WaitElevatorToRun = 5,  //表示等待电梯启动
    RunWithElevator = 6, // 表示跟随电梯运行
//    StopWithElevator = 7, // 跟随电梯停留
//    WaitToGetOutElevator = 8,   // 等待下电梯
//    GetOutElevator = 9, //  正在下电梯
    AfterSimulation = 10,   //  仿真结束
}PassengerState;

// 电梯状态
typedef enum {
    Stop = 0, // 停止
    GoUp = 1,   // 向上
    GoDown = 2, // 向下
    Stay = 3,   // 停留
}ElevatorState;


#endif //ELEVATOR_CONSTVALUES_H
