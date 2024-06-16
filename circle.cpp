#include<iostream>
#include<vector>
#include<cmath>
#include<windows.h>

using namespace std;


void display();
void fillArrayZero(int array[29][60]);


struct point
{
    double x, y, z;
    double centerX, centerY, centerZ;
};


class Circle
{
    /*This is a cicrle class with a center and radius*/
private:
    int radius;
    vector<point> points;
    int points2D[29][60] = {};
    int ZindexArray[29][60];
public:
    Circle(/* args */);
    Circle(int r);
    ~Circle();
    void initialize();
    int checkPoint(int x, int y);
    void rotateY(int degree);
    void display();
    void initializeDonut();
    int calculateLight(point p);
    bool calculateScrrenFacing(point p);
};
Circle::Circle()
{   
    radius = 15;
}
Circle::Circle(int r) {
    radius = r;
}
Circle::~Circle()
{
}
void Circle::initialize() {
    points.clear();
    for(int o = 0; o < 360; o = o + 10) {
        double radians = o * 3.1415926535 / 180.0; // Convert degrees to radians
        point p;
        p.x = (radius * cos(radians));
        p.y = (radius * sin(radians));
        p.z = 0;
        p.centerX = 0;
        p.centerY = 0;
        p.centerZ = 0;
        points.emplace_back(p);
    }
}
int Circle::checkPoint(int x, int y) {
    // for(auto& i : points2D) {
    //     if((int)i.x == x && (int)i.y == y) {
    //         return i.z;
    //     }
    // }
    return -1;
}
void Circle::rotateY(int degree = 10) {
    double rad = degree * 3.14159265 / 180.0;
    double radX = (360 - degree) * 3.14159265 / 180.0;
    int screen_distance = 40;
    int obj_distance = 30;
    fillArrayZero(ZindexArray);
    fillArrayZero(points2D);
    for(point &i : points) {
        point p;
        //Rotation on X-axis
       // p.y = (i.y * cos(radX) - i.z * sin(radX));
        //p.z = (i.y * sin(radX) + i.z * cos(radX));
        //p.x = i.x;
        //Rotation on Y-axis
        //p.x = (i.x * cos(rad) + i.z * sin(rad));
        //p.z = (-i.x * sin(rad) + i.z * cos(rad));

        //Rotation X-Y axis
        //p.x = (i.x * cos(rad) + i.y * 0 + i.z * sin(rad));
        //p.y = (i.x * sin(radX) * sin(rad) + i.y * cos(radX) - i.z * cos(rad) * sin(radX));
        //p.z = (-i.x * cos(radX) * sin(rad) + i.y * sin(radX) + i.z * cos(radX) * cos(rad));

        //Rotation X-Z axis
        p.x = (i.x * cos(rad) - i.y * sin(rad) * cos(radX) + i.z * sin(radX) * sin(rad));
        p.y = (i.x * sin(rad) + i.y * cos(rad) * cos(radX) - i.z * cos(rad) * sin(radX));
        p.z = (i.y * sin(radX) + i.z * cos(radX));

        p.centerX = (i.centerX * cos(rad) - i.centerY * sin(rad) * cos(radX) + i.centerZ * sin(radX) * sin(rad));
        p.centerY = (i.centerX * sin(rad) + i.centerY * cos(rad) * cos(radX) - i.centerZ * cos(rad) * sin(radX));
        p.centerZ = (i.centerY * sin(radX) + i.centerZ * cos(radX));

        //Scale it on the screen with z distance
        //30 is the distance between the object and the screen     
        p.z = p.z + screen_distance + obj_distance;
        p.centerZ = p.centerZ + screen_distance + obj_distance;
        if(p.z > 0) {
            p.x = p.x * (screen_distance / p.z);
            p.y = p.y * (screen_distance / p.z);
            int rounded_x = (int)(p.x) + 30;
            int rounded_y = (int)(p.y) + 15;
            if(rounded_x >= 0 && rounded_x < 60 && rounded_y >= 0 && rounded_y < 29) {
                //cout << points2D[rounded_y][rounded_x];
                if (ZindexArray[rounded_y][rounded_x] > p.z && calculateScrrenFacing(p)) {
                    int L = calculateLight(p);
                    points2D[rounded_y][rounded_x] = L;
                    ZindexArray[rounded_y][rounded_x] = p.z;
                    // ZindexArray[rounded_y][rounded_x + 1] = p.z;
                    // ZindexArray[rounded_y][rounded_x - 1] = p.z;
                    // ZindexArray[rounded_y + 1][rounded_x] = p.z;
                    // ZindexArray[rounded_y - 1][rounded_x] = p.z;
                    // ZindexArray[rounded_y +1 ][rounded_x + 1] = p.z;
                    // ZindexArray[rounded_y - 1][rounded_x - 1] = p.z;
                    // ZindexArray[rounded_y + 1][rounded_x - 1] = p.z;
                    // ZindexArray[rounded_y - 1][rounded_x + 1] = p.z;
                    //cout << "added";
                }
            }
        } 
    }
}
void Circle::display() {
    for(int y = 0; y < 29; y++) {
        cout << y;
        for(int x = 0; x < 60; x++) {
            //This screen going be on at z = 20 so anything greater than z = 20 will not be displayed
            if(points2D[y][x] == 0) cout << " ";
            else if(points2D[y][x] == 1) cout << ".";
            else if(points2D[y][x] == 2) cout << "-";
            else if(points2D[y][x] == 3) cout << "=";
            else if(points2D[y][x] == 4) cout << "#";
            else if(points2D[y][x] == 5) cout << "@";
            else cout << " ";
            cout << " ";
        }
        cout << endl;
    }
}
void Circle::initializeDonut() {
    initialize();
    for(auto& i : points) {
        i.x = radius + 10 + i.x;
        i.centerX = radius + 10 + i.centerX;
    }
    vector<point> points_copy = points;
    for(int deg = 0; deg < 360; deg = deg + 5) {
        for(auto& i : points_copy) {
            double rad = deg * 3.1415926535 / 180.0; // Convert degrees to radians
            //Rotation on Y-axis
            point p;
            p.x = (i.x * cos(rad) + i.z * sin(rad));
            p.z = (-i.x * sin(rad) + i.z * cos(rad));
            p.y = i.y;

            p.centerX = (i.centerX * cos(rad) + i.centerZ * sin(rad));
            p.centerZ = (-i.centerX * sin(rad) + i.centerZ * cos(rad));
            p.centerY = i.centerY;
            points.emplace_back(p);
        }
    }   
}
int Circle::calculateLight(point p) {
    double normalX = p.x - p.centerX;
    double normalY = p.y - p.centerY;
    double normalZ = p.z - p.centerZ;

    double i = sqrt(normalX * normalX + normalY * normalY + normalZ * normalZ);

    double rad = acos((-normalY - normalZ) / (sqrt(2) * i));

    if(rad < 3.14 / 8) return 5;
    else if (rad < 3.14 / 4) return 4;
    else if (rad < 3.14 / 3) return 3;
    else if (rad < (3.14 / 3) * 2) return 2;
    else if (rad < (3.14 / 6) * 5) return 1;
    else return 0;
}
bool Circle::calculateScrrenFacing(point p) {
    double normalX = p.x - p.centerX;
    double normalY = p.y - p.centerY;
    double normalZ = p.z - p.centerZ;

    double i = sqrt(normalX * normalX + normalY * normalY + normalZ * normalZ);

    double rad = acos((-0 - normalZ) / (sqrt(1) * i));
    if (rad < (3.14 / 3) * 2) return true;
    else return false;
}
void fillArrayZero(int array[29][60]) {
    for (int y = 0; y < 29; y++)
    {
        for (int x = 0; x < 60; x++)
        {
            array[y][x] = 1000000;
        }
        
    }
}

int main() {
    Circle c;
    c.initializeDonut();
    for(int i = 0; i >= 0; i = i + 5) {    
        c.rotateY(i % 360);
        c.display();
        cout << flush << "\u001b[30A" << flush;
        Sleep(30);
        cout << flush << "\u001b[11A" << flush;
    }
    
    return 0;
}