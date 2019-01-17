#include <iostream>
#include <cassert>
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

#define SCENE_SIZE 5

// 兔子类，属性：坐标
class Bunny {
public:
    Bunny(int x, int y) {
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

// 场景类：场景里随机生存一定数量兔子
// vector<Bunny> 用于存放场景里的兔子
// removeBunny(target), 将场景里的任意一个兔子转移到 user 下
// Iterable
// Iterator
class Scene {
public:
    Scene() { iterator_ = bunnies_.begin(); }

    void initialScene() {
        cout << "bunny number is " << DEFAULT_BUNNY_NUM << endl;
        for (int i = 0; i < DEFAULT_BUNNY_NUM; i++) {
            addBunny();
        }
    }

    void addBunny() {
        bunnies_.emplace_back(rand() % SCENE_SIZE,rand() % SCENE_SIZE);// default call constructor
        cout << "a bunny appeared at: " << bunnies_.back().getX() << "," << bunnies_.back().getY() << endl;
    }
    //void removeBunny(Bunny& bunny, vector<Bunny>& target) {
    //void removeBunny(Bunny bunny, vector<Bunny>& target) {
    //    target.push_back(move(bunny));
    //}
    bool hasNext() {
        return iterator_ != bunnies_.end();
    }
    vector<Bunny>::iterator initialIterator() {
        iterator_ = bunnies_.begin();
        return iterator_;
    }
    Bunny& getNext() {
        return *(iterator_++);
    }
    int getNumOfBunnies() {
        return bunnies_.size();
    }
    vector<Bunny>& getBunnies() {
        return bunnies_;
    }
private:
    vector<Bunny> bunnies_;
    vector<Bunny>::iterator iterator_;
};

// 玩家类，拥有 vector<Bunny> 用于装已经被抓到的兔子
class User {
public:
    User() {
        scene_ = nullptr;
    }
    int getBunnyCount() {
        return bunnies_.size();
    }
    vector<Bunny> getBunnies() {
        return bunnies_;
    }
    bool catchBunny(int x, int y) {
        assert(scene_);
//        vector<Bunny>::iterator iter = scene_.getIterator();
//        while (scene_.hasNext()) {
//            //Bunny& bunny = scene_.getNext();
//            Bunny bunny = scene_.getNext();
//            if (position.getX() == bunny.getPosition().getX() && position.getY() == bunny.getPosition().getY()) {
//                move()
//                scene_.removeBunny(bunny, bunnies_);
//                cout << "Congratulation. Caught a bunny." << endl;
//                cout << "The number of bunnies in scene is : " << scene_.getNumOfBunnies() << "\n"
//                     << "The number of bunnies caught by player is : " << getNumOfBunnies() << endl;
//                return true;
//            }
//        }
         for (int i = 0; i < scene_->getNumOfBunnies(); i++) {
            //cout << "enter" << endl;
             const int bunnyX = scene_->getBunnies().at(i).getX();
             const int bunnyY = scene_->getBunnies().at(i).getY();
             //cout << "this bunny at " << bunnyX << " , " << bunnyY << endl;
             if (x == bunnyX && y == bunnyY) {
                 cout << "befor move" << endl;
                 cout << "the size of bunny vector is " << bunnies_.size() << endl;
                 //move(scene_.getBunnies().begin() + i, scene_.getBunnies().begin() + i + 1, back_inserter(this->bunnies_));
                 bunnies_.push_back(move(scene_->getBunnies().at(i)));
                 scene_->getBunnies().erase(scene_->getBunnies().begin() + i);
                 cout << "Congratulation. Caught a bunny." << endl;
                 cout << "The number of bunnies in scene is : " << scene_->getNumOfBunnies() << "\n"
                 << "The number of bunnies caught by player is : " << getNumOfBunnies() << endl;
                 return true;
             }
         }


        cout << "Sorry, there is no bunny. Try again. Have Fun." << endl;
        return false;
    }



    void enterScene(Scene& scene) {
        scene_ = &scene;
    }
    int getNumOfBunnies() {
        return bunnies_.size();
    }
private:
    vector<Bunny> bunnies_;
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
            int y = 0;
            cin >> x >> y;
            cout << "you are going to catch at " << x << "," << y << endl;
            user_.catchBunny(x, y);
        }
    }

private:
    Scene scene_;
    User user_;
};


int main() {
//    vector<string> src {"aaa", "bbb"};
//    cout<< "size of src is " << src.size() << endl;
//    vector<string> target {"ccc"};
//    cout<< "size of target is " << target.size() << endl;
//
//    move(src.begin(), src.begin() + 1, back_inserter(target));
//    src.erase(src.begin());
//
//
//    cout<< "After moving, size of src is " << src.size() << endl;
//    cout<< "After moving, size of target is " << target.size() << endl;

    Game game;
    game.play();
    std::cout << "Catching Bunny. Have Fun!" << std::endl;
    return 0;
}