#include <iostream>
#include <fstream>

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class MessageCommand : public LogCommand {
public:

    void print(const std::string& message) override {
        std::cout << message << '\n';
    }

};

class FileCommand : public LogCommand {
public:

    FileCommand () {
        in.open("in.txt");
        if (!(in.is_open())) {
            std::cout << "No log file found" << '\n';
        }
    }
    ~FileCommand() {
        in.close();
    }
    void print(const std::string& message) override {
        in << message << '\n';
    }

private:
    std::ofstream in;
};

int main()
{
    MessageCommand Text;
    Text.print("message");

    FileCommand Log;
    Log.print("message");
}

