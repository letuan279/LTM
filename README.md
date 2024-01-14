**Lập trình mạng - BTL**
------------------------
# HƯỚNG DẪN CÀI ĐẶT
1. Clone dự án: `git clone https://github.com/letuan279/LTM.git`
2. Cài đặt thư viện json: `sudo apt install nlohmann-json3-dev`
3. Khởi động server
   - Bật terminal ở thư mục `/server`
   - Chạy câu lệnh `g++ server.cpp -o server.out && ./server.out`
4. Khởi động client
   - Ở thư mục `/build-*`, chạy file **TaskManager**
5. Sử dụng chat (chỉ khả dụng trên terminal)
   - Server:
     + Bật terminal ở thư mục `/server`
     + Chạy câu lệnh: `g++ chat_server.cpp -o chat_server.out && ./chat_server.out`
   - Mỗi terminal con ở thư mục `/server`, chạy lệnh `g++ chat_client.cpp -o chat_client.out && ./chat_client.out` để vào client chat.
