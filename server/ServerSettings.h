#pragma once

class ServerSettings{
    public:
    static const int serverPort = 13579;
    static const int datagramSize = 280;
    static const int maxConcurrentSessions = 1;
    static const int playersPerSession = 1;
    static const int kickTimeout = 5;
    static const int queueSize = 5;
    inline static const char* serverDir = nullptr;
};