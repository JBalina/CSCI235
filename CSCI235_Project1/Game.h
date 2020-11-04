/*
Jonathan Balina
CSCI 235 Project #1
Prof. Shostak
*/

#ifndef GAME_H
#define GAME_H
#include <vector>
#include <iostream>
#include <string>
enum Activity {SEEDING, HARVESTING, MOVING, IDLE};

class Tractor
{
private:
    int x;
    int y;
    unsigned short size;
    Activity activity;
    double minX;
    double minY;
    double maxX;
    double maxY;
public:
    Tractor();
    Tractor(int x_val, int y_val, unsigned short size_val, Activity activity_val);
    void move(int x_val, int y_val);
    int getX() const;
    int getY() const;
    unsigned short getSize() const;
    void setSize(unsigned short size_val);
    Activity getActivity() const;
    void setActivity(Activity activity_val);
    double getMinX() const;
    double getMaxX() const;
    double getMinY() const;
    double getMaxY() const;
    std::string enumToString() const;
};

class Game
{
private:
    unsigned int  map_size;
    std::vector<Tractor> all;
    std::vector<int> selected;
public:
    Game(unsigned int new_size);
    int GetTractor(int x, int y) const;
    void SelectTractor(int x, int y);
    void SelectTractors(int x1, int y1, int x2, int y2);
    void AddTractor(const Tractor& new_unit);
    bool MoveTractor(int i, int new_x, int new_y);
    void AssignTractorsActivity(Activity new_activity);
    void PrintTractor(int i) const;
    void PrintSelectedTractors() const;
    void PrintAllTractors() const;
};

#endif
