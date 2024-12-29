#!/usr/bin/env python3

import rospy
from std_msgs.msg import String
import socket

def sensor_data_receiver():
    rospy.init_node('sensor_data_receiver', anonymous=True)
    pub = rospy.Publisher('sensor_data', String, queue_size=10)
    rate = rospy.Rate(10)  # 10 Hz

    # 设置 TCP/IP 连接
    host = '127.0.0.1'  # 传感器软件运行的主机地址
    port = 12345        # 传感器软件使用的端口号

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((host, port))
    s.listen(1)
    rospy.loginfo("Waiting for connection...")
    conn, addr = s.accept()
    rospy.loginfo(f"Connected by {addr}")

    while not rospy.is_shutdown():
        data = conn.recv(1024)  # 接收数据
        if data:
            rospy.loginfo(f"Received data: {data.decode('utf-8')}")
            pub.publish(data.decode('utf-8'))
        rate.sleep()

    conn.close()
    s.close()

if __name__ == '__main__':
    try:
        sensor_data_receiver()
    except rospy.ROSInterruptException:
        pass