import socket
import time

def tcp_client():
    host = '127.0.0.1'  # 服务器地址（ROS 节点运行的主机地址）
    port = 12345        # 服务器端口（ROS 节点使用的端口号）

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))

    try:
        while True:
            message = "Hello ROS"
            s.sendall(message.encode('utf-8'))
            print(f"Sent: {message}")
            time.sleep(1)  # 每秒发送一次
    except KeyboardInterrupt:
        print("Client stopped.")
    finally:
        s.close()

if __name__ == '__main__':
    tcp_client()