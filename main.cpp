//
// Created by 许卫 on 2019-01-17.
//

#include <iostream>
#include <cassert>
#include "vector"
#include "iterator"
#include "unordered_set"
#include "unordered_map"
using namespace std;
#ifndef SCENE_SIZE
#define SCENE_SIZE 100
#endif
#ifndef DEFAULT_BUNNY_NUM
#define DEFAULT_BUNNY_NUM 8
#endif
#ifndef DEFAULT_PLAY_TIMES
#define DEFAULT_PLAY_TIMES 5
#endif

// 兔子类，属性：坐标
class Bunny {
public:
    Bunny(){}
    pair<int, int> position;
    int index;
};

using IntPair = std::pair<int, int>;

struct IntPairHash {
    static_assert(sizeof(int) * 2 == sizeof(size_t));

    size_t operator()(IntPair p) const noexcept {
        return size_t(p.first) << 32 | p.second;
    }
};



// 场景类：场景里随机生存一定数量兔子
// vector<Bunny> 用于存放场景里的兔子
// removeBunny(target), 将场景里的任意一个兔子转移到 user 下
// Iterable
// Iterator
class Scene {
public:
    Scene() { }

    void initialScene() {
        cout << "bunny number is " << DEFAULT_BUNNY_NUM << endl;
        for (int i = 0; i < DEFAULT_BUNNY_NUM; i++) {
            addBunnyInScene();
        }
    }
    void addBunnyInScene() {

        pair<int, int> position= make_pair(rand() % SCENE_SIZE, rand() % SCENE_SIZE);
        if(hasBunny(position)) return;
        Bunny bunny;
        bunny.index = bunniesInScene_.size();
        //bunniesInScene_.emplace(position, bunny);
        bunniesInScene_[position] = bunny;
        cout << "a bunny appeared at: " << position.first << "," << position.second << " with index " << bunny.index << endl;
    }
    int getNumOfBunnies() {
        return bunniesInScene_.size();
    }
    bool hasBunny(pair<int, int> position) {
        return bunniesInScene_.find(position) != bunniesInScene_.end();
    }
    Bunny getBunnyByPosition(pair<int, int> position) {
        Bunny b = std::move(bunniesInScene_[position]);
        bunniesInScene_.erase(position);
        return std::move(b);
    }

    //unordered_map <Coordinate, Bunny> bunnies_;
    std::unordered_map<IntPair, Bunny, IntPairHash> bunniesInScene_; //std::pair<int, int>

};

// 玩家类，拥有 vector<Bunny> 用于装已经被抓到的兔子
class User {
public:
    User() {
        scene_ = nullptr;
    }
    int getBunnyCount() {
        return bunniesCaught_.size();
    }
    vector<Bunny>& getBunnies() {
        return bunniesCaught_;
    }

    bool catchBunny(pair<int, int> position) {
        assert(scene_);
        if (scene_->hasBunny(position)) {
            cout << "You got it" << endl;
            Bunny bunny = scene_ -> getBunnyByPosition(position);
            cout << "The bunny you got is" << &bunny <<endl ;
            // bunniesCaught_.insert(bunny);
            cout << "Bunny index: " << bunny.index << endl;
            bunniesCaught_.push_back(std::move(bunny));
            cout << "The number of bunnies caught " << bunniesCaught_.size() << endl;
            cout << "The number of bunnies in scene " <<  scene_->getNumOfBunnies() << endl;
            return true;
        }
        cout << "Sorry, there is no bunny. Try again. Have Fun." << endl;
        return false;
    }


    void enterScene(Scene& scene) {
        scene_ = &scene;
    }
    int getNumOfBunnies() {
        return bunniesCaught_.size();
    }
private:
    vector<Bunny> bunniesCaught_;
    Scene* scene_;
};

// 游戏，一个场景，一个玩家
// play() 让玩家抓五次兔子
class Game {
public:
    Game() {
    }
    void play() {
        scene_.initialScene();
        user_.enterScene(scene_);
        for (int i = 0; i < DEFAULT_PLAY_TIMES; i++) {
            cout << "Please the coordinate x and y you'd like to catch a bunny, and seperate x and y using space"<<endl;
            int x = 0;
            //cin >> x;
            int y = 0;
            cin >> x >> y;
            //cout << "you are going to catch at " << x << "," << y << endl;
            cout << "you are going to catch at " << x << endl;
            //user_.catchBunny(x, y);
            user_.catchBunny(pair<int, int>(x, y));
        }
    }

private:
    Scene scene_;
    User user_;
};


int main() {
    Game game;
    game.play();
    std::cout << "Catching Bunny. Have Fun!" << std::endl;
    return 0;
}