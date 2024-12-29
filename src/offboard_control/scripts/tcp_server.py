import socket
import time

def tcp_server():
    host = '127.0.0.1'  # 服务器地址
    port = 12345        # 服务器端口

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((host, port))
    s.listen(1)
    print("Server listening on {}:{}".format(host, port))

    conn, addr = s.accept()
    print("Connected by", addr)

    try:
        while True:
            message = "Hello from server"
            conn.sendall(message.encode('utf-8'))
            print(f"Sent: {message}")
            time.sleep(1)  # 每秒发送一次
    except KeyboardInterrupt:
        print("Server stopped.")
    finally:
        conn.close()
        s.close()

if __name__ == '__main__':
    tcp_server()