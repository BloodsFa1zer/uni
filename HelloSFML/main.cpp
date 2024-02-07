//#include <SFML/Graphics.hpp>
//#include <iostream>
//
//using namespace sf;
//using namespace std;
//const int radius = 25;
//const Color standartColor(51, 255, 153);
//
//float pow (float a)
//{
//    return a*a;
//}
//
//int main() {
//    bool click = false;
//    float angle = 0, tempAngle = 0, radiusTrajekt = 0, cntClick = 0;
//    int time = M_PI/2, cnt = 0;
//    double speed = 0.0;
//
//    cout << "Input speed:";
//    cin >> speed;
//
//    speed *= 180.0;
//
//    RenderWindow window(VideoMode(1900, 1000), "SFML works!");
//
//    Color ColorTemp(0,0,0);
//
//
//    Vector2f inputCenter, inputPoint, tempPoint, TempRadius, TempCenter, temp;
//    CircleShape circle, point;
//
//    VertexArray trochoid(LineStrip, 360);
//    VertexArray earth(Lines, 2);
//    VertexArray lineRadius(Lines, 2);
//
//    circle.setRadius(0);
//    circle.setFillColor(sf::Color::Yellow);
//
//    sf::ConvexShape triangle;
//    triangle.setPointCount(3);
//
//    // Define the coordinates for the triangle's vertices
//    sf::Vector2f vertex1(800.0f, 300.0f); // Bottom-left vertex
//    sf::Vector2f vertex2(600.0f, 500.0f); // Bottom-right vertex
//    sf::Vector2f vertex3(1000.0f, 500.0f); // Top-right vertex
//
//    triangle.setPoint(0, vertex1);
//    point.setFillColor(sf::Color::Red);
//    point.setRadius(4.0);
//    point.setPosition(vertex2.x-4, vertex2.y);
//
//    circle.setRadius(25.0);
//    circle.setPosition(vertex2.x-25, vertex2.y);
//    circle.setOutlineColor(Color(105, 105, 105));
//
//    triangle.setPoint(1, vertex2);
//    triangle.setPoint(2, vertex3);
//    triangle.setFillColor(sf::Color::Green);  // Fill color of the triangle
//
//    float degrees = 120;
//    float radians = - degrees * (3.14159265359 / 180);
//
//    bool flag = true;
//    while (window.isOpen()) {
//        Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == Event::Closed) {
//                window.close();
//            }
//        }
//
//        if (radiusTrajekt != 0) {
//            tempPoint.x = inputCenter.x + radius * (tempAngle - angle) + radiusTrajekt * sin(tempAngle);
//            tempPoint.y = inputCenter.y - radiusTrajekt * cos(tempAngle);
//            temp.x = tempPoint.x ;
//            temp.y = tempPoint.y;
//            trochoid.append(temp);
//            tempAngle += M_PI / speed;
//
//            TempCenter.x = inputCenter.x + radius * (tempAngle - angle);
//            TempRadius.x = inputCenter.x + radius * (tempAngle - angle) - radius * sin(tempAngle);
//            TempRadius.y = inputCenter.y + radius * cos(tempAngle);
//            lineRadius[1] = TempRadius;
//            lineRadius[0] = TempCenter;
//            point.setPosition(tempPoint.x - 4, tempPoint.y - 4);
//            circle.setPosition(TempCenter.x - radius, TempCenter.y - radius);
//        } else trochoid.clear();
//
//
//        if (event.type == sf::Event::KeyPressed) click = true;
//            if (event.key.code == sf::Keyboard::Enter) {
//                click = false;
//                if(cntClick == 0) {
//                    circle.setPosition(vertex2.x - radius, vertex2.y - radius);
//                    inputCenter.x = vertex2.x;
//                    inputCenter.y = vertex2.y + 25;
//                    TempCenter = inputCenter;
//                }
//
//                inputPoint.x = vertex2.x;
//                inputPoint.y = vertex2.y;
//                float deltaX = abs(inputCenter.x - inputPoint.x);
//                float deltaY = abs(inputCenter.y - inputPoint.y);
//
//                radiusTrajekt = sqrt(pow(deltaX) + pow(deltaY));
//                angle = acos(deltaY / radiusTrajekt);
//
//                tempAngle = angle;
//                point.setPosition(Vector2f(inputPoint.x, inputPoint.y));
//
//                cntClick++;
//            }
//
//        if (vertex3.x <= point.getPosition().x) {
//            sf::Vector2f vertex = triangle.getPoint(3);
//            sf::Transform transform;
//            transform.rotate(radians, vertex2);
//
//            sf::Vector2f newPosition = transform.transformPoint(circle.getPosition());
//            circle.setPosition(newPosition);
//            sf::Vector2f newPosition1 = transform.transformPoint(point.getPosition());
//            point.setPosition(newPosition1);
//        }
//
//
//
//        window.clear();
//        window.draw(triangle);
//        window.draw(circle);
//        window.draw(trochoid);
//        window.draw(point);
//
//
//        window.display();
//
//    }
//
//    return 0;
//}


#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;



double crossProduct(const Vector2f & A, const Vector2f & B, const Vector2f & C) {
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

bool isConvexPolygon(const std::vector<Vector2f>& polygon) {
    int n = polygon.size();
   int pos = 0, neg = 0;

    for (int i = 0; i < n; i++) {
        double result = crossProduct(polygon[i], polygon[(i + 1) % n], polygon[(i + 2) % n]);
        if (result > 0) {
            pos++;
        } else if (result < 0) {
            neg++;
        }
    }

    return (pos == 0 || neg == 0);
}

int main() {

    VideoMode desktopMode = VideoMode::getDesktopMode();
    RenderWindow window(VideoMode(desktopMode), "SFML Application");

    vector<Vector2f> polygonPoints;
    VertexArray lines(LineStrip);

    bool isDrawing = true;

    while (window.isOpen()) {

        Event event{};

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    // Connect the last point with the first to close the polygon
                    if (polygonPoints.size() >= 3) {
                        lines.append(sf::Vertex(polygonPoints.back()));
                        lines.append(sf::Vertex(polygonPoints.front()));


                        isDrawing = false; // Stop drawing after closing the polygon
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && isDrawing) {
                sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
                polygonPoints.push_back(mousePosition);

                lines.append(Vertex(mousePosition));
            }
            if (event.type == Event::Closed) {
                window.close();
            }
        }


        window.clear();
        window.draw(lines);

        if (!isDrawing) {
            // Draw a filled polygon when finished
            ConvexShape polygon;
            polygon.setPointCount(polygonPoints.size());
            for (int i = 0; i < polygonPoints.size(); i++) {
                polygon.setPoint(i, polygonPoints[i]);
            }
            polygon.setFillColor(Color::Green);
            window.draw(polygon);

        }

        window.display();
    }

    if (!isConvexPolygon(polygonPoints)) {
        cout << "The polygon is concave." << endl;
    } else {
        cout << "The polygon is convex." << endl;
    }
}