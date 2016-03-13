#include <iostream>
#include <string>
#include <map>

class StackItem {
public:
    StackItem(std::string, StackItem*);
    std::string data;
    StackItem* next;
};

StackItem::StackItem(std::string data, StackItem *nextItem = nullptr) {
    this->data = data;
    next = nextItem;
}

class Handler {
public:
    static StackItem *head;
    virtual ~Handler() {};
    virtual void handler(std::string) {};
};

StackItem* Handler::head = nullptr;

class Push: public Handler {
public:
    void handler(std::string str) {
        StackItem *newHead = new StackItem(str, head);
        head = newHead;
    }
};

class Pop: public Handler {
public:
    void handler(std::string) {
        if (head == nullptr) {
            return;
        }

        StackItem *item = head;
        std::cout << item->data << std::endl;
        
        head = item->next;
        delete item;
    }
};

class List: public Handler {
public:
    void handler(std::string) {
        if (head == nullptr) {
            return;
        }

        StackItem *item = head;
        do {
            std::cout << item->data << std::endl;
            item = item->next;
        } while (item != nullptr);
    }
};

struct Command {
    Command( Handler* c, bool d) : command(c), isNeedData(d) {};
    Handler *command;
    bool isNeedData;
};

int main(int argc, const char * argv[]) {
    std::string command = "";
    std::string data = "";
    std::map<std::string, Command*> handlers;
    
    Command *c = nullptr;
    
    handlers["push"] = new Command(new Push(), true);
    handlers["list"] = new Command(new List(), false);
    handlers["pop"] = new Command(new Pop(), false);
    
    while (true) {
        std::cin >> command;

        if (command == "quit") {
            break;
        }

        if ( handlers.find(command) != handlers.end() ) {
            c = handlers[command];

            if (c->isNeedData) {
                std::cin >> data;
                c->command->handler(data);
            } else {
                c->command->handler("");
            }

        } else {
            std::cout << "Command not found" << std::endl;
        }
    }

    return 0;
}
