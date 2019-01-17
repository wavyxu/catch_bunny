#include <iostream>
#include "vector"
#include "iterator"
using namespace std;
#ifndef SCENE_SIZE
#define SCENE_SIZE 10
#endif
#ifndef DEFAULT_SCENE_SIZE
#define DEFAULT_SCENE_SIZE 20
#endif
#ifndef DEFAULT_BUNNY_NUM
#define DEFAULT_BUNNY_NUM 20
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
        scene_size_ = DEFAULT_SCENE_SIZE;
        for (int i = 0; i < DEFAULT_BUNNY_NUM; i++) {
            addBunny();
        }
    }
    Scene(int scene_size) {
        for (int i = 0; i < scene_size; i++) {
            addBunny();
        }
    }
    void addBunny() {
        bunnies_.emplace_back(Bunny(Position(rand() % scene_size_,rand() % scene_size_)));
    }
    void removeBunny(vector<Bunny>::iterator target) {
        move(std::begin(bunnies_), std::end(bunnies_), std::back_inserter(target));
    }
    bool hasNext() {
        return iter != bunnies_.end();
    }
    vector<Bunny>::iterator getIterator() {
        iter = bunnies_.begin();
        return iter;
    }
    Bunny& getNext() {
        return *iter++;
    }
private:
    int scene_size_;
    vector<Bunny> bunnies_;
    int currIndex;
    vector<Bunny>::iterator iter;
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
        vector<Bunny>::iterator iter = scene_.getIterator();
        while (scene_.hasNext()) {
            Bunny& bunny = scene_.getNext();
            if (position.getX() == bunny.getPosition().getX() && position.getY() == bunny.getPosition().getY()) {
                scene_.removeBunny(bunnies_.begin());
                cout << "Congratulation. Caught a bunny.";
            }
        }
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
        scene_ = Scene(SCENE_SIZE);
    }
    void initialUser() {
        user_ = User();
    }
    void play(Scene scene, User user) {
        for (int i = 0; i < 5; i++) {
            user.catchBunny(Position(rand() % SCENE_SIZE, rand() % SCENE_SIZE));
        }
    }
private:
    Scene scene_;
    User user_;
};


int main() {
    Game game = Game();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}