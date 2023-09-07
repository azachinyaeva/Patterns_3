#include <iostream>
#include <vector>
#include <fstream>

class Observer {
public:
    virtual ~Observer() {}
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};

class Observed {
public:

    void AddObserver(Observer* observer) {
        observers_.push_back(observer);
    }
    void RemoveObserver(Observer* observer) {
        auto it = std::remove(observers_.begin(), observers_.end(), observer);
        observers_.erase(it, observers_.end());
    }
    void onWarning() {
        for (auto observer : observers_) {
            observer->onWarning("Warning!");
        }
    }
    void onError() {
        for (auto observer : observers_) {
            observer->onError("Error!");
        }
    }
    void onFatalError() {
        for (auto observer : observers_) {
            observer->onFatalError("Fatal Error!");
        }
    }

private:
    std::vector<Observer*> observers_;
};



class WarningObserver : public Observer {

    void onWarning(const std::string& message) override {
        std::cout << message << std::endl;
    }
    void onError(const std::string& message) override {}
    void onFatalError(const std::string& message) override {}
};

class ErrorObserver : public Observer {
public:
    ErrorObserver() {
        out.open("out.txt");
        if (!(out.is_open())) {
            std::cout << "No log file found" << '\n';
        }
    }
    ~ErrorObserver() {
        out.close();
    }
    void onError(const std::string& message) override {
        out << "Error message: " << message << '\n';
    }
    void onWarning(const std::string& message) override {}
    void onFatalError(const std::string& message) override {}

private:
    std::ofstream out;
};

class FatalErrObserver : public Observer {
public:
    FatalErrObserver() {
        out.open("out.txt");
        if (!(out.is_open())) {
            std::cout << "No log file found" << '\n';
        }
    }
    ~FatalErrObserver() {
        out.close();
    }
    void onFatalError(const std::string& message) override{
        out << std::endl << "Fatal error message: " << message << '\n';
        std::cout << message << '\n';
        
    }
    void onWarning(const std::string& message) override {}
    void onError(const std::string& message) override {}
private:
    std::ofstream out;
};


int main()
{
    Observed Object;
    WarningObserver warning;
    ErrorObserver error;
    FatalErrObserver fatal;
    Object.AddObserver(&warning);
    Object.AddObserver(&error);
    Object.AddObserver(&fatal);
    Object.onWarning();
    Object.onError();
    Object.onFatalError();

}

