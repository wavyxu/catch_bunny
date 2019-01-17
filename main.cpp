#include <iostream>
#include "vector"
#include "iterator"
using namespace std;
#ifndef SCENE_SIZE
#define SCENE_SIZE 5
#endif
#ifndef DEFAULT_BUNNY_NUM
#define DEFAULT_BUNNY_NUM 8
#endif
#ifndef DEFAULT_PLAY_TIMES
#define DEFAULT_PLAY_TIMES 5
#endif


// 兔子在场景重的坐标
class Position {
public:
    Position() {
        x_ = 0;
        y_ = 0;
    }
    Position(int x, int y) {
        x_ = x;
        y_ = y;
    }
    int getX() {
        return x_;
    }
    int getY() {
        return y_;
    }
private:
    int x_;
    int y_;
};

// 兔子类，属性：坐标
class Bunny {
public:
    Bunny(Position position) {
        position_ = position;
    }
    Position getPosition() {
        return position_;
    }
private:
    Position position_;
};

// 场景类：场景里随机生存一定数量兔子
// vector<Bunny> 用于存放场景里的兔子
// removeBunny(target), 将场景里的任意一个兔子转移到 user 下
class Scene {
public:
    Scene() {
        cout << "bunny number is " << DEFAULT_BUNNY_NUM << endl;
        for (int i = 0; i < DEFAULT_BUNNY_NUM; i++) {
            addBunny();
        }
    }
    
    void addBunny() {
        bunnies_.emplace_back(Bunny(Position(rand() % SCENE_SIZE,rand() % SCENE_SIZE)));
        cout << "a bunny appeared at: " << bunnies_.back().getPosition().getX() << "," << bunnies_.back().getPosition().getY() << endl;
    }
    void removeBunny(Bunny& bunny, vector<Bunny>& target) {
        target.push_back(move(bunny));
    }
    bool hasNext() {
        return iterator != bunnies_.end();
    }
    vector<Bunny>::iterator getIterator() {
        iterator = bunnies_.begin();
        return iterator;
    }
    Bunny& getNext() {
        return *iterator++;
    }
private:
    vector<Bunny> bunnies_;
    vector<Bunny>::iterator iterator;
};

// 玩家类，拥有 vector<Bunny> 用于装已经被抓到的兔子
class User {
public:
    User() {
    }
    int getBunnyCount() {
        return bunnies_.size();
    }
    vector<Bunny> getBunnies() {
        return bunnies_;
    }
    bool catchBunny(Position position) {
        cout << "Please the coordinate x and y you'd like to catch a bunny, and seperate x and y using space"<<endl;
        int x = 0;
        int y = 0;
        cin >> x >> y;
        position = Position(x, y);
        vector<Bunny>::iterator iter = scene_.getIterator();
        while (scene_.hasNext()) {
            Bunny& bunny = scene_.getNext();
            if (position.getX() == bunny.getPosition().getX() && position.getY() == bunny.getPosition().getY()) {
                scene_.removeBunny(bunny, bunnies_);
                cout << "Congratulation. Caught a bunny.";
                return true;
            }
        }
        cout << "Sorry, there is no bunny. Try again. Have Fun." << endl;
        return false;
    }
    void enterScene(Scene scene) {
        scene_ = scene;
    }
private:
    vector<Bunny> bunnies_;
    Scene scene_;
};

// 游戏，一个场景，一个玩家
// play() 让玩家抓五次兔子
class Game {
public:
    Game() {
        initialScene();
        initialUser();
        user_.enterScene(scene_);
    }
    void initialScene() {
        scene_ = Scene();
    }
    void initialUser() {
        user_ = User();
    }
    void play() {
        for (int i = 0; i < DEFAULT_PLAY_TIMES; i++) {
            user_.catchBunny(Position(rand() % SCENE_SIZE, rand() % SCENE_SIZE));
        }
    }

private:
    Scene scene_;
    User user_;
};


int main() {
    Game game = Game();
    game.play();
    std::cout << "Catching Bunny. Have Fun!" << std::endl;
    return 0;
}