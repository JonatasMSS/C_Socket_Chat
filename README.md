# 💬 C Socket Chat

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)](https://www.microsoft.com/windows)
[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))

A simple, lightweight real-time chat application built in C using Windows Sockets (Winsock2). This project demonstrates low-level socket programming with a client-server architecture for bidirectional communication.

## ✨ Features

- 🔌 **Client-Server Architecture**: Simple TCP/IP socket-based communication
- 💬 **Real-time Messaging**: Instant bidirectional message exchange
- 🧵 **Multi-threaded**: Separate threads for sending and receiving messages
- 🌐 **UTF-8 Support**: Full Unicode character support for international messages
- 🚪 **Graceful Exit**: Clean connection termination with `exit` command
- 📦 **Lightweight**: Minimal dependencies, pure C implementation

## 🔧 Prerequisites

Before you begin, ensure you have the following installed:

- **Operating System**: Windows (uses Winsock2 API)
- **Compiler**: GCC (MinGW) or any C compiler with Winsock2 support
- **Build Tool**: Make (optional, but recommended)

## 📥 Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/JonatasMSS/C_Socket_Chat.git
   cd C_Socket_Chat
   ```

2. **Compile the project**
   
   Using Make:
   ```bash
   make
   ```
   
   Or compile manually:
   ```bash
   gcc server.c -o server.exe -lws2_32
   gcc client.c -o client.exe -lws2_32
   ```

## 🚀 Usage

### Starting the Server

1. Open a terminal/command prompt
2. Run the server executable:
   ```bash
   ./server.exe
   ```
3. The server will start listening on port **8080**
4. Wait for a client connection

### Connecting a Client

1. Open another terminal/command prompt
2. Run the client executable with the server's IP and port:
   ```bash
   ./client.exe <server_ip> <port>
   ```
   
   For local testing:
   ```bash
   ./client.exe localhost 8080
   ```
   or
   ```bash
   ./client.exe 127.0.0.1 8080
   ```

### Chatting

Once connected:
- Type your message and press `Enter` to send
- Messages from the other party will appear automatically
- Type `exit` and press `Enter` to close the connection

**Example conversation:**
```
Server Terminal:
Aguardando conexão na porta 8080...
Cliente conectado!
Você: Hello from server!
Cliente: Hi! How are you?
Você: I'm great, thanks!

Client Terminal:
Conectado ao servidor!
Servidor: Hello from server!
Você: Hi! How are you?
Servidor: I'm great, thanks!
```

## 📁 Project Structure

```
C_Socket_Chat/
├── server.c        # Server implementation
├── client.c        # Client implementation
├── Makefile        # Build configuration
├── LICENSE         # Apache 2.0 License
└── README.md       # Project documentation
```

## 🔍 Technical Details

### Architecture

- **Protocol**: TCP/IP
- **Port**: 8080 (configurable in server.c)
- **Buffer Size**: 512 bytes
- **Socket Library**: Winsock2 (ws2_32.lib)

### Key Components

#### Server (`server.c`)
- Initializes Winsock
- Creates a listening socket on port 8080
- Accepts one client connection
- Spawns a thread to receive messages
- Main thread handles sending messages

#### Client (`client.c`)
- Connects to a specified server IP and port
- Spawns a thread to receive messages from server
- Main thread handles sending messages to server

### Threading Model

Both server and client use a multi-threaded approach:
- **Main Thread**: Handles user input and message sending
- **Receive Thread**: Continuously listens for incoming messages

## 🛠️ Building from Source

### Requirements
- GCC compiler with MinGW
- Windows SDK (for Winsock2)

### Build Commands

Build both executables:
```bash
make all
```

Build server only:
```bash
make server.exe
```

Build client only:
```bash
make client.exe
```

Clean build artifacts:
```bash
make clean
```

## ⚙️ Configuration

### Changing the Port

To use a different port, modify the port number in `server.c`:

```c
// Line 62 in server.c
iResult = getaddrinfo(NULL, "8080", &hints, &result);  // Change "8080" to your desired port
```

### Buffer Size

To adjust the message buffer size, modify the constant in both files:

```c
#define DEFAULT_BUFLEN 512  // Change to desired size
```

## 🐛 Troubleshooting

### Common Issues

**Problem**: `WSAStartup failed`
- **Solution**: Ensure you're running on Windows with Winsock2 support

**Problem**: `bind failed`
- **Solution**: Port 8080 might be in use. Close other applications or change the port

**Problem**: `connect failed`
- **Solution**: 
  - Verify the server is running
  - Check the IP address and port are correct
  - Ensure firewall isn't blocking the connection

**Problem**: Compilation errors with `ws2_32`
- **Solution**: Make sure to link the Winsock library: `-lws2_32`

## 📄 License

This project is licensed under the Apache License 2.0 - see the [LICENSE](LICENSE) file for details.

## 👤 Author

**Jonatas MSS**
- GitHub: [@JonatasMSS](https://github.com/JonatasMSS)

## 🤝 Contributing

Contributions, issues, and feature requests are welcome! Feel free to check the [issues page](https://github.com/JonatasMSS/C_Socket_Chat/issues).

### How to Contribute

1. Fork the project
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 🌟 Future Enhancements

Potential improvements for this project:
- [ ] Support for multiple concurrent clients
- [ ] Message history/logging
- [ ] Encryption for secure communication
- [ ] Cross-platform support (Linux/macOS)
- [ ] GUI interface
- [ ] File transfer capability
- [ ] User authentication

## 📚 Learning Resources

If you're interested in learning more about socket programming:
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
- [Microsoft Winsock Documentation](https://docs.microsoft.com/en-us/windows/win32/winsock/windows-sockets-start-page-2)
- [TCP/IP Fundamentals](https://www.ietf.org/rfc/rfc793.txt)

---

<div align="center">
  
**If you found this project helpful, please consider giving it a ⭐!**

Made with ❤️ using C and Winsock2

</div>
