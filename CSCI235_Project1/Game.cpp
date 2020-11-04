/*
Jonathan Balina
CSCI 235 Project 1
Prof. Shostak
*/
#include "Game.h"

//basic constructor
Tractor::Tractor()
{
    x = 0;
    y = 0;
    size = 1;
    activity = IDLE;
}

//I used the given size to find the coordinates of all corners of the box of the tractor
Tractor::Tractor(int x_val, int y_val, unsigned short size_val, Activity activity_val)
{
    x = x_val;
    y = y_val;
    size = size_val;
    activity = activity_val;
    maxX = (x + (size/2));
    minX = (x - (size/2));
    maxY = (y + (size/2));
    minY = (y - (size/2));
}

//setter for x,y values
void Tractor::move(int x_val, int y_val)
{
    x = x_val;
    y = y_val;
    maxX = (x + (size/2));
    minX = (x - (size/2));
    maxY = (y + (size/2));
    minY = (y - (size/2));
}

//getter for x
int Tractor::getX() const
{
    return x;
}

//getter for y
int Tractor::getY() const
{
    return y;
}

//get size
unsigned short Tractor::getSize() const
{
    return size;
}

//setter for size
void Tractor::setSize(unsigned short size_val)
{
    size = size_val;
}

//get activity
Activity Tractor::getActivity() const
{
    return activity;
}

//set activity
void Tractor::setActivity(Activity activity_val)
{
    activity = activity_val;
}

//get the top x coordinate of the tractor box
double Tractor::getMaxX() const
{
    return maxX;
}

//get the lowest x coordinate of the tractor box
double Tractor::getMinX() const
{
    return minX;
}

//get the top y coordinate of the tractor box
double Tractor::getMaxY() const
{
    return maxX;
}

//get the lowest y coordinate of the tractor box
double Tractor::getMinY() const
{
    return minX;
}

//converts Activity value into a string
std::string Tractor::enumToString() const
{
    if(activity == IDLE)
        return "IDLE";
    else if(activity == SEEDING)
        return "SEEDING";
    else if(activity == HARVESTING)
        return "HARVESTING";
    else if(activity == MOVING)
        return "MOVING";

}

//constructor
Game::Game(unsigned int new_size)
{
    map_size = new_size;

}

//I used a for loop to look through the all vector and find the tractor with matching x and y coordinates inside its box. Then returns index
//if not found it returns -1.
int Game::GetTractor(int x, int y) const
{
    for(int i = 0; i < all.size(); i++)
    {
        //checks if x and y are within the range of a Tractors maximum and minimum x and y values
        if((all[i].getMinX() <= x) && (x <= all[i].getMaxX()) &&(all[i].getMinY() <= y) && (y <= all[i].getMaxY()))
            return i;
    }
    return -1;
}

//uses GetTractor to determine if Tractor at x,y exists. Then adds index to selected vector
void Game::SelectTractor(int x, int y)
{
    selected.clear();
    if(GetTractor(x,y)!=-1)
    {
        selected.push_back(GetTractor(x,y));
    }
}

//I first made variables low_x, high_x, low_y, and high_y in order to find the coordinates of each corner the rectangle.
//Then, using a for loop I went through the all vector and checked if any points of the Tractors were present within the selection rectangle
void Game::SelectTractors(int x1, int y1, int x2, int y2)
{
    //first cleared selected vector
    selected.clear();
    //made four variables to find coordinates of each corner of selection rectangle
    //used if statements to find the lower corner of the rectangle
    int low_x; int high_x; int low_y; int high_y;
    if(x1 > x2)
    {
        low_x = x2;
        high_x = x1;
    }
    else
    {
        low_x = x1;
        high_x = x2;
    }
    if(y1 > y2)
    {
        low_y = y2;
        high_y = y1;
    }
    else
    {
        low_y = y1;
        high_y = y2;
    }
    //ensured that rectangle is within the range of the map
    if(low_x < 0)
        low_x = 0;
    if(low_y < 0)
        low_y = 0;
    if(high_x >= map_size)
        high_x = map_size-1;
    if(high_y >= map_size)
        high_y = map_size-1;
    /*
    for loop loops through the all vector.
    I checked if any of the corner points of the Tractor square appeared within the selection rectangle and vice versa
    e.g. I checked if the coordinates of the lower left corner of a tractor box(all[i].getMinX(), all[i].getMinY()) appeared
    within the range of the lowest and highest x coordinates of the selection rectangle and the lowest and highest y coordinates
    */
    for(int i = 0; i < all.size(); i++)
    {
        if(((low_x <= all[i].getMinX()) && (all[i].getMinX() <= high_x) && (low_y <= all[i].getMinY()) && (all[i].getMinY() <= high_y)) ||
           ((low_x <= all[i].getMaxX()) && (all[i].getMaxX() <= high_x) && (low_y <= all[i].getMinY()) && (all[i].getMinY() <= high_y)) ||
           ((low_x <= all[i].getMinX()) && (all[i].getMinX() <= high_x) && (low_y <= all[i].getMaxY()) && (all[i].getMaxY() <= high_y)) ||
           ((low_x <= all[i].getMaxX()) && (all[i].getMaxX() <= high_x) && (low_y <= all[i].getMaxY()) && (all[i].getMaxY() <= high_y)) ||
           ((all[i].getMinX() <= low_x) && (low_x <= all[i].getMaxX()) && (all[i].getMinY() <= low_y) && (low_y <= all[i].getMaxY())) ||
           ((all[i].getMinX() <= high_x) && (high_x <= all[i].getMaxX()) && (all[i].getMinY() <= low_y) && (low_y <= all[i].getMaxY())) ||
           ((all[i].getMinX() <= low_x) && (low_x <= all[i].getMaxX()) && (all[i].getMinY() <= high_y) && (high_y <= all[i].getMaxY())) ||
           ((all[i].getMinX() <= high_x) && (high_x <= all[i].getMaxX()) && (all[i].getMinY() <= high_y) && (high_y <= all[i].getMaxY())))
        {
            selected.push_back(i);
        }
    }
}

//I first checked if the Tractor to be added can fit in the map. If it fits then inserted it into the all vector
void Game::AddTractor(const Tractor& new_unit)
{
    //I created a boolean variable for if the Tractor fits
    bool canFit = false;
    //I first checked if the Tractor fit within the range of the map
    if((0 <= new_unit.getMinX()) && (new_unit.getMaxX() < map_size) && (0 <= new_unit.getMinY()) && (new_unit.getMaxY() < map_size))
        canFit = true;
    //I then went through a similar checking process as in the SelectTractors method where i checked if the corners of any of the Tractor squares intersected
    for(int i = 0; i < all.size(); i++)
    {
        if(((all[i].getMinX() <= new_unit.getMinX()) && (new_unit.getMinX() <= all[i].getMaxX()) && (all[i].getMinY() <= new_unit.getMinY()) && (new_unit.getMinY() <= all[i].getMaxY())) ||
           ((all[i].getMinX() <= new_unit.getMaxX()) && (new_unit.getMaxX() <= all[i].getMaxX()) && (all[i].getMinY() <= new_unit.getMinY()) && (new_unit.getMinY() <= all[i].getMaxY())) ||
           ((all[i].getMinX() <= new_unit.getMinX()) && (new_unit.getMinX() <= all[i].getMaxX()) && (all[i].getMinY() <= new_unit.getMaxY()) && (new_unit.getMaxY() <= all[i].getMaxY())) ||
           ((all[i].getMinX() <= new_unit.getMaxX()) && (new_unit.getMaxX() <= all[i].getMaxX()) && (all[i].getMinY() <= new_unit.getMaxY()) && (new_unit.getMaxY() <= all[i].getMaxY())) ||
           ((new_unit.getMinX() <= all[i].getMinX()) && (all[i].getMinX() <= new_unit.getMaxX()) && (new_unit.getMinY() <= all[i].getMinY()) && (all[i].getMinY() <= new_unit.getMaxY())) ||
           ((new_unit.getMinX() <= all[i].getMaxX()) && (all[i].getMaxX() <= new_unit.getMaxX()) && (new_unit.getMinY() <= all[i].getMinY()) && (all[i].getMinY() <= new_unit.getMaxY())) ||
           ((new_unit.getMinX() <= all[i].getMinX()) && (all[i].getMinX() <= new_unit.getMaxX()) && (new_unit.getMinY() <= all[i].getMaxY()) && (all[i].getMaxY() <= new_unit.getMaxY())) ||
           ((new_unit.getMinX() <= all[i].getMaxX()) && (all[i].getMaxX() <= new_unit.getMaxX()) && (new_unit.getMinY() <= all[i].getMaxY()) && (all[i].getMaxY() <= new_unit.getMaxY())))
        {
            canFit = false;
        }
    }
    //if the canFit variable remained true then the Tractor was added to the all vector
    if(canFit)
    {
        all.push_back(new_unit);
    }
}

//I first checked is Tractor i exists within the all vector, then i check if it will be within bounds in the new location
//i then check if it will intersect with other tractors in the new location
bool Game::MoveTractor(int i, int new_x, int new_y)
{
    //I use boolean canMove to determine if the tractor will be able to move
    bool canMove = false;
    //first checking for if the Tractor exists in all vector
    if(i < all.size())
    {
        canMove = true;
        Tractor temp = all[i];
        //i use a temporary Tractor to simulate if i moved the actual tractor
        temp.move(new_x, new_y);
        //I checked if the new location tractor is within bounds of the map
        if((temp.getMinX() < 0) || (temp.getMaxX() >= map_size) || (temp.getMinY() < 0) || (temp.getMaxY() >= map_size))
        {
            canMove = false;
        }
        //Then I used similar method of checking as the SelectTractors method to check if Tractor corners intersect
        for(int j = 0; j < all.size(); j++)
        {
            if(j != i)
            {
                if(((all[j].getMinX() <= temp.getMinX()) && (temp.getMinX() <= all[j].getMaxX()) && (all[j].getMinY() <= temp.getMinY()) && (temp.getMinY() <= all[j].getMaxY())) ||
                   ((all[j].getMinX() <= temp.getMaxX()) && (temp.getMaxX() <= all[j].getMaxX()) && (all[j].getMinY() <= temp.getMinY()) && (temp.getMinY() <= all[j].getMaxY())) ||
                   ((all[j].getMinX() <= temp.getMinX()) && (temp.getMinX() <= all[j].getMaxX()) && (all[j].getMinY() <= temp.getMaxY()) && (temp.getMaxY() <= all[j].getMaxY())) ||
                   ((all[j].getMinX() <= temp.getMaxX()) && (temp.getMaxX() <= all[j].getMaxX()) && (all[j].getMinY() <= temp.getMaxY()) && (temp.getMaxY() <= all[j].getMaxY())) ||
                   ((temp.getMinX() <= all[j].getMinX()) && (all[j].getMinX() <= temp.getMaxX()) && (temp.getMinY() <= all[j].getMinY()) && (all[j].getMinY() <= temp.getMaxY())) ||
                   ((temp.getMinX() <= all[j].getMaxX()) && (all[j].getMaxX() <= temp.getMaxX()) && (temp.getMinY() <= all[j].getMinY()) && (all[j].getMinY() <= temp.getMaxY())) ||
                   ((temp.getMinX() <= all[j].getMinX()) && (all[j].getMinX() <= temp.getMaxX()) && (temp.getMinY() <= all[j].getMaxY()) && (all[j].getMaxY() <= temp.getMaxY())) ||
                   ((temp.getMinX() <= all[j].getMaxX()) && (all[j].getMaxX() <= temp.getMaxX()) && (temp.getMinY() <= all[j].getMaxY()) && (all[j].getMaxY() <= temp.getMaxY())))
                {
                    canMove = false;
                }
            }
        }
    }
    //if canMove remained true then it will move the actual tractor
    if(canMove)
    {
        all[i].move(new_x, new_y);
    }
    return canMove;
}

//goes through the selected vector and sets the activity to new_activity
void Game::AssignTractorsActivity(Activity new_activity)
{
    for(int i = 0; i < selected.size(); i++)
    {
        all[selected[i]].setActivity(new_activity);
    }
}

//prints the information of the Tractor at index i
void Game::PrintTractor(int i) const
{
    std::cout << "Tractor #" << i << ":" << std::endl;
    std::cout << "Location: " << all[i].getX() << ", " << all[i].getY() << std::endl;
    std::cout << "Size: " << all[i].getSize() << std::endl;
    std::cout << "Activity: " << all[i].enumToString() << std::endl;
}

//loops through the selected vector and prints each tractors information
void Game::PrintSelectedTractors() const
{
    for(int i = 0; i < selected.size(); i++)
    {
        std::cout << "Tractor #" << selected[i] << ":" << std::endl;
        std::cout << "Location: " << all[selected[i]].getX() << ", " << all[selected[i]].getY() << std::endl;
        std::cout << "Size: " << all[selected[i]].getSize() << std::endl;
        std::cout << "Activity: " << all[selected[i]].enumToString() << std::endl;
    }
}

//loops through the all vector and prints each tractors information
void Game::PrintAllTractors() const
{
    for(int i = 0; i < all.size(); i++)
    {
        std::cout << "Tractor #" << i << ":" << std::endl;
        std::cout << "Location: " << all[i].getX() << ", " << all[i].getY() << std::endl;
        std::cout << "Size: " << all[i].getSize() << std::endl;
        std::cout << "Activity: " << all[i].enumToString() << std::endl;
    }
}
